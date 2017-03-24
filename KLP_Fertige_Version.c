//@Author: Patrik Höpfl

#include <stdio.h>
#include <math.h>
#include <string.h>

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

int file_zeilen_berechnung(FILE* datei, char* dateiname)
{

    int counter = 0;
    char c;
    while ((c = fgetc(datei)) != EOF)
    if (c == '\n') 
    {
        counter++;
    }
    fclose(datei);
    fopen(dateiname, "r");
    return counter;
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
    
   
    

    Vektor d_eckpunkt[50]; //Eckpunkte des Dreiecks
    Vektor dreieckseitenvektor[50];  //TODO Überprüfung wegen Arraynamen globale Variable
    Vektor viereckseitenvektor[50];  //TODO Überprüfung wegen Arraynamen
    double flaecheninhalt_u_dreieck[50];  //Flächeninhalt Urpsrungsdreieck
    double flaecheninhalt_viereck_d[50];    //Flaecheninhalt der drei Dreiecke innerhalb des Vierecks
    double flaecheninhalt_u_gesamt = 0;    //Flaecheninhalt des Urpsrungspolygons.
    double flaecheninhalt_viereck_g = 0;   //Flaecheninhalt des Vierecks gesamt
    char aktuelles_polygon1[30];
    char aktuelles_polygon2[30];
    int counter_s_1 = 0;
    int counter_s_2 = 0;
    int counter_datei = 0;
    int counter_zugang = 0;
    char error[30] = "ausserhalb Patrik_Loesung";
    char error2[30] = "Beide FI 0";
    int zeilen_datei_punkte = 0;
    int zeilen_datei_eckpunkte = 0;
    char* datei_erg = "EAF_Punkte_Polygon_Zuordnung.csv";
    char* datei_neue_punkte = "Netz_EAF_Lieferungen_DezPunkt.csv";
    char* datei_eckpunkte = "EckpunkteEAF_DezPunkt000Nr_14.csv";
    

    FILE* punkte_zuordnung = fopen(datei_erg, "w");

    //Flaecheninhalte arrays mit Null befüllen:
    memset(flaecheninhalt_u_dreieck, 0, (sizeof(flaecheninhalt_u_dreieck)));
    memset(flaecheninhalt_viereck_d, 0, (sizeof(flaecheninhalt_viereck_d)));

    for(int i = 0; i < 10; i++)
    {
        d_eckpunkt[i].vektorkomponent[0] = 0;
        d_eckpunkt[i].vektorkomponent[1] = 0;
        dreieckseitenvektor[i].vektorkomponent[0] = 0;
        dreieckseitenvektor[i].vektorkomponent[1] = 0;
        viereckseitenvektor[i].vektorkomponent[0] = 0;
        viereckseitenvektor[i].vektorkomponent[1] = 0;
    }

    for(int i = 0; i < 10; i++)
    {
        printf("d_eckpunkt:\t\t %lf/%lf\n", d_eckpunkt[i].vektorkomponent[0], d_eckpunkt[i].vektorkomponent[1]);
        printf("dreieckseitenvektor:\t %lf/%lf\n", dreieckseitenvektor[i].vektorkomponent[0], dreieckseitenvektor[i].vektorkomponent[1]);
        printf("viereckseitenvektor:\t %lf/%lf\n", viereckseitenvektor[i].vektorkomponent[0], viereckseitenvektor[i].vektorkomponent[1]);
    }

    //Berechnung Flächeninhalt Ursprungsdreieck & Viereck bzw. Berechnung der Flächeninhalte der 3 enthaltenen Dreiecke.
    //Schritt 1: Einlesen des zu überprüfenden Punktes:
    
    //1. Schleife: So viele Wdh. wie "neue Punkte" in CSV-Datei
    FILE* neue_punkte = fopen(datei_neue_punkte, "r");
    zeilen_datei_punkte = file_zeilen_berechnung(neue_punkte, datei_neue_punkte);
    
    printf("Zeilen Datei Punkte :%i \n", zeilen_datei_punkte);
    
    for(int a = 0; a <= zeilen_datei_punkte; a++)
    {
        //Neuer Punkt aus CSV "Testpunkte" lesen und in ersten vektorn speicher (0/0):
        printf("Der neue Punkte wurde aus der CSV-Datei gelesen\n");
        fscanf(neue_punkte, "%lf; %lf\n", &d_eckpunkt[0].vektorkomponent[0], &d_eckpunkt[0].vektorkomponent[1]);
        counter_s_2 = 0;
        //2. Schleife: So viele Wdh. wie Eckpunkte in CSV-Datei.
        FILE* eckpunkte = fopen(datei_eckpunkte, "r");
        zeilen_datei_eckpunkte = file_zeilen_berechnung(eckpunkte, datei_eckpunkte);// Durch 3 wegen Dreiecke, muss angepasst werden.
        //printf("Zeilen Datei Eckpunkte :%i \n", zeilen_datei_eckpunkte);
        
        
        for(int b = 0; b < zeilen_datei_eckpunkte; b++)
        {
            //Schritt 2: Einlesen der Eckpunkte des aktuellen Polygons:
            //Einlesen des 1. Eckpunktes um die Nr. des Dreiecks in eine Variable zu speichern um vergleichen zu können:
            fscanf(eckpunkte, "%lf; %lf; %i; %s\n", &d_eckpunkt[1].vektorkomponent[0], &d_eckpunkt[1].vektorkomponent[1], &counter_datei, aktuelles_polygon1);
            // Schleifenzeahler für Eckpunkte einlesen.
            int j = 1;
            //Einlesen der nächsten Eckpunkte bis 0;0;0
            do
            {
                fscanf(eckpunkte, "%lf; %lf; %i; %s\n", &d_eckpunkt[j+1].vektorkomponent[0], &d_eckpunkt[j+1].vektorkomponent[1], &counter_datei, aktuelles_polygon2);
                j++;

            }while(strncmp(aktuelles_polygon1, aktuelles_polygon2, 30) == 0);
            
            d_eckpunkt[j].vektorkomponent[0] = d_eckpunkt[1].vektorkomponent[0];
            d_eckpunkt[j].vektorkomponent[1] = d_eckpunkt[1].vektorkomponent[1];
            

            printf("Schleifezaehler j = %i\n", j);

            /*
            
            for(int i = 0; i < 3; i++)
            {
                //printf("Eckpunkt %i wurde aus der CSV-Datei gelesen\n", i);
                fscanf(eckpunkte, "%lf; %lf; %i\n", &d_eckpunkt[i+1].vektorkomponent[0], &d_eckpunkt[i+1].vektorkomponent[1], &aktuelles_polygon1);
            }

            */
            /*
            //Schritt 3: Berechnung der Seitenvektoren des Ursprungsdreiecks:
            for(int i = 0; i < j - 2; i++)
            {
                dreieckseitenvektor[i] = seiten_vektor_berechnung(d_eckpunkt[2+i], d_eckpunkt[1]);
            }
            */

            //Unterteilung des Polygons in Dreiecke und berechnung deren Flächeninhalte. Schleife:
            for(int c = 1; c < j-2; c++)
            {
                printf("Ich bin in der c-Schleife\n");

                //Schritt 3: Berechnung der Seitenvektoren des Ursprungsdreiecks:
                for(int i = 0; i < 2; i++)
                {                                                                             
                    dreieckseitenvektor[i] = seiten_vektor_berechnung(d_eckpunkt[c+i+1], d_eckpunkt[1]);
                }
                //Schritt 4: Berechnung der Seitenvektoren des Vierecks bzw. der drei innenliegenden Dreiecke
                viereckseitenvektor[0] = seiten_vektor_berechnung(d_eckpunkt[1], d_eckpunkt[0]);

                for(int i = 0; i < 2; i++)
                {
                    viereckseitenvektor[i+1] = seiten_vektor_berechnung(d_eckpunkt[c+i+1], d_eckpunkt[0]);
                }
                viereckseitenvektor[3] = seiten_vektor_berechnung(d_eckpunkt[1], d_eckpunkt[0]);

                //Schritt 5: Berechnung Flächeninhalt Ursprungsdreieck:
               
                flaecheninhalt_u_dreieck[0] = flaechen_berechnung_dreieck(dreieckseitenvektor[0], dreieckseitenvektor[1]);
                
                
                //Summe der Flächeninhalte Ursprungsdreieck
                for(int i = 0; i < j - 3; i++)
                {
                    flaecheninhalt_u_gesamt += flaecheninhalt_u_dreieck[i];
                }
                

                //Schritt 6: Berechnung der Flächeninhalte der 3 enthaltenen Dreiecke im Viereck:
                //TODO: evtl 1. Vektor duplizieren auf dritten damit Schleife funktioniert. => Erledigt 
                for(int i = 0; i < 3; i++)
                {
                    flaecheninhalt_viereck_d[i] = flaechen_berechnung_dreieck(viereckseitenvektor[i], viereckseitenvektor[i+1]);
                }
                /*
                flaecheninhalt_viereck_d[0] = flaechen_berechnung_dreieck(viereckseitenvektor[0], viereckseitenvektor[1]);
                flaecheninhalt_viereck_d[1] = flaechen_berechnung_dreieck(viereckseitenvektor[1], viereckseitenvektor[2]);
                flaecheninhalt_viereck_d[2] = flaechen_berechnung_dreieck(viereckseitenvektor[2], viereckseitenvektor[0]);
                */

                //Schritt 7: Flächeninhalt Viereck gesamt:
                //TODO: Bisschen effizienter schreiben: soll hübscher aussehen

                for(int i = 0; i < 3; i++)
                {
                    flaecheninhalt_viereck_g += flaecheninhalt_viereck_d[i];
                }
                
                //flaecheninhalt_viereck_g = flaecheninhalt_viereck_d[0] + flaecheninhalt_viereck_d[1] + flaecheninhalt_viereck_d[2];

                //Ausgabe Eckpunktvektoren Dreieck:
                for(int i = 0; i < j+1; i++)
                {
                    printf("Eckpunkt %i = (%lf, %lf)\n", i, d_eckpunkt[i].vektorkomponent[0], d_eckpunkt[i].vektorkomponent[1]);
                }
                
                //Ausgabe Dreieckseitenvektoren:
                for(int i = 0; i < j-2; i++)
                {
                    printf("Dreieckseitenvektor %i = (%lf, %lf)\n", i, dreieckseitenvektor[i].vektorkomponent[0], dreieckseitenvektor[i].vektorkomponent[1]);
                }
                

                //Ausgabe Flaecheninhalt Ursprungsdreiecke:

                for(int i = 0; i < j - 3; i++)
                {
                    printf("Flaecheninhalt Ursprung Dreieck %i: %lf\n", i, flaecheninhalt_u_dreieck[i]);
                }

                //Ausgabe Flaecheninhalt Ursprungsdreiecke:
                printf("Flaecheninhalt Ursprungsdreieck gesamt: %lf\n", flaecheninhalt_u_gesamt);

                
                //Ausgabe Viereckseitenvektoren:
            
                for(int i = 0; i < 4; i++)
                {
                    printf("Viereckseitenvektor %i = (%lf, %lf)\n", i, viereckseitenvektor[i].vektorkomponent[0], viereckseitenvektor[i].vektorkomponent[1]);
                }
                
                
                //Ausgabe Flächeninhalte der drei Dreiecke innerhalb des Vierecks:
                for(int i = 0; i < 3; i++)
                {
                    printf("Flaecheninhalt %i. Dreieck im Viereck: %lf\n", i, flaecheninhalt_viereck_d[i]);
                }
                
            
                /*
                for(int i = 0; i < j - 1; i++)
                {
                    printf("Flaecheninhalt Viereck Dreieck %i: %lf\n", i, flaecheninhalt_viereck_d[i]);
                }
                */
            
                //Ausgabe Flächeninhalt Viereck gesamt:
                printf("Flaecheninhalt des Vierecks: %lf\n", flaecheninhalt_viereck_g);

                //Ausgabe: aktuelles Dreieck
                printf("Aktuelles Dreieck: %s\n", aktuelles_polygon1);

                //Ausgabe: Counter & Nummer Datei:
                counter_s_2++;
                //printf("Durchlaufnummer 2. Schleife: %i\n", counter_s_2);
                printf("Nummer in Datei: %i\n", counter_datei);
                
                /*          
                //Ausgabe komplette Dreiecke FI:
                for(int i = 0; i < 10; i++)
                {
                    printf("Flaecheninhalt Ursprung Dreieck %i: %lf\n", i, flaecheninhalt_u_dreieck[i]);
                }
                */

            
                //Überprüfung ob Punkt im Dreieck liegt:
                //Fall falls beides Fleacheninhalte 0 sind:

            
                //Punkt liegt in keinem Dreieck:
                if(flaecheninhalt_u_gesamt >= 0.99 *  flaecheninhalt_viereck_g && flaecheninhalt_u_gesamt <= 1.01 * flaecheninhalt_viereck_g)
                {
                    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
                    fprintf(punkte_zuordnung, "%lf;%lf;%s\n", d_eckpunkt[0].vektorkomponent[0], d_eckpunkt[0].vektorkomponent[1], aktuelles_polygon1);
                    fclose(eckpunkte);
                    counter_zugang++;
                    break;
                }
                if(flaecheninhalt_u_gesamt == 0 && flaecheninhalt_viereck_g == 0)
                {
                    printf("---------------------------------------------------------------------------------------------------------------------------------\n");
                    fprintf(punkte_zuordnung, "%lf;%lf;%s\n", d_eckpunkt[0].vektorkomponent[0], d_eckpunkt[0].vektorkomponent[1], error2);
                    break;
                }                
                else
                {
                    //Dreieck hat nicht gepasst, einfach Schleife weiter machen lassen & nächstes Dreieck machen.
                    memset(flaecheninhalt_u_dreieck, 0, (sizeof(flaecheninhalt_u_dreieck)));
                    memset(flaecheninhalt_viereck_d, 0, (sizeof(flaecheninhalt_viereck_d)));
                    flaecheninhalt_u_gesamt = 0;
                    flaecheninhalt_viereck_g = 0;
                }
            }
                
                if(zeilen_datei_eckpunkte == counter_datei-1) // TODO: Muss angepasst werden!
                {
                    printf("---------------------------------------------------------------------------------------------------------------------------------\n");
                    fprintf(punkte_zuordnung, "%lf;%lf;%s\n", d_eckpunkt[0].vektorkomponent[0], d_eckpunkt[0].vektorkomponent[1], error);
                    break;
                }

                if(counter_zugang == 1)
                {
                    counter_zugang = 0;
                    break;
                }
             
            
        }   
        counter_s_1++;
        printf("Durchlaufnummer 1. Schleife: %i\n", counter_s_1);
    }
    printf("Zeilen Datei Eckpunkte :%i \n", zeilen_datei_eckpunkte);

    fclose(neue_punkte);
    
    fclose(punkte_zuordnung);
    
    return 0;
}