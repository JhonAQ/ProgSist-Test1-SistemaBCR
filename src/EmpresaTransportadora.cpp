#include "../include/EmpresaTransportadora.h"

EmpresaTransportadora::EmpresaTransportadora(const std::string& id, const std::string& nombre)
  : idTransportadora(id), nombre(nombre) {}

void EmpresaTransportadora::agregarVehiculo(std::unique_ptr<Vehiculo> vehiculo) {
  if (vehiculo) {
    flota.push_back(std::move(vehiculo));
  }
}
