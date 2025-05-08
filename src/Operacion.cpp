#include "Operacion.h"

Operacion::Operacion(std::string fecha, std::string tipo,
                     EntidadBancaria* origen, EntidadBancaria* destino,
                     Transportadora* transportadora, Plaza* plaza,
                     int b200, int b100, int b50, int b10, int b5,
                     int bonos, int joyas)
    : fecha(fecha), tipo(tipo), origen(origen), destino(destino),
      transportadora(transportadora), plaza(plaza),
      billetes_200(b200), billetes_100(b100), billetes_50(b50),
      billetes_10(b10), billetes_5(b5), bonos(bonos), joyas(joyas) {}

int Operacion::calcularMontoTotal() const {
  return billetes_200*200 + billetes_100*100 + billetes_50*50 +
          billetes_10*10 + billetes_5*5 + bonos + joyas;
}

void Operacion::aplicar() {
  if (origen) origen->agregarOperacion(this, false);
  if (destino) destino->agregarOperacion(this, true);
  if (transportadora) transportadora->registrarOperacion(this);
}

std::string Operacion::getFecha() const {
  return fecha;
}

int Operacion::getBilletes(int valor) const {
  switch(valor) {
    case 200: return billetes_200;
    case 100: return billetes_100;
    case 50:  return billetes_50;
    case 10:  return billetes_10;
    case 5:   return billetes_5;
    default: return 0;
  }
}

int Operacion::getBonos() const {
  return bonos;
}

int Operacion::getJoyas() const {
  return joyas;
}

Plaza* Operacion::getPlaza() const {
  return plaza;
}
