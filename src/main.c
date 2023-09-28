#include <stdio.h>
#include <pthread.h>

int main(int argc, char *argv[])
{
    printf("\n\n===========SISTEMA ONDO HASIERATUA===========\n\n");

    if (pthread_create(&erl, NULL, (void *)erlojua, NULL) != 0)
    {
        perror("Failed to create threads");
        exit();
    } // Hariak sortzeko momentuan existitzen badira dagoeneko, honek "errorea" bueltatuko du
}