// ray.h

#ifndef RAY_H
#define RAY_H

#include "matvec.h"

/**
 * @brief A classe Ray representa um raio no espa�o tridimensional.
 */
class Ray {
public:
    /**
     * @brief Construtor padr�o para Ray.
     */
    Ray();

    /**
     * @brief Construtor para Ray com origem e dire��o especificadas.
     * @param origin O ponto de origem do raio.
     * @param direction O vetor de dire��o do raio.
     */
    Ray(const vec3& origin, const vec3& direction);

    /**
     * @brief Fun��o de acesso para obter a origem do raio.
     * @return O ponto de origem do raio.
     */
    vec3 origin() const;

    /**
     * @brief Fun��o de acesso para obter a dire��o do raio.
     * @return O vetor de dire��o do raio.
     */
    vec3 direction() const;

    /**
     * @brief Retorna um ponto ao longo do raio em um valor de par�metro especificado.
     * @param t O valor do par�metro.
     * @return O ponto ao longo do raio no par�metro t.
     */
    vec3 at(double t) const;



private:
    vec3 orig; ///< O ponto de origem do raio.
    vec3 dir;  ///< O vetor de dire��o do raio.
};

#endif // RAY_H
