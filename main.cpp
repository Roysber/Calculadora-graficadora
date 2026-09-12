#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <sstream>
#include <cmath>

// Estructura para representar un botón de la calculadora
struct Boton {
    sf::RectangleShape forma;
    std::unique_ptr<sf::Text> texto;
    std::string valor;
};

// Función para evaluar expresiones simples encadenadas (ej. "3+3+3+3")
double evaluarExpresion(const std::string& expr) {
    std::stringstream ss(expr);
    double acumulado = 0;
    double numero = 0;
    char op = '+';

    while (ss >> numero) {
        switch (op) {
            case '+': acumulado += numero; break;
            case '-': acumulado -= numero; break;
            case '*': acumulado *= numero; break;
            case '/': acumulado = (numero != 0) ? (acumulado / numero) : 0; break;
        }
        ss >> op; // Leer el siguiente operador
    }
    return acumulado;
}

int main() {
    // Ventana estilo teléfono (320x480)
    sf::RenderWindow window(sf::VideoMode({320, 480}), "Calculadora C++", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.openFromFile("arial.ttf")) {
        std::cout << "Error: No se pudo cargar arial.ttf.\n";
        return -1;
    }

    // Pantalla de la calculadora
    sf::RectangleShape pantallaFondo(sf::Vector2f({300.f, 70.f}));
    pantallaFondo.setFillColor(sf::Color(0, 0, 0));
    pantallaFondo.setPosition({10.f, 10.f});

    std::string expresion = "";
    std::string numeroActual = "";
    bool expresionTerminada = false;

    sf::Text textoDisplay(font, "0", 28);
    textoDisplay.setFillColor(sf::Color::White);
    textoDisplay.setPosition({20.f, 25.f});

    // Cuadrícula de botones
    std::vector<Boton> botones;
    std::vector<std::string> etiquetas = {
        "C", "/", "*", "-",
        "7", "8", "9", "+",
        "4", "5", "6", "=",
        "1", "2", "3", "0"
    };

    float ancho = 65.f, alto = 65.f;
    float margenX = 10.f, margenY = 90.f, espacio = 10.f;

    for (size_t i = 0; i < etiquetas.size(); ++i) {
        int fila = i / 4;
        int col = i % 4;

        Boton btn;
        btn.forma.setSize({ancho, alto});
        
        if (etiquetas[i] == "C") {
            btn.forma.setFillColor(sf::Color(200, 50, 50));
        } else if (etiquetas[i] == "+" || etiquetas[i] == "-" || etiquetas[i] == "*" || etiquetas[i] == "/" || etiquetas[i] == "=") {
            btn.forma.setFillColor(sf::Color(21, 67, 96));
        } else {
            btn.forma.setFillColor(sf::Color(41, 128, 185));
        }

        sf::Vector2f pos = {margenX + col * (ancho + espacio), margenY + fila * (alto + espacio)};
        btn.forma.setPosition(pos);
        
        btn.texto = std::make_unique<sf::Text>(font, etiquetas[i], 24);
        btn.texto->setFillColor(sf::Color::White);
        btn.texto->setPosition({
            pos.x + (ancho / 2.f) - 8.f,
            pos.y + (alto / 2.f) - 16.f
        });
        btn.valor = etiquetas[i];

        botones.push_back(std::move(btn));
    }

    // Bucle principal
    while (window.isOpen()) {
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (const auto* mousePress = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mousePress->button == sf::Mouse::Button::Left) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(mousePress->position);

                    for (auto& btn : botones) {
                        if (btn.forma.getGlobalBounds().contains(mousePos)) {
                            std::string val = btn.valor;

                            // Si se presiona un número (0-9)
                            if (val >= "0" && val <= "9") {
                                if (expresionTerminada) {
                                    expresion = "";
                                    numeroActual = "";
                                    expresionTerminada = false;
                                }
                                // Mantiene el límite de 5 cifras por cada número ingresado
                                if (numeroActual.length() < 5) {
                                    numeroActual += val;
                                    expresion += val;
                                }
                            } 
                            // Si se presiona un operador (+, -, *, /)
                            else if (val == "+" || val == "-" || val == "*" || val == "/") {
                                if (!expresion.empty() && std::isdigit(expresion.back())) {
                                    expresion += " " + val + " ";
                                    numeroActual = ""; // Reiniciar conteo de 5 cifras para el nuevo número
                                    expresionTerminada = false;
                                }
                            } 
                            // Botón de borrado (C)
                            else if (val == "C") {
                                expresion = "";
                                numeroActual = "";
                                expresionTerminada = false;
                            } 
                            // Botón Igual (=)
                            else if (val == "=") {
                                if (!expresion.empty() && std::isdigit(expresion.back())) {
                                    double res = evaluarExpresion(expresion);
                                    
                                    std::string resStr = std::to_string(res);
                                    resStr.erase(resStr.find_last_not_of('0') + 1, std::string::npos);
                                    if (resStr.back() == '.') resStr.pop_back();

                                    expresion = resStr;
                                    numeroActual = resStr;
                                    expresionTerminada = true;
                                }
                            }

                            // Ajustar tamaño del texto si la expresión se vuelve muy larga en pantalla
                            if (expresion.length() > 14) {
                                textoDisplay.setCharacterSize(18);
                            } else {
                                textoDisplay.setCharacterSize(28);
                            }

                            textoDisplay.setString(expresion.empty() ? "0" : expresion);
                        }
                    }
                }
            }
        }

        // Renderizado
        window.clear(sf::Color(255, 255, 255));
        window.draw(pantallaFondo);
        window.draw(textoDisplay);

        for (const auto& btn : botones) {
            window.draw(btn.forma);
            if (btn.texto) {
                window.draw(*btn.texto);
            }
        }

        window.display();
    }

    return 0;
}