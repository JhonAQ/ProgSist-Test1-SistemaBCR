#include <iostream>  // Para std::cout, std::cerr
#include <string>    // Para std::string
#include <stdexcept> // Para std::runtime_error, la base de nuestras excepciones

// --- 1. Clase Base de Excepción para el Sistema Bóveda ---
// Todas nuestras excepciones personalizadas heredarán de esta.
// A su vez, BovedaException hereda de std::runtime_error para integrarse
// con el ecosistema de excepciones estándar de C++.
class BovedaException : public std::runtime_error {
public:
    // Constructor que toma un mensaje de error y lo pasa a std::runtime_error
    explicit BovedaException(const std::string& message)
        : std::runtime_error(message) {
        // Opcional: Podrías añadir lógica de logueo aquí para todas las excepciones del sistema
        // std::cerr << "LOG: BovedaException base lanzada: " << message << std::endl;
    }
};

// --- 2. Clases de Excepción Específicas ---

// 2.1 Excepciones relacionadas con el estado y los fondos
class SaldoInsuficienteException : public BovedaException {
public:
    explicit SaldoInsuficienteException(const std::string& message = "Error de fondos: Saldo insuficiente en la bóveda de origen.")
        : BovedaException(message) {}
};

class ActivoNoDisponibleException : public BovedaException {
public:
    explicit ActivoNoDisponibleException(const std::string& message = "Error de activo: El tipo de activo solicitado no está disponible o es insuficiente.")
        : BovedaException(message) {}
};

// 2.2 Excepciones relacionadas con la validación de datos y la lógica de negocio
class OperacionInvalidaException : public BovedaException {
public:
    explicit OperacionInvalidaException(const std::string& message = "Error de operación: La operación es inválida debido a reglas de negocio o estado.")
        : BovedaException(message) {}
};

class TipoOperacionNoSoportadoException : public BovedaException {
public:
    explicit TipoOperacionNoSoportadoException(const std::string& message = "Error de tipo: El tipo de operación especificado no es soportado.")
        : BovedaException(message) {}
};

class DatosInvalidosException : public BovedaException {
public:
    explicit DatosInvalidosException(const std::string& message = "Error de datos: Los datos de entrada son inválidos o tienen formato incorrecto.")
        : BovedaException(message) {}
};

// 2.3 Excepciones relacionadas con la disponibilidad y existencia de entidades
class BovedaNoEncontradaException : public BovedaException {
public:
    explicit BovedaNoEncontradaException(const std::string& message = "Error de entidad: La bóveda especificada no fue encontrada.")
        : BovedaException(message) {}
};

class EntidadBancariaNoEncontradaException : public BovedaException {
public:
    explicit EntidadBancariaNoEncontradaException(const std::string& message = "Error de entidad: La entidad bancaria especificada no fue encontrada.")
        : BovedaException(message) {}
};

class TransportadoraNoDisponibleException : public BovedaException {
public:
    explicit TransportadoraNoDisponibleException(const std::string& message = "Error de servicio: La transportadora no está disponible o no cubre la zona.")
        : BovedaException(message) {}
};

// 2.4 Excepciones de sistema/internas
class ConfiguracionInvalidaException : public BovedaException {
public:
    explicit ConfiguracionInvalidaException(const std::string& message = "Error de configuración: El sistema no está configurado correctamente.")
        : BovedaException(message) {}
};

class ErrorInternoSistemaException : public BovedaException {
public:
    explicit ErrorInternoSistemaException(const std::string& message = "Error interno: Se ha producido un fallo inesperado en el sistema.")
        : BovedaException(message) {}
};


// --- Función de ejemplo para simular una operación de transferencia ---
// Esta función podría estar dentro de una clase como SistemaGestionBovedas
void simularTransferencia(double monto, double saldoBovedaOrigen, bool bovedaDestinoExiste, bool transportadoraHabilitada, int tipoOperacion) {
    if (monto <= 0) {
        throw DatosInvalidosException("El monto de la transferencia debe ser positivo.");
    }
    if (monto > saldoBovedaOrigen) {
        throw SaldoInsuficienteException("El monto " + std::to_string(monto) + " excede el saldo disponible de " + std::to_string(saldoBovedaOrigen) + ".");
    }
    if (!bovedaDestinoExiste) {
        throw BovedaNoEncontradaException("La bóveda de destino especificada no existe.");
    }
    if (!transportadoraHabilitada) {
        throw TransportadoraNoDisponibleException("La transportadora no puede realizar el servicio en este momento.");
    }
    if (tipoOperacion == 99) { // Un tipo de operación ficticio no soportado
        throw TipoOperacionNoSoportadoException("El tipo de operación 99 no está definido para transferencias.");
    }
    if (tipoOperacion == 10 && monto > 1000000) { // Ejemplo de regla de negocio "OperacionInvalida"
        throw OperacionInvalidaException("Transferencias internas de más de 1,000,000 requieren aprobación especial.");
    }

    std::cout << "Transferencia de " << monto << " realizada exitosamente." << std::endl;
}


// --- Función Principal (main) para Demostrar el Manejo ---
int main() {
    std::cout << "--- Demostración del Manejo de Excepciones del Sistema Bóveda ---" << std::endl;

    // --- Escenario 1: Saldo Insuficiente ---
    std::cout << "\n--- Escenario 1: Saldo Insuficiente ---" << std::endl;
    try {
        simularTransferencia(1500.0, 1000.0, true, true, 1); // Monto > Saldo
    } catch (const SaldoInsuficienteException& e) {
        std::cerr << "Capturado SaldoInsuficienteException: " << e.what() << std::endl;
    } catch (const BovedaException& e) {
        std::cerr << "Capturado BovedaException (genérico): " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Capturado std::exception (muy genérico): " << e.what() << std::endl;
    }

    // --- Escenario 2: Bóveda No Encontrada ---
    std::cout << "\n--- Escenario 2: Bóveda No Encontrada ---" << std::endl;
    try {
        simularTransferencia(500.0, 1000.0, false, true, 1); // Bóveda destino no existe
    } catch (const BovedaNoEncontradaException& e) {
        std::cerr << "Capturado BovedaNoEncontradaException: " << e.what() << std::endl;
    } catch (const BovedaException& e) {
        std::cerr << "Capturado BovedaException (genérico): " << e.what() << std::endl;
    }

    // --- Escenario 3: Transportadora No Disponible ---
    std::cout << "\n--- Escenario 3: Transportadora No Disponible ---" << std::endl;
    try {
        simularTransferencia(500.0, 1000.0, true, false, 1); // Transportadora no habilitada
    } catch (const TransportadoraNoDisponibleException& e) {
        std::cerr << "Capturado TransportadoraNoDisponibleException: " << e.what() << std::endl;
    } catch (const BovedaException& e) {
        std::cerr << "Capturado BovedaException (genérico): " << e.what() << std::endl;
    }

    // --- Escenario 4: Tipo de Operación No Soportado ---
    std::cout << "\n--- Escenario 4: Tipo de Operación No Soportado ---" << std::endl;
    try {
        simularTransferencia(500.0, 1000.0, true, true, 99); // Tipo de operación no soportado
    } catch (const TipoOperacionNoSoportadoException& e) {
        std::cerr << "Capturado TipoOperacionNoSoportadoException: " << e.what() << std::endl;
    } catch (const BovedaException& e) {
        std::cerr << "Capturado BovedaException (genérico): " << e.what() << std::endl;
    }

    // --- Escenario 5: Operación Válida ---
    std::cout << "\n--- Escenario 5: Operación Válida ---" << std::endl;
    try {
        simularTransferencia(500.0, 1000.0, true, true, 1);
    } catch (const BovedaException& e) {
        // Este catch no debería activarse en un escenario válido
        std::cerr << "ERROR INESPERADO en escenario válido: " << e.what() << std::endl;
    }

    // --- Escenario 6: Captura Genérica de BovedaException (Ej: DatosInválidos) ---
    std::cout << "\n--- Escenario 6: Captura Genérica de BovedaException (DatosInválidos) ---" << std::endl;
    try {
        simularTransferencia(-100.0, 1000.0, true, true, 1); // Monto negativo
    } catch (const BovedaException& e) { // Se captura con el tipo base
        std::cerr << "Capturado BovedaException (DatosInvalidos): " << e.what() << std::endl;
    }

    // --- Escenario 7: OperaciónInválida (monto alto) ---
    std::cout << "\n--- Escenario 7: Operación Inválida (Monto Alto) ---" << std::endl;
    try {
        simularTransferencia(1500000.0, 2000000.0, true, true, 10); // Tipo 10 con monto alto
    } catch (const OperacionInvalidaException& e) {
        std::cerr << "Capturado OperacionInvalidaException: " << e.what() << std::endl;
    } catch (const BovedaException& e) {
        std::cerr << "Capturado BovedaException (genérico): " << e.what() << std::endl;
    }

    std::cout << "\n--- Fin de la demostración ---" << std::endl;

    return 0;
}