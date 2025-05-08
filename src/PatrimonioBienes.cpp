#include "PatrimonioBienes.h"

PatrimonioBienes::PatrimonioBienes(int cantidad, const std::string& descripcion,
                                  const std::string& tipoBien, double valorUnitario)
    : Patrimonio(cantidad, descripcion), tipoBien(tipoBien), valorUnitario(valorUnitario) {}

double PatrimonioBienes::calcularValor() const {
    return cantidad * valorUnitario;
}

Patrimonio* PatrimonioBienes::clonar() const {
    return new PatrimonioBienes(*this);
}

std::string PatrimonioBienes::getTipoBien() const {
    return tipoBien;
}

double PatrimonioBienes::getValorUnitario() const {
    return valorUnitario;
}