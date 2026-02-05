/**
 * @file GEVertex.h
 * @brief Declaración de la estructura GEVertex para vértices.
 */

#pragma once

#include <glm\glm.hpp>

/**
 * @struct GEVertex
 * @brief Estructura que describe los atributos de un vértice.
 */
typedef struct 
{
	glm::vec3 pos;  ///< Posición del vértice en el espacio 3D.
	glm::vec3 norm; ///< Vector normal del vértice.
} GEVertex;

