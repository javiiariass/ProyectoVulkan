/**
 * @file GEScene.h
 * @brief Declaración de la clase GEScene que contiene la escena con esqueleto animado.
 */

#pragma once

#include "GEGraphicsContext.h"
#include "GEDrawingContext.h"
#include "GECommandContext.h"
#include "GERenderingContext.h"

#include "GEFigure.h"
#include "GESkeleton.h"
#include "GEAnimation.h"
#include "GECamera.h"
#include <vulkan/vulkan.h>
#include <glm/glm.hpp>

/**
 * @class GEScene
 * @brief Escena con esqueleto animado realizando tiro libre.
 */
class GEScene
{
private:
    GERenderingContext* rc; ///< Contexto de renderizado.
    GEFigure* ground; ///< Figura del terreno.
    GESkeleton* skeleton; ///< Esqueleto de la escena.
    GEAnimation* animation; ///< Animación asociada.
    double lastTime; ///< Tiempo de la última actualización.
    GECamera* camera; ///< Cámara de la escena.
    glm::mat4 projection; ///< Matriz de proyección.

public:
    /**
     * @brief Construye la escena y crea los objetos gráficos.
     * @param gc Contexto gráfico.
     * @param dc Contexto de dibujo.
     * @param cc Contexto de comandos.
     */
    GEScene(GEGraphicsContext* gc, GEDrawingContext* dc, GECommandContext* cc);

    /**
     * @brief Destruye los componentes gráficos de la escena.
     * @param gc Contexto gráfico.
     */
    void destroy(GEGraphicsContext* gc);

    /**
     * @brief Reconstruye los componentes gráficos de la escena.
     * @param gc Contexto gráfico.
     * @param dc Contexto de dibujo.
     * @param cc Contexto de comandos.
     */
    void recreate(GEGraphicsContext* gc, GEDrawingContext* dc, GECommandContext* cc);

    /**
     * @brief Actualiza la escena (animaciones y transformaciones).
     * @param gc Contexto gráfico.
     * @param index Índice de la imagen a renderizar.
     */
    void update(GEGraphicsContext* gc, uint32_t index);

    /**
     * @brief Maneja acciones de teclado.
     * @param key Tecla (GLFW_KEY_*).
     * @param pressed true si la tecla está pulsada.
     */
    void key_action(int key, bool pressed);

    /**
     * @brief Ajusta la relación de aspecto y la matriz de proyección.
     * @param aspect Relación anchura/altura.
     */
    void aspect_ratio(double aspect);

private:
    /**
     * @brief Obtiene la configuración del pipeline para un extent dado.
     * @param extent Extensión de la imagen.
     * @return Nueva configuración del pipeline.
     */
    GEPipelineConfig* createPipelineConfig(VkExtent2D extent);

    /**
     * @brief Rellena los buffers de comandos para el renderizado.
     * @param commandBuffers Buffers de comandos a rellenar.
     */
    void fillCommandBuffers(std::vector<VkCommandBuffer> commandBuffers);

    /**
     * @brief Crea la animación de tiro libre.
     * @return Puntero a la animación creada.
     */
    GEAnimation* createBasketballThrowAnimation();
};
