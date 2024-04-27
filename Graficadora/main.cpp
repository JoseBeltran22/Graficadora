#include <conio.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

const int SCREEN_WIDTH = 100;
const int SCREEN_HEIGHT = 24;

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

char showFigureMenu() {
    system("cls");
    cout << "Elija una figura:\n";
    cout << "1 - Circulo\n";
    cout << "2 - Triangulo\n";
    cout << "3 - Cuadrado\n";
    cout << "4 - Rectangulo\n";
    cout << "Presione la tecla de la figura que desea\n";

    return _getch();
}

int main() {
    int x = 0, y = 1;
    int prevX = 0, prevY = 1; // Posición previa del cursor
    char tecla;
    char opcionSeleccionada = ' ';
    unordered_map<int, string> figuras;

    // Ocultar cursor
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);

    // Mostrar mensaje de instrucción
    cout << "Mueva el cursor hacia donde desea graficar, a continuacion presione F12 para escoger la figura:\n\n";
    gotoxy(x, y);
    cout << ".";

    while (true) {
        //Movimiento del cursor
        if (_kbhit()) {
            //Borrar posición previa del cursor
            gotoxy(prevX, prevY);
            cout << " ";

            tecla = _getch();

            switch (tecla) {
                case 'w':
                case 'W':
                    y--;
                    if (y < 0) y = SCREEN_HEIGHT - 1;
                    break;
                case 'a':
                case 'A':
                    x--;
                    if (x < 0) x = SCREEN_WIDTH - 1;
                    break;
                case 's':
                case 'S':
                    y++;
                    if (y >= SCREEN_HEIGHT) y = 0;
                    break;
                case 'd':
                case 'D':
                    x++;
                    if (x >= SCREEN_WIDTH) x = 0;
                    break;
                default:
                    break;
            }

            gotoxy(x, y);
            cout << ".";
        }

        //Menú de figuras
        if (GetAsyncKeyState(VK_F12) & 0x8000) {
            opcionSeleccionada = showFigureMenu();

            system("cls");

            gotoxy(prevX, prevY);

            switch (opcionSeleccionada) {
                case '1':
                {
                    // Dibujar el círculo
                    int centerX = prevX + 2; // Coordenada X del centro del círculo
                    int centerY = prevY + 2; // Coordenada Y del centro del círculo
                    int radius = 6; // Radio del círculo

                    for (int y = centerY - radius; y <= centerY + radius; ++y) {
                        for (int x = centerX - radius; x <= centerX + radius; ++x) {
                            if ((x - centerX) * (x - centerX) + (y - centerY) * (y - centerY) <= radius * radius) {
                                if ((x - centerX) * (x - centerX) + (y - centerY) * (y - centerY) == radius * radius ||
                                    (x - centerX) * (x - centerX) + (y - centerY) * (y - centerY) == radius * radius - 1 ||
                                    (x - centerX) * (x - centerX) + (y - centerY) * (y - centerY) == radius * radius + 1 ||
                                    (x - centerX) * (x - centerX) + (y - centerY) * (y - centerY) == radius * radius - 2 ||
                                    (x - centerX) * (x - centerX) + (y - centerY) * (y - centerY) == radius * radius + 2) {
                                    figuras[y * SCREEN_WIDTH + x] = "*";
                                }
                            }
                        }
                    }
                }
                break;
                case '2':
                {
                    // Definir la altura del triángulo
                    int height = 5;

                    // Imprimir el triángulo
                    for (int row = 0; row < height; row++) {
                        for (int col = 0; col < height * 2 - 1; col++) {
                            if (col >= height - row - 1 && col <= height + row - 1) {
                                if (col == height - row - 1 || col == height + row - 1 || row == height - 1) {
                                    figuras[col + prevX + (row + prevY) * SCREEN_WIDTH] = "*"; // Imprimir asteriscos para los bordes y la base
                                } else {
                                    figuras[col + prevX + (row + prevY) * SCREEN_WIDTH] = " "; // Imprimir espacios para el interior del triángulo
                                }
                            }
                        }
                    }
                }
                break;
                case '3':
                {
                    for (int i = 0; i < 5; ++i) {
                        for (int j = 0; j < 9; ++j) {
                            if (i == 0 || i == 4 || j == 0 || j == 8) {
                                if (i == 0 || i == 4) {
                                    if (j % 2 == 0) {
                                        figuras[(i + prevY) * SCREEN_WIDTH + (j + prevX)] = "*"; // Imprime asterisco en posiciones impares
                                    } else {
                                        figuras[(i + prevY) * SCREEN_WIDTH + (j + prevX)] = " "; // Imprime espacio en posiciones pares
                                    }
                                }    else {
                                    figuras[(i + prevY) * SCREEN_WIDTH + (j + prevX)] = "*"; // Imprime asteriscos en los bordes
                                }
                            } else {
                                figuras[(i + prevY) * SCREEN_WIDTH + (j + prevX)] = " "; // Imprime espacios para el interior del cuadrado
                            }
                        }
                    }
                }
                break;
                case '4':
                {
                    for (int i = 0; i < 5; ++i) {
                        for (int j = 0; j < 17; ++j) {
                            if (i == 0 || i == 4 || j == 0 || j == 16) {
                                if (i == 0 || i == 4) {
                                    if (j % 2 == 0) {
                                        figuras[(i + prevY) * SCREEN_WIDTH + (j + prevX)] = "*"; // Imprime asterisco en posiciones impares
                                    } else {
                                        figuras[(i + prevY) * SCREEN_WIDTH + (j + prevX)] = " "; // Imprime espacio en posiciones pares
                                    }
                                }    else {
                                    figuras[(i + prevY) * SCREEN_WIDTH + (j + prevX)] = "*"; // Imprime asteriscos en los bordes
                                }
                            } else {
                                figuras[(i + prevY) * SCREEN_WIDTH + (j + prevX)] = " "; // Imprime espacios para el interior del cuadrado
                            }
                        }
                    }
                }
                break;
                default:
                    break;
            }

            // Mostrar todas las figuras almacenadas
            for (const auto& kv : figuras) {
                int startX = kv.first % SCREEN_WIDTH;
                int startY = kv.first / SCREEN_WIDTH;

                // Calcular el texto que cabe en esta línea
                string texto = kv.second;
                int textLength = texto.length();

                // Mostrar texto en la línea actual y ajustar para el desbordamiento
                int remainingLength = textLength;
                int currentX = startX;
                int currentY = startY;

                while (remainingLength > 0) {
                    // Calcular cuántos caracteres caben en la línea actual
                    int charactersToShow = min(remainingLength, SCREEN_WIDTH - currentX);

                    // Mostrar el texto en la posición actual
                    gotoxy(currentX, currentY);
                    cout << texto.substr(textLength - remainingLength, charactersToShow);

                    // Actualizar el estado para el próximo segmento de texto
                    remainingLength -= charactersToShow;
                    currentX += charactersToShow;

                    // Si el texto aún no se ha mostrado completamente,
                    // pasar a la siguiente línea y ajustar las posiciones
                    if (remainingLength > 0) {
                        currentX = 0;
                        currentY = (currentY) % SCREEN_HEIGHT;
                    }
                }
            }

            _getch(); // Esperar a que el usuario presione una tecla antes de continuar
        }

        // Actualizar posición previa del cursor
        prevX = x;
        prevY = y;
    }

    return 0;
}
