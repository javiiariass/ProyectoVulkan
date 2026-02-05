/**
 * @file GEWindowPosition.h
 * @brief Declaración de la estructura GEWindowPosition para ventanas.
 */

#pragma once

/**
 * @struct GEWindowPosition
 * @brief Estructura que almacena la posición y el tamaño de la ventana gráfica.
 */
typedef struct {
	int width;        ///< Ancho de la ventana en píxeles.
	int height;       ///< Alto de la ventana en píxeles.
	int Xpos;         ///< Posición X de la ventana.
	int Ypos;         ///< Posición Y de la ventana.
	int screenWidth;  ///< Ancho de la pantalla.
	int screenHeight; ///< Alto de la pantalla.
	bool fullScreen;  ///< Indica si la ventana está en pantalla completa.
} GEWindowPosition;
