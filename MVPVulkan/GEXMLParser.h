/**
 * @file GEXMLParser.h
 * @brief Parser para archivos .skel (XML) usando pugixml.
 */

#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "pugixml/pugixml.hpp"

/**
 * @struct GEJointData
 * @brief Estructura para almacenar los datos de una articulación parseada.
 */
struct GEJointData {
    std::string name;                   ///< Nombre de la articulación.
    float length;                       ///< Longitud del hueso.
    glm::vec3 offset;                   ///< Desplazamiento local respecto al padre.
    glm::vec3 zAxis;                    ///< Eje Z local (dirección del hueso).
    glm::vec3 yAxis;                    ///< Eje Y local (orientación "arriba").
    glm::vec3 limitsMin;                ///< Límites mínimos de rotación (grados).
    glm::vec3 limitsMax;                ///< Límites máximos de rotación (grados).
    bool hasLimits;                     ///< Indica si tiene límites definidos.
    std::vector<GEJointData> children;  ///< Articulaciones hijas.
};

/**
 * @struct GESkeletonData
 * @brief Estructura para almacenar los datos completos del esqueleto.
 */
struct GESkeletonData {
    std::string name;                   ///< Nombre del esqueleto.
    glm::vec3 offset;                   ///< Offset global del esqueleto.
    glm::vec3 zAxis;                    ///< Eje Z del esqueleto.
    glm::vec3 yAxis;                    ///< Eje Y del esqueleto.
    std::vector<GEJointData> rootJoints;///< Articulaciones raíz (hijas directas del skeleton).
};

/**
 * @class GEXMLParser
 * @brief Parser para archivos .skel en formato XML usando pugixml.
 */
class GEXMLParser {
public:
    /**
     * @brief Parsea un archivo .skel y devuelve los datos del esqueleto.
     * @param filename Ruta al archivo .skel.
     * @param outData Estructura donde se almacenarán los datos parseados.
     * @return true si el parseo fue exitoso, false en caso contrario.
     */
    static bool parseSkeletonFile(const std::string& filename, GESkeletonData& outData);

private:
    /**
     * @brief Parsea un nodo vec3 (offset, zaxis, yaxis).
     * @param node Nodo XML con atributos x, y, z.
     * @return Vector parseado.
     */
    static glm::vec3 parseVec3(pugi::xml_node node);
    
    /**
     * @brief Parsea una articulación y sus hijas recursivamente.
     * @param node Nodo XML del balljoint.
     * @return Datos de la articulación parseada.
     */
    static GEJointData parseBalljoint(pugi::xml_node node);
};
