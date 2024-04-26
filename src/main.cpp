#include <benchmark/benchmark.h>
#include <lib2k/random.hpp>
#include <vector>
#include <concepts>

static constexpr auto count = std::size_t{ 10'000'000 };

template<std::integral Integer>
[[nodiscard]] std::vector<Integer> random_vector(std::size_t const size, Integer const min, Integer const max) {
    auto result = std::vector<Integer>{};
    result.reserve(size);
    auto random = c2k::Random{};
    for (auto i = std::size_t{ 0 }; i < size; ++i) {
        result.push_back(random.next_integral(min, max));
    }
    return result;
}

static void no_range_check(benchmark::State& state) {
    auto const numbers = random_vector(count, 1u, 101u);
    auto const indices = random_vector(count, std::size_t{ 0 }, numbers.size());
    for (auto _ : state) {
        auto sum = decltype(numbers)::value_type{ 0 };
        for (auto const index : indices) {
            sum += numbers[index];
        }
        benchmark::DoNotOptimize(sum);
        benchmark::ClobberMemory();
    }
}

BENCHMARK(no_range_check);

static void with_range_check(benchmark::State& state) {
    auto const numbers = random_vector(count, 1u, 101u);
    auto const indices = random_vector(count, std::size_t{ 0 }, numbers.size());
    for (auto _ : state) {
        auto sum = decltype(numbers)::value_type{ 0 };
        for (auto const index : indices) {
            sum += numbers.at(index);
        }
        benchmark::DoNotOptimize(sum);
        benchmark::ClobberMemory();
    }
}

BENCHMARK(with_range_check);

BENCHMARK_MAIN();
