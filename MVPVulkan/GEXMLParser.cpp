/**
 * @file GEXMLParser.cpp
 * @brief Implementación del parser XML usando pugixml.
 */

#include "GEXMLParser.h"
#include <iostream>

/**
 * @brief Parsea un nodo vec3 con atributos x, y, z.
 */
glm::vec3 GEXMLParser::parseVec3(pugi::xml_node node) {
    return glm::vec3(
        node.attribute("x").as_float(0.0f),
        node.attribute("y").as_float(0.0f),
        node.attribute("z").as_float(0.0f)
    );
}

/**
 * @brief Parsea una articulación y sus hijas recursivamente.
 */
GEJointData GEXMLParser::parseBalljoint(pugi::xml_node node) {
    GEJointData joint;
    
    // Atributos básicos
    joint.name = node.attribute("name").as_string("");
    joint.length = node.attribute("length").as_float(0.0f);
    
    // Valores por defecto
    joint.offset = glm::vec3(0.0f);
    joint.zAxis = glm::vec3(0.0f, 0.0f, 1.0f);
    joint.yAxis = glm::vec3(0.0f, 1.0f, 0.0f);
    joint.limitsMin = glm::vec3(-180.0f);
    joint.limitsMax = glm::vec3(180.0f);
    joint.hasLimits = false;
    
    // Parsear offset
    pugi::xml_node offsetNode = node.child("offset");
    if (offsetNode) {
        joint.offset = parseVec3(offsetNode);
    }
    
    // Parsear zaxis
    pugi::xml_node zaxisNode = node.child("zaxis");
    if (zaxisNode) {
        joint.zAxis = parseVec3(zaxisNode);
    }
    
    // Parsear yaxis
    pugi::xml_node yaxisNode = node.child("yaxis");
    if (yaxisNode) {
        joint.yAxis = parseVec3(yaxisNode);
    }
    
    // Parsear límites (opcional)
    pugi::xml_node limitsNode = node.child("limits");
    if (limitsNode) {
        joint.hasLimits = true;
        pugi::xml_node minNode = limitsNode.child("min");
        pugi::xml_node maxNode = limitsNode.child("max");
        if (minNode) {
            joint.limitsMin = parseVec3(minNode);
        }
        if (maxNode) {
            joint.limitsMax = parseVec3(maxNode);
        }
    }
    
    // Parsear hijos recursivamente
    for (pugi::xml_node child : node.children("balljoint")) {
        joint.children.push_back(parseBalljoint(child));
    }
    
    return joint;
}

/**
 * @brief Parsea un archivo .skel y devuelve los datos del esqueleto.
 */
bool GEXMLParser::parseSkeletonFile(const std::string& filename, GESkeletonData& outData) {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(filename.c_str());
    
    if (!result) {
        std::cerr << "Error al cargar " << filename << ": " << result.description() << std::endl;
        return false;
    }
    
    pugi::xml_node skeleton = doc.child("skeleton");
    if (!skeleton) {
        std::cerr << "Error: No se encontró el elemento <skeleton>" << std::endl;
        return false;
    }
    
    // Atributos del esqueleto
    outData.name = skeleton.attribute("name").as_string("skeleton");
    
    // Valores por defecto
    outData.offset = glm::vec3(0.0f);
    outData.zAxis = glm::vec3(0.0f, 0.0f, 1.0f);
    outData.yAxis = glm::vec3(0.0f, 1.0f, 0.0f);
    
    // Parsear offset del esqueleto
    pugi::xml_node offsetNode = skeleton.child("offset");
    if (offsetNode) {
        outData.offset = parseVec3(offsetNode);
    }
    
    // Parsear zaxis del esqueleto
    pugi::xml_node zaxisNode = skeleton.child("zaxis");
    if (zaxisNode) {
        outData.zAxis = parseVec3(zaxisNode);
    }
    
    // Parsear yaxis del esqueleto
    pugi::xml_node yaxisNode = skeleton.child("yaxis");
    if (yaxisNode) {
        outData.yAxis = parseVec3(yaxisNode);
    }
    
    // Parsear articulaciones raíz
    outData.rootJoints.clear();
    for (pugi::xml_node joint : skeleton.children("balljoint")) {
        outData.rootJoints.push_back(parseBalljoint(joint));
    }
    
    std::cout << "Esqueleto '" << outData.name << "' cargado con " 
              << outData.rootJoints.size() << " articulaciones raiz" << std::endl;
    
    return true;
}
