#include <benchmark/benchmark.h>
#include <concepts>
#include <lib2k/random.hpp>
#include <vector>

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

template<typename T, bool use_at>
void access_pattern(benchmark::State& state, std::vector<T> const& data, std::vector<size_t> const& indices) {
    for (auto _ : state) {
        T sum = 0;
        for (auto const index : indices) {
            if constexpr (use_at) {
                sum += data.at(index);
            } else {
                sum += data[index];
            }
        }
        benchmark::DoNotOptimize(sum);
        benchmark::ClobberMemory();
    }
}

static void with_range_check_varying_sizes(benchmark::State& state) {
    auto const numbers = random_vector(state.range(0), 1u, 101u);
    auto const indices = random_vector(state.range(0), std::size_t{ 0 }, numbers.size());
    access_pattern<decltype(numbers)::value_type, true>(state, numbers, indices);
}

BENCHMARK(with_range_check_varying_sizes)->RangeMultiplier(2)->Range(1 << 10, 1 << 20);

static void no_range_check_varying_sizes(benchmark::State& state) {
    auto const numbers = random_vector(state.range(0), 1u, 101u);
    auto const indices = random_vector(state.range(0), std::size_t{ 0 }, numbers.size());
    access_pattern<decltype(numbers)::value_type, false>(state, numbers, indices);
}

BENCHMARK(no_range_check_varying_sizes)->RangeMultiplier(2)->Range(1 << 10, 1 << 20);

BENCHMARK_MAIN();
