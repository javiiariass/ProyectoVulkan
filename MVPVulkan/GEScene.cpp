/**
 * @file GEScene.cpp
 * @brief Escena con animación de tiro libre de baloncesto.
 */

#include "GEScene.h"

#include "GECylinder.h"
#include "GESphere.h"
#include "GEGround.h"
#include "GETransform.h"
#include "GEMaterial.h"
#include "GELight.h"
#include <windows.h>
#include "resource.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

/**
 * @brief Crea la animación de tiro libre con salto.
 */
GEAnimation* GEScene::createBasketballThrowAnimation()
{
    GEAnimation* anim = new GEAnimation(6.0f, true);
    
    // T Pose
    /* {
        std::map<std::string, glm::vec3> poses;
        
        // Columna
        poses["neck"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["spine"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["pelvis"] = glm::vec3(0.0f, 00.0f, 0.0f);

        // Brazo derecho
        poses["clavicle_r"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["shoulder_r"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["elbow_r"] = glm::vec3(0.0f, 0.0f, 0.0f);
        poses["wrist_r"] = glm::vec3(0.0f, 0.0f, 0.0f);

        // Brazo izquierdo
        poses["clavicle_l"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["shoulder_l"] = glm::vec3(0.0f, 0.0f, 0.0f);
        poses["elbow_l"] = glm::vec3(0.0f, 0.0f, 0.0f);
        poses["wrist_l"] = glm::vec3(0.0f, 0.0f, 0.0f);

        // Pierna izquierda
        poses["knee_l"] = glm::vec3(0.0f, 0.0f, 0.0f);
        poses["leg_l"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["ankle_l"] = glm::vec3(0.0f, 0.0f, 0.0f);

        // Pierna derecha
        poses["knee_r"] = glm::vec3(0.0f, 0.0f, 0.0f);
        poses["leg_r"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["ankle_r"] = glm::vec3(0.0f, 0.0f, 0.0f);
        
        anim->addKeyframe(0.0f, poses, glm::vec3(0.0f, 1.0f, 0.0f));
    }
    /**/
    
    // Keyframe 0: Reposo
    {
        std::map<std::string, glm::vec3> poses;
        
        // Columna
        poses["neck"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["spine"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["pelvis"] = glm::vec3(0.0f, 00.0f, 0.0f);

        // Brazo derecho
        poses["clavicle_r"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["shoulder_r"] = glm::vec3(80.0f, 00.0f, 0.0f);
        poses["elbow_r"] = glm::vec3(0.0f, 0.0f, 0.0f);
        poses["wrist_r"] = glm::vec3(0.0f, 0.0f, 0.0f);

        // Brazo izquierdo
        poses["clavicle_l"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["shoulder_l"] = glm::vec3(80.0f, 0.0f, 0.0f);
        poses["elbow_l"] = glm::vec3(0.0f, 0.0f, 0.0f);
        poses["wrist_l"] = glm::vec3(0.0f, 0.0f, 0.0f);

        // Pierna izquierda
        poses["knee_l"] = glm::vec3(0.0f, 0.0f, 0.0f);
        poses["leg_l"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["ankle_l"] = glm::vec3(0.0f, 0.0f, 0.0f);

        // Pierna derecha
        poses["knee_r"] = glm::vec3(0.0f, 0.0f, 0.0f);
        poses["leg_r"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["ankle_r"] = glm::vec3(0.0f, 0.0f, 0.0f);
        
        anim->addKeyframe(0.0f, poses, glm::vec3(0.0f, 1.0f, 0.0f));
    }

    // Keyframe 1: Pelota
    {
        std::map<std::string, glm::vec3> poses;
        
        // Columna
        poses["neck"] = glm::vec3(-30.0f, 00.0f, 0.0f);
        poses["spine"] = glm::vec3(-10.0f, 00.0f, 0.0f);
        poses["pelvis"] = glm::vec3(-10.0f, 00.0f, 0.0f);

        // Brazo derecho
        poses["clavicle_r"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["shoulder_r"] = glm::vec3(80.0f, 125.0f, 0.0f);
        poses["elbow_r"] = glm::vec3(-30.0f, 0.0f, 0.0f);
        poses["wrist_r"] = glm::vec3(-30.0f, 0.0f, 90.0f);

        // Brazo izquierdo
        poses["clavicle_l"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["shoulder_l"] = glm::vec3(80.0f, -125.0f, 0.0f);
        poses["elbow_l"] = glm::vec3(-30.0f, 0.0f, 0.0f);
        poses["wrist_l"] = glm::vec3(-30.0f, 0.0f, -90.0f);

        // Pierna izquierda
        poses["knee_l"] = glm::vec3(0.0f, 0.0f, 0.0f);
        poses["leg_l"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["ankle_l"] = glm::vec3(0.0f, 0.0f, 0.0f);

        // Pierna derecha
        poses["knee_r"] = glm::vec3(0.0f, 0.0f, 0.0f);
        poses["leg_r"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["ankle_r"] = glm::vec3(0.0f, 0.0f, 0.0f);
        
        anim->addKeyframe(0.5f, poses, glm::vec3(0.0f, 1.0f, 0.0f));
    }

    // Keyframe 2: Transición
    {
        std::map<std::string, glm::vec3> poses;

        // Columna
        poses["neck"] = glm::vec3(-10.0f, 00.0f, 0.0f);
        poses["spine"] = glm::vec3(-10.0f, 00.0f, 0.0f);
        poses["pelvis"] = glm::vec3(-10.0f, 00.0f, 0.0f);

        // Brazo derecho
        poses["clavicle_r"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["shoulder_r"] = glm::vec3(70.0f, 110.0f, 0.0f);
        poses["elbow_r"] = glm::vec3(-80.0f, 0.0f, 0.0f);
        poses["wrist_r"] = glm::vec3(-30.0f, 0.0f, 90.0f);

        // Brazo izquierdo
        poses["clavicle_l"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["shoulder_l"] = glm::vec3(70.0f, -110.0f, 0.0f);
        poses["elbow_l"] = glm::vec3(-80.0f, 0.0f, 0.0f);
        poses["wrist_l"] = glm::vec3(-30.0f, 0.0f, -90.0f);

        // Pierna izquierda
        poses["knee_l"] = glm::vec3(0.0f, 0.0f, 0.0f);
        poses["leg_l"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["ankle_l"] = glm::vec3(0.0f, 0.0f, 0.0f);

        // Pierna derecha
        poses["knee_r"] = glm::vec3(0.0f, 0.0f, 0.0f);
        poses["leg_r"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["ankle_r"] = glm::vec3(0.0f, 0.0f, 0.0f);

        anim->addKeyframe(1.0f, poses, glm::vec3(0.0f, 1.0f, 0.0f));
    }

    // Keyframe 3: Flexión
    {
        std::map<std::string, glm::vec3> poses;
        
        // Columna
        poses["neck"] = glm::vec3(30.0f, 00.0f, 0.0f);
        poses["spine"] = glm::vec3(-10.0f, 00.0f, 0.0f);
        poses["pelvis"] = glm::vec3(-10.0f, 00.0f, 0.0f);

        // Brazo derecho
        poses["clavicle_r"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["shoulder_r"] = glm::vec3(40.0f, 120.0f, 0.0f);
        poses["elbow_r"] = glm::vec3(-120.0f, 0.0f, 0.0f);
        poses["wrist_r"] = glm::vec3(-70.0f, 0.0f, -20.0f);

        
        // Brazo izquierdo
        poses["clavicle_l"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["shoulder_l"] = glm::vec3(25.0f, -125.0f, 0.0f);
        poses["elbow_l"] = glm::vec3(-100.0f, 0.0f, 0.0f);
        poses["wrist_l"] = glm::vec3(-30.0f, 0.0f, -70.0f);

        // Pierna izquierda
        poses["leg_l"] = glm::vec3(-40.0f, 00.0f, 0.0f);
        poses["knee_l"] = glm::vec3(60.0f, 0.0f, 0.0f);
        poses["ankle_l"] = glm::vec3(-19.0f, 0.0f, 0.0f);

        // Pierna derecha
        poses["leg_r"] = glm::vec3(-40.0f, 00.0f, 0.0f);
        poses["knee_r"] = glm::vec3(60.0f, 0.0f, 0.0f);
        poses["ankle_r"] = glm::vec3(-19.0f, 0.0f, 0.0f);
        
        anim->addKeyframe(2.0f, poses, glm::vec3(0.0f, 0.85f, -0.19f));
    }

    // Keyframe 4: Despegue
    {
        std::map<std::string, glm::vec3> poses;

        // Columna
        poses["neck"] = glm::vec3(25.0f, 00.0f, 0.0f);
        poses["spine"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["pelvis"] = glm::vec3(0.0f, 00.0f, 0.0f);

        // Brazo derecho
        poses["clavicle_r"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["shoulder_r"] = glm::vec3(15.0f, 110.0f, 0.0f);
        poses["elbow_r"] = glm::vec3(-100.0f, 0.0f, 0.0f);
        poses["wrist_r"] = glm::vec3(-60.0f, 0.0f, -20.0f);


        // Brazo izquierdo
        poses["clavicle_l"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["shoulder_l"] = glm::vec3(0.0f, -120.0f, 0.0f);
        poses["elbow_l"] = glm::vec3(-80.0f, 0.0f, 0.0f);
        poses["wrist_l"] = glm::vec3(-30.0f, 0.0f, -70.0f);

        // Pierna izquierda
        poses["leg_l"] = glm::vec3(-20.0f, 00.0f, 0.0f);
        poses["knee_l"] = glm::vec3(40.0f, 0.0f, 0.0f);
        poses["ankle_l"] = glm::vec3(13.0f, 0.0f, 0.0f);

        // Pierna derecha
        poses["leg_r"] = glm::vec3(-20.0f, 00.0f, 0.0f);
        poses["knee_r"] = glm::vec3(40.0f, 0.0f, 0.0f);
        poses["ankle_r"] = glm::vec3(13.0f, 0.0f, 0.0f);

        anim->addKeyframe(2.5f, poses, glm::vec3(0.0f, 1.04f, 0.0f));
    }

    // Keyframe 5: aire intermedio
    {
        std::map<std::string, glm::vec3> poses;

        // Columna
        poses["neck"] = glm::vec3(25.0f, 00.0f, 0.0f);
        poses["spine"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["pelvis"] = glm::vec3(0.0f, 00.0f, 0.0f);

        // Brazo derecho
        poses["clavicle_r"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["shoulder_r"] = glm::vec3(15.0f, 110.0f, 0.0f);
        poses["elbow_r"] = glm::vec3(-100.0f, 0.0f, 0.0f);
        poses["wrist_r"] = glm::vec3(-60.0f, 0.0f, -20.0f);


        // Brazo izquierdo
        poses["clavicle_l"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["shoulder_l"] = glm::vec3(0.0f, -120.0f, 0.0f);
        poses["elbow_l"] = glm::vec3(-80.0f, 0.0f, 0.0f);
        poses["wrist_l"] = glm::vec3(-30.0f, 0.0f, -70.0f);

        // Pierna izquierda
        poses["leg_l"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["knee_l"] = glm::vec3(0.0f, 0.0f, 0.0f);
        poses["ankle_l"] = glm::vec3(50.0f, 0.0f, 0.0f);

        // Pierna derecha
        poses["leg_r"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["knee_r"] = glm::vec3(0.0f, 0.0f, 0.0f);
        poses["ankle_r"] = glm::vec3(50.0f, 0.0f, 0.0f);

        anim->addKeyframe(2.9f, poses, glm::vec3(0.0f, 1.5f, 0.0f));
    }

    // Keyframe 6: Aire
    {
        std::map<std::string, glm::vec3> poses;

        // Columna
        poses["neck"] = glm::vec3(5.0f, 00.0f, 0.0f);
        poses["spine"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["pelvis"] = glm::vec3(0.0f, 00.0f, 0.0f);

        // Brazo derecho
        poses["clavicle_r"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["shoulder_r"] = glm::vec3(-50.0f, 110.0f, 0.0f);
        poses["elbow_r"] = glm::vec3(-10.0f, 0.0f, 0.0f);
        poses["wrist_r"] = glm::vec3(10.0f, 0.0f, 0.0f);


        // Brazo izquierdo
        poses["clavicle_l"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["shoulder_l"] = glm::vec3(-35.0f, -120.0f, 0.0f);
        poses["elbow_l"] = glm::vec3(-20.0f, 0.0f, 0.0f);
        poses["wrist_l"] = glm::vec3(10.0f, 0.0f, 0.0f);

        // Pierna izquierda
        poses["leg_l"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["knee_l"] = glm::vec3(0.0f, 0.0f, 0.0f);
        poses["ankle_l"] = glm::vec3(50.0f, 0.0f, 0.0f);

        // Pierna derecha
        poses["leg_r"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["knee_r"] = glm::vec3(0.0f, 0.0f, 0.0f);
        poses["ankle_r"] = glm::vec3(50.0f, 0.0f, 0.0f);

        anim->addKeyframe(3.2f, poses, glm::vec3(0.0f, 2.0f, 0.0f));
    }


	// Keyframe 7: Aire final
    {
        std::map<std::string, glm::vec3> poses;

        // Columna
        poses["neck"] = glm::vec3(5.0f, 00.0f, 0.0f);
        poses["spine"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["pelvis"] = glm::vec3(0.0f, 00.0f, 0.0f);

        // Brazo derecho
        poses["clavicle_r"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["shoulder_r"] = glm::vec3(-35.0f, 100.0f, 0.0f);
        poses["elbow_r"] = glm::vec3(-10.0f, 0.0f, 0.0f);
        poses["wrist_r"] = glm::vec3(10.0f, 0.0f, 0.0f);


        // Brazo izquierdo
        poses["clavicle_l"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["shoulder_l"] = glm::vec3(-20.0f, -110.0f, 0.0f);
        poses["elbow_l"] = glm::vec3(-20.0f, 0.0f, 0.0f);
        poses["wrist_l"] = glm::vec3(10.0f, 0.0f, 0.0f);

        // Pierna izquierda
        poses["leg_l"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["knee_l"] = glm::vec3(0.0f, 0.0f, 0.0f);
        poses["ankle_l"] = glm::vec3(50.0f, 0.0f, 0.0f);

        // Pierna derecha
        poses["leg_r"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["knee_r"] = glm::vec3(0.0f, 0.0f, 0.0f);
        poses["ankle_r"] = glm::vec3(50.0f, 0.0f, 0.0f);

        anim->addKeyframe(3.6f, poses, glm::vec3(0.0f, 1.5f, 0.0f));
    }


    // Keyframe 8: Aterrizaje
    {
        std::map<std::string, glm::vec3> poses;

        // Columna
        poses["neck"] = glm::vec3(-10.0f, 00.0f, 0.0f);
        poses["spine"] = glm::vec3(-10.0f, 00.0f, 0.0f);
        poses["pelvis"] = glm::vec3(-10.0f, 00.0f, 0.0f);

        // Brazo derecho
        poses["clavicle_r"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["shoulder_r"] = glm::vec3(75.0f, 0.0f, 0.0f);
        poses["elbow_r"] = glm::vec3(-20.0f, 0.0f, 0.0f);
        poses["wrist_r"] = glm::vec3(20.0f, 0.0f, 0.0f);


        // Brazo izquierdo
        poses["clavicle_l"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["shoulder_l"] = glm::vec3(75.0f, 0.0f, 0.0f);
        poses["elbow_l"] = glm::vec3(-20.0f, 0.0f, 0.0f);
        poses["wrist_l"] = glm::vec3(20.0f, 0.0f, 0.0f);

        // Pierna izquierda
        poses["leg_l"] = glm::vec3(-40.0f, 00.0f, 0.0f);
        poses["knee_l"] = glm::vec3(60.0f, 0.0f, 0.0f);
        poses["ankle_l"] = glm::vec3(-19.0f, 0.0f, 0.0f);

        // Pierna derecha
        poses["leg_r"] = glm::vec3(-40.0f, 00.0f, 0.0f);
        poses["knee_r"] = glm::vec3(60.0f, 0.0f, 0.0f);
        poses["ankle_r"] = glm::vec3(-19.0f, 0.0f, 0.0f);

        anim->addKeyframe(4.0f, poses, glm::vec3(0.0f, 0.85f, -0.19f));
    }

    // Keyframe 9: Reposo
    {
        std::map<std::string, glm::vec3> poses;
        
        // Columna
        poses["neck"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["spine"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["pelvis"] = glm::vec3(0.0f, 00.0f, 0.0f);

        // Brazo derecho
        poses["clavicle_r"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["shoulder_r"] = glm::vec3(80.0f, 00.0f, 0.0f);
        poses["elbow_r"] = glm::vec3(0.0f, 0.0f, 0.0f);
        poses["wrist_r"] = glm::vec3(0.0f, 0.0f, 0.0f);

        // Brazo izquierdo
        poses["clavicle_l"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["shoulder_l"] = glm::vec3(80.0f, 0.0f, 0.0f);
        poses["elbow_l"] = glm::vec3(0.0f, 0.0f, 0.0f);
        poses["wrist_l"] = glm::vec3(0.0f, 0.0f, 0.0f);

        // Pierna izquierda
        poses["knee_l"] = glm::vec3(0.0f, 0.0f, 0.0f);
        poses["leg_l"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["ankle_l"] = glm::vec3(0.0f, 0.0f, 0.0f);

        // Pierna derecha
        poses["knee_r"] = glm::vec3(0.0f, 0.0f, 0.0f);
        poses["leg_r"] = glm::vec3(0.0f, 00.0f, 0.0f);
        poses["ankle_r"] = glm::vec3(0.0f, 0.0f, 0.0f);
        
        anim->addKeyframe(5.0f, poses, glm::vec3(0.0f, 1.0f, 0.0f));
    }
 
    return anim;
}

/**
 * @brief Crea la escena.
 */
GEScene::GEScene(GEGraphicsContext* gc, GEDrawingContext* dc, GECommandContext* cc)
{
    VkExtent2D extent = dc->getExtent();
    double aspect = (double)extent.width / (double)extent.height;
    aspect_ratio(aspect);

    GEPipelineConfig* config = createPipelineConfig(dc->getExtent());
    rc = new GERenderingContext(gc, dc, config);

    this->camera = new GECamera();

    // Ubicamos la camara detras del esqueleto
    // this->camera->setPosition(glm::vec3(0.0f, 1.5f, -5.0f));
    this->camera->setPosition(glm::vec3(6.0f, 1.5f, -4.0f));
    this->camera->setDirection(glm::vec3(1.2f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    // Camara apuntando hacia el esqueleto
    // this->camera->setDirection(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    this->camera->setMoveStep(0.0f);

    
    GELight light = {};
    light.Ldir = glm::normalize(glm::vec3(1.0f, -0.8f, -0.7f));
    light.La = glm::vec3(0.2f, 0.2f, 0.2f);
    light.Ld = glm::vec3(0.8f, 0.8f, 0.8f);
    light.Ls = glm::vec3(1.0f, 1.0f, 1.0f);

    GEMaterial groundMat = {};
    groundMat.Ka = glm::vec3(0.0f, 0.3f, 0.0f);
    groundMat.Kd = glm::vec3(0.0f, 0.3f, 0.0f);
    groundMat.Ks = glm::vec3(0.8f, 0.8f, 0.8f);
    groundMat.Shininess = 16.0f;

    ground = new GEGround(5.0f, 5.0f);
    ground->initialize(gc, rc);
    ground->setLight(light);
    ground->setMaterial(groundMat);

    // Crear esqueleto
    skeleton = new GESkeleton();
    skeleton->setPosition(glm::vec3(0.0f, 1.0f, 0.0f));
    skeleton->initialize(gc, rc);
    skeleton->setLight(light);
    
    // Crear animación
    animation = createBasketballThrowAnimation();
    
    lastTime = glfwGetTime();

    fillCommandBuffers(cc->commandBuffers);
}

/**
 * @brief Destruye los componentes gráficos de la escena.
 * @param gc Contexto gráfico.
 */
void GEScene::destroy(GEGraphicsContext* gc)
{
    rc->destroy(gc);
    delete rc;

    ground->destroy(gc);
    delete ground;
    
    skeleton->destroy(gc);
    delete skeleton;
    
    delete animation;
}

/**
 * @brief Reconstruye los componentes gráficos de la escena.
 * @param gc Contexto gráfico.
 * @param dc Contexto de dibujo.
 * @param cc Contexto de comandos.
 */
void GEScene::recreate(GEGraphicsContext* gc, GEDrawingContext* dc, GECommandContext* cc)
{
    rc->destroy(gc);
    GEPipelineConfig* config = createPipelineConfig(dc->getExtent());
    this->rc = new GERenderingContext(gc, dc, config);
    fillCommandBuffers(cc->commandBuffers);
}

/**
 * @brief Actualiza la información para generar la imagen.
 * @param gc Contexto gráfico.
 * @param index Índice de la imagen a renderizar.
 */
void GEScene::update(GEGraphicsContext* gc, uint32_t index)
{
    camera->update();
    glm::mat4 view = camera->getViewMatrix();

    // Calcular deltaTime
    double currentTime = glfwGetTime();
    float deltaTime = (float)(currentTime - lastTime);
    lastTime = currentTime;
    
    // Actualizar animación
    animation->update(deltaTime);
    animation->applyToSkeleton(skeleton);

    ground->update(gc, index, view, projection);
    skeleton->update(gc, index, view, projection);
}

/**
 * @brief Respuesta a acciones de teclado.
 * @param key Código de la tecla (GLFW_KEY_*).
 * @param pressed true si la tecla está pulsada.
 */
void GEScene::key_action(int key, bool pressed)
{
    switch (key)
    {
    case GLFW_KEY_UP:
        camera->setTurnDown(pressed);
        break;
    case GLFW_KEY_DOWN:
        camera->setTurnUp(pressed);
        break;
    case GLFW_KEY_LEFT:
        camera->setTurnCCW(pressed);
        break;
    case GLFW_KEY_RIGHT:
        camera->setTurnCW(pressed);
        break;
    case GLFW_KEY_S:
        camera->setMoveStep(0.0f);
        break;
    case GLFW_KEY_KP_ADD:
    case GLFW_KEY_1:
        camera->setMoveStep(camera->getMoveStep() + 0.1f);
        break;
    case GLFW_KEY_KP_SUBTRACT:
    case GLFW_KEY_2:
        camera->setMoveStep(camera->getMoveStep() - 0.1f);
        break;
    case GLFW_KEY_Q:
        camera->setMoveUp(pressed);
        break;
    case GLFW_KEY_A:
        camera->setMoveDown(pressed);
        break;
    case GLFW_KEY_O:
        camera->setMoveLeft(pressed);
        break;
    case GLFW_KEY_P:
        camera->setMoveRight(pressed);
        break;
    case GLFW_KEY_K:
        camera->setTurnLeft(pressed);
        break;
    case GLFW_KEY_L:
        camera->setTurnRight(pressed);
        break;
        
    // Controles de animación
    case GLFW_KEY_SPACE:
        if (pressed) {
            animation->togglePause();
            std::cout << (animation->isPaused() ? "Pausado" : "Reproduciendo") << std::endl;
        }
        break;
    case GLFW_KEY_R:
        if (pressed) {
            animation->reset();
            std::cout << "Animacion reiniciada" << std::endl;
        }
        break;
    case GLFW_KEY_M:
        if (pressed) {
            animation->nextKeyframe();
            std::cout << "Keyframe " << animation->getCurrentKeyframeIndex() 
                      << " / " << animation->getKeyframeCount() - 1 << std::endl;
        }
        break;
    case GLFW_KEY_N:
        if (pressed) {
            animation->prevKeyframe();
            std::cout << "Keyframe " << animation->getCurrentKeyframeIndex() 
                      << " / " << animation->getKeyframeCount() - 1 << std::endl;
        }
        break;
    }
}

/**
 * @brief Modifica la relación anchura/altura del modelo.
 * @param aspect Relación anchura/altura.
 */
void GEScene::aspect_ratio(double aspect)
{
    constexpr double fov = glm::radians(30.0f);
    double sin_fov = sin(fov);
    double cos_fov = cos(fov);
    float wHeight = (float)(sin_fov * 0.2 / cos_fov);
    float wWidth = (float)(wHeight * aspect);

    projection = glm::perspective((float)fov, (float)aspect, 0.2f, 400.0f);
    projection[1][1] *= -1.0f;
}

/**
 * @brief Obtiene la configuración del pipeline de renderizado.
 * @param extent Extensión de la imagen.
 * @return Configuración del pipeline creada.
 */
GEPipelineConfig* GEScene::createPipelineConfig(VkExtent2D extent)
{
    GEPipelineConfig* config = new GEPipelineConfig();
    config->vertex_shader = IDR_HTML1;
    config->fragment_shader = IDR_HTML2;

    config->attrStride = sizeof(GEVertex);
    config->attrOffsets.resize(2);
    config->attrOffsets[0] = offsetof(GEVertex, pos);
    config->attrOffsets[1] = offsetof(GEVertex, norm);
    config->attrFormats.resize(2);
    config->attrFormats[0] = VK_FORMAT_R32G32B32_SFLOAT;
    config->attrFormats[1] = VK_FORMAT_R32G32B32_SFLOAT;

    config->descriptorTypes.resize(3);
    config->descriptorTypes[0] = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    config->descriptorTypes[1] = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    config->descriptorTypes[2] = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    config->descriptorStages.resize(3);
    config->descriptorStages[0] = VK_SHADER_STAGE_ALL_GRAPHICS;
    config->descriptorStages[1] = VK_SHADER_STAGE_FRAGMENT_BIT;
    config->descriptorStages[2] = VK_SHADER_STAGE_FRAGMENT_BIT;

    config->depthTestEnable = VK_TRUE;
    config->cullMode = VK_CULL_MODE_BACK_BIT;
    config->extent = extent;

    return config;
}

/**
 * @brief Rellena los buffers de comandos.
 * @param commandBuffers Buffers de comandos a rellenar.
 */
void GEScene::fillCommandBuffers(std::vector<VkCommandBuffer> commandBuffers)
{
    rc->startFillingCommandBuffers(commandBuffers);
    for (size_t i = 0; i < commandBuffers.size(); i++)
    {
        ground->addCommands(commandBuffers[i], rc->pipelineLayout, (int)i);
        skeleton->addCommands(commandBuffers[i], rc->pipelineLayout, (int)i);
    }
    rc->endFillingCommandBuffers(commandBuffers);
}