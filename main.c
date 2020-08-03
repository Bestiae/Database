#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "project_9.h"


int main() {
    //otvarm file
    FILE *file;
    char *fname = "DB.txt";

    file = fopen(fname, "r+");

    if(file == NULL){
        printf("nedalo sa otvorit %s.\n", fname);
        return 0;
    }

    int id, den, mesiac, rok;
    double plat;
    char pozicia[20];
    char meno[20];

    int pocetZames = 0;
    while (fscanf(file, "%d %lf %s %s %d %d %d", &id, &plat, pozicia, meno, &den, &mesiac, &rok) != EOF) {
        pocetZames++;
    }
    rewind(file);


    //malloc pamet pre DB
    Zamestnanec *db;
    db = (Zamestnanec*)malloc(sizeof(Zamestnanec)*pocetZames);

    for (int i = 0; i < pocetZames; i++) {
        fscanf(file, "%d %lf %s %s %d %d %d", &db[i].id, &db[i].plat, db[i].pozicia, db[i].udaje.meno, &db[i].udaje.d_narodeniea.den,
                                                &db[i].udaje.d_narodeniea.mesiac, &db[i].udaje.d_narodeniea.rok);
    }
    rewind(file);

    printALL(db, pocetZames);
    //getchar();

    char prikaz[MAX_LEN] = {0};
    char slovo[MAX_LEN] = {0};


    int prem_na_del = -1;
    int super_prem = -3;
    int koniec_prog = 1;
    while(koniec_prog == 1){
        CLEAR_SCREEN();
        printf("pocet zamestnancov do insert je: %d\n", pocetZames);
        printALL(db, pocetZames);
        printf("\nPrikaz: ");
        int off = 0;
        while(fgets(prikaz, MAX_LEN, stdin)) {//!=NULL
            sscanf(prikaz, "%s", slovo);
            if(!strcmp(slovo, "insert")){ //chyba?

                prem_na_del = 3;

                off = strlen(slovo);
                //pocitam kolko je Zamestnancov +1, REALLOK A VYPIS
                pocetZames++;
                db = realloc(db, sizeof(Zamestnanec)*(pocetZames));

                sscanf(prikaz+off, "%d %lf %s %s %d %d %d", &db[pocetZames-1].id, &db[pocetZames-1].plat, db[pocetZames-1].pozicia,
                        db[pocetZames-1].udaje.meno, &db[pocetZames-1].udaje.d_narodeniea.den,
                           &db[pocetZames-1].udaje.d_narodeniea.mesiac, &db[pocetZames-1].udaje.d_narodeniea.rok);

                printf("pocet zamestnancov po insert je: %d\n", pocetZames);
                getchar();
                break;

            }else if(sscanf(prikaz, "%s", slovo) == 1)
            if(!strcmp(slovo, "end")){
                koniec_prog++;
                if(prem_na_del == 3){
                    for (int j = 0; j < pocetZames; j++) { //zapisuje do suboru
                        fprintf(file, "%d %.2lf %s %s %d %d %d\n", db[j].id, db[j].plat, db[j].pozicia, db[j].udaje.meno, db[j].udaje.d_narodeniea.den,
                                db[j].udaje.d_narodeniea.mesiac, db[j].udaje.d_narodeniea.rok);
                    }
                }else if(prem_na_del == 0){

                }

                getchar();
                break;
            }

        }
    }

    return 0;
}
