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
    Vektor dreieckseitenvektor[DREIECK-1];  //TODO Überprüfung wegen Arraynamen 
    Vektor viereckseitenvektor[VIERECK-1];  //TODO Überprüfung wegen Arraynamen
    float flaecheninhalt_dreieck = 0;   //Flächeninhalt Urpsrungsdreieck
    float flaecheninhalt_viereck_d1 = 0;    //Flaecheninhalt des 1. Dreiecks innerhalb des Vierecks
    float flaecheninhalt_viereck_d2 = 0;    //Flaecheninhalt des 2. Dreiecks innerhalb des Vierecks
    float flaecheninhalt_viereck_d3 = 0;    //Flaecheninhalt des 3. Dreiecks innerhalb des Vierecks
    float flaecheninhalt_viereck = 0;   //Flaecheninhalt des Vierecks gesamt

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

   /* 
    //Flächeninhalt berechnen eines Dreiecks:
    //Eckpunkte Dreieck befüllen:
    for(int i = 0; i < DREIECK; i++)
    {
        printf("Bitte geben Sie drei Eckpunktvektoren des Ursprungsdreiecks ein.\n");
        scanf("%f", &d_eckpunkt[i].vektorkomponent[0]);
        scanf("%f", &d_eckpunkt[i].vektorkomponent[1]);
    }

    //Aufstellen zweier neuer Vektoren mit gleichem Fußpunkt (Spitze - Fuß):
    dreieckseitenvektor[0] = seiten_vektor_berechnung(d_eckpunkt[SPITZE_1], d_eckpunkt[FUSS]);
    dreieckseitenvektor[1] = seiten_vektor_berechnung(d_eckpunkt[SPITZE_2], d_eckpunkt[FUSS]);

    //Vektorprodukt und Betrag davon:
    flaecheninhalt_dreieck = flaechen_berechnung_dreieck(dreieckseitenvektor[0], dreieckseitenvektor[1]);

    //Flächeninhalt Viereck berechnen:
    //Neuen Punkt/Eckpunkt eingeben zur Überprüfung:
    printf("Bitte einen Punkt eingeben damit ueberprueft werden kann ob er innerhalb oder ausserhalb des Dreiecks liegt.\n");
    scanf("%f", &neuer_punkt.vektorkomponent[0]);
    scanf("%f", &neuer_punkt.vektorkomponent[1]);

    //Eckpunkte Viereck befüllen (unnötig),sind bereits befüllt + neuer Punkt bereits eingegeben:
    //Aufstellen dreier neuer Vektoren mit gleichem Fußpunkt (Spitze - Fuß):
    viereckseitenvektor[0] = seiten_vektor_berechnung(d_eckpunkt[SPITZE_2], neuer_punkt);
    viereckseitenvektor[1] = seiten_vektor_berechnung(d_eckpunkt[SPITZE_1], neuer_punkt);
    viereckseitenvektor[2] = seiten_vektor_berechnung(d_eckpunkt[SPITZE_3], neuer_punkt);

    //Flächeninhalt der beiden Dreiecke innerhalb des Vierecksberechnen:
    flaecheninhalt_viereck_d1 = flaechen_berechnung_dreieck(viereckseitenvektor[0], viereckseitenvektor[1]);
    flaecheninhalt_viereck_d2 = flaechen_berechnung_dreieck(viereckseitenvektor[0], viereckseitenvektor[2]);

    //Flächeninhaltberechnung des gesammten Vierecks:
    flaecheninhalt_viereck = flaecheninhalt_viereck_d1 + flaecheninhalt_viereck_d2;
    */
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

    /*

    //Ausgabe Flaecheninhalt Ursprungsdreieck:
    printf("Flaecheninhalt Ursprung Dreieck: %f\n", flaecheninhalt_dreieck);
    
    //Ausgabe Eckpunktvektoren Viereck:
    //Ausgabe Eckpunkte Dreieck:
    for(int i = 0; i < DREIECK; i++)
    {
        printf("Eckpunkt %i = (%f, %f)\n", i, d_eckpunkt[i].vektorkomponent[0], d_eckpunkt[i].vektorkomponent[1]);
    }
    //Ausgabe Neuer Punkt:
    printf("Eckpunkt %i = (%f, %f) = zu ueberpruefender Punkt\n", VIERECK-1, neuer_punkt.vektorkomponent[0], neuer_punkt.vektorkomponent[1]);

    //Ausgabe Viereckseitenvektoren:
    for(int i = 0; i < VIERECK-1; i++)
    {
        printf("Viereckseitenvektor %i = (%f, %f)\n", i, viereckseitenvektor[i].vektorkomponent[0], viereckseitenvektor[i].vektorkomponent[1]);
    }

    //Ausgabe Flächeninhalte der zwei Dreiecke innerhalb des Vierecks:
    printf("Flaecheninhalt 1. Dreieck im Viereck: %f\n", flaecheninhalt_viereck_d1);
    printf("Flaecheninhalt 2. Dreieck im Viereck: %f\n", flaecheninhalt_viereck_d2);
    printf("Flaecheninhalt des Vierecks: %f\n", flaecheninhalt_viereck);

    if(flaecheninhalt_viereck < flaecheninhalt_dreieck)
    {
        printf("Der gewaehlte Punkt liegt innerhalb des Dreiecks.\n");
    }
    else
    {
        printf("Der gewahlte Punkt liegt ausserhalb des Dreiecks.\n");
    }

    */

    return 0;
}
