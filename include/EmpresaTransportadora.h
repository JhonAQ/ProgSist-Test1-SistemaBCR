#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Vehiculo.h"

class EmpresaTransportadora {
public:
  EmpresaTransportadora(const std::string& id, const std::string& nombre);
  void agregarVehiculo(std::unique_ptr<Vehiculo> vehiculo);

private:
  std::string idTransportadora;
  std::string nombre;
  std::vector<std::unique_ptr<Vehiculo>> flota; // Composición
};
