/**
 * @file GEDescriptorSet.h
 * @brief Declaración de la clase GEDescriptorSet para gestionar conjuntos de descriptores.
 */

#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include "GEGraphicsContext.h"
#include "GERenderingContext.h"
#include "GEUniformBuffer.h"

/**
 * @class GEDescriptorSet
 * @brief Clase que describe un conjunto de descriptores.
 */
class GEDescriptorSet
{
private:
	VkDescriptorPool descriptorPool; ///< Descriptor pool usado para asignar conjuntos.

public:
	std::vector<VkDescriptorSet> descriptorSets; ///< Conjuntos de descriptores por imagen.

public:
	/**
	 * @brief Crea los conjuntos de descriptores asociados a los uniform buffers.
	 * @param gc Contexto gráfico.
	 * @param rc Contexto de renderizado.
	 * @param ubos Vector de uniform buffers a enlazar.
	 */
	GEDescriptorSet(GEGraphicsContext* gc, GERenderingContext* rc, std::vector<GEUniformBuffer*> ubos);

	/**
	 * @brief Destruye los conjuntos de descriptores y libera recursos.
	 * @param gc Contexto gráfico.
	 */
	void destroy(GEGraphicsContext* gc);
};

