#pragma once

#include <stdexcept>
#include <string>

class BovedaException : public std::runtime_error {
public:
  explicit BovedaException(const std::string& message) : std::runtime_error(message) {}
};

// --- Jerarquía de Excepciones ---

class ReglaNegocioException : public BovedaException {
public:
  using BovedaException::BovedaException;
};

class SaldoInsuficienteException : public ReglaNegocioException {
public:
  SaldoInsuficienteException() : ReglaNegocioException("Saldo insuficiente para la operacion.") {}
};

class ActivoNoEncontradoException : public ReglaNegocioException {
public:
  ActivoNoEncontradoException() : ReglaNegocioException("El activo especificado no se encontro en la boveda.") {}
};

class OperacionInvalidaException : public ReglaNegocioException {
public:
  explicit OperacionInvalidaException(const std::string& reason) : ReglaNegocioException("Operacion invalida: " + reason) {}
};


class ValidacionException : public BovedaException {
public:
  using BovedaException::BovedaException;
};

class RecursoNoEncontradoException : public ValidacionException {
public:
  explicit RecursoNoEncontradoException(const std::string& resource) : ValidacionException("Recurso no encontrado: " + resource) {}
};
