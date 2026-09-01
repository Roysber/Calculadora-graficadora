# Variables de compilación
CXX = g++
CXXFLAGS = -Wall -std=c++17
TARGET = calculadora.exe
SRC = main.cpp

# Regla principal (se ejecuta por defecto con 'make')
all: $(TARGET)

# Compilación del ejecutable
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Regla para compilar y ejecutar de una vez
run: $(TARGET)
	./$(TARGET)

# Regla para limpiar los ejecutables generados
clean:
	rm -f $(TARGET) app.exe prueba.exe *.o

.PHONY: all run clean