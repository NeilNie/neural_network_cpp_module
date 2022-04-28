module;

// importing <vector> seems to break module export, so we'll just include it
#include <vector>

import <iostream>;
import <iomanip>;
import <string>;

export module LibNeuralNets;

export namespace nn {

template <class T>
class Mat;
template <class T>
std::ostream& operator<<(std::ostream& os, const Mat<T>& mat);
template <class T>
bool operator==(const Mat<T>& mat1, const Mat<T>& mat2);
template <class T>
Mat<T> operator+(Mat<T> l, const Mat<T>& r);
template <class T>
Mat<T> operator*(const Mat<T>& l, const Mat<T>& r);

template <class T>
class Mat {
public:
    // constructors
    Mat()
        : data_(), rows_(0), cols_(0)
    {}
    Mat(size_t size, const T& fill)
        : data_(size*size, fill), rows_(size), cols_(size)
    {}
    Mat(size_t rows, size_t cols, const T& fill)
        : data_(rows*cols, fill), rows_(rows), cols_(cols)
    {}

    explicit Mat(const char* full_path)
    {
        load_from_txt(full_path);
    }

    void load_from_txt(const char* full_path)
    {
        /**
         * Load a matrix given a file path to a txt
         * in our proprietary format.
         */

#ifndef NDEBUG
        std::cout << "loading from file: " << full_path << "\n";
#endif
        // using C stdio instead of std::fstream because the later seems to incur
        // internal compiler error in a module
        FILE *file = std::fopen(full_path, "r");
        if (file == nullptr)
            throw std::system_error(errno, std::generic_category());
        int count = 0;

        int rows, cols;
        std::vector<float> data;
        char *line = nullptr;
        size_t n = 0;
        while (::getline(&line, &n, file) != -1) {
            float line_data = std::strtof(line, nullptr);
            if (count == 0) {
                rows = (int) line_data;
            } else if (count == 1) {
                cols = (int) line_data;
            } else {
                data.push_back(line_data);
            }
            count++;
        }
        std::free(line);
        bool ferr = std::ferror(file);
        std::fclose(file);
        if (ferr)
            throw std::system_error(errno, std::generic_category());

#ifndef NDEBUG
        std::cout << "matrix rows: " << rows << " columns: " << cols << "\n";
#endif
        resize(rows, cols);

        for (auto i = 0; i < n_rows(); i++)
            for (auto j = 0; j < n_cols(); j++)
                (*this)(i, j) = data[i * n_cols() + j]; //

#ifndef NDEBUG
        std::cout << "Finished loading" << "\n";
#endif
    }

    // operators
    T& operator()(size_t row, size_t col)
    {
        return data_[row*cols_ + col];
    }
    const T& operator()(size_t row, size_t col) const
    {
        return const_cast<Mat&>(*this)(row, col);
    }
    Mat<T>& operator+=(const Mat<T>& other);
    friend Mat operator+ <>(Mat l, const Mat& r);
    friend Mat operator* <>(const Mat& l, const Mat& r);
    friend std::ostream& operator<< <>(std::ostream& os, const Mat& mat);
    friend bool operator== <>(const Mat& mat1, const Mat& mat2);
    friend bool operator!=(const Mat& mat1, const Mat& mat2)
    {
        return !(mat1 == mat2);
    }

    // return size details from private members
    size_t size() const
    {
        return rows_*cols_;
    }
    size_t n_rows() const
    {
        return rows_;
    }
    size_t n_cols() const
    {
        return cols_;
    }

    // print unformatted to stream (stdout by default) with optional header; allows for stream formatting parameters to be set manually
    void raw_print(std::ostream& os) const;
    void raw_print(std::ostream& os, const std::string& header) const
    {
        os << header << std::endl;
        raw_print(os);
    }
    void raw_print() const
    {
        raw_print(std::cout);
    }
    void raw_print(const std::string& header) const
    {
        raw_print(std::cout, header);
    }

    // print with default formatting to stream (stdout by default) with optional header
    void print(std::ostream& os) const;
    void print(std::ostream& os, const std::string& header) const
    {
        os << header << std::endl;
        print(os);
    }
    void print() const
    {
        print(std::cout);
    }
    void print(const std::string& header) const
    {
        print(std::cout, header);
    }

    void resize(size_t rows, size_t cols);

    // fill the matrix (will resize for new dimensions)
    void fill(size_t rows, size_t cols, const T& fill);
    void fill(const T& fill)
    {
        fill(rows_, cols_, fill);
    }
    void zeros(size_t rows, size_t cols)
    {
        fill(rows, cols, 0);
    }
    void zeros()
    {
        zeros(rows_, cols_);
    }

    // transpose
    Mat t() const;

    T *data()
    {
        return data_.data();
    }
    const T *data() const
    {
        return data_.data();
    }

    // iterator just uses std::vector's
    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;

    iterator begin()
    {
        return data_.begin();
    }
    const_iterator begin() const
    {
        return data_.begin();
    }
    iterator end()
    {
        return data_.end();
    }
    const_iterator end() const
    {
        return data_.end();
    }

private:
    std::vector<T> data_;
    size_t rows_, cols_;

    static inline constexpr unsigned int PRINT_WIDTH = 13;
    static inline constexpr unsigned int PRINT_PRECISION = 5;

};

// matrix -> string format is tab-separated by column, newline separated by row
template <class T>
std::ostream& operator<<(std::ostream& os, const Mat<T>& mat)
{
    size_t i = 0;
    for (const T& item : mat) {
        os << item << '\t';
        if (++i >= mat.cols_) {
            os << std::endl;
            i = 0;
        }
    }
    return os;
}

// matrices are equal if dimensions are the same and entries are identical
template <class T>
bool operator==(const Mat<T>& mat1, const Mat<T>& mat2)
{
    if (mat1.rows_ != mat2.rows_ || mat1.cols_ != mat2.cols_) {
        return false;
    }

    typename Mat<T>::const_iterator it = mat2.begin();
    for (const T& item : mat1) {
        if (item != *it++) {
            return false;
        }
    }

    return true;
}

template <class T>
Mat<T> operator+(Mat<T> l, const Mat<T>& r)
{
    return l += r;
}

template <class T>
Mat<T>& Mat<T>::operator+=(const Mat<T>& other)
{
    auto end = std::min(size(), other.size());
    for (auto i = 0; i < end; ++i)
        data_[i] += other.data_[i];
    return *this;
}

template <class T>
Mat<T> operator*(const Mat<T>& l, const Mat<T>& r) {

    Mat<T> out(l.rows_, r.cols_, 0);
    for (auto i = 0; i < l.rows_; ++i)
        for (auto j = 0; j < r.cols_; ++j)
            for (auto k = 0; k < l.cols_; ++k)
                out(i, j) += l(i, k) * r(k, j);
    return out;
}

template <class T>
void Mat<T>::raw_print(std::ostream& os) const
{
    std::streamsize width_save = os.width();
    size_t i = 0;
    for (const T& item : *this) {
        os << std::setw(width_save) << item;
        if (++i >= cols_) {
            os << std::endl;
            i = 0;
        }
    }
}

template <class T>
void Mat<T>::print(std::ostream& os) const
{
    char fill_save = os.fill();
    std::streamsize width_save = os.width();
    std::streamsize precision_save = os.precision();
    std::ios::fmtflags flags_save = os.flags();

    os.fill(' ');
    os.width(PRINT_WIDTH);
    os.precision(PRINT_PRECISION);
    os.flags(flags_save | std::ios::fixed);

    raw_print(os);

    os.fill(fill_save);
    os.width(width_save);
    os.precision(precision_save);
    os.flags(flags_save);
}

template <class T>
void Mat<T>::resize(size_t rows, size_t cols)
{
    if (size() != rows*cols) {
        data_.resize(rows*cols);
    }
    rows_ = rows;
    cols_ = cols;
}

template <class T>
void Mat<T>::fill(size_t rows, size_t cols, const T& fill)
{
    resize(rows, cols);
    std::fill(begin(), end(), fill);
}

template <class T>
Mat<T> Mat<T>::t() const
{
    Mat<T> mat_t(cols_, rows_, 0);

    for (size_t r = 0; r < rows_; r++) {
        for (size_t c = 0; c < cols_; c++) {
            mat_t(c, r) = (*this)(r, c);
        }
    }

    return mat_t;
}

class Layer {
public:
    const std::string& name() const
    {
        return name_;
    }

    virtual Mat<float> forward(const Mat<float>& input) const = 0;

protected:
    Layer(const std::string& layer_name,
          const Mat<float>& init_weights,
          const Mat<float>& init_biases)
        : name_(layer_name), weights_(init_weights), biases_(init_biases)
    {}
    Layer(const std::string& layer_name)
        : name_(layer_name)
    {}

    std::string name_;
    Mat<float> weights_;
    Mat<float> biases_;
};

class Dense : public Layer {
public:
    Dense(const std::string& layer_name,
          const Mat<float>& init_weights,
          const Mat<float>& init_biases)
        : Layer(layer_name, init_weights, init_biases)
    {
        if (weights_.size() == 0 || biases_.size() == 0) {
            throw std::invalid_argument("Dense layer weights and/or biases empty");
        }
    }

    Mat<float> forward(const Mat<float> &input) const override;
};

class Sigmoid : public Layer {
public:
    Sigmoid(const std::string& layer_name)
        : Layer(layer_name)
    {}

    Mat<float> forward(const Mat<float> &input) const override;
};

class Module {
public:
    /// Initialize an instance of the module given the H5 and layer names
    explicit Module(const std::string& h5_path, const std::vector<std::string>& names);

    /// Initialize an instance of the model given layers
    explicit Module(const std::vector<Layer>& init_layers);

    ~Module();

    Mat<float> forward(const Mat<float>& input) const;

private:
    std::vector<Layer *> layers_;
};

} // export namespace nn
