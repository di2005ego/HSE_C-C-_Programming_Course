#define NULL nullptr

#include <iostream>
#include <random>
#include <sstream>
#include <vector>
using namespace std;

class Matrix {
private:
    int rows;
    int columns;
    double** data;

public:
    Matrix() : rows(0), columns(0), data(NULL) {}

    Matrix(const Matrix& other) : rows(other.rows), columns(other.columns) {
        data = new double*[rows];
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
        data = new double*[rows];
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
        data = new double*[rows];
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
};

int main() {
    Matrix A = Matrix::FromString("[1, 2, 3], [4, 5, 6], [7, 8, 9]");
    Matrix B = Matrix::Random(3, 3);
    Matrix AT = A.Transpose();
    Matrix BT = B.Transpose();
    double sumA = A.Sum();
    double sumB = B.Sum();
    //Matrix result = ((A * B) - (B / AT) * sumA) + (BT * A / sumB);
    //Вместо деления на матрицу, которого не существует (существует только умножение на обратную матрицу),
    //используем операцию деления на скаляр
    Matrix result = ((A * B) - (B / 2) * sumA) + (BT * A / sumB);
    cout << result;
    return 0;
}