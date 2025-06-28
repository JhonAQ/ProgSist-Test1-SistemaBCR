#pragma once
#include "Patrimonio.h"

class PatrimonioBienes : public Patrimonio {
private:
    std::string tipoBien;
    double valorUnitario;

public:
    PatrimonioBienes(int cantidad, const std::string& descripcion,
                    const std::string& tipoBien, double valorUnitario);
    
    double calcularValor() const override;
    Patrimonio* clonar() const override;
    
    std::string getTipoBien() const;
    double getValorUnitario() const;
};