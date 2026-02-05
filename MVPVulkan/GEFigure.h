/**
 * @file GEFigure.h
 * @brief Declaración de la clase GEFigure para figuras de malla.
 */

#pragma once

#include "GEGraphicsContext.h"
#include "GERenderingContext.h"
#include "GEVertex.h"
#include "GETransform.h"
#include "GEMaterial.h"
#include "GELight.h"
#include "GEVertexBuffer.h"
#include "GEIndexBuffer.h"
#include "GEUniformBuffer.h"
#include "GEDescriptorSet.h"
#include <glm/glm.hpp>
#include <vector>

/**
 * @class GEFigure
 * @brief Clase que describe una figura formada por una malla de vértices.
 */
class GEFigure
{
protected:
	std::vector<GEVertex> vertices; ///< Lista de vértices.
	std::vector<uint16_t> indices; ///< Lista de índices.
	glm::mat4 location; ///< Matriz de localización (modelo).
	GEMaterial material; ///< Propiedades del material.
	GELight light; ///< Propiedades de la luz.

public:
	/**
	 * @brief Inicializa los buffers de la figura.
	 * @param gc Contexto gráfico.
	 * @param rc Contexto de renderizado.
	 */
	void initialize(GEGraphicsContext* gc, GERenderingContext* rc);

	/**
	 * @brief Libera los buffers de la figura.
	 * @param gc Contexto gráfico.
	 */
	void destroy(GEGraphicsContext* gc);

	/**
	 * @brief Añade los comandos de renderizado al command buffer.
	 * @param commandBuffer Buffer de comandos.
	 * @param pipelineLayout Layout del pipeline.
	 * @param index Índice de la imagen.
	 */
	void addCommands(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, int index);

	/**
	 * @brief Actualiza las variables uniformes.
	 * @param gc Contexto gráfico.
	 * @param index Índice de la imagen.
	 * @param view Matriz de vista.
	 * @param projection Matriz de proyección.
	 */
	void update(GEGraphicsContext* gc, uint32_t index, glm::mat4 view, glm::mat4 projection);

	/**
	 * @brief Resetea la matriz de localización (Model).
	 */
	void resetLocation();

	/**
	 * @brief Asigna la matriz de localización (Model).
	 * @param m Matriz de localización.
	 */
	void setLocation(glm::mat4 m);

	/**
	 * @brief Añade un desplazamiento a la matriz de localización (Model).
	 * @param t Vector de traslación.
	 */
	void translate(glm::vec3 t);

	/**
	 * @brief Añade una rotación a la matriz de localización (Model).
	 * @param angle Ángulo de rotación en grados.
	 * @param axis Eje de rotación.
	 */
	void rotate(float angle, glm::vec3 axis);

	/**
	 * @brief Asigna las propiedades del material de la figura.
	 * @param m Material a asignar.
	 */
	void setMaterial(GEMaterial m);

	/**
	 * @brief Asigna las propiedades de la luz que ilumina la figura.
	 * @param l Luz a asignar.
	 */
	void setLight(GELight l);

private:
	GEVertexBuffer* vbo; ///< Vertex buffer object.
	GEIndexBuffer* ibo; ///< Index buffer object.
	GEUniformBuffer* transformBuffer; ///< Uniform buffer para transformaciones.
	GEUniformBuffer* materialBuffer; ///< Uniform buffer para material.
	GEUniformBuffer* lightBuffer; ///< Uniform buffer para luz.
	GEDescriptorSet* dset; ///< Descriptor set asociado.
};

