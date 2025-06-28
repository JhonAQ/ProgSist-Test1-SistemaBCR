#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Vehiculo.h"

class EmpresaTransportadora {
public:
  EmpresaTransportadora(const std::string& id, const std::string& nombre);
  void agregarVehiculo(std::unique_ptr<Vehiculo> vehiculo);

  const std::string& obtenerId() const { return idTransportadora; }
  const std::string& obtenerNombre() const { return nombre; }
  const std::vector<std::unique_ptr<Vehiculo>>& obtenerFlota() const { return flota; }

private:
  std::string idTransportadora;
  std::string nombre;
  std::vector<std::unique_ptr<Vehiculo>> flota; // Composición
};
