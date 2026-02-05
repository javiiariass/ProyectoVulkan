/**
 * @file GEAnimation.h
 * @brief Declaración de la clase GEAnimation para sistema de animación por keyframes.
 * 
 */

#pragma once

#include <glm/glm.hpp>
#include <string>
#include <map>
#include <vector>

class GESkeleton;

/**
 * @struct Keyframe
 * @brief Representa un fotograma clave de la animación.
 */
struct Keyframe {
    float time;  ///< Tiempo del keyframe.
    std::map<std::string, glm::vec3> poses;  ///< Mapa de poses por nombre de articulación. nombre -> (angleX, angleY, angleZ)
    glm::vec3 skeletonPosition;  ///< Posición del esqueleto.
};

/**
 * @class GEAnimation
 * @brief Sistema de animación por keyframes con interpolación lineal.
 */
class GEAnimation {
private:
    std::vector<Keyframe> keyframes;
    float duration;
    float currentTime;
    bool loop;
    bool paused;

public:
    /**
     * @brief Constructor de la animación.
     * @param duration Duración de la animación en segundos.
     * @param loop Indica si la animación se repite en bucle.
     */
    GEAnimation(float duration, bool loop = true);
    
    /**
     * @brief Añade un keyframe a la animación.
     * @param time Tiempo del keyframe.
     * @param poses Mapa de poses por nombre de articulación.
     * @param skeletonPos Posición del esqueleto en el keyframe.
     */
    void addKeyframe(float time, const std::map<std::string, glm::vec3>& poses,
                     glm::vec3 skeletonPos = glm::vec3(0.0f));
    /**
     * @brief Actualiza el tiempo de la animación.
     * @param deltaTime Tiempo transcurrido desde la última actualización.
     */
    void update(float deltaTime);
    /**
     * @brief Reinicia la animación.
     */
    void reset();
    /**
     * @brief Pausa la animación.
     */
    void pause();
    /**
     * @brief Reanuda la animación.
     */
    void resume();
    /**
     * @brief Alterna pausa/reproducción.
     */
    void togglePause();
    
    /**
     * @brief Obtiene la pose interpolada para una articulación.
     * @param jointName Nombre de la articulación.
     * @return Vector con las rotaciones X, Y, Z.
     */
    glm::vec3 getPoseAt(const std::string& jointName) const;
    /**
     * @brief Obtiene la posición del esqueleto interpolada.
     * @return Posición del esqueleto.
     */
    glm::vec3 getSkeletonPosition() const;
    /**
     * @brief Aplica la animación actual al esqueleto.
     * @param skeleton Puntero al esqueleto a animar.
     */
    void applyToSkeleton(GESkeleton* skeleton);
    
    /**
     * @brief Obtiene el tiempo actual de la animación.
     * @return Tiempo actual en segundos.
     */
    float getCurrentTime() const;
    /**
     * @brief Obtiene la duración de la animación.
     * @return Duración en segundos.
     */
    float getDuration() const;
    /**
     * @brief Obtiene el índice del keyframe actual.
     * @return Índice del keyframe.
     */
    int getCurrentKeyframeIndex() const;
    /**
     * @brief Obtiene el número de keyframes.
     * @return Número de keyframes.
     */
    int getKeyframeCount() const;
    /**
     * @brief Indica si la animación está pausada.
     * @return Verdadero si está pausada.
     */
    bool isPaused() const;
    
    /**
     * @brief Avanza al siguiente keyframe.
     */
    void nextKeyframe();
    /**
     * @brief Retrocede al keyframe anterior.
     */
    void prevKeyframe();
};
