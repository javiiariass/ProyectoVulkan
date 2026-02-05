/**
 * @file GEIndexBuffer.h
 * @brief Declaración de la clase GEIndexBuffer para buffers de índices.
 */

#pragma once

#include <vulkan/vulkan.h>
#include "GEGraphicsContext.h"

/**
 * @class GEIndexBuffer
 * @brief Clase que describe un buffer de índices.
 */
class GEIndexBuffer
{
public:
	VkBuffer buffer;           ///< Buffer Vulkan que contiene índices.
	VkDeviceMemory memory;     ///< Memoria asociada al buffer.

	/**
	 * @brief Crea un Index Buffer y sube los datos al buffer.
	 * @param gc Contexto gráfico.
	 * @param size Tamaño del buffer en bytes.
	 * @param data Puntero a los datos de índices.
	 */
	GEIndexBuffer(GEGraphicsContext* gc, size_t size, const void* data);

	/**
	 * @brief Destruye los recursos del index buffer.
	 * @param gc Contexto gráfico.
	 */
	void destroy(GEGraphicsContext* gc);
};

