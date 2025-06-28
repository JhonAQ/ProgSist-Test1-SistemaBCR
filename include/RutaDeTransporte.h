#pragma once

#include <string>
#include <vector>
#include <memory>
#include "enums.h"
#include "Operacion.h"

// Forward declarations
class EmpresaTransportadora;
class Vehiculo;

class RutaDeTransporte {
public:
  RutaDeTransporte(const std::string& id, EmpresaTransportadora* transportadora, Vehiculo* vehiculo);

  void agregarParada(std::unique_ptr<Operacion> operacion);
  void ejecutarSiguienteParada();

  const std::string& obtenerId() const { return idRuta; }
  EstadoRuta obtenerEstado() const { return estado; }

private:
  std::string idRuta;
  EstadoRuta estado;
  EmpresaTransportadora* transportadora;
  Vehiculo* vehiculo;
  std::vector<std::unique_ptr<Operacion>> paradas;
  size_t proximaParadaIndex;
};
