#pragma once

#include <string>
#include <vector>
#include <memory>
#include "enums.h"

// Forward declaration
class Boveda;

class EntidadBancaria {
public:
  EntidadBancaria(const std::string& id, const std::string& nombre);

  void agregarBoveda(std::unique_ptr<Boveda> boveda);
  double obtenerSaldoConsolidado(TipoMoneda moneda) const;

  const std::string& obtenerId() const { return idEntidad; }
  const std::string& obtenerNombre() const { return nombreComercial; }
  const std::vector<std::unique_ptr<Boveda>>& obtenerBovedas() const { return bovedas; }

private:
  std::string idEntidad;
  std::string nombreComercial;
  std::vector<std::unique_ptr<Boveda>> bovedas; // Composición
};
