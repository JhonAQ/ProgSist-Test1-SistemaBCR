#include "Boveda.h"
#include <iostream>

Boveda::Boveda(const std::string& id, const std::string& entidad) 
    : id(id), entidadBancaria(entidad), activa(true) {
    if (id.empty() || entidad.empty()) {
        throw DatosInvalidosException("ID de bóveda y entidad bancaria no pueden estar vacíos");
    }
}

void Boveda::depositar(const std::string& tipoActivo, double cantidad) {
    if (!activa) {
        throw OperacionInvalidaException("No se puede depositar en una bóveda inactiva");
    }
    
    if (cantidad <= 0) {
        throw DatosInvalidosException("La cantidad a depositar debe ser positiva");
    }
    
    if (tipoActivo.empty()) {
        throw DatosInvalidosException("El tipo de activo no puede estar vacío");
    }
    
    activos[tipoActivo] += cantidad;
    std::cout << "Depositado: " << cantidad << " de " << tipoActivo << " en bóveda " << id << std::endl;
}

void Boveda::retirar(const std::string& tipoActivo, double cantidad) {
    if (!activa) {
        throw OperacionInvalidaException("No se puede retirar de una bóveda inactiva");
    }
    
    if (cantidad <= 0) {
        throw DatosInvalidosException("La cantidad a retirar debe ser positiva");
    }
    
    if (activos.find(tipoActivo) == activos.end()) {
        throw ActivoNoDisponibleException("El tipo de activo '" + tipoActivo + "' no existe en la bóveda");
    }
    
    if (activos[tipoActivo] < cantidad) {
        throw SaldoInsuficienteException("Saldo insuficiente. Disponible: " + 
            std::to_string(activos[tipoActivo]) + ", solicitado: " + std::to_string(cantidad));
    }
    
    activos[tipoActivo] -= cantidad;
    std::cout << "Retirado: " << cantidad << " de " << tipoActivo << " de bóveda " << id << std::endl;
}

void Boveda::transferir(Boveda& destino, const std::string& tipoActivo, double cantidad) {
    if (this->id == destino.getId()) {
        throw OperacionInvalidaException("No se puede transferir a la misma bóveda");
    }
    
    // Validar que la bóveda destino existe y está activa
    if (!destino.estaActiva()) {
        throw BovedaNoEncontradaException("La bóveda destino no está activa");
    }
    
    // Retirar de origen (esto valida saldo y otros requisitos)
    this->retirar(tipoActivo, cantidad);
    
    try {
        // Depositar en destino
        destino.depositar(tipoActivo, cantidad);
        std::cout << "Transferencia exitosa de " << cantidad << " " << tipoActivo 
                  << " desde " << this->id << " hacia " << destino.getId() << std::endl;
    } catch (const BovedaException& e) {
        // Si falla el depósito, revertir el retiro
        this->depositar(tipoActivo, cantidad);
        throw OperacionInvalidaException("Error en transferencia: " + std::string(e.what()));
    }
}

double Boveda::consultarSaldo(const std::string& tipoActivo) const {
    auto it = activos.find(tipoActivo);
    if (it == activos.end()) {
        return 0.0;
    }
    return it->second;
}
