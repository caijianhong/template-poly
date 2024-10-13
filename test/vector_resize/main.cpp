#include <benchmark/benchmark.h>
#include <vector>
using namespace std;
void touch1(benchmark::State& state) {
  for (auto _ : state) {
    vector<int> vec;
    for (int i = 1; i <= state.range(0); i++) {
      vec.resize(i);
    }
  }
}
BENCHMARK(touch1)->RangeMultiplier(2)->Range(1, 1<<20);
void touch2(benchmark::State& state) {
  for (auto _ : state) {
    vector<int> vec{0};
    for (int i = 1; i <= state.range(0); i++) {
      while (vec.size() < i) vec.resize(vec.size() * 2);
    }
  }
}
BENCHMARK(touch2)->RangeMultiplier(2)->Range(1, 1<<20);
void touch3(benchmark::State& state) {
  for (auto _ : state) {
    vector<int> vec{0};
    for (int i = 1; i <= state.range(0); i++) {
      vec.reserve(i);
      while (vec.size() < i) vec.resize(vec.size() * 2);
    }
  }
}
BENCHMARK(touch3)->RangeMultiplier(2)->Range(1, 1<<20);
BENCHMARK_MAIN();
