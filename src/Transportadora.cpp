#include "Transportadora.h"

Transportadora::Transportadora(std::string nombre) : nombre(nombre) {}

void Transportadora::registrarOperacion(Operacion* op) {
  historial.push_back(op);
}
