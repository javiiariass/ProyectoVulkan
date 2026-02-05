/**
 * @file GEAnimation.cpp
 * @brief Implementación del sistema de animación por keyframes.
 */

#include "GEAnimation.h"
#include "GESkeleton.h"
#include "GEBalljoint.h"

/**
 * @brief Constructor de la animación.
 */
GEAnimation::GEAnimation(float duration, bool loop)
    : duration(duration), loop(loop), currentTime(0.0f), paused(false)
{
}

/**
 * @brief Añade un keyframe a la animación.
 * @param time Tiempo del keyframe.
 * @param poses Mapa de poses por nombre de articulación.
 * @param skeletonPos Posición del esqueleto en el keyframe para el espacio 3D.
 */
void GEAnimation::addKeyframe(float time, const std::map<std::string, glm::vec3>& poses,
                               glm::vec3 skeletonPos)
{
    Keyframe kf;
    kf.time = time;
    kf.poses = poses;
    kf.skeletonPosition = skeletonPos;
    
    // Insertar ordenado por tiempo
    auto it = keyframes.begin();
    while (it != keyframes.end() && it->time < time) {
        ++it;
    }
    keyframes.insert(it, kf);
}

/**
 * @brief Actualiza el tiempo de la animación.
 * @param deltaTime Tiempo transcurrido desde la última actualización.
 */
void GEAnimation::update(float deltaTime)
{
    if (paused || keyframes.empty()) return;
    
    currentTime += deltaTime;
    
    if (currentTime >= duration) {
        if (loop) {
            currentTime = fmod(currentTime, duration);
        } else {
            currentTime = duration;
            paused = true;
        }
    }
}

/**
 * @brief Reinicia la animación.
 */
void GEAnimation::reset()
{
    currentTime = 0.0f;
    paused = false;
}

/**
 * @brief Pausa la animación.
 */
void GEAnimation::pause()
{
    paused = true;
}

/**
 * @brief Reanuda la animación.
 */
void GEAnimation::resume()
{
    paused = false;
}

/**
 * @brief Alterna pausa/reproducción.
 */
void GEAnimation::togglePause()
{
    paused = !paused;
}

/**
 * @brief Obtiene la pose interpolada para una articulación.
 * @param jointName Nombre de la articulación.
 * @return Vector con las rotaciones X, Y, Z.
 */
glm::vec3 GEAnimation::getPoseAt(const std::string& jointName) const
{
    if (keyframes.empty()) return glm::vec3(0.0f);
    
    // Encontrar keyframes anterior y siguiente
    const Keyframe* prev = &keyframes[0];
    const Keyframe* next = &keyframes[0];
    
    for (size_t i = 0; i < keyframes.size(); i++) {
        if (keyframes[i].time <= currentTime) {
            prev = &keyframes[i];
        }
        if (keyframes[i].time >= currentTime) {
            next = &keyframes[i];
            break;
        }
    }
    
    // Obtener poses
    glm::vec3 prevPose(0.0f);
    glm::vec3 nextPose(0.0f);
    
    auto it = prev->poses.find(jointName);
    if (it != prev->poses.end()) {
        prevPose = it->second;
    }
    
    it = next->poses.find(jointName);
    if (it != next->poses.end()) {
        nextPose = it->second;
    }
    
    // Interpolar
    if (prev == next || prev->time == next->time) {
        return prevPose;
    }
    
    float t = (currentTime - prev->time) / (next->time - prev->time);
    return glm::mix(prevPose, nextPose, t);
}

/**
 * @brief Obtiene la posición del esqueleto interpolada (para salto).
 * @return Posición del esqueleto.
 */
glm::vec3 GEAnimation::getSkeletonPosition() const
{
    if (keyframes.empty()) return glm::vec3(0.0f);
    
    const Keyframe* prev = &keyframes[0];
    const Keyframe* next = &keyframes[0];
    
    for (size_t i = 0; i < keyframes.size(); i++) {
        if (keyframes[i].time <= currentTime) {
            prev = &keyframes[i];
        }
        if (keyframes[i].time >= currentTime) {
            next = &keyframes[i];
            break;
        }
    }
    
    if (prev == next || prev->time == next->time) {
        return prev->skeletonPosition;
    }
    
    float t = (currentTime - prev->time) / (next->time - prev->time);
    return glm::mix(prev->skeletonPosition, next->skeletonPosition, t);
}

/**
 * @brief Aplica la animación actual al esqueleto.
 * @param skeleton Puntero al esqueleto a animar.
 */
void GEAnimation::applyToSkeleton(GESkeleton* skeleton)
{
    if (!skeleton) return;
    
    // Aplicar posición del esqueleto (para salto)
    skeleton->setPosition(getSkeletonPosition());
    
    // Lista de articulaciones a animar
    const char* jointNames[] = {
        "pelvis", "spine", "neck",
        "clavicle_l", "shoulder_l", "elbow_l", "wrist_l",
        "clavicle_r", "shoulder_r", "elbow_r", "wrist_r",
        "hip_l", "leg_l", "knee_l", "ankle_l",
        "hip_r", "leg_r", "knee_r", "ankle_r"
    };
    
    for (const char* name : jointNames) {
        GEBalljoint* joint = skeleton->findJoint(name);
        if (joint) {
            glm::vec3 pose = getPoseAt(name);
            joint->setPose(pose.x, pose.y, pose.z);
        }
    }
}

/**
 * @brief Obtiene el tiempo actual.
 * @return Tiempo actual en segundos.
 */
float GEAnimation::getCurrentTime() const
{
    return currentTime;
}

/**
 * @brief Obtiene la duración.
 * @return Duración en segundos.
 */
float GEAnimation::getDuration() const
{
    return duration;
}

/**
 * @brief Obtiene el índice del keyframe actual.
 * @return Índice del keyframe.
 */
int GEAnimation::getCurrentKeyframeIndex() const
{
    for (size_t i = 0; i < keyframes.size(); i++) {
        if (keyframes[i].time >= currentTime) {
            return (int)i;
        }
    }
    return (int)keyframes.size() - 1;
}

/**
 * @brief Obtiene el número de keyframes.
 * @return Número de keyframes.
 */
int GEAnimation::getKeyframeCount() const
{
    return (int)keyframes.size();
}

/**
 * @brief Indica si está pausado.
 * @return Verdadero si está pausado.
 */
bool GEAnimation::isPaused() const
{
    return paused;
}

/**
 * @brief Avanza al siguiente keyframe.
 */
void GEAnimation::nextKeyframe()
{
    if (keyframes.empty()) return;
    
    for (size_t i = 0; i < keyframes.size(); i++) {
        if (keyframes[i].time > currentTime + 0.01f) {
            currentTime = keyframes[i].time;
            return;
        }
    }
    currentTime = keyframes[0].time;
}

/**
 * @brief Retrocede al keyframe anterior.
 */
void GEAnimation::prevKeyframe()
{
    if (keyframes.empty()) return;
    
    for (int i = (int)keyframes.size() - 1; i >= 0; i--) {
        if (keyframes[i].time < currentTime - 0.01f) {
            currentTime = keyframes[i].time;
            return;
        }
    }
    currentTime = keyframes.back().time;
}
