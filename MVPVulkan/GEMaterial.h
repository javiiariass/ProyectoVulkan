/**
 * @file GEMaterial.h
 * @brief Declaración de la estructura GEMaterial para materiales.
 */

#pragma once

#include <glm/glm.hpp>

/**
 * @struct GEMaterial
 * @brief Estructura que describe las propiedades de un material.
 */
typedef struct
{
	alignas(16) glm::vec3 Ka;       ///< Reflectividad ambiental
	alignas(16) glm::vec3 Kd;       ///< Reflectividad difusa
	alignas(16) glm::vec3 Ks;       ///< Reflectividad especular
	alignas(4) float Shininess;     ///< Factor de brillo especular
} GEMaterial;

