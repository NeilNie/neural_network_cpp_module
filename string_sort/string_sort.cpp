#include <chrono>
#include <iostream>
#include <random>
#include <vector>
#include <functional>
#include <cstring>
#include <typeinfo>


static const char alphanum[] = "0123456789abcdefghijklmnopqrstuvwxyz";
static const int one_million = 1'000'000;
static const int STRING_LEN_MIN = 4;
static const int STRING_LEN_MAX = 32;


auto get_random_int_generator(int lower, int upper) {
    std::random_device r;
    std::default_random_engine generator(r());
    std::uniform_int_distribution<int> distribution(lower, upper);
    return std::bind(distribution, generator);
}

const char* malloc_random_c_string(const int len) {
    char *string = static_cast<char *>(malloc(STRING_LEN_MAX * sizeof(char)));
    auto dice = get_random_int_generator(0, sizeof(alphanum) - 1);
    for (int i = 0; i < len; ++i) {
        *string = alphanum[dice() % (sizeof(alphanum) - 1)];
        string++;
    }
    return string - len;
}

void free_c_strings(std::vector<const char *> strings) {
    for (auto string: strings) {
        free((void *) string);
    }
}

std::string get_random_cpp_string(const int len) {

    // Seed with a real random value, if available
    auto dice = get_random_int_generator(0, sizeof(alphanum) - 1);
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[dice() % (sizeof(alphanum) - 1)];
    }
    return tmp_s;
}

std::vector<std::string> get_one_million_cpp_strings() {

    using namespace std;
    vector<string> string_vec;
    auto random_length = get_random_int_generator(STRING_LEN_MIN, STRING_LEN_MAX);

    string_vec.reserve(one_million);
    for (int i = 0; i < 10; i++)
        string_vec.push_back(get_random_cpp_string(random_length()));

    return string_vec;
}

std::vector<const char*> get_one_million_c_strings() {

    using namespace std;
    vector<const char*> string_vec;
    auto random_length = get_random_int_generator(STRING_LEN_MIN, STRING_LEN_MAX);
    string_vec.reserve(one_million);

    for (int i = 0; i < 10; i++)
        string_vec.push_back(malloc_random_c_string(random_length()));

    return string_vec;
}

bool string_icompare_cpp(const std::string& s1, const std::string& s2) {
    return s1.compare(s2) < 0;
}

bool string_dcompare_cpp(const std::string& s1, const std::string& s2) {
    return s1.compare(s2) > 0;
}

int string_pointer_icompare_cpp( void const* e1, void const* e2 ) {
    std::string const* const p1 = *reinterpret_cast<std::string* const*>(e1);
    std::string const* const p2 = *reinterpret_cast<std::string* const*>(e2);
    return p1->compare(*p2);
}

int string_pointer_dcompare_cpp( void const* e1, void const* e2 ) {
    std::string const* const p1 = *reinterpret_cast<std::string* const*>(e1);
    std::string const* const p2 = *reinterpret_cast<std::string* const*>(e2);
    return -1 * p1->compare(*p2);
}

int string_pointer_icompare_c( const void *a, const void *b) {
    const char *ia = *(const char **) a;
    const char *ib = *(const char **) b;
    return strcmp(ia, ib);
}

int string_pointer_dcompare_c( const void *a, const void *b) {
    const char *ia = *(const char **) a;
    const char *ib = *(const char **) b;
    return -1 * strcmp(ia, ib);}

int c_string_icompare_cpp(const char* s1, const char* s2) {
    return strcmp(s1, s2) < 0;
}

int c_string_dcompare_cpp(const char* s1, const char* s2) {
    return strcmp(s1, s2) > 0;
}

// =====================================================================================================================

void std_string_increasing_sort(std::vector<std::string> cpp_strings) {
    /*
     * Make a copy and sort
     */
    std::cout << "Sort std::string using sort() increasing" << "\n";
    for (auto i = 0; i < 3; i++) {
        auto start = std::chrono::steady_clock::now();
        std::sort(cpp_strings.begin(), cpp_strings.end(), string_icompare_cpp);
        auto end = std::chrono::steady_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " microseconds" << "\n";
    }

    std::cout << "==== end test ====" << "\n";
}

void std_string_decreasing_sort(std::vector<std::string> cpp_strings) {
    /*
     * Make a copy and sort
     */
    std::cout << "Sort std::string using sort() increasing" << "\n";
    for (auto i = 0; i < 3; i++) {
        auto start = std::chrono::steady_clock::now();
        std::sort(cpp_strings.begin(), cpp_strings.end(), string_dcompare_cpp);
        auto end = std::chrono::steady_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " microseconds" << "\n";
    }
    std::cout << "==== end test ====" << "\n";
}

void c_string_increasing_sort(std::vector<const char *> c_strings) {
    /*
     * Make a copy and sort
     */
    std::cout << "Sort c-string using sort() increasing" << "\n";

    for (auto i = 0; i < 3; i++) {
        auto start = std::chrono::steady_clock::now();
        std::sort(c_strings.begin(), c_strings.end(), c_string_icompare_cpp);
        auto end = std::chrono::steady_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " microseconds" << "\n";
    }

    std::cout << "==== end test ====" << "\n";
}

void c_string_decreasing_sort(std::vector<const char *> c_strings) {
    /*
     * Make a copy and sort
     */
    std::cout << "Sort c-string using sort() decreasing" << "\n";
    for (auto i = 0; i < 3; i++) {
        auto start = std::chrono::steady_clock::now();
        std::sort(c_strings.begin(), c_strings.end(), c_string_dcompare_cpp);
        auto end = std::chrono::steady_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " microseconds" << "\n";
    }
    std::cout << "==== end test ====" << "\n";
}

void c_string_increasing_qsort(std::vector<const char *> c_strings) {
    /*
     * Make a copy and sort
     */
    std::cout << "Sort c-string using qsort() increasing" << "\n";

    char *str_pointers[c_strings.size()];
    for (int i = 0; i < c_strings.size(); i++)
        str_pointers[i] = (char *)c_strings[i];

    for (auto i = 0; i < 3; i++) {
        auto start = std::chrono::steady_clock::now();

        qsort(str_pointers,
              c_strings.size(),
              sizeof(char *),
              string_pointer_icompare_c);

        auto end = std::chrono::steady_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds" << "\n";
    }

    std::cout << "==== end test ====" << "\n";
}

void c_string_decreasing_qsort(std::vector<const char *> c_strings) {
    /*
     * Make a copy and sort
     */
    std::cout << "Sort c-string using sort() decreasing" << "\n";

    char *str_pointers[c_strings.size()];
    for (int i = 0; i < c_strings.size(); i++)
        str_pointers[i] = (char *)c_strings[i];

    for (auto i = 0; i < 3; i++) {
        auto start = std::chrono::steady_clock::now();

        qsort(str_pointers,
              c_strings.size(),
              sizeof(char *),
              string_pointer_dcompare_c);

        auto end = std::chrono::steady_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds" << "\n";
    }

    std::cout << "==== end test ====" << "\n";
}

// =====================================================================================================================

int main(int argc, char *argv[]) {

    auto cpp_strings = get_one_million_cpp_strings();
    auto c_strings = get_one_million_c_strings();

    // Sort the std::string increasing
    std_string_increasing_sort(cpp_strings);

    // Sort the std::string decreasing
    std_string_decreasing_sort(cpp_strings);

    // Sort the std::string using qsort() increasing
    std::vector<std::string const*> str_pointers;
    str_pointers.reserve(cpp_strings.size());
    for(const auto& item : cpp_strings)
        str_pointers.push_back(&item);
    qsort(&str_pointers[0],
          str_pointers.size(),
          sizeof(str_pointers[0]),
          string_pointer_icompare_cpp);

    // Sort the std::string using qsort() decreasing
    std::vector<std::string const*> str_pointers_2;
    str_pointers_2.reserve(cpp_strings.size());
    for(const auto& item : cpp_strings)
        str_pointers_2.push_back(&item);
    qsort(&str_pointers_2[0],
          str_pointers_2.size(),
          sizeof(str_pointers_2[0]),
          string_pointer_dcompare_cpp);

    // Sort the std::string using sort() increasing
    c_string_increasing_sort(c_strings);

    // Sort the std::string using sort() decreasing
    c_string_decreasing_sort(c_strings);

    // Sort the std::string using sort() increasing
    c_string_increasing_qsort(c_strings);

    // Sort the std::string using sort() decreasing
    c_string_decreasing_qsort(c_strings);

    free_c_strings(c_strings);

    return 0;
}

