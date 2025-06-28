#pragma once

enum class TipoOperacion { TraspasoInterno, TransferenciaInterbancaria, OperacionBCRP };
enum class EstadoRuta { PLANIFICADA, EN_CURSO, COMPLETADA, CANCELADA };
enum class EstadoOperacion { PENDIENTE_ASIGNACION, PROGRAMADA, COMPLETADA, CANCELADA };
enum class TipoMoneda { PEN, USD };
enum class Denominacion { B_200, B_100, B_50, B_20, B_10 };
enum class TipoActivoNoMonetario { BONOS, JOYAS, DOCUMENTOS_VALORADOS };
