//@Author: Patrik Höpfl

#include <stdio.h>
#include <math.h>

#define DIMENSION 2
#define DREIECK 3
#define VIERECK 4
#define FUSS 0
#define SPITZE 1
#define FUSS_U_D 1
#define SPITZE_U_D 2
#define D_SEITENVEKTOREN_ANZAHL 2
#define V_SEITENVEKTOREN_ANZAHL 3

typedef struct _vektor
{
    float vektorkomponent[DIMENSION];  
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
    Vektor d_eckpunkt[DREIECK+1]; //Eckpunkte des Dreiecks
    Vektor dreieckseitenvektor[DREIECK-1];  //TODO Überprüfung wegen Arraynamen globale Variable
    Vektor viereckseitenvektor[VIERECK-1];  //TODO Überprüfung wegen Arraynamen
    float flaecheninhalt_u_dreieck = 0;   //Flächeninhalt Urpsrungsdreieck
    float flaecheninhalt_viereck_d[VIERECK-1] = {0, 0, 0};    //Flaecheninhalt der drei Dreiecke innerhalb des Vierecks
    float flaecheninhalt_viereck_g = 0;   //Flaecheninhalt des Vierecks gesamt

    //Berechnung Flächeninhalt Ursprungsdreieck & Viereck bzw. Berechnung der Flächeninhalte der 3 enthaltenen Dreiecke.
    //Schritt 1: Einlesen des zu überprüfenden Punktes:
    printf("Bitte einen Punkt eingeben damit ueberprueft werden kann ob er innerhalb oder ausserhalb des Dreiecks liegt.\n");
    scanf("%f", &d_eckpunkt[0].vektorkomponent[0]);
    scanf("%f", &d_eckpunkt[0].vektorkomponent[1]);
    
    //Schritt 2: Einlesen der drei Eckpunkte des Urpsrungsdreiecks:
    for(int i = 0; i < DREIECK; i++)
    {
        printf("Bitte geben Sie drei Eckpunkte des Ursprungsdreiecks ein.\n");
        scanf("%f", &d_eckpunkt[i+1].vektorkomponent[0]);
        scanf("%f", &d_eckpunkt[i+1].vektorkomponent[1]);
    }

    //Schritt 3: Berechnung der Seitenvektoren des Ursprungsdreiecks:
    for(int i = 0; i < D_SEITENVEKTOREN_ANZAHL; i++)
    {
        dreieckseitenvektor[i] = seiten_vektor_berechnung(d_eckpunkt[SPITZE_U_D +i], d_eckpunkt[FUSS_U_D]);
    }
    
    //Schritt 4: Berechnung der Seitenvektoren des Vierecks bzw. der drei innenliegenden Dreiecke
    for(int i = 0; i < V_SEITENVEKTOREN_ANZAHL; i++)
    {
        viereckseitenvektor[i] = seiten_vektor_berechnung(d_eckpunkt[SPITZE + i], d_eckpunkt[FUSS]);
    }

    //Schritt 5: Berechnung Flächeninhalt Ursprungsdreieck:
    flaecheninhalt_u_dreieck = flaechen_berechnung_dreieck(dreieckseitenvektor[0], dreieckseitenvektor[1]);

    //Schritt 6: Berechnung der Flächeninhalte der 3 enthaltenen Dreiecke im Viereck:
    //TODO: evtl 1. Vektor duplizieren auf dritten damit Schleife funktioniert.

    flaecheninhalt_viereck_d[0] = flaechen_berechnung_dreieck(viereckseitenvektor[0], viereckseitenvektor[1]);
    flaecheninhalt_viereck_d[1] = flaechen_berechnung_dreieck(viereckseitenvektor[1], viereckseitenvektor[2]);
    flaecheninhalt_viereck_d[2] = flaechen_berechnung_dreieck(viereckseitenvektor[2], viereckseitenvektor[0]);

    //Schritt 7: Flächeninhalt Viereck gesamt:
    //TODO: Bisschen effizienter schreiben: soll hübscher aussehen
    flaecheninhalt_viereck_g = flaecheninhalt_viereck_d[0] + flaecheninhalt_viereck_d[1] + flaecheninhalt_viereck_d[2];

    //Ausgabe Eckpunktvektoren Dreieck:
    for(int i = 0; i < DREIECK+1; i++)
    {
        printf("Eckpunkt %i = (%f, %f)\n", i, d_eckpunkt[i].vektorkomponent[0], d_eckpunkt[i].vektorkomponent[1]);
    }
    
    //Ausgabe Dreieckseitenvektoren:
    for(int i = 0; i < D_SEITENVEKTOREN_ANZAHL; i++)
    {
        printf("Dreieckseitenvektor %i = (%f, %f)\n", i, dreieckseitenvektor[i].vektorkomponent[0], dreieckseitenvektor[i].vektorkomponent[1]);
    }

    //Ausgabe Flaecheninhalt Ursprungsdreieck:
    printf("Flaecheninhalt Ursprung Dreieck: %f\n", flaecheninhalt_u_dreieck);

    //Ausgabe Viereckseitenvektoren:
    for(int i = 0; i < V_SEITENVEKTOREN_ANZAHL; i++)
    {
        printf("Viereckseitenvektor %i = (%f, %f)\n", i, viereckseitenvektor[i].vektorkomponent[0], viereckseitenvektor[i].vektorkomponent[1]);
    }
    

    //Ausgabe Flächeninhalte der zwei Dreiecke innerhalb des Vierecks:
    for(int i = 0; i < VIERECK-1; i++)
    {
        printf("Flaecheninhalt %i. Dreieck im Viereck: %f\n", i, flaecheninhalt_viereck_d[i]);
    }
  
    //Ausgabe Flächeninhalt Viereck gesamt:
    printf("Flaecheninhalt des Vierecks: %f\n", flaecheninhalt_viereck_g);


    //Überprüfung ob Punkt im Dreieck oder ausserhalb liegt:
    if(flaecheninhalt_viereck_g == flaecheninhalt_u_dreieck)
    {
        printf("Der gewaehlte Punkt liegt innerhalb des Dreiecks.\n");
    }
    else
    {
        printf("Der gewahlte Punkt liegt ausserhalb des Dreiecks.\n");
    }

    return 0;
}
