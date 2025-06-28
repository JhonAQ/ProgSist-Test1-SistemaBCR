CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -I$(INC_DIR)
LDFLAGS =

# Project directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin
DATA_DIR = data
REPORT_DIR = reports
TEST_DIR = test

# Project files
# Ahora SOURCES incluye todos los .cpp dentro de SRC_DIR, incluyendo src/main.cpp
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
# Convierte las rutas de los archivos fuente a rutas de archivos objeto
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))
EXECUTABLE = $(BIN_DIR)/gestor_bovedas


# Target por defecto
all: $(EXECUTABLE)

# Regla para enlazar los archivos objeto y crear el ejecutable
$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)
	@echo "Ejecutable '$@' creado exitosamente."

# Regla general para compilar un archivo .cpp a un .o
# Esta regla ahora es suficiente para todos los archivos .cpp en SRC_DIR, incluyendo main.cpp
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Target para ejecutar el programa
run: all
	@echo "--- Ejecutando el Sistema de Gestión de Bóvedas ---"
	./$(EXECUTABLE)
	@echo "--- Fin de la ejecución ---"

# Target para limpiar los archivos generados
clean:
	@echo "Limpiando archivos generados..."
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@mkdir -p $(REPORT_DIR) # Asegura que el directorio de reportes exista
	rm -f $(REPORT_DIR)/* # Elimina solo los archivos dentro de reports, no el directorio

# Target placeholder para pruebas
test:
	@echo "Funcionalidad de pruebas no implementada en este Makefile."

# Crea directorios necesarios
setup:
	@mkdir -p $(INC_DIR) $(SRC_DIR) $(TEST_DIR) $(DATA_DIR) $(REPORT_DIR) $(BIN_DIR) $(OBJ_DIR)

.PHONY: all clean run test setup
