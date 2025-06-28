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
SOURCES = $(wildcard $(SRC_DIR)/*.cpp) main.cpp
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(filter $(SRC_DIR)/%.cpp,$(SOURCES))) \
          $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(filter %.cpp,$(SOURCES)))
EXECUTABLE = $(BIN_DIR)/gestor_bovedas


# Target por defecto
all: $(EXECUTABLE)
$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)
	@echo "Ejecutable '$@' creado exitosamente."

# Target para compilar un .cpp a un .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Target especial para main.cpp
$(OBJ_DIR)/main.o: main.cpp
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
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(REPORT_DIR)/*

# Target placeholder para pruebas
test:
	@echo "Funcionalidad de pruebas no implementada en este Makefile."

# Crea directorios necesarios
setup:
	@mkdir -p $(INC_DIR) $(SRC_DIR) $(TEST_DIR) $(DATA_DIR) $(REPORT_DIR) $(BIN_DIR) $(OBJ_DIR)

.PHONY: all clean run test setup
