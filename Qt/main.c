#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 500

struct Data
{ char fre;
  char s11_1;
  char *s11_2;
  char *s21_1;
  char *s21_2;
  char *s12_1;
  char *s12_2;
  char *s22_1;
  char *s22_2;
};

int Getline(FILE * file){
    int flag;
    int count = 0;
    file = fopen("/home/ke/QtWork/Aboutfile/test.S2P","r");
    while(!feof(file))
      {
        flag = fgetc(file);
        if(flag == '\n')
          count++;
      }
    //printf("hangshu:%d\n", count + 1);
    fclose(file);
    return count;
}

void Gettext(FILE * file){
    char ch = '#';
    char *ret;
    char *buffer;
    int flag ;
    int n;

    file = fopen("/home/ke/QtWork/Aboutfile/test.S2P","r");
    buffer = (char *)malloc (Getline(file) * SIZE * sizeof (char));
    //find the '#'
    for (n = 0; n < Getline(file); n++){
        fgets(buffer, 1024, file);
        if (strchr(buffer, ch) != NULL){
            printf("#location:%d\n", n + 1);
        }

    }





}

void Read(FILE *file){
    char *buffer;
    int n = Getline(file);
    double fre[n];
    double s11_1[n];
    double s11_2[n];
    double s21_1[n];
    double s21_2[n];
    double s12_1[n];
    double s12_2[n];
    double s22_1[n];
    double s22_2[n];

    char d1[50];
    char d2[50];
    char d3[50];
    char d4[50];
    char d5[50];
    char d6[50];
    char d7[50];
    char d8[50];
    char d9[50];

    int b =0;

    file = fopen("/home/ke/QtWork/Aboutfile/test.S2P","r");
    buffer = (char *)malloc (Getline(file) * SIZE * sizeof (char));

    while (!feof(file)) {
        //fscanf(file, "%s", buffer);
        fgets(buffer, 1024, file);
        sscanf(buffer, "%s %s %s %s %s %s %s %s %s", d1, d2, d3, d4, d5, d6, d7, d8, d9);
        //printf("%s %s %s %s %s %s %s %s %s\n", d1, d2, d3, d4, d5, d6, d7, d8, d9);

        fre[b] = atof(d1);
        s11_1[b] = atof(d2);
        s11_2[b] = atof(d3);
        s21_1[b] = atof(d4);
        s21_2[b] = atof(d5);
        s12_1[b] = atof(d6);
        s12_2[b] = atof(d7);
        s22_1[b] = atof(d8);
        s22_2[b] = atof(d9);
        printf("%lf %lf %lf %lf %lf %lf %lf %lf %lf\n", fre[b], s11_1[b], s11_2[b], s21_1[b], s21_2[b], s12_1[b], s12_2[b], s22_1[b], s22_2[b]);
        b++;
   }

    fclose(file);
}

int main()
{
    FILE *filehandle;
    Gettext(filehandle);
    //Read(filehandle);

    puts("Is here");


    return 0;
}
