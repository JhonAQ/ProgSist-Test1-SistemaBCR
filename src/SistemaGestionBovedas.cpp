#include "../include/SistemaGestionBovedas.h"
#include "../utils/csv_parser.h"
#include "../include/Excepciones.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <cctype>
#include <random>

namespace {
  std::string obtenerTimestamp() {
    auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::stringstream ss;
    ss << std::put_time(std::localtime(&t), "%Y%m%d_%H%M%S");
    return ss.str();
  }

  void limpiarBufferEntrada() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  // Helper para convertir string a mayúsculas
  std::string aMayusculas(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c){ return std::toupper(c); });
    return s;
  }
}

// --- Constructor y Destructor ---
SistemaGestionBovedas::SistemaGestionBovedas() {}
SistemaGestionBovedas::~SistemaGestionBovedas() {}

// --- Flujo Principal de la Aplicación ---

void SistemaGestionBovedas::cargarDatosIniciales() {
  try {
    std::cout << "Cargando datos iniciales del sistema..." << std::endl;
    
    plazas = CsvParser::cargarPlazas("data/plazas.csv");
    entidades = CsvParser::cargarEntidades("data/entidades.csv");
    transportadoras = CsvParser::cargarTransportadoras("data/transportadoras.csv");
    CsvParser::cargarVehiculos("data/vehiculos.csv", transportadoras);
    CsvParser::cargarBovedas("data/bovedas.csv", entidades, plazas);
    CsvParser::cargarActivosIniciales("data/activos_iniciales.csv", entidades);

    std::cout << "\nCarga de datos iniciales completada." << std::endl;
    generarReporte("Inicializacion_Sistema", "El sistema se ha inicializado y cargado los datos base desde archivos CSV.");
  
  } catch (const std::exception& e) {
    std::cerr << "ERROR FATAL durante la inicializacion: " << e.what() << std::endl;
    generarReporte("Inicializacion_FALLO", e.what());
    throw;
  }
}

void SistemaGestionBovedas::ejecutarMenuSeleccionEntidad() {
  int opcion;
  do {
    std::cout << "\n===== SELECCION DE ENTIDAD BANCARIA =====\n";
    for (size_t i = 0; i < entidades.size(); ++i) {
      std::cout << i + 1 << ". Supervisar " << entidades[i]->obtenerNombre() << std::endl;
    }
    std::cout << entidades.size() + 1 << ". Salir del Sistema\n";
    std::cout << "=========================================\n";
    std::cout << "Seleccione una entidad para supervisar: ";
    std::cin >> opcion;

    if (std::cin.fail() || opcion < 1 || opcion > (int)entidades.size() + 1) {
      opcion = 0;
      limpiarBufferEntrada();
      std::cout << "Opcion invalida. Intente de nuevo.\n";
      continue;
    }
    
    if (opcion <= (int)entidades.size()) {
      ejecutarSubMenuEntidad(entidades[opcion - 1].get());
    }

  } while (opcion != (int)entidades.size() + 1);
  std::cout << "Saliendo del sistema de gestion. Hasta luego.\n";
}

void SistemaGestionBovedas::ejecutarSubMenuEntidad(EntidadBancaria* entidad) {
  if (!entidad) return;
  int opcion;
  do {
    std::cout << "\n--- Supervisando: " << entidad->obtenerNombre() << " ---\n";
    std::cout << "1. Ver Saldos de la Entidad\n";
    std::cout << "2. Ver Detalle de Activos en una Boveda\n";
    std::cout << "3. Crear y Planificar Nueva Operacion\n";
    std::cout << "4. Ver Rutas de Transporte Planificadas\n";
    std::cout << "5. Ejecutar Siguiente Parada de una Ruta\n";
    std::cout << "6. Volver a la Seleccion de Entidad\n";
    std::cout << "--------------------------------------\n";
    std::cout << "Seleccione una opcion: ";
    std::cin >> opcion;
    
    if(std::cin.fail()) {
      opcion = 0;
      limpiarBufferEntrada();
    }

    switch (opcion) {
      case 1: opcionVerSaldos(entidad); break;
      case 2: opcionVerDetalleActivos(entidad); break;
      case 3: opcionCrearOperacion(entidad); break;
      case 4: opcionVerRutas(); break;
      case 5: opcionEjecutarParada(); break;
      case 6: std::cout << "Regresando a la seleccion de entidad...\n"; break;
      default: std::cout << "Opcion no valida. Intente de nuevo.\n"; break;
    }
  } while (opcion != 6);
}

// --- Implementaciones de las Opciones del Menú ---

void SistemaGestionBovedas::opcionVerSaldos(EntidadBancaria* entidad) const {
  std::cout << "\n--- Saldos para " << entidad->obtenerNombre() << " ---\n";
  std::stringstream reporte;
  reporte << "Consulta de saldos para la entidad: " << entidad->obtenerNombre() << "\n\n";

  for (const auto& boveda : entidad->obtenerBovedas()) {
    boveda->imprimirSaldos();
    reporte << "  - Boveda " << boveda->obtenerId() 
            << " | PEN: " << boveda->calcularSaldoPorMoneda(TipoMoneda::PEN)
            << " | USD: " << boveda->calcularSaldoPorMoneda(TipoMoneda::USD) << "\n";
  }
  std::cout << "  -----------------------------------------" << std::endl;
  std::cout << "  Saldo Consolidado (SALDO_BCR) PEN: " << entidad->obtenerSaldoConsolidado(TipoMoneda::PEN) << std::endl;
  std::cout << "  Saldo Consolidado (SALDO_BCR) USD: " << entidad->obtenerSaldoConsolidado(TipoMoneda::USD) << std::endl;
  reporte << "\nSALDO CONSOLIDADO (SALDO_BCR) PEN: " << entidad->obtenerSaldoConsolidado(TipoMoneda::PEN) << "\n";
  reporte << "SALDO CONSOLIDADO (SALDO_BCR) USD: " << entidad->obtenerSaldoConsolidado(TipoMoneda::USD) << "\n";

  generarReporte("Consulta_Saldos_" + entidad->obtenerId(), reporte.str());
}

void SistemaGestionBovedas::opcionVerDetalleActivos(EntidadBancaria* entidad) const {
  std::cout << "Listado de bovedas para " << entidad->obtenerNombre() << ":\n";
  const auto& bovedas = entidad->obtenerBovedas();
  for (size_t i = 0; i < bovedas.size(); ++i) {
    std::cout << i + 1 << ". " << bovedas[i]->obtenerId() << "\n";
  }
  std::cout << "Seleccione una boveda para ver su detalle (0 para cancelar): ";
  int opcion;
  std::cin >> opcion;
  if (std::cin.fail() || opcion < 1 || opcion > (int)bovedas.size()) {
    limpiarBufferEntrada();
    if (opcion != 0) std::cout << "Opcion invalida.\n";
    return;
  }
  bovedas[opcion - 1]->imprimirDetalleActivos();
}

void SistemaGestionBovedas::opcionCrearOperacion(EntidadBancaria* entidadActual) {
  try {
    std::cout << "\n--- Creacion de Nueva Operacion ---\n";
    
    // 1. Seleccionar tipo de operación
    std::cout << "Seleccione el tipo de operacion:\n1. Traspaso Interno\n2. Transferencia Interbancaria\n3. Operacion con BCRP\nOpcion: ";
    int tipoOp;
    std::cin >> tipoOp;
    if (std::cin.fail() || tipoOp < 1 || tipoOp > 3) throw ValidacionException("Tipo de operacion invalido.");

    // 2. Seleccionar bóvedas
    std::cout << "\n-- Boveda de Origen (pertenece a " << entidadActual->obtenerNombre() << ") --\n";
    Boveda* origen = seleccionarBoveda("origen");
    if (origen->obtenerPropietario() != entidadActual) {
      throw OperacionInvalidaException("La boveda de origen debe pertenecer a la entidad supervisada.");
    }
    
    std::cout << "\n-- Boveda de Destino --\n";
    Boveda* destino = seleccionarBoveda("destino");

    // 3. Crear el activo a transferir
    std::cout << "\n-- Detalle del Activo a Transferir --\n";
    std::cout << "Ingrese ID del activo a mover (e.g., ACT001): ";
    std::string idActivo;
    std::cin >> idActivo;
    limpiarBufferEntrada();

    // 4. Crear la operación
    std::unique_ptr<Operacion> nuevaOperacion;
    std::string opId = "OP_" + obtenerTimestamp();
    
    switch (tipoOp) {
      case 1: nuevaOperacion = std::make_unique<TraspasoInterno>(opId, origen, destino); break;
      case 2: nuevaOperacion = std::make_unique<TransferenciaInterbancaria>(opId, origen, destino); break;
      case 3: nuevaOperacion = std::make_unique<OperacionBCRP>(opId, origen, destino); break;
    }
    
    std::unique_ptr<Activo> activoAMover = origen->retirarActivo(idActivo); // Lanza excepción si no existe
    double valorMovido = activoAMover->obtenerValorEquivalente();
    nuevaOperacion->agregarActivo(std::move(activoAMover));

    // 5. Asignar a una ruta
    std::cout << "\n-- Asignacion a Ruta de Transporte --\n";
    EmpresaTransportadora* transportadora = seleccionarTransportadora();
    Vehiculo* vehiculo = seleccionarVehiculo(transportadora);

    std::string rutaId = "RUTA_" + obtenerTimestamp();
    rutas.push_back(std::make_unique<RutaDeTransporte>(rutaId, transportadora, vehiculo));
    rutas.back()->agregarParada(std::move(nuevaOperacion));

    std::cout << "\nOperacion " << opId << " creada y asignada a la nueva ruta " << rutaId << " con exito." << std::endl;
    std::stringstream reporte;
    reporte << "Nueva operacion planificada:\n"
            << "  - ID Operacion: " << opId << "\n"
            << "  - ID Ruta: " << rutaId << "\n"
            << "  - Origen: " << origen->obtenerId() << "\n"
            << "  - Destino: " << destino->obtenerId() << "\n"
            << "  - Valor: " << valorMovido << "\n";
    generarReporte("Creacion_Operacion", reporte.str());

  } catch (const BovedaException& e) {
    std::cerr << "ERROR al crear la operacion: " << e.what() << std::endl;
    generarReporte("Creacion_Operacion_FALLO", e.what());
  }
}

void SistemaGestionBovedas::opcionVerRutas() const {
  std::cout << "\n--- Rutas de Transporte Planificadas y en Curso ---\n";
  if (rutas.empty()) {
    std::cout << "No hay rutas planificadas en el sistema.\n";
    return;
  }
  for(const auto& ruta : rutas) {
    std::cout << "  - Ruta ID: " << ruta->obtenerId() << " | Estado: ";
    switch(ruta->obtenerEstado()) {
      case EstadoRuta::PLANIFICADA: std::cout << "Planificada\n"; break;
      case EstadoRuta::EN_CURSO: std::cout << "En Curso\n"; break;
      case EstadoRuta::COMPLETADA: std::cout << "Completada\n"; break;
      case EstadoRuta::CANCELADA: std::cout << "Cancelada\n"; break;
    }
  }
}

void SistemaGestionBovedas::opcionEjecutarParada() {
  std::cout << "\n--- Ejecutar Siguiente Parada de una Ruta ---\n";
  if (rutas.empty()) {
    std::cout << "No hay rutas para ejecutar.\n";
    return;
  }
  
  std::vector<RutaDeTransporte*> rutasActivas;
  for(size_t i = 0; i < rutas.size(); ++i) {
    if (rutas[i]->obtenerEstado() == EstadoRuta::PLANIFICADA || rutas[i]->obtenerEstado() == EstadoRuta::EN_CURSO) {
      std::cout << rutasActivas.size() + 1 << ". Ruta ID: " << rutas[i]->obtenerId() << std::endl;
      rutasActivas.push_back(rutas[i].get());
    }
  }

  if (rutasActivas.empty()) {
    std::cout << "No hay rutas activas para ejecutar.\n";
    return;
  }

  std::cout << "Seleccione una ruta para avanzar (0 para cancelar): ";
  int opcion;
  std::cin >> opcion;
  if (std::cin.fail() || opcion < 1 || opcion > (int)rutasActivas.size()) {
    limpiarBufferEntrada();
    if (opcion != 0) std::cout << "Opcion invalida.\n";
    return;
  }

  RutaDeTransporte* rutaSeleccionada = rutasActivas[opcion - 1];
  try {
    rutaSeleccionada->ejecutarSiguienteParada();
    std::cout << "Parada ejecutada con exito. Nuevo estado de la ruta: ";
    if(rutaSeleccionada->obtenerEstado() == EstadoRuta::COMPLETADA) {
      std::cout << "Completada.\n";
    } else {
      std::cout << "En Curso.\n";
    }
    generarReporte("Ejecucion_Parada", "Se ejecuto la siguiente parada de la ruta " + rutaSeleccionada->obtenerId());
  } catch (const BovedaException& e) {
    std::cerr << "ERROR al ejecutar la parada: " << e.what() << std::endl;
    generarReporte("Ejecucion_Parada_FALLO", "Ruta " + rutaSeleccionada->obtenerId() + ": " + e.what());
  }
}

// --- Métodos de Ayuda (Helpers) ---

void SistemaGestionBovedas::generarReporte(const std::string& tipoAccion, const std::string& contenido) const {
  std::string timestamp = obtenerTimestamp();
  std::string filename = "reports/report_" + timestamp + "_" + aMayusculas(tipoAccion) + ".md";
  std::ofstream file(filename);

  if (file.is_open()) {
      file << "# Reporte de Accion: " << tipoAccion << "\n\n";
      file << "**Fecha y Hora:** " << timestamp << "\n\n";
      file << "## Detalles\n\n";
      file << "```\n";
      file << contenido << "\n";
      file << "```\n";
      file.close();
  } else {
      std::cerr << "Error: No se pudo crear el archivo de reporte " << filename << std::endl;
  }
}

Boveda* SistemaGestionBovedas::seleccionarBoveda(const std::string& proposito) const {
  std::cout << "Listado de todas las bovedas del sistema:\n";
  std::vector<Boveda*> bovedasDisponibles;
  for (const auto& ent : entidades) {
    for (const auto& bov : ent->obtenerBovedas()) {
      std::cout << "  - ID: " << bov->obtenerId() << " (Propietario: " << ent->obtenerId() << ")\n";
      bovedasDisponibles.push_back(bov.get());
    }
  }
  std::cout << "Ingrese el ID de la boveda de " << proposito << ": ";
  std::string id;
  std::cin >> id;
  limpiarBufferEntrada();

  auto it = std::find_if(bovedasDisponibles.begin(), bovedasDisponibles.end(),
    [&](Boveda* b) { return b->obtenerId() == id; });

  if (it == bovedasDisponibles.end()) {
    throw RecursoNoEncontradoException("Boveda con ID '" + id + "'");
  }
  return *it;
}

EmpresaTransportadora* SistemaGestionBovedas::seleccionarTransportadora() const {
  if (transportadoras.empty()) {
    throw RecursoNoEncontradoException("No hay empresas transportadoras registradas en el sistema.");
  }

  std::cout << "\n-- Seleccion de Empresa Transportadora --\n";
  std::cout << "Listado de transportadoras disponibles:\n";
  for (const auto& t : transportadoras) {
    std::cout << "  - ID: " << t->obtenerId() << " | Nombre: " << t->obtenerNombre() << "\n";
  }

  while (true) {
    std::cout << "Ingrese el ID de la transportadora deseada (o 'cancelar'): ";
    std::string idSeleccionado;
    std::cin >> idSeleccionado;
    limpiarBufferEntrada();

    if (aMayusculas(idSeleccionado) == "CANCELAR") {
      throw BovedaException("Seleccion de transportadora cancelada por el usuario.");
    }

    auto it = std::find_if(transportadoras.begin(), transportadoras.end(),
      [&](const std::unique_ptr<EmpresaTransportadora>& t) {
        return aMayusculas(t->obtenerId()) == aMayusculas(idSeleccionado);
      });

    if (it != transportadoras.end()) {
      std::cout << "Transportadora '" << (*it)->obtenerNombre() << "' seleccionada.\n";
      return it->get();
    } else {
      std::cerr << "ID no valido. Por favor, intente de nuevo.\n";
    }
  }
}

Vehiculo* SistemaGestionBovedas::seleccionarVehiculo(EmpresaTransportadora* transportadora) const {
  if (!transportadora) {
    // Esta excepción es defensiva, el flujo normal no debería permitir un puntero nulo.
    throw ValidacionException("Puntero a transportadora nulo proporcionado.");
  }

  const auto& flota = transportadora->obtenerFlota();
  if (flota.empty()) {
    throw RecursoNoEncontradoException("La transportadora '" + transportadora->obtenerNombre() + "' no tiene vehiculos en su flota.");
  }

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(0, flota.size() - 1);

  // Seleccionar un índice aleatorio
  int indiceAleatorio = distrib(gen);
  Vehiculo* vehiculoSeleccionado = flota[indiceAleatorio].get();

  std::cout << "La transportadora ha asignado aleatoriamente el vehiculo: " 
            << vehiculoSeleccionado->obtenerId() << " (Placa: " << vehiculoSeleccionado->obtenerPlaca() << ")\n";
  
  return vehiculoSeleccionado;
}
