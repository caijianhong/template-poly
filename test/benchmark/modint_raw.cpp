#include <benchmark/benchmark.h>
#include "poly/modint.hpp"
#include <random>
using namespace std;
using mint = poly::modint<998244353>;
void mint_construct_const1(benchmark::State& state) {
  for (auto _ : state) {
    mint x = 1;
    benchmark::DoNotOptimize(x);
  }
}
BENCHMARK(mint_construct_const1);
void mint_construct_const2(benchmark::State& state) {
  for (auto _ : state) {
    mint x = mint::raw(1);
    benchmark::DoNotOptimize(x);
  }
}
BENCHMARK(mint_construct_const2);
void mint_construct_const3(benchmark::State& state) {
  for (auto _ : state) {
    mint x;
    x.v = 1;
    benchmark::DoNotOptimize(x);
  }
}
BENCHMARK(mint_construct_const3);
void mint_construct_const4(benchmark::State& state) {
  for (auto _ : state) {
    mint&& x = mint::raw(1);
    benchmark::DoNotOptimize(x);
  }
}
BENCHMARK(mint_construct_const4);

mt19937 rng{random_device{}()};


void mint_rndruct_rnd1(benchmark::State& state) {
  int y = rng() % mint::mod;
  for (auto _ : state) {
    mint x = y;
    benchmark::DoNotOptimize(x);
  }
}
BENCHMARK(mint_rndruct_rnd1);
void mint_rndruct_rnd2(benchmark::State& state) {
  int y = rng() % mint::mod;
  for (auto _ : state) {
    mint x = mint::raw(y);
    benchmark::DoNotOptimize(x);
  }
}
BENCHMARK(mint_rndruct_rnd2);
void mint_rndruct_rnd3(benchmark::State& state) {
  int y = rng() % mint::mod;
  for (auto _ : state) {
    mint x;
    x.v = y;
    benchmark::DoNotOptimize(x);
  }
}
BENCHMARK(mint_rndruct_rnd3);
void mint_rndruct_rnd4(benchmark::State& state) {
  int y = rng() % mint::mod;
  for (auto _ : state) {
    mint&& x = mint::raw(y);
    benchmark::DoNotOptimize(x);
  }
}
BENCHMARK(mint_rndruct_rnd4);
void mint_rndruct_1(benchmark::State& state) {
  int y = rng();
  for (auto _ : state) {
    mint x = y;
    benchmark::DoNotOptimize(x);
  }
}
BENCHMARK(mint_rndruct_1);
void mint_rndruct_2(benchmark::State& state) {
  int y = rng();
  for (auto _ : state) {
    mint x = mint::raw(y % mint::mod);
    benchmark::DoNotOptimize(x);
  }
}
BENCHMARK(mint_rndruct_2);
void mint_rndruct_3(benchmark::State& state) {
  int y = rng();
  for (auto _ : state) {
    mint x;
    x.v = y % mint::mod;
    benchmark::DoNotOptimize(x);
  }
}
BENCHMARK(mint_rndruct_3);
void mint_rndruct_4(benchmark::State& state) {
  int y = rng();
  for (auto _ : state) {
    mint&& x = mint::raw(y % mint::mod);
    benchmark::DoNotOptimize(x);
  }
}
BENCHMARK(mint_rndruct_4);
mt19937_64 rnd{random_device{}()};
void mint_rndruct_ll1(benchmark::State& state) {
unsigned   long long y = rnd();
  for (auto _ : state) {
    mint x = y;
    benchmark::DoNotOptimize(x);
  }
}
BENCHMARK(mint_rndruct_ll1);
void mint_rndruct_ll2(benchmark::State& state) {
  unsigned long long y = rnd();
  for (auto _ : state) {
    mint x = mint::raw(y % mint::mod);
    benchmark::DoNotOptimize(x);
  }
}
BENCHMARK(mint_rndruct_ll2);
void mint_rndruct_ll3(benchmark::State& state) {
unsigned   long long y = rnd();
  for (auto _ : state) {
    mint x;
    x.v = y % mint::mod;
    benchmark::DoNotOptimize(x);
  }
}
BENCHMARK(mint_rndruct_ll3);
void mint_rndruct_ll4(benchmark::State& state) {
unsigned   long long y = rnd();
  for (auto _ : state) {
    mint&& x = mint::raw(y % mint::mod);
    benchmark::DoNotOptimize(x);
  }
}
BENCHMARK(mint_rndruct_ll4);

BENCHMARK_MAIN();

