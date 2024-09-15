#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 9

void imprimirTablero(int tablero[SIZE][SIZE]) {
    for (int fila = 0; fila < SIZE; fila++) {
        for (int columna = 0; columna < SIZE; columna++) {
            if (tablero[fila][columna] == 0)
                printf(". ");
            else
                printf("%d ", tablero[fila][columna]);
        }
        printf("\n");
    }
}

int esSeguro(int tablero[SIZE][SIZE], int fila, int columna, int numero) {
    for (int x = 0; x < SIZE; x++) {
        if (tablero[fila][x] == numero || tablero[x][columna] == numero)
            return 0;
    }

    int inicioFila = fila - fila % 3, inicioColumna = columna - columna % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (tablero[i + inicioFila][j + inicioColumna] == numero)
                return 0;

    return 1;
}

int resolverSudoku(int tablero[SIZE][SIZE], int fila, int columna) {
    if (fila == SIZE - 1 && columna == SIZE)
        return 1;
    if (columna == SIZE) {
        fila++;
        columna = 0;
    }
    if (tablero[fila][columna] != 0)
        return resolverSudoku(tablero, fila, columna + 1);

    for (int numero = 1; numero <= SIZE; numero++) {
        if (esSeguro(tablero, fila, columna, numero)) {
            tablero[fila][columna] = numero;
            if (resolverSudoku(tablero, fila, columna + 1))
                return 1;
            tablero[fila][columna] = 0;
        }
    }
    return 0;
}

void eliminarNumeros(int tablero[SIZE][SIZE], int dificultad) {
    int eliminaciones;
    if (dificultad == 1)  // Fácil
        eliminaciones = 20;
    else if (dificultad == 2)  // Intermedio
        eliminaciones = 40;
    else  // Difícil
        eliminaciones = 55;

    while (eliminaciones > 0) {
        int fila = rand() % SIZE;
        int columna = rand() % SIZE;
        if (tablero[fila][columna] != 0) {
            tablero[fila][columna] = 0;
            eliminaciones--;
        }
    }
}

void generarTablero(int dificultad) {
    int tablero[SIZE][SIZE] = {0};
    srand(time(0));

    resolverSudoku(tablero, 0, 0);  // Genera un tablero completo
    eliminarNumeros(tablero, dificultad);  // Elimina números según la dificultad

    imprimirTablero(tablero);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <dificultad>\n1 - Fácil\n2 - Intermedio\n3 - Difícil\n", argv[0]);
        return 1;
    }

    int dificultad = atoi(argv[1]);
    if (dificultad < 1 || dificultad > 3) {
        printf("Dificultad inválida. Debe ser 1, 2 o 3.\n");
        return 1;
    }

    generarTablero(dificultad);
    return 0;
}
