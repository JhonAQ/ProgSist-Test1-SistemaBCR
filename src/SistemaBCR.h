#pragma once
#include <vector>
#include <string>
using namespace std;

class Operacion;

class SistemaBCR {
private:
  vector<Operacion*> operaciones;
  // vector<Operacion*> operaciones;

public:
  void registrarOperacion(Operacion* op);
  void calcularSaldoBCR(string fecha);
  void mostrarInformePorTipoMonedaYBien(string fecha);
};
