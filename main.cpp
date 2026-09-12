#include <iostream>
#include <cmath>

// Función que ejecuta las 4 operaciones básicas
double procesarOperacion(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b != 0) {
                return a / b;
            } else {
                std::cout << "\n[Error] No se puede dividir entre cero.\n";
                return 0;
            }
        default:
            std::cout << "\n[Error] Operacion no valida.\n";
            return 0;
    }
}

int main() {
    int opcion = 0;

    while (opcion != 3) {
        std::cout << "\n====================================\n";
        std::cout << "  Calculadora Cientifica (Consola)  \n";
        std::cout << "====================================\n";
        std::cout << "1. Operaciones basicas (+, -, *, /)\n";
        std::cout << "2. Evaluar expresion (Proximamente)\n";
        std::cout << "3. Salir\n";
        std::cout << "Selecciona una opcion: ";

        std::cin >> opcion;

        if (opcion == 1) {
            double a, b;
            char op;

            std::cout << "Ingresa el primer numero (max 5 cifras): ";
            std::cin >> a;

            // Validar límite de 5 cifras
            if (std::abs(a) > 99999) {
                std::cout << "[Advertencia] El numero supera el limite de 5 cifras (99999).\n";
            }

            std::cout << "Ingresa la operacion (+, -, *, /): ";
            std::cin >> op;

            std::cout << "Ingresa el segundo numero (max 5 cifras): ";
            std::cin >> b;

            if (std::abs(b) > 99999) {
                std::cout << "[Advertencia] El numero supera el limite de 5 cifras (99999).\n";
            }

            double resultado = procesarOperacion(a, b, op);
            std::cout << "Resultado: " << resultado << std::endl;

        } else if (opcion == 2) {
            std::cout << "\n[Info] La evaluacion de expresiones complejas se desarrollara en la siguiente fase.\n";
        } else if (opcion == 3) {
            std::cout << "\nSaliendo del programa... Hasta luego!\n";
        } else {
            std::cout << "\nOpcion no valida. Intenta de nuevo.\n";
        }
    }

    return 0;
}