#include "PatrimonioMonetario.h"

PatrimonioMonetario::PatrimonioMonetario(int cantidad, const std::string& descripcion,
                                        const std::string& tipoMoneda, double denominacion)
    : Patrimonio(cantidad, descripcion), tipoMoneda(tipoMoneda), denominacion(denominacion) {}

double PatrimonioMonetario::calcularValor() const {
    return cantidad * denominacion;
}

Patrimonio* PatrimonioMonetario::clonar() const {
    return new PatrimonioMonetario(*this);
}

std::string PatrimonioMonetario::getTipoMoneda() const {
    return tipoMoneda;
}

double PatrimonioMonetario::getDenominacion() const {
    return denominacion;
}