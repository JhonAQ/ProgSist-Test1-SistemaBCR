#pragma once

// Define los tipos de operaciones principales que se pueden realizar.
enum class TipoOperacion {
  TraspasoInterno,
  TransferenciaInterbancaria,
  OperacionBCRP
};

// Define los estados posibles para una ruta de transporte.
enum class EstadoRuta {
  PLANIFICADA,
  EN_CURSO,
  COMPLETADA,
  CANCELADA
};

// Define los estados posibles para una operación individual (una parada en la ruta).
enum class EstadoOperacion {
  PENDIENTE_ASIGNACION,
  PROGRAMADA,
  COMPLETADA,
  CANCELADA
};

// Define las monedas soportadas por el sistema.
enum class TipoMoneda {
  PEN, // Sol Peruano
  USD  // Dólar Americano
};

// Define las denominaciones de billetes para activos monetarios.
enum class Denominacion {
  B_200, B_100, B_50, B_20, B_10
};

// Define los tipos de activos no monetarios que se pueden gestionar.
enum class TipoActivoNoMonetario {
  BONOS,
  JOYAS,
  DOCUMENTOS_VALORADOS
};
