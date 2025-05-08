#include "EntidadBancaria.h"

EntidadBancaria::EntidadBancaria(std::string nombre) : nombre(nombre) {}

void EntidadBancaria::agregarBoveda(Boveda* boveda) {
  bovedas.push_back(boveda);
}

Boveda* EntidadBancaria::getBovedaPorPlaza(std::string nombrePlaza) {
  for (auto boveda : bovedas) {
    if (boveda->getPlaza()->getNombre() == nombrePlaza)
      return boveda;
  }
  return nullptr;
}

void EntidadBancaria::agregarOperacion(Operacion* op, bool esEntrada) {
  Boveda* b = getBovedaPorPlaza(op->getPlaza()->getNombre());
  if (b) {
    b->actualizarSaldo(op, esEntrada);
  }
}
