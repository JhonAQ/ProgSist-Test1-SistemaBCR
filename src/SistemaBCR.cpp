#include "SistemaBCR.h"

#include <iostream>
#include <map>

#include "Operacion.h"

void SistemaBCR::registrarOperacion(Operacion* op) {
  operaciones.push_back(op);
}

void SistemaBCR::calcularSaldoBCR(string fecha) {
  int total = 0;
  for (Operacion* op : operaciones) {
    if (op->getFecha() == fecha)
      total += op->calcularMontoTotal();
  }
  cout << "Saldo total del BCR en la fecha " << fecha << ": " << total << " soles\n";
}

void SistemaBCR::mostrarInformePorTipoMonedaYBien(string fecha) {
  map<int, int> billetes;
  int totalBonos = 0, totalJoyas = 0;

  for (Operacion* op : operaciones) {
    if (op->getFecha() != fecha) continue;
    for (int d : {200, 100, 50, 10, 5}) {
      billetes[d] += op->getBilletes(d);
    }
    totalBonos += op->getBonos();
    totalJoyas += op->getJoyas();
  }

  cout << "===== INFORME BCR - " << fecha << " =====\n";
  cout << "-> Billetes:\n";
  for (int d : {200, 100, 50, 10, 5}) {
    cout << "   " << d << ": " << billetes[d] << " unidades\n";
  }
  cout << "-> Bienes:\n";
  cout << "   Bonos : " << totalBonos << " unidades\n";
  cout << "   Joyas : " << totalJoyas << " unidades\n";
}
