#include <iostream>

using namespace std;

class Vector {
public:
    Vector() : size(1), codeError(0) {
        data = new float[size];
        data[0] = 0.0;
    }
    Vector(int s) : size(s), codeError(0) {
        data = new float[size];
        for (int i = 0; i < size; i++) {
            data[i] = 0.0;
        }
    }
    Vector(int s, float value) : size(s), codeError(0) {
        data = new float[size];
        for (int i = 0; i < size; i++) {
            data[i] = value;
        }
    }
    Vector(const Vector& other) : size(other.size), codeError(other.codeError) {
        data = new float[size];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }
    ~Vector() {
        delete[] data;
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new float[size];
            for (int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
            codeError = other.codeError;
        }
        return *this;
    }

    Vector& operator++() {
        for (int i = 0; i < size; i++) {
            data[i] += 1.0;
        }
        return *this;
    }
    Vector operator++(int) {
        Vector temp(*this);
        ++(*this);
        return temp;
    }
    Vector& operator--() {
        for (int i = 0; i < size; i++) {
            data[i] -= 1.0;
        }
        return *this;
    }
    Vector operator--(int) {
        Vector temp(*this);
        --(*this);
        return temp;
    }

    bool operator!() const {
        return size == 0;
    }

    Vector operator-() const {
        Vector res(size);
        for (int i = 0; i < size; i++) {
            res.data[i] = -data[i];
        }
        return res;
    }

    Vector& operator+=(const Vector& other) {
        if (size != other.size) {
            codeError = 1;
            return *this;
        }
        for (int i = 0; i < size; i++) {
            data[i] += other.data[i];
        }
        return *this;
    }

    Vector& operator-=(const Vector& other) {
        if (size != other.size) {
            codeError = 1;
            return *this;
        }
        for (int i = 0; i < size; i++) {
            data[i] -= other.data[i];
        }
        return *this;
    }

    Vector& operator*=(float value) {
        for (int i = 0; i < size; i++) {
            data[i] *= value;
        }
        return *this;
    }

    Vector& operator/=(float value) {
        if (value == 0) {
            codeError = 1;
            return *this;
        }
        for (int i = 0; i < size; i++) {
            data[i] /= value;
        }
        return *this;
    }

    Vector& operator%=(int value) {
        if (value == 0) {
            codeError = 1;
            return *this;
        }
        for (int i = 0; i < size; i++) {
            data[i] = static_cast<int>(data[i]) % value;
        }
        return *this;
    }

    Vector operator+(const Vector& other) const {
        Vector res(*this);
        res += other;
        return res;
    }
    Vector operator-(const Vector& other) const {
        Vector res(*this);
        res -= other;
        return res;
    }
    Vector operator*(float value) const {
        Vector res(*this);
        res *= value;
        return res;
    }
    Vector operator/(float value) const {
        Vector res(*this);
        res /= value;
        return res;
    }
    Vector operator%(int value) const {
        Vector res(*this);
        res %= value;
        return res;
    }

    friend istream& operator>>(istream& in, Vector& vec) {
        for (int i = 0; i < vec.size; i++) {
            in >> vec.data[i];
        }
        return in;
    }
    friend ostream& operator<<(ostream& out, const Vector& vec) {
        for (int i = 0; i < vec.size; i++) {
            out << vec.data[i] << " ";
        }
        return out;
    }

    bool operator==(const Vector& other) const {
        if (size != other.size) return false;
        for (int i = 0; i < size; i++) {
            if (data[i] != other.data[i]) return false;
        }
        return true;
    }
    bool operator!=(const Vector& other) const {
        return !(*this == other);
    }
    bool operator>(const Vector& other) const {
        for (int i = 0; i < size; i++) {
            if (data[i] <= other.data[i]) return false;
        }
        return true;
    }
    bool operator>=(const Vector& other) const {
        return (*this > other) || (*this == other);
    }
    bool operator<(const Vector& other) const {
        return !(*this >= other);
    }
    bool operator<=(const Vector& other) const {
        return !(*this > other);
    }

    float& operator[](int index) {
        if (index < 0 || index >= size) {
            codeError = 1;
            return data[size - 1];
        }
        return data[index];
    }
    void operator()() const {
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }

    int getsize() const { return size; }

protected:
    float* data;
    int size;
    int codeError;
};



int main()
{
    setlocale(LC_ALL, "ukr");

    Vector vec1;
    Vector vec2(5);
    Vector vec3(5, 3);

    cout << "Вектори " << endl;
    cout << "Вектор 1: " << vec1 << endl;
    cout << "Вектор 2: " << vec2 << endl;
    cout << "Вектор 3: " << vec3 << endl;

    cout << "Введіть вектор 1 "; cin >> vec1;

    vec1++; ++vec2;
    cout << "Вектори після ++ " << endl;
    cout << "Вектор 1: " << vec1 << endl;
    cout << "Вектор 2: " << vec2 << endl;

    vec1--; --vec2;
    cout << "Вектори після -- " << endl;
    cout << "Вектор 1: " << vec1 << endl;
    cout << "Вектор 2: " << vec2 << endl;

    cout << "Вектори після ! " << endl;
    cout << "Вектор 1: " << !vec1 << endl;

    Vector vecNeg = -vec3;
    cout << "Унарний вектор " << endl;
    cout << "Унарний вектор 3: " << vecNeg << endl;

    vec2 = vec1;
    cout << "Вектор після = " << endl;
    cout << "Вектор 2: " << vec2 << endl;

    vec2 += vec3;
    vec2 -= vec3;
    vec2 *= 2.0;
    vec2 /= 2.0;
    vec2 %= 3;

    cout << "Вектор 2 після усіх операції з = " << endl;
    cout << "Вектор 2: " << vec2 << endl;

    Vector vecSum = vec2 + vec3;
    Vector vecDiff = vec2 - vec3;
    Vector vecProd = vec2 * 2.0;
    Vector vecDrob = vec2 / 2.0;
    Vector vecMod = vec2 % 2;

    cout << "Сума: " << vecSum << endl;
    cout << "Мінус: " << vecDiff << endl;
    cout << "Множ: " << vecProd << endl;
    cout << "Діл: " << vecDrob << endl;
    cout << "Остача: " << vecMod << endl;

    cout << "(vec2 == vec3): " << (vec2 == vec3) << endl;
    cout << "(vec2 != vec3): " << (vec2 != vec3) << endl;
    cout << "(vec2 > vec3): " << (vec2 > vec3) << endl;
    cout << "(vec2 >= vec3): " << (vec2 >= vec3) << endl;
    cout << "(vec2 < vec3): " << (vec2 < vec3) << endl;
    cout << "(vec2 <= vec3): " << (vec2 <= vec3) << endl;
}



