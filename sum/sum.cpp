//
// Created by Yongyang Nie on 3/9/22.
//

#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <random>
#include <unordered_set>
#include <functional>

static const int MAX_INT_SIZE = 1'000'000;

auto get_random_int_generator(int lower, int upper) {
    std::random_device r;
    std::default_random_engine generator(r());
    std::uniform_int_distribution<int> distribution(lower, upper);
    return std::bind(distribution, generator);
}

std::vector<int> generate_random_numbers(size_t size) {

    auto dice = get_random_int_generator(0, MAX_INT_SIZE);
    std::vector<int> list;

    std::unordered_set<int> m;
    while (m.size() < size)
        m.insert(dice());

    for (auto it = begin(m); it != end(m); it++)
        list.push_back(*it);

    return list;
}

template<typename Container, typename Operation, typename Accumulator>
Accumulator sum(Container c, Operation op, Accumulator acc){
    for (auto element: c)
        acc = op(std::move(acc), element);
    return acc;
}

template <class ContainerType>
concept Container = requires(ContainerType a) {
//    requires std::regular<ContainerType>;
//    requires std::swappable<ContainerType>;
//    requires std::destructible<typename ContainerType::value_type>;
//    requires std::same_as<typename ContainerType::reference, typename ContainerType::value_type &>;
//    requires std::same_as<typename ContainerType::const_reference, const typename ContainerType::value_type &>;
//    requires std::forward_iterator<typename ContainerType::iterator>;
//    requires std::forward_iterator<typename ContainerType::const_iterator>;
//    requires std::signed_integral<typename ContainerType::difference_type>;
//    requires std::same_as<typename ContainerType::difference_type, typename std::iterator_traits<typename ContainerType::iterator>::difference_type>;
//    requires std::same_as<typename ContainerType::difference_type, typename std::iterator_traits<typename ContainerType::const_iterator>::difference_type>;
    { a.begin() } -> std::same_as<typename ContainerType::iterator>;
    { a.end() } -> std::same_as<typename ContainerType::iterator>;
    { a.cbegin() } -> std::same_as<typename ContainerType::const_iterator>;
    { a.cend() } -> std::same_as<typename ContainerType::const_iterator>;
    { a.size() } -> std::same_as<typename ContainerType::size_type>;
    { a.max_size() } -> std::same_as<typename ContainerType::size_type>;
    { a.empty() } -> std::same_as<bool>;
};

template<Container ContainerType, typename Operation, typename Accumulator>
Accumulator sum_with_concepts(ContainerType c, Operation op, Accumulator acc){
    for (auto element: c)
        acc = op(std::move(acc), element);
    return acc;
}


std::string dash_fold(const std::string& a, const std::string& b) {
    return a + '-' + b;
}

int main() {

    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // vector and ints
    int product = sum(v, std::multiplies<int>(), 1);
    std::cout << product << "\n";

    int total = sum(v, std::plus<int>(), 1);
    std::cout << total << "\n";

    // strings
    std::vector<std::string> strings{"1", "2", "3", "4", "5"};
    std::string s = sum(strings, dash_fold, strings[0]);
    std::cout << s << "\n";

    // performance comparison

}
