#include "../include/Sistema.h"
#include "../include/Excepciones.h"
#include "../include/Boveda.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <limits>

Sistema::Sistema() = default;
Sistema::~Sistema() = default;

// helper methods
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
}

void Sistema::inicializarDatosDePrueba() {
  plazas.push_back(std::make_unique<Plaza>("PLAZA_LIMA", "Lima"));

  auto bcp = std::make_unique<EntidadBancaria>("BCP", "Banco de Credito del Peru");
  auto bbva = std::make_unique<EntidadBancaria>("BBVA", "BBVA Peru");
  auto bcrp = std::make_unique<EntidadBancaria>("BCRP", "Banco Central de Reserva del Peru");

  bcp->agregarBoveda(std::make_unique<BovedaCentral>("BCP_CEN", plazas[0].get(), bcp.get()));
  bcp->agregarBoveda(std::make_unique<BovedaSucursal>("BCP_SURCO", plazas[0].get(), bcp.get()));
  bbva->agregarBoveda(std::make_unique<BovedaCentral>("BBVA_CEN", plazas[0].get(), bbva.get()));
  bcrp->agregarBoveda(std::make_unique<BovedaBCRP>("BCRP_CEN", plazas[0].get(), bcrp.get()));

  bcp->obtenerBovedas()[0]->agregarActivo(std::make_unique<ValorMonetario>("ACT001", 5000000.0, TipoMoneda::PEN, std::map<Denominacion, int>{{Denominacion::B_100, 50000}}));
  bbva->obtenerBovedas()[0]->agregarActivo(std::make_unique<ValorMonetario>("ACT002", 4000000.0, TipoMoneda::PEN, std::map<Denominacion, int>{{Denominacion::B_100, 40000}}));
  bcrp->obtenerBovedas()[0]->agregarActivo(std::make_unique<ValorMonetario>("ACT003", 100000000.0, TipoMoneda::PEN, std::map<Denominacion, int>{{Denominacion::B_200, 500000}}));

  entidades.push_back(std::move(bcp));
  entidades.push_back(std::move(bbva));
  entidades.push_back(std::move(bcrp));

  transportadoras.push_back(std::make_unique<EmpresaTransportadora>("HERMES", "Hermes Transportes Blindados S.A."));

  std::cout << "Sistema inicializado con datos de prueba." << std::endl;
}

void Sistema::cargarOperacionesDesdeCSV(const std::string& filepath) {
  std::cout << "Cargando operaciones desde " << filepath << "..." << std::endl;
  generarReporte("Carga de CSV", "Se intento cargar operaciones. Funcionalidad de parsing no implementada en detalle.");
  std::cout << "Funcionalidad de parsing de CSV no implementada en detalle para este prototipo." << std::endl;
}

void Sistema::mostrarMenu() const {
  std::cout << "\n===== MENU - SISTEMA DE GESTION DE BOVEDAS =====\n";
  std::cout << "1. Ver Saldos de Todas las Bovedas\n";
  std::cout << "2. Crear y Ejecutar Operacion (Demo)\n";
  std::cout << "3. Ver Rutas de Transporte (No implementado)\n";
  std::cout << "4. Ejecutar Siguiente Parada de Ruta (No implementado)\n";
  std::cout << "5. Cargar Operaciones desde CSV\n";
  std::cout << "6. Salir\n";
  std::cout << "==============================================\n";
  std::cout << "Seleccione una opcion: ";
}

void Sistema::ejecutarMenuPrincipal() {
  int opcion;
  do {
    mostrarMenu();
    std::cin >> opcion;
    if(std::cin.fail()) {
      opcion = 0; // Fuerza opción inválida
      limpiarBufferEntrada();
    }
    
    switch (opcion) {
      case 1: opcionVerSaldos(); break;
      case 2: opcionCrearOperacion(); break;
      case 3: std::cout << "Funcionalidad aun no implementada.\n"; break;
      case 4: std::cout << "Funcionalidad aun no implementada.\n"; break;
      case 5: cargarOperacionesDesdeCSV("data/operations_data.csv"); break;
      case 6: std::cout << "Saliendo del sistema...\n"; break;
      default: std::cout << "Opcion no valida. Intente de nuevo.\n"; break;
    }
  } while (opcion != 6);
}

void Sistema::opcionVerSaldos() const {
  std::cout << "\n--- ESTADO ACTUAL DE SALDOS ---" << std::endl;
  std::stringstream reporte;
  reporte << "Consulta de saldos realizada a las " << obtenerTimestamp() << ".\n\n";

  for (const auto& entidad : entidades) {
    std::cout << "Entidad: " << entidad->obtenerNombre() << std::endl;
    reporte << "Entidad: " << entidad->obtenerNombre() << "\n";
    for (const auto& boveda : entidad->obtenerBovedas()) {
      boveda->imprimirSaldos();
      reporte << "  - Boveda " << boveda->obtenerId() 
              << " | PEN: " << boveda->calcularSaldoPorMoneda(TipoMoneda::PEN)
              << " | USD: " << boveda->calcularSaldoPorMoneda(TipoMoneda::USD) << "\n";
    }
    std::cout << "  Saldo Consolidado PEN: " << entidad->obtenerSaldoConsolidado(TipoMoneda::PEN) << std::endl;
    std::cout << "  Saldo Consolidado USD: " << entidad->obtenerSaldoConsolidado(TipoMoneda::USD) << std::endl;
    reporte << "  Total Entidad PEN: " << entidad->obtenerSaldoConsolidado(TipoMoneda::PEN) << "\n";
    reporte << "  Total Entidad USD: " << entidad->obtenerSaldoConsolidado(TipoMoneda::USD) << "\n\n";
  }
  std::cout << "-------------------------------" << std::endl;
  generarReporte("Consulta_Saldos", reporte.str());
}

void Sistema::opcionCrearOperacion() {
  try {
    std::cout << "\n--- Ejecutando Operacion Demo ---" << std::endl;
    std::cout << "Traspaso Interno: BCP_CEN -> BCP_SURCO de 100,000 PEN" << std::endl;

    Boveda* origen = entidades[0]->obtenerBovedas()[0].get();
    Boveda* destino = entidades[0]->obtenerBovedas()[1].get();

    auto activo_a_mover = std::make_unique<ValorMonetario>("ACT_DEMO", 100000.0, TipoMoneda::PEN, std::map<Denominacion, int>{{Denominacion::B_100, 1000}});
    origen->agregarActivo(std::move(activo_a_mover));

    TraspasoInterno op("OP_DEMO_01", origen, destino);
    op.agregarActivo(origen->retirarActivo("ACT_DEMO"));

    std::stringstream reporte;
    reporte << "Operacion de Traspaso Interno Demo: OP_DEMO_01\n";
    reporte << "Origen: " << origen->obtenerId() << " | Destino: " << destino->obtenerId() << "\n\n";
    reporte << "ESTADO ANTES:\n";
    reporte << "  Saldo Origen (PEN): " << origen->calcularSaldoPorMoneda(TipoMoneda::PEN) << "\n";
    reporte << "  Saldo Destino (PEN): " << destino->calcularSaldoPorMoneda(TipoMoneda::PEN) << "\n\n";

    op.ejecutar();

    reporte << "ESTADO DESPUES:\n";
    reporte << "  Saldo Origen (PEN): " << origen->calcularSaldoPorMoneda(TipoMoneda::PEN) << "\n";
    reporte << "  Saldo Destino (PEN): " << destino->calcularSaldoPorMoneda(TipoMoneda::PEN) << "\n\n";
    reporte << "Resultado: EXITO";

    std::cout << "Operacion ejecutada con exito." << std::endl;
    generarReporte("Ejecucion_Operacion_Demo", reporte.str());

  } catch (const BovedaException& e) {
    std::cerr << "ERROR: " << e.what() << std::endl;
    generarReporte("Ejecucion_Operacion_Demo_FALLO", e.what());
  }
}

void Sistema::generarReporte(const std::string& tipoAccion, const std::string& contenido) const {
  std::string timestamp = obtenerTimestamp();
  std::string filename = "reports/report_" + timestamp + "_" + tipoAccion + ".md";
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
