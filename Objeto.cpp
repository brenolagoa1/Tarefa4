#include "Objeto.h"
#include "assert.h"
#include <iostream> 

/**
 * @brief Construtor da classe Objeto.
 *
 * @param filePath Caminho do arquivo a ser lido.
 */
    Objeto::Objeto(const std::string & filePath) {
    std::ifstream file(filePath);
    if (!file) {
        std::cerr << "Erro ao abrir o arquivo: " << filePath << std::endl;
        exit(1);
    }
    bool flag = false;

    double somax = 0, somay = 0, somaz = 0;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;

        iss >> token;

        if (token == "v") {
            double x, y, z;
            iss >> x >> y >> z;
            if (x > 1 || x < -1 || y > 1 || y < -1 || z > 1 || z < -1) {
                flag = true;
            }

            vertices.emplace_back(x, y, z);
        }
        else if (token == "f") {
            int v1;
            char separator;

            std::string t;
            for (int i = 0; i < 3; i++) {
                iss >> token;
                std::stringstream ttoken(token);
                std::getline(ttoken, t, '/');

                //std::cout << t << std::endl;
                v1 = atoi(t.c_str());
                assert(v1 > 0);
                assert(v1 <= vertices.size());
                faces.push_back(v1 - 1); // Subtrai 1 para ajustar ao formato com índices iniciando em 1
            }
            //printf("\n");
        }
    }

    vec3 centroid;

    double bigDif = calcDimension(vertices, centroid);

    translateToCameraCenter(vertices, -centroid);

    redimensionarVertices(vertices, bigDif);

    translateToCameraCenter(vertices, vec3(0, 0, -1));

    assert(faces.size() % 3 == 0);

    // Construir objetos Triangulo a partir das faces
    for (size_t i = 0; i < faces.size(); i += 3) {
        int v0Index = faces[i];
        int v1Index = faces[i + 1];
        int v2Index = faces[i + 2];

        vec3 v0 = vertices[v0Index];
        vec3 v1 = vertices[v1Index];
        vec3 v2 = vertices[v2Index]; // erro aqui de out of array

        triangulos.push_back(criarTriangulo(v0, v1, v2));
    }
}

/**
 * @brief Obtém os vértices do objeto.
 *
 * @return const std::vector<vec3>& Vetor de vértices.
 */
const std::vector<vec3>& Objeto::getVertices() const {
    return vertices;
}

/**
 * @brief Obtém os índices dos vértices que compõem as faces do objeto.
 *
 * @return const std::vector<int>& Vetor de índices de vértices das faces.
 */
const std::vector<int>& Objeto::getFaces() const {
    return faces;
}

/**
 * @brief Obtém os Triângulos que compõem o objeto.
 *
 * @return const std::vector<Triangulo>& Vetor de Triângulos.
 */
const std::vector<Triangulo>& Objeto::getTriangulos() const {
    return triangulos;
}

/**
 * @brief Cria um Triângulo a partir de três vértices.
 *
 * @param v0 Vértice 0.
 * @param v1 Vértice 1.
 * @param v2 Vértice 2.
 * @return Triangulo Triângulo criado.
 */
Triangulo Objeto::criarTriangulo(const vec3& v0, const vec3& v1, const vec3& v2) {
    // Implemente a criação de um Triangulo usando os vértices v0, v1, v2
    // Pode ser semelhante ao que você já tinha implementado
    return Triangulo(v0, v1, v2);
}

/**
 * @brief Redimensiona os vértices do objeto.
 *
 * @param vertices Vetor de vértices a ser redimensionado.
 * @param biggerDif Maior diferença entre as coordenadas.
 */
void Objeto::redimensionarVertices(std::vector<vec3>& vertices, double biggerDif) {
    // Redimensionar os vértices
    for (vec3& vertex : vertices) {
        vertex.x = (vertex.x) / biggerDif;
        vertex.y = (vertex.y) / biggerDif;
        //vertex.z = std::abs((vertex.z - minZ) / biggerDif) * -15 ;
        vertex.z = (vertex.z) / biggerDif;
    }
}

/**
 * @brief Calcula o centroide dos vértices.
 *
 * @param vertices Vetor de vértices.
 * @return vec3 Centroide calculado.
 */
vec3 Objeto::calculateCentroid(std::vector<vec3>& vertices) {
    double sumX = 0, sumY = 0, sumZ = 0;

    for (const vec3& vertex : vertices) {
        sumX += vertex.x;
        sumY += vertex.y;
        sumZ += vertex.z;
    }
    vec3 centroid;
    centroid.x = sumX / vertices.size();
    centroid.y = sumY / vertices.size();
    centroid.z = sumZ / vertices.size();

    return centroid;
}

/**
 * @brief Translada os vértices para o centro da câmera.
 *
 * @param vertices Vetor de vértices a ser transladado.
 * @param centroid Vetor de deslocamento para o centro da câmera.
 */
void Objeto::translateToCameraCenter(std::vector<vec3>& vertices, const vec3& centroid) {
    for (vec3& vertex : vertices) {
        vertex.x += centroid.x;
        vertex.y += centroid.y;
        vertex.z += centroid.z;
    }
}

/**
 * @brief Calcula a dimensão do objeto e o centroide.
 *
 * @param vertices Vetor de vértices.
 * @param centroid Centroide calculado.
 * @return double Maior diferença entre as coordenadas.
 */
double Objeto::calcDimension(std::vector<vec3>& vertices, vec3& centroid) {
    // Encontrar os limites iniciais
    double minX = std::numeric_limits<double>::max();
    double maxX = std::numeric_limits<double>::min();
    double minY = std::numeric_limits<double>::max();
    double maxY = std::numeric_limits<double>::min();
    double minZ = std::numeric_limits<double>::max();
    double maxZ = std::numeric_limits<double>::min();

    for (const vec3& vertex : vertices) {
        minX = std::min(minX, vertex.x);
        maxX = std::max(maxX, vertex.x);
        minY = std::min(minY, vertex.y);
        maxY = std::max(maxY, vertex.y);
        minZ = std::min(minZ, vertex.z);
        maxZ = std::max(maxZ, vertex.z);
    }

    // Encontrar a maior diferença
    double biggerDif = std::max({ maxX - minX, maxY - minY, maxZ - minZ });

    //centroid
    centroid.x = minX + (maxX - minX) / 2;
    centroid.y = minY + (maxY - minY) / 2;
    centroid.z = minZ + (maxZ - minZ) / 2;

    return biggerDif;
}
