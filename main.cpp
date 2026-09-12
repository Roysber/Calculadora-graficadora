#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cmath>

// Estructura para representar un botón de la calculadora
struct Boton {
    sf::RectangleShape forma;
    std::unique_ptr<sf::Text> texto;
    std::string valor;
};

// Función para procesar las operaciones
double calcular(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return (b != 0) ? (a / b) : 0;
        default: return 0;
    }
}

int main() {
    // 1. Crear ventana (estilo móvil: 320x480)
    sf::RenderWindow window(sf::VideoMode({320, 480}), "Calculadora C++", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    // 2. Cargar fuente de texto
    sf::Font font;
    if (!font.openFromFile("arial.ttf")) {
        std::cout << "Error: No se pudo cargar arial.ttf.\n";
        return -1;
    }

    // 3. Pantalla de la calculadora
    sf::RectangleShape pantallaFondo(sf::Vector2f({300.f, 70.f}));
    pantallaFondo.setFillColor(sf::Color(30, 30, 30));
    pantallaFondo.setPosition({10.f, 10.f});

    std::string entradaActual = "";
    double primerNumero = 0;
    char operacion = ' ';
    bool nuevaEntrada = false;

    sf::Text textoDisplay(font, "0", 32);
    textoDisplay.setFillColor(sf::Color::White);
    textoDisplay.setPosition({20.f, 25.f});

    // 4. Diseñar la cuadrícula de botones
    std::vector<Boton> botones;
    std::vector<std::string> etiquetas = {
        "C", "/", "*", "-",
        "7", "8", "9", "+",
        "4", "5", "6", "=",
        "1", "2", "3", "0"
    };

    float ancho = 65.f;
    float alto = 65.f;
    float margenX = 10.f;
    float margenY = 90.f;
    float espacio = 10.f;

    for (size_t i = 0; i < etiquetas.size(); ++i) {
        int fila = i / 4;
        int col = i % 4;

        Boton btn;
        btn.forma.setSize({ancho, alto});
        
        if (etiquetas[i] == "C") {
            btn.forma.setFillColor(sf::Color(200, 50, 50));
        } else if (etiquetas[i] == "+" || etiquetas[i] == "-" || etiquetas[i] == "*" || etiquetas[i] == "/" || etiquetas[i] == "=") {
            btn.forma.setFillColor(sf::Color(230, 140, 30));
        } else {
            btn.forma.setFillColor(sf::Color(60, 60, 60));
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

    // 5. Bucle de eventos
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

                            if (val >= "0" && val <= "9") {
                                if (nuevaEntrada) {
                                    entradaActual = "";
                                    nuevaEntrada = false;
                                }
                                // Límite estricto de máximo 5 cifras por entrada
                                if (entradaActual.length() < 5) {
                                    entradaActual += val;
                                }
                            } else if (val == "C") {
                                entradaActual = "";
                                primerNumero = 0;
                                operacion = ' ';
                            } else if (val == "+" || val == "-" || val == "*" || val == "/") {
                                if (!entradaActual.empty()) {
                                    primerNumero = std::stod(entradaActual);
                                    operacion = val[0];
                                    entradaActual = "";
                                }
                            } else if (val == "=") {
                                if (!entradaActual.empty() && operacion != ' ') {
                                    double segundoNumero = std::stod(entradaActual);
                                    double res = calcular(primerNumero, segundoNumero, operacion);
                                    
                                    std::string resStr = std::to_string(res);
                                    resStr.erase(resStr.find_last_not_of('0') + 1, std::string::npos);
                                    if (resStr.back() == '.') resStr.pop_back();

                                    entradaActual = resStr;
                                    operacion = ' ';
                                    nuevaEntrada = true;
                                }
                            }

                            textoDisplay.setString(entradaActual.empty() ? "0" : entradaActual);
                        }
                    }
                }
            }
        }

        // Renderizado
        window.clear(sf::Color(20, 20, 20));
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