#pragma once
#include "Plaza.h"
#include "Operacion.h"

class Boveda {
  Plaza* plaza;
  int saldo_200, saldo_100, saldo_50, saldo_10, saldo_5;
  int saldo_bonos, saldo_joyas;

public:
  Boveda(Plaza* plaza);
  void actualizarSaldo(Operacion* op, bool esEntrada);
  void mostrarSaldo();
  Plaza* getPlaza() const;
};