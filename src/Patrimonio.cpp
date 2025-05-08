#include "Patrimonio.h"

Patrimonio::Patrimonio(int cantidad, const std::string& descripcion)
    : cantidad(cantidad), descripcion(descripcion) {}

int Patrimonio::getCantidad() const {
    return cantidad;
}

void Patrimonio::setCantidad(int cantidad) {
    this->cantidad = cantidad;
}

std::string Patrimonio::getDescripcion() const {
    return descripcion;
}