
/**
 * @file GEBalljoint.h
 * @brief Declaración de la clase GEBalljoint para articulaciones jerárquicas.
 */

#pragma once

#include "GEGraphicsContext.h"
#include "GERenderingContext.h"
#include "GESphere.h"
#include "GECylinder.h"
#include "GELight.h"
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "DEBUG.h"

/**
 * @class GEBalljoint
 * @brief Representa una articulación esférica con 3 grados de libertad.
 *
 * Soporta jerarquía padre-hijo para formar esqueletos completos.
 */
class GEBalljoint
{
private:
    // ===== Propiedades básicas =====
    GLfloat length;       ///< Longitud del hueso.
    glm::vec3 location;   ///< Posición de la articulación.
    glm::vec3 dir;        ///< Dirección del hueso.
    glm::vec3 up;         ///< Vector arriba local.
    glm::vec3 right;      ///< Vector derecha local.
    GLfloat angles[3];    ///< Ángulos de rotación (X, Y, Z).
    GESphere *joint;      ///< Esfera que representa la articulación.
    GECylinder *bone;     ///< Cilindro que representa el hueso.

    // ===== Jerarquía =====
    std::string name;                   ///< Nombre de la articulación.
    glm::vec3 offset;                   ///< Desplazamiento respecto al padre.
    glm::vec3 localZAxis;               ///< Eje Z local.
    glm::vec3 localYAxis;               ///< Eje Y local.
    std::vector<GEBalljoint *> children; ///< Articulaciones hijas.
    glm::mat4 worldMatrix;              ///< Matriz de transformación mundo.

    /**
     * @struct Limits
     * @brief Estructura que almacena los límites de rotación de la articulación.
     */
    struct Limits
    {
        glm::vec3 min;  ///< Límites mínimos de rotación (X, Y, Z).
        glm::vec3 max;  ///< Límites máximos de rotación (X, Y, Z).
        bool enabled;   ///< Indica si los límites están activos.
// Test
// Si macro definida en main, mostrar si algún valor en las articulaciones alcanza límite
#ifdef DEBUG
        bool wasLimited; ///< Para debug: evitar spam de mensajes.
#endif
    } limits; ///< Límites de rotación de esta articulación.

    /**
     * @brief Calcula la matriz de transformación local.
     */
    void ComputeMatrix();

    /**
     * @brief Calcula la matriz de transformación con matriz del padre.
     * @param parentMatrix Matriz de transformación del nodo padre.
     */
    void ComputeMatrix(glm::mat4 parentMatrix);

public:
    /**
     * @brief Construye una articulación.
     * @param length Longitud del hueso.
     */
    GEBalljoint(float length);

    /**
     * @brief Constructor jerárquico para esqueletos.
     * @param name Nombre de la articulación.
     * @param length Longitud del hueso.
     * @param offset Desplazamiento local.
     * @param zAxis Eje Z local.
     * @param yAxis Eje Y local.
     */
    GEBalljoint(const std::string &name, float length,
                glm::vec3 offset, glm::vec3 zAxis, glm::vec3 yAxis);

    // Ciclo de vida
    /**
     * @brief Inicializa las piezas de la articulación.
     * @param gc Contexto gráfico.
     * @param rc Contexto de renderizado.
     */
    void initialize(GEGraphicsContext *gc, GERenderingContext *rc);
    /**
     * @brief Destruye los buffers de las piezas.
     * @param gc Contexto gráfico.
     */
    void destroy(GEGraphicsContext *gc);
    /**
     * @brief Añade los comandos de dibujo.
     * @param commandBuffer Buffer de comandos.
     * @param pipelineLayout Layout del pipeline.
     * @param index Índice de la imagen.
     */
    void addCommands(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, int index);
    /**
     * @brief Actualiza las variables uniformes.
     * @param gc Contexto gráfico.
     * @param index Índice de la imagen.
     * @param view Matriz de vista.
     * @param projection Matriz de proyección.
     */
    void update(GEGraphicsContext *gc, uint32_t index, glm::mat4 view, glm::mat4 projection);

    // Métodos recursivos
    /**
     * @brief Inicializa recursivamente esta articulación y sus hijas.
     * @param gc Contexto gráfico.
     * @param rc Contexto de renderizado.
     */
    void initializeRecursive(GEGraphicsContext *gc, GERenderingContext *rc);
    /**
     * @brief Destruye recursivamente esta articulación y sus hijas.
     * @param gc Contexto gráfico.
     */
    void destroyRecursive(GEGraphicsContext *gc);
    /**
     * @brief Añade comandos recursivamente.
     * @param commandBuffer Buffer de comandos.
     * @param pipelineLayout Layout del pipeline.
     * @param index Índice de la imagen.
     */
    void addCommandsRecursive(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, int index);
    /**
     * @brief Actualiza recursivamente con matriz del padre.
     * @param gc Contexto gráfico.
     * @param index Índice de la imagen.
     * @param parentMatrix Matriz del padre.
     * @param view Matriz de vista.
     * @param projection Matriz de proyección.
     */
    void updateRecursive(GEGraphicsContext *gc, uint32_t index,
                         glm::mat4 parentMatrix, glm::mat4 view, glm::mat4 projection);
    /**
     * @brief Asigna la luz recursivamente.
     * @param l Propiedades de la luz.
     */
    void setLightRecursive(GELight l);

    // Setters
    /**
     * @brief Asigna las propiedades de la luz.
     * @param l Propiedades de la luz.
     */
    void setLight(GELight l);
    /**
     * @brief Asigna la posición de la articulación.
     * @param loc Posición.
     */
    void setLocation(glm::vec3 loc);
    /**
     * @brief Asigna la orientación de la articulación.
     * @param nDir Dirección.
     * @param nUp Vector arriba.
     */
    void setOrientation(glm::vec3 nDir, glm::vec3 nUp);
    /**
     * @brief Asigna la rotación de la articulación (respetando límites).
     * @param xrot Rotación en X.
     * @param yrot Rotación en Y.
     * @param zrot Rotación en Z.
     */
    void setPose(float xrot, float yrot, float zrot);
    /**
     * @brief Asigna los límites de rotación.
     * @param min Límite mínimo.
     * @param max Límite máximo.
     */
    void setLimits(glm::vec3 min, glm::vec3 max);

    // Jerarquía
    /**
     * @brief Añade una articulación hija.
     * @param child Puntero a la articulación hija.
     */
    void addChild(GEBalljoint *child);
    /**
     * @brief Busca una articulación hija por nombre.
     * @param searchName Nombre a buscar.
     * @return Puntero a la articulación encontrada o nullptr.
     */
    GEBalljoint *findChild(const std::string &searchName);

    // Getters
    /**
     * @brief Obtiene el nombre de la articulación.
     * @return Nombre de la articulación.
     */
    const std::string &getName() const;
    /**
     * @brief Obtiene la lista de hijos.
     * @return Vector de punteros a hijos.
     */
    const std::vector<GEBalljoint *> &getChildren() const;
    /**
     * @brief Obtiene la matriz mundo.
     * @return Matriz de transformación mundo.
     */
    glm::mat4 getWorldMatrix() const;
    /**
     * @brief Obtiene la matriz en el extremo del hueso.
     * @return Matriz en el extremo del hueso.
     */
    glm::mat4 getBoneEndMatrix() const;
};
