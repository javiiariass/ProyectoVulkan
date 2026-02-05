/**
 * @file GEFigure.cpp
 * @brief Implementación de la clase GEFigure.
 */

#include "GEFigure.h"

#include "GEVertex.h"
#include "GETransform.h"
#include "GEMaterial.h"
#include "GELight.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

/**
 * @brief Inicializa los buffers de la figura.
 * @param gc Contexto gráfico.
 * @param rc Contexto de renderizado.
 */
void GEFigure::initialize(GEGraphicsContext* gc, GERenderingContext* rc)
{
	size_t vertexSize = sizeof(GEVertex) * vertices.size();
	vbo = new GEVertexBuffer(gc, vertexSize, vertices.data());

	size_t indexSize = sizeof(indices[0]) * indices.size();
	ibo = new GEIndexBuffer(gc, indexSize, indices.data());

	size_t transformBufferSize = sizeof(GETransform);
	transformBuffer = new GEUniformBuffer(gc, rc->imageCount, transformBufferSize);

	size_t materialBufferSize = sizeof(GEMaterial);
	materialBuffer = new GEUniformBuffer(gc, rc->imageCount, materialBufferSize);

	size_t lightBufferSize = sizeof(GELight);
	lightBuffer = new GEUniformBuffer(gc, rc->imageCount, lightBufferSize);

	std::vector<GEUniformBuffer*> ubos(3);
	ubos[0] = transformBuffer;
	ubos[1] = materialBuffer;
	ubos[2] = lightBuffer;

	dset = new GEDescriptorSet(gc, rc, ubos);

	location = glm::mat4(1.0f);
}

/**
 * @brief Libera los buffers de la figura.
 * @param gc Contexto gráfico.
 */
void GEFigure::destroy(GEGraphicsContext* gc)
{
	vbo->destroy(gc);
	ibo->destroy(gc);
	transformBuffer->destroy(gc);
	materialBuffer->destroy(gc);
	lightBuffer->destroy(gc);
	dset->destroy(gc);

	delete vbo;
	delete ibo;
	delete transformBuffer;
	delete materialBuffer;
	delete lightBuffer;
	delete dset;
}

/**
 * @brief Añade los comandos de renderizado al command buffer.
 * @param commandBuffer Buffer de comandos.
 * @param pipelineLayout Layout del pipeline.
 * @param index Índice de la imagen.
 */
void GEFigure::addCommands(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, int index)
{
	VkDeviceSize offset = 0;
	vkCmdBindVertexBuffers(commandBuffer, 0, 1, &(vbo->buffer), &offset);
	vkCmdBindIndexBuffer(commandBuffer, ibo->buffer, 0, VK_INDEX_TYPE_UINT16);
	vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &(dset->descriptorSets[index]), 0, nullptr);
	vkCmdDrawIndexed(commandBuffer, (uint32_t)indices.size(), 1, 0, 0, 0);
}

/**
 * @brief Actualiza las variables uniformes sobre una imagen del swapchain.
 * @param gc Contexto gráfico.
 * @param index Índice de la imagen.
 * @param view Matriz de vista.
 * @param projection Matriz de proyección.
 */
void GEFigure::update(GEGraphicsContext* gc, uint32_t index, glm::mat4 view, glm::mat4 projection)
{
	GETransform transform;
	transform.MVP = projection * view * location;
	transform.ModelViewMatrix = view * location;
	transform.ViewMatrix = view;

	transformBuffer->update(gc, index, sizeof(GETransform), &transform);
	materialBuffer->update(gc, index, sizeof(GEMaterial), &material);
	lightBuffer->update(gc, index, sizeof(GELight), &light);
}

/**
 * @brief Resetea la matriz de localización (Model).
 */
void GEFigure::resetLocation()
{
	location = glm::mat4(1.0f);
}

/**
 * @brief Asigna la matriz de localización (Model).
 * @param m Matriz de localización.
 */
void GEFigure::setLocation(glm::mat4 m)
{
	location = glm::mat4(m);
}

/**
 * @brief Añade un desplazamiento a la matriz de localización (Model).
 * @param t Vector de traslación.
 */
void GEFigure::translate(glm::vec3 t)
{
	location = glm::translate(location, t);
}

/**
 * @brief Añade una rotación a la matriz de localización (Model).
 * @param angle Ángulo de rotación en grados.
 * @param axis Eje de rotación.
 */
void GEFigure::rotate(float angle, glm::vec3 axis)
{
	location = glm::rotate(location, glm::radians(angle), axis);
}

/**
 * @brief Asigna las propiedades del material de la figura.
 * @param m Material a asignar.
 */
void GEFigure::setMaterial(GEMaterial m)
{
	this->material = m;
}

/**
 * @brief Asigna las propiedades de la luz que ilumina la figura.
 * @param l Luz a asignar.
 */
void GEFigure::setLight(GELight l)
{
	this->light = l;
}