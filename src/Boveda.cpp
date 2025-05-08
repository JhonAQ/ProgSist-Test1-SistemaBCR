#include "Boveda.h"
#include "PatrimonioMonetario.h"
#include "PatrimonioBienes.h"
#include <iostream>

Boveda::Boveda(Plaza* plaza) : plaza(plaza) {}

Boveda::~Boveda() {
  for (auto& [key, patrimonio] : inventario) {
    delete patrimonio;
  }
  inventario.clear();
}

void Boveda::actualizarSaldo(Operacion* op, bool esEntrada) {
  for (const auto& patrimonio : op->getPatrimonios()) {
    std::string clave = patrimonio->getDescripcion();
    
    if (inventario.find(clave) == inventario.end()) {
      inventario[clave] = patrimonio->clonar();
    } else {
      int cantidadActual = inventario[clave]->getCantidad();
      int cambio = patrimonio->getCantidad();
      
      if (esEntrada) {
        inventario[clave]->setCantidad(cantidadActual + cambio);
      } else {
        inventario[clave]->setCantidad(cantidadActual - cambio);
      }
    }
  }
}

void Boveda::mostrarSaldo() {
  std::cout << "Saldo en boveda de plaza " << plaza->getNombre() << ":\n";
  
  std::cout << "-- Monedas --\n";
  for (const auto& [clave, patrimonio] : inventario) {
    const PatrimonioMonetario* moneda = dynamic_cast<const PatrimonioMonetario*>(patrimonio);
    if (moneda) {
      std::cout << "  " << moneda->getDescripcion() << ": " 
                << moneda->getCantidad() << " unidades ("
                << moneda->calcularValor() << " " << moneda->getTipoMoneda() << ")\n";
    }
  }
  
  std::cout << "-- Bienes --\n";
  for (const auto& [clave, patrimonio] : inventario) {
    const PatrimonioBienes* bien = dynamic_cast<const PatrimonioBienes*>(patrimonio);
    if (bien) {
      std::cout << "  " << bien->getDescripcion() << ": " 
                << bien->getCantidad() << " unidades ("
                << bien->calcularValor() << " valor estimado)\n";
    }
  }
}

Plaza* Boveda::getPlaza() const {
  return plaza;
}