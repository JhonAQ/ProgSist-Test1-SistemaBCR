#include "Operacion.h"
#include "EntidadBancaria.h"
#include "Plaza.h"
#include "Transportadora.h"

Operacion::Operacion(string fecha, string tipo,
                     EntidadBancaria* origen, EntidadBancaria* destino,
                     Transportadora* transportadora, Plaza* plaza)
    : fecha(fecha), tipo(tipo), origen(origen), destino(destino), 
      transportadora(transportadora), plaza(plaza) {}

Operacion::~Operacion() {
  for (auto patrimonio : patrimonios) {
    delete patrimonio;
  }
  patrimonios.clear();
}

void Operacion::agregarPatrimonio(Patrimonio* patrimonio) {
  patrimonios.push_back(patrimonio);
}

double Operacion::calcularMontoTotal() const {
  double total = 0.0;
  for (const auto& patrimonio : patrimonios) {
    total += patrimonio->calcularValor();
  }
  return total;
}

void Operacion::aplicar() {
  if (origen) origen->agregarOperacion(this, false);
  if (destino) destino->agregarOperacion(this, true);
  if (transportadora) transportadora->registrarOperacion(this);
}

string Operacion::getFecha() const { 
  return fecha; 
}

const vector<Patrimonio*>& Operacion::getPatrimonios() const {
  return patrimonios;
}

Plaza* Operacion::getPlaza() const {
  return plaza;
}