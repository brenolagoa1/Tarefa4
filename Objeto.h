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
    /// \param filePath Caminho do arquivo contendo a descrição do objeto.
    Objeto(const std::string& filePath);

    /// \brief Obtém os vértices do objeto.
    /// \return Vetor contendo os vértices do objeto.
    const std::vector<vec3>& getVertices() const;

    /// \brief Obtém os índices dos vértices que compõem as faces do objeto.
    /// \return Vetor contendo os índices dos vértices das faces do objeto.
    const std::vector<int>& getFaces() const;

    /// \brief Obtém os triângulos que compõem o objeto.
    /// \return Vetor contendo os triângulos do objeto.
    const std::vector<Triangulo>& getTriangulos() const;

private:
    std::vector<vec3> vertices; ///< Vetores que representam os vértices do objeto.
    std::vector<int> faces; ///< Índices dos vértices das faces do objeto.
    std::vector<Triangulo> triangulos; ///< Triângulos que compõem o objeto.

    /// \brief Cria um triângulo a partir de três vértices.
    /// \param v0 Vértice 0 do triângulo.
    /// \param v1 Vértice 1 do triângulo.
    /// \param v2 Vértice 2 do triângulo.
    /// \return Triângulo criado a partir dos vértices dados.
    Triangulo criarTriangulo(const vec3& v0, const vec3& v1, const vec3& v2);

    /// \brief Redimensiona os vértices do objeto.
    /// \param vertices Vetor de vértices a ser redimensionado.
    /// \param biggerDif Diferença máxima permitida para redimensionamento.
    void redimensionarVertices(std::vector<vec3>& vertices, double biggerDif);

    /// \brief Calcula o centróide dos vértices do objeto.
    /// \param vertices Vetor de vértices do objeto.
    /// \return Vetor representando o centróide.
    vec3 calculateCentroid(std::vector<vec3>& vertices);

    /// \brief Translada os vértices para o centro da câmera.
    /// \param vertices Vetor de vértices a ser transladado.
    /// \param centroid Vetor representando o centróide do objeto.
    void translateToCameraCenter(std::vector<vec3>& vertices, const vec3& centroid);

    /// \brief Calcula a dimensão do objeto.
    /// \param vertices Vetor de vértices do objeto.
    /// \param centroid Vetor representando o centróide do objeto.
    /// \return Dimensão calculada do objeto.
    double calcDimension(std::vector<vec3>& vertices, vec3& centroid);
};
