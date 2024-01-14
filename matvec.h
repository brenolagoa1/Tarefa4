#ifndef MATVEC_H
#define MATVEC_H

/// \file
/// \brief Contém as definições de classes para vetores e matrizes 2D, 3D e 4D.

/// \class vec2
/// \brief Classe que representa um vetor 2D.
class vec2 {
public:
    double x, y;

    vec2();
    vec2(double x, double y);

    vec2 operator+(const vec2& other) const;
    vec2 operator-(const vec2& other) const;
    double operator*(const vec2& other) const;
    vec2 operator*(double scalar) const;
    vec2 operator/(double scalar) const;
    double length() const;
};

/// \class vec3
/// \brief Classe que representa um vetor 3D.
class vec3 {
public:
    double x, y, z;

    vec3();
    vec3(double x, double y, double z);

    vec3 operator+(const vec3& other) const;
    vec3 operator-(const vec3& other) const;
    double operator*(const vec3& other) const;
    vec3 operator*(double scalar) const;
    vec3 operator/(double scalar) const;
    double length() const;
};

/// \class ivec3
/// \brief Classe que representa um vetor de inteiros 3D.
class ivec3 {
public:
    int x, y, z;

    ivec3();
    ivec3(int x, int y, int z);
};


/// \brief Sobrecarga do operador de subtração para vetores 3D.
/// \param v Vetor a ser subtraído.
/// \return Vetor resultante da subtração.
vec3 operator-(const vec3& v);

/// \brief Implementa a multiplicação de vetor 3D por escalar.
vec3 operator*(double scalar, const vec3& v);

/// \brief Implementa a divisão de escalar por vetor 3D.
vec3 operator/(double scalar, const vec3& v);

/// \brief Implementa a normalização de um vetor 3D.
vec3 unit_vector(const vec3& v);

/// \brief Implementa o produto vetorial de dois vetores 3D.
vec3 cross(const vec3& v1, const vec3& v2);

/// \brief Implementa o produto escalar de dois vetores 3D.
double dot(const vec3& v1, const vec3& v2);

/// \class vec4
/// \brief Classe que representa um vetor 4D.
class vec4 {
public:
    double x, y, z, w;

    vec4();
    vec4(double x, double y, double z, double w);

    vec4 operator+(const vec4& other) const;
    vec4 operator-(const vec4& other) const;
    double operator*(const vec4& other) const;
    vec4 operator*(double scalar) const;
    vec4 operator/(double scalar) const;
    double length() const;
};

/// \class mat2
/// \brief Classe que representa uma matriz 2x2.
class mat2 {
public:
    double data[2][2];

    mat2();
    mat2(double a, double b, double c, double d);

    mat2 operator+(const mat2& other) const;
};

/// \class mat3
/// \brief Classe que representa uma matriz 3x3.
class mat3 {
public:
    double data[3][3];

    mat3();
    mat3(double a, double b, double c, double d, double e, double f, double g, double h, double i);

    mat3 operator+(const mat3& other) const;
};

/// \class mat4
/// \brief Classe que representa uma matriz 4x4.
class mat4 {
public:
    double data[4][4];

    mat4();
    mat4(double a, double b, double c, double d, double e, double f, double g, double h, double i, double j, double k, double l, double m, double n, double o, double p);

    mat4 operator+(const mat4& other) const;
};

/// \brief Implementa a multiplicação de matriz 2D por vetor 2D.
vec2 operator*(const mat2& m, const vec2& v);

/// \brief Implementa a multiplicação de matriz 4D por vetor 4D.
vec4 operator*(const mat4& m, const vec4& v);

#endif // MATVEC_H

