/**
 * @file main.cpp
 * @brief Punto de entrada principal de la aplicación MVPVulkan.
 */

#include "GEApplication.h"
#include <iostream>
#include <stdexcept>

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                 TEST                                          //
//                          LIMITES ARTICULACIONES                                               //
//                  Si descomentas la linea del archivo DEBUG.h,                                 // 
//                  cuando ejecutes el programa podrás ver en terminal si algún ángulo           //
//                  definido en alguna articulación ha superado el límite y se ha limitado       //
//                  Únicamente lo he hecho para testear.                                         //
//                                                                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Imprime los controles de la aplicación en consola.
 */
void printControls();

int main()
{
	GEApplication app;

    printControls();
	try
	{
		app.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}


void printControls() {
    std::cout << R"(
    ___________________________________________________________
   /                                                           \
  |                SISTEMA DE CONTROL DE CAMARA                 |
   \___________________________________________________________/
    
    [ MOVIMIENTO ]                   [ ROTACION / ORIENTACION ]
     Q : Subir                        UP    : Inclinar Abajo
     A : Bajar                        DOWN  : Inclinar Arriba
     O : Izquierda                    LEFT  : Giro Antihorario
     P : Derecha                      RIGHT : Giro Horario
                                      K     : Rotar Izquierda
    [ AVANCE / RETROCESO ]            L     : Rotar Derecha
     1 / [+] : Avanzar (+0.1)
     2 / [-] : Retroceder (-0.1)     [ CONTROL ANIMACION ]
     S       : Reset (0.0)            SPACE : Pausa / Play
                                      R     : Reiniciar Animacion (Reset)
                                      N     : Keyframe Anterior
                                      M     : Siguiente Keyframe
    ___________________________________________________________
    )" << std::endl;
}