#include "../include/DatuEgiturak.h"

uint8_t agindu_mota_atera (uint32_t agindua){
    return (agindua >> 28) & 0xF;
} 

uint8_t lortu_erregistroa (uint32_t agindua, int n){
    if (n == 1) return (agindua >> 24) & 0xF;
    else if (n == 2) return (agindua >> 20) & 0xF;
    else return (agindua >> 16) & 0xF;
} 

uint32_t lortu_helbidea (uint32_t agindua){
    return agindua & 0xFFFF;
} 

/**
 * lortu_datua funtzioa egiteko dago oraindikan, memoria fisikoa inplementatzean egin
 */

void prozesatuAgindua(uint32_t agindua, uint32_t* erregistro_multzoa){
    uint8_t agindu_mota = agindu_mota_atera(agindua);
    switch (agindu_mota){
        case 0x0:
            uint8_t erregistroa = lortu_erregistroa(agindua, 1);
            uint32_t helbidea = lortu_helbidea(agindua);
            uint32_t datua = lortu_datua(helbidea); 
            erregistro_multzoa[erregistroa] = datua;
            printf("\nld  r%d, 0x%X", (int) erregistroa, helbidea);
            break;
        case 0x1:
            uint8_t erregistroa = lortu_erregistroa(agindua, 1);
            uint32_t helbidea = lortu_helbidea(agindua);
            uint32_t datua = lortu_datua(helbidea);
            printf("\nst  r%d, 0x%X", (int) erregistroa, helbidea);
            break;
        case 0x2:
            printf("\nadd");
            break;
        case 0x3:
            printf("\nsub");
            break;
        case 0x4:
            printf("\nmul");
            break;
        case 0x5:
            printf("\ndiv");
            break;
        case 0x6:
            printf("\nand");
            break;
        case 0x7:
            printf("\nor");
            break;
        case 0x8:
            printf("\nxor");
            break;
        case 0x9:
            printf("\nmov");
            break;
        case 0xA:
            printf("\ncmp");
            break;
        case 0xB:
            printf("\nb");
            break;
        case 0xC:
            printf("\nbeq");
            break;
        case 0xD:
            printf("\nbgt");
            break;
        case 0xE:
            printf("\nblt");
            break;
        case 0xF:
            printf("\nexit");
            break;
    } 
} 