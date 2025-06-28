CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -Iinclude -Iutils
LDFLAGS =

# Directorios del proyecto
SRC_DIR = src
UTIL_DIR = utils
OBJ_DIR = obj
BIN_DIR = bin
DATA_DIR = data
REPORT_DIR = reports
TEST_DIR = test

# Archivos fuente (.cpp)
SRCS = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(UTIL_DIR)/*.cpp)

# Archivos objeto (.o)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(filter $(SRC_DIR)/%.cpp, $(SRCS))) \
       $(patsubst $(UTIL_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(filter $(UTIL_DIR)/%.cpp, $(SRCS)))

# Nombre del ejecutable
EXECUTABLE = $(BIN_DIR)/gestor_bovedas

# --- Targets ---

# Construir el ejecutable
all: setup $(EXECUTABLE)

# Regla de enlazado
$(EXECUTABLE): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)
	@echo "Ejecutable '$@' creado."

# Regla de compilacion para src/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla de compilacion para utils/
$(OBJ_DIR)/%.o: $(UTIL_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ejecutar el programa
run: all
	@echo "--- Ejecutando el Sistema de Gestion de Bovedas ---"
	./$(EXECUTABLE)
	@echo "--- Fin de la ejecucion ---"

# Limpiar archivos de compilacion
clean:
	@echo "Limpiando archivos de compilacion..."
	@rm -rf $(OBJ_DIR) $(BIN_DIR)

# Limpiar todo (incluyendo reportes)
clean-all: clean
	@echo "Limpiando reportes..."
	@mkdir -p $(REPORT_DIR)
	@rm -f $(REPORT_DIR)/*

# Crear estructura de directorios
setup:
	@mkdir -p $(INC_DIR) $(SRC_DIR) $(UTIL_DIR) $(TEST_DIR) $(DATA_DIR) $(REPORT_DIR) $(BIN_DIR) $(OBJ_DIR)

.PHONY: all clean clean-all run setup
