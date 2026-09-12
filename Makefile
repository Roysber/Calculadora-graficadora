# Variables de compilacion
CXX = g++
CXXFLAGS = -Wall -std=c++17
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
TARGET = calculadora.exe
SRC = main.cpp

# Regla principal
all: $(TARGET)

# Compilacion del ejecutable
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LIBS)

# Regla para ejecutar
run: $(TARGET)
	./$(TARGET)

# Regla para limpiar los ejecutables
clean:
	rm -f $(TARGET)

.PHONY: all run clean