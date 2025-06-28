#include "../include/SistemaGestionBovedas.h"
#include <iostream>

int main() {
  try {
    SistemaGestionBovedas sistema;
    sistema.cargarDatosIniciales();
    sistema.ejecutarMenuSeleccionEntidad();
  } catch (const std::exception& e) {
    std::cerr << "Una excepcion no controlada ha terminado el programa: " << e.what() << std::endl;
    return 1;
  }
  return 0;
}
