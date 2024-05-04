/**
* @file proje2
* @description Bu program karmaşık sayılar uzayında tanımlı olan vektör
               ve matris üzerinde bir takım lineer cebir işlemleri gerçekleştiren sınıf ve metotlar içermektedir.
* @assignment İkinci ödev
* @date 01/01/2024
* @author Mohamed Marwan Abdel Wahed
*/




#include <iostream>
#include <vector>

class Imaginary {
private:
    double im;

public:
    Imaginary(double imaginary) : im(imaginary) {}

    double getImaginary() const {
        return im;
    }

    // Operatör overloading 
    Imaginary& operator+=(const Imaginary& other) {
        im += other.im;
        return *this;
    }

    Imaginary& operator-=(const Imaginary& other) {
        im -= other.im;
        return *this;
    }
};





class Complex : public Imaginary {
private:
    double re;

public:
    Complex(double real, double imaginary) : re(real), Imaginary(imaginary) {}

    double getReal() const {
        return re;
    }

    // Aşırı yüklenmiş operatörler
    Complex operator+(const Complex& other) const {
        return Complex(re + other.re, getImaginary() + other.getImaginary());
    }

    Complex operator-(const Complex& other) const {
        return Complex(re - other.re, getImaginary() - other.getImaginary());
    }

    Complex operator*(const Complex& other) const {
        double realPart = re * other.re - getImaginary() * other.getImaginary();
        double imaginaryPart = re * other.getImaginary() + getImaginary() * other.re;
        return Complex(realPart, imaginaryPart);
    }

    Complex operator/(const Complex& other) const {
        double denominator = other.re * other.re + other.getImaginary() * other.getImaginary();
        double realPart = (re * other.re + getImaginary() * other.getImaginary()) / denominator;
        double imaginaryPart = (getImaginary() * other.re - re * other.getImaginary()) / denominator;
        return Complex(realPart, imaginaryPart);
    }

    Complex& operator=(const Complex& other) {
        if (this != &other) {
            re = other.re;
            Imaginary::operator=(other);
        }
        return *this;
    }

    Complex& operator+=(const Complex& other) {
        re += other.re;
        Imaginary::operator+=(other);
        return *this;
    }

    Complex& operator-=(const Complex& other) {
        re -= other.re;
        Imaginary::operator-=(other);
        return *this;
    }

    Complex& operator*=(const Complex& other) {
        Complex result = *this * other;
        *this = result;
        return *this;
    }

    Complex& operator/=(const Complex& other) {
        Complex result = *this / other;
        *this = result;
        return *this;
    }

    bool operator==(const Complex& other) const {
        return (re == other.re) && (getImaginary() == other.getImaginary());
    }

    void print() const {
        std::cout << re << " + " << getImaginary() << "i" << std::endl;
    }
};

class Vector {
private:
    size_t size;
    std::vector<Complex> elements;

public:
    Vector(size_t s, const std::vector<Complex>& elems) : size(s), elements(elems) {}

    // Gerekli operatörlerin overloading

    void print() const {
        std::cout << "Vector:" << std::endl;
        for (const auto& element : elements) {
            element.print();
        }
    }
};

class Matrix {
protected:
    size_t row;
    size_t col;
    std::vector<std::vector<Complex>> elements;

public:
    Matrix(size_t r, size_t c, const std::vector<std::vector<Complex>>& elems)
        : row(r), col(c), elements(elems) {}

    // Gerekli operatörlerin overloading

            Matrix transpose() const {
        std::vector<std::vector<Complex>> transposedElements(col, std::vector<Complex>(row));

        for (size_t i = 0; i < row; ++i) {
            for (size_t j = 0; j < col; ++j) {
                transposedElements[j][i] = elements[i][j];
            }
        }

        return Matrix(col, row, transposedElements);
    }



    

    Complex determinant() const {
        // Determinant hesaplama işlemi
        // Bu örnekte basitleştirilmiş bir yöntem kullandım
        return elements[0][0] * elements[1][1] - elements[0][1] * elements[1][0];
    }

    void print() const {
        std::cout << "Matrix:" << std::endl;
        for (const auto& row : elements) {
            for (const auto& element : row) {
                element.print();
            }
            std::cout << std::endl;
        }
    }
};

class SquareMatrix : public Matrix {
public:
    SquareMatrix(size_t s, const std::vector<std::vector<Complex>>& elems)
        : Matrix(s, s, elems) {}
};

class IdentityMatrix : public SquareMatrix {
public:
    IdentityMatrix(size_t s) : SquareMatrix(s, std::vector<std::vector<Complex>>(s, std::vector<Complex>(s, Complex(0, 0)))) {
        for (size_t i = 0; i < s; ++i) {
            elements[i][i] = Complex(1, 0);
        }
    }
};

class TriangleMatrix : public SquareMatrix {
public:
    TriangleMatrix(size_t s, const std::vector<std::vector<Complex>>& elems)
        : SquareMatrix(s, elems) {}
};

class LinearAlgebraObject {
public:
    virtual void print() const = 0;
    virtual ~LinearAlgebraObject() {}
};

int main() {
    // Testing complex numbers
    Complex c1(2, 3);
    Complex c2(1, -2);

    std::cout << "Complex Numbers:" << std::endl;
    c1.print();
    c2.print();

    Complex addition = c1 + c2;
    Complex subtraction = c1 - c2;
    Complex multiplication = c1 * c2;
    Complex division = c1 / c2;

    std::cout << "Addition:" << std::endl;
    addition.print();
    std::cout << "Subtraction:" << std::endl;
    subtraction.print();
    std::cout << "Multiplication:" << std::endl;
    multiplication.print();
    std::cout << "Division:" << std::endl;
    division.print();

    // Test Vectors
    Vector v1(3, {Complex(1, 2), Complex(3, 4), Complex(5, 6)});
    Vector v2(3, {Complex(7, 8), Complex(9, 10), Complex(11, 12)});

    std::cout << "\nVectors:" << std::endl;
    v1.print();
    v2.print();

    // Test Matrices
    Matrix m1(2, 3, {{Complex(1, 2), Complex(3, 4), Complex(5, 6)},
                    {Complex(7, 8), Complex(9, 10), Complex(11, 12)}});
    
    Matrix m2(3, 2, {{Complex(2, 1), Complex(4, 3)},
                    {Complex(6, 5), Complex(8, 7)},
                    {Complex(10, 9), Complex(12, 11)}});
    
    std::cout << "\nMatrices:" << std::endl;
    m1.print();
    m2.print();

    // Test Matrix Transpose
    Matrix m2Transposed = m2.transpose();
    std::cout << "\nTransposed Matrix:" << std::endl;
    m2Transposed.print();

    // Test Matrix Determinant
    Complex determinant = m1.determinant();
    std::cout << "\nDeterminant of Matrix m1: ";
    determinant.print();

    // Test SquareMatrix, IdentityMatrix, TriangleMatrix
    SquareMatrix squareMatrix(3, {{Complex(1, 0), Complex(2, 0), Complex(3, 0)},
                                  {Complex(4, 0), Complex(5, 0), Complex(6, 0)},
                                  {Complex(7, 0), Complex(8, 0), Complex(9, 0)}});

    IdentityMatrix identityMatrix(3);
    TriangleMatrix triangleMatrix(3, {{Complex(1, 0), Complex(2, 0), Complex(3, 0)},
                                      {Complex(0, 0), Complex(5, 0), Complex(6, 0)},
                                      {Complex(0, 0), Complex(0, 0), Complex(9, 0)}});

    std::cout << "\nSquare Matrix:" << std::endl;
    squareMatrix.print();
    std::cout << "\nIdentity Matrix:" << std::endl;
    identityMatrix.print();
    std::cout << "\nTriangle Matrix:" << std::endl;
    triangleMatrix.print();

    return 0;
}
