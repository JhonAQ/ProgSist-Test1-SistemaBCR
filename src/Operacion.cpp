#include "../include/Operacion.h"
#include "../include/Boveda.h"
#include "../include/Excepciones.h"
#include "../include/EntidadBancaria.h"

Operacion::Operacion(const std::string& id, Boveda* origen, Boveda* destino)
  : idOperacion(id), estado(EstadoOperacion::PENDIENTE_ASIGNACION), origen(origen), destino(destino) {}

void Operacion::agregarActivo(std::unique_ptr<Activo> activo) {
  if (activo) {
    activosTransferidos.push_back(std::move(activo));
  }
}

void TraspasoInterno::ejecutar() {
  if (origen->obtenerPropietario() != destino->obtenerPropietario()) {
    throw OperacionInvalidaException("Traspaso interno debe ser entre bovedas de la misma entidad.");
  }
  
  // Lógica de transferencia
  for (auto& activo : activosTransferidos) {
    destino->agregarActivo(origen->retirarActivo(activo->obtenerId()));
  }
  this->estado = EstadoOperacion::COMPLETADA;
}

void TransferenciaInterbancaria::ejecutar() {
  if (origen->obtenerPropietario() == destino->obtenerPropietario()) {
    throw OperacionInvalidaException("Transferencia interbancaria debe ser entre bovedas de distintas entidades.");
  }

  for (auto& activo : activosTransferidos) {
    destino->agregarActivo(origen->retirarActivo(activo->obtenerId()));
  }
  this->estado = EstadoOperacion::COMPLETADA;
}

void OperacionBCRP::ejecutar() {
  bool esBCRPOrigen = (dynamic_cast<BovedaBCRP*>(origen) != nullptr);
  bool esBCRPDestino = (dynamic_cast<BovedaBCRP*>(destino) != nullptr);

  if (!esBCRPOrigen && !esBCRPDestino) {
    throw OperacionInvalidaException("Operacion con BCRP debe involucrar una boveda del BCRP.");
  }

  for (auto& activo : activosTransferidos) {
    destino->agregarActivo(origen->retirarActivo(activo->obtenerId()));
  }
  this->estado = EstadoOperacion::COMPLETADA;
}
