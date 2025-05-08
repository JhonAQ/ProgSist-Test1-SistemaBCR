#include <iomanip>
#include <iostream>
#include <string>

#include "Boveda.h"
#include "EntidadBancaria.h"
#include "Operacion.h"
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

int main() {
  // 1 Iniciand
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

  Operacion* op1 = new Operacion("08/05/2025", "entrega", bcp, interbank,
                                 hermes, arequipa, 10, 20, 15, 5, 0, 3, 2);
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

  Operacion* op2 = new Operacion("08/05/2025", "recojo", interbank, bcp,
                                 hermes, arequipa, 5, 10, 5, 2, 1, 1, 0);
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
  cout << "Detalle: 2 billetes de 200, 5 billetes de 100, 10 billetes de 50," << endl;
  cout << "         8 billetes de 10, 4 billetes de 5, 2 bonos, 1 joya" << endl;

  Operacion* op3 = new Operacion("08/05/2025", "entrega", bcp, scotiabank,
                                 prosegur, arequipa, 2, 5, 10, 8, 4, 2, 1);
  cout << "\nAplicando operación..." << endl;
  op3->aplicar();
  sistema.registrarOperacion(op3);
  cout << "Operación aplicada y registrada en el sistema BCR" << endl;

  imprimirTitulo("REPORTES DEL SISTEMA BCR");

  sistema.calcularSaldoBCR("08/05/2025");
  cout << endl;

  sistema.mostrarInformePorTipoMonedaYBien("08/05/2025");

  imprimirTitulo("FINALIZANDO SISTEMA");
  cout << "Liberando recursos..." << endl;

  cout << "Sistema finalizado correctamente" << endl;

  return 0;
}