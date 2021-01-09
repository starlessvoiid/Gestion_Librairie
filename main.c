#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#define FICHIER "adherent.dat"

typedef struct{
    int num_adh;
    char nom_adh[20];
    char prenom_adh[20];
    char email_adh[30];
    char address_adh[30];
    int nbre_emprunts_adh;
}adherent;

void ajouter_adherent();
void get_adherent();
void lister_adherents();
void search_adherent();
void supprimer_adherent();
void modifier_adherent();
int check_adherent(int num);


void main()
{
int opt;

    while(1)
    {
        printf("\n***** MENU ******\n");
        printf("1. Ajouter Adherent\n");
        printf("2. Liste des adherents\n");
        printf("3. Trouver l'adherent (Par numero)\n");
        printf("4. Cherchez adherent (par nom)\n");
        printf("5. Supprimer un adherent\n");
        printf("6. Modifier adherent\n");
        printf("7. Quitter\n");
        printf("Enter your choice [1-5] :");
        scanf("%d",&opt);

        switch(opt)
        {
           case 1: ajouter_adherent(); break;
           case 2: lister_adherents(); break;
           case 3: get_adherent(); break;
           case 4: search_adherent(); break;
           case 5: supprimer_adherent(); break;
           case 6: modifier_adherent(); break;
           case 7: exit(0);
        } // switch
    } // while
} // main()


void ajouter_adherent()
{
    FILE *fp;
    adherent nouveau;

       fp = fopen(FICHIER,"ab");
       if (fp==NULL)
       {
           printf("Sorry! File could not be opened!");
           exit(0);
       }
        fflush(stdin); // clear keyboard buffer
        printf("Numero de l'adherent :");
        scanf("%d",&nouveau.num_adh);
        if (check_adherent(nouveau.num_adh)==1){
            printf("Oops..adherent deja existant\n");
        }
        else{
            fflush(stdin);
            printf("Nom de l'adherent :");
            gets(nouveau.nom_adh);
            fflush(stdin);
            printf("Prenom de l'adherent :");
            gets(nouveau.prenom_adh);
            fflush(stdin);
            printf("Email de l'adherent :");
            gets(nouveau.email_adh);
            fflush(stdin);
            printf("Address de l'adherent :");
            gets(nouveau.address_adh);
            fwrite(&nouveau,sizeof(adherent),1,fp);
            printf("\nContact Saved Successfully!\n");
        }
       fclose(fp);
       printf("\nPress a key to continue...\n");
       getch();
       system("cls");
}

void lister_adherents()
{
    FILE *fp;
    adherent nouveau;
    int count;

       fp = fopen(FICHIER,"rb");
       if (fp==NULL)
       {
           printf("Erreur...");
           exit(0);
       }
       printf("\nListe des adherents\n");
       printf("\n================\n");
       printf("%-20s %-20s %-20s %-30s %-30s %s\n\n","Numero","Nom","Prenom","E-mail","Address","Livres Empruntes");
       while(1)
       {
         count = fread(&nouveau,sizeof(nouveau),1,fp);
         if (count == 0)
            break;
         printf("%-20d %-20s %-20s %-30s %-30s %d\n",nouveau.num_adh,nouveau.nom_adh,nouveau.prenom_adh,nouveau.email_adh,
                                       nouveau.address_adh,nouveau.nbre_emprunts_adh);
       }

       fclose(fp);
       printf("\nPress a key to continue...\n");
       getch();
       system("cls");
}

void get_adherent()
{
    FILE *fp;
    adherent nouveau;
    int id,count;

       fp = fopen(FICHIER,"rb");
       if (fp==NULL)
       {
           printf("Sorry! File could not be opened!");
           exit(0);
       }

       printf("Enter contact id : ");\
       scanf("%d",&id);
       fseek(fp, (id-1) * sizeof(nouveau), SEEK_SET);
       count = fread(&nouveau,sizeof(nouveau),1,fp);
       if (count == 0)
            printf("Cet adherent n'existe pas\n");
       else
            printf("%-20d %-20s %-20s %-30s %-30s %d\n",nouveau.num_adh,nouveau.nom_adh,nouveau.prenom_adh,nouveau.email_adh,
                                       nouveau.address_adh,nouveau.nbre_emprunts_adh);

       fclose(fp);
       printf("\nPress a key to continue...\n");
       getch();
       system("cls");
}


void search_adherent()
{
    FILE *fp;
    adherent nouveau;
    char nom[30];
    int count;

       fp = fopen(FICHIER,"rb");
       if (fp==NULL)
       {
           printf("Sorry! File could not be opened!");
           exit(0);
       }

       fflush(stdin);
       printf("Enter contact nom to search : ");
       scanf("%s",nom);

       while(1)
       {
         count = fread(&nouveau,sizeof(nouveau),1,fp);
         if (count == 0){
            break;
         }
         if(strstr(nouveau.nom_adh, nom) !=NULL)
            printf("%-20d %-20s %-20s %-30s %-30s %d\n",nouveau.num_adh,nouveau.nom_adh,nouveau.prenom_adh,nouveau.email_adh,
                                       nouveau.address_adh,nouveau.nbre_emprunts_adh);
       }

       fclose(fp);
       printf("\nPress a key to continue...\n");
       getch();
       system("cls");
}
int check_adherent(int num){
       FILE *fp;
       fp=fopen(FICHIER,"rb");
       adherent nouveau;
       while(fread(&nouveau,sizeof(nouveau),1,fp)){
            if (nouveau.num_adh==num){
                return 1;
            }

       }
    fclose(fp);
    return 0;
}
void supprimer_adherent(){
    int num;
    FILE *fp,*fp2;
    fp=fopen(FICHIER,"rb");
    fp2=fopen("copy.dat","ab");
    adherent nouveau;
    printf("Entrez le numero de l'adherent à supprimer :");
    scanf("%d",&num);
    while(fread(&nouveau,sizeof(adherent),1,fp)){
        if(nouveau.num_adh==num){
            continue;
        }
        else{
            fwrite(&nouveau,sizeof(nouveau),1,fp2);/*On ajoute les donnees dans un nouveau fichier sauf celui a qui
                                                      Correspond le numero.*/
        }
    }
    fclose(fp);
    fclose(fp2);
    remove("adherent.dat");
    rename("copy.dat","adherent.dat");
}
void modifier_adherent(){
    int num;
    printf("Entrez le num de l'adherent que vous voulez modifer :");
    scanf("%d",&num);
    adherent nouveau;
    FILE *fp,*fp2;
    fp=fopen(FICHIER,"rb");
    fp2=fopen("copy.dat","ab");
    while(fread(&nouveau,sizeof(nouveau),1,fp)){
        if(nouveau.num_adh==num){
            fflush(stdin);
            printf("Nom de l'adherent :");
            gets(nouveau.nom_adh);
            fflush(stdin);
            printf("Prenom de l'adherent :");
            gets(nouveau.prenom_adh);
            fflush(stdin);
            printf("Email de l'adherent :");
            gets(nouveau.email_adh);
            fflush(stdin);
            printf("Address de l'adherent :");
            gets(nouveau.address_adh);
            fwrite(&nouveau,sizeof(nouveau),1,fp2);
            printf("\nvous avez changez cet adherent.\n");
        }
        else{
                fwrite(&nouveau,sizeof(nouveau),1,fp2);
        }
    }

    fclose(fp);
    fclose(fp2);
    remove("adherent.dat");
    rename("copy.dat","adherent.dat");
}
