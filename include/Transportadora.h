#pragma once
#include <string>
#include <vector>
#include "Boveda.h"

using namespace std;

class Transportadora {
  string nombre;
  vector<Operacion*> historial;

public:
  Transportadora(string nombre);
  void registrarOperacion(Operacion* op);
};
