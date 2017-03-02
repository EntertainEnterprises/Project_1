//@Author: Patrik Höpfl

#include <stdio.h>
#include <math.h>

#define DIMENSION 2
#define FUSS 0
#define SPITZE 1
#define FUSS_U_D 1
#define SPITZE_U_D 2

typedef struct _vektor
{
    double vektorkomponent[DIMENSION];  
}Vektor;

Vektor seiten_vektor_berechnung(Vektor bc, Vektor a)
{
    Vektor erg;
    erg.vektorkomponent[0] = bc.vektorkomponent[0] - a.vektorkomponent[0];
    erg.vektorkomponent[1] = bc.vektorkomponent[1] - a.vektorkomponent[1];
    return erg;
}

double flaechen_berechnung_dreieck(Vektor dreieckseite_1, Vektor dreieckseite_2)
{
    double kreuzprodukt = 0;
    double betrag = 0;
    double flaecheninhalt = 0;
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
    
   
    FILE* punkte_zuordnung = fopen("Punkte_zuordnung.csv", "w");

    Vektor d_eckpunkt[4]; //Eckpunkte des Dreiecks
    Vektor dreieckseitenvektor[2];  //TODO Überprüfung wegen Arraynamen globale Variable
    Vektor viereckseitenvektor[3];  //TODO Überprüfung wegen Arraynamen
    int flaecheninhalt_u_dreieck = 0;   //Flächeninhalt Urpsrungsdreieck
    double flaecheninhalt_viereck_d[3] = {0, 0, 0};    //Flaecheninhalt der drei Dreiecke innerhalb des Vierecks
    int flaecheninhalt_viereck_g = 0;   //Flaecheninhalt des Vierecks gesamt
    int aktuelles_dreieck = 0;
    int counter_s_1 = 0;
    int counter_s_2 = 0;
    char error[30] = "ausserhalb Patrik_Loesung";

    //Berechnung Flächeninhalt Ursprungsdreieck & Viereck bzw. Berechnung der Flächeninhalte der 3 enthaltenen Dreiecke.
    //Schritt 1: Einlesen des zu überprüfenden Punktes:
    
    //1. Schleife: So viele Wdh. wie "neue Punkte" in CSV-Datei
    FILE* neue_punkte = fopen("EAF_Testpunkte.csv", "r");
    for(int a = 0; a < 10; a++)
    {
        printf("Der neue Punkte wurde aus der CSV-Datei gelesen\n");
        fscanf(neue_punkte, "%lf; %lf\n", &d_eckpunkt[0].vektorkomponent[0], &d_eckpunkt[0].vektorkomponent[1]);
        counter_s_2 = 0;
        //2. Schleife: So viele Wdh. wie Eckpunkte in CSV-Datei.
        FILE* eckpunkte = fopen("EAF_Testdreiecke.csv", "r");
        for(int b = 0; b < 11; b++)
        {
            //Schritt 2: Einlesen der drei Eckpunkte des Urpsrungsdreiecks:
            for(int i = 0; i < 3; i++)
            {
                //printf("Eckpunkt %i wurde aus der CSV-Datei gelesen\n", i);
                fscanf(eckpunkte, "%lf; %lf; %i\n", &d_eckpunkt[i+1].vektorkomponent[0], &d_eckpunkt[i+1].vektorkomponent[1], &aktuelles_dreieck);
            }

            //Schritt 3: Berechnung der Seitenvektoren des Ursprungsdreiecks:
            for(int i = 0; i < 2; i++)
            {
                dreieckseitenvektor[i] = seiten_vektor_berechnung(d_eckpunkt[SPITZE_U_D +i], d_eckpunkt[FUSS_U_D]);
            }

            //Schritt 4: Berechnung der Seitenvektoren des Vierecks bzw. der drei innenliegenden Dreiecke
            for(int i = 0; i < 3; i++)
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
            for(int i = 0; i < 4; i++)
            {
                printf("Eckpunkt %i = (%lf, %lf)\n", i, d_eckpunkt[i].vektorkomponent[0], d_eckpunkt[i].vektorkomponent[1]);
            }
            /*
            //Ausgabe Dreieckseitenvektoren:
            for(int i = 0; i < 2; i++)
            {
                printf("Dreieckseitenvektor %i = (%lf, %lf)\n", i, dreieckseitenvektor[i].vektorkomponent[0], dreieckseitenvektor[i].vektorkomponent[1]);
            }
            */

            //Ausgabe Flaecheninhalt Ursprungsdreieck:
            printf("Flaecheninhalt Ursprung Dreieck: %i\n", flaecheninhalt_u_dreieck);
            /*
            //Ausgabe Viereckseitenvektoren:
            for(int i = 0; i < 3; i++)
            {
                printf("Viereckseitenvektor %i = (%lf, %lf)\n", i, viereckseitenvektor[i].vektorkomponent[0], viereckseitenvektor[i].vektorkomponent[1]);
            }
            

            //Ausgabe Flächeninhalte der drei Dreiecke innerhalb des Vierecks:
            for(int i = 0; i < 3; i++)
            {
                printf("Flaecheninhalt %i. Dreieck im Viereck: %lf\n", i, flaecheninhalt_viereck_d[i]);
            }
            */
        
            //Ausgabe Flächeninhalt Viereck gesamt:
            printf("Flaecheninhalt des Vierecks: %i\n", flaecheninhalt_viereck_g);

            //Ausgabe: aktuelles Dreieck
            printf("Aktuelles Dreieck: %i\n", aktuelles_dreieck);

            //Ausgabe: Counter:
            counter_s_2++;
            printf("Durchlaufnummer 2. Schleife: %i\n", counter_s_2);

            //Überprüfung ob Punkt im Dreieck liegt:
            if(flaecheninhalt_u_dreieck == flaecheninhalt_viereck_g)
            {
                fprintf(punkte_zuordnung, "%lf;%lf;%i\n", d_eckpunkt[0].vektorkomponent[0], d_eckpunkt[0].vektorkomponent[1], aktuelles_dreieck);
                fclose(eckpunkte);
                break;
            }
            else
            {
                //Dreieck hat nicht gepasst, einfach Schleife weiter machen lassen & nächstes Dreieck machen.
            }

            //Punkt liegt in keinem Dreieck:
            if(counter_s_2 == 10)
            {
                printf("ERROR: Keine Uebereinstimmung gefunden!\n");
                fprintf(punkte_zuordnung, "%lf;%lf;%s\n", d_eckpunkt[0].vektorkomponent[0], d_eckpunkt[0].vektorkomponent[1], error);
            }
        }   
        counter_s_1++;
        printf("Durchlaufnummer 1. Schleife: %i\n", counter_s_1);
    }

    fclose(neue_punkte);
    
    fclose(punkte_zuordnung);
    
    return 0;
}
