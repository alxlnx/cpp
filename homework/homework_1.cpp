#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <random>
#include <iterator>

template <typename T>
std::ostream& operator<<(std::ostream& ost, const std::vector<T>& v) {
  for (auto x : v) ost << x << ' ';
  ost << '\n';
  return ost;
}

int main() {
  // TASK I
  std::vector<int> v(10);
  std::iota(v.begin(), v.end(), 1);

  // TASK II
  constexpr int vals_num{3};
  for (int i{}, tmp{}; i < vals_num; ++i) {
    std::cout << "Please, enter a value (" << i+1 << " / " << vals_num << ")\n";
    std::cin >> tmp;
    v.push_back(tmp);
  }

  // TASK III
  std::random_device rd{};
  std::shuffle(v.begin(), v.end(), rd);
  std::cout << "Here is your shuffled number sequence: \n";
  std::cout << v;

  // TASK IV
  auto odd_num = std::count_if(v.begin(), v.end(), 
                 [](int x) { return x % 2; }    );
  std::cout << "The number of odd elements in the vector is " << odd_num << '\n';

  // TASK V
  auto max_elem = std::max_element(v.begin(), v.end());
  auto min_elem = std::min_element(v.begin(), v.end());
  std::cout << "The smallest numer is " << *min_elem << '\n'
            << "The largest number is " << *max_elem << '\n';

  // TASK VI
  auto prime_idx = std::find_if(v.begin(), v.end(),
                   [](auto x) 
                   {
                     for (auto i{2}; i*i <= x; ++i) {
                       if (x % i == 0) return false;
                     }
                   return true;
                   }); // disgusting.
  if (prime_idx == v.end()) std::cout << "No primes in this sequence.\n";
  else std::cout << "There is a prime number in this sequence: " << *prime_idx << '\n';

  // TASK VII
  std::transform(v.begin(), v.end(), v.begin(),
                [](auto x) { return x*x; });
  std::cout << "The sequence squared is " << v;

  // TASK VIII
  auto sum = std::accumulate(v.begin(), v.end(), 0);
  std::cout << "The sum of sequence's elements is " << sum << '\n';

  // TASK IX
  std::replace_if(v.begin(), v.end(), 
                 [v](auto x){
                   if (v.at(x % v.size()) < 3) return true;
                   else return false;
                 }, 1);
  std::cout << "Sequence with replaced elements is " << v;

  // TASK X
  auto rm_it = std::remove_if(v.begin(), v.end(), [](auto x){ return x == 0; });
  v.erase(rm_it, v.end());
  std::cout << "With 0s erased, the sequence is " << v;
  
  // TASK XI
  std::reverse(v.begin(), v.end());
  std::cout << "Reversed: " << v;

  // TASK XII
  std::partial_sort(v.begin(), v.begin() + 3, v.end(), [](auto a, auto b){ return a > b; });
  std::cout << "Partially sorted sequence: " << v;

  // TASK XIII
  std::sort(v.begin(), v.end());
  std::cout << "Sorted: " << v;

  // TASK XIV
  auto range = std::equal_range(v.begin(), v.end(), 3);
  std::cout << "The range is " << *range.first << " " << *range.second << '\n';

  // TASK XV
  std::cout << "Output using ostream_iterator: ";
  std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << '\n';
}
