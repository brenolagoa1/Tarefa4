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
                faces.push_back(v1 - 1); // Subtrai 1 para ajustar ao formato com �ndices iniciando em 1
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
 * @brief Obt�m os v�rtices do objeto.
 *
 * @return const std::vector<vec3>& Vetor de v�rtices.
 */
const std::vector<vec3>& Objeto::getVertices() const {
    return vertices;
}

/**
 * @brief Obt�m os �ndices dos v�rtices que comp�em as faces do objeto.
 *
 * @return const std::vector<int>& Vetor de �ndices de v�rtices das faces.
 */
const std::vector<int>& Objeto::getFaces() const {
    return faces;
}

/**
 * @brief Obt�m os Tri�ngulos que comp�em o objeto.
 *
 * @return const std::vector<Triangulo>& Vetor de Tri�ngulos.
 */
const std::vector<Triangulo>& Objeto::getTriangulos() const {
    return triangulos;
}

/**
 * @brief Cria um Tri�ngulo a partir de tr�s v�rtices.
 *
 * @param v0 V�rtice 0.
 * @param v1 V�rtice 1.
 * @param v2 V�rtice 2.
 * @return Triangulo Tri�ngulo criado.
 */
Triangulo Objeto::criarTriangulo(const vec3& v0, const vec3& v1, const vec3& v2) {
    // Implemente a cria��o de um Triangulo usando os v�rtices v0, v1, v2
    // Pode ser semelhante ao que voc� j� tinha implementado
    return Triangulo(v0, v1, v2);
}

/**
 * @brief Redimensiona os v�rtices do objeto.
 *
 * @param vertices Vetor de v�rtices a ser redimensionado.
 * @param biggerDif Maior diferen�a entre as coordenadas.
 */
void Objeto::redimensionarVertices(std::vector<vec3>& vertices, double biggerDif) {
    // Redimensionar os v�rtices
    for (vec3& vertex : vertices) {
        vertex.x = (vertex.x) / biggerDif;
        vertex.y = (vertex.y) / biggerDif;
        //vertex.z = std::abs((vertex.z - minZ) / biggerDif) * -15 ;
        vertex.z = (vertex.z) / biggerDif;
    }
}

/**
 * @brief Calcula o centroide dos v�rtices.
 *
 * @param vertices Vetor de v�rtices.
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
 * @brief Translada os v�rtices para o centro da c�mera.
 *
 * @param vertices Vetor de v�rtices a ser transladado.
 * @param centroid Vetor de deslocamento para o centro da c�mera.
 */
void Objeto::translateToCameraCenter(std::vector<vec3>& vertices, const vec3& centroid) {
    for (vec3& vertex : vertices) {
        vertex.x += centroid.x;
        vertex.y += centroid.y;
        vertex.z += centroid.z;
    }
}

/**
 * @brief Calcula a dimens�o do objeto e o centroide.
 *
 * @param vertices Vetor de v�rtices.
 * @param centroid Centroide calculado.
 * @return double Maior diferen�a entre as coordenadas.
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

    // Encontrar a maior diferen�a
    double biggerDif = std::max({ maxX - minX, maxY - minY, maxZ - minZ });

    //centroid
    centroid.x = minX + (maxX - minX) / 2;
    centroid.y = minY + (maxY - minY) / 2;
    centroid.z = minZ + (maxZ - minZ) / 2;

    return biggerDif;
}
