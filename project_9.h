#ifndef PROG2_ZAD_9_PROJECT_9_H
#define PROG2_ZAD_9_PROJECT_9_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LEN 50
#define MAX_ZAM 10

// MAKRA na vymazanie obsahu konzoly a uspanie programu
#ifdef _WIN32
#include <windows.h>
#define CLEAR_SCREEN() system("cls")
#define SLEEP(sleepMs) Sleep(sleepMs)
#else
#include <unistd.h>
#define CLEAR_SCREEN() system("clear")
#define SLEEP(sleepMs) usleep(sleepMs * 1000)
#endif
//

typedef struct {
    int den, mesiac, rok;
}Datum;

typedef struct {
    char  meno[MAX_LEN];
    Datum d_narodeniea;
}Osobneudaje;

typedef struct {
    int id;
    char pozicia[MAX_LEN];
    double plat;
    Osobneudaje udaje;
}Zamestnanec;

Zamestnanec genZamestnanec();
void genZamenestnacov(Zamestnanec db[], int n);
void printALL(Zamestnanec db[], int n);
void printWherePlat(Zamestnanec db[], int n, int Z, int velkost, int super_znak);
void printWherePozicia(Zamestnanec db[], int n, int Z, char string[], int super_znak);
void printWhereMeno(Zamestnanec db[], int n, int Z, char string[], int super_znak);
void printWhereDatum(Zamestnanec db[], int n, int Z, int den, int mesiac, int rok, int super_znak);


#endif //PROG2_ZAD_9_PROJECT_9_H
