#include <stdio.h>
#include <math.h>

#define DIMENSION 2
#define DREIECK 3

typedef struct _vektor
{
    float vektorkomponent[DIMENSION];
    float vektor_betrag;
   
}Vektor;

Vektor seiten_vektor_berechnung(Vektor bc, Vektor a)
{
    Vektor erg;
    erg.vektorkomponent[0] = bc.vektorkomponent[0] - a.vektorkomponent[0];
    erg.vektorkomponent[1] = bc.vektorkomponent[1] - a.vektorkomponent[1];
    return erg;
}

float flaechen_berechnung_dreieck(Vektor dreieckseite_1, Vektor dreieckseite_2)
{
    float kreuzprodukt = 0;
    float betrag = 0;
    float flaecheninhalt = 0;
    kreuzprodukt = dreieckseite_1.vektorkomponent[0] * dreieckseite_2.vektorkomponent[1] - dreieckseite_1.vektorkomponent[1] * dreieckseite_2.vektorkomponent[0];
    if(kreuzprodukt < 0)
    {
        betrag = fabs(kreuzprodukt);
    }
    else
    {
        betrag = kreuzprodukt;
    }
    flaecheninhalt = 0.5 * betrag;
    return flaecheninhalt;
}

int main()
{
    Vektor eckpunkt[3];
    Vektor dreieckseitenvektor[2];
    float flaecheninhalt_dreieck = 0;
    //Eckpunkte Dreieck befüllen:
    for(int i = 0; i < DREIECK; i++)
    {
        printf("Bitte geben Sie drei Eckpunktvektoren ein.\n");
        scanf("%f", &eckpunkt[i].vektorkomponent[0]);
        scanf("%f", &eckpunkt[i].vektorkomponent[1]);
    }

    //Flächeninhalt berechnen eines Dreiecks:
    //Aufstellen zweier neuer Vektoren mit gleicher Basis:
    dreieckseitenvektor[0] = seiten_vektor_berechnung(eckpunkt[1], eckpunkt[0]);
    dreieckseitenvektor[1] = seiten_vektor_berechnung(eckpunkt[2], eckpunkt[0]);

    //Vektorprodukt und Betrag davon:
    flaecheninhalt_dreieck = flaechen_berechnung_dreieck(dreieckseitenvektor[0], dreieckseitenvektor[1]);

    //Ausgabe Eckpunktvektoren:
    for(int i = 0; i < DREIECK; i++)
    {
        printf("Eckpunkt %i = (%f, %f)\n", i, eckpunkt[i].vektorkomponent[0], eckpunkt[i].vektorkomponent[1]);
    }

    //Ausgabe Dreieckseitenvektoren:
    for(int i = 0; i < 2; i++)
    {
        printf("Dreieckseitenvektor %i = (%f, %f)\n", i, dreieckseitenvektor[i].vektorkomponent[0], dreieckseitenvektor[i].vektorkomponent[1]);
    }

    //Ausgabe Flaecheninhalt:
    printf("Flaecheninhalt: %f\n", flaecheninhalt_dreieck);




    return 0;
}