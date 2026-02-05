/**
 * @file GECommandContext.h
 * @brief Declaración de la clase GECommandContext que gestiona buffers de comandos.
 * @author Javi
 */

#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include "GEGraphicsContext.h"

/**
 * @class GECommandContext
 * @brief Clase que almacena los buffers de comandos vinculados a cada imagen de la swapchain.
 */
class GECommandContext
{
public:
	std::vector<VkCommandBuffer> commandBuffers;  ///< Buffers de comandos por imagen.

	/**
	 * @brief Construye los buffers de comandos.
	 * @param gc Contexto gráfico.
	 * @param imageCount Número de imágenes de la swapchain.
	 */
	GECommandContext(GEGraphicsContext* gc, uint32_t imageCount);

	/**
	 * @brief Destruye los buffers de comandos.
	 * @param gc Contexto gráfico.
	 */
	void destroy(GEGraphicsContext* gc);

private:
	VkCommandPool commandPool;  ///< Pool de comandos usado para asignar buffers.
	
	/**
	 * @brief Crea el command pool vinculado a la familia de colas para gráficos.
	 * @param gc Contexto gráfico.
	 */
	void createCommandPool(GEGraphicsContext* gc);

	/**
	 * @brief Crea los buffers de comandos que se enviarán a la cola gráfica.
	 * @param gc Contexto gráfico.
	 * @param imageCount Número de imágenes del swapchain.
	 */
	void createCommandBuffers(GEGraphicsContext* gc, uint32_t imageCount);
};

