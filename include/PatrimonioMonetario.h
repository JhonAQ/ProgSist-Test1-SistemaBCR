#pragma once
#include "Patrimonio.h"

class PatrimonioMonetario : public Patrimonio {
private:
    std::string tipoMoneda;
    double denominacion;

public:
    PatrimonioMonetario(int cantidad, const std::string& descripcion, 
                        const std::string& tipoMoneda, double denominacion);
    
    double calcularValor() const override;
    Patrimonio* clonar() const override;
    
    std::string getTipoMoneda() const;
    double getDenominacion() const;
};