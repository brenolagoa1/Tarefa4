#pragma once

#include "Triangulo.h"
#include "matvec.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

/// \class Objeto
/// \brief Classe que representa um objeto tridimensional carregado a partir de um arquivo.
class Objeto {
public:
    /// \brief Construtor da classe Objeto.
    /// \param filePath Caminho do arquivo contendo a descri��o do objeto.
    Objeto(const std::string& filePath);

    /// \brief Obt�m os v�rtices do objeto.
    /// \return Vetor contendo os v�rtices do objeto.
    const std::vector<vec3>& getVertices() const;

    /// \brief Obt�m os �ndices dos v�rtices que comp�em as faces do objeto.
    /// \return Vetor contendo os �ndices dos v�rtices das faces do objeto.
    const std::vector<int>& getFaces() const;

    /// \brief Obt�m os tri�ngulos que comp�em o objeto.
    /// \return Vetor contendo os tri�ngulos do objeto.
    const std::vector<Triangulo>& getTriangulos() const;

private:
    std::vector<vec3> vertices; ///< Vetores que representam os v�rtices do objeto.
    std::vector<int> faces; ///< �ndices dos v�rtices das faces do objeto.
    std::vector<Triangulo> triangulos; ///< Tri�ngulos que comp�em o objeto.

    /// \brief Cria um tri�ngulo a partir de tr�s v�rtices.
    /// \param v0 V�rtice 0 do tri�ngulo.
    /// \param v1 V�rtice 1 do tri�ngulo.
    /// \param v2 V�rtice 2 do tri�ngulo.
    /// \return Tri�ngulo criado a partir dos v�rtices dados.
    Triangulo criarTriangulo(const vec3& v0, const vec3& v1, const vec3& v2);

    /// \brief Redimensiona os v�rtices do objeto.
    /// \param vertices Vetor de v�rtices a ser redimensionado.
    /// \param biggerDif Diferen�a m�xima permitida para redimensionamento.
    void redimensionarVertices(std::vector<vec3>& vertices, double biggerDif);

    /// \brief Calcula o centr�ide dos v�rtices do objeto.
    /// \param vertices Vetor de v�rtices do objeto.
    /// \return Vetor representando o centr�ide.
    vec3 calculateCentroid(std::vector<vec3>& vertices);

    /// \brief Translada os v�rtices para o centro da c�mera.
    /// \param vertices Vetor de v�rtices a ser transladado.
    /// \param centroid Vetor representando o centr�ide do objeto.
    void translateToCameraCenter(std::vector<vec3>& vertices, const vec3& centroid);

    /// \brief Calcula a dimens�o do objeto.
    /// \param vertices Vetor de v�rtices do objeto.
    /// \param centroid Vetor representando o centr�ide do objeto.
    /// \return Dimens�o calculada do objeto.
    double calcDimension(std::vector<vec3>& vertices, vec3& centroid);
};
