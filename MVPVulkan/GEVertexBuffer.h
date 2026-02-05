#pragma once

#include <vulkan/vulkan.h>
#include "GEGraphicsContext.h"

/**
 * @class GEVertexBuffer
 * @brief Clase que describe un buffer de vértices.
 */
class GEVertexBuffer
{
public:
	VkBuffer buffer;
	VkDeviceMemory memory;

	GEVertexBuffer(GEGraphicsContext* gc, size_t size, const void* data);
	void destroy(GEGraphicsContext* gc);
};

