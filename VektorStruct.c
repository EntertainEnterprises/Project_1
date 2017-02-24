#include <stdio.h>
#include <math.h>

#define DIMENSION 2
#define DREIECK 3

typedef struct _vektor
{
    int vektorkomponent[DIMENSION];
    int vektor_betrag;
   
}Vektor;

Vektor seiten_vektor_berechnung(Vektor bc, Vektor a)
{
    Vektor erg;
    erg.vektorkomponent[0] = bc.vektorkomponent[0] - a.vektorkomponent[0];
    erg.vektorkomponent[1] = bc.vektorkomponent[1] - a.vektorkomponent[1];
    return erg;
}

int main()
{
    Vektor eckpunkt[3];
    Vektor dreieckseitenvektor[2];
    //Eckpunkte Dreieck befüllen:
    for(int i = 0; i < DREIECK; i++)
    {
        printf("Bitte geben Sie drei Eckpunktvektoren ein.\n");
        scanf("%i", &eckpunkt[i].vektorkomponent[0]);
        scanf("%i", &eckpunkt[i].vektorkomponent[1]);
    }

    //Flächeninhalt berechnen eines Dreiecks:
    //Aufstellen zweier neuer Vektoren mit gleicher Basis:
    dreieckseitenvektor[0] = seiten_vektor_berechnung(eckpunkt[1], eckpunkt[0]);
    dreieckseitenvektor[1] = seiten_vektor_berechnung(eckpunkt[2], eckpunkt[0]);


    //Ausgabe Eckpunktvektoren:
    for(int i = 0; i < DREIECK; i++)
    {
        printf("Eckpunkt %i = (%i, %i)\n", i, eckpunkt[i].vektorkomponent[0], eckpunkt[i].vektorkomponent[1]);
    }

    //Ausgabe Dreieckseitenvektoren:
    for(int i = 0; i < 2; i++)
    {
        printf("Dreieckseitenvektoren %i = (%i, %i)\n", i, dreieckseitenvektor[i].vektorkomponent[0], dreieckseitenvektor[i].vektorkomponent[1]);
    }




    return 0;
}