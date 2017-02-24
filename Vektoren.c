#include <stdio.h>
#include <math.h>

#define DIMENSION 2

typedef struct _vektor
{
    float vektor[DIMENSION];
    float vektor_betrag = 0;
    vektor[0] = 0;
    vektor[1] = 0;

}Vektor;

float vektor_betrag_berechnung(int x, int y)
{
    float betrag = sqrt(x * x + y * y);
    return betrag;
}

int main()
{
    float vektor_1[DIMENSION];
    float vektor_2[DIMENSION];
    float vektor_3[DIMENSION];
    float vektor_betrag = 0;

    vektor_1[0] = 10;
    vektor_1[1] = 10;

    vektor_2[0] = 15;
    vektor_2[1] = 20;

    vektor_3[0] = vektor_2[0] - vektor_1[0];
    vektor_3[1] = vektor_2[1] - vektor_1[1];

    vektor_betrag = vektor_betrag_berechnung(vektor_3[0], vektor_3[1]);



    printf("Vektor_3[a] = %f\n", vektor_3[0]);
    printf("Vektor_3[b] = %f\n", vektor_3[1]);
    printf("Vektorbetrag = %f\n", vektor_betrag);
    printf("");


}