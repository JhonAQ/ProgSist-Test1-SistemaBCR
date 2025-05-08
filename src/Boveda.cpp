#include "Boveda.h"
#include <iostream>

Boveda::Boveda(Plaza* plaza)
    : plaza(plaza), saldo_200(0), saldo_100(0), saldo_50(0), saldo_10(0), saldo_5(0),
      saldo_bonos(0), saldo_joyas(0) {}

void Boveda::actualizarSaldo(Operacion* op, bool esEntrada) {
  int signo = esEntrada ? 1 : -1;
  saldo_200 += signo * op->getBilletes(200);
  saldo_100 += signo * op->getBilletes(100);
  saldo_50  += signo * op->getBilletes(50);
  saldo_10  += signo * op->getBilletes(10);
  saldo_5   += signo * op->getBilletes(5);
  saldo_bonos += signo * op->getBonos();
  saldo_joyas += signo * op->getJoyas();
}

void Boveda::mostrarSaldo() {
  std::cout << "Saldo en boveda de plaza " << plaza->getNombre() << ":";
  std::cout << "  Billetes 200: " << saldo_200 << "\n";
  std::cout << "  Billetes 100: " << saldo_100 << "\n";
  std::cout << "  Billetes 50:  " << saldo_50  << "\n";
  std::cout << "  Billetes 10:  " << saldo_10  << "\n";
  std::cout << "  Billetes 5:   " << saldo_5   << "\n";
  std::cout << "  Bonos:        " << saldo_bonos << "\n";
  std::cout << "  Joyas:        " << saldo_joyas << "\n";
}
