#include <chrono>
#include <iostream>
#include <random>
#include <vector>
#include <functional>
#include <cstring>
#include <typeinfo>

/*
 * ***************** Discussion on the Results *****************
 *
 *  Results Table
 *  +-------------+-----------+----------+---------------------+
 *  | Type        | Algorithm | Order    | Time (milliseconds) |
 *  +-------------+-----------+----------+---------------------+
 *  | std::string | sort()    | Increase | 469                 |
 *  +-------------+-----------+----------+---------------------+
 *  | std::string | sort()    | Decrease | 466                 |
 *  +-------------+-----------+----------+---------------------+
 *  | std::string | qsort()   | Increase | 546                 |
 *  +-------------+-----------+----------+---------------------+
 *  | std::string | qsort()   | Decrease | 541                 |
 *  +-------------+-----------+----------+---------------------+
 *  | c-string    | sort()    | Increase | 345                 |
 *  +-------------+-----------+----------+---------------------+
 *  | c-string    | sort()    | Decrease | 352                 |
 *  +-------------+-----------+----------+---------------------+
 *  | c-string    | qsort()   | Increase | 300                 |
 *  +-------------+-----------+----------+---------------------+
 *  | c-string    | qsort()   | Decrease | 314                 |
 *  +-------------+-----------+----------+---------------------+
 *
 *  The program is compiled using -O2 flag to improve the efficiency
 *  Each sorting algorithm is run three times and the average
 *  runtime captured by high_resolution_clock is reported in the
 *  table above.
 *
 *  For std::string() we can see that std::sort() is much faster
 *  than using the qsort() method. The difference is almost 20%.
 *  This observation is consistent with our expectation that sort()
 *  is better for sorting containers in c++ than the qsort()
 *  method.
 *
 *  For c style strings, we see that sort() is actually slower
 *  than qsort(). Although this result is surprising, it also
 *  makes sense. C strings have less overhead, and qsort() is
 *  meant to be used in C.
 *
 *  Between the std::string and the c-string, we can see that
 *  given one million randomly generated words, sorting the
 *  C strings is considerably faster than std::string().
 *  This also makes sense since std::string() has slightly
 *  more overhead than just the character arrays in c strings.
 *
 */

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
    for (int i = 0; i < one_million; i++)
        string_vec.push_back(get_random_cpp_string(random_length()));

    return string_vec;
}

std::vector<const char*> get_one_million_c_strings() {

    using namespace std;
    vector<const char*> string_vec;
    auto random_length = get_random_int_generator(STRING_LEN_MIN, STRING_LEN_MAX);
    string_vec.reserve(one_million);

    for (int i = 0; i < one_million; i++)
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

void std_string_increasing_sort(const std::vector<std::string>& cpp_strings) {
    /*
     * Make a copy and sort
     */
    std::cout << "Sort std::string using sort() increasing" << "\n";
    for (auto i = 0; i < 3; i++) {
        auto string_copy = cpp_strings;
        auto start = std::chrono::high_resolution_clock::now();
        std::sort(string_copy.begin(), string_copy.end(), string_icompare_cpp);
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds" << "\n";
    }

    std::cout << "==== end test ====" << "\n";
}

void std_string_decreasing_sort(const std::vector<std::string>& cpp_strings) {
    /*
     * Make a copy and sort
     */
    std::cout << "Sort std::string using sort() increasing" << "\n";
    for (auto i = 0; i < 3; i++) {
        auto string_copy = cpp_strings;
        auto start = std::chrono::high_resolution_clock::now();
        std::sort(string_copy.begin(), string_copy.end(), string_dcompare_cpp);
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds" << "\n";
    }
    std::cout << "==== end test ====" << "\n";
}

void c_string_increasing_sort(const std::vector<const char *>& c_strings) {
    /*
     * Make a copy and sort
     */
    std::cout << "Sort c-string using sort() increasing" << "\n";

    for (auto i = 0; i < 3; i++) {
        auto string_copy = c_strings;
        auto start = std::chrono::high_resolution_clock::now();
        std::sort(string_copy.begin(), string_copy.end(), c_string_icompare_cpp);
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds" << "\n";
    }

    std::cout << "==== end test ====" << "\n";
}

void c_string_decreasing_sort(const std::vector<const char *>& c_strings) {
    /*
     * Make a copy and sort
     */
    std::cout << "Sort c-string using sort() decreasing" << "\n";
    for (auto i = 0; i < 3; i++) {
        auto string_copy = c_strings;
        auto start = std::chrono::high_resolution_clock::now();
        std::sort(string_copy.begin(), string_copy.end(), c_string_dcompare_cpp);
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds" << "\n";
    }
    std::cout << "==== end test ====" << "\n";
}

void c_string_increasing_qsort(std::vector<const char *> c_strings) {
    /*
     * Make a copy and sort
     */
    std::cout << "Sort c-string using qsort() increasing" << "\n";

    for (auto i = 0; i < 3; i++) {

        char *str_pointers[c_strings.size()];
        for (auto j = 0; j < c_strings.size(); j++)
            str_pointers[j] = (char *)c_strings[j];

        auto start = std::chrono::high_resolution_clock::now();

        qsort(str_pointers,
              c_strings.size(),
              sizeof(char *),
              string_pointer_icompare_c);

        auto end = std::chrono::high_resolution_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds" << "\n";
    }

    std::cout << "==== end test ====" << "\n";
}

void c_string_decreasing_qsort(std::vector<const char *> c_strings) {
    /*
     * Make a copy and sort
     */
    std::cout << "Sort c-string using qsort() decreasing" << "\n";

    for (auto i = 0; i < 3; i++) {

        char *str_pointers[c_strings.size()];
        for (auto j = 0; j < c_strings.size(); j++)
            str_pointers[j] = (char *)c_strings[j];

        auto start = std::chrono::high_resolution_clock::now();

        qsort(str_pointers,
              c_strings.size(),
              sizeof(char *),
              string_pointer_dcompare_c);

        auto end = std::chrono::high_resolution_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds" << "\n";
    }

    std::cout << "==== end test ====" << "\n";
}

void std_string_increasing_qsort(std::vector<std::string> c_strings) {
    std::cout << "Sort c-string using qsort() decreasing" << "\n";

    for (auto i = 0; i < 3; i++) {

        std::vector<std::string const*> str_pointers;
        str_pointers.reserve(c_strings.size());
        for(const auto& item : c_strings)
            str_pointers.push_back(&item);

        auto start = std::chrono::high_resolution_clock::now();

        qsort(&str_pointers[0],
              str_pointers.size(),
              sizeof(str_pointers[0]),
              string_pointer_icompare_cpp);

        auto end = std::chrono::high_resolution_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milliseconds" << "\n";
    }

    std::cout << "==== end test ====" << "\n";
}

void std_string_decreasing_qsort(std::vector<std::string> c_strings) {
    std::cout << "Sort c-string using qsort() decreasing" << "\n";

    for (auto i = 0; i < 3; i++) {

        std::vector<std::string const*> str_pointers_2;
        str_pointers_2.reserve(c_strings.size());
        for(const auto& item : c_strings)
            str_pointers_2.push_back(&item);

        auto start = std::chrono::high_resolution_clock::now();

        qsort(&str_pointers_2[0],
              str_pointers_2.size(),
              sizeof(str_pointers_2[0]),
              string_pointer_dcompare_cpp);

        auto end = std::chrono::high_resolution_clock::now();
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
    std_string_increasing_qsort(cpp_strings);

    // Sort the std::string using qsort() decreasing
    std_string_decreasing_qsort(cpp_strings);

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
