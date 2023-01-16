#include <stdio.h>                                  
#include <stdlib.h>                                 
#include <string.h>                                 
#include <stdbool.h> 

struct message{
    char *data;
    int tailleData;
    int idEmeteur;
    struct message *messageSuiv;
    struct message *messageFin;
};

typedef struct {

    int idRecept;
    struct BAL *BALSuiv;
    struct BAL *BALFin;
    struct message *message;
}BAL;


struct message creeMessage(char *dataPara,int idEmeteurPara);

int main(void){
    char * txt="simon";
    struct message *listeMessage =malloc(sizeof(struct message));
    *listeMessage=creeMessage(txt,12);
    printf("idEmeteur = %d\n",listeMessage->idEmeteur);
    printf("data=%s\n",listeMessage->data);
    printf("taille data=%d\n",listeMessage->tailleData);
    return 0;
}



struct message creeMessage(char *dataPara,int idEmeteurPara){
    int tailleDataPara =strlen(dataPara);
    struct message * elementMessage  =(struct message *)malloc(sizeof(struct message));

    elementMessage->idEmeteur=idEmeteurPara;
    elementMessage->tailleData=tailleDataPara;
    elementMessage->data=(char*)malloc(sizeof(char)*tailleDataPara);
    strcpy(elementMessage->data,(dataPara));
    return *elementMessage;
}