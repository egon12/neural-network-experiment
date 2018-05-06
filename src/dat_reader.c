#include <stdio.h>

int main() {

    FILE *fd = fopen("iris_training.dat", "r");


    double n1, n2, n3, n4;
    char mat[3];
    fscanf(fd, "%lf,%lf,%lf,%lf,%s\n", &n1, &n2, &n3, &n4, mat);
    printf("n1 = %f, n2= %f, n3 = %f, n4 = %f, %s\n", n1, n2, n3, n4, mat);
    fclose(fd);

}
