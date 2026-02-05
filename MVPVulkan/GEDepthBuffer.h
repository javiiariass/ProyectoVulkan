/**
 * @file GEDepthBuffer.h
 * @brief Declaración de la clase GEDepthBuffer que gestiona el recurso de profundidad.
 */

#pragma once

#include <vulkan/vulkan.h>
#include "GEGraphicsContext.h"

/**
 * @class GEDepthBuffer
 * @brief Clase que describe un buffer de profundidad.
 */
class GEDepthBuffer
{
public:
	VkImage image;            ///< Imagen de profundidad.
	VkDeviceMemory imageMemory; ///< Memoria asociada a la imagen.
	VkImageView imageView;    ///< Vista de la imagen.

	/**
	 * @brief Crea un buffer de profundidad (imagen, memoria y vista).
	 * @param gc Contexto gráfico.
	 * @param extent Dimensiones de la imagen.
	 */
	GEDepthBuffer(GEGraphicsContext* gc, VkExtent2D extent);

	/**
	 * @brief Destruye el buffer de profundidad liberando recursos Vulkan.
	 * @param gc Contexto gráfico.
	 */
	void destroy(GEGraphicsContext* gc);
};

