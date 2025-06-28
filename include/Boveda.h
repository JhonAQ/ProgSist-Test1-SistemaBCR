#pragma once
#include "Plaza.h"
#include "Operacion.h"
#include <map>
#include <string>

class Boveda {
  Plaza* plaza;
  std::map<std::string, Patrimonio*> inventario;

public:
  Boveda(Plaza* plaza);
  ~Boveda();
  
  void actualizarSaldo(Operacion* op, bool esEntrada);
  void mostrarSaldo();
  Plaza* getPlaza() const;
};