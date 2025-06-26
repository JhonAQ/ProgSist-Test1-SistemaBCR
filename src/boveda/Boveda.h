#ifndef BOVEDA_H
#define BOVEDA_H

#include "../exceptions/exceptionsHandler.h"
#include <string>
#include <map>

class Boveda {
private:
    std::string id;
    std::string entidadBancaria;
    std::map<std::string, double> activos; // tipo_activo -> cantidad
    bool activa;

public:
    Boveda(const std::string& id, const std::string& entidad);
    
    void depositar(const std::string& tipoActivo, double cantidad);
    void retirar(const std::string& tipoActivo, double cantidad);
    void transferir(Boveda& destino, const std::string& tipoActivo, double cantidad);
    
    double consultarSaldo(const std::string& tipoActivo) const;
    bool estaActiva() const { return activa; }
    void setActiva(bool estado) { activa = estado; }
    
    const std::string& getId() const { return id; }
    const std::string& getEntidadBancaria() const { return entidadBancaria; }
};

#endif // BOVEDA_H
