#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "project_8.h"


int main() {
    srand((unsigned int) time(0));
    Zamestnanec db[MAX_ZAM];

//    Zamestnanec* BD;
//    int count = 5;
//    BD = (Zamestnanec*)malloc(count* sizeof(Zamestnanec));
//
//



    //gen zamestnanec
    genZamestnanec();
    // vygener zamestnancov
    genZamenestnacov(db, MAX_ZAM);

    //3 . vypis zamestn
    //printALL(db, MAX_ZAM);

    //
    char prikaz[MAX_LEN] = {0};
    char slovo[MAX_LEN] = {0};

    int koniec_prog = 1;
    while (koniec_prog == 1){
        CLEAR_SCREEN();
        printALL(db, MAX_ZAM);
        printf("\nPrikaz: ");
        int off = 0;
        while(fgets(prikaz, MAX_LEN, stdin)){//!=NULL
            //printALL(db, MAX_ZAM);
            int super_premenna = -3;
            int super_znak = -3;
            int super_zam = -3;

            off = 0;
            //printf("%s", prikaz);

            sscanf(prikaz, "%s", slovo);
            if(strcmp(slovo, "show")){ //chyba?
                break;//continue;
            }

//            //off += strlen(slovo);
//            if(sscanf(prikaz+off, "%s", slovo)==1){
//                if(!strcmp(slovo, "end")){
//                    koniec_prog++;
//                    getchar();
//                    break;
//                }
//            }

            off += strlen(slovo);
            if(sscanf(prikaz+off, "%s", slovo)==1){
                if(!strcmp(slovo, "end")){
                    koniec_prog++;
                    getchar();
                    break;
                }
                if(!strcmp(slovo, "all")){
                    super_zam = MAX_ZAM;
                    //printALL(db, MAX_ZAM);
                    //continue;
                }else{
                    super_zam = atoi(slovo);
                    if(super_zam > MAX_ZAM){
                        printf("Data Baza nema tolko zamestnancov, skus zadat menej.\nData Baza ma %d zamestnancov.\n", MAX_ZAM);
                        getchar();
                        break;//continue;
                    }else if(super_zam <= 0){
                        printf("Data Baza nema menej ako 1 zamestnancov, skus zadat viac.\nData Baza ma %d zamestnancov.\n", MAX_ZAM);
                        getchar();
                        break;//continue;
                    }
                    //printALL(db, super_zam);
                }
            }

            off += strlen(slovo)+1;
            if(sscanf(prikaz+off, "%s", slovo)==1){
                if(!strcmp(slovo, "where")){
                    //printf("je to where\n");
                    //continue;
                }
            }

            //podmienky pre plat, pozicia, meno, datum
            off += strlen(slovo)+1;
            if(sscanf(prikaz+off, "%s", slovo)==1){
                if(!strcmp(slovo, "plat")){
                    super_premenna = 0;
                }else if(!strcmp(slovo, "pozicia")){
                    super_premenna = 1;
                    //printf("je to poz\n");
                }else if(!strcmp(slovo, "meno")){
                    super_premenna = 2;
                    //printf("je to meno\n");
                }else if(!strcmp(slovo, "datum")){
                    super_premenna = 3;
                    //printf("je to dat\n");
                }
            }
            //pre where
            off += strlen(slovo)+1;
            if(sscanf(prikaz+off, "%s", slovo)==1){
                if((!strcmp(slovo, "<"))){
                    //printf("tvoj znak < sa dobre naicital\n");
                    super_znak = -1;
                }else if(!strcmp(slovo, ">")){
                    //printf("tvoj znak > sa dobre naicital\n");
                    super_znak = 1;
                }else if(!strcmp(slovo, "=")){
                    //printf("tvoj znak = sa dobre naicital\n");
                    super_znak = 0;
                }
            }
            // v konec to ide
            if((super_premenna == 0) && ((super_znak == -1) || (super_znak == 1) || (super_znak == 0))){
                off += strlen(slovo)+1;
                if(sscanf(prikaz+off, "%s", slovo)==1){
                    int c = atoi(slovo);
                    printWherePlat(db, MAX_ZAM, super_zam, c, super_znak);
                    getchar();
                    break;//continue;
                }
            }else if((super_premenna == 1) && ((super_znak == -1) || (super_znak == 1) || (super_znak == 0))){
                off += strlen(slovo)+1;
                if(sscanf(prikaz+off, "%s", slovo)==1){
                    printWherePozicia(db, MAX_ZAM, super_zam, slovo, super_znak);
                    getchar();
                    break;//continue;
                }
            }else if((super_premenna == 2) && ((super_znak == -1) || (super_znak == 1) || (super_znak == 0))){
                off += strlen(slovo)+1;
                if(sscanf(prikaz+off, "%s", slovo)==1){
                    printWhereMeno(db, MAX_ZAM, super_zam, slovo, super_znak);
                    getchar();
                    break;//continue;
                }
            }else if((super_premenna == 3) && ((super_znak == -1) || (super_znak == 1) || (super_znak == 0))){
                int den, mesiac, rok;
                off += strlen(slovo)+1;
                if(sscanf(prikaz+off, "%s", slovo)==1){
                    den = atoi(slovo);
                }
                off += strlen(slovo)+1;
                if(sscanf(prikaz+off, "%s", slovo)==1){
                    mesiac = atoi(slovo);
                }
                off += strlen(slovo)+1;
                if(sscanf(prikaz+off, "%s", slovo)==1){
                    rok = atoi(slovo);
                }
                printWhereDatum(db, MAX_ZAM, super_zam, den, mesiac, rok, super_znak);
                getchar();
                break;//continue;
            }else if((super_zam > -3) && ((super_premenna = -3) && (super_znak = -3))){
                printALL(db, super_zam);
                getchar();
                break;//continue;
            }
        }
    }

    return 0;
}