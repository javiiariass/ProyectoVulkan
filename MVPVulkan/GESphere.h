/**
 * @file GESphere.h
 * @brief Declaración de la clase GESphere que describe una esfera.
 */

#pragma once

#include "GEFigure.h"

/**
 * @class GESphere
 * @brief Clase que describe una esfera.
 */
class GESphere : public GEFigure
{
public:
	/**
	 * @brief Crea la figura de la esfera.
	 * @param p Número de divisiones en latitud.
	 * @param m Número de divisiones en longitud.
	 * @param r Radio de la esfera.
	 */
	GESphere(int p, int m, float r);
};

