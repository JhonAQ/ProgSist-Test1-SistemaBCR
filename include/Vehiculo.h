#pragma once

#include <string>

class Vehiculo {
public:
  Vehiculo(const std::string& id, const std::string& placa);
  const std::string& obtenerId() const { return idVehiculo; }
  const std::string& obtenerPlaca() const { return placa; }

private:
  std::string idVehiculo;
  std::string placa;
};
