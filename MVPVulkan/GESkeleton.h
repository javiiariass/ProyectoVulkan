/**
 * @file GESkeleton.h
 * @brief Declaración de la clase GESkeleton que representa un esqueleto con articulaciones jerárquicas.
 */

#pragma once

#include "GEGraphicsContext.h"
#include "GERenderingContext.h"
#include "GEBalljoint.h"
#include "GEXMLParser.h"
#include "GELight.h"
#include <glm/glm.hpp>
#include <string>

/**
 * @class GESkeleton
 * @brief Representa un esqueleto completo con articulaciones jerárquicas.
 */
class GESkeleton {
private:
    std::string name; ///< Nombre del esqueleto.
    glm::vec3 position; ///< Posición global del esqueleto.
    glm::vec3 zAxis; ///< Eje Z local.
    glm::vec3 yAxis; ///< Eje Y local.
    std::vector<GEBalljoint*> rootJoints; ///< Articulaciones raíz del esqueleto.
    
    /**
     * @brief Construye la jerarquía de articulaciones desde body.skel.
     */
    void buildSkeleton();
    
    /**
     * @brief Crea recursivamente las articulaciones desde los datos parseados.
     * @param data Datos de la articulación.
     * @return Puntero a la articulación creada.
     */
    GEBalljoint* createJointFromData(const GEJointData& data);

public:
    /**
     * @brief Constructor del esqueleto.
     */
    GESkeleton();

    /**
     * @brief Destructor del esqueleto.
     */
    ~GESkeleton();
    
    /**
     * @brief Inicializa los recursos gráficos del esqueleto.
     * @param gc Contexto gráfico.
     * @param rc Contexto de renderizado.
     */
    void initialize(GEGraphicsContext* gc, GERenderingContext* rc);

    /**
     * @brief Destruye los recursos asociados al esqueleto.
     * @param gc Contexto gráfico.
     */
    void destroy(GEGraphicsContext* gc);

    /**
     * @brief Actualiza el esqueleto (transformaciones y memoria intermedia).
     * @param gc Contexto gráfico.
     * @param index Índice de la imagen a renderizar.
     * @param view Matriz de vista.
     * @param projection Matriz de proyección.
     */
    void update(GEGraphicsContext* gc, uint32_t index, glm::mat4 view, glm::mat4 projection);

    /**
     * @brief Añade comandos de dibujo del esqueleto al command buffer.
     * @param commandBuffer Buffer de comandos Vulkan.
     * @param pipelineLayout Layout del pipeline.
     * @param index Índice de imagen.
     */
    void addCommands(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, int index);

    /**
     * @brief Asigna la luz para el esqueleto.
     * @param light Estructura con los parámetros de la luz.
     */
    void setLight(GELight light);
    
    // Acceso a articulaciones
    /**
     * @brief Busca una articulación por nombre.
     * @param jointName Nombre de la articulación.
     * @return Puntero a la articulación o nullptr si no existe.
     */
    GEBalljoint* findJoint(const std::string& jointName);

    /**
     * @brief Obtiene la primera articulación raíz (pelvis).
     * @return Puntero a la articulación raíz.
     */
    GEBalljoint* getRoot() const;
    
    /**
     * @brief Obtiene todas las articulaciones raíz.
     * @return Vector de punteros a las articulaciones raíz.
     */
    const std::vector<GEBalljoint*>& getRootJoints() const;
    
    // Getters/Setters
    /**
     * @brief Establece la posición global del esqueleto.
     * @param pos Posición.
     */
    void setPosition(glm::vec3 pos);

    /**
     * @brief Obtiene la posición global del esqueleto.
     * @return Posición.
     */
    glm::vec3 getPosition() const;

    /**
     * @brief Ajusta la orientación local del esqueleto (ejes Z y Y).
     * @param z Vector que define el eje Z local.
     * @param y Vector que define el eje Y local.
     */
    void setOrientation(glm::vec3 z, glm::vec3 y);
};
