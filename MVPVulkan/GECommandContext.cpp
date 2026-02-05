/**
 * @file GECommandContext.cpp
 * @brief Implementación de la clase GECommandContext.
 */

#include "GECommandContext.h"

#include <iostream>

///////////////////////////////////////////////////////////////////////////////////////////
/////                                                                                 /////
/////                              Métodos públicos                                   /////
/////                                                                                 /////
///////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Construye los buffers de comandos.
 * @param gc Contexto gráfico.
 * @param imageCount Número de imágenes del swapchain.
 */
GECommandContext::GECommandContext(GEGraphicsContext* gc, uint32_t imageCount)
{
	createCommandPool(gc);
	createCommandBuffers(gc, imageCount);
}

/**
 * @brief Destruye los buffers de comandos.
 * @param gc Contexto gráfico.
 */
void GECommandContext::destroy(GEGraphicsContext* gc)
{
	size_t bufferCount = commandBuffers.size();

	vkFreeCommandBuffers(gc->device, commandPool, (uint32_t) bufferCount, commandBuffers.data());
	vkDestroyCommandPool(gc->device, commandPool, nullptr);
}

///////////////////////////////////////////////////////////////////////////////////////////
/////                                                                                 /////
/////                    Métodos de creación de los componentes                       /////
/////                                                                                 /////
///////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Crea el command pool vinculado a la familia de colas para gráficos.
 * @param gc Contexto gráfico.
 */
void GECommandContext::createCommandPool(GEGraphicsContext* gc)
{
	VkCommandPoolCreateInfo poolInfo{};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.queueFamilyIndex = gc->graphicsQueueFamilyIndex;

	if (vkCreateCommandPool(gc->device, &poolInfo, nullptr, &commandPool) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create command pool!");
	}
}

/**
 * @brief Crea los buffers de comandos que se enviarán a la cola gráfica.
 * 
 * El contenido de los buffers incluye la orden de dibujar.
 * @param gc Contexto gráfico.
 * @param imageCount Número de imágenes del swapchain.
 */
void GECommandContext::createCommandBuffers(GEGraphicsContext* gc, uint32_t imageCount)
{
	commandBuffers.resize(imageCount);

	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = imageCount;

	if (vkAllocateCommandBuffers(gc->device, &allocInfo, commandBuffers.data()) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to allocate command buffers!");
	}
}

