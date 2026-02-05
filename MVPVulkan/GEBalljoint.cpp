/**
 * @file GEBalljoint.cpp
 * @brief Implementación de la clase GEBalljoint con soporte jerárquico.
 */

#include "GEBalljoint.h"
#include "GEMaterial.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

/**
 * @brief Construye una articulación.
 * @param l Longitud del hueso.
 */
GEBalljoint::GEBalljoint(float l)
{
    length = l;
    name = "";

    location = glm::vec3(0.0f, 0.0f, 0.0f);
    offset = glm::vec3(0.0f, 0.0f, 0.0f);
    dir = glm::vec3(0.0f, 0.0f, 1.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    right = glm::vec3(1.0f, 0.0f, 0.0f);

    localZAxis = glm::vec3(0.0f, 0.0f, 1.0f);
    localYAxis = glm::vec3(0.0f, 1.0f, 0.0f);

    angles[0] = 0.0f;
    angles[1] = 0.0f;
    angles[2] = 0.0f;

    joint = nullptr;
    bone = nullptr;

    worldMatrix = glm::mat4(1.0f);

    limits.enabled = false;

    // TEST
    // Si macro definida en main, mostrar si algún valor en las articulaciones alcanza límite
#ifdef DEBUG
    limits.wasLimited = false;
#endif

    limits.min = glm::vec3(-180.0f);
    limits.max = glm::vec3(180.0f);
}

/**
 * @brief Constructor jerárquico para esqueletos.
 * @param name Nombre de la articulación.
 * @param length Longitud del hueso.
 * @param offset Desplazamiento local.
 * @param zAxis Eje Z local.
 * @param yAxis Eje Y local.
 */
GEBalljoint::GEBalljoint(const std::string &name, float length,
                         glm::vec3 offset, glm::vec3 zAxis, glm::vec3 yAxis)
{
    this->name = name;
    this->length = length;
    this->offset = offset;
    this->localZAxis = zAxis;
    this->localYAxis = yAxis;

    glm::vec3 xAxis = glm::cross(yAxis, zAxis);
    this->dir = zAxis;
    this->up = yAxis;
    this->right = xAxis;
    this->location = glm::vec3(0.0f);

    angles[0] = 0.0f;
    angles[1] = 0.0f;
    angles[2] = 0.0f;

    joint = nullptr;
    bone = nullptr;
    worldMatrix = glm::mat4(1.0f);

    limits.enabled = false;

    // TEST
    // Si macro definida en main, mostrar si algún valor en las articulaciones alcanza límite
#ifdef DEBUG
    limits.wasLimited = false;
#endif

    limits.min = glm::vec3(-180.0f);
    limits.max = glm::vec3(180.0f);
}

/**
 * @brief Calcula la matriz de transformación.
 */
void GEBalljoint::ComputeMatrix()
{
    glm::mat4 jointm;
    jointm[0][0] = right.x;
    jointm[0][1] = right.y;
    jointm[0][2] = right.z;
    jointm[0][3] = 0.0;

    jointm[1][0] = up.x;
    jointm[1][1] = up.y;
    jointm[1][2] = up.z;
    jointm[1][3] = 0.0;

    jointm[2][0] = dir.x;
    jointm[2][1] = dir.y;
    jointm[2][2] = dir.z;
    jointm[2][3] = 0.0;

    jointm[3][0] = location.x;
    jointm[3][1] = location.y;
    jointm[3][2] = location.z;
    jointm[3][3] = 1.0;

    float cx = cos(glm::radians(angles[0]));
    float sx = sin(glm::radians(angles[0]));
    float cy = cos(glm::radians(angles[1]));
    float sy = sin(glm::radians(angles[1]));
    float cz = cos(glm::radians(angles[2]));
    float sz = sin(glm::radians(angles[2]));

    glm::mat4 posem;
    posem[0][0] = cz * cy;
    posem[1][0] = -sz * cx + cz * sy * sx;
    posem[2][0] = sz * sx + cz * sy * cx;
    posem[3][0] = 0;

    posem[0][1] = sz * cy;
    posem[1][1] = cz * cx + sz * sy * sx;
    posem[2][1] = -cz * sx + sz * sy * cx;
    posem[3][1] = 0;

    posem[0][2] = -sy;
    posem[1][2] = cy * sx;
    posem[2][2] = cy * cx;
    posem[3][2] = 0;

    posem[0][3] = 0;
    posem[1][3] = 0;
    posem[2][3] = 0;
    posem[3][3] = 1;

    worldMatrix = jointm * posem;

    if (joint && bone)
    {
        joint->setLocation(worldMatrix);
        glm::mat4 mm = glm::translate(worldMatrix, glm::vec3(0.0f, 0.0f, length / 2));
        bone->setLocation(mm);
    }
}

/**
 * @brief Calcula la matriz de transformación considerando la matriz del padre.
 */
void GEBalljoint::ComputeMatrix(glm::mat4 parentMatrix)
{
    // Matriz de orientación local
    glm::vec3 xAxis = glm::cross(localYAxis, localZAxis);

    glm::mat4 orientationMatrix;
    orientationMatrix[0] = glm::vec4(xAxis, 0.0f);
    orientationMatrix[1] = glm::vec4(localYAxis, 0.0f);
    orientationMatrix[2] = glm::vec4(localZAxis, 0.0f);
    orientationMatrix[3] = glm::vec4(offset, 1.0f);

    // Matriz de pose (rotaciones Euler ZYX)
    float cx = cos(glm::radians(angles[0]));
    float sx = sin(glm::radians(angles[0]));
    float cy = cos(glm::radians(angles[1]));
    float sy = sin(glm::radians(angles[1]));
    float cz = cos(glm::radians(angles[2]));
    float sz = sin(glm::radians(angles[2]));

    glm::mat4 poseMatrix;
    poseMatrix[0][0] = cz * cy;
    poseMatrix[1][0] = -sz * cx + cz * sy * sx;
    poseMatrix[2][0] = sz * sx + cz * sy * cx;
    poseMatrix[3][0] = 0;

    poseMatrix[0][1] = sz * cy;
    poseMatrix[1][1] = cz * cx + sz * sy * sx;
    poseMatrix[2][1] = -cz * sx + sz * sy * cx;
    poseMatrix[3][1] = 0;

    poseMatrix[0][2] = -sy;
    poseMatrix[1][2] = cy * sx;
    poseMatrix[2][2] = cy * cx;
    poseMatrix[3][2] = 0;

    poseMatrix[0][3] = 0;
    poseMatrix[1][3] = 0;
    poseMatrix[2][3] = 0;
    poseMatrix[3][3] = 1;

    worldMatrix = parentMatrix * orientationMatrix * poseMatrix;

    if (joint && bone)
    {
        joint->setLocation(worldMatrix);
        glm::mat4 boneMatrix = glm::translate(worldMatrix, glm::vec3(0.0f, 0.0f, length / 2));
        bone->setLocation(boneMatrix);
    }
}

/**
 * @brief Inicializa las piezas de la articulación.
 * @param gc Contexto gráfico.
 * @param rc Contexto de renderizado.
 */
void GEBalljoint::initialize(GEGraphicsContext *gc, GERenderingContext *rc)
{
    GEMaterial jointMat = {};
    jointMat.Ka = glm::vec3(1.0f, 0.0f, 0.0f);
    jointMat.Kd = glm::vec3(1.0f, 0.0f, 0.0f);
    jointMat.Ks = glm::vec3(0.8f, 0.8f, 0.8f);
    jointMat.Shininess = 16.0f;

    joint = new GESphere(10, 20, 0.05f);
    joint->initialize(gc, rc);
    joint->setMaterial(jointMat);

    GEMaterial boneMat = {};
    boneMat.Ka = glm::vec3(0.0f, 0.0f, 0.8f);
    boneMat.Kd = glm::vec3(0.0f, 0.0f, 0.8f);
    boneMat.Ks = glm::vec3(0.8f, 0.8f, 0.8f);
    boneMat.Shininess = 16.0f;

    bone = new GECylinder(2, 10, 0.03f, length / 2);
    bone->initialize(gc, rc);
    bone->setMaterial(boneMat);

    ComputeMatrix();
}

/**
 * @brief Inicializa recursivamente esta articulación y sus hijas.
 * @param gc Contexto gráfico.
 * @param rc Contexto de renderizado.
 */
void GEBalljoint::initializeRecursive(GEGraphicsContext *gc, GERenderingContext *rc)
{
    initialize(gc, rc);
    for (GEBalljoint *child : children)
    {
        child->initializeRecursive(gc, rc);
    }
}

/**
 * @brief Actualiza las variables uniformes.
 * @param gc Contexto gráfico.
 * @param index Índice de la imagen.
 * @param view Matriz de vista.
 * @param projection Matriz de proyección.
 */
void GEBalljoint::update(GEGraphicsContext *gc, uint32_t index, glm::mat4 view, glm::mat4 projection)
{
    if (joint && bone)
    {
        joint->update(gc, index, view, projection);
        bone->update(gc, index, view, projection);
    }
}

/**
 * @brief Actualiza recursivamente con matriz del padre.
 */
void GEBalljoint::updateRecursive(GEGraphicsContext *gc, uint32_t index,
                                  glm::mat4 parentMatrix, glm::mat4 view, glm::mat4 projection)
{
    ComputeMatrix(parentMatrix);
    update(gc, index, view, projection);

    glm::mat4 childBaseMatrix = getBoneEndMatrix();
    for (GEBalljoint *child : children)
    {
        child->updateRecursive(gc, index, childBaseMatrix, view, projection);
    }
}

/**
 * @brief Destruye los buffers de las piezas.
 * @param gc Contexto gráfico.
 */
void GEBalljoint::destroy(GEGraphicsContext *gc)
{
    if (joint)
    {
        joint->destroy(gc);
        delete joint;
        joint = nullptr;
    }
    if (bone)
    {
        bone->destroy(gc);
        delete bone;
        bone = nullptr;
    }
}

/**
 * @brief Destruye recursivamente esta articulación y sus hijas.
 */
void GEBalljoint::destroyRecursive(GEGraphicsContext *gc)
{
    for (GEBalljoint *child : children)
    {
        child->destroyRecursive(gc);
        delete child;
    }
    children.clear();
    destroy(gc);
}

/**
 * @brief Asigna la posición de la articulación.
 * @param loc Posición.
 */
void GEBalljoint::setLocation(glm::vec3 loc)
{
    location = loc;
    ComputeMatrix();
}

/**
 * @brief Asigna la orientación de la articulación.
 * @param nDir Dirección.
 * @param nUp Vector arriba.
 */
void GEBalljoint::setOrientation(glm::vec3 nDir, glm::vec3 nUp)
{
    dir = nDir;
    up = nUp;
    right = glm::cross(up, dir);
    ComputeMatrix();
}

/**
 * @brief Asigna la rotación de la articulación (respetando límites).
 * @param xrot Rotación en X.
 * @param yrot Rotación en Y.
 * @param zrot Rotación en Z.
 */
void GEBalljoint::setPose(float xrot, float yrot, float zrot)
{
    // Uso de glm::clamp para habilitar límites
    if (limits.enabled)
    {
        angles[0] = glm::clamp(xrot, limits.min.x, limits.max.x);
        angles[1] = glm::clamp(yrot, limits.min.y, limits.max.y);
        angles[2] = glm::clamp(zrot, limits.min.z, limits.max.z);

        // TEST
        // Si macro definida en main, mostrar si algún valor en las articulaciones alcanza límite
#ifdef DEBUG

        // Debug: detectar si se ha alcanzado un límite (solo muestra una vez por cambio de estado)
        bool isLimited = (xrot != angles[0] || yrot != angles[1] || zrot != angles[2]);

        if (isLimited && !limits.wasLimited)
        {
            std::cout << "[Limit alcanzado] " << name << ": ";
            if (xrot != angles[0])
                std::cout << "X(" << xrot << "->" << angles[0] << ") ";
            if (yrot != angles[1])
                std::cout << "Y(" << yrot << "->" << angles[1] << ") ";
            if (zrot != angles[2])
                std::cout << "Z(" << zrot << "->" << angles[2] << ") ";
            std::cout << std::endl;
        }
        limits.wasLimited = isLimited;
#endif

    }
    else
    {
        angles[0] = xrot;
        angles[1] = yrot;
        angles[2] = zrot;
    }
}

/**
 * @brief Asigna los límites de rotación.
 */
void GEBalljoint::setLimits(glm::vec3 min, glm::vec3 max)
{
    limits.min = min;
    limits.max = max;
    limits.enabled = true;
}

/**
 * @brief Añade los comandos de dibujo.
 */
void GEBalljoint::addCommands(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, int index)
{
    if (joint && bone)
    {
        joint->addCommands(commandBuffer, pipelineLayout, index);
        bone->addCommands(commandBuffer, pipelineLayout, index);
    }
}

/**
 * @brief Añade comandos recursivamente.
 */
void GEBalljoint::addCommandsRecursive(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, int index)
{
    addCommands(commandBuffer, pipelineLayout, index);
    for (GEBalljoint *child : children)
    {
        child->addCommandsRecursive(commandBuffer, pipelineLayout, index);
    }
}

/**
 * @brief Asigna las propiedades de la luz.
 */
void GEBalljoint::setLight(GELight l)
{
    if (joint && bone)
    {
        joint->setLight(l);
        bone->setLight(l);
    }
}

/**
 * @brief Asigna la luz recursivamente.
 */
void GEBalljoint::setLightRecursive(GELight l)
{
    setLight(l);
    for (GEBalljoint *child : children)
    {
        child->setLightRecursive(l);
    }
}

/**
 * @brief Añade una articulación hija.
 */
void GEBalljoint::addChild(GEBalljoint *child)
{
    children.push_back(child);
}

/**
 * @brief Busca una articulación hija por nombre.
 * @param searchName Nombre a buscar.
 * @return Puntero a la articulación encontrada o nullptr.
 */
GEBalljoint *GEBalljoint::findChild(const std::string &searchName)
{
    if (name == searchName)
    {
        return this;
    }
    for (GEBalljoint *child : children)
    {
        GEBalljoint *found = child->findChild(searchName);
        if (found != nullptr)
        {
            return found;
        }
    }
    return nullptr;
}

/**
 * @brief Obtiene el nombre de la articulación.
 * @return Nombre de la articulación.
 */
const std::string &GEBalljoint::getName() const
{
    return name;
}

/**
 * @brief Obtiene la lista de hijos.
 * @return Vector de punteros a hijos.
 */
const std::vector<GEBalljoint *> &GEBalljoint::getChildren() const
{
    return children;
}

/**
 * @brief Obtiene la matriz mundo.
 * @return Matriz de transformación mundo.
 */
glm::mat4 GEBalljoint::getWorldMatrix() const
{
    return worldMatrix;
}

/**
 * @brief Obtiene la matriz en el extremo del hueso.
 * @return Matriz en el extremo del hueso.
 */
glm::mat4 GEBalljoint::getBoneEndMatrix() const
{
    return glm::translate(worldMatrix, glm::vec3(0.0f, 0.0f, length));
}
