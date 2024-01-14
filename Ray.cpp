// ray.cpp
#include "ray.h"

/**
 * @brief Construtor padr�o para Ray.
 */
Ray::Ray() {}

/**
 * @brief Construtor para Ray com origem e dire��o especificadas.
 * @param origin O ponto de origem do raio.
 * @param direction O vetor de dire��o do raio.
 */
Ray::Ray(const vec3& origin, const vec3& direction) : orig(origin), dir(direction) {}

/**
 * @brief Fun��o de acesso para obter a origem do raio.
 * @return O ponto de origem do raio.
 */
vec3 Ray::origin() const {
    return orig;
}

/**
 * @brief Fun��o de acesso para obter a dire��o do raio.
 * @return O vetor de dire��o do raio.
 */
vec3 Ray::direction() const {
    return dir;
}

/**
 * @brief Retorna um ponto ao longo do raio em um valor de par�metro especificado.
 * @param t O valor do par�metro.
 * @return O ponto ao longo do raio no par�metro t.
 */
vec3 Ray::at(double t) const {
    return orig + t * dir;
}


