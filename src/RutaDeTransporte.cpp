#include "../include/RutaDeTransporte.h"
#include "../include/Excepciones.h"

RutaDeTransporte::RutaDeTransporte(const std::string& id, EmpresaTransportadora* transportadora, Vehiculo* vehiculo)
  : idRuta(id), estado(EstadoRuta::PLANIFICADA), transportadora(transportadora), vehiculo(vehiculo), proximaParadaIndex(0) {}

void RutaDeTransporte::agregarParada(std::unique_ptr<Operacion> operacion) {
  if (operacion) {
    paradas.push_back(std::move(operacion));
  }
}

void RutaDeTransporte::ejecutarSiguienteParada() {
  if (estado != EstadoRuta::EN_CURSO) {
    estado = EstadoRuta::EN_CURSO;
  }
  if (proximaParadaIndex >= paradas.size()) {
    estado = EstadoRuta::COMPLETADA;
    throw BovedaException("La ruta ya ha sido completada. No hay mas paradas.");
  }

  paradas[proximaParadaIndex]->ejecutar();
  proximaParadaIndex++;

  if (proximaParadaIndex >= paradas.size()) {
    estado = EstadoRuta::COMPLETADA;
  }
}
