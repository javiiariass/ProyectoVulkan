/**
 * @file GECamera.cpp
 * @brief Implementación de la clase GECamera.
 */

#include "GECamera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/**
 * @brief Construye una cámara.
 * 
 * La posición inicial es (0,0,0).
 * La orientación inicial es el sistema de coordenadas del modelo.
 * El tamaño del paso inicial es 0.1.
 * El tamaño del giro inicial es 1.0 grados.
 */
GECamera::GECamera()
{
	Pos = glm::vec3(0.0f, 0.0f, 0.0f);
	Dir = glm::vec3(0.0f, 0.0f, 1.0f);
	Up = glm::vec3(0.0f, 1.0f, 0.0f);
	Right = glm::vec3(1.0f, 0.0f, 0.0f);

	moveStep = 0.1f;
	turnStep = 1.0f;
	cosAngle = (float)cos(glm::radians(turnStep));
	sinAngle = (float)sin(glm::radians(turnStep));

	turnLeftPressed = false;
	turnRightPressed = false;
	turnUpPressed = false;
	turnDownPressed = false;
	turnCWPressed = false;
	turnCCWPressed = false;
	moveLeftPressed = false;
	moveRightPressed = false;
	moveUpPressed = false;
	moveDownPressed = false;
}

/**
 * @brief Obtiene la matriz View para situar la cámara.
 * @return Matriz de vista.
 */
glm::mat4 GECamera::getViewMatrix()
{
	return glm::lookAt(Pos, Pos - Dir, Up);
}

/**
 * @brief Asigna la posición de la cámara.
 * @param pos Posición en coordenadas del modelo.
 */
void GECamera::setPosition(glm::vec3 pos)
{
	Pos = glm::vec3(pos);
}

/**
 * @brief Asigna la orientación de la cámara.
 * @param dir Dirección de la cámara.
 * @param up Vector arriba.
 */
void GECamera::setDirection(glm::vec3 dir, glm::vec3 up)
{
	Dir = glm::vec3(dir);
	Up = glm::vec3(up);
	Right = glm::cross(Up, Dir);
}

/**
 * @brief Asigna el avance en cada paso.
 * @param step Tamaño del paso.
 */
void GECamera::setMoveStep(float step)
{
	moveStep = step;
}

/**
 * @brief Asigna el ángulo de giro en cada paso.
 * @param step Ángulo de giro en grados.
 */
void GECamera::setTurnStep(float step)
{
	turnStep = step;
	cosAngle = (float)cos(glm::radians(turnStep));
	sinAngle = (float)sin(glm::radians(turnStep));
}

/**
 * @brief Obtiene la posición de la cámara.
 * @return Posición de la cámara.
 */
glm::vec3 GECamera::getPosition()
{
	return Pos;
}

/**
 * @brief Obtiene la orientación de la cámara (eje Z).
 * @return Dirección de la cámara.
 */
glm::vec3 GECamera::getDirection()
{
	return Dir;
}

/**
 * @brief Obtiene la orientación cenital de la cámara (eje Y).
 * @return Vector arriba de la cámara.
 */
glm::vec3 GECamera::getUpDirection()
{
	return Up;
}

/**
 * @brief Obtiene el avance en cada paso.
 * @return Tamaño del paso.
 */
float GECamera::getMoveStep()
{
	return moveStep;
}

/**
 * @brief Obtiene el ángulo de giro en cada paso.
 * @return Ángulo de giro en grados.
 */
float GECamera::getTurnStep()
{
	return turnStep;
}

/**
 * @brief Actualiza la posición y orientación de la cámara.
 */
void GECamera::update()
{
	if (turnLeftPressed && !turnRightPressed) turnLeft();
	if (!turnLeftPressed && turnRightPressed) turnRight();
	if (turnUpPressed && !turnDownPressed) turnUp();
	if (!turnUpPressed && turnDownPressed) turnDown();
	if (turnCWPressed && !turnCCWPressed) turnCW();
	if (!turnCWPressed && turnCCWPressed) turnCCW();
	if (moveLeftPressed && !moveRightPressed) moveLeft();
	if (!moveLeftPressed && moveRightPressed) moveRight();
	if (moveUpPressed && !moveDownPressed) moveUp();
	if (!moveUpPressed && moveDownPressed) moveDown();

	moveFront();
}

/**
 * @brief Mueve el observador un paso hacia adelante (dirección -Dir).
 */
void GECamera::moveFront()
{
	Pos -= moveStep * Dir;
}


/**
 * @brief Mueve el observador un paso hacia atrás (dirección Dir).
 */
void GECamera::moveBack()
{
	Pos += moveStep * Dir;
}

/**
 * @brief Mueve el observador un paso hacia la izquierda.
 */
void GECamera::moveLeft()
{
//	Pos -= moveStep * Right;
	Pos -= 0.1f * Right;
}

/**
 * @brief Mueve el observador un paso hacia la derecha.
 */
void GECamera::moveRight()
{
//	Pos += moveStep * Right;
	Pos += 0.1f * Right;
}

/**
 * @brief Mueve el observador un paso hacia arriba.
 */
void GECamera::moveUp()
{
//	Pos += moveStep * Up;
	Pos += 0.1f * Up;
}

/**
 * @brief Mueve el observador un paso hacia abajo.
 */
void GECamera::moveDown()
{
//	Pos -= moveStep * Up;
	Pos -= 0.1f * Up;
}

/**
 * @brief Rota el observador un paso hacia su derecha.
 */
void GECamera::turnRight()
{
	Dir.x = cosAngle * Dir.x - sinAngle * Right.x;
	Dir.y = cosAngle * Dir.y - sinAngle * Right.y;
	Dir.z = cosAngle * Dir.z - sinAngle * Right.z;

	// Right = Up x Dir
	Right = glm::cross(Up, Dir);
}

/**
 * @brief Rota el observador un paso hacia su izquierda.
 */
void GECamera::turnLeft()
{
	Dir.x = cosAngle * Dir.x + sinAngle * Right.x;
	Dir.y = cosAngle * Dir.y + sinAngle * Right.y;
	Dir.z = cosAngle * Dir.z + sinAngle * Right.z;

	// Right = Up x Dir
	Right = glm::cross(Up, Dir);
}

/**
 * @brief Rota el observador un paso hacia arriba.
 */
void GECamera::turnUp()
{
	Dir.x = cosAngle * Dir.x - sinAngle * Up.x;
	Dir.y = cosAngle * Dir.y - sinAngle * Up.y;
	Dir.z = cosAngle * Dir.z - sinAngle * Up.z;

	// Up = Dir x Right
	Up = glm::cross(Dir, Right);
}

/**
 * @brief Rota el observador un paso hacia abajo.
 */
void GECamera::turnDown()
{
	Dir.x = cosAngle * Dir.x + sinAngle * Up.x;
	Dir.y = cosAngle * Dir.y + sinAngle * Up.y;
	Dir.z = cosAngle * Dir.z + sinAngle * Up.z;

	// Up = Dir x Right
	Up = glm::cross(Dir, Right);
}

/**
 * @brief Rota el observador un paso en sentido horario.
 */
void GECamera::turnCW()
{
	Up.x = cosAngle * Up.x + sinAngle * Right.x;
	Up.y = cosAngle * Up.y + sinAngle * Right.y;
	Up.z = cosAngle * Up.z + sinAngle * Right.z;

	// Right = Up x Dir
	Right = glm::cross(Up, Dir);
}

/**
 * @brief Rota el observador un paso en sentido antihorario.
 */
void GECamera::turnCCW()
{
	Up.x = cosAngle * Up.x - sinAngle * Right.x;
	Up.y = cosAngle * Up.y - sinAngle * Right.y;
	Up.z = cosAngle * Up.z - sinAngle * Right.z;

	// Right = Up x Dir
	Right = glm::cross(Up, Dir);
}

/**
 * @brief Activa o desactiva el giro a la izquierda.
 * @param flag true para activar, false para desactivar.
 */
void GECamera::setTurnLeft(bool flag)
{
	turnLeftPressed = flag;
}

/**
 * @brief Activa o desactiva el giro a la derecha.
 * @param flag true para activar, false para desactivar.
 */
void GECamera::setTurnRight(bool flag)
{
	turnRightPressed = flag;
}

/**
 * @brief Activa o desactiva el giro hacia arriba.
 * @param flag true para activar, false para desactivar.
 */
void GECamera::setTurnUp(bool flag)
{
	turnUpPressed = flag;
}

/**
 * @brief Activa o desactiva el giro hacia abajo.
 * @param flag true para activar, false para desactivar.
 */
void GECamera::setTurnDown(bool flag)
{
	turnDownPressed = flag;
}

/**
 * @brief Activa o desactiva el giro horario.
 * @param flag true para activar, false para desactivar.
 */
void GECamera::setTurnCW(bool flag)
{
	turnCWPressed = flag;
}

/**
 * @brief Activa o desactiva el giro antihorario.
 * @param flag true para activar, false para desactivar.
 */
void GECamera::setTurnCCW(bool flag)
{
	turnCCWPressed = flag;
}

/**
 * @brief Activa o desactiva el desplazamiento a la izquierda.
 * @param flag true para activar, false para desactivar.
 */
void GECamera::setMoveLeft(bool flag)
{
	moveLeftPressed = flag;
}

/**
 * @brief Activa o desactiva el desplazamiento a la derecha.
 * @param flag true para activar, false para desactivar.
 */
void GECamera::setMoveRight(bool flag)
{
	moveRightPressed = flag;
}

/**
 * @brief Activa o desactiva el desplazamiento hacia arriba.
 * @param flag true para activar, false para desactivar.
 */
void GECamera::setMoveUp(bool flag)
{
	moveUpPressed = flag;
}

/**
 * @brief Activa o desactiva el desplazamiento hacia abajo.
 * @param flag true para activar, false para desactivar.
 */
void GECamera::setMoveDown(bool flag)
{
	moveDownPressed = flag;
}