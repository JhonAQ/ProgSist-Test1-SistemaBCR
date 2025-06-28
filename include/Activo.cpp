#pragma once
#include "enums.h"
#include <string>
#include <map>

class Activo {
protected:
  std::string idActivo;
  std::string descripcion;
  double equivalenciaMonetaria;
  TipoMoneda monedaEquivalencia;
public:
  virtual ~Activo() = default;
  virtual void print() const = 0;
  double getEquivalencia() const { return equivalenciaMonetaria; }
};

class ValorMonetario : public Activo {
private:
  std::map<Denominacion, int> desglose;
public:
  ValorMonetario(double valor, TipoMoneda moneda, std::map<Denominacion, int> desg);
  void print() const override;
};

class ValorNoMonetario : public Activo {
private:
  TipoActivoNoMonetario tipo;
  double cantidad;
  std::string unidadDeMedida;
public:
  ValorNoMonetario(TipoActivoNoMonetario tipo, double valor, TipoMoneda moneda, double cant, std::string unidad);
  void print() const override;
};
