/**
 * @file GEApplication.h
 * @brief Declaración de la clase GEApplication que crea y lanza la aplicación gráfica.
 */

#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "GEWindowPosition.h"
#include "GEGraphicsContext.h"
#include "GEDrawingContext.h"
#include "GECommandContext.h"
#include "GEScene.h"

const int WIDTH = 800;
const int HEIGHT = 600;

/**
 * @class GEApplication
 * @brief Clase que crea y lanza la aplicación gráfica.
 */
class GEApplication
{
public:
	/**
	 * @brief Ejecuta la aplicación.
	 */
	void run();

private:
	GLFWwindow* window;  ///< Ventana GLFW.
	GEWindowPosition windowPos;
	GEGraphicsContext* gc;
	GEDrawingContext* dc;
	GECommandContext* cc;
	GEScene* scene;

	// ===== Métodos principales =====
	/**
	 * @brief Inicializa la ventana GLFW.
	 * @return Puntero a la ventana GLFW creada.
	 */
	GLFWwindow* initWindow();

	/**
	 * @brief Inicializa la posición de la ventana.
	 * @return Struct con posición y tamaño.
	 */
	GEWindowPosition initWindowPos();

	/**
	 * @brief Bucle principal que procesa eventos y dibuja cada frame.
	 */
	void mainLoop();

	/**
	 * @brief Lanza la generación del dibujo.
	 */
	void draw();

	/**
	 * @brief Libera los recursos y finaliza la aplicación.
	 */
	void cleanup();

	/**
	 * @brief Cambia entre pantalla completa y modo ventana.
	 */
	void swapFullScreen();

	/**
	 * @brief Reconstruye los objetos con el nuevo tamaño de ventana.
	 */
	void resize();

	// ===== Respuesta a eventos =====
	/**
	 * @brief Respuesta a un evento de teclado.
	 * @param window Ventana GLFW.
	 * @param key Código de la tecla.
	 * @param scancode Código de escaneo.
	 * @param action Acción (presionar, soltar, repetir).
	 * @param mods Modificadores activos.
	 */
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	/**
	 * @brief Respuesta a un evento de botón de ratón.
	 * @param window Ventana GLFW.
	 * @param button Botón del ratón.
	 * @param action Acción (presionar, soltar).
	 * @param mods Modificadores activos.
	 */
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

	/**
	 * @brief Respuesta a un evento de movimiento del cursor.
	 * @param window Ventana GLFW.
	 * @param xpos Posición X del cursor.
	 * @param ypos Posición Y del cursor.
	 */
	static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);

	/**
	 * @brief Respuesta a un evento de redimensionamiento de la ventana.
	 * @param window Ventana GLFW.
	 * @param width Nuevo ancho.
	 * @param height Nueva altura.
	 */
	static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
};

