#include "Vector.h"
#include <iostream>

using namespace std;

class Matrix {
public:
    Matrix() : Arr(NULL), n(0), size(0), codeError(0) {}
    Matrix(int n, int size) : n(n), size(size), codeError(0) {
        Arr = new Vector[n];
        for (int i = 0; i < n; i++) {
            Arr[i] = Vector(size, 0);
        }
    }
    Matrix(int n, int size, float value) : n(n), size(size), codeError(0) {
        Arr = new Vector[n];
        for (int i = 0; i < n; i++) {
            Arr[i] = Vector(size, value);
        }
    }
    Matrix(const Matrix& other)
        : n(other.n), size(other.size), codeError(other.codeError) {
        Arr = new Vector[n];
        for (int i = 0; i < n; i++) {
            Arr[i] = other.Arr[i];
        }
    }
    ~Matrix() { delete[] Arr; }

    int getn() const { return n; }
    int getsize() const { return size; }
    int getcodeError() const { return codeError; }

    Matrix& operator++() {
        for (int i = 0; i < n; i++) {
            ++Arr[i];
        }
        return *this;
    }
    Matrix operator++(int) {
        Matrix temp = *this;
        ++(*this);
        return temp;
    }
    Matrix& operator--() {
        for (int i = 0; i < n; i++) {
            --Arr[i];
        }
        return *this;
    }
    Matrix operator--(int) {
        Matrix temp = *this;
        --(*this);
        return temp;
    }

    bool operator!() const { return (n != 0 && size != 0); }
    Matrix operator-() const {
        Matrix temp(n, size);
        for (int i = 0; i < n; i++) {
            temp.Arr[i] = -Arr[i];
        }
        return temp;
    }
    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            delete[] Arr;
            n = other.n;
            size = other.size;
            codeError = other.codeError;
            Arr = new Vector[n];
            for (int i = 0; i < n; i++) {
                Arr[i] = other.Arr[i];
            }
        }
        return *this;
    }
    Matrix operator+(const Matrix& other) const {
        Matrix temp(n, size);
        for (int i = 0; i < n; i++) {
            temp.Arr[i] = Arr[i] + other.Arr[i];
        }
        return temp;
    }
    Matrix operator+(int s) {
        Matrix temp(n, size);
        for (int i = 0; i < n; i++) {
            temp.Arr[i] = Arr[i] + s;
        }
        return temp;
    }

    Matrix operator-(const Matrix& other) {
        Matrix temp(n, size);
        for (int i = 0; i < n; i++) {
            temp.Arr[i] = Arr[i] - other.Arr[i];
        }
        return temp;
    }
    Matrix operator-(int s) {
        Matrix temp(n, size);
        for (int i = 0; i < n; i++) {
            temp.Arr[i] = Arr[i] - s;
        }
        return temp;
    }

    Matrix operator*(const Matrix& other) {
        if (this->size != other.n) {
            codeError = 1;
            return *this;
        }
        Matrix temp(this->n, other.size);
        for (int i = 0; i < this->n; i++) {
            for (int j = 0; j < other.size; j++) {
                temp.Arr[i][j] = 0;
                for (int k = 0; k < this->size; k++) {
                    temp.Arr[i][j] += this->Arr[i][k] * other.Arr[k][j];
                }
            }
        }
        return temp;
    }
    Matrix operator*(int s) {
        Matrix temp(n, size);
        for (int i = 0; i < n; i++) {
            temp.Arr[i] = Arr[i] * s;
        }
        return temp;
    }

    Matrix operator/(int s) {
        Matrix temp(n, size);
        for (int i = 0; i < n; i++) {
            temp.Arr[i] = Arr[i] / s;
        }
        return temp;
    }

    Matrix operator%(int s) {
        Matrix temp(*this);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < size; j++) {
                temp.Arr[i][j] = static_cast<int>(temp.Arr[i][j]) % s;
            }
        }
        return temp;
    }

    Matrix operator+=(const Matrix& other) {
        if (this->n != other.n || this->size != other.size) {
            codeError = 1;
            return *this;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < size; j++) {
                this->Arr[i][j] += other.Arr[i][j];
            }
        }
        return *this;
    }
    Matrix operator+=(int s) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < size; j++) {
                this->Arr[i][j] += s;
            }
        }
        return *this;
    }

    Matrix operator-=(const Matrix& other) {
        if (this->n != other.n || this->size != other.size) {
            codeError = 1;
            return *this;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < size; j++) {
                this->Arr[i][j] -= other.Arr[i][j];
            }
        }
        return *this;
    }
    Matrix operator-=(int s) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < size; j++) {
                this->Arr[i][j] -= s;
            }
        }
        return *this;
    }

    Matrix& operator*=(const Matrix& other) {
        if (this->size != other.n) {
            codeError = 1;
            return *this;
        }
        Matrix temp(this->n, other.size);
        for (int i = 0; i < this->n; i++) {
            for (int j = 0; j < other.size; j++) {
                temp.Arr[i][j] = 0;
                for (int k = 0; k < this->size; k++) {
                    temp.Arr[i][j] += this->Arr[i][k] * other.Arr[j][k];
                }
            }
        }
        *this = temp;
        return *this;
    }
    Matrix& operator*=(int s) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < size; j++) {
                this->Arr[i][j] *= s;
            }
        }
        return *this;
    }

    Matrix& operator/=(int s) {
        if (s == 0) {
            codeError = 1;
            return *this;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < size; j++) {
                this->Arr[i][j] /= s;
            }
        }
        return *this;
    }
    Matrix& operator%=(int s) {
        if (s == 0) {
            codeError = 1;
            return *this;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < size; j++) {
                this->Arr[i][j] = static_cast<int>(this->Arr[i][j]) % s;
            }
        }
        return *this;
    }

    Matrix operator|(const Matrix& other) {
        if (this->n != other.n || this->size != other.size) {
            codeError = 1;
            return *this;
        }
        Matrix temp(this->n, this->size);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < size; j++) {
                temp.Arr[i][j] = static_cast<int>(this->Arr[i][j]) |
                    static_cast<int>(other.Arr[i][j]);
            }
        }
        return temp;
    }
    Matrix operator^(const Matrix& other) {
        if (this->n != other.n || this->size != other.size) {
            codeError = 1;
            return *this;
        }
        Matrix temp(this->n, this->size);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < size; j++) {
                temp.Arr[i][j] = static_cast<int>(this->Arr[i][j]) ^
                    static_cast<int>(other.Arr[i][j]);
            }
        }
        return temp;
    }
    Matrix operator&(const Matrix& other) {
        if (this->n != other.n || this->size != other.size) {
            codeError = 1;
            return *this;
        }
        Matrix temp(this->n, this->size);
        for (int i = 0; i < this->n; i++) {
            for (int j = 0; j < this->size; j++) {
                temp.Arr[i][j] = static_cast<int>(this->Arr[i][j]) & static_cast<int>(other.Arr[i][j]);
            }
        }
        return temp;
    }
    Matrix operator&(int s) {
        Matrix temp(this->n, this->size);
        for (int i = 0; i < this->n; i++) {
            for (int j = 0; j < this->size; j++) {
                temp.Arr[i][j] = static_cast<int>(this->Arr[i][j]) & s;
            }
        }
        return temp;
    }

    Matrix& operator>>=(const Matrix& other) {
        if (this->n != other.n || this->size != other.size) {
            codeError = 1;
            return *this;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < size; j++) {
                this->Arr[i][j] /= other.Arr[i][j];
            }
        }
        return *this;
    }
    Matrix& operator>>=(int s) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < size; j++) {
                this->Arr[i][j] /= s;
            }
        }
        return *this;
    }
    Matrix& operator<<=(const Matrix& other) {
        if (this->n != other.n || this->size != other.size) {
            codeError = 1;
            return *this;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < size; j++) {
                this->Arr[i][j] *= other.Arr[i][j];
            }
        }
        return *this;
    }
    Matrix& operator<<=(int s) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < size; j++) {
                this->Arr[i][j] *= s;
            }
        }
        return *this;
    }
    Matrix& operator|=(const Matrix& other) {
        if (this->n != other.n || this->size != other.size) {
            codeError = 1;
            return *this;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < size; j++) {
                this->Arr[i][j] = static_cast<int>(this->Arr[i][j]) |
                    static_cast<int>(other.Arr[i][j]);
            }
        }
        return *this;
    }
    Matrix& operator|=(int s) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < size; j++) {
                this->Arr[i][j] = static_cast<int>(this->Arr[i][j]) | s;
            }
        }
        return *this;
    }
    Matrix& operator^=(const Matrix& other) {
        if (this->n != other.n || this->size != other.size) {
            codeError = 1;
            return *this;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < size; j++) {
                this->Arr[i][j] = static_cast<int>(this->Arr[i][j]) ^
                    static_cast<int>(other.Arr[i][j]);
            }
        }
        return *this;
    }
    Matrix& operator^=(int s) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < size; j++) {
                this->Arr[i][j] = static_cast<int>(this->Arr[i][j]) ^ s;
            }
        }
        return *this;
    }
    Matrix& operator&=(const Matrix& other) {
        if (this->n != other.n || this->size != other.size) {
            codeError = 1;
            return *this;
        }
        for (int i = 0; i < this->n; i++) {
            for (int j = 0; j < this->size; j++) {
                this->Arr[i][j] *= other.Arr[i][j];
            }
        }
        return *this;
    }

    Matrix& operator&=(int s) {
        for (int i = 0; i < this->n; i++) {
            for (int j = 0; j < this->size; j++) {
                this->Arr[i][j] *= s;
            }
        }
        return *this;
    }

    bool operator==(const Matrix& other) {
        if (this->n != other.n || this->size != other.size) {
            return false;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < size; j++) {
                if (this->Arr[i][j] != other.Arr[i][j])
                    return false;
            }
        }
        return true;
    }
    bool operator!=(const Matrix& other) { return !(*this == other); }
    bool operator>(const Matrix& other) {
        if (this->n != other.n || this->size != other.size) {
            codeError = 1;
            return false;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < size; j++) {
                if (this->Arr[i][j] <= other.Arr[i][j])
                    return false;
            }
        }
        return true;
    }
    bool operator>=(const Matrix& other) {
        if (this->n != other.n || this->size != other.size) {
            codeError = 1;
            return false;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < size; j++) {
                if (this->Arr[i][j] < other.Arr[i][j])
                    return false;
            }
        }
        return true;
    }
    bool operator<(const Matrix& other) { return !(*this >= other); }
    bool operator<=(const Matrix& other) { return !(*this > other); }

    float& operator[](int index) {
        if (index < 0 || index >= size) {
            codeError = 1;
            return Arr[size - 1][0];
        }
        return Arr[index][0];
    }

    float& operator()(int index) { return (*this)[index]; }

protected:
    Vector* Arr;
    int n, size;
    int codeError;
};

int main() {

}
