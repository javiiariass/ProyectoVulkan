/**
 * @file GECylinder.h
 * @brief Declaración de la clase GECylinder.
 */

#pragma once

#include "GEFigure.h"

/**
 * @class GECylinder
 * @brief Clase que describe un cilindro.
 */
class GECylinder : public GEFigure
{
public:
	/**
	 * @brief Crea la figura del cilindro.
	 * @param p Número de divisiones en altura.
	 * @param m Número de divisiones en circunferencia.
	 * @param r Radio del cilindro.
	 * @param l Longitud (altura) del cilindro.
	 */
	GECylinder(int p, int m, float r, float l);
};

