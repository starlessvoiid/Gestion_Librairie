
//Structure représentant l'adhérent:

#define MAX_LIVRES 3

typedef struct{
        int num_adh;
        char nom_adh[30];
        char prenom_adh[30];
        char* email_adh;
        char* adress_adh;
        int nbre_emprunts_adh;
}adherent;

typedef adherent* liste_adherents; //Liste des adherents disponibles.

liste_adherents *ajouter_adherent(){
        adherent *nouveau_adherent=(adherent*)malloc(sizeof(adherent));
        puts("Entrez le numero de l'adherent : ");
        scanf("%d",nouveau_adherent -> num_adh);
}
