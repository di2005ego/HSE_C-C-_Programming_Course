#define TASK_1

//Реализация через векторы (итерации по строкам и по столбцам)
#ifdef TASK_1
#include <iostream>
#include <vector>
using namespace std;

class Matrix {
public:
    using ValueType = int;
    using Row = vector<ValueType>;
    using Data = vector<Row>;

    struct Rows;
    struct Columns;

private:
    Data data;

public:
    Matrix(initializer_list<Row> rows) : data(rows) {}

    Rows iter_rows();
    Columns iter_columns();

    size_t rows() const {
        return data.size(); 
    }
    size_t columns() const {
        if (data.empty()) {
            return 0;
        }
        else {
            return data[0].size();
        }
    }

    ValueType& at(size_t row, size_t col) {
        return data[row][col];
    }

    const ValueType& at(size_t row, size_t col) const {
        return data[row][col];
    }

    template <typename Functor>
    void intracolumn(size_t column, Functor&& functor) {
        for (size_t i = 0; i < rows(); i++) {
            functor(data[i][column]);
        }
    }
};

struct Matrix::Rows {
    Matrix& matrix;

    Rows(Matrix& m) : matrix(m) {}

    struct iterator {
        Matrix& matrix;
        size_t currRow;

        iterator(Matrix& m, size_t row) : matrix(m), currRow(row) {}

        using iterator_category = random_access_iterator_tag;
        using value_type = Row;
        using difference_type = ptrdiff_t;
        using pointer = Row*;
        using reference = Row&;

        bool operator==(const iterator& other) const {
            return &matrix == &other.matrix && currRow == other.currRow;
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

        Row operator*() {
            return Row(matrix.data[currRow]);
        }

        iterator& operator++() {
            ++currRow;
            return *this;
        }

        iterator& operator--() {
            --currRow;
            return *this;
        }

        ValueType& operator[](ptrdiff_t idx) const {
            return matrix.data[currRow + idx][0];
        }

        iterator& operator+=(ptrdiff_t shift) {
            currRow += shift;
            return *this;
        }

        iterator& operator-=(ptrdiff_t shift) {
            currRow -= shift;
            return *this;
        }

        iterator operator+(ptrdiff_t shift) const {
            return iterator(matrix, currRow + shift);
        }

        iterator operator-(ptrdiff_t shift) const {
            return iterator(matrix, currRow - shift);
        }

        ptrdiff_t operator-(const iterator& other) const {
            return currRow - other.currRow;
        }
    };

    iterator begin() {
        return iterator(matrix, 0);
    }
    iterator end() {
        return iterator(matrix, matrix.rows());
    }
};

struct Matrix::Columns {
    Matrix& matrix;

    Columns(Matrix& m) : matrix(m) {}

    struct iterator {
        Matrix& matrix;
        size_t currCol;
        size_t currRow;

        iterator(Matrix& m, size_t col, size_t row) : matrix(m), currCol(col), currRow(row) {}

        using iterator_category = random_access_iterator_tag;
        using value_type = ValueType;
        using difference_type = ptrdiff_t;
        using pointer = ValueType*;
        using reference = ValueType&;

        bool operator==(const iterator& other) const {
            return &matrix == &other.matrix && currCol == other.currCol && currRow == other.currRow;
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

        ValueType& operator[](ptrdiff_t idx) const {
            return matrix.data[currRow][currCol + idx];
        }

        iterator& operator+=(ptrdiff_t shift) {
            currRow += shift;
            return *this;
        }

        iterator& operator-=(ptrdiff_t shift) {
            currRow -= shift;
            return *this;
        }

        iterator operator+(ptrdiff_t shift) const {
            return iterator(matrix, currCol, currRow + shift);
        }

        iterator operator-(ptrdiff_t shift) const {
            return iterator(matrix, currCol, currRow - shift);
        }

        ptrdiff_t operator-(const iterator& other) const {
            return currRow - other.currRow;
        }
    };

    iterator begin() {
        return iterator(matrix, 0, 0);
    }

    iterator end() {
        return iterator(matrix, matrix.columns(), matrix.rows());
    }
};

Matrix::Rows Matrix::iter_rows() {
    return Rows(*this);
}

Matrix::Columns Matrix::iter_columns() {
    return Columns(*this);
}

int main() {
    Matrix m{
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    for (auto&& row : m.iter_rows()) {
        for (auto&& elem : row) {
            cout << elem << " ";
        }
        cout << endl;
    }

    cout << endl << "Iteration by lines: ";

    for (auto&& row : m.iter_rows()) {
        for (auto&& elem : row) {
            cout << elem << " ";
        }
    }
    cout << endl << "Iteration by columns: ";

    for (size_t col = 0; col < m.columns(); col++) {
        m.intracolumn(col, [](
            Matrix::ValueType& elem) {
                cout << elem << " ";
            }
        );
    }

    return 0;
}
#endif

//Реализация через double** (итерация по строкам)
#ifdef TASK_2
#include <iostream>
#include <random>
#include <sstream>
using namespace std;

class Matrix {
private:
    int rows;
    int columns;
    double** data;

public:
    Matrix() : rows(0), columns(0), data(nullptr) {}

    Matrix(const Matrix& other) : rows(other.rows), columns(other.columns) {
        data = new double* [rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new double[columns];
            for (int j = 0; j < columns; j++) {
                data[i][j] = other.data[i][j];
            }
        }
    }

    Matrix(Matrix&& other) noexcept : rows(0), columns(0), data(NULL) {
        swap(rows, other.rows);
        swap(columns, other.columns);
        swap(data, other.data);
    }

    Matrix(int n, int m) : rows(n), columns(m) {
        data = new double* [rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new double[columns] {};
        }
    }

    Matrix(int n, int m, double val) : rows(n), columns(m) {
        data = new double* [rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new double[columns];
            for (int j = 0; j < columns; j++) {
                data[i][j] = val;
            }
        }
    }

    Matrix(initializer_list<initializer_list<double>> list) : rows(list.size()) {
        columns = list.begin()->size();
        data = new double* [rows];
        int i = 0;
        for (const auto& row : list) {
            data[i] = new double[columns];
            int j = 0;
            for (double val : row) {
                data[i][j] = val;
                j++;
            }
            i++;
        }
    }

    ~Matrix() {
        if (data != NULL) {
            for (int i = 0; i < rows; i++) {
                delete[] data[i];
            }
            delete[] data;
        }
    }

    static Matrix Identity(int n, int m) {
        Matrix identity(n, m);
        for (int i = 0; i < n && i < m; i++) {
            identity.data[i][i] = 1;
        }
        return identity;
    }

    static Matrix Zero(int n, int m) {
        return Matrix(n, m, 0);
    }

    static Matrix Random(int n, int m) {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<double> dis(0.0, 10.0);
        Matrix randomMatrix(n, m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                randomMatrix.data[i][j] = dis(gen);
            }
        }
        return randomMatrix;
    }

    static Matrix FromString(const string& str) {
        vector<vector<double>> values;
        stringstream ss(str);
        char ch;
        while (ss >> ch) {
            if (ch == '[') {
                vector<double> row;
                double val;
                while (ss >> val) {
                    row.push_back(val);
                    if (ss >> ch) {
                        if (ch == ']') {
                            break;
                        }
                        else if (ch != ',') {
                            ss.unget();
                        }
                    }
                    else {
                        break;
                    }
                }
                values.push_back(row);
            }
        }
        Matrix matrix(values.size(), values[0].size());
        for (int i = 0; i < matrix.rows; i++) {
            for (int j = 0; j < matrix.columns; j++) {
                matrix.data[i][j] = values[i][j];
            }
        }
        return matrix;
    }

    Matrix operator+(const Matrix& other) const {
        if (rows != other.rows || columns != other.columns) {
            throw invalid_argument("Different matrix sizes");
        }
        Matrix result(rows, columns);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    Matrix operator-(const Matrix& other) const {
        if (rows != other.rows || columns != other.columns) {
            throw invalid_argument("Different matrix sizes");
        }
        Matrix result(rows, columns);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    Matrix operator*(const Matrix& other) const {
        if (columns != other.rows) {
            throw invalid_argument("Matrix dimensions are not suitable for multiplication");
        }
        Matrix result(rows, other.columns);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.columns; j++) {
                for (int k = 0; k < columns; k++) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    Matrix operator*(double scalar) const {
        Matrix result(rows, columns);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                result.data[i][j] = data[i][j] * scalar;
            }
        }
        return result;
    }

    friend Matrix operator*(double scalar, const Matrix& matrix) {
        return matrix * scalar;
    }

    Matrix operator/(double scalar) const {
        if (scalar == 0) {
            throw domain_error("Division by zero");
        }
        Matrix result(rows, columns);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                result.data[i][j] = data[i][j] / scalar;
            }
        }
        return result;
    }

    Matrix operator-() const {
        Matrix result(rows, columns);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                result.data[i][j] = -data[i][j];
            }
        }
        return result;
    }

    bool operator==(const Matrix& other) const {
        if (rows != other.rows || columns != other.columns) {
            return false;
        }
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                if (data[i][j] != other.data[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!=(const Matrix& other) const {
        return !(*this == other);
    }

    double& operator()(int i, int j) {
        if (i < 0 || i >= rows || j < 0 || j >= columns) {
            throw out_of_range("Index out of range");
        }
        return data[i][j];
    }

    const double& operator()(int i, int j) const {
        if (i < 0 || i >= rows || j < 0 || j >= columns) {
            throw out_of_range("Index out of range");
        }
        return data[i][j];
    }

    Matrix Transpose() const {
        Matrix result(columns, rows);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                result.data[j][i] = data[i][j];
            }
        }
        return result;
    }

    double Sum() const {
        double sum = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                sum += data[i][j];
            }
        }
        return sum;
    }

    friend ostream& operator<<(ostream& out, const Matrix& matrix) {
        for (int i = 0; i < matrix.rows; i++) {
            for (int j = 0; j < matrix.columns; j++) {
                out << matrix.data[i][j] << " ";
            }
            out << endl;
        }
        return out;
    }

    // Итератор
    class RowIterator {
    private:
        double* rowPtr;
    public:
        using iterator_category = random_access_iterator_tag;
        using value_type = double;
        using difference_type = ptrdiff_t;
        using pointer = double*;
        using reference = double&;

        RowIterator(double* ptr) : rowPtr(ptr) {}

        bool operator==(const RowIterator& other) const {
            return rowPtr == other.rowPtr;
        }

        bool operator!=(const RowIterator& other) const {
            return !(*this == other);
        }

        reference operator*() const {
            return *rowPtr;
        }

        pointer operator->() {
            return rowPtr;
        }

        RowIterator& operator++() {
            ++rowPtr;
            return *this;
        }

        RowIterator operator++(int) {
            RowIterator temp = *this;
            ++(*this);
            return temp;
        }

        RowIterator& operator--() {
            --rowPtr;
            return *this;
        }

        RowIterator operator--(int) {
            RowIterator temp = *this;
            --(*this);
            return temp;
        }

        reference operator[](size_t idx) {
            return rowPtr[idx];
        }

        RowIterator& operator+=(size_t shift) {
            rowPtr += shift;
            return *this;
        }

        RowIterator& operator-=(size_t shift) {
            rowPtr -= shift;
            return *this;
        }

        RowIterator operator+(size_t shift) {
            RowIterator temp = *this;
            temp += shift;
            return temp;
        }

        RowIterator operator-(size_t shift) {
            RowIterator temp = *this;
            temp -= shift;
            return temp;
        }
    };

    RowIterator row_begin(int row) {
        return RowIterator(data[row]);
    }

    RowIterator row_end(int row) {
        return RowIterator(data[row] + columns);
    }

    int getRows() {
        return rows;
    }
};

int main() {
    Matrix m{
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8}
    };

    int mRows = m.getRows();

    for (int i = 0; i < mRows; i++) {
        for (auto it = m.row_begin(i); it != m.row_end(i); it++) {
            cout << *it << " ";
        }
        cout << endl;
    }
    cout << endl << "Iteration by lines: ";
    for (int i = 0; i < mRows; i++) {
        for (auto it = m.row_begin(i); it != m.row_end(i); it++) {
            cout << *it << " ";
        }
    }
    return 0;
}
#endif