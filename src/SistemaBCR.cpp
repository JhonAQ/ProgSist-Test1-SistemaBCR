#include "SistemaBCR.h"
#include <iostream>
#include <map>
#include "Operacion.h"
#include "PatrimonioMonetario.h"
#include "PatrimonioBienes.h"

void SistemaBCR::registrarOperacion(Operacion* op) {
  operaciones.push_back(op);
}

void SistemaBCR::calcularSaldoBCR(string fecha) {
  double total = 0.0;
  for (Operacion* op : operaciones) {
    if (op->getFecha() == fecha)
      total += op->calcularMontoTotal();
  }
  cout << "Saldo total del BCR en la fecha " << fecha << ": " << total << " soles\n";
}

void SistemaBCR::mostrarInformePorTipoMonedaYBien(string fecha) {
  map<double, int> billetesSoles;
  map<string, int> bienes;

  for (Operacion* op : operaciones) {
    if (op->getFecha() != fecha) continue;
    
    for (const auto& patrimonio : op->getPatrimonios()) {
      const PatrimonioMonetario* moneda = dynamic_cast<const PatrimonioMonetario*>(patrimonio);
      if (moneda && moneda->getTipoMoneda() == "soles") {
        billetesSoles[moneda->getDenominacion()] += moneda->getCantidad();
        continue;
      }
      
      const PatrimonioBienes* bien = dynamic_cast<const PatrimonioBienes*>(patrimonio);
      if (bien) {
        bienes[bien->getTipoBien()] += bien->getCantidad();
      }
    }
  }

  cout << "===== INFORME BCR - " << fecha << " =====\n";
  cout << "-> Billetes:\n";
  for (const auto& [denominacion, cantidad] : billetesSoles) {
    cout << "   " << denominacion << ": " << cantidad << " unidades\n";
  }
  cout << "-> Bienes:\n";
  for (const auto& [tipo, cantidad] : bienes) {
    cout << "   " << tipo << ": " << cantidad << " unidades\n";
  }
}