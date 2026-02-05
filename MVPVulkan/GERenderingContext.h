#pragma once

#include <vulkan/vulkan.h>
#include <iostream>
#include "GEGraphicsContext.h"
#include "GEDrawingContext.h"
#include "GEPipelineConfig.h"
#include "GEDepthBuffer.h"

/**
 * @file GERenderingContext.h
 * @brief Declaración de la clase GERenderingContext que describe un contexto de renderizado.
 */

/**
 * @class GERenderingContext
 * @brief Clase que describe un contexto de renderizado.
 */
class GERenderingContext
{
public:
	uint32_t imageCount; ///< Número de imágenes en el swapchain.
	VkDescriptorSetLayout descriptorSetLayout; ///< Layout de los descriptor sets.
	VkPipelineLayout pipelineLayout; ///< Layout del pipeline.

private:
	VkFormat format;
	VkExtent2D extent;
	VkRenderPass renderPass;
	VkPipeline graphicsPipeline;
	std::vector<GEDepthBuffer*> depthBuffers;
	std::vector<VkFramebuffer> framebuffers;
	VkViewport viewport;
	VkRect2D scissor;

public:
	/**
	 * @brief Construye el contexto de renderizado (render pass, pipeline y framebuffers).
	 * @param gc Contexto gráfico.
	 * @param dc Contexto de dibujo.
	 * @param config Configuración del pipeline.
	 */
	GERenderingContext(GEGraphicsContext* gc, GEDrawingContext* dc, GEPipelineConfig* config);

	/**
	 * @brief Destruye los recursos del contexto de renderizado.
	 * @param gc Contexto gráfico.
	 */
	void destroy(GEGraphicsContext* gc);

	/**
	 * @brief Prepara los buffers de comandos para añadir las operaciones de renderizado.
	 * @param commandBuffers Buffers de comandos a rellenar.
	 */
	void startFillingCommandBuffers(std::vector<VkCommandBuffer> commandBuffers);

	/**
	 * @brief Finaliza el llenado de los buffers de comandos.
	 * @param commandBuffers Buffers de comandos.
	 */
	void endFillingCommandBuffers(std::vector<VkCommandBuffer> commandBuffers);

private:
	// ===== Métodos de creación de componentes =====
	void createRenderPass(GEGraphicsContext* gc);
	void createGraphicsPipeline(GEGraphicsContext* gc, GEPipelineConfig* config);
	void createDepthBuffers(GEGraphicsContext* gc);
	void createFramebuffers(GEGraphicsContext* gc, GEDrawingContext* dc);

	// ===== Métodos de definición del pipeline de renderizado =====
	void createPipelineLayout(GEGraphicsContext* gc, GEPipelineConfig* config);
	void createVertexShaderStageCreateInfo(GEGraphicsContext* gc, int resource, VkShaderModule* vertShaderModule, VkPipelineShaderStageCreateInfo* vertShaderStageInfo);
	void createFragmentShaderStageCreateInfo(GEGraphicsContext* gc, int resource, VkShaderModule* fragShaderModule, VkPipelineShaderStageCreateInfo* fragShaderStageInfo);
	void createPipelineVertexInputStateCreateInfo(GEPipelineConfig* config, VkPipelineVertexInputStateCreateInfo* vertexInputInfo);
	void createPipelineInputAssemblyStateCreateInfo(VkPipelineInputAssemblyStateCreateInfo* inputAssembly);
	void createPipelineViewportStateCreateInfo(VkPipelineViewportStateCreateInfo* viewportState);
	void createPipelineRasterizationStateCreateInfo(GEPipelineConfig* config, VkPipelineRasterizationStateCreateInfo* rasterizer);
	void createPipelineMultisampleStateCreateInfo(VkPipelineMultisampleStateCreateInfo* multisampling);
	void createPipelineDepthStencilStateCreateInfo(GEPipelineConfig* config, VkPipelineDepthStencilStateCreateInfo* depthStencil);
	void createPipelineColorBlendStateCreateInfo(VkPipelineColorBlendAttachmentState* colorBlendAttachment, VkPipelineColorBlendStateCreateInfo* colorBlending);

	// ===== Métodos auxiliares =====
	VkShaderModule createShaderModule(GEGraphicsContext* gc, const std::vector<char>& code);
	std::vector<char> getFileFromResource(int resource);
};

