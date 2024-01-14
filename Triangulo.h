#pragma once

#include "matvec.h"
#include <tuple>

/// \class Triangulo
/// \brief Classe que representa um tri�ngulo no espa�o tridimensional.
class Triangulo {
public:
    /// \brief Construtor padr�o da classe Triangulo.
    Triangulo();

    /// \brief Construtor da classe Triangulo com par�metros.
    /// \param v0 V�rtice 0 do tri�ngulo.
    /// \param v1 V�rtice 1 do tri�ngulo.
    /// \param v2 V�rtice 2 do tri�ngulo.
    Triangulo(const vec3& v0, const vec3& v1, const vec3& v2);

    /// \brief Obt�m os v�rtices do tri�ngulo.
    /// \return Tupla contendo os tr�s v�rtices do tri�ngulo.
    std::tuple<vec3, vec3, vec3> getVertices() const;

private:
    vec3 v0; ///< V�rtice 0 do tri�ngulo.
    vec3 v1; ///< V�rtice 1 do tri�ngulo.
    vec3 v2; ///< V�rtice 2 do tri�ngulo.
};
