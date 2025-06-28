#include "../include/Boveda.h"
#include "../include/Excepciones.h"
#include "../include/EntidadBancaria.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

Boveda::Boveda(const std::string& id, Plaza* plaza, EntidadBancaria* propietario)
  : idBoveda(id), plaza(plaza), propietario(propietario) {}

void Boveda::agregarActivo(std::unique_ptr<Activo> activo) {
  if (activo) {
    activosAlmacenados.push_back(std::move(activo));
  }
}

std::unique_ptr<Activo> Boveda::retirarActivo(const std::string& idActivo) {
  auto it = std::find_if(activosAlmacenados.begin(), activosAlmacenados.end(),
    [&](const std::unique_ptr<Activo>& activo) {
      return activo->obtenerId() == idActivo;
    });

  if (it == activosAlmacenados.end()) {
    throw ActivoNoEncontradoException();
  }

  std::unique_ptr<Activo> activoRetirado = std::move(*it);
  activosAlmacenados.erase(it);
  return activoRetirado;
}

double Boveda::calcularSaldoPorMoneda(TipoMoneda moneda) const {
  double total = 0.0;
  for (const auto& activo : activosAlmacenados) {
    if (activo->obtenerMonedaEquivalencia() == moneda) {
      total += activo->obtenerValorEquivalente();
    }
  }
  return total;
}

void Boveda::imprimirSaldos() const {
  std::cout << "  Boveda: " << idBoveda << " (" << propietario->obtenerNombre() << ")" << std::endl;
  std::cout << "    Saldo Consolidado PEN: " << std::fixed << std::setprecision(2) << calcularSaldoPorMoneda(TipoMoneda::PEN) << std::endl;
  std::cout << "    Saldo Consolidado USD: " << std::fixed << std::setprecision(2) << calcularSaldoPorMoneda(TipoMoneda::USD) << std::endl;
}

void Boveda::imprimirDetalleActivos() const {
  std::cout << "  Detalle de Activos en Boveda " << idBoveda << ":" << std::endl;
  if (activosAlmacenados.empty()) {
    std::cout << "    (Boveda vacia)" << std::endl;
  } else {
    for (const auto& activo : activosAlmacenados) {
      activo->imprimirDetalles();
    }
  }
}
