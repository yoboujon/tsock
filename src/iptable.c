#include "../header/iptable.h"

int iptableTest()
{
    struct listeIpTable * l = initListeIpTable();
    ajoutListeIpTable(l,creeIpTable("localhost",1));
    ajoutListeIpTable(l,creeIpTable("192.168.1.21",2));
    afficheListeIpTable(*l);
    return 0;
}

ipTable * creeIpTable(char *ipAddress,int idEmetteur)
{
    ipTable * iptablevector = malloc(sizeof(ipTable));
    iptablevector->idEmetteur=idEmetteur;
    iptablevector->tailleipAddress=strlen(ipAddress);
    iptablevector->ipAddress=(char*)malloc(sizeof(char)*iptablevector->tailleipAddress);
    strcpy(iptablevector->ipAddress,ipAddress);
    return iptablevector;
}

struct elementIpTable * initElementIpTable(void)
{
    struct elementIpTable * returnElement = malloc(sizeof(struct elementIpTable));
    returnElement->actualIpTable = creeIpTable("",0);
    returnElement->suiv = NULL;
    return returnElement;
}

struct listeIpTable * initListeIpTable(void)
{
    struct listeIpTable * l=malloc(sizeof(struct listeIpTable));
    l->debut=initElementIpTable();
    l->fin=initElementIpTable();
    l->courant=initElementIpTable();
    l->taille=0;
    return l;
}

void ajoutListeIpTable(struct listeIpTable * listeActuel,ipTable * lipTable)                               
{
    struct elementIpTable * elementActuel = malloc(sizeof(struct elementIpTable));    
    elementActuel->actualIpTable=lipTable;                                                                                     
    elementActuel->suiv=listeActuel->courant;                                                                                        
    listeActuel->debut=elementActuel;                                                     
    listeActuel->courant=elementActuel;
    listeActuel->taille=listeActuel->taille+1;                                                   
}

void afficheListeIpTable(struct listeIpTable listeActuel)
{
    struct elementIpTable * elementFinal = listeActuel.fin;
    struct elementIpTable * elementCourant = listeActuel.courant;
    while(elementCourant->suiv != elementFinal->suiv)
    {
        printf("Adresse IP : %s\tEmetteur = %d\n",elementCourant->actualIpTable->ipAddress,elementCourant->actualIpTable->idEmetteur);
        elementCourant=elementCourant->suiv;
    }
}

struct elementIpTable * existInListIP(struct listeIpTable listeActuel, char* ipAdress, bool * boolRetour)
{
    struct elementIpTable * elementFinal = listeActuel.fin;
    struct elementIpTable * elementCourant = listeActuel.courant;
    while(elementCourant->suiv != elementFinal->suiv)
    {
        if(strcmp(elementCourant->actualIpTable->ipAddress,ipAdress) == 0)
        {
            *boolRetour = true;
            return elementCourant;
        }
        elementCourant=elementCourant->suiv;
    };
    *boolRetour = false;
    return elementFinal;
}