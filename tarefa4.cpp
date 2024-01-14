#define cimg_display 0
#include "CImg.h"
#include "matvec.h"
#include "Ray.h"
#include "objeto.h"
#include "Triangulo.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace cimg_library;




/**
 * @brief Verifica se um raio atinge um triângulo no espaço 3D.
 * @param v0,v1,v2 Os vértices do triângulo.
 * @param r O raio a ser verificado.
 * @return true se houver interseção, false caso contrário.
 */
bool hit_triangle(const vec3& v0, const vec3& v1, const vec3& v2, const Ray& r) {
    vec3 e1 = v1 - v0;
    vec3 e2 = v2 - v0;
    vec3 h = cross(r.direction(), e2);
    double a = dot(e1, h);

    if (a > -1e-6 && a < 1e-6)
        return false;

    double f = 1.0 / a;
    vec3 s = r.origin() - v0;
    double u = f * dot(s, h);

    if (u < 0.0 || u > 1.0)
        return false;

    vec3 q = cross(s, e1);
    double v = f * dot(r.direction(), q);

    if (v < 0.0 || u + v > 1.0)
        return false;

    double t = f * dot(e2, q);

    return t > 1e-6;  // Considerar apenas interseções à frente do raio
}


/**
 * @brief Verifica se um raio atinge uma esfera no espaço 3D.
 * @param center O centro da esfera.
 * @param radius O raio da esfera.
 * @param r O raio a ser verificado.
 * @return true se houver interseção, false caso contrário.
 */
bool hit_sphere(const vec3& center, double radius, const Ray& r) {
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(oc, r.direction());
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;
    return (discriminant >= 0);
}


/**
 * @brief Salva uma imagem usando a biblioteca CImg.
 * @param imagem A imagem a ser salva.
 * @param nomeArquivo O nome do arquivo de destino.
 */
void salvarImagem(const CImg<unsigned char>& imagem, const std::string& nomeArquivo) {
    imagem.save_png(nomeArquivo.c_str());
}


/**
 * @brief Calcula a cor de um pixel na imagem gerada considerando uma esfera.
 * @param r O raio lançado.
 * @return A cor calculada para o pixel.
 */
vec3 ray_color_sphere(const Ray& r) {
    if (hit_sphere(vec3(0, 0, -1), 0.5, r))
        return vec3(1, 0, 0);  // Cor da esfera

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y + 1.0);
    return (1.0 - a) * vec3(1.0, 1.0, 1.0) + a * vec3(0.5, 0.7, 1.0);
}


/**
 * @brief Calcula a cor de um pixel na imagem gerada considerando um triângulo.
 * @param triangulo O triângulo a ser verificado.
 * @param r O raio lançado.
 * @param[out] hit_detected Um ponteiro para um bool que indica se houve um hit.
 * @return A cor calculada para o pixel.
 */
vec3 ray_color_triangle(const Triangulo& triangulo, const Ray& r, bool* hit_detected) {
    vec3 v0, v1, v2;
    std::tie(v0, v1, v2) = triangulo.getVertices();

    if (hit_triangle(v0, v1, v2, r)) {
        if (hit_detected != nullptr) {
            *hit_detected = true;
        }
        return vec3(0, 1, 0);  // Cor do triângulo
    }

    if (hit_detected != nullptr) {
        *hit_detected = false;
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y + 1.0);
    return (1.0 - a) * vec3(1.0, 1.0, 1.0) + a * vec3(0.5, 0.7, 1.0);
}





/**
 * @brief Função principal do programa.
 * @return 0 em caso de sucesso e tem as duas imagens sendo geradas
 */
int main() {
    // Image
    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 800;
    int image_height = static_cast<int>(image_width / aspect_ratio);

    // Camera
    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);
    auto camera_center = vec3(0, 0, 0);
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height; 
    auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    
    // Definir o triângulo a partir de um arquivo .obj
    Objeto meuObjeto("C:\\Users\\lagoa\\source\\repos\\tarefa4\\seahorse.obj");
    const std::vector<Triangulo>& triangulosLidos = meuObjeto.getTriangulos();


    // Render
    CImg<unsigned char> imagem_triangulo_lido(image_width, image_height, 1, 3, 255);
    CImg<unsigned char> imagem_esfera(image_width, image_height, 1, 3, 0);
    CImg<unsigned char> imagem_triangulo(image_width, image_height, 1, 3, 0);

    


    for (int j = 0; j < image_height; ++j) {
        //std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' ;
        for (int i = 0; i < image_width; ++i) {
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            Ray r(camera_center, ray_direction);

            

            // Esfera
            vec3 pixel_color_esfera = ray_color_sphere(r);
            unsigned char cor_esfera[3] = { static_cast<unsigned char>(255.999 * pixel_color_esfera.x),
                                           static_cast<unsigned char>(255.999 * pixel_color_esfera.y),
                                           static_cast<unsigned char>(255.999 * pixel_color_esfera.z) };
            imagem_esfera.draw_point(i, j, 0, cor_esfera);

            //triangulo
            Triangulo trianguloTeste = Triangulo(vec3(-1, -0.5, -1), vec3(1, -0.5, -1), vec3(0, 0.5, -1));

            bool hit_detected_triangulo = false;
            vec3 pixel_color_triangulo = ray_color_triangle(trianguloTeste, r, &hit_detected_triangulo);
            if (hit_detected_triangulo) {
                // Faça algo se houve um hit no triângulo de teste
                //std::cout << "Hit detected in the test triangle!\n";
            }
            unsigned char cor_triangulo[3] = { static_cast<unsigned char>(255.999 * pixel_color_triangulo.x),
                                                static_cast<unsigned char>(255.999 * pixel_color_triangulo.y),
                                                static_cast<unsigned char>(255.999 * pixel_color_triangulo.z) };
            imagem_triangulo.draw_point(i, j, 0, cor_triangulo);

            // obj Lido
            bool hit_detected_lido = false;
            vec3 cor_final_lido = vec3(1.0, 1.0, 1.0);  // Cor de fundo padrão
            for (const auto& trianguloLido : triangulosLidos) {
                vec3 pixel_color_triangulo_lido = ray_color_triangle(trianguloLido, r, &hit_detected_lido);

                if (hit_detected_lido) {
                    // Usar a cor do triângulo quando houver hit
                    cor_final_lido = pixel_color_triangulo_lido;

                    
                    //std::cout << "Hit detected in a loaded triangle!\n";

                    // Não é necessário continuar verificando outros triângulos após o primeiro hit
                    break;
                }
            }

            unsigned char cor_triangulo_lido[3] = { static_cast<unsigned char>(255.999 * cor_final_lido.x),
                                                    static_cast<unsigned char>(255.999 * cor_final_lido.y),
                                                    static_cast<unsigned char>(255.999 * cor_final_lido.z) };
            imagem_triangulo_lido.draw_point(i, j, 0, cor_triangulo_lido);

        }
    }

    std::clog << "\rDone.\n";

    // Salvar as imagens    
    salvarImagem(imagem_esfera, "esfera.png");
    salvarImagem(imagem_triangulo, "triangulo.png");
    salvarImagem(imagem_triangulo_lido, "cavaloMarinho.png");
    

    return 0;
}

