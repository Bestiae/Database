#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "project_9.h"

char* pozicie[3] = {"devevloper", "analitik", "tester"};

Zamestnanec genZamestnanec(){
    Zamestnanec z;
    z.id = rand()%1000;
    z.plat = rand()%2000 + 2000;
    strcpy(z.pozicia, pozicie[rand()%3]);
    int rand_len = rand()%10+1;
    for (int i = 0; i < rand_len; ++i) {
        z.udaje.meno[i] = rand()%('z'-'a') + 'a';
    }
    z.udaje.meno[rand_len] = '\0';
    z.udaje.d_narodeniea.den = rand()%31+1;
    z.udaje.d_narodeniea.mesiac = rand()%12+1;
    z.udaje.d_narodeniea.rok = rand()% (2019-1980) + 1980;

    return z;
}

void genZamenestnacov(Zamestnanec db[], int n){
    for (int i = 0; i < n; ++i) {
        db[i] = genZamestnanec();
    }
}

void  printZamestnanec(const Zamestnanec* z){
    int meno, pozicia;
    meno = strlen(z->udaje.meno);
    pozicia = strlen(z->pozicia);
    printf("%5.d | %8.2lf |",
           z->id,
           z->plat);

    printf(" %s", z->pozicia);
    for (int i = 0; i < 11 - pozicia; i++) {
        printf(" ");
    } printf("| ");

    printf(" %s", z->udaje.meno);
    for (int i = 0; i < 11 - meno; i++) {
        printf(" ");
    } printf("| ");

    printf("%d/%d/%d\n",
           z->udaje.d_narodeniea.den,
           z->udaje.d_narodeniea.mesiac,
           z->udaje.d_narodeniea.rok);

}

void printWherePlat(Zamestnanec db[], int n, int Z, int velkost, int super_znak){
    int pole[MAX_ZAM];
    int j = 0;

    if(super_znak == -1){
        for(int i = 0; i < n; i++){
            if(db[i].plat < velkost){
                pole[j] = i;
                j++;
            }
        }
    }else if(super_znak == 1){
        for(int i = 0; i < n; i++){
            if(db[i].plat > velkost){
                pole[j] = i;
                j++;
            }
        }
    }else if(super_znak == 0){
        for(int i = 0; i < n; i++){
            if(db[i].plat == velkost){
                pole[j] = i;
                j++;
            }
        }
    }

    if(Z == MAX_ZAM){
        printf("\n.................................................................\n");
        printf("|Num.|  ID  |   Plat   |  Position  |     Name    |    Date     |\n");
        printf("'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''\n");
        for (int k = 0; k < j; k++) {
            printf("|%3.d |", k+1);
            printZamestnanec(&db[pole[k]]);
        }
        printf("'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''\n");
    }else if(Z < MAX_ZAM){
        if(Z < j){
            printf("\n.................................................................\n");
            printf("|Num.|  ID  |   Plat   |  Position  |     Name    |    Date     |\n");
            printf("'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''\n");
            for (int k = 0; k < Z; k++) {
                printf("|%3.d |", k+1);
                printZamestnanec(&db[pole[k]]);
            }
            printf("'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''\n");
        }else if(Z >= j){
            printf("\n.................................................................\n");
            printf("|Num.|  ID  |   Plat   |  Position  |     Name    |    Date     |\n");
            printf("'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''\n");
            for (int k = 0; k < j; k++) {
                printf("|%3.d |", k+1);
                printZamestnanec(&db[pole[k]]);
            }
            printf("'''''''''''''''''MAX ZAMESTN. CO SA DALO NACITAT'''''''''''''''''\n");
        }

    }

}

void printWherePozicia(Zamestnanec db[], int n, int Z, char string[], int super_znak){
    //potrevujem porovnavat poziciju z databazou
    int pole[MAX_ZAM];
    int polePreMV[MAX_ZAM];
    int VM_ako_pismenko = 0;

    int k = 0; //pocet zamestnancov, ktory su potrebne
    int pomoc = 0; //pocet tych ktorych potrebujem
    char posledne_pismenko = string[strlen(string)-1];
    //printf("pos pismenko = %c\n", posledne_pismenko);

    //printf("slovo moje je = %s\n", string);
    //printf("znak posledny d db[1].pozicia = %c, pozicia = %s\n", db[1].pozicia[strlen(string)-1], db[1].pozicia);
    if(super_znak == 0){ //ked je rovne
        if(strlen(string) >= 2){
            for (int j = 0; j < n; j++){
                char *istr;
                istr = strstr(db[j].pozicia, string);
                if(istr != NULL){
                    pole[pomoc] = j;
                    pomoc++;
                }
            }
            //printf("pocet ludi ktore maju dev je = %d\n", pomoc);
            for(int o = 0; o < pomoc; o++){
                polePreMV[o] = pole[o];
                VM_ako_pismenko++;
            }
//        for (int a = 0; a < pomoc; a++) {
//            printZamestnanec(&db[polePreMV[a]]);
//        }
        }else if(strlen(string) < 2){
            int a = string[strlen(string)-1];
            //printf("znak moj je %c, cislo jeho je %d\n", a, a);

            for(int i = 0; i < n; i++){
                if(db[i].pozicia[0] == a){
                    //printf("string moj maly je %c mensi ako %c,  db[%d]\n", a, db[i].udaje.meno[0], i);
                    polePreMV[pomoc] = i;
                    pomoc++;
                    VM_ako_pismenko++;
                }
            }
        }
    }else if(super_znak == -1){ //ked je mensie
        //posledne_pismenko = string[strlen(string)-1];//zoberem posledne pismenko
        if(strlen(string) >= 2){ //ked tam je 2 pismenka
            char str[MAX_LEN] = "";
            strcpy(str, string);
            str[strlen(string)-1] = '\0';
            //printf("to je nas = %s, zmeneny je = %s\n", string, str);
            for (int j = 0; j < n; j++){
                char *istr;
                istr = strstr(db[j].pozicia, str);
                if(istr != NULL){
                    pole[pomoc] = j;
                    pomoc++;
                }
            }
            //printf("pocet ludi ktore maju %s je = %d\n",str, pomoc);
            int a = string[strlen(string)-1];
            printf("rovna tento char %c z tymto char je %c\n",db[pole[0]].pozicia[strlen(string)-1], a);
            for(int i = 0; i < pomoc; i++){
                if(db[pole[i]].pozicia[strlen(string)-1] < a ){
                    polePreMV[i] = pole[i];
                    VM_ako_pismenko++; //kolko sa nacitalo z mensimy pismenkamy
                }
            }
        }else if(strlen(string) < 2){
            int a = string[strlen(string)-1];
            //printf("znak moj je %c, cislo jeho je %d\n", a, a);

            for(int i = 0; i < n; i++){
                if(db[i].pozicia[0] < a){
                    //printf("string moj maly je %c mensi ako %c,  db[%d]\n", a, db[i].udaje.meno[0], i);
                    polePreMV[pomoc] = i;
                    pomoc++;
                    VM_ako_pismenko++;
                }
            }
        }
    }else if(super_znak == 1){ //ked je vecsie
        if(strlen(string) >= 2){
            char str[MAX_LEN] = "";
            strcpy(str, string);
            str[strlen(string)-1] = '\0';
            //printf("to je nas = %s, zmeneny je = %s\n", string, str);
            for (int j = 0; j < n; j++){
                char *istr;
                istr = strstr(db[j].pozicia, str);
                if(istr != NULL){
                    pole[pomoc] = j;
                    pomoc++;
                }
            }
            //printf("pocet ludi ktore maju %s je = %d\n",str, pomoc);

            int a = string[strlen(string)-1];

            for(int i = 0; i < pomoc; i++){
                if(db[pole[i]].pozicia[strlen(string)-1] > a ){
                    polePreMV[i] = pole[i];
                    VM_ako_pismenko++; //kolko sa nacitalo z vecsimy pismenkamy
                }
            }
        }else if(strlen(string) < 2){
            int a = string[strlen(string)-1];
            //printf("znak moj je %c, cislo jeho je %d\n", a, a);

            for(int i = 0; i < n; i++){
                if(db[i].pozicia[0] > a){
                    //printf("string moj maly je %c mensi ako %c,  db[%d]\n", a, db[i].udaje.meno[0], i);
                    polePreMV[pomoc] = i;
                    pomoc++;
                    VM_ako_pismenko++;
                }
            }
        }
    }

    if(Z == MAX_ZAM){
        if((VM_ako_pismenko == 0)){
            printf("Nemas ziadneho takeho zamestnanca!\n");
        }else {
            printf("\n.................................................................\n");
            printf("|Num.|  ID  |   Plat   |  Position  |     Name    |    Date     |\n");
            printf("'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''\n");
            for (int d = 0; d < pomoc; d++) {
                printf("|%3.d |", d + 1);
                printZamestnanec(&db[polePreMV[d]]);
            }
            printf("'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''\n");
        }
    }else if(Z < MAX_ZAM){
        if(Z <= pomoc){
            printf("\n.................................................................\n");
            printf("|Num.|  ID  |   Plat   |  Position  |     Name    |    Date     |\n");
            printf("'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''\n");
            for (int d = 0; d < Z; d++) {
                printf("|%3.d |", d+1);
                printZamestnanec(&db[polePreMV[d]]);
            }
            printf("'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''\n");
        }else if(Z >= pomoc){
            printf("\n.................................................................\n");
            printf("|Num.|  ID  |   Plat   |  Position  |     Name    |    Date     |\n");
            printf("'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''\n");
            for (int d = 0; d < pomoc; d++) {
                printf("|%3.d |", d+1);
                printZamestnanec(&db[polePreMV[d]]);
            }
            printf("'''''''''''''''''MAX ZAMESTN. CO SA DALO NACITAT'''''''''''''''''\n");
        }

    }

}

void printWhereMeno(Zamestnanec db[], int n, int Z, char string[], int super_znak){
    //potrevujem porovnavat poziciju z databazou
    int pole[MAX_ZAM];
    int polePreMV[MAX_ZAM];
    int VM_ako_pismenko = 0;

    int k = 0; //pocet zamestnancov, ktory su potrebne
    int pomoc = 0; //pocet tych ktorych potrebujem
    char posledne_pismenko = string[strlen(string)-1];
    //printf("pos pismenko = %c\n", posledne_pismenko);

    //printf("slovo moje je = %s\n", string);
    //printf("znak posledny d db[1].pozicia = %c, pozicia = %s\n", db[1].pozicia[strlen(string)-1], db[1].pozicia);
    if(super_znak == 0){ //ked je rovne
        if(strlen(string) >= 2){
            for (int j = 0; j < n; j++){
                char *istr;
                istr = strstr(db[j].udaje.meno, string);
                if(istr != NULL){
                    pole[pomoc] = j;
                    pomoc++;
                }
            }
            //printf("pocet ludi ktore maju dev je = %d\n", pomoc);
            for(int o = 0; o < pomoc; o++){
                polePreMV[o] = pole[o];
                VM_ako_pismenko++;
            }
//        for (int a = 0; a < pomoc; a++) {
//            printZamestnanec(&db[polePreMV[a]]);
//        }
        }else if(strlen(string) < 2){
            int a = string[strlen(string)-1];
            //printf("znak moj je %c, cislo jeho je %d\n", a, a);

            for(int i = 0; i < n; i++){
                if(db[i].udaje.meno[0] == a){
                    //printf("string moj maly je %c mensi ako %c,  db[%d]\n", a, db[i].udaje.meno[0], i);
                    polePreMV[pomoc] = i;
                    pomoc++;
                    VM_ako_pismenko++;
                }
            }
        }
    }else if(super_znak == -1){ //ked je mensie
        //posledne_pismenko = string[strlen(string)-1];//zoberem posledne pismenko
        if(strlen(string) >= 2){ //ked tam je 2 pismenka
            char str[MAX_LEN] = "";
            strcpy(str, string);
            str[strlen(string)-1] = '\0';
            //printf("to je nas = %s, zmeneny je = %s\n", string, str);
            for (int j = 0; j < n; j++){
                char *istr;
                istr = strstr(db[j].udaje.meno, str);
                if(istr != NULL){
                    pole[pomoc] = j;
                    pomoc++;
                }
            }
            //printf("pocet ludi ktore maju %s je = %d\n",str, pomoc);
            int a = string[strlen(string)-1];
            printf("rovna tento char %c z tymto char je %c\n",db[pole[0]].udaje.meno[strlen(string)-1], a);
            for(int i = 0; i < pomoc; i++){
                if(db[pole[i]].udaje.meno[strlen(string)-1] < a ){
                    polePreMV[i] = pole[i];
                    VM_ako_pismenko++; //kolko sa nacitalo z mensimy pismenkamy
                }
            }
        }else if(strlen(string) < 2){
            int a = string[strlen(string)-1];
            //printf("znak moj je %c, cislo jeho je %d\n", a, a);

            for(int i = 0; i < n; i++){
                if(db[i].udaje.meno[0] < a){
                    //printf("string moj maly je %c mensi ako %c,  db[%d]\n", a, db[i].udaje.meno[0], i);
                    polePreMV[pomoc] = i;
                    pomoc++;
                    VM_ako_pismenko++;
                }
            }
        }
    }else if(super_znak == 1){ //ked je vecsie
        if(strlen(string) >= 2){
            char str[MAX_LEN] = "";
            strcpy(str, string);
            str[strlen(string)-1] = '\0';
            //printf("to je nas = %s, zmeneny je = %s\n", string, str);
            for (int j = 0; j < n; j++){
                char *istr;
                istr = strstr(db[j].udaje.meno, str);
                if(istr != NULL){
                    pole[pomoc] = j;
                    pomoc++;
                }
            }
            //printf("pocet ludi ktore maju %s je = %d\n",str, pomoc);

            int a = string[strlen(string)-1];

            for(int i = 0; i < pomoc; i++){
                if(db[pole[i]].udaje.meno[strlen(string)-1] > a ){
                    polePreMV[i] = pole[i];
                    VM_ako_pismenko++; //kolko sa nacitalo z vecsimy pismenkamy
                }
            }
        }else if(strlen(string) < 2){
            int a = string[strlen(string)-1];
            //printf("znak moj je %c, cislo jeho je %d\n", a, a);

            for(int i = 0; i < n; i++){
                if(db[i].udaje.meno[0] > a){
                    //printf("string moj maly je %c mensi ako %c,  db[%d]\n", a, db[i].udaje.meno[0], i);
                    polePreMV[pomoc] = i;
                    pomoc++;
                    VM_ako_pismenko++;
                }
            }
        }
    }

    if(Z == MAX_ZAM){
        if((VM_ako_pismenko == 0)){
            printf("Nemas ziadneho takeho zamestnanca!\n");
        }else {
            printf("\n.................................................................\n");
            printf("|Num.|  ID  |   Plat   |  Position  |     Name    |    Date     |\n");
            printf("'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''\n");
            for (int d = 0; d < pomoc; d++) {
                printf("|%3.d |", d + 1);
                printZamestnanec(&db[polePreMV[d]]);
            }
            printf("'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''\n");
        }
    }else if(Z < MAX_ZAM){
        if(Z <= pomoc){
            printf("\n.................................................................\n");
            printf("|Num.|  ID  |   Plat   |  Position  |     Name    |    Date     |\n");
            printf("'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''\n");
            for (int d = 0; d < Z; d++) {
                printf("|%3.d |", d+1);
                printZamestnanec(&db[polePreMV[d]]);
            }
            printf("'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''\n");
        }else if(Z >= pomoc){
            printf("\n.................................................................\n");
            printf("|Num.|  ID  |   Plat   |  Position  |     Name    |    Date     |\n");
            printf("'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''\n");
            for (int d = 0; d < pomoc; d++) {
                printf("|%3.d |", d+1);
                printZamestnanec(&db[polePreMV[d]]);
            }
            printf("'''''''''''''''''MAX ZAMESTN. CO SA DALO NACITAT'''''''''''''''''\n");
        }

    }

}

void printWhereDatum(Zamestnanec db[], int n, int Z, int den, int mesiac, int rok, int super_znak){
    int pole[MAX_ZAM];
    int polePreMV[MAX_ZAM];
    int dalosanacitat = 0;
    int pomoc = 0;

    if(super_znak == 0){
        for (int i = 0; i < n; i++) {
            if((db[i].udaje.d_narodeniea.den == den) && (db[i].udaje.d_narodeniea.mesiac == mesiac) && (db[i].udaje.d_narodeniea.rok == rok)){
                pole[pomoc] = i;
                pomoc++;
                dalosanacitat++;
            }
        }
    }else if(super_znak == -1){
        for (int i = 0; i < n; i++) {
            if(db[i].udaje.d_narodeniea.rok < rok){
                pole[pomoc] = i;
                pomoc++;
                dalosanacitat++;
            }else if((db[i].udaje.d_narodeniea.rok == rok) && (db[i].udaje.d_narodeniea.mesiac < mesiac)){
                pole[pomoc] = i;
                pomoc++;
                dalosanacitat++;
            }else if((db[i].udaje.d_narodeniea.rok == rok) && (db[i].udaje.d_narodeniea.mesiac == mesiac) && (db[i].udaje.d_narodeniea.den < den)){
                pole[pomoc] = i;
                pomoc++;
                dalosanacitat++;
            }
        }
    }else if(super_znak == 1){
        for (int i = 0; i < n; i++) {
            if(db[i].udaje.d_narodeniea.rok > rok){
                pole[pomoc] = i;
                pomoc++;
                dalosanacitat++;
            }else if((db[i].udaje.d_narodeniea.rok == rok) && (db[i].udaje.d_narodeniea.mesiac > mesiac)){
                pole[pomoc] = i;
                pomoc++;
                dalosanacitat++;
            }else if((db[i].udaje.d_narodeniea.rok == rok) && (db[i].udaje.d_narodeniea.mesiac == mesiac) && (db[i].udaje.d_narodeniea.den > den)){
                pole[pomoc] = i;
                pomoc++;
                dalosanacitat++;
            }
        }
    }
    //printf("den %d, mesiac %d, rok %d\n", den, mesiac, rok);
    if(Z == MAX_ZAM){
        if((dalosanacitat == 0)){
            printf("Nemas ziadneho takeho zamestnanca!\n");
        }else {
            printf("\n.................................................................\n");
            printf("|Num.|  ID  |   Plat   |  Position  |     Name    |    Date     |\n");
            printf("'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''\n");
            for (int d = 0; d < pomoc; d++) {
                printf("|%3.d |", d + 1);
                printZamestnanec(&db[pole[d]]);
            }
            printf("'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''\n");
        }
    }else if(Z < MAX_ZAM){
        if(Z <= pomoc){
            printf("\n.................................................................\n");
            printf("|Num.|  ID  |   Plat   |  Position  |     Name    |    Date     |\n");
            printf("'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''\n");
            for (int d = 0; d < Z; d++) {
                printf("|%3.d |", d+1);
                printZamestnanec(&db[pole[d]]);
            }
            printf("'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''\n");
        }else if(Z >= pomoc){
            printf("\n.................................................................\n");
            printf("|Num.|  ID  |   Plat   |  Position  |     Name    |    Date     |\n");
            printf("'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''\n");
            for (int d = 0; d < pomoc; d++) {
                printf("|%3.d |", d+1);
                printZamestnanec(&db[pole[d]]);
            }
            printf("'''''''''''''''''MAX ZAMESTN. CO SA DALO NACITAT'''''''''''''''''\n");
        }

    }

}

void printALL(Zamestnanec db[], int n){
    printf("\n.................................................................\n");
    printf("|Num.|  ID  |   Plat   |  Position  |     Name    |    Date     |\n");
    //printf("-----------------------------------------------------------------\n");
    printf("'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''\n");
    for (int i = 0; i < n; ++i) {
        printf("|%3.d |", i+1);
        printZamestnanec(&db[i]);
    }
    printf("'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''\n");
}
