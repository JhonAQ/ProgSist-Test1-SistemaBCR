#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>
#include "enums.h"
#include "Activo.h"

// Forward declarations para evitar dependencias circulares.
class Plaza;
class EntidadBancaria;

class Boveda {
public:
  Boveda(const std::string& id, Plaza* plaza, EntidadBancaria* propietario);
  virtual ~Boveda() = default;

  const std::string& obtenerId() const { return idBoveda; }
  EntidadBancaria* obtenerPropietario() const { return propietario; }

  void agregarActivo(std::unique_ptr<Activo> activo);
  std::unique_ptr<Activo> retirarActivo(const std::string& idActivo);
  
  double calcularSaldoPorMoneda(TipoMoneda moneda) const;
  void imprimirSaldos() const;
  void imprimirDetalleActivos() const;

protected:
  std::string idBoveda;
  Plaza* plaza; // Asociación, no propiedad
  EntidadBancaria* propietario; // Asociación, no propiedad
  std::vector<std::unique_ptr<Activo>> activosAlmacenados;
};

class BovedaCentral : public Boveda {
public:
  using Boveda::Boveda;
};

class BovedaSucursal : public Boveda {
public:
  using Boveda::Boveda;
};

class BovedaBCRP : public Boveda {
public:
  using Boveda::Boveda;
};
