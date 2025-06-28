#include "../include/EntidadBancaria.h"
#include "../include/Boveda.h"

EntidadBancaria::EntidadBancaria(const std::string& id, const std::string& nombre)
  : idEntidad(id), nombreComercial(nombre) {}

void EntidadBancaria::agregarBoveda(std::unique_ptr<Boveda> boveda) {
  if (boveda) {
    bovedas.push_back(std::move(boveda));
  }
}

double EntidadBancaria::obtenerSaldoConsolidado(TipoMoneda moneda) const {
  double total = 0.0;
  for (const auto& boveda : bovedas) {
    total += boveda->calcularSaldoPorMoneda(moneda);
  }
  return total;
}
