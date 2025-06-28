#pragma once

#include <string>
#include <vector>
#include <memory>
#include "../include/Plaza.h"
#include "../include/EntidadBancaria.h"
#include "../include/EmpresaTransportadora.h"
#include "../include/Vehiculo.h"
#include "../include/Activo.h"
#include "../include/Operacion.h"
#include "../include/RutaDeTransporte.h"
#include "../include/Boveda.h"

namespace CsvParser {

  // Carga entidades que no tienen dependencias externas.
  std::vector<std::unique_ptr<Plaza>> cargarPlazas(const std::string& filepath);
  std::vector<std::unique_ptr<EntidadBancaria>> cargarEntidades(const std::string& filepath);
  std::vector<std::unique_ptr<EmpresaTransportadora>> cargarTransportadoras(const std::string& filepath);

  // Carga entidades que dependen de las anteriores.
  void cargarVehiculos(const std::string& filepath, std::vector<std::unique_ptr<EmpresaTransportadora>>& transportadoras);
  void cargarBovedas(
    const std::string& filepath,
    std::vector<std::unique_ptr<EntidadBancaria>>& entidades,
    const std::vector<std::unique_ptr<Plaza>>& plazas
  );
  void cargarActivosIniciales(const std::string& filepath, const std::vector<std::unique_ptr<EntidadBancaria>>& entidades);
  void cargarPlanDeOperaciones(
    const std::string& filepath, 
    const std::vector<std::unique_ptr<EntidadBancaria>>& entidades, 
    std::vector<std::unique_ptr<RutaDeTransporte>>& rutas
  );

}
