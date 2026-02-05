/**
 * @file GEUniformBuffer.cpp
 * @brief Implementación de la clase GEUniformBuffer.
 */

#include "GEUniformBuffer.h"

#include <iostream>

/**
 * @brief Crea una lista de Uniform Buffers asociados a cada imagen a generar.
 * @param gc Contexto gráfico.
 * @param imageCount Número de imágenes del swapchain.
 * @param bufferSize Tamaño del buffer en bytes.
 */
GEUniformBuffer::GEUniformBuffer(GEGraphicsContext* gc, uint32_t imageCount, size_t bufferSize)
{
	this->bufferSize = bufferSize;
	this->buffers.resize(imageCount);
	this->memories.resize(imageCount);

	for (uint32_t i = 0; i < imageCount; i++)
	{
		VkBuffer buffer;
		VkDeviceMemory deviceMemory;

		VkBufferCreateInfo bufferInfo = {};
		bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferInfo.size = bufferSize;
		bufferInfo.usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
		bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		if (vkCreateBuffer(gc->device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create buffer!");
		}

		VkMemoryRequirements memRequirements;
		vkGetBufferMemoryRequirements(gc->device, buffer, &memRequirements);

		VkMemoryAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.allocationSize = memRequirements.size;
		allocInfo.memoryTypeIndex = gc->findMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

		if (vkAllocateMemory(gc->device, &allocInfo, nullptr, &deviceMemory) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to allocate buffer memory!");
		}

		vkBindBufferMemory(gc->device, buffer, deviceMemory, 0);

		buffers[i] = buffer;
		memories[i] = deviceMemory;
	}
}

/**
 * @brief Actualiza el valor almacenado en un Uniform Buffer.
 * @param gc Contexto gráfico.
 * @param currentImage Índice de la imagen actual.
 * @param size Tamaño de los datos a actualizar.
 * @param data Puntero a los datos.
 */
void GEUniformBuffer::update(GEGraphicsContext* gc, uint32_t currentImage, size_t size, const void* data)
{
	void* mdata;
	vkMapMemory(gc->device, memories[currentImage], 0, size, 0, &mdata);
	memcpy(mdata, data, size);
	vkUnmapMemory(gc->device, memories[currentImage]);
}

/**
 * @brief Destruye los campos de un Uniform Buffer.
 * @param gc Contexto gráfico.
 */
void GEUniformBuffer::destroy(GEGraphicsContext* gc)
{
	uint32_t size = (uint32_t) buffers.size();
	for (uint32_t i = 0; i < size; i++)
	{
		vkDestroyBuffer(gc->device, buffers[i], nullptr);
		vkFreeMemory(gc->device, memories[i], nullptr);
	}
}

