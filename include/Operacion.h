#pragma once

#include <string>
#include <vector>
#include <memory>
#include "enums.h"
#include "Activo.h"

// Forward declaration
class Boveda;

class Operacion {
public:
  Operacion(const std::string& id, Boveda* origen, Boveda* destino);
  virtual ~Operacion() = default;

  void agregarActivo(std::unique_ptr<Activo> activo);
  virtual void ejecutar() = 0;

  const std::string& obtenerId() const { return idOperacion; }
  EstadoOperacion obtenerEstado() const { return estado; }

protected:
  std::string idOperacion;
  EstadoOperacion estado;
  Boveda* origen;
  Boveda* destino;
  std::vector<std::unique_ptr<Activo>> activosTransferidos;
};

class TraspasoInterno : public Operacion {
public:
  using Operacion::Operacion;
  void ejecutar() override;
};

class TransferenciaInterbancaria : public Operacion {
public:
  using Operacion::Operacion;
  void ejecutar() override;
};

class OperacionBCRP : public Operacion {
public:
  using Operacion::Operacion;
  void ejecutar() override;
};
