#include <chrono>
#include <iostream>
#include <random>
#include <vector>
#include <list>
#include <set>
#include <functional>
#include <unordered_set>
#include <concepts>

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

template <class ContainerType>
ContainerType insert_random_numbers_to_container(std::vector<int> numbers) {

    ContainerType container;

    // insert the first element
    container.push_back(numbers[0]);
    numbers.erase(numbers.begin());

    // insert all elements
    for (int number : numbers) {
        bool inserted = false;
        for (auto it = begin(container); it != end(container); it++) {
            if (number < *it) {
                container.insert(it, number);
                inserted = true;
                break;
            }
        }
        if (!inserted)
            container.push_back(number);
    }
    return container;
}

template <class T>
T insert_random_numbers_to_set(std::vector<int> numbers) {

    T set;
    for (int number: numbers)
        set.insert(number);
    return set;
}

template <class T>
void time_method(T (*f)(std::vector<int>), const std::vector<int>& data) {

    auto start = std::chrono::high_resolution_clock::now();
    f(data);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds" << "\n";

}

int main() {

    auto vector_10k = generate_random_numbers(10'000);
    auto vector_20k = generate_random_numbers(20'000);
    auto vector_30k = generate_random_numbers(30'000);
    auto vector_40k = generate_random_numbers(40'000);
    auto vector_50k = generate_random_numbers(50'000);
    auto vector_60k = generate_random_numbers(60'000);
    auto vector_70k = generate_random_numbers(70'000);
    auto vector_80k = generate_random_numbers(80'000);
    auto vector_90k = generate_random_numbers(90'000);

    std::cout << "std::list -> input size: 10k" << "\n";
    time_method(&insert_random_numbers_to_container<std::list<int>>, vector_10k);
    std::cout << "std::list -> input size: 20k" << "\n";
    time_method(&insert_random_numbers_to_container<std::list<int>>, vector_20k);
    std::cout << "std::list -> input size: 30k" << "\n";
    time_method(&insert_random_numbers_to_container<std::list<int>>, vector_30k);
    std::cout << "std::list -> input size: 40k" << "\n";
    time_method(&insert_random_numbers_to_container<std::list<int>>, vector_40k);
    std::cout << "std::list -> input size: 50k" << "\n";
    time_method(&insert_random_numbers_to_container<std::list<int>>, vector_50k);
    std::cout << "std::list -> input size: 60k" << "\n";
    time_method(&insert_random_numbers_to_container<std::list<int>>, vector_60k);
    std::cout << "std::list -> input size: 70k" << "\n";
    time_method(&insert_random_numbers_to_container<std::list<int>>, vector_70k);
    std::cout << "std::list -> input size: 80k" << "\n";
    time_method(&insert_random_numbers_to_container<std::list<int>>, vector_80k);
    std::cout << "std::list -> input size: 90k" << "\n";
    time_method(&insert_random_numbers_to_container<std::list<int>>, vector_90k);

    std::cout << "\n" << "\n";

    std::cout << "std::vector -> input size: 10k" << "\n";
    time_method(&insert_random_numbers_to_container<std::vector<int>>, vector_10k);
    std::cout << "std::vector -> input size: 20k" << "\n";
    time_method(&insert_random_numbers_to_container<std::vector<int>>, vector_20k);
    std::cout << "std::vector -> input size: 30k" << "\n";
    time_method(&insert_random_numbers_to_container<std::vector<int>>, vector_30k);
    std::cout << "std::vector -> input size: 40k" << "\n";
    time_method(&insert_random_numbers_to_container<std::vector<int>>, vector_40k);
    std::cout << "std::vector -> input size: 50k" << "\n";
    time_method(&insert_random_numbers_to_container<std::vector<int>>, vector_50k);
    std::cout << "std::vector -> input size: 60k" << "\n";
    time_method(&insert_random_numbers_to_container<std::vector<int>>, vector_60k);
    std::cout << "std::vector -> input size: 70k" << "\n";
    time_method(&insert_random_numbers_to_container<std::vector<int>>, vector_70k);
    std::cout << "std::vector -> input size: 80k" << "\n";
    time_method(&insert_random_numbers_to_container<std::vector<int>>, vector_80k);
    std::cout << "std::vector -> input size: 90k" << "\n";
    time_method(&insert_random_numbers_to_container<std::vector<int>>, vector_90k);

    std::cout << "\n" << "\n";

    std::cout << "std::set-> input size: 10k" << "\n";
    time_method(&insert_random_numbers_to_set<std::set<int>>, vector_10k);
    std::cout << "std::set -> input size: 20k" << "\n";
    time_method(&insert_random_numbers_to_set<std::set<int>>, vector_20k);
    std::cout << "std::set -> input size: 30k" << "\n";
    time_method(&insert_random_numbers_to_set<std::set<int>>, vector_30k);
    std::cout << "std::set -> input size: 40k" << "\n";
    time_method(&insert_random_numbers_to_set<std::set<int>>, vector_40k);
    std::cout << "std::set -> input size: 50k" << "\n";
    time_method(&insert_random_numbers_to_set<std::set<int>>, vector_50k);
    std::cout << "std::set -> input size: 60k" << "\n";
    time_method(&insert_random_numbers_to_set<std::set<int>>, vector_60k);
    std::cout << "std::set -> input size: 70k" << "\n";
    time_method(&insert_random_numbers_to_set<std::set<int>>, vector_70k);
    std::cout << "std::set -> input size: 80k" << "\n";
    time_method(&insert_random_numbers_to_set<std::set<int>>, vector_80k);
    std::cout << "std::set -> input size: 90k" << "\n";
    time_method(&insert_random_numbers_to_set<std::set<int>>, vector_90k);

    return 0;
}