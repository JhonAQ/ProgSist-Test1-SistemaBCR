#pragma once
#include <string>
#include <vector>
#include "Patrimonio.h"

using namespace std;

class EntidadBancaria;
class Transportadora;
class Plaza;

class Operacion {
private:
  string fecha;
  string tipo;
  EntidadBancaria* origen;
  EntidadBancaria* destino;
  Transportadora* transportadora;
  Plaza* plaza;
  
  vector<Patrimonio*> patrimonios;

public:
  Operacion(string fecha, string tipo,
            EntidadBancaria* origen, EntidadBancaria* destino,
            Transportadora* transportadora, Plaza* plaza);
  
  ~Operacion();
  
  void agregarPatrimonio(Patrimonio* patrimonio);
  double calcularMontoTotal() const;
  void aplicar();
  
  string getFecha() const;
  const vector<Patrimonio*>& getPatrimonios() const;
  Plaza* getPlaza() const;
};