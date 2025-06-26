#include <iomanip>
#include <iostream>
#include <string>

#include "Boveda.h"
#include "EntidadBancaria.h"
#include "Operacion.h"
#include "Patrimonio.h"
#include "PatrimonioMonetario.h"
#include "PatrimonioBienes.h"
#include "Plaza.h"
#include "SistemaBCR.h"
#include "Transportadora.h"

using namespace std;

void imprimirLinea(char c = '-', int n = 50) {
  cout << string(n, c) << endl;
}

void imprimirTitulo(const string& titulo) {
  imprimirLinea('=');
  cout << setw(25 + titulo.length() / 2) << titulo << endl;
  imprimirLinea('=');
}

void pruebaOperacionesBasicas() {
    std::cout << "\n=== PRUEBA: Operaciones Básicas ===" << std::endl;
    
    try {
        Boveda boveda1("BOV001", "Banco Central");
        
        // Depósitos exitosos
        boveda1.depositar("USD", 10000.0);
        boveda1.depositar("EUR", 5000.0);
        
        std::cout << "Saldo USD: " << boveda1.consultarSaldo("USD") << std::endl;
        std::cout << "Saldo EUR: " << boveda1.consultarSaldo("EUR") << std::endl;
        
        // Retiro exitoso
        boveda1.retirar("USD", 2000.0);
        std::cout << "Saldo USD después del retiro: " << boveda1.consultarSaldo("USD") << std::endl;
        
    } catch (const BovedaException& e) {
        std::cout << "Error inesperado: " << e.what() << std::endl;
    }
}

void pruebaExcepciones() {
    std::cout << "\n=== PRUEBA: Manejo de Excepciones ===" << std::endl;
    
    Boveda boveda1("BOV001", "Banco Central");
    boveda1.depositar("USD", 1000.0);
    
    // Prueba 1: Saldo insuficiente
    try {
        boveda1.retirar("USD", 2000.0);
    } catch (const SaldoInsuficienteException& e) {
        std::cout << "✓ Capturada: " << e.what() << std::endl;
    }
    
    // Prueba 2: Activo no disponible
    try {
        boveda1.retirar("JPY", 100.0);
    } catch (const ActivoNoDisponibleException& e) {
        std::cout << "✓ Capturada: " << e.what() << std::endl;
    }
    
    // Prueba 3: Datos inválidos
    try {
        boveda1.depositar("", 100.0);
    } catch (const DatosInvalidosException& e) {
        std::cout << "✓ Capturada: " << e.what() << std::endl;
    }
    
    // Prueba 4: Operación inválida en bóveda inactiva
    try {
        boveda1.setActiva(false);
        boveda1.depositar("USD", 100.0);
    } catch (const OperacionInvalidaException& e) {
        std::cout << "✓ Capturada: " << e.what() << std::endl;
    }
}

void pruebaTransferencias() {
    std::cout << "\n=== PRUEBA: Transferencias ===" << std::endl;
    
    try {
        Boveda boveda1("BOV001", "Banco Central");
        Boveda boveda2("BOV002", "Banco Comercial");
        
        boveda1.depositar("USD", 5000.0);
        
        std::cout << "Antes de transferencia:" << std::endl;
        std::cout << "BOV001 USD: " << boveda1.consultarSaldo("USD") << std::endl;
        std::cout << "BOV002 USD: " << boveda2.consultarSaldo("USD") << std::endl;
        
        // Transferencia exitosa
        boveda1.transferir(boveda2, "USD", 1500.0);
        
        std::cout << "Después de transferencia:" << std::endl;
        std::cout << "BOV001 USD: " << boveda1.consultarSaldo("USD") << std::endl;
        std::cout << "BOV002 USD: " << boveda2.consultarSaldo("USD") << std::endl;
        
        // Transferencia fallida por saldo insuficiente
        boveda1.transferir(boveda2, "USD", 10000.0);
        
    } catch (const SaldoInsuficienteException& e) {
        std::cout << "✓ Error esperado en transferencia: " << e.what() << std::endl;
    } catch (const BovedaException& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

int main() {
  // 1 Iniciando
  imprimirTitulo("INICIALIZACIÓN DEL SISTEMA BCR");

  cout << "Creando plazas..." << endl;
  Plaza* arequipa = new Plaza("Arequipa");
  Plaza* lima = new Plaza("Lima");
  cout << "Plazas creadas: Arequipa, Lima" << endl;

  cout << "\nCreando transportadoras..." << endl;
  Transportadora* hermes = new Transportadora("Hermes");
  Transportadora* prosegur = new Transportadora("Prosegur");
  cout << "Transportadoras creadas: Hermes, Prosegur" << endl;

  cout << "\nCreando entidades bancarias..." << endl;
  EntidadBancaria* bcp = new EntidadBancaria("BCP");
  EntidadBancaria* interbank = new EntidadBancaria("Interbank");
  EntidadBancaria* scotiabank = new EntidadBancaria("Scotiabank");
  cout << "Entidades creadas: BCP, Interbank, Scotiabank" << endl;

  cout << "\nCreando bóvedas en plazas para cada entidad..." << endl;
  bcp->agregarBoveda(new Boveda(arequipa));
  bcp->agregarBoveda(new Boveda(lima));
  interbank->agregarBoveda(new Boveda(arequipa));
  interbank->agregarBoveda(new Boveda(lima));
  scotiabank->agregarBoveda(new Boveda(arequipa));
  cout << "Bóvedas creadas y asignadas a entidades" << endl;

  SistemaBCR sistema;
  cout << "\nSistema BCR inicializado correctamente" << endl;
  imprimirLinea();

  // 2
  imprimirTitulo("SIMULACIÓN DE OPERACIONES - DÍA 08/05/2025");

  cout << "OPERACIÓN 1: BCP entrega valores a Interbank en Arequipa" << endl;
  cout << "Transportadora: Hermes" << endl;
  cout << "Detalle: 10 billetes de 200, 20 billetes de 100, 15 billetes de 50," << endl;
  cout << "         5 billetes de 10, 0 billetes de 5, 3 bonos, 2 joyas" << endl;

  Operacion* op1 = new Operacion("08/05/2025", "entrega", bcp, interbank, hermes, arequipa);
  
  op1->agregarPatrimonio(new PatrimonioMonetario(10, "Billete de 200", "soles", 200));
  op1->agregarPatrimonio(new PatrimonioMonetario(20, "Billete de 100", "soles", 100));
  op1->agregarPatrimonio(new PatrimonioMonetario(15, "Billete de 50", "soles", 50));
  op1->agregarPatrimonio(new PatrimonioMonetario(5, "Billete de 10", "soles", 10));
  op1->agregarPatrimonio(new PatrimonioBienes(3, "Bono", "bonos", 1000));
  op1->agregarPatrimonio(new PatrimonioBienes(2, "Joya", "joyas", 5000));
  
  cout << "\nAplicando operación..." << endl;
  op1->aplicar();
  sistema.registrarOperacion(op1);
  cout << "Operación aplicada y registrada en el sistema BCR" << endl;

  cout << "\nEstado de bóvedas después de Operación 1:" << endl;
  cout << "BCP (Arequipa):" << endl;
  bcp->getBovedaPorPlaza("Arequipa")->mostrarSaldo();
  cout << "\nInterbank (Arequipa):" << endl;
  interbank->getBovedaPorPlaza("Arequipa")->mostrarSaldo();
  imprimirLinea();

  cout << "OPERACIÓN 2: Interbank entrega valores a BCP en Arequipa" << endl;
  cout << "Transportadora: Hermes" << endl;
  cout << "Detalle: 5 billetes de 200, 10 billetes de 100, 5 billetes de 50," << endl;
  cout << "         2 billetes de 10, 1 billete de 5, 1 bono, 0 joyas" << endl;

  Operacion* op2 = new Operacion("08/05/2025", "recojo", interbank, bcp, hermes, arequipa);
  
  op2->agregarPatrimonio(new PatrimonioMonetario(5, "Billete de 200", "soles", 200));
  op2->agregarPatrimonio(new PatrimonioMonetario(10, "Billete de 100", "soles", 100));
  op2->agregarPatrimonio(new PatrimonioMonetario(5, "Billete de 50", "soles", 50));
  op2->agregarPatrimonio(new PatrimonioMonetario(2, "Billete de 10", "soles", 10));
  op2->agregarPatrimonio(new PatrimonioMonetario(1, "Billete de 5", "soles", 5));
  op2->agregarPatrimonio(new PatrimonioBienes(1, "Bono", "bonos", 1000));
  
  cout << "\nAplicando operación..." << endl;
  op2->aplicar();
  sistema.registrarOperacion(op2);
  cout << "Operación aplicada y registrada en el sistema BCR" << endl;

  cout << "\nEstado de bóvedas después de Operación 2:" << endl;
  cout << "BCP (Arequipa):" << endl;
  bcp->getBovedaPorPlaza("Arequipa")->mostrarSaldo();
  cout << "\nInterbank (Arequipa):" << endl;
  interbank->getBovedaPorPlaza("Arequipa")->mostrarSaldo();
  imprimirLinea();

  cout << "OPERACIÓN 3: BCP entrega valores a Scotiabank en Arequipa" << endl;
  cout << "Transportadora: Prosegur" << endl;
  
  Operacion* op3 = new Operacion("08/05/2025", "entrega", bcp, scotiabank, prosegur, arequipa);
  op3->agregarPatrimonio(new PatrimonioMonetario(3, "Billete de 200", "soles", 200));
  op3->agregarPatrimonio(new PatrimonioMonetario(5, "Billete de 100", "soles", 100));
  op3->agregarPatrimonio(new PatrimonioBienes(1, "Joya", "joyas", 5000));
  
  op3->aplicar();
  sistema.registrarOperacion(op3);
  
  delete arequipa;
  delete lima;
  delete hermes;
  delete prosegur;
  delete bcp;
  delete interbank;
  delete scotiabank;
  
  pruebaOperacionesBasicas();
  pruebaExcepciones();
  pruebaTransferencias();
  
  std::cout << "\n=== FIN DE PRUEBAS ===" << std::endl;
  
  return 0;
}