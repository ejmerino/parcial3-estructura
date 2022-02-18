#include <stdio.h>
#include <stdlib.h>

/*VISITA WWW.CYPASCAL.BLOGSPOT.COM*/

struct TpCasilla
{
    int HayNum;
    int Num;
    int Posibilidades;
    int Posibles[10];
};



void LecturaDatos(struct TpCasilla T[][10]);
void InicializarDatos(struct TpCasilla T[][10]);
void ImprimeDatos(struct TpCasilla T[][10]);
void ImprimeDatos2(struct TpCasilla T[][10]);
void ImprimeDatos3(struct TpCasilla T[][10]);
void ImprimeDatos4(struct TpCasilla T[][10]);

void CandidatosSolos(struct TpCasilla T[][10], int* P);
void CandBloq1(struct TpCasilla T[][10], int* P, int U[]);
void CandBloq2(struct TpCasilla T[][10], int* P, int U[]);
void Desnudas(struct TpCasilla T[][10], int* P, int U[]);
void Escondidas(struct TpCasilla T[][10], int* P, int U[]);
void X_Wing(struct TpCasilla T[][10], int* P, int U[]);

int main(void)
{
    struct TpCasilla Tablero[10][10];
    int Usos[20], a, Puesto;

    printf("\n\n         Bienvenido a 'SUDOKU RESOLVER'\n\n");
    printf("Si quieres mas informacion visita WWW.CYPASCAL.BLOGSPOT.COM\n\n\n");
    InicializarDatos(Tablero);
    LecturaDatos(Tablero);

    Puesto = 1;
    ImprimeDatos4(Tablero); a = 0;
    for (a = 1; a <= 20; a++) Usos[a] = 0;

    while (Puesto == 1) {
        Puesto = 0;
        CandidatosSolos(Tablero, &Puesto);
        if (Puesto == 0) {
            CandBloq1(Tablero, &Puesto, Usos);
            if (Puesto == 0) {
                CandBloq2(Tablero, &Puesto, Usos);
                if (Puesto == 0) {
                    Desnudas(Tablero, &Puesto, Usos);
                    if (Puesto == 0) {
                        Escondidas(Tablero, &Puesto, Usos);
                        if (Puesto == 0) {
                            X_Wing(Tablero, &Puesto, Usos);
                        }
                    }
                }
            }
        }
        ImprimeDatos4(Tablero);
    }

    if (Usos[1] == 1) printf("\n Se ha utilizado Candidatos Bloqueados 1\n");
    if (Usos[2] == 1) printf("\n Se ha utilizado Candidatos Bloqueados 2\n");
    if (Usos[3] == 1) printf("\n Se ha utilizado Desnudas Parejas\n");
    if (Usos[4] == 1) printf("\n Se ha utilizado Desnudas Trios\n");
    if (Usos[5] == 1) printf("\n Se ha utilizado Desnudas Cuartetos\n");
    if (Usos[6] == 1) printf("\n Se ha utilizado Escondidos Parejas\n");
    if (Usos[7] == 1) printf("\n Se ha utilizado Escondidos Trios\n");
    if (Usos[8] == 1) printf("\n Se ha utilizado Escondidos Cuartetos\n");
    if (Usos[9] == 1) printf("\n Se ha utilizado X-Wing\n");
    if (Usos[10] == 1) printf("\n Se ha utilizado Swordfish\n");
    scanf_s("%c");
    return(0);
}

void CandidatosSolos(struct TpCasilla T[][10], int* P) {
    int a, b, c, d, e, N;
    for (b = 1; b <= 9; b++)
        for (a = 1; a <= 9; a++) {
            if (T[a][b].HayNum == 1) {
                N = T[a][b].Num;
                for (c = 1; c <= 9; c++)
                    if (T[a][c].HayNum == 0) {
                        if (T[a][c].Posibles[N] != 0) {
                            T[a][c].Posibles[N] = 0;
                            T[a][c].Posibilidades--;
                            *P = 1;
                        }
                        if (T[a][c].Posibilidades == 1) {
                            *P = 1;
                            e = 1;
                            while (T[a][c].Posibles[e] != 1) e++;
                            T[a][c].Posibilidades = 0;
                            T[a][c].Num = e;
                            T[a][c].HayNum = 1;
                        }
                    }

                for (c = 1; c <= 9; c++)
                    if (T[c][b].HayNum == 0) {
                        if (T[c][b].Posibles[N] != 0) {
                            T[c][b].Posibles[N] = 0;
                            T[c][b].Posibilidades--;
                            *P = 1;
                        }
                        if (T[c][b].Posibilidades == 1) {
                            *P = 1;
                            e = 1;
                            while (T[c][b].Posibles[e] != 1) e++;
                            T[c][b].Posibilidades = 0;
                            T[c][b].Num = e;
                            T[c][b].HayNum = 1;
                        }
                    }

                for (c = (((a - 1) / 3) * 3 + 1); c <= (((a - 1) / 3) * 3 + 3); c++)
                    for (d = (((b - 1) / 3) * 3 + 1); d <= (((b - 1) / 3) * 3 + 3); d++) {
                        if (T[c][d].HayNum == 0) {
                            if (T[c][d].Posibles[N] != 0) {
                                T[c][d].Posibles[N] = 0;
                                T[c][d].Posibilidades--;
                                *P = 1;
                            }

                            if (T[c][d].Posibilidades == 1) {
                                *P = 1;
                                e = 1;
                                while (T[c][d].Posibles[e] != 1) e++;
                                T[c][d].Posibilidades = 0;
                                T[c][d].Num = e;
                                T[c][d].HayNum = 1;
                            }
                        }
                    }
            }
        }
}

void CandBloq1(struct TpCasilla T[][10], int* P, int U[])
{
    struct TpPos
    {
        int Fila;
        int Columna;
    };

    int FilR, ColR, Fil, Col, N, AlinF, AlinC;
    struct TpPos Pos[10];

    for (FilR = 1; FilR <= 3; FilR++)
        for (ColR = 1; ColR <= 3; ColR++)
            for (N = 1; N <= 9; N++) {
                Pos[0].Fila = 0;
                for (Fil = ((3 * FilR) - 2); Fil <= (3 * FilR); Fil++)
                    for (Col = ((3 * ColR) - 2); Col <= (3 * ColR); Col++)
                        if ((T[Fil][Col].Posibles[N] == 1) && (T[Fil][Col].HayNum == 0))
                        {
                            Pos[0].Fila++;
                            Pos[Pos[0].Fila].Fila = Fil;
                            Pos[Pos[0].Fila].Columna = Col;
                        }
                if (Pos[0].Fila == 1) {
                    T[Pos[1].Fila][Pos[1].Columna].HayNum = 1;
                    T[Pos[1].Fila][Pos[1].Columna].Num = N;
                    T[Pos[1].Fila][Pos[1].Columna].Posibilidades = 0;
                    *P = 1;
                    U[1] = 1;
                    for (Col = 1; Col <= 9; Col++)
                        T[Pos[1].Fila][Pos[1].Columna].Posibles[Col] = 0;
                }
                else if (Pos[0].Fila >= 1) {
                    AlinF = 1; AlinC = 1;
                    for (Col = 1; Col <= Pos[0].Fila; Col++) {
                        if (Pos[Col].Fila != Pos[1].Fila) AlinF = 0;
                        if (Pos[Col].Columna != Pos[1].Columna) AlinC = 0;
                    }
                    if (AlinF == 1)
                        for (Col = 1; Col <= 9; Col++)
                            if (((((Col - 1) / 3) + 1) != ColR) &&
                                (T[Pos[1].Fila][Col].HayNum == 0) &&
                                (T[Pos[1].Fila][Col].Posibles[N] != 0)) {
                                *P = 1;
                                T[Pos[1].Fila][Col].Posibles[N] = 0;
                                T[Pos[1].Fila][Col].Posibilidades--;
                                U[1] = 1;
                            }
                    if (AlinC == 1)
                        for (Fil = 1; Fil <= 9; Fil++)
                            if (((((Fil - 1) / 3) + 1) != FilR) &&
                                (T[Fil][Pos[1].Columna].HayNum == 0) &&
                                (T[Fil][Pos[1].Columna].Posibles[N] != 0)) {
                                T[Fil][Pos[1].Columna].Posibles[N] = 0;
                                T[Fil][Pos[1].Columna].Posibilidades--;
                                *P = 1;
                                U[1] = 1;
                            }
                }
            }
}

void CandBloq2(struct TpCasilla T[][10], int* P, int U[])
{
    int Fil, Fil2, Col, Col2, N, Pos[10], Mismo3x3, MismaCol, MismaFil;

    for (Fil = 1; Fil <= 9; Fil++)
        for (N = 1; N <= 9; N++) {
            Pos[0] = 0; Mismo3x3 = 1;
            for (Col = 1; Col <= 9; Col++)
                if ((T[Fil][Col].Posibles[N] == 1) && (T[Fil][Col].HayNum == 0)) {
                    Pos[0]++;
                    Pos[Pos[0]] = Col;
                    if (((Col - 1) / 3) != ((Pos[1] - 1) / 3)) Mismo3x3 = 0;
                }
            if (Mismo3x3 == 1) {
                if (Pos[0] == 1) {
                    T[Fil][Pos[1]].HayNum = 1;
                    T[Fil][Pos[1]].Num = N;
                    T[Fil][Pos[1]].Posibilidades = 0;
                    *P = 1;
                    U[2] = 1;
                }
                if (Pos[0] != 0)
                    for (Col2 = ((((Pos[1] - 1) / 3) * 3) + 1);
                        Col2 <= ((((Pos[1] - 1) / 3) + 1) * 3); Col2++)
                        for (Fil2 = ((((Fil - 1) / 3) * 3) + 1);
                            Fil2 <= ((((Fil - 1) / 3) + 1) * 3); Fil2++)
                            if ((T[Fil2][Col2].Posibles[N] == 1) &&
                                (T[Fil2][Col2].HayNum == 0)) {
                                MismaCol = 0;
                                for (Col = 1; Col <= Pos[0]; Col++)
                                    if (Pos[Col] == Col2) MismaCol = 1;
                                if ((MismaCol == 0) || (Fil != Fil2)) {
                                    T[Fil2][Col2].Posibilidades--;
                                    T[Fil2][Col2].Posibles[N] = 0;
                                    *P = 1;
                                    U[2] = 1;
                                }
                            }
            }
        }

    for (Col = 1; Col <= 9; Col++)
        for (N = 1; N <= 9; N++) {
            Pos[0] = 0; Mismo3x3 = 1;
            for (Fil = 1; Fil <= 9; Fil++) {
                if ((T[Fil][Col].Posibles[N] == 1) && (T[Fil][Col].HayNum == 0)) {
                    Pos[0]++;
                    Pos[Pos[0]] = Fil;
                    if (((Fil - 1) / 3) != ((Pos[1] - 1) / 3)) Mismo3x3 = 0;
                }

            }
            if (Mismo3x3 == 1) {
                if (Pos[0] == 1) {
                    T[Pos[1]][Col].HayNum = 1;
                    T[Pos[1]][Col].Num = N;
                    T[Pos[1]][Col].Posibilidades = 0;
                    U[2] = 1;
                    *P = 1;
                }
                if (Pos[0] != 0)
                    for (Fil2 = ((((Pos[1] - 1) / 3) * 3) + 1);
                        Fil2 <= ((((Pos[1] - 1) / 3) + 1) * 3); Fil2++)
                        for (Col2 = ((((Col - 1) / 3) * 3) + 1);
                            Col2 <= ((((Col - 1) / 3) + 1) * 3); Col2++)
                            if ((T[Fil2][Col2].Posibles[N] == 1) &&
                                (T[Fil2][Col2].HayNum == 0)) {
                                MismaFil = 0;
                                if (Pos[0] != 0) for (Fil = 1; Fil <= Pos[0]; Fil++)
                                    if (Pos[Fil] == Fil2) MismaFil = 1;
                                if ((MismaFil == 0) || (Col != Col2)) {
                                    T[Fil2][Col2].Posibilidades--;
                                    T[Fil2][Col2].Posibles[N] = 0;
                                    U[2] = 1;
                                    *P = 1;
                                }
                            }
            }
        }
}

void Desnudas(struct TpCasilla T[][10], int* P, int U[])
{
    int a[2], b[2], c[2], d[2], N, N2, Fila, Col, Pos[10];

    for (Fila = 1; Fila <= 9; Fila++)
        for (a[0] = 1; a[0] <= 8; a[0]++)
            for (b[0] = a[0] + 1; b[0] <= 9; b[0]++)
                if ((T[Fila][a[0]].HayNum == 0) && (T[Fila][b[0]].HayNum == 0)) {
                    Pos[0] = 0;
                    for (N = 1; N <= 9; N++)
                        if ((T[Fila][a[0]].Posibles[N] == 1) ||
                            (T[Fila][b[0]].Posibles[N] == 1)) {
                            Pos[0]++;
                            Pos[Pos[0]] = N;
                        }
                    if (Pos[0] == 2) {
                        for (N = 0; N <= 9; N++)
                            if (((a[0] != N) && (b[0] != N)) && (T[Fila][N].HayNum == 0)) {
                                if (T[Fila][N].Posibles[Pos[1]] == 1) {
                                    T[Fila][N].Posibles[Pos[1]] = 0;
                                    T[Fila][N].Posibilidades--;
                                    U[3] = 1;
                                    *P = 1;
                                }
                                if (T[Fila][N].Posibles[Pos[2]] == 1) {
                                    T[Fila][N].Posibles[Pos[2]] = 0;
                                    T[Fila][N].Posibilidades--;
                                    U[3] = 1;
                                    *P = 1;
                                }
                            }
                    }
                }

    for (Fila = 1; Fila <= 9; Fila++)
        for (a[0] = 1; a[0] <= 7; a[0]++)
            for (b[0] = a[0] + 1; b[0] <= 8; b[0]++)
                for (c[0] = b[0] + 1; c[0] <= 9; c[0]++)
                    if ((T[Fila][a[0]].HayNum == 0) && (T[Fila][b[0]].HayNum == 0)
                        && (T[Fila][c[0]].HayNum == 0)) {
                        Pos[0] = 0;
                        for (N = 1; N <= 9; N++) {
                            if ((T[Fila][a[0]].Posibles[N] == 1) ||
                                (T[Fila][b[0]].Posibles[N] == 1)
                                || (T[Fila][c[0]].Posibles[N] == 1)) {
                                Pos[0]++;
                                Pos[Pos[0]] = N;
                            }
                        }
                        if (Pos[0] == 3) {
                            for (N = 0; N <= 9; N++)
                                if (((a[0] != N) && (b[0] != N) && (c[0] != N)) &&
                                    (T[Fila][N].HayNum == 0)) {
                                    if (T[Fila][N].Posibles[Pos[1]] == 1) {
                                        T[Fila][N].Posibles[Pos[1]] = 0;
                                        T[Fila][N].Posibilidades--;
                                        U[4] = 1;
                                        *P = 1;
                                    }
                                    if (T[Fila][N].Posibles[Pos[2]] == 1) {
                                        T[Fila][N].Posibles[Pos[2]] = 0;
                                        T[Fila][N].Posibilidades--;
                                        U[4] = 1;
                                        *P = 1;
                                    }
                                    if (T[Fila][N].Posibles[Pos[3]] == 1) {
                                        T[Fila][N].Posibles[Pos[3]] = 0;
                                        T[Fila][N].Posibilidades--;
                                        U[4] = 1;
                                        *P = 1;
                                    }
                                }
                        }
                    }

    for (Fila = 1; Fila <= 9; Fila++)
        for (a[0] = 1; a[0] <= 6; a[0]++)
            for (b[0] = a[0] + 1; b[0] <= 7; b[0]++)
                for (c[0] = b[0] + 1; c[0] <= 8; c[0]++)
                    for (d[0] = c[0] + 1; d[0] <= 9; d[0]++)
                        if ((T[Fila][a[0]].HayNum == 0) && (T[Fila][b[0]].HayNum == 0)
                            && (T[Fila][c[0]].HayNum == 0) && (T[Fila][d[0]].HayNum == 0)) {
                            Pos[0] = 0;
                            for (N = 1; N <= 9; N++) {
                                if ((T[Fila][a[0]].Posibles[N] == 1) ||
                                    (T[Fila][b[0]].Posibles[N] == 1) ||
                                    (T[Fila][c[0]].Posibles[N] == 1) ||
                                    (T[Fila][d[0]].Posibles[N] == 1)) {
                                    Pos[0]++;
                                    Pos[Pos[0]] = N;
                                }
                            }
                            if (Pos[0] == 4) {
                                for (N = 0; N <= 9; N++)
                                    if (((a[0] != N) && (b[0] != N) && (c[0] != N)
                                        && (d[0] != N)) && (T[Fila][N].HayNum == 0)) {
                                        if (T[Fila][N].Posibles[Pos[1]] == 1) {
                                            T[Fila][N].Posibles[Pos[1]] = 0;
                                            T[Fila][N].Posibilidades--;
                                            U[5] = 1;
                                            *P = 1;
                                        }
                                        if (T[Fila][N].Posibles[Pos[2]] == 1) {
                                            T[Fila][N].Posibles[Pos[2]] = 0;
                                            T[Fila][N].Posibilidades--;
                                            U[5] = 1;
                                            *P = 1;
                                        }
                                        if (T[Fila][N].Posibles[Pos[3]] == 1) {
                                            T[Fila][N].Posibles[Pos[3]] = 0;
                                            T[Fila][N].Posibilidades--;
                                            U[5] = 1;
                                            *P = 1;
                                        }
                                        if (T[Fila][N].Posibles[Pos[4]] == 1) {
                                            T[Fila][N].Posibles[Pos[4]] = 0;
                                            T[Fila][N].Posibilidades--;
                                            U[5] = 1;
                                            *P = 1;
                                        }
                                    }
                            }
                        }

    for (Col = 1; Col <= 9; Col++)
        for (a[0] = 1; a[0] <= 8; a[0]++)
            for (b[0] = a[0] + 1; b[0] <= 9; b[0]++)
                if ((T[a[0]][Col].HayNum == 0) && (T[b[0]][Col].HayNum == 0)) {
                    Pos[0] = 0;
                    for (N = 1; N <= 9; N++)
                        if ((T[a[0]][Col].Posibles[N] == 1) ||
                            (T[b[0]][Col].Posibles[N] == 1)) {
                            Pos[0]++;
                            Pos[Pos[0]] = N;
                        }
                    if (Pos[0] == 2) {
                        for (N = 0; N <= 9; N++)
                            if (((a[0] != N) && (b[0] != N)) && (T[N][Col].HayNum == 0)) {
                                if (T[N][Col].Posibles[Pos[1]] == 1) {
                                    T[N][Col].Posibles[Pos[1]] = 0;
                                    T[N][Col].Posibilidades--;
                                    U[3] = 1;
                                    *P = 1;
                                }
                                if (T[N][Col].Posibles[Pos[2]] == 1) {
                                    T[N][Col].Posibles[Pos[2]] = 0;
                                    T[N][Col].Posibilidades--;
                                    U[3] = 1;
                                    *P = 1;
                                }
                            }
                    }
                }

    for (Col = 1; Col <= 9; Col++)
        for (a[0] = 1; a[0] <= 7; a[0]++)
            for (b[0] = a[0] + 1; b[0] <= 8; b[0]++)
                for (c[0] = b[0] + 1; c[0] <= 9; c[0]++)
                    if ((T[a[0]][Col].HayNum == 0) && (T[b[0]][Col].HayNum == 0)
                        && (T[c[0]][Col].HayNum == 0))
                    {
                        Pos[0] = 0;
                        for (N = 1; N <= 9; N++) {
                            if ((T[a[0]][Col].Posibles[N] == 1) ||
                                (T[b[0]][Col].Posibles[N] == 1) ||
                                (T[c[0]][Col].Posibles[N] == 1)) {
                                Pos[0]++;
                                Pos[Pos[0]] = N;
                            }
                        }
                        if (Pos[0] == 3) {
                            for (N = 0; N <= 9; N++)
                                if (((a[0] != N) && (b[0] != N) && (c[0] != N)) &&
                                    (T[N][Col].HayNum == 0)) {
                                    if (T[N][Col].Posibles[Pos[1]] == 1) {
                                        T[N][Col].Posibles[Pos[1]] = 0;
                                        T[N][Col].Posibilidades--;
                                        U[4] = 1;
                                        *P = 1;
                                    }
                                    if (T[N][Col].Posibles[Pos[2]] == 1) {
                                        T[N][Col].Posibles[Pos[2]] = 0;
                                        T[N][Col].Posibilidades--;
                                        U[4] = 1;
                                        *P = 1;
                                    }
                                    if (T[N][Col].Posibles[Pos[3]] == 1) {
                                        T[N][Col].Posibles[Pos[3]] = 0;
                                        T[N][Col].Posibilidades--;
                                        U[4] = 1;
                                        *P = 1;
                                    }
                                }
                        }
                    }

    for (Col = 1; Col <= 9; Col++)
        for (a[0] = 1; a[0] <= 6; a[0]++)
            for (b[0] = a[0] + 1; b[0] <= 7; b[0]++)
                for (c[0] = b[0] + 1; c[0] <= 8; c[0]++)
                    for (d[0] = c[0] + 1; d[0] <= 9; d[0]++)
                        if ((T[a[0]][Col].HayNum == 0) && (T[b[0]][Col].HayNum == 0)
                            && (T[c[0]][Col].HayNum == 0) && (T[d[0]][Col].HayNum == 0)) {
                            Pos[0] = 0;
                            for (N = 1; N <= 9; N++) {
                                if ((T[a[0]][Col].Posibles[N] == 1) ||
                                    (T[b[0]][Col].Posibles[N] == 1)
                                    || (T[c[0]][Col].Posibles[N] == 1) ||
                                    (T[d[0]][Col].Posibles[N] == 1)) {
                                    Pos[0]++;
                                    Pos[Pos[0]] = N;
                                }
                            }
                            if (Pos[0] == 4) {
                                for (N = 0; N <= 9; N++)
                                    if (((a[0] != N) && (b[0] != N) && (c[0] != N) && (d[0] != N)) &&
                                        (T[N][Col].HayNum == 0)) {
                                        if (T[N][Col].Posibles[Pos[1]] == 1) {
                                            T[N][Col].Posibles[Pos[1]] = 0;
                                            T[N][Col].Posibilidades--;
                                            U[5] = 1;
                                            *P = 1;
                                        }
                                        if (T[N][Col].Posibles[Pos[2]] == 1) {
                                            T[N][Col].Posibles[Pos[2]] = 0;
                                            T[N][Col].Posibilidades--;
                                            U[5] = 1;
                                            *P = 1;
                                        }
                                        if (T[N][Col].Posibles[Pos[3]] == 1) {
                                            T[N][Col].Posibles[Pos[3]] = 0;
                                            T[N][Col].Posibilidades--;
                                            U[5] = 1;
                                            *P = 1;
                                        }
                                        if (T[N][Col].Posibles[Pos[4]] == 1) {
                                            T[N][Col].Posibles[Pos[4]] = 0;
                                            T[N][Col].Posibilidades--;
                                            U[5] = 1;
                                            *P = 1;
                                        }
                                    }
                            }
                        }

    for (Fila = 1; Fila <= 3; Fila++) for (Col = 1; Col <= 3; Col++)
        for (a[0] = (Fila * 3) - 2; a[0] <= (Fila * 3); a[0]++)
            for (a[1] = (Col * 3) - 2; a[1] <= (Col * 3); a[1]++)
                for (b[0] = (Fila * 3) - 2; b[0] <= (Fila * 3); b[0]++)
                    for (b[1] = (Col * 3) - 2; b[1] <= (Col * 3); b[1]++)
                        if ((T[a[0]][a[1]].HayNum == 0) && (T[b[0]][b[1]].HayNum == 0) &&
                            ((a[0] != b[0]) || (a[1] != b[1]))) {
                            Pos[0] = 0;
                            for (N = 1; N <= 9; N++)
                                if ((T[a[0]][a[1]].Posibles[N] == 1) ||
                                    (T[b[0]][b[1]].Posibles[N] == 1)) {
                                    Pos[0]++;
                                    Pos[Pos[0]] = N;
                                }
                            if (Pos[0] == 2) {
                                for (N = (Fila * 3) - 2; N <= (Fila * 3); N++)
                                    for (N2 = (Col * 3) - 2; N2 <= (Col * 3); N2++)
                                        if ((((a[0] != N) || (a[1] != N2)) && ((b[0] != N) || (b[1] != N2)))
                                            && (T[N][N2].HayNum == 0)) {
                                            if (T[N][N2].Posibles[Pos[1]] == 1) {
                                                T[N][N2].Posibles[Pos[1]] = 0;
                                                T[N][N2].Posibilidades--;
                                                U[3] = 1;
                                                *P = 1;
                                            }
                                            if (T[N][N2].Posibles[Pos[2]] == 1) {
                                                T[N][N2].Posibles[Pos[2]] = 0;
                                                T[N][N2].Posibilidades--;
                                                U[3] = 1;
                                                *P = 1;
                                            }
                                        }
                            }
                        }

    for (Fila = 1; Fila <= 3; Fila++) for (Col = 1; Col <= 3; Col++)
        for (a[0] = (Fila * 3) - 2; a[0] <= (Fila * 3); a[0]++)
            for (a[1] = (Col * 3) - 2; a[1] <= (Col * 3); a[1]++)
                for (b[0] = (Fila * 3) - 2; b[0] <= (Fila * 3); b[0]++)
                    for (b[1] = (Col * 3) - 2; b[1] <= (Col * 3); b[1]++)
                        for (c[0] = (Fila * 3) - 2; c[0] <= (Fila * 3); c[0]++)
                            for (c[1] = (Col * 3) - 2; c[1] <= (Col * 3); c[1]++)
                                if ((T[a[0]][a[1]].HayNum == 0) && (T[b[0]][b[1]].HayNum == 0) &&
                                    (T[c[0]][c[1]].HayNum == 0) && ((a[0] != b[0]) || (a[1] != b[1]))
                                    && ((a[0] != c[0]) || (a[1] != c[1])) && ((c[0] != b[0]) || (c[1] != b[1]))) {
                                    Pos[0] = 0;
                                    for (N = 1; N <= 9; N++)
                                        if ((T[a[0]][a[1]].Posibles[N] == 1) ||
                                            (T[b[0]][b[1]].Posibles[N] == 1) ||
                                            (T[c[0]][c[1]].Posibles[N] == 1)) {
                                            Pos[0]++;
                                            Pos[Pos[0]] = N;
                                        }
                                    if (Pos[0] == 3) {
                                        for (N = (Fila * 3) - 2; N <= (Fila * 3); N++)
                                            for (N2 = (Col * 3) - 2; N2 <= (Col * 3); N2++)
                                                if ((((a[0] != N) || (a[1] != N2)) && ((b[0] != N) || (b[1] != N2))
                                                    && ((c[0] != N) || (c[1] != N2))) && (T[N][N2].HayNum == 0)) {
                                                    if (T[N][N2].Posibles[Pos[1]] == 1) {
                                                        T[N][N2].Posibles[Pos[1]] = 0;
                                                        T[N][N2].Posibilidades--;
                                                        U[4] = 1;
                                                        *P = 1;
                                                    }
                                                    if (T[N][N2].Posibles[Pos[2]] == 1) {
                                                        T[N][N2].Posibles[Pos[2]] = 0;
                                                        T[N][N2].Posibilidades--;
                                                        U[4] = 1;
                                                        *P = 1;
                                                    }
                                                    if (T[N][N2].Posibles[Pos[3]] == 1) {
                                                        T[N][N2].Posibles[Pos[3]] = 0;
                                                        T[N][N2].Posibilidades--;
                                                        U[4] = 1;
                                                        *P = 1;
                                                    }
                                                }
                                    }
                                }

    for (Fila = 1; Fila <= 3; Fila++) for (Col = 1; Col <= 3; Col++)
        for (a[0] = (Fila * 3) - 2; a[0] <= (Fila * 3); a[0]++)
            for (a[1] = (Col * 3) - 2; a[1] <= (Col * 3); a[1]++)
                for (b[0] = (Fila * 3) - 2; b[0] <= (Fila * 3); b[0]++)
                    for (b[1] = (Col * 3) - 2; b[1] <= (Col * 3); b[1]++)
                        for (c[0] = (Fila * 3) - 2; c[0] <= (Fila * 3); c[0]++)
                            for (c[1] = (Col * 3) - 2; c[1] <= (Col * 3); c[1]++)
                                for (d[0] = (Fila * 3) - 2; d[0] <= (Fila * 3); d[0]++)
                                    for (d[1] = (Col * 3) - 2; d[1] <= (Col * 3); d[1]++)
                                        if ((T[a[0]][a[1]].HayNum == 0) && (T[b[0]][b[1]].HayNum == 0) &&
                                            (T[c[0]][c[1]].HayNum == 0) && (T[d[0]][d[1]].HayNum == 0) &&
                                            ((a[0] != b[0]) || (a[1] != b[1])) && ((a[0] != c[0]) || (a[1] != c[1])) &&
                                            ((c[0] != b[0]) || (c[1] != b[1])) && ((d[0] != a[0]) || (d[1] != a[1])) &&
                                            ((d[0] != b[0]) || (d[1] != b[1])) && ((c[0] != d[0]) || (c[1] != d[1]))) {
                                            Pos[0] = 0;
                                            for (N = 1; N <= 9; N++)
                                                if ((T[a[0]][a[1]].Posibles[N] == 1) ||
                                                    (T[b[0]][b[1]].Posibles[N] == 1) ||
                                                    (T[c[0]][c[1]].Posibles[N] == 1) ||
                                                    (T[d[0]][d[1]].Posibles[N] == 1)) {
                                                    Pos[0]++;
                                                    Pos[Pos[0]] = N;
                                                }
                                            if (Pos[0] == 4) {
                                                for (N = (Fila * 3) - 2; N <= (Fila * 3); N++)
                                                    for (N2 = (Col * 3) - 2; N2 <= (Col * 3); N2++)
                                                        if ((((a[0] != N) || (a[1] != N2)) && ((b[0] != N) || (b[1] != N2))
                                                            && ((c[0] != N) || (c[1] != N2)) && ((d[0] != N) || (d[1] != N2)))
                                                            && (T[N][N2].HayNum == 0)) {
                                                            if (T[N][N2].Posibles[Pos[1]] == 1) {
                                                                T[N][N2].Posibles[Pos[1]] = 0;
                                                                T[N][N2].Posibilidades--;
                                                                U[5] = 1;
                                                                *P = 1;
                                                            }
                                                            if (T[N][N2].Posibles[Pos[2]] == 1) {
                                                                T[N][N2].Posibles[Pos[2]] = 0;
                                                                T[N][N2].Posibilidades--;
                                                                U[5] = 1;
                                                                *P = 1;
                                                            }
                                                            if (T[N][N2].Posibles[Pos[3]] == 1) {
                                                                T[N][N2].Posibles[Pos[3]] = 0;
                                                                T[N][N2].Posibilidades--;
                                                                U[5] = 1;
                                                                *P = 1;
                                                            }
                                                            if (T[N][N2].Posibles[Pos[4]] == 1) {
                                                                T[N][N2].Posibles[Pos[4]] = 0;
                                                                T[N][N2].Posibilidades--;
                                                                U[5] = 1;
                                                                *P = 1;
                                                            }
                                                        }
                                            }
                                        }
}

void Escondidas(struct TpCasilla T[][10], int* P, int U[])
{
    struct TpPos
    {
        int C;
        int F;
    };

    int a, b, c, d, N, Estan[10], Fila, Col, FilaR, ColR;
    struct TpPos Pos[10];

    for (Fila = 1; Fila <= 9; Fila++)
        for (a = 1; a <= 8; a++)
            for (b = a + 1; b <= 9; b++)
            {
                for (Col = 1; Col <= 9; Col++) Estan[Col] = 0;
                Pos[0].C = 0;
                for (Col = 1; Col <= 9; Col++)
                    if (((T[Fila][Col].Posibles[a] == 1) || (T[Fila][Col].Posibles[b] == 1))
                        && (T[Fila][Col].HayNum != 1))
                    {
                        if (T[Fila][Col].Posibles[a] == 1) Estan[a] = 1;
                        if (T[Fila][Col].Posibles[b] == 1) Estan[b] = 1;
                        Pos[0].C++;
                        Pos[Pos[0].C].C = Col;
                    }
                if ((Pos[0].C == 2) && (Estan[a] == 1) && (Estan[b] == 1))
                    for (N = 1; N <= 9; N++)
                        if ((N != a) && (N != b)) {
                            if (T[Fila][Pos[1].C].Posibles[N] == 1) {
                                T[Fila][Pos[1].C].Posibles[N] = 0;
                                T[Fila][Pos[1].C].Posibilidades--;
                                U[6] = 1;
                                *P = 1;
                            }
                            if (T[Fila][Pos[2].C].Posibles[N] == 1) {
                                T[Fila][Pos[2].C].Posibles[N] = 0;
                                T[Fila][Pos[2].C].Posibilidades--;
                                U[6] = 1;
                                *P = 1;
                            }
                        }
            }

    for (Fila = 1; Fila <= 9; Fila++)
        for (a = 1; a <= 7; a++)
            for (b = a + 1; b <= 8; b++)
                for (c = b + 1; c <= 9; c++) {
                    for (Col = 1; Col <= 9; Col++) Estan[Col] = 0;
                    Pos[0].C = 0;
                    for (Col = 1; Col <= 9; Col++)
                        if (((T[Fila][Col].Posibles[a] == 1) || (T[Fila][Col].Posibles[b] == 1)
                            || (T[Fila][Col].Posibles[c] == 1)) && (T[Fila][Col].HayNum != 1)) {
                            if (T[Fila][Col].Posibles[a] == 1) Estan[a] = 1;
                            if (T[Fila][Col].Posibles[b] == 1) Estan[b] = 1;
                            if (T[Fila][Col].Posibles[c] == 1) Estan[c] = 1;
                            Pos[0].C++;
                            Pos[Pos[0].C].C = Col;
                        }
                    if ((Pos[0].C == 3) && (Estan[a] == 1) && (Estan[b] == 1) && (Estan[c] == 1))
                        for (N = 1; N <= 9; N++)
                            if ((N != a) && (N != b) && (N != c)) {
                                if (T[Fila][Pos[1].C].Posibles[N] == 1) {
                                    T[Fila][Pos[1].C].Posibles[N] = 0;
                                    T[Fila][Pos[1].C].Posibilidades--;
                                    U[7] = 1;
                                    *P = 1;
                                }
                                if (T[Fila][Pos[2].C].Posibles[N] == 1) {
                                    T[Fila][Pos[2].C].Posibles[N] = 0;
                                    T[Fila][Pos[2].C].Posibilidades--;
                                    U[7] = 1;
                                    *P = 1;
                                }
                                if (T[Fila][Pos[3].C].Posibles[N] == 1) {
                                    T[Fila][Pos[3].C].Posibles[N] = 0;
                                    T[Fila][Pos[3].C].Posibilidades--;
                                    U[7] = 1;
                                    *P = 1;
                                }
                            }
                }

    for (Fila = 1; Fila <= 9; Fila++)
        for (a = 1; a <= 6; a++)
            for (b = a + 1; b <= 7; b++)
                for (c = b + 1; c <= 8; c++)
                    for (d = c + 1; d <= 9; d++) {
                        for (Col = 1; Col <= 9; Col++) Estan[Col] = 0;
                        Pos[0].C = 0;
                        for (Col = 1; Col <= 9; Col++)
                            if (((T[Fila][Col].Posibles[a] == 1) || (T[Fila][Col].Posibles[b] == 1)
                                || (T[Fila][Col].Posibles[c] == 1) ||
                                (T[Fila][Col].Posibles[d] == 1)) && (T[Fila][Col].HayNum != 1)) {
                                if (T[Fila][Col].Posibles[a] == 1) Estan[a] = 1;
                                if (T[Fila][Col].Posibles[b] == 1) Estan[b] = 1;
                                if (T[Fila][Col].Posibles[c] == 1) Estan[c] = 1;
                                if (T[Fila][Col].Posibles[d] == 1) Estan[d] = 1;
                                Pos[0].C++;
                                Pos[Pos[0].C].C = Col;
                            }
                        if ((Pos[0].C == 4) && (Estan[a] == 1) && (Estan[b] == 1) &&
                            (Estan[c] == 1) && (Estan[d] == 1))
                            for (N = 1; N <= 9; N++)
                                if ((N != a) && (N != b) && (N != c) && (N != d)) {
                                    if (T[Fila][Pos[1].C].Posibles[N] == 1) {
                                        T[Fila][Pos[1].C].Posibles[N] = 0;
                                        T[Fila][Pos[1].C].Posibilidades--;
                                        U[8] = 1;
                                        *P = 1;
                                    }
                                    if (T[Fila][Pos[2].C].Posibles[N] == 1) {
                                        T[Fila][Pos[2].C].Posibles[N] = 0;
                                        T[Fila][Pos[2].C].Posibilidades--;
                                        U[8] = 1;
                                        *P = 1;
                                    }
                                    if (T[Fila][Pos[3].C].Posibles[N] == 1) {
                                        T[Fila][Pos[3].C].Posibles[N] = 0;
                                        T[Fila][Pos[3].C].Posibilidades--;
                                        U[8] = 1;
                                        *P = 1;
                                    }
                                    if (T[Fila][Pos[4].C].Posibles[N] == 1) {
                                        T[Fila][Pos[4].C].Posibles[N] = 0;
                                        T[Fila][Pos[4].C].Posibilidades--;
                                        U[8] = 1;
                                        *P = 1;
                                    }
                                }
                    }

    for (Col = 1; Col <= 9; Col++)
        for (a = 1; a <= 8; a++)
            for (b = a + 1; b <= 9; b++) {
                for (Fila = 1; Fila <= 9; Fila++) Estan[Fila] = 0;
                Pos[0].F = 0;
                for (Fila = 1; Fila <= 9; Fila++)
                    if (((T[Fila][Col].Posibles[a] == 1) || (T[Fila][Col].Posibles[b] == 1))
                        && (T[Fila][Col].HayNum != 1)) {
                        if (T[Fila][Col].Posibles[a] == 1) Estan[a] = 1;
                        if (T[Fila][Col].Posibles[b] == 1) Estan[b] = 1;
                        Pos[0].F++;
                        Pos[Pos[0].F].F = Fila;
                    }
                if ((Pos[0].F == 2) && (Estan[a] == 1) && (Estan[b] == 1))
                    for (N = 1; N <= 9; N++)
                        if ((N != a) && (N != b)) {
                            if (T[Pos[1].F][Col].Posibles[N] == 1) {
                                T[Pos[1].F][Col].Posibles[N] = 0;
                                T[Pos[1].F][Col].Posibilidades--;
                                U[6] = 1;
                                *P = 1;
                            }
                            if (T[Pos[2].F][Col].Posibles[N] == 1) {
                                T[Pos[2].F][Col].Posibles[N] = 0;
                                T[Pos[2].F][Col].Posibilidades--;
                                U[6] = 1;
                                *P = 1;
                            }
                        }
            }

    for (Col = 1; Col <= 9; Col++)
        for (a = 1; a <= 7; a++)
            for (b = a + 1; b <= 8; b++)
                for (c = b + 1; c <= 9; c++) {
                    for (Fila = 1; Fila <= 9; Fila++) Estan[Fila] = 0;
                    Pos[0].F = 0;
                    for (Fila = 1; Fila <= 9; Fila++)
                        if (((T[Fila][Col].Posibles[a] == 1) || (T[Fila][Col].Posibles[b] == 1)
                            || (T[Fila][Col].Posibles[c] == 1)) && (T[Fila][Col].HayNum != 1)) {
                            if (T[Fila][Col].Posibles[a] == 1) Estan[a] = 1;
                            if (T[Fila][Col].Posibles[b] == 1) Estan[b] = 1;
                            if (T[Fila][Col].Posibles[c] == 1) Estan[c] = 1;
                            Pos[0].F++;
                            Pos[Pos[0].F].F = Fila;
                        }
                    if ((Pos[0].F == 3) && (Estan[a] == 1) && (Estan[b] == 1) && (Estan[c] == 1))
                        for (N = 1; N <= 9; N++)
                            if ((N != a) && (N != b) && (N != c)) {
                                if (T[Pos[1].F][Col].Posibles[N] == 1) {
                                    T[Pos[1].F][Col].Posibles[N] = 0;
                                    T[Pos[1].F][Col].Posibilidades--;
                                    U[7] = 1;
                                    *P = 1;
                                }
                                if (T[Pos[2].F][Col].Posibles[N] == 1) {
                                    T[Pos[2].F][Col].Posibles[N] = 0;
                                    T[Pos[2].F][Col].Posibilidades--;
                                    U[7] = 1;
                                    *P = 1;
                                }
                                if (T[Pos[3].F][Col].Posibles[N] == 1) {
                                    T[Pos[3].F][Col].Posibles[N] = 0;
                                    T[Pos[3].F][Col].Posibilidades--;
                                    U[7] = 1;
                                    *P = 1;
                                }
                            }
                }

    for (Col = 1; Col <= 9; Col++)
        for (a = 1; a <= 6; a++)
            for (b = a + 1; b <= 7; b++)
                for (c = b + 1; c <= 8; c++)
                    for (d = c + 1; d <= 9; d++) {
                        for (Fila = 1; Fila <= 9; Fila++) Estan[Fila] = 0;
                        Pos[0].F = 0;
                        for (Fila = 1; Fila <= 9; Fila++)
                            if (((T[Fila][Col].Posibles[a] == 1) || (T[Fila][Col].Posibles[b] == 1)
                                || (T[Fila][Col].Posibles[c] == 1) ||
                                (T[Fila][Col].Posibles[d] == 1)) && (T[Fila][Col].HayNum != 1)) {
                                if (T[Fila][Col].Posibles[a] == 1) Estan[a] = 1;
                                if (T[Fila][Col].Posibles[b] == 1) Estan[b] = 1;
                                if (T[Fila][Col].Posibles[c] == 1) Estan[c] = 1;
                                if (T[Fila][Col].Posibles[d] == 1) Estan[d] = 1;
                                Pos[0].F++;
                                Pos[Pos[0].F].F = Fila;
                            }
                        if ((Pos[0].F == 3) && (Estan[a] == 1) && (Estan[b] == 1) &&
                            (Estan[c] == 1) && (Estan[d] == 1))
                            for (N = 1; N <= 9; N++)
                                if ((N != a) && (N != b) && (N != c)) {
                                    if (T[Pos[1].F][Col].Posibles[N] == 1) {
                                        T[Pos[1].F][Col].Posibles[N] = 0;
                                        T[Pos[1].F][Col].Posibilidades--;
                                        U[8] = 1;
                                        *P = 1;
                                    }
                                    if (T[Pos[2].F][Col].Posibles[N] == 1) {
                                        T[Pos[2].F][Col].Posibles[N] = 0;
                                        T[Pos[2].F][Col].Posibilidades--;
                                        U[8] = 1;
                                        *P = 1;
                                    }
                                    if (T[Pos[3].F][Col].Posibles[N] == 1) {
                                        T[Pos[3].F][Col].Posibles[N] = 0;
                                        T[Pos[3].F][Col].Posibilidades--;
                                        U[8] = 1;
                                        *P = 1;
                                    }
                                    if (T[Pos[4].F][Col].Posibles[N] == 1) {
                                        T[Pos[4].F][Col].Posibles[N] = 0;
                                        T[Pos[4].F][Col].Posibilidades--;
                                        U[8] = 1;
                                        *P = 1;
                                    }
                                }
                    }

    for (FilaR = 1; FilaR <= 3; FilaR++)
        for (ColR = 1; ColR <= 3; ColR++)
            for (a = 1; a <= 8; a++)
                for (b = a + 1; b <= 9; b++) {
                    for (Fila = 1; Fila <= 9; Fila++) Estan[Fila] = 0;
                    Pos[0].F = 0;
                    for (Fila = ((3 * FilaR) - 2); Fila <= (3 * FilaR); Fila++)
                        for (Col = ((3 * ColR) - 2); Col <= (3 * ColR); Col++)
                            if (((T[Fila][Col].Posibles[a] == 1) || (T[Fila][Col].Posibles[b] == 1))
                                && (T[Fila][Col].HayNum != 1)) {
                                if (T[Fila][Col].Posibles[a] == 1) Estan[a] = 1;
                                if (T[Fila][Col].Posibles[b] == 1) Estan[b] = 1;
                                Pos[0].F++;
                                Pos[Pos[0].F].F = Fila;
                                Pos[Pos[0].F].C = Col;
                            }
                    if ((Pos[0].F == 2) && (Estan[a] == 1) && (Estan[b] == 1))
                        for (N = 1; N <= 9; N++)
                            if ((N != a) && (N != b)) {
                                if (T[Pos[1].F][Pos[1].C].Posibles[N] == 1) {
                                    T[Pos[1].F][Pos[1].C].Posibles[N] = 0;
                                    T[Pos[1].F][Pos[1].C].Posibilidades--;
                                    U[6] = 1;
                                    *P = 1;
                                }
                                if (T[Pos[2].F][Pos[2].C].Posibles[N] == 1) {
                                    T[Pos[2].F][Pos[2].C].Posibles[N] = 0;
                                    T[Pos[2].F][Pos[2].C].Posibilidades--;
                                    U[6] = 1;
                                    *P = 1;
                                }
                            }
                }

    for (FilaR = 1; FilaR <= 3; FilaR++)
        for (ColR = 1; ColR <= 3; ColR++)
            for (a = 1; a <= 7; a++)
                for (b = a + 1; b <= 8; b++)
                    for (c = b + 1; c <= 9; c++) {
                        for (Fila = 1; Fila <= 9; Fila++) Estan[Fila] = 0;
                        Pos[0].F = 0;
                        for (Fila = ((3 * FilaR) - 2); Fila <= (3 * FilaR); Fila++)
                            for (Col = ((3 * ColR) - 2); Col <= (3 * ColR); Col++)
                                if (((T[Fila][Col].Posibles[a] == 1) || (T[Fila][Col].Posibles[b] == 1)
                                    || (T[Fila][Col].Posibles[c] == 1)) && (T[Fila][Col].HayNum != 1)) {
                                    if (T[Fila][Col].Posibles[a] == 1) Estan[a] = 1;
                                    if (T[Fila][Col].Posibles[b] == 1) Estan[b] = 1;
                                    if (T[Fila][Col].Posibles[c] == 1) Estan[c] = 1;
                                    Pos[0].F++;
                                    Pos[Pos[0].F].F = Fila;
                                    Pos[Pos[0].F].C = Col;
                                }
                        if ((Pos[0].F == 3) && (Estan[a] == 1) && (Estan[b] == 1) && (Estan[c] == 1))
                            for (N = 1; N <= 9; N++)
                                if ((N != a) && (N != b) && (N != c)) {
                                    if (T[Pos[1].F][Pos[1].C].Posibles[N] == 1) {
                                        T[Pos[1].F][Pos[1].C].Posibles[N] = 0;
                                        T[Pos[1].F][Pos[1].C].Posibilidades--;
                                        U[7] = 1;
                                        *P = 1;
                                    }
                                    if (T[Pos[2].F][Pos[2].C].Posibles[N] == 1) {
                                        T[Pos[2].F][Pos[2].C].Posibles[N] = 0;
                                        T[Pos[2].F][Pos[2].C].Posibilidades--;
                                        U[7] = 1;
                                        *P = 1;
                                    }
                                    if (T[Pos[3].F][Pos[3].C].Posibles[N] == 1) {
                                        T[Pos[3].F][Pos[3].C].Posibles[N] = 0;
                                        T[Pos[3].F][Pos[3].C].Posibilidades--;
                                        U[7] = 1;
                                        *P = 1;
                                    }
                                }
                    }

    for (FilaR = 1; FilaR <= 3; FilaR++)
        for (ColR = 1; ColR <= 3; ColR++)
            for (a = 1; a <= 6; a++)
                for (b = a + 1; b <= 7; b++)
                    for (c = b + 1; c <= 8; c++)
                        for (d = c + 1; d <= 9; d++) {
                            for (Fila = 1; Fila <= 9; Fila++) Estan[Fila] = 0;
                            Pos[0].F = 0;
                            for (Fila = ((3 * FilaR) - 2); Fila <= (3 * FilaR); Fila++)
                                for (Col = ((3 * ColR) - 2); Col <= (3 * ColR); Col++)
                                    if (((T[Fila][Col].Posibles[a] == 1) || (T[Fila][Col].Posibles[b] == 1)
                                        || (T[Fila][Col].Posibles[c] == 1) ||
                                        (T[Fila][Col].Posibles[d] == 1)) && (T[Fila][Col].HayNum != 1)) {
                                        if (T[Fila][Col].Posibles[a] == 1) Estan[a] = 1;
                                        if (T[Fila][Col].Posibles[b] == 1) Estan[b] = 1;
                                        if (T[Fila][Col].Posibles[c] == 1) Estan[c] = 1;
                                        if (T[Fila][Col].Posibles[d] == 1) Estan[d] = 1;
                                        Pos[0].F++;
                                        Pos[Pos[0].F].F = Fila;
                                        Pos[Pos[0].F].C = Col;
                                    }
                            if ((Pos[0].F == 4) && (Estan[a] == 1) && (Estan[b] == 1)
                                && (Estan[c] == 1) && (Estan[d] == 1))
                                for (N = 1; N <= 9; N++)
                                    if ((N != a) && (N != b) && (N != c) && (N != d)) {
                                        if (T[Pos[1].F][Pos[1].C].Posibles[N] == 1) {
                                            T[Pos[1].F][Pos[1].C].Posibles[N] = 0;
                                            T[Pos[1].F][Pos[1].C].Posibilidades--;
                                            U[8] = 1;
                                            *P = 1;
                                        }
                                        if (T[Pos[2].F][Pos[2].C].Posibles[N] == 1) {
                                            T[Pos[2].F][Pos[2].C].Posibles[N] = 0;
                                            T[Pos[2].F][Pos[2].C].Posibilidades--;
                                            U[8] = 1;
                                            *P = 1;
                                        }
                                        if (T[Pos[3].F][Pos[3].C].Posibles[N] == 1) {
                                            T[Pos[3].F][Pos[3].C].Posibles[N] = 0;
                                            T[Pos[3].F][Pos[3].C].Posibilidades--;
                                            U[8] = 1;
                                            *P = 1;
                                        }
                                        if (T[Pos[4].F][Pos[4].C].Posibles[N] == 1) {
                                            T[Pos[4].F][Pos[4].C].Posibles[N] = 0;
                                            T[Pos[4].F][Pos[4].C].Posibilidades--;
                                            U[8] = 1;
                                            *P = 1;
                                        }
                                    }
                        }
}

void X_Wing(struct TpCasilla T[][10], int* P, int U[])
{
    int Fil, Fil1, Fil2, Fil3, Col, Pos[10], Esta1, Esta2, Esta3, N;

    for (Fil1 = 1; Fil1 <= 8; Fil1++)
        for (Fil2 = Fil1 + 1; Fil2 <= 9; Fil2++)
            for (N = 1; N <= 9; N++) {
                Pos[0] = 0; Esta1 = Esta2 = 0;
                for (Col = 1; Col <= 9; Col++) {
                    if ((T[Fil1][Col].Posibles[N] == 1) && (T[Fil1][Col].HayNum == 0))
                        Esta1 = 1;
                    if ((T[Fil2][Col].Posibles[N] == 1) && (T[Fil2][Col].HayNum == 0))
                        Esta2 = 1;
                    if (((T[Fil1][Col].Posibles[N] == 1) && (T[Fil1][Col].HayNum == 0)) ||
                        ((T[Fil2][Col].Posibles[N] == 1) && (T[Fil2][Col].HayNum == 0))) {
                        Pos[0]++;
                        Pos[Pos[0]] = Col;
                    }
                }
                if ((Pos[0] == 2) && (Esta1) && (Esta2)) {
                    for (Fil = 1; Fil <= 9; Fil++)
                        if ((Fil != Fil1) && (Fil != Fil2)) {
                            if ((T[Fil][Pos[1]].Posibles[N] == 1)
                                && (T[Fil][Pos[1]].HayNum == 0)) {
                                T[Fil][Pos[1]].Posibles[N] = 0;
                                T[Fil][Pos[1]].Posibilidades--;
                                U[9] = 1;
                                *P = 1;
                            }
                            if ((T[Fil][Pos[2]].Posibles[N] == 1)
                                && (T[Fil][Pos[2]].HayNum == 0)) {
                                T[Fil][Pos[2]].Posibles[N] = 0;
                                T[Fil][Pos[2]].Posibilidades--;
                                U[9] = 1;
                                *P = 1;
                            }
                        }
                }
            }

    for (Fil1 = 1; Fil1 <= 7; Fil1++)
        for (Fil2 = Fil1 + 1; Fil2 <= 8; Fil2++)
            for (Fil3 = Fil2 + 1; Fil3 <= 9; Fil3++)
                for (N = 1; N <= 9; N++) {
                    Pos[0] = 0; Esta1 = Esta2 = Esta3 = 0;
                    for (Col = 1; Col <= 9; Col++) {
                        if ((T[Fil1][Col].Posibles[N] == 1) && (T[Fil1][Col].HayNum == 0))
                            Esta1 = 1;
                        if ((T[Fil2][Col].Posibles[N] == 1) && (T[Fil2][Col].HayNum == 0))
                            Esta2 = 1;
                        if ((T[Fil3][Col].Posibles[N] == 1) && (T[Fil3][Col].HayNum == 0))
                            Esta3 = 1;
                        if (((T[Fil1][Col].Posibles[N] == 1) && (T[Fil1][Col].HayNum == 0)) ||
                            ((T[Fil2][Col].Posibles[N] == 1) && (T[Fil2][Col].HayNum == 0)) ||
                            ((T[Fil3][Col].Posibles[N] == 1) && (T[Fil3][Col].HayNum == 0))) {
                            Pos[0]++;
                            Pos[Pos[0]] = Col;
                        }
                    }
                    if ((Pos[0] == 3) && (Esta1) && (Esta2) && (Esta3)) {
                        for (Fil = 1; Fil <= 9; Fil++)
                            if ((Fil != Fil1) && (Fil != Fil2) && (Fil != Fil3)) {
                                if ((T[Fil][Pos[1]].Posibles[N] == 1)
                                    && (T[Fil][Pos[1]].HayNum == 0)) {
                                    T[Fil][Pos[1]].Posibles[N] = 0;
                                    T[Fil][Pos[1]].Posibilidades--;
                                    U[10] = 1;
                                    *P = 1;
                                }
                                if ((T[Fil][Pos[2]].Posibles[N] == 1)
                                    && (T[Fil][Pos[2]].HayNum == 0)) {
                                    T[Fil][Pos[2]].Posibles[N] = 0;
                                    T[Fil][Pos[2]].Posibilidades--;
                                    U[10] = 1;
                                    *P = 1;
                                }
                                if ((T[Fil][Pos[3]].Posibles[N] == 1)
                                    && (T[Fil][Pos[3]].HayNum == 0)) {
                                    T[Fil][Pos[3]].Posibles[N] = 0;
                                    T[Fil][Pos[3]].Posibilidades--;
                                    U[10] = 1;
                                    *P = 1;
                                }
                            }
                    }
                }
}

void InicializarDatos(struct TpCasilla T[][10])
{
    int a, b, c;
    for (a = 1; a <= 9; a++)
        for (b = 1; b <= 9; b++) {
            T[a][b].HayNum = 0;
            T[a][b].Num = 0;
            T[a][b].Posibilidades = 9;
            for (c = 1; c <= 9; c++)
                T[a][b].Posibles[c] = 1;
        }
}

void LecturaDatos(struct TpCasilla T[][10])
{
    FILE* FSud;
    char NombreF[30], car;
    int N, a, b, c;

    printf("Escriba el nombre del fichero donde esta almacenado el Sudoku: ");
    gets(NombreF);

    if ((FSud = fopen(NombreF, "r")) == 0) {
        printf("No se pudo abrir el fichero."); scanf_s("%c", &car);
        exit(1);
    }

    car = getc(FSud);
    a = 1; b = 1;
    printf("\n\nEl Sudoku del fichero es el siguiente: \n\n\n");
    while (!feof(FSud)) {
        printf("%c", car);
        N = car; N = N - 48;
        if ((N >= 0) && (N <= 9)) {
            T[b][a].Num = N;
            if (T[b][a].Num != 0) {
                T[b][a].HayNum = 1;
                T[b][a].Posibilidades = 0;
                for (c = 1; c <= 9; c++)
                    T[b][a].Posibles[c] = 0;
            }
            if (a == 9) { a = 0; b++; }
            a++;
        }
        car = getc(FSud);
    }
    fclose(FSud);
    scanf("%c", &car);
}

void ImprimeDatos(struct TpCasilla T[][10])
{
    int b, a, N;
    printf("\n\n\n\n\nNumeros que pueden ir en cada casilla\n\n\n");
    for (b = 1; b <= 9; b++) {
        for (a = 1; a <= 9; a++) {
            for (N = 1; N <= 9; N++)
                printf(" %d:%d ", N, T[b][a].Posibles[N]);
            printf("   ");
        }
        printf("\n");
    }
}

void ImprimeDatos2(struct TpCasilla T[][10])
{
    int b, a;

    printf("\nCANTIDAD DE POSIBILIDADES\n\n");
    for (b = 1; b <= 9; b++) {
        for (a = 1; a <= 9; a++) {
            printf("%d", T[b][a].Posibilidades);
            printf("   ");
        }
        printf("\n");
    }
    printf("\n\n");
}

void ImprimeDatos3(struct TpCasilla T[][10])
{
    int b, a;

    for (b = 1; b <= 9; b++) {
        for (a = 1; a <= 9; a++) {
            printf("%d", T[b][a].HayNum);
            printf("   ");
        }
        printf("\n");
    }
}

void ImprimeDatos4(struct TpCasilla T[][10])
{
    int b, a;

    printf("\nSUDOKU\n\n");
    for (b = 1; b <= 9; b++) {
        for (a = 1; a <= 9; a++) {
            printf("%d", T[b][a].Num);
            if ((a % 3) == 0) printf(" ");
        }
        printf("\n");
        if ((b % 3) == 0) printf("\n");
    }
    printf("\n\n");
}