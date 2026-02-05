/**
 * @file GELight.h
 * @brief Declaración de la estructura GELight para iluminación.
 */

#pragma once

#include <glm/glm.hpp>

/**
 * @struct GELight
 * @brief Estructura que describe una fuente de luz direccional.
 */
typedef struct
{
	alignas(16) glm::vec3 Ldir;	///< Dirección de la luz
	alignas(16) glm::vec3 La;   ///< Intensidad ambiental
	alignas(16) glm::vec3 Ld;   ///< Intensidad difusa
	alignas(16) glm::vec3 Ls;   ///< Intensidad especular
} GELight;
