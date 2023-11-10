#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "../include/config.h"
#include "../include/erlojua.h"
#include "../include/timer.h"
#include "../include/SD.h"
#include "../include/PG.h"
#include "../include/DataEgiturak.h"

int done = 0;
int freq;

long clockF, SDF, PGF;

pthread_t cl, timSD, timPG, tSD, tPG;

pthread_mutex_t mutex;

pthread_cond_t cond1, cond2;

int main(int argc, char *argv[])
{

    
    if (argc != 4)
    {
        printf("Argumentuak ez dira ondo pasatu\n\n");
        printf("========================= Argumentuak nola pasa =========================\n\n");
        printf("./seso <clock frequency> <Scheduler frequency> <Process Generator>\n\n");
        printf("Erloju, Scheduler eta Process Generator-aren frekuentzia ms-tan hartuko da.\n\n");
        printf("Frekuentzia = (Sartutako datua) * 1000");
        printf("=========================================================================\n\n");
        return 1;
    }
    else
    {
        clockF = 1000.0 * strtol(argv[1], NULL, 10);
        SDF = 1000.0 * strtol(argv[2], NULL, 10);
        PGF = 1000.0 * strtol(argv[3], NULL, 10);
    }
    

    printf("\n\n===========SISTEMA ONDO HASIERATUA===========\n\n");

    /*Gure ilara sortu eta abiarazi*/
    struct ProcessQueue queue;
    initQueue(&queue);

    pthread_mutex_init(&mutex, NULL);
    printf("Mutexa ondo hasieratu da\n");
    pthread_cond_init(&cond1, NULL);
    printf("Lehen baldintza ondo hasieratu da\n");
    pthread_cond_init(&cond2, NULL);
    printf("Bigarren baldintza ondo hasieratu da\n");

    if (pthread_create(&cl, NULL, (void *)erlojua, NULL) != 0)
    {
        perror("Failed to create threads");

    } // Hariak sortzeko momentuan existitzen badira dagoeneko, honek "errorea" bueltatuko du

    if (pthread_create(&timSD, NULL, (void *)timer_SD, NULL) != 0)
    {
        perror("Failed to create threads");
    }

    if (pthread_create(&timPG, NULL, (void *)timer_PG, NULL) != 0)
    {
        perror("Failed to create threads");
    }

    if (pthread_create(&tPG, NULL, (void *)processGenerator, NULL) != 0)
    {
        perror("Failed to create threads");
    }

    if (pthread_create(&tSD, NULL, (void *)scheduler, NULL) != 0)
    {
        perror("Failed to create threads");
    }

    printf("\n\n");

    // HARIEN testuinguru osoa hemen joineatzen da dena ondo amaitzeko
    if (pthread_join(cl, NULL) != 0)
        perror("Failed to join threads");
    if (pthread_join(timSD, NULL) != 0)
        perror("Failed to join threads");
    if (pthread_join(timPG, NULL) != 0)
        perror("Failed to join threads");
    if (pthread_join(tSD, NULL) != 0)
        perror("Failed to join threads");
    if (pthread_join(tPG, NULL) != 0)
        perror("Failed to join threads");

    printf("\n\n");

    // MUTEX-aren testuinguru osoa hemen amaitzen da dena suntsituz
    pthread_mutex_destroy(&mutex);
    printf("Mutexa ondo amaitu da\n");
    pthread_cond_destroy(&cond1);
    printf("Lehen baldintza ondo amaitu da\n");
    pthread_cond_destroy(&cond2);
    printf("Bigarren baldintza ondo amaitu da\n");

    return 0;
}