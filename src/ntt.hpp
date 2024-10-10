#pragma once
#ifndef NTT_VERSION
#define NTT_VERSION 1
#endif
#if NTT_VERSION == 0
#include "ntt0.hpp"
#elif NTT_VERSION == 1
#include "ntt1.hpp"
#elif
#error "invaild argument: NTT_VERSION"
#endif
