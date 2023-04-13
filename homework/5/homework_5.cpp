/* Поддержите ввод произвольного количества потоков в функцию parallel_accumulate, рассматриваемую на семинаре, 
 * а также перепишите её с использованием std::async + std::future 
 * (загляните в код с предыдущего семинара и не забудьте передать флаг исполнения std::launch::async). 
 * Произведите измерения быстродействия: постройте график скорости работы в зависимости от количества переданных потоков. 
 * (Сильно превышать аппаратное количество не требуется). 
*/

#include <iostream>
#include <vector>
#include <future>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <string>
#include <sstream>
#include <fstream>
#include <random>

template <typename T>
class Timer {
	using steady_clock = std::chrono::steady_clock;
public:
	Timer(T& os) : start{steady_clock::now()}, os{os} {}
	
	~Timer() {
		os << std::chrono::duration_cast< std::chrono::nanoseconds  >(steady_clock::now() - start).count() << std::endl;
	}
	
private:
	steady_clock::time_point start{};
	T& os;
};

constexpr auto BORDER_SIZE = 1000ll;

template<typename Iter, typename T>
T parallel_accumulate(Iter begin, Iter end, T init, auto num_threads) {
	auto size = std::distance(begin, end);
	if (size <= BORDER_SIZE) {
		return std::accumulate(begin, end, init);
	}

	auto block_size = size / num_threads;
	std::vector< std::future<T> > futures{};
	
	for (auto i = 0u; i + 1 < num_threads; ++i) {
		futures.emplace_back(
			std::async(std::launch::async, std::accumulate<Iter, T>, 
			std::next ( begin,    i    * block_size ),
			std::next ( begin, (i + 1) * block_size ),
			init)
		);
	}
	
	auto last_result = std::accumulate(
		std::next(begin, (num_threads - 1) * block_size),
		end,
		init
	);
	
	T result{};
	std::for_each(futures.begin(), futures.end(), [&result](std::future<T>& f) { result += f.get(); } );
	result += last_result;
	return result;
}

int main() {
	std::vector<long long> nums;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<long long> d(-10'000, 10'000);
	std::generate_n(std::back_inserter(nums), 10'000'000,
			[&gen, &d](){return d(gen);});
	
	for (auto i = 0; i < 100; ++i) {
		std::ostringstream ss{};
		const std::string opt_level = "O3";
		ss << "homework_5_data_" << i+1 << "_" << opt_level << "_NANO.txt";
		std::ofstream ofs{ss.str()};

		constexpr auto K = 3;
		for (auto num_threads = 1ull; num_threads <= std::thread::hardware_concurrency() * K; ++num_threads) {
			// apparently writing to std::cout A LOT slower than writing to a file via std::ofstream
			Timer t(ofs);
			parallel_accumulate(std::begin(nums), std::end(nums), 0ull, num_threads);
			ofs << nums.size() << '\t' <<  num_threads << '\t';
		}
	}
}
