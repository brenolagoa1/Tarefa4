#pragma once

#include "matvec.h"
#include <tuple>

/// \class Triangulo
/// \brief Classe que representa um triângulo no espaço tridimensional.
class Triangulo {
public:
    /// \brief Construtor padrão da classe Triangulo.
    Triangulo();

    /// \brief Construtor da classe Triangulo com parâmetros.
    /// \param v0 Vértice 0 do triângulo.
    /// \param v1 Vértice 1 do triângulo.
    /// \param v2 Vértice 2 do triângulo.
    Triangulo(const vec3& v0, const vec3& v1, const vec3& v2);

    /// \brief Obtém os vértices do triângulo.
    /// \return Tupla contendo os três vértices do triângulo.
    std::tuple<vec3, vec3, vec3> getVertices() const;

private:
    vec3 v0; ///< Vértice 0 do triângulo.
    vec3 v1; ///< Vértice 1 do triângulo.
    vec3 v2; ///< Vértice 2 do triângulo.
};
