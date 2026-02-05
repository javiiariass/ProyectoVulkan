/**
 * @file GEApplication.cpp
 * @brief Implementación de la clase GEApplication.
 */

#include "GEApplication.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <windows.h>
#include <iostream>
#include <vector>
#include <glm/common.hpp>
#include "resource.h"

/**
 * @brief Ejecuta la aplicación.
 */
void GEApplication::run()
{
	this->window = initWindow();
	this->windowPos = initWindowPos();
	this->gc = new GEGraphicsContext(window);
	this->dc = new GEDrawingContext(this->gc, this->windowPos);
	this->cc = new GECommandContext(this->gc, this->dc->getImageCount());

	this->scene = new GEScene(gc, dc, cc);

	mainLoop();

	cleanup();
}

/**
 * @brief Inicializa la ventana.
 * @return Puntero a la ventana GLFW creada.
 */
GLFWwindow* GEApplication::initWindow()
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	GLFWwindow* w = glfwCreateWindow(WIDTH, HEIGHT, "Game Engine", nullptr, nullptr);
	glfwSetWindowUserPointer(w, this);
	glfwSetFramebufferSizeCallback(w, framebufferResizeCallback);
	glfwSetKeyCallback(w, keyCallback);
	glfwSetCursorPosCallback(w, cursorPositionCallback);
	glfwSetMouseButtonCallback(w, mouseButtonCallback);

	/*
	GLFWimage images[2];
	images[0].pixels = stbi_load("C:/GameEngine/Icon/toy.png", &images[0].width, &images[0].height, 0, 4); 
	images[1].pixels = stbi_load("C:/GameEngine/Icon/toy_small.png", &images[1].width, &images[1].height, 0, 4);
	glfwSetWindowIcon(window, 2, images);
	stbi_image_free(images[0].pixels);
	stbi_image_free(images[1].pixels);
	*/

	return w;
}

/**
 * @brief Inicializa la posición de la ventana.
 * @return Struct GEWindowPosition con la posición y tamaño de la ventana.
 */
GEWindowPosition GEApplication::initWindowPos()
{
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	GEWindowPosition wp = {};
	wp.fullScreen = false;
	glfwGetWindowSize(window, &wp.width, &wp.height);
	glfwGetWindowPos(window, &wp.Xpos, &wp.Ypos);
	wp.screenWidth = mode->width;
	wp.screenHeight = mode->height;
	return wp;
}


/**
 * @brief Bucle principal que procesa los eventos de la aplicación.
 */
void GEApplication::mainLoop()
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		draw();
	}
}

/**
 * @brief Lanza la generación del dibujo.
 */
void GEApplication::draw()
{
	dc->waitForNextImage(gc);
	scene->update(gc, dc->getCurrentImage());
	dc->submitGraphicsCommands(gc, cc->commandBuffers);
	dc->submitPresentCommands(gc);
}

/**
 * @brief Libera los recursos y finaliza la aplicación.
 */
void GEApplication::cleanup()
{
	scene->destroy(gc);
	cc->destroy(gc);
	dc->destroy(gc);
	delete scene;
	delete cc;
	delete dc;
	delete gc;
	glfwDestroyWindow(window);
	glfwTerminate();
}

/**
 * @brief Dibuja la ventana a pantalla completa o a tamaño configurable.
 */
void GEApplication::swapFullScreen()
{
	if (!windowPos.fullScreen)
	{
		glfwGetWindowSize(window, &windowPos.width, &windowPos.height);
		glfwGetWindowPos(window, &windowPos.Xpos, &windowPos.Ypos);
		windowPos.fullScreen = true;
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
	}
	else
	{
		windowPos.fullScreen = false;
		glfwSetWindowMonitor(window, nullptr, windowPos.Xpos, windowPos.Ypos, windowPos.width, windowPos.height, NULL);
	}
}

/**
 * @brief Respuesta a un evento de teclado sobre la aplicación.
 * @param window Ventana GLFW de tipo @ref GLFWwindow.
 * @param key Código de la tecla.
 * @param scancode Código de escaneo.
 * @param action Acción (presionar, soltar, repetir).
 * @param mods Modificadores activos.
 */
void GEApplication::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	GEApplication* app = (GEApplication*)glfwGetWindowUserPointer(window);
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		if (key == GLFW_KEY_F12) app->swapFullScreen();
		else app->scene->key_action(key, true);
	}
	else app->scene->key_action(key, false);
}

/**
 * @brief Respuesta a un evento de ratón sobre la aplicación.
 * @param window Ventana GLFW de tipo @ref GLFWwindow.
 * @param button Botón del ratón.
 * @param action Acción (presionar, soltar).
 * @param mods Modificadores activos.
 */
void GEApplication::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
}

/**
 * @brief Respuesta a un evento de movimiento del cursor sobre la aplicación.
 * @param window Ventana GLFW de tipo @ref GLFWwindow.
 * @param xpos Posición X del cursor.
 * @param ypos Posición Y del cursor.
 */
void GEApplication::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
}

/**
 * @brief Respuesta a un evento de redimensionamiento de la ventana de la aplicación.
 * @param window Ventana GLFW de tipo @ref GLFWwindow.
 * @param width Nuevo ancho.
 * @param height Nueva altura.
 */
void GEApplication::framebufferResizeCallback(GLFWwindow* window, int width, int height)
{
	GEApplication* app = (GEApplication*)glfwGetWindowUserPointer(window);
	if (height != 0)
	{
		app->resize();
	}
}

/**
 * @brief Reconstruye los objetos con el nuevo tamaño de ventana.
 */
void GEApplication::resize()
{
	if (!windowPos.fullScreen)
	{
		glfwGetWindowSize(window, &windowPos.width, &windowPos.height);
		glfwGetWindowPos(window, &windowPos.Xpos, &windowPos.Ypos);
	}

	dc->recreate(gc, windowPos);
	cc->destroy(gc);
	delete cc;

	this->cc = new GECommandContext(this->gc, this->dc->getImageCount());

	scene->recreate(gc, dc, cc);

	double aspect;
	if (!windowPos.fullScreen) aspect = (double)this->windowPos.width / (double)this->windowPos.height;
	else aspect = (double)this->windowPos.screenWidth / (double)this->windowPos.screenHeight;
	this->scene->aspect_ratio(aspect);
}

