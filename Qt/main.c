#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 500

typedef struct
{
    double x;
    double y;

}SData;

typedef struct
{
    char x;
    char y;

}SData_c;

//Get the file line nums;
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

//Get the '#' location;
int Gettextline(FILE * file){
    char ch = '#';

    char *buffer;

    int n;

    file = fopen("/home/ke/QtWork/Aboutfile/test.S2P","r");
    buffer = (char *)malloc (Getline(file) * SIZE * sizeof (char));
    //find the '#'
    for (n = 0; n < Getline(file); n++){
        fgets(buffer, 1024, file);
        if (strchr(buffer, ch) != NULL){
            //printf("#location:%d\n", n + 1);
            break;
        }
    }
    //printf("#location:%d\n", n + 1);
    fclose(file);
    return n + 1;

}

//Read the file from data line;
void Read(FILE *file){
    char *buffer;
    int n = Getline(file);
    int m = Gettextline(file);
    int count = 0;
    int flag;
    double fre[n-m];

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

    SData s11[n-m];
    SData s21[n-m];
    SData s12[n-m];
    SData s22[n-m];

    file = fopen("/home/ke/QtWork/Aboutfile/test.S2P","r");
    buffer = (char *)malloc (Getline(file) * SIZE * sizeof (char));

    while (!feof(file)) {

        flag = fgetc(file);
        if(flag == '\n')
          count++;
        while(count >= m){
            //fscanf(file, "%s", buffer);
            fgets(buffer, 1024, file);
            sscanf(buffer, "%s %s %s %s %s %s %s %s %s", d1, d2, d3, d4, d5, d6, d7, d8, d9);
            //printf("%s %s %s %s %s %s %s %s %s\n", d1, d2, d3, d4, d5, d6, d7, d8, d9);

            fre[b]   = atof(d1);
            s11[b].x = atof(d2);
            s11[b].y = atof(d3);
            s21[b].x = atof(d4);
            s21[b].y = atof(d5);
            s12[b].x = atof(d6);
            s12[b].y = atof(d7);
            s22[b].x = atof(d8);
            s22[b].y = atof(d9);
            printf("%lf %lf %lf %lf %lf %lf %lf %lf %lf\n", fre[b], s11[b].x, s11[b].y, s21[b].x, s21[b].y, s12[b].x, s12[b].y, s22[b].x
                    , s22[b].y);
            b++;

            if (b > n - m)
                break;
        }
   }

    fclose(file);
}

int main()
{
    FILE *filehandle = NULL;
    Gettextline(filehandle);
    Read(filehandle);

    puts("Is here");


    return 0;
}
