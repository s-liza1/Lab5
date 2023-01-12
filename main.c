#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double);
void File_W(double x, int N, double delta,char group_name [40], char student_name [40]);
void binary_R(char group_name [40], char student_name [40]);
int main()
{
    char group_name[40]= {0};
    char student_name[40]= {0};
    double x1, x2, delta;
    int N;
    FILE* input_File = fopen ("File.txt", "r");
    if (input_File==NULL)
    {
        printf("Error");
    }
    else
    {
        fscanf( input_File, "%lf", &x1 );
        fscanf( input_File, "%lf", &x2 );
        fscanf( input_File, "%d", &N );
        fscanf( input_File, "%lf\n", &delta );
        fgets( group_name, 40, input_File );
        fgets( student_name, 40, input_File );
        fclose(input_File);
        File_W(x1,N,delta,group_name,student_name);
        binary_R(group_name,student_name);
    }
    return(0);
}
double f(double x)
{
    return sqrt(x + 1);
}
void File_W(double x, int N, double delta,char group_name [40], char student_name [40])
{
    FILE* input_table = fopen ("Table.txt", "w");
    FILE* bina = fopen ("Binary.bin", "w+b");
    if (input_table==NULL || bina==NULL)
    {
        printf("Error");
        return(0);
    }
    else
    {
        fwrite(&N, sizeof(int), 1, bina);
        fprintf(input_table, "\n^^^^^^^^^^^^^^^^^^^^^^^^\n");
        fprintf(input_table, "|N|\t |x|\t|F(x)|");
        fprintf(input_table, "\n^^^^^^^^^^^^^^^^^^^^^^^^\n");

        for(int i=0; i<N; i++)
        {
            fprintf(input_table,"|%d\t",i+1);
            fprintf(input_table,"|%.1f\t",x);
            fprintf(input_table,"|%.2f|\n",f(x));

            fwrite(&x, sizeof(double), 1, bina);
            double z;
            z=f(x);
            fwrite(&z,sizeof(double),1, bina);
            x+=delta;
        }
        fprintf(input_table, "%s%s", group_name, student_name );
        fclose(input_table);
        fclose(bina);
    }
}
void binary_R(char group_name [40], char student_name [40])
{
    int N=0;
    double num=0;
    FILE* bin = fopen("Binary.bin", "r+b");
    if (bin==NULL)
    {
        printf("Error");
    }
    else
    {
        printf("\n^^^^^^^^^^^^^^^^^^^^^^^^");
        printf("\n|N|\t |x|\t|F(x)|");
        printf("\n^^^^^^^^^^^^^^^^^^^^^^^^\n");
        fread(&N, sizeof(int), 1, bin);
        for(int i=0; i<N; i++)
        {
            printf("|%d\t|",i+1);
            fread(&num, sizeof(double), 1, bin);
            printf("%.1f\t|", num);
            fread(&num, sizeof(double), 1, bin);
            printf("%.2f| ", num);
            printf("\n");
        }
        printf("^^^^^^^^^^^^^^^^^^^^^^^^\n");
        printf("%s%s", group_name, student_name);
        fclose(bin);
    }
}
