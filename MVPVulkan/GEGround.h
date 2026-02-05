/**
 * @file GEGround.h
 * @brief Declaración de la clase GEGround para terreno rectangular.
 */

#pragma once

#include "GEFigure.h"

/**
 * @class GEGround
 * @brief Clase que describe un terreno rectangular.
 */
class GEGround : public GEFigure
{
public:
	/**
	 * @brief Crea la figura del suelo.
	 * @param l1 Longitud en el eje X.
	 * @param l2 Longitud en el eje Z.
	 */
	GEGround(float l1, float l2);
};


