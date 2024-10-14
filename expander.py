#!/usr/bin/env pypy3
# thanks ac-library <https://github.com/atcoder/ac-library>

import re
import sys
import argparse
from logging import Logger, basicConfig, getLogger
from os import getenv, environ, pathsep
from pathlib import Path
from typing import List, Set, Optional


logger = getLogger(__name__)  # type: Logger


class Expander:
    atcoder_include = re.compile(
        # '#include\s*["<](atcoder/[a-z_]*(|.hpp))[">]\s*')
        r'#include\s*["<]poly/([a-z_0-9]*(|.hpp)|header.h)[">]\s*'
    )
    std_include = re.compile(
        r'#include\s*["<]([a-z]*|bits/stdc\+\+.h)[">]\s*|\s*using\s*namespace\s*std\s*;\s*'
    )

    # include_guard = re.compile(r'#.*ATCODER_[A-Z_]*_HPP')

    def is_ignored_line(self, line) -> bool:
        # if self.include_guard.match(line):
        #     return True
        if line.strip() == "#pragma once":
            return True
        if line.strip().startswith("//"):
            return True
        return False

    def __init__(self, lib_paths: List[Path], replaces: List[str]):
        self.lib_paths = lib_paths
        self.replaces = replaces

    included = set()  # type: Set[Path]
    std_included = set()

    def find_acl(self, acl_name: str) -> Path:
        for lib_path in self.lib_paths:
            path = lib_path / "poly" / acl_name
            logger.info(lib_path)
            logger.info(path)
            if path.exists():
                return path
        logger.error("cannot find: {}".format(acl_name))
        raise FileNotFoundError()

    def expand_acl(self, acl_file_path: Path) -> List[str]:
        while acl_file_path.name in self.replaces:
            replace_to = self.replaces[acl_file_path.name]
            logger.info("{} -> {}".format(acl_file_path.name, replace_to))
            acl_file_path = self.find_acl(replace_to)
        if acl_file_path in self.included:
            logger.info("already included: {}".format(acl_file_path.name))
            return []
        self.included.add(acl_file_path)
        logger.info("include: {}".format(acl_file_path.name))

        acl_source = open(str(acl_file_path)).read()

        result = []  # type: List[str]
        for line in acl_source.splitlines():
            if self.is_ignored_line(line):
                continue

            m = self.atcoder_include.match(line)
            if m:
                name = m.group(1)
                result.extend(self.expand_acl(self.find_acl(name)))
                continue

            m2 = self.std_include.match(line)
            if m2:
                code = m2.group(0)
                if code not in self.std_included:
                    logger.info('write: "{}"'.format(code))
                    self.std_included.add(code)
                else:
                    logger.info('already written: "{}"'.format(code))
                    continue

            result.append(line)
        return result

    def expand(self, source: str) -> str:
        self.included = set()
        result = []  # type: List[str]
        for line in source.splitlines():
            m = self.atcoder_include.match(line)
            if m:
                acl_path = self.find_acl(m.group(1))
                result.extend(self.expand_acl(acl_path))
                continue

            m2 = self.std_include.match(line)
            if m2:
                code = m2.group(0)
                if code not in self.std_included:
                    self.std_included.add(code)
                    logger.info('write: "{}"'.format(code))
                else:
                    logger.info('already written: "{}"'.format(code))
                    continue

            result.append(line)
        return "\n".join(result)


lib_switchs = [{"name": "ntt", "vers": [0, 1]}]

if __name__ == "__main__":
    basicConfig(
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%H:%M:%S",
        level=getenv("LOG_LEVEL", "INFO"),
    )
    parser = argparse.ArgumentParser(description="Expander")
    parser.add_argument("source", help="Source File")
    parser.add_argument("-c", "--console", action="store_true", help="Print to Console")
    parser.add_argument("--lib", help="Path to Poly Library")
    parser.add_argument("-o", help="Output File", default='combined.cpp')
    for switch in lib_switchs:
        name = switch['name']
        vers = switch['vers']
        parser.add_argument(
            "--{}".format(name),
            help="{} version (in {} or -1 if including all versions)".format(name.upper(), list(vers)),
            default=-1,
        )

    opts = parser.parse_args()

    replaces = {}
    opts_dict = vars(opts)
    for switch in lib_switchs:
        name = switch['name']
        if opts_dict[name] != -1:
            replaces['{}.hpp'.format(name)] = '{}{}.hpp'.format(name, opts_dict[name])
    logger.info('versions: {}'.format(replaces))

    lib_paths = []
    if opts.lib:
        lib_paths.append(Path(opts.lib))
    if "CPLUS_INCLUDE_PATH" in environ:
        lib_paths.extend(
            map(Path, filter(None, environ["CPLUS_INCLUDE_PATH"].split(pathsep)))
        )
    lib_paths.append(Path.cwd())
    expander = Expander(lib_paths, replaces)
    source = open(opts.source).read()
    output = expander.expand(source)

    if opts.console:
        print(output)
    else:
        with open(opts.o, "w") as f:
            f.write(output)
