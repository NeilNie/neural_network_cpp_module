module;

// importing <vector> seems to break module export, so we'll just include it
#include <vector>

import <string>;
import <iostream>;
import <iomanip>;

export module LibNeuralNets;

export namespace nn {
    template <class T>
    class Mat;
    template <class T>
    std::ostream& operator<<(std::ostream& os, const Mat<T>& mat);
    template <class T>
    bool operator==(const Mat<T>& mat1, const Mat<T>& mat2);
 
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
        Mat<T>& operator*=(const Mat<T>& other);
        friend Mat<T> operator+(Mat<T> l, const Mat<T>& r)
        {
            return l += r;
        }
        friend Mat<T> operator*(Mat<T> l, const Mat<T>& r)
        {
            return l *= r;
        }
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
        Mat t();

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
    Mat<T>& Mat<T>::operator+=(const Mat<T>& other)
    {
        auto end = std::min(size(), other.size());
        for (auto i = 0; i < end; ++i)
            data_[i] += other.data_[i];
        return *this;
    }

    template <class T>
    Mat<T>& Mat<T>::operator*=(const Mat<T>& other)
    {
        auto end = std::min(cols_, other.rows_);
        for (auto i = 0; i < rows_; ++i)
            for (auto j = 0; j < other.cols_; ++j)
                for (auto k = 0; k < end; ++k)
                    (*this)(i, k) *= other(k, j);
        return *this;
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
    Mat<T> Mat<T>::t()
    {
        Mat<T> mat_t(cols_, rows_, 0);

        for (size_t r = 0; r < rows_; r++) {
            for (size_t c = 0; c < cols_; c++) {
                mat_t(c, r) = (*this)(r, c);
            }
        }

        return mat_t;
    }

    class Module {
    public:
        Module(std::string filepath);

        const auto& bias0() { return bias0_; }
        const auto& kernel0() { return kernel0_; }

        const auto& bias1() { return bias1_; }
        const auto& kernel1() { return kernel1_; }

    private:
        std::vector<float> bias0_;
        Mat<float> kernel0_;

        std::vector<float> bias1_;
        Mat<float> kernel1_;
    };

    class Layer {

    public:
        virtual ~Layer();

    };

    class Conv2d {

    };

    class Dense {

    };

    class ReLU {

    };

    class Sigmoid {

    };
}
