#pragma once

#include <vulkan/vulkan.h>
#include <vector>

/**
 * @file GEPipelineConfig.h
 * @brief Declaración de la clase GEPipelineConfig que almacena la configuración de un pipeline de renderizado.
 */

/**
 * @class GEPipelineConfig
 * @brief Almacena la configuración de un pipeline de renderizado.
 */
class GEPipelineConfig {
public:
	int vertex_shader; ///< Identificador del recurso del shader de vértices.
	int fragment_shader; ///< Identificador del recurso del shader de fragmento.

	int attrStride; ///< Tamaño en bytes del stride de los atributos de vértice.
	std::vector<VkFormat> attrFormats; ///< Formatos de los atributos de vértice.
	std::vector<int> attrOffsets; ///< Offsets de los atributos dentro del vértice.

	std::vector<VkDescriptorType> descriptorTypes; ///< Tipos de descriptores usados por el pipeline.
	std::vector<VkShaderStageFlags> descriptorStages; ///< Etapas de shader para cada descriptor.

	VkBool32 depthTestEnable; ///< Habilita test de profundidad.
	VkCullModeFlags cullMode; ///< Modo de culling.
	VkExtent2D extent; ///< Extensión de la imagen (swapchain).

	/**
	 * @brief Construye un objeto con valores por defecto.
	 */
	GEPipelineConfig();
};