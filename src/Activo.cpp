#include "../include/Activo.h"
#include <iostream>
#include <iomanip>

ValorMonetario::ValorMonetario(const std::string& id, double valor, TipoMoneda moneda, std::map<Denominacion, int> desglose) 
  : desgloseDenominaciones(std::move(desglose)) {
  this->idActivo = id;
  this->valorEquivalente = valor;
  this->monedaEquivalencia = moneda;
  this->descripcion = "Activo Monetario";
}

void ValorMonetario::imprimirDetalles() const {
  std::cout << "  - ID: " << idActivo << " | " << descripcion << " | Valor: " << std::fixed << std::setprecision(2) << valorEquivalente
            << (monedaEquivalencia == TipoMoneda::USD ? " USD" : " PEN") << std::endl;
}

ValorNoMonetario::ValorNoMonetario(const std::string& id, TipoActivoNoMonetario tipo, double valor, TipoMoneda moneda, double cantidad, const std::string& unidad)
  : tipo(tipo), cantidad(cantidad), unidadDeMedida(unidad) {
  this->idActivo = id;
  this->valorEquivalente = valor;
  this->monedaEquivalencia = moneda;
  switch (tipo) {
    case TipoActivoNoMonetario::BONOS: this->descripcion = "Bonos del Tesoro"; break;
    case TipoActivoNoMonetario::JOYAS: this->descripcion = "Joyas (Oro/Plata)"; break;
    case TipoActivoNoMonetario::DOCUMENTOS_VALORADOS: this->descripcion = "Documentos Valorados"; break;
  }
}

void ValorNoMonetario::imprimirDetalles() const {
  std::cout << "  - ID: " << idActivo << " | " << descripcion << " (" << cantidad << " " << unidadDeMedida << ") | Valor Equivalente: " 
            << std::fixed << std::setprecision(2) << valorEquivalente
            << (monedaEquivalencia == TipoMoneda::USD ? " USD" : " PEN") << std::endl;
}
