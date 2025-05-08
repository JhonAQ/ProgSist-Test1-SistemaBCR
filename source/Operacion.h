#pragma once
#include <string>
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

  int billetes_200, billetes_100, billetes_50, billetes_10, billetes_5;
  int bonos, joyas;

public:
  Operacion(string fecha, string tipo,
            EntidadBancaria* origen, EntidadBancaria* destino,
            Transportadora* transportadora, Plaza* plaza,
            int b200, int b100, int b50, int b10, int b5,
            int bonos, int joyas);

  int calcularMontoTotal() const;
  void aplicar();
  string getFecha() const;
  int getBilletes(int valor) const;
  int getBonos() const;
  int getJoyas() const;
  Plaza* getPlaza() const;
};