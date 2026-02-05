/**
 * @file GESkeleton.cpp
 * @brief Implementación de GESkeleton con carga desde archivo .skel.
 */

#include "GESkeleton.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

/**
 * @brief Constructor del esqueleto.
 */
GESkeleton::GESkeleton()
{
    name = "body";
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    zAxis = glm::vec3(0.0f, 0.0f, 1.0f);
    yAxis = glm::vec3(0.0f, 1.0f, 0.0f);
    
    buildSkeleton();
}

/**
 * @brief Destructor.
 */
GESkeleton::~GESkeleton()
{
    // La destrucción de joints se hace en destroy()
}

/**
 * @brief Crea recursivamente las articulaciones desde los datos parseados.
 * @param data Datos de la articulación.
 * @return Puntero a la articulación creada.
 */
GEBalljoint* GESkeleton::createJointFromData(const GEJointData& data)
{
    GEBalljoint* joint = new GEBalljoint(data.name, data.length, 
                                          data.offset, data.zAxis, data.yAxis);
    
    // Aplicar límites si están definidos
    if (data.hasLimits) {
        joint->setLimits(data.limitsMin, data.limitsMax);
    }
    
    // Crear hijos recursivamente
    for (const GEJointData& childData : data.children) {
        GEBalljoint* child = createJointFromData(childData);
        joint->addChild(child);
    }
    
    return joint;
}

/**
 * @brief Construye el árbol de articulaciones desde body.skel.
 */
void GESkeleton::buildSkeleton()
{
    GESkeletonData skelData;
    
    // Intentar cargar desde archivo
    // if (GEXMLParser::parseSkeletonFile("body.skel", skelData)) {
    if (GEXMLParser::parseSkeletonFile("bodyLimit.skel", skelData)) {
        name = skelData.name;
        zAxis = skelData.zAxis;
        yAxis = skelData.yAxis;
        position = skelData.offset;
        
        // Crear todas las articulaciones raíz
        for (const GEJointData& jointData : skelData.rootJoints) {
            GEBalljoint* rootJoint = createJointFromData(jointData);
            rootJoints.push_back(rootJoint);
        }
        
        std::cout << "Esqueleto cargado desde body.skel con " 
                  << rootJoints.size() << " articulaciones raiz." << std::endl;
    } else {
        std::cerr << "Error: No se pudo cargar body.skel" << std::endl;
    }
}

/**
 * @brief Inicializa el esqueleto.
 * @param gc Contexto gráfico.
 * @param rc Contexto de renderizado.
 */
void GESkeleton::initialize(GEGraphicsContext* gc, GERenderingContext* rc)
{
    for (GEBalljoint* root : rootJoints) {
        root->initializeRecursive(gc, rc);
    }
}

/**
 * @brief Destruye el esqueleto.
 * @param gc Contexto gráfico.
 */
void GESkeleton::destroy(GEGraphicsContext* gc)
{
    for (GEBalljoint* root : rootJoints) {
        root->destroyRecursive(gc);
        delete root;
    }
    rootJoints.clear();
}

/**
 * @brief Actualiza el esqueleto.
 */
void GESkeleton::update(GEGraphicsContext* gc, uint32_t index, glm::mat4 view, glm::mat4 projection)
{
    // Matriz base: traslación + orientación del esqueleto
    glm::mat4 baseMatrix = glm::translate(glm::mat4(1.0f), position);
    
    for (GEBalljoint* root : rootJoints) {
        root->updateRecursive(gc, index, baseMatrix, view, projection);
    }
}

/**
 * @brief Añade comandos de dibujo.
 * @param commandBuffer Buffer de comandos Vulkan.
 * @param pipelineLayout Layout del pipeline.
 * @param index Índice de la imagen.
 */
void GESkeleton::addCommands(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, int index)
{
    for (GEBalljoint* root : rootJoints) {
        root->addCommandsRecursive(commandBuffer, pipelineLayout, index);
    }
}

/**
 * @brief Asigna la luz al esqueleto.
 * @param light Parámetros de la luz.
 */
void GESkeleton::setLight(GELight light)
{
    for (GEBalljoint* root : rootJoints) {
        root->setLightRecursive(light);
    }
}

/**
 * @brief Busca una articulación por nombre.
 * @param jointName Nombre de la articulación a buscar.
 * @return Puntero a la articulación o nullptr si no se encuentra.
 */
GEBalljoint* GESkeleton::findJoint(const std::string& jointName)
{
    for (GEBalljoint* root : rootJoints) {
        GEBalljoint* found = root->findChild(jointName);
        if (found != nullptr) {
            return found;
        }
    }
    return nullptr;
}

/**
 * @brief Obtiene la primera articulación raíz (pelvis).
 * @return Puntero a la articulación raíz.
 */
GEBalljoint* GESkeleton::getRoot() const
{
    return rootJoints.empty() ? nullptr : rootJoints[0];
}

/**
 * @brief Obtiene todas las articulaciones raíz.
 * @return Vector de punteros a las articulaciones raíz.
 */
const std::vector<GEBalljoint*>& GESkeleton::getRootJoints() const
{
    return rootJoints;
}

/**
 * @brief Asigna la posición del esqueleto.
 * @param pos Nueva posición.
 */
void GESkeleton::setPosition(glm::vec3 pos)
{
    position = pos;
}

/**
 * @brief Obtiene la posición del esqueleto.
 * @return Posición actual.
 */
glm::vec3 GESkeleton::getPosition() const
{
    return position;
}

/**
 * @brief Asigna la orientación del esqueleto.
 * @param z Vector del eje Z local.
 * @param y Vector del eje Y local.
 */
void GESkeleton::setOrientation(glm::vec3 z, glm::vec3 y)
{
    zAxis = z;
    yAxis = y;
}
