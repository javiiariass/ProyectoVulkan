/**
 * @file GETransform.h
 * @brief Estructura para transformaciones usadas por las figuras.
 */

#pragma once

#include <glm/glm.hpp>

/**
 * @struct GETransform
 * @brief Estructura que almacena los datos necesarios para girar las figuras.
 */
typedef struct
{
	alignas(16) glm::mat4 MVP; ///< Matriz modelo-vista-proyección.
	alignas(16) glm::mat4 ViewMatrix; ///< Matriz de vista.
	alignas(16) glm::mat4 ModelViewMatrix; ///< Matriz modelo-vista.
} GETransform;