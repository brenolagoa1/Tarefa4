#include "triangulo.h"
#include "matvec.h"

// Implementa��o do construtor padr�o
Triangulo::Triangulo() : v0(0, 0, 0), v1(0, 0, 0), v2(0, 0, 0) {}

// Implementa��o do construtor com par�metros
Triangulo::Triangulo(const vec3& v0, const vec3& v1, const vec3& v2)
    : v0(v0), v1(v1), v2(v2) {
    // Se necess�rio, fa�a algo mais no construtor
}

// Implementa��o da fun��o getVertices
std::tuple<vec3, vec3, vec3> Triangulo::getVertices() const {
    return std::make_tuple(v0, v1, v2);
}
