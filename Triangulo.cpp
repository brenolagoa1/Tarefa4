#include "triangulo.h"
#include "matvec.h"

// Implementação do construtor padrão
Triangulo::Triangulo() : v0(0, 0, 0), v1(0, 0, 0), v2(0, 0, 0) {}

// Implementação do construtor com parâmetros
Triangulo::Triangulo(const vec3& v0, const vec3& v1, const vec3& v2)
    : v0(v0), v1(v1), v2(v2) {
    // Se necessário, faça algo mais no construtor
}

// Implementação da função getVertices
std::tuple<vec3, vec3, vec3> Triangulo::getVertices() const {
    return std::make_tuple(v0, v1, v2);
}
