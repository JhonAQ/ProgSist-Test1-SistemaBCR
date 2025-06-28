#pragma once

#include <vector>
#include <memory>
#include <string>
#include "EntidadBancaria.h"
#include "EmpresaTransportadora.h"
#include "RutaDeTransporte.h"
#include "Plaza.h"

class Sistema {
public:
  Sistema();
  ~Sistema();

  void inicializarDatosDePrueba();
  void cargarOperacionesDesdeCSV(const std::string& filepath);
  void ejecutarMenuPrincipal();

private:
  void mostrarMenu() const;
  void opcionVerSaldos() const;
  void opcionCrearOperacion();
  void opcionVerRutas() const;
  void opcionEjecutarParada();
  
  void generarReporte(const std::string& tipoAccion, const std::string& contenido) const;

  std::vector<std::unique_ptr<EntidadBancaria>> entidades;
  std::vector<std::unique_ptr<EmpresaTransportadora>> transportadoras;
  std::vector<std::unique_ptr<RutaDeTransporte>> rutas;
  std::vector<std::unique_ptr<Plaza>> plazas;
};
