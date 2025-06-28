#pragma once
#include <string>

class Patrimonio {
protected:
    int cantidad;
    std::string descripcion;

public:
    Patrimonio(int cantidad, const std::string& descripcion);
    virtual ~Patrimonio() = default;
    
    virtual double calcularValor() const = 0;
    virtual Patrimonio* clonar() const = 0;
    
    int getCantidad() const;
    void setCantidad(int cantidad);
    std::string getDescripcion() const;
};