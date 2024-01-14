#include "matvec.h"
#include <iostream>

#include <cmath>

// Implementa��o da classe vec2

/// Construtor padr�o da classe vec2.
vec2::vec2() : x(0.0), y(0.0) {}

/// Construtor da classe vec2 com par�metros.
vec2::vec2(double x, double y) : x(x), y(y) {}

/// Sobrecarga do operador de adi��o para vetores 2D.
vec2 vec2::operator+(const vec2& other) const {
    return vec2(x + other.x, y + other.y);
}

/// Sobrecarga do operador de subtra��o para vetores 2D.
vec2 vec2::operator-(const vec2& other) const {
    return vec2(x - other.x, y - other.y);
}

/// Sobrecarga do operador de multiplica��o escalar para vetores 2D.
double vec2::operator*(const vec2& other) const {
    return x * other.x + y * other.y;
}

/// Sobrecarga do operador de multiplica��o por escalar para vetores 2D.
vec2 vec2::operator*(double scalar) const {
    return vec2(x * scalar, y * scalar);
}

/// Sobrecarga do operador de divis�o por escalar para vetores 2D.
vec2 vec2::operator/(double scalar) const {
    if (scalar == 0) {
        return vec2(0, 0);
    }
    return vec2(x / scalar, y / scalar);
}

/// Calcula o comprimento (magnitude) do vetor 2D.
double vec2::length() const {
    return std::sqrt(x * x + y * y);
}

// Implementa��o da classe vec3

/// Construtor padr�o da classe vec3.
vec3::vec3() : x(0.0), y(0.0), z(0.0) {}

/// Construtor da classe vec3 com par�metros.
vec3::vec3(double x, double y, double z) : x(x), y(y), z(z) {}

/// Sobrecarga do operador de adi��o para vetores 3D.
vec3 vec3::operator+(const vec3& other) const {
    return vec3(x + other.x, y + other.y, z + other.z);
}

/// Sobrecarga do operador de subtra��o para vetores 3D.
vec3 vec3::operator-(const vec3& other) const {
    return vec3(x - other.x, y - other.y, z - other.z);
}

/// Sobrecarga do operador de multiplica��o escalar para vetores 3D.
double vec3::operator*(const vec3& other) const {
    return x * other.x + y * other.y + z * other.z;
}

/// Sobrecarga do operador de multiplica��o por escalar para vetores 3D.
vec3 vec3::operator*(double scalar) const {
    return vec3(x * scalar, y * scalar, z * scalar);
}

/// Sobrecarga do operador de divis�o por escalar para vetores 3D.
vec3 vec3::operator/(double scalar) const {
    if (scalar == 0) {
        return vec3(0, 0, 0);
    }
    return vec3(x / scalar, y / scalar, z / scalar);
}

/// Calcula o comprimento (magnitude) do vetor 3D.
double vec3::length() const {
    return std::sqrt(x * x + y * y + z * z);
}

// Outras fun��es relacionadas a vec3

/// Sobrecarga do operador de multiplica��o escalar por vetor 3D.
vec3 operator*(double scalar, const vec3& v) {
    return v * scalar;
}

/// \brief Sobrecarga do operador de nega��o para vetores 3D.
/// \param v Vetor a ser negado.
/// \return Vetor resultante da nega��o.
vec3 operator-(const vec3& v)
{
    return vec3(-v.x, -v.y, -v.z);
}

/// Sobrecarga do operador de divis�o escalar por vetor 3D.
vec3 operator/(double scalar, const vec3& v) {
    if (scalar == 0) {
        return vec3(0, 0, 0);
    }
    return vec3(v.x / scalar, v.y / scalar, v.z / scalar);
}

/// Calcula o vetor normalizado (unit�rio) de um vetor 3D.
vec3 unit_vector(const vec3& v) {
    return v / v.length();
}

/// Calcula o produto vetorial de dois vetores 3D.
vec3 cross(const vec3& v1, const vec3& v2) {
    return vec3(
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
    );
}

/// Calcula o produto escalar de dois vetores 3D.
double dot(const vec3& v1, const vec3& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}


// Implementa��o da classe ivec3
ivec3::ivec3() : x(0), y(0), z(0) {}

ivec3::ivec3(int x, int y, int z) : x(x), y(y), z(z) {}

// Implementa��o da fun��o para multiplica��o de um inteiro por um vetor de inteiros 3D
ivec3 operator*(int scalar, const ivec3& v) {
    return ivec3(scalar * v.x, scalar * v.y, scalar * v.z);
}

// Implementa��o da fun��o para divis�o de um vetor de inteiros 3D por um inteiro
ivec3 operator/(const ivec3& v, int scalar) {
    return ivec3(v.x / scalar, v.y / scalar, v.z / scalar);
}

// Implementa��o da fun��o para imprimir um vetor de inteiros 3D no cerr
std::ostream& operator<<(std::ostream& os, const ivec3& v) {
    os << "ivec3(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}


// Implementa��o da classe vec4

/// Construtor padr�o da classe vec4.
vec4::vec4() : x(0.0), y(0.0), z(0.0), w(0.0) {}

/// Construtor da classe vec4 com par�metros.
vec4::vec4(double x, double y, double z, double w) : x(x), y(y), z(z), w(w) {}

/// Sobrecarga do operador de adi��o para vetores 4D.
vec4 vec4::operator+(const vec4& other) const {
    return vec4(x + other.x, y + other.y, z + other.z, w + other.w);
}

/// Sobrecarga do operador de subtra��o para vetores 4D.
vec4 vec4::operator-(const vec4& other) const {
    return vec4(x - other.x, y - other.y, z - other.z, w - other.w);
}

/// Sobrecarga do operador de multiplica��o escalar para vetores 4D.
double vec4::operator*(const vec4& other) const {
    return x * other.x + y * other.y + z * other.z + w * other.w;
}

/// Sobrecarga do operador de multiplica��o por escalar para vetores 4D.
vec4 vec4::operator*(double scalar) const {
    return vec4(x * scalar, y * scalar, z * scalar, w * scalar);
}

/// Sobrecarga do operador de divis�o por escalar para vetores 4D.
vec4 vec4::operator/(double scalar) const {
    if (scalar == 0) {
        return vec4(0, 0, 0, 0);
    }
    return vec4(x / scalar, y / scalar, z / scalar, w / scalar);
}

/// Calcula o comprimento (magnitude) do vetor 4D.
double vec4::length() const {
    return std::sqrt(x * x + y * y + z * z + w * w);
}

// Implementa��o das classes mat2, mat
/// Construtor padr�o de mat2.
mat2::mat2() {
    data[0][0] = 0.0;
    data[0][1] = 0.0;
    data[1][0] = 0.0;
    data[1][1] = 0.0;
}

/// Construtor de mat2 com par�metros.
mat2::mat2(double a, double b, double c, double d) {
    data[0][0] = a;
    data[0][1] = b;
    data[1][0] = c;
    data[1][1] = d;
}

/// Sobrecarga do operador de adi��o para mat2.
mat2 mat2::operator+(const mat2& other) const {
    return mat2(data[0][0] + other.data[0][0], data[0][1] + other.data[0][1], data[1][0] + other.data[1][0], data[1][1] + other.data[1][1]);
}

/// Construtor padr�o de mat3.
mat3::mat3() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            data[i][j] = 0.0;
        }
    }
}

/// Construtor de mat3 com par�metros.
mat3::mat3(double a, double b, double c, double d, double e, double f, double g, double h, double i) {
    data[0][0] = a;
    data[0][1] = b;
    data[0][2] = c;
    data[1][0] = d;
    data[1][1] = e;
    data[1][2] = f;
    data[2][0] = g;
    data[2][1] = h;
    data[2][2] = i;
}

/// Sobrecarga do operador de adi��o para mat3.
mat3 mat3::operator+(const mat3& other) const {
    mat3 result;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}

/// Construtor padr�o de mat4.
mat4::mat4() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            data[i][j] = 0.0;
        }
    }
}

/// Construtor de mat4 com par�metros.
mat4::mat4(double a, double b, double c, double d, double e, double f, double g, double h, double i, double j, double k, double l, double m, double n, double o, double p) {
    data[0][0] = a;
    data[0][1] = b;
    data[0][2] = c;
    data[0][3] = d;
    data[1][0] = e;
    data[1][1] = f;
    data[1][2] = g;
    data[1][3] = h;
    data[2][0] = i;
    data[2][1] = j;
    data[2][2] = k;
    data[2][3] = l;
    data[3][0] = m;
    data[3][1] = n;
    data[3][2] = o;
    data[3][3] = p;
}

/// Sobrecarga do operador de adi��o para mat4.
mat4 mat4::operator+(const mat4& other) const {
    mat4 result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}

// Implementa��o das opera��es de multiplica��o de matriz por vetor (fora das classes)

/// Multiplica uma matriz 2x2 por um vetor 2D.
vec2 operator*(const mat2& m, const vec2& v) {
    return vec2(m.data[0][0] * v.x + m.data[0][1] * v.y, m.data[1][0] * v.x + m.data[1][1] * v.y);
}

/// Multiplica uma matriz 4x4 por um vetor 4D.
vec4 operator*(const mat4& m, const vec4& v) {
    return vec4(
        m.data[0][0] * v.x + m.data[0][1] * v.y + m.data[0][2] * v.z + m.data[0][3] * v.w,
        m.data[1][0] * v.x + m.data[1][1] * v.y + m.data[1][2] * v.z + m.data[1][3] * v.w,
        m.data[2][0] * v.x + m.data[2][1] * v.y + m.data[2][2] * v.z + m.data[2][3] * v.w,
        m.data[3][0] * v.x + m.data[3][1] * v.y + m.data[3][2] * v.z + m.data[3][3] * v.w
    );
}
