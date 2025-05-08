#include "SistemaBCR.h"
#include <iostream>

void SistemaBCR::registrarOperacion(Operacion* op) {
  operaciones.push_back(op);
  op->aplicar();
}

void SistemaBCR::calcularSaldoBCR(std::string fecha) {
  std::cout << "Calculando saldos para fecha: " << fecha << "\n";
  for (auto op : operaciones) {
    if (op->getFecha() == fecha) {
      op->aplicar();
    }
  }
}

void SistemaBCR::mostrarInformePorTipoMonedaYBien(std::string fecha) {
  std::cout << "Informe de operaciones del BCR por fecha: " << fecha << "\n";
  for (auto op : operaciones) {
    if (op->getFecha() == fecha) {
      std::cout << "Operacion de tipo " << op->getFecha() << ", monto: " << op->calcularMontoTotal() << "\n";
    }
  }
}
