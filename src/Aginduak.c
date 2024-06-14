#include "../include/DatuEgiturak.h"
#include "../include/config.h"

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

int prozesatuAgindua(uint32_t agindua, uint32_t* erregistro_multzoa){
    uint8_t agindu_mota = agindu_mota_atera(agindua);
    switch (agindu_mota){
        case 0x0:
            uint8_t erregistroa = lortu_erregistroa(agindua, 1);
            uint32_t helbidea = lortu_helbidea(agindua);
            uint32_t datua = lortu_datua(helbidea); 
            erregistro_multzoa[erregistroa] = datua;
            printf("\nld    r%d, 0x%X", (int) erregistroa, helbidea);
            break;
        case 0x1:
            uint8_t erregistroa = lortu_erregistroa(agindua, 1);
            uint32_t helbidea = lortu_helbidea(agindua);
            uint32_t datua = lortu_datua(helbidea);
            printf("\nst    r%d, 0x%X", (int) erregistroa, helbidea);
            break;
        case 0x2:
            uint8_t erregistroa1 = lortu_erregistroa(agindua, 1);
            uint8_t erregistroa2 = lortu_erregistroa(agindua, 2);
            uint8_t erregistroa3 = lortu_erregistroa(agindua, 3);
            erregistro_multzoa[erregistroa1] =  erregistro_multzoa[erregistroa2] + erregistro_multzoa[erregistroa3];
            printf("\nadd   r%d, r%d, r%d", (int) erregistroa1, (int) erregistroa2, (int) erregistroa3);
            break;
        case 0x3:
            uint8_t erregistroa1 = lortu_erregistroa(agindua, 1);
            uint8_t erregistroa2 = lortu_erregistroa(agindua, 2);
            uint8_t erregistroa3 = lortu_erregistroa(agindua, 3);
            erregistro_multzoa[erregistroa1] =  erregistro_multzoa[erregistroa2] - erregistro_multzoa[erregistroa3];
            printf("\nsub   r%d, r%d, r%d", (int) erregistroa1, (int) erregistroa2, (int) erregistroa3);
            break;
        case 0x4:
            uint8_t erregistroa1 = lortu_erregistroa(agindua, 1);
            uint8_t erregistroa2 = lortu_erregistroa(agindua, 2);
            uint8_t erregistroa3 = lortu_erregistroa(agindua, 3);
            erregistro_multzoa[erregistroa1] =  erregistro_multzoa[erregistroa2] * erregistro_multzoa[erregistroa3];
            printf("\nmul   r%d, r%d, r%d", (int) erregistroa1, (int) erregistroa2, (int) erregistroa3);
            break;
        case 0x5:
            uint8_t erregistroa1 = lortu_erregistroa(agindua, 1);
            uint8_t erregistroa2 = lortu_erregistroa(agindua, 2);
            uint8_t erregistroa3 = lortu_erregistroa(agindua, 3);
            erregistro_multzoa[erregistroa1] =  erregistro_multzoa[erregistroa2] / erregistro_multzoa[erregistroa3];
            printf("\ndiv   r%d, r%d, r%d", (int) erregistroa1, (int) erregistroa2, (int) erregistroa3);
            break;
        case 0x6:
            uint8_t erregistroa1 = lortu_erregistroa(agindua, 1);
            uint8_t erregistroa2 = lortu_erregistroa(agindua, 2);
            uint8_t erregistroa3 = lortu_erregistroa(agindua, 3);
            erregistro_multzoa[erregistroa1] =  erregistro_multzoa[erregistroa2] & erregistro_multzoa[erregistroa3];
            printf("\nand   r%d, r%d, r%d", (int) erregistroa1, (int) erregistroa2, (int) erregistroa3);
            break;
        case 0x7:
            uint8_t erregistroa1 = lortu_erregistroa(agindua, 1);
            uint8_t erregistroa2 = lortu_erregistroa(agindua, 2);
            uint8_t erregistroa3 = lortu_erregistroa(agindua, 3);
            erregistro_multzoa[erregistroa1] =  erregistro_multzoa[erregistroa2] | erregistro_multzoa[erregistroa3];
            printf("\nor   r%d, r%d, r%d", (int) erregistroa1, (int) erregistroa2, (int) erregistroa3);
            break;
        case 0x8:
            uint8_t erregistroa1 = lortu_erregistroa(agindua, 1);
            uint8_t erregistroa2 = lortu_erregistroa(agindua, 2);
            uint8_t erregistroa3 = lortu_erregistroa(agindua, 3);
            erregistro_multzoa[erregistroa1] =  erregistro_multzoa[erregistroa2] ^ erregistro_multzoa[erregistroa3];
            printf("\nxor   r%d, r%d, r%d", (int) erregistroa1, (int) erregistroa2, (int) erregistroa3);
            break;
        case 0x9:
            uint8_t erregistroa1 = lortu_erregistroa(agindua, 1);
            uint8_t erregistroa2 = lortu_erregistroa(agindua, 2);
            erregistro_multzoa[erregistroa1] = erregistro_multzoa[erregistroa2];  
            printf("\nmov   r%d, r%d", (int) erregistroa1, (int) erregistroa2);
            break;
        case 0xA:
            uint8_t erregistroa1 = lortu_erregistroa(agindua, 1);
            uint8_t erregistroa2 = lortu_erregistroa(agindua, 2);
            uint8_t lag = erregistro_multzoa[erregistroa1] - erregistro_multzoa[erregistroa2];
            printf("\ncmp   r%d, r%d", (int) erregistroa1, (int) erregistroa2);
            return (int) lag;
            break;
        case 0xB:
            //adierazitako helbidera jauzi egin, PC = branch
            uint32_t helbidea = lortu_helbidea(agindua);
            uint32_t datua = lortu_datua(helbidea); 
            printf("\nb     %X", helbidea);
            break;
        case 0xC:
            //adierazitako helbidera jauzi egin cc == 0 bada
            printf("\nbeq   %X", helbidea);
            break;
        case 0xD:
            //adierazitako helbidera jauzi egin cc > 0 bada
            uint32_t helbidea = lortu_helbidea(agindua);
            uint32_t datua = lortu_datua(helbidea); 
            printf("\nbgt   %X", helbidea);
            break;
        case 0xE:
            //adierazitako helbidera jauzi egin cc < 0 bada
            uint32_t helbidea = lortu_helbidea(agindua);
            uint32_t datua = lortu_datua(helbidea); 
            printf("\nblt   %X", helbidea);
            break;
        case 0xF:
            printf("\nexit");
            amaituProg();
            break;
    } 
    return 0;
} 