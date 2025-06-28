#pragma once

#include <string>
#include <map>
#include <vector>
#include <memory>
#include "enums.h"

// Clase base abstracta para cualquier tipo de activo valorado.
// Utiliza polimorfismo para manejar de forma unificada dinero, bonos, joyas, etc.
class Activo {
public:
  virtual ~Activo() = default;

  // Método virtual puro para imprimir los detalles del activo.
  virtual void imprimirDetalles() const = 0;

  double obtenerValorEquivalente() const { return valorEquivalente; }
  TipoMoneda obtenerMonedaEquivalencia() const { return monedaEquivalencia; }
  const std::string& obtenerId() const { return idActivo; }

protected:
  std::string idActivo;
  std::string descripcion;
  double valorEquivalente;
  TipoMoneda monedaEquivalencia;
};

// Especialización para activos monetarios (dinero en efectivo).
class ValorMonetario : public Activo {
public:
  ValorMonetario(const std::string& id, double valor, TipoMoneda moneda, std::map<Denominacion, int> desglose);
  void imprimirDetalles() const override;

private:
  std::map<Denominacion, int> desgloseDenominaciones;
};

// Especialización para activos no monetarios.
class ValorNoMonetario : public Activo {
public:
  ValorNoMonetario(const std::string& id, TipoActivoNoMonetario tipo, double valor, TipoMoneda moneda, double cantidad, const std::string& unidad);
  void imprimirDetalles() const override;

private:
  TipoActivoNoMonetario tipo;
  double cantidad;
  std::string unidadDeMedida;
};
