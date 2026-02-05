/**
 * @file GEGraphicsContext.h
 * @brief Declaración de la clase GEGraphicsContext que almacena el contexto gráfico de Vulkan.
 */

#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

/**
 * @class GEGraphicsContext
 * @brief Clase que almacena el contexto gráfico de Vulkan (instancia y dispositivo).
 */
class GEGraphicsContext
{
public:
	VkInstance instance; ///< Instancia de Vulkan.
	VkSurfaceKHR surface; ///< Superficie de presentación.
	VkPhysicalDevice physicalDevice; ///< Dispositivo físico seleccionado.
	VkDevice device; ///< Dispositivo lógico.
	uint32_t graphicsQueueFamilyIndex; ///< Índice de la familia de colas para gráficos.
	uint32_t presentQueueFamilyIndex; ///< Índice de la familia de colas para presentación.

private:
	VkPhysicalDeviceMemoryProperties memProperties; ///< Propiedades de memoria del dispositivo.

public:
	/**
	 * @brief Construye el contexto gráfico de Vulkan.
	 * @param window Ventana GLFW sobre la que crear el contexto.
	 */
	GEGraphicsContext(GLFWwindow* window);

	/**
	 * @brief Destruye el contexto gráfico y libera recursos.
	 */
	~GEGraphicsContext();

	/**
	 * @brief Busca el tipo de memoria adecuado para un filtro y propiedades dadas.
	 * @param typeFilter Máscara de tipos de memoria disponibles.
	 * @param properties Propiedades de memoria requeridas.
	 * @return Índice del tipo de memoria adecuado.
	 */
	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

	/**
	 * @brief Busca el formato de imagen adecuado para el buffer de profundidad.
	 * @return Formato de profundidad soportado.
	 */
	VkFormat findDepthFormat();

private:
	// ===== Métodos de inicialización de Vulkan =====
	/**
	 * @brief Crea la instancia de Vulkan.
	 */
	void createInstance();

	/**
	 * @brief Crea la superficie para la ventana GLFW.
	 * @param window Ventana GLFW.
	 */
	void createSurface(GLFWwindow* window);

	/**
	 * @brief Selecciona el dispositivo físico adecuado.
	 */
	void pickPhysicalDevice();

	/**
	 * @brief Crea el dispositivo lógico y configura las colas.
	 */
	void createLogicalDevice();

	// ===== Métodos auxiliares =====
	/**
	 * @brief Muestra propiedades de la instancia Vulkan (depuración).
	 */
	void showInstanceProperties();

	/**
	 * @brief Comprueba si un dispositivo físico es adecuado.
	 * @param pDevice Dispositivo físico a verificar.
	 * @return true si es adecuado.
	 */
	bool isDeviceSuitable(VkPhysicalDevice pDevice);

	/**
	 * @brief Muestra y escribe en fichero las propiedades de los dispositivos detectados.
	 */
	void showDevices();

	/**
	 * @brief Escribe en fichero las características detalladas de un dispositivo.
	 * @param pDevice Dispositivo físico a describir.
	 * @param index Índice del dispositivo.
	 */
	void resumeDeviceProperties(VkPhysicalDevice pDevice, int index);
};

