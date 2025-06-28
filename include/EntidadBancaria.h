#pragma once
#include <string>
#include <vector>
#include "Boveda.h"

using namespace std;

class EntidadBancaria {
  string nombre;
  vector<Boveda*> bovedas;

public:
  EntidadBancaria(string nombre);
  Boveda* getBovedaPorPlaza(string nombrePlaza);
  void agregarOperacion(Operacion* op, bool esEntrada);
  void agregarBoveda(Boveda* boveda);
};
