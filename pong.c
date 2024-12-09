#include <stdio.h>
#include <stdlib.h>
#include <windows.h> // Para Sleep()
#include <conio.h>   // Para _kbhit() y _getch()

#define WIDTH 40
#define HEIGHT 20
#define PADDLE_SIZE 4
#define DELAY 50000 // Velocidad del juego en microsegundos

// Variables globales
int ball_x, ball_y;          // Posición de la pelota
int ball_dir_x = 1, ball_dir_y = 1; // Dirección de la pelota
int paddle_left_y, paddle_right_y; // Posición de las barras
int score_left = 0, score_right = 0; // Puntuaciones

// Función para limpiar la pantalla
void clear_screen() {
    system("cls");
}

// Dibujar el campo de juego
void draw_game() {
    clear_screen();

    // Dibujar la parte superior del campo
    for (int x = 0; x < WIDTH; x++) {
        printf("#");
    }
    printf("\n");

    // Dibujar el campo
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == 0 || x == WIDTH - 1) {
                printf("#"); // Bordes laterales
            } else if (x == 2 && y >= paddle_left_y && y < paddle_left_y + PADDLE_SIZE) {
                printf("|"); // Barra izquierda
            } else if (x == WIDTH - 3 && y >= paddle_right_y && y < paddle_right_y + PADDLE_SIZE) {
                printf("|"); // Barra derecha
            } else if (x == ball_x && y == ball_y) {
                printf("O"); // Pelota
            } else {
                printf(" "); // Espacio vacío
            }
        }
        printf("\n");
    }

    // Dibujar la parte inferior del campo
    for (int x = 0; x < WIDTH; x++) {
        printf("#");
    }
    printf("\n");

    // Mostrar puntuaciones
    printf("Jugador Izq: %d   Jugador Der: %d\n", score_left, score_right);
}

// Actualizar la posición de la pelota
void update_ball() {
    ball_x += ball_dir_x;
    ball_y += ball_dir_y;

    // Colisión con bordes superior e inferior
    if (ball_y <= 0 || ball_y >= HEIGHT - 1) {
        ball_dir_y *= -1;
    }

    // Colisión con la barra izquierda
    if (ball_x == 3 && ball_y >= paddle_left_y && ball_y < paddle_left_y + PADDLE_SIZE) {
        ball_dir_x *= -1;
    }

    // Colisión con la barra derecha
    if (ball_x == WIDTH - 4 && ball_y >= paddle_right_y && ball_y < paddle_right_y + PADDLE_SIZE) {
        ball_dir_x *= -1;
    }

    // Punto para el jugador derecho
    if (ball_x <= 0) {
        score_right++;
        ball_x = WIDTH / 2;
        ball_y = HEIGHT / 2;
        ball_dir_x = 1;
    }

    // Punto para el jugador izquierdo
    if (ball_x >= WIDTH - 1) {
        score_left++;
        ball_x = WIDTH / 2;
        ball_y = HEIGHT / 2;
        ball_dir_x = -1;
    }
}

// Leer entrada del teclado
void handle_input() {
    if (_kbhit()) { // Verifica si se ha presionado una tecla
        char ch = _getch();
        switch (ch) {
            case 'w': // Mover barra izquierda hacia arriba
                if (paddle_left_y > 0) paddle_left_y--;
                break;
            case 's': // Mover barra izquierda hacia abajo
                if (paddle_left_y < HEIGHT - PADDLE_SIZE) paddle_left_y++;
                break;
            case 'i': // Mover barra derecha hacia arriba
                if (paddle_right_y > 0) paddle_right_y--;
                break;
            case 'k': // Mover barra derecha hacia abajo
                if (paddle_right_y < HEIGHT - PADDLE_SIZE) paddle_right_y++;
                break;
            case 'q': // Salir del juego
                exit(0);
        }
    }
}

int main() {
    // Inicializar posiciones
    ball_x = WIDTH / 2;
    ball_y = HEIGHT / 2;
    paddle_left_y = HEIGHT / 2 - PADDLE_SIZE / 2;
    paddle_right_y = HEIGHT / 2 - PADDLE_SIZE / 2;

    while (1) {
        draw_game();
        update_ball();
        handle_input();
        Sleep(DELAY / 1000); // Convertir microsegundos a milisegundos
    }

    return 0;
}
