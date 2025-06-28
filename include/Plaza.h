#pragma once

#include <string>

class Plaza {
public:
  Plaza(const std::string& id, const std::string& ciudad);
  const std::string& obtenerId() const { return idPlaza; }
  const std::string& obtenerNombre() const { return nombreCiudad; }

private:
  std::string idPlaza;
  std::string nombreCiudad;
};
