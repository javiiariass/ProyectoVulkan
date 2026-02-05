/**
 * @file GECamera.h
 * @brief Declaración de la clase GECamera para gestión de cámara 3D.
 */

#pragma once

#include <glm/glm.hpp>

/**
 * @class GECamera
 * @brief Clase que representa una cámara en el espacio 3D.
 */
class GECamera {
public:
	/**
	 * @brief Constructor por defecto.
	 */
	GECamera();

	/**
	 * @brief Obtiene la matriz View para situar la cámara.
	 * @return Matriz de vista.
	 */
	glm::mat4 getViewMatrix();

	/**
	 * @brief Asigna la posición de la cámara.
	 * @param pos Posición en coordenadas del modelo.
	 */
	void setPosition(glm::vec3 pos);

	/**
	 * @brief Asigna la orientación de la cámara.
	 * @param dir Dirección de la cámara.
	 * @param up Vector arriba.
	 */
	void setDirection(glm::vec3 dir, glm::vec3 up);

	/**
	 * @brief Asigna el avance en cada paso.
	 * @param step Tamaño del paso.
	 */
	void setMoveStep(float step);

	/**
	 * @brief Asigna el ángulo de giro en cada paso.
	 * @param step Ángulo de giro en grados.
	 */
	void setTurnStep(float step);

	/**
	 * @brief Obtiene la posición de la cámara.
	 * @return Posición de la cámara.
	 */
	glm::vec3 getPosition();

	/**
	 * @brief Obtiene la dirección (eje Z) de la cámara.
	 * @return Dirección de la cámara.
	 */
	glm::vec3 getDirection();

	/**
	 * @brief Obtiene el vector arriba (eje Y) de la cámara.
	 * @return Vector arriba.
	 */
	glm::vec3 getUpDirection();

	/**
	 * @brief Obtiene el avance en cada paso.
	 * @return Tamaño del paso.
	 */
	float getMoveStep();

	/**
	 * @brief Obtiene el ángulo de giro en cada paso.
	 * @return Ángulo de giro en grados.
	 */
	float getTurnStep();

	/**
	 * @brief Actualiza la posición y orientación según entradas.
	 */
	void update();

	/**
	 * @brief Activa o desactiva el giro a la izquierda.
	 * @param flag true para activar, false para desactivar.
	 */
	void setTurnLeft(bool flag);
	void setTurnRight(bool flag);
	void setTurnUp(bool flag);
	void setTurnDown(bool flag);
	void setTurnCW(bool flag);
	void setTurnCCW(bool flag);
	void setMoveLeft(bool flag);
	void setMoveRight(bool flag);
	void setMoveUp(bool flag);
	void setMoveDown(bool flag);

private:
	glm::vec3 Pos;   ///< Posición de la cámara en coordenadas del mundo.
	glm::vec3 Dir;   ///< Vector dirección (eje Z) de la cámara.
	glm::vec3 Up;    ///< Vector 'arriba' (eje Y) de la cámara.
	glm::vec3 Right; ///< Vector derecho (eje X) de la cámara.

	float moveStep; ///< Tamaño del paso para movimientos.
	float turnStep; ///< Ángulo de giro en grados.
	float cosAngle; ///< Coseno del ángulo de giro (cache).
	float sinAngle; ///< Seno del ángulo de giro (cache).

	bool turnLeftPressed;  ///< Flag de giro a la izquierda.
	bool turnRightPressed; ///< Flag de giro a la derecha.
	bool turnUpPressed;    ///< Flag de giro hacia arriba.
	bool turnDownPressed;  ///< Flag de giro hacia abajo.
	bool turnCWPressed;    ///< Flag de giro horario.
	bool turnCCWPressed;   ///< Flag de giro antihorario.
	bool moveLeftPressed;  ///< Flag de desplazamiento a la izquierda.
	bool moveRightPressed; ///< Flag de desplazamiento a la derecha.
	bool moveUpPressed;    ///< Flag de desplazamiento hacia arriba.
	bool moveDownPressed;  ///< Flag de desplazamiento hacia abajo.

	/**
	 * @brief Rota el observador un paso hacia su derecha.
	 */
	void turnRight();

	/**
	 * @brief Rota el observador un paso hacia su izquierda.
	 */
	void turnLeft();

	/**
	 * @brief Rota el observador un paso hacia arriba.
	 */
	void turnUp();

	/**
	 * @brief Rota el observador un paso hacia abajo.
	 */
	void turnDown();

	/**
	 * @brief Rota el observador un paso en sentido horario.
	 */
	void turnCW();

	/**
	 * @brief Rota el observador un paso en sentido antihorario.
	 */
	void turnCCW();

	/**
	 * @brief Mueve el observador un paso hacia la izquierda.
	 */
	void moveLeft();

	/**
	 * @brief Mueve el observador un paso hacia la derecha.
	 */
	void moveRight();

	/**
	 * @brief Mueve el observador un paso hacia arriba.
	 */
	void moveUp();

	/**
	 * @brief Mueve el observador un paso hacia abajo.
	 */
	void moveDown();

	/**
	 * @brief Mueve el observador un paso hacia adelante (dirección -Dir).
	 */
	void moveFront();

	/**
	 * @brief Mueve el observador un paso hacia atrás (dirección Dir).
	 */
	void moveBack();
};

