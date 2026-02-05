/**
 * @file GEDrawingContext.h
 * @brief Declaración de la clase GEDrawingContext para gestionar swapchain y present.
 */

#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include "GEGraphicsContext.h"
#include "GEWindowPosition.h"

/**
 * @class GEDrawingContext
 * @brief Clase que contiene la información sobre el destino de las imágenes a generar (swapchain, vistas, colas de comandos).
 */
class GEDrawingContext
{
public:
	std::vector<VkImageView> imageViews; ///< Vistas de las imágenes del swapchain.

private:
	// ===== Campos auxiliares =====
	uint32_t imageCount; ///< Número de imágenes en la swapchain.
	uint32_t frameCount; ///< Número de frames en vuelo.
	size_t currentFrame = 0; ///< Índice del frame actual.
	uint32_t currentImage = 0; ///< Índice de la imagen actual.

	// ===== Componentes gráficos =====
	VkSwapchainKHR swapChain; ///< Swapchain de Vulkan.
	VkFormat imageFormat; ///< Formato de imagen.
	VkExtent2D imageExtent; ///< Extensión de las imágenes.
	std::vector<VkImage> images; ///< Imágenes de la swapchain.
	VkQueue graphicsQueue; ///< Cola gráfica.
	VkQueue presentQueue; ///< Cola de presentación.

	// ===== Sincronización entre imágenes =====
	std::vector<VkSemaphore> imageAvailableSemaphores; ///< Semáforos de imagen disponible.
	std::vector<VkSemaphore> renderFinishedSemaphores; ///< Semáforos de render terminado.
	std::vector<VkFence> inFlightFences; ///< Fences por frame.
	std::vector<VkFence> imagesInFlight; ///< Fence por imagen.

public:
	/**
	 * @brief Crea el contexto de dibujo (swapchain, vistas y sincronización).
	 * @param gc Contexto gráfico.
	 * @param wpos Posición y tamaño de la ventana.
	 */
	GEDrawingContext(GEGraphicsContext* gc, GEWindowPosition wpos);

	/**
	 * @brief Destruye los recursos del contexto de dibujo.
	 * @param gc Contexto gráfico.
	 */
	void destroy(GEGraphicsContext* gc);

	/**
	 * @brief Reconstruye el contexto de dibujo tras un cambio de tamaño.
	 * @param gc Contexto gráfico.
	 * @param wpos Nueva posición/tamaño de la ventana.
	 */
	void recreate(GEGraphicsContext* gc, GEWindowPosition wpos);

	/**
	 * @brief Obtiene el formato de la imagen.
	 * @return Formato de la imagen.
	 */
	VkFormat getFormat();

	/**
	 * @brief Obtiene la extensión de la imagen.
	 * @return Extensión de la imagen.
	 */
	VkExtent2D getExtent();

	/**
	 * @brief Obtiene el número de imágenes de la swapchain.
	 * @return Número de imágenes.
	 */
	uint32_t getImageCount();

	/**
	 * @brief Obtiene el índice de la imagen actual.
	 * @return Índice de la imagen.
	 */
	uint32_t getCurrentImage();

	// ===== Métodos de generación de la imagen =====
	/**
	 * @brief Espera y adquiere la siguiente imagen disponible.
	 * @param gc Contexto gráfico.
	 */
	void waitForNextImage(GEGraphicsContext* gc);

	/**
	 * @brief Envía los comandos gráficos para la imagen actual.
	 * @param gc Contexto gráfico.
	 * @param commandBuffers Vector con los command buffers.
	 */
	void submitGraphicsCommands(GEGraphicsContext* gc, std::vector<VkCommandBuffer> commandBuffers);

	/**
	 * @brief Envía los comandos de presentación para la imagen actual.
	 * @param gc Contexto gráfico.
	 */
	void submitPresentCommands(GEGraphicsContext* gc);

private:
	// ===== Métodos de creación de componentes =====
	void createSwapChain(GEGraphicsContext* gc, GEWindowPosition wpos);
	void createImageViews(VkDevice device);
	void createSyncObjects(VkDevice device);
	void createQueues(GEGraphicsContext* gc);

	// ===== Métodos auxiliares =====
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, GEWindowPosition wpos);
};

