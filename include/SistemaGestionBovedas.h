#pragma once

#include <vector>
#include <memory>
#include <string>
#include "EntidadBancaria.h"
#include "EmpresaTransportadora.h"
#include "RutaDeTransporte.h"
#include "Plaza.h"
#include "Boveda.h"
#include "Operacion.h"
#include "Vehiculo.h"

class SistemaGestionBovedas {
public:
  SistemaGestionBovedas();
  ~SistemaGestionBovedas();

  void cargarDatosIniciales();
  void ejecutarMenuSeleccionEntidad();

private:
  void ejecutarSubMenuEntidad(EntidadBancaria* entidad);

  void opcionVerSaldos(EntidadBancaria* entidad) const;
  void opcionVerDetalleActivos(EntidadBancaria* entidad) const;
  void opcionCrearOperacion(EntidadBancaria* entidad);
  void opcionVerRutas() const;
  void opcionEjecutarParada();
  
  void generarReporte(const std::string& tipoAccion, const std::string& contenido) const;

  Boveda* seleccionarBoveda(const std::string& proposito) const;
  Vehiculo* seleccionarVehiculo(EmpresaTransportadora* transportadora) const;
  EmpresaTransportadora* seleccionarTransportadora() const;

  std::vector<std::unique_ptr<EntidadBancaria>> entidades;
  std::vector<std::unique_ptr<EmpresaTransportadora>> transportadoras;
  std::vector<std::unique_ptr<RutaDeTransporte>> rutas;
  std::vector<std::unique_ptr<Plaza>> plazas;
};
