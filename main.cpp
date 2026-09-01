#include <iostream>

int main() {
    int opcion = 0;

    while (opcion != 3) {
        std::cout << "\n====================================\n";
        std::cout << "  Calculadora Cientifica (Consola)  \n";
        std::cout << "====================================\n";
        std::cout << "1. Operacion basica (Suma)\n";
        std::cout << "2. Evaluar expresion (Proximamente)\n";
        std::cout << "3. Salir\n";
        std::cout << "Selecciona una opcion: ";
        
        std::cin >> opcion;

        if (opcion == 1) {
            double a, b;
            std::cout << "Ingresa el primer numero: ";
            std::cin >> a;
            std::cout << "Ingresa el segundo numero: ";
            std::cin >> b;
            std::cout << "Resultado: " << (a + b) << std::endl;
        } else if (opcion == 2) {
            std::cout << "\n[Info] La evaluacion de expresiones complejas se desarrollara en la siguiente fase.\n";
        } else if (opcion == 3) {
            std::cout << "\n¡Saliendo del programa... Hasta luego!\n";
        } else {
            std::cout << "\nOpcion no valida. Intenta de nuevo.\n";
        }
    }

    return 0;
}