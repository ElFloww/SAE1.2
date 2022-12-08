// DUBUT Florent
// ELOUALI Wissam
// EL MASSAOUDI Sami
// BUT INFO 1A-GE1
// Version 2.1
// Créé le: 05-12-2021
// Modifié le: 13-01-2022

//Libraries:
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Constantes
#define EOL '\n'
#define N 20001
#define P 21

//Types
typedef char tableau[N][P];
typedef char fichier[50];

//Fichiers
int taille_fichier(fichier fichier_lecture) //Calcul la taille du fichier en ligne
{
    FILE *f;
    char c;
    int taille = 1;
    f=fopen(fichier_lecture,"rt");
    while((c=fgetc(f))!=EOF)
    {
        if (c == 10)
        {
            taille++;
        }
    }
    return taille;
}
int taille_max_mot(fichier fichier_lecture)
{
    FILE *f;
    int taille = 0,taille_max = 0;
    char c;
    f=fopen(fichier_lecture,"rt");
    while((c=fgetc(f))!= EOF)
    {
        if ((int)c == 10 || (int)c == 9) //Dès que on à un retour à la ligne
        {
            if (taille > taille_max) //Si la taille du mot est supérieure à la taille maximal de mot enregistré
            {
                taille_max = taille; // La taille actuelle deviens la taille maximal
            }
            taille = 0; // On rénitialise la taille du mot pour recommencer sur les autres mots
        }
        else
        {
            taille++; // On prend en compte le caractère
        }
    }  
    if (taille > taille_max) //Si la taille du dernier mot de la liste est supérieure à la taille maximal de mot enregistré.
        {
            taille_max = taille; // La taille actuelle deviens la taille maximal
        }
    return taille_max + 1;  
}

int tailleurl(fichier fichier_lecture) //Calcul la taille d'une url, soit la taille d'un tableau
{
    int taille = 0;
    for (int i=0; fichier_lecture[i] != '\0';i++)
    {
        taille++;
    }
    return taille;
}

void FichierReadNiveau1(tableau chaine, fichier fichier_lecture)
{
    int n=0,p=0,i,j;
    FILE *f;
    char c;
    
    //Remplissage d'un tableau de dimentions N, P avec des 0 pour l'initialiser

    for(i=0;i<N;i++){
        for(j=0;j<P;j++){
            chaine[i][j]=0;
        }
    }

    //Ouverture du fichier text
    f=fopen(fichier_lecture,"rt");

    while((c=fgetc(f))!=EOF){
        //Si le caractère sélectionné est une lettre majuscule, ou une tiret ou un apostrophe, on le rajoute au tableau
        if(((int)c>=65 && (int)c<=90) || (int)c == 45 || (int)c == 39){
            chaine[n][p]=c;
            p++;
        }

        //Si le caractère sélectionné à un code ascii = 10, on change de tableau. Le code ascii 10 est un retour à la ligne \n
        if((int)c == 10)
        {
            p=0;
            n++;
        }

        //Si lec caractère sélectionné à un code ascii = 13, on l'affecte pas au tableau, il s'agit d'un caractère de retour à la ligne, /r
        if((int)c == 13)
        {
            chaine[n][p] = 0;
        }
    }
    //Fin du traitement, fermeture du fichier
    fclose(f);
}

void FichierReadNiveau2(tableau nom, tableau prenom, tableau numEtud, fichier fichier_lecture)
{
    int n=0,p=0,i,j;
    FILE *f;
    char c;
    
    //Remplissage des 3 tableaux de 0
    for(i=0;i<N;i++){
        for(j=0;j<P;j++)
        {
            nom[i][j]=0;
            prenom[i][j]=0;
            numEtud[i][j]=0;
        }
    }

    //Ouverture des fichiers
    f=fopen(fichier_lecture,"rt");

    //La variable nb_tab permet de sélectionner un tableau en particulier, c'est-à-dire :
    //nb_tab = 1 : Tableau prenom
    //nb_tab = 2 : Tableau nom
    //nb_tab = 3 : Tableau numéro Etudiant

    int nb_tab = 1;
    while((c=fgetc(f))!=EOF){
        //Si le caratère est une tabulation '\t'
        if((int)c == 9)
        {
            //On change de tableau et on prend un nouveau caractère
            nb_tab += 1;
            c=fgetc(f);
            //On positione l'indice de colonne à 0
            p=0;
        }

        //Si le caractère est un retour à la ligne '\n'
        if((int)c == 10)
        {
            //On se repositionne sur le tableau 1
            nb_tab = 1;
            //Indice de colonne repasse à 0
            p = 0;
            //Indice de ligne augmente de 1
            n++;
        }
        //Dans les autres cas, c'est-à-dire l'inverse des deux cas précédent, on remplit un tableau
        if((int)c != 10 && (int)c != 9)
        {
            //Si nb_tab est sur 1, alors on rempli le tableau prenom
            if(nb_tab == 1)
            {
                //Remplissage du tableau avec le caractère
                prenom[n][p]=c;
                //Décalage de l'indice de colonne
                p++;
            }

            //Si nb_tab est sur 2, alors on rempli le tableau nom
            if(nb_tab == 2)
            {
                //Remplissage du tableau avec le caractère
                nom[n][p]=c;
                //Décalage de l'indice de colonne
                p++;
            }

            //Si nb_tab est sur 2, alors on rempli le tableau numEtud
            if(nb_tab == 3)
            {
                //Remplissage du tableau avec le caractère
                numEtud[n][p]=c;
                //Décalage de l'indice de colonne
                p++;
            }
        }
    }
    fclose(f);
}

void FichierWriteNiveau1(tableau chaine, fichier fichier_sortie)
{ //Le fichierwrite de ce fichier sera à modifier pour s'adapter aux besoin dont s'occupe celui du tri par selection
    int i,j;
    FILE *fichier;

    fichier=fopen(fichier_sortie, "w");

    for(i=0;i<N;i++)
    {
        for(j=0;j<P;j++)
        {
            char cara = chaine[i][j];
            if((cara <=90 && cara>=65) || cara == '-')
            {
                fputc(cara,fichier);
            }
        }
        if (i != N-1)
        {
            fputc('\n',fichier);
        }
    }
    fclose(fichier);
}

void FichierWriteNiveau2(tableau nom, tableau prenom ,tableau numEtud, fichier fichier_sortie)
{
    int i,j = 0,k;
    int termine = 0;
    FILE *fichier;

    //Ouverture du fichier de sortie en ecriture
    fichier=fopen(fichier_sortie, "w");
    
    //Pour toutes les lignes de 0 à N-1
    for(i=0;i<N;i++)
    {   
        //Pour tous les tableaux de 1 à 3
        for(k=1;k<=3;k++)
        {
            //Tant que la variable termine == FAUX -> Tant que il y a des caractères dans la ligne du tableau
            while(termine == 0)
            {
                //Le tableau est rempli seulement de lettres , d'apostrophe ou de tiret, donc, si on à un 0 à la lecture, on à fini la lecture de la ligne
                
                //Si on est sur le premier tableau -> prenom
                if(k==1)
                {
                    //On selectionne le caractère dans le tableau prenom
                    char cara = prenom[i][j];

                    //Si le caractère est un chiffre ou un symbole
                    if((int)cara != 0)
                    {
                        //On l'insère dans le fichier
                        fputc(cara,fichier);

                        //On décale l'indice de colonne de 1
                        j++;
                    }
                    //Sinon, c'est un espace
                    else
                    {
                        //On insère dans le fichier un '\t', une tabulation pour séparer les données
                        fputc(9,fichier);
                        //Termine devient VRAI
                        termine = 1;
                    }
                }
                //Si on est sur le second tableau -> nom
                if(k==2)
                {
                    //On selectionne le caractère dans le tableau prenom
                    char cara = nom[i][j];

                    //Si le caractère est un chiffre ou un symbole
                    if((int)cara != 0)
                    {
                        //On l'insère dans le fichier
                        fputc(cara,fichier);

                        //On décale l'indice de colonne de 1
                        j++;
                    }
                    else
                    {
                        //On insère dans le fichier un '\t', une tabulation pour séparer les données
                        fputc(9,fichier);
                        //Termine devient VRAI
                        termine = 1;
                    }
                }
                //Si on est sur le troisème tableau -> numEtud
                if(k==3)
                {
                    //On selectionne le caractère dans le tableau prenom
                    char cara = numEtud[i][j];

                    //Si le caractère est un chiffre ou un symbole
                    if((int)cara != 0)
                    {
                        //On l'insère dans le fichier
                        fputc(cara,fichier);

                        //On décale l'indice de colonne de 1
                        j++;
                    }
                    else
                    {
                        //Contraitement à avant, on à fini d'écrire la ligne, donc on renvoie rien dans le fichier texte
                        //Termine devient VRAI
                        termine = 1;
                    }
                }
            }

            //Le Booleen termine repasse à 0 car le traitement du tableau est fini, on change de tableau
            termine = 0;
            //On rénitialise l'indice de colonne
            j = 0;
        }
        //On à fini l'écriture sur la ligne, on fait un retour à la ligne pour recommencer une ligne
        if (i != N-1)
        {
            fputc('\n',fichier);
        }
    }
    //Tout est fini, on peut fermer le fichier
    fclose(fichier);
}

void affichetab(tableau chaine)
{
    //Affichage du tableau
    for(int i=0;i<N;i++){
    printf("ligne %d :  ",i+1);
    for(int j=0;j<P;j++){
        printf("[%c]",chaine[i][j]);
    }
    printf("\n");
    }
}

void inverse(tableau chaine, int ind1, int ind2)
{
    //Inversion de deux lignes du tableau
    char garage;
    int i;
    for(i=0;i<P;i++)
    {
        garage = chaine[ind1][i];
        chaine[ind1][i] = chaine[ind2][i];
        chaine[ind2][i] = garage;
    }
}

void unpassageNiveau1(tableau chaine, int debut, int fin)
{
    for(int i=0;i<fin;i++)
    {
        //indlettre est une variable qui peut servir si l'on à des chaines de caractères qui se ressemblent, comme BABOU et BABIN, qui servira à les comparer
        int indlettre = 0;
        //Si le programme vient de se lancer, l'indice minimum est l'indice de début, si c'est pas le cas, on passe dans le else
        if(chaine[i][indlettre] > chaine[i+1][indlettre])
        {
            //On sais que indice suivant est plus petit que l'actuel, on les inverse
            inverse(chaine,i+1,i);
        }
        //Si le premier caractère de la chaine selectionné est la même que la chaine minimum, on va tester toutes les autres lettres de la chaine de caractère pour savoir lequel est le plus petit
        while(chaine[i][indlettre] == chaine[i+1][indlettre])
        {
            //Dans ce cas, le caractère à l'indice indlettre est le même dans les deux chaines de caractères, alors on regarde la lettre suivante et on regarde.
            indlettre++;
        }
        //Après avoir rechercher une différence entre les deux chaines de caractère du tableau chaine, on regarde si le caractère est inférieur à celui du minimum, comme par exemple BAB[O]U et BAB[I]N, ici, la chaine minimum est BABOU, hormis, BABIN est plus petit, car le [I] est avant le [O], donc BABIN deviens le minimum
        if(chaine[i][indlettre] > chaine[i+1][indlettre])
        {
            //On sais que indice suivant est plus petit que l'actuel, on les inverse
            inverse(chaine,i+1,i);
        }
    }
}

void unpassageNiveau2(tableau nom, tableau prenom, tableau numEtud, int debut, int fin)
{
    for(int i=0;i<fin;i++)
    {
        //indlettre est une variable qui peut servir si l'on à des chaines de caractères qui se ressemblent, comme BABOU et BABIN, qui servira à les comparer
        int indlettre = 0;
        //Si le programme vient de se lancer, l'indice minimum est l'indice de début, si c'est pas le cas, on passe dans le else
        if(nom[i][indlettre] > nom[i+1][indlettre])
        {
            //On sais que indice suivant est plus petit que l'actuel, on les inverse
            inverse(nom,i+1,i);
            inverse(prenom,i+1,i);
            inverse(numEtud,i+1,i);
        }
        //Si le premier caractère de la chaine nom selectionné est la même que la chaine minimum, on va tester toutes les autres lettres de la chaine de caractère pour savoir lequel est le plus petit
        while(nom[i][indlettre] == nom[i+1][indlettre])
        {
            //Dans ce cas, le caractère à l'indice indlettre est le même dans les deux chaines de caractères, alors on regarde la lettre suivante et on regarde.
            indlettre++;
        }
        //Après avoir rechercher une différence entre les deux chaines de caractère du tableau nom, on regarde si le caractère est inférieur à celui du minimum, comme par exemple BAB[O]U et BAB[I]N, ici, la chaine minimum est BABOU, hormis, BABIN est plus petit, car le [I] est avant le [O], donc BABIN deviens le minimum
        if(nom[i][indlettre] > nom[i+1][indlettre])
        {
            //On sais que indice suivant est plus petit que l'actuel, on les inverse
            inverse(nom,i+1,i);
            inverse(prenom,i+1,i);
            inverse(numEtud,i+1,i);
        }
    }
}

void triBullesNiveau1(tableau chaine, int debut, int fin)
{
    int indlettre = 0;
    //Parcours les indices du début à fin
    for(int i=0;i<fin;i++)
    {
        //On cherche le minimum dans l'intervalle [i;N], et on placera le minimum à l'indice N-i, soit fin-1
        unpassageNiveau1(chaine,debut,fin-i);
    }
}

void triBullesNiveau2(tableau nom, tableau prenom, tableau numEtud, int debut, int fin)
{
    int indlettre = 0;
    //Parcours les indices du début à fin
    for(int i=0;i<fin;i++)
    {
        //On cherche le minimum dans l'intervalle [i;N], et on placera le minimum à l'indice N-i, soit fin-1
        unpassageNiveau2(nom,prenom,numEtud,0,fin-i);
    }
}

int indice_minimumTAB(tableau chaine,int indice_debut)
{
    int min = indice_debut,indlettre;
    for (int i=indice_debut;i<N;i++)
    {
        //indlettre est une variable qui peut servir si l'on à des chaines de caractères qui se ressemblent, comme BABOU et BABIN, qui servira à les comparer
        indlettre = 0;
        //Si le programme vient de se lancer, l'indice minimum est l'indice de début, si c'est pas le cas, on passe dans le else
        if(i==indice_debut)
        {
            min = indice_debut;
        }
        else
        {
            //Si le premier caractère de la chaine selectionné est plus petit que le premier caractère de la chaine selectionné, alors la chaine selectionné sera la minimum
            if (chaine[i][indlettre] < chaine[min][indlettre])
            {
                min = i;
            }
            else
            {
                //Si le premier caractère de la chaine selectionné est la même que la chaine minimum, on va tester toutes les autres lettres de la chaine de caractère pour savoir lequel est le plus petit
                while(chaine[i][indlettre] == chaine[min][indlettre])
                {
                    //Dans ce cas, le caractère à l'indice indlettre est le même dans les deux chaines de caractères, alors on regarde la lettre suivante et on regarde.
                    indlettre++;
                }
                //Après avoir rechercher une différence entre les deux chaines, on regarde si le caractère est inférieur à celui du minimum, comme par exemple BAB[O]U et BAB[I]N, ici, la chaine minimum est BABOU, hormis, BABIN est plus petit, car le [I] est avant le [O], donc BABIN deviens le minimum
                if(chaine[i][indlettre] < chaine[min][indlettre])
                {
                    min = i;
                }
            }
        }
    }
    //Dès que on à parcouru toute la liste, on retourne le minimum qui à été trouvé entre les deux bornes indice début et N : la taille du tableau
    return min;
}

void Tri_croissantTABNiveau1(tableau chaine)
{
    int rang_mini;
    //Parcours de la liste mot par mot
    for (int i=0;i<(N-1);i++)
    {
        //Calcul du rang mini
        rang_mini = indice_minimumTAB(chaine,i);
        //Inversion de la ligne minimum et de la ligne i
        inverse(chaine,rang_mini,i);
    }
}

void Tri_croissantTABNiveau2(tableau nom, tableau prenom, tableau numEtud)
{
    int rang_mini;
    //Parcours de la liste mot par mot
    for (int i=0;i<(N-1);i++)
    {
        //Calcul du rang mini
        rang_mini = indice_minimumTAB(nom,i);
        //Inversion de la ligne minimum et de la ligne i
        inverse(nom,rang_mini,i);
        inverse(prenom,rang_mini,i);
        inverse(numEtud,rang_mini,i);
    }
}

//Fonction principale
int main()
{
    printf("\n\nDUBUT Florent\n");
    printf("El MANOUZI Elias-Anis\n");
    printf("EL MASSAOUDI Sami\n");
    printf("ELOUALI Wissam\n\n");
    printf("BUT INFO 1A-GE1\n");
    printf("Version 2.1\n\n");
    printf("Creer le: 05-12-2021\n");
    printf("Modifie le: 13-01-2022\n\n");

    int typetri; //Permet de stoquer une variable 1 ou 2 qui va permettre le choix entre tri niveau 1 ou tri niveau 2
    int methodetri; //Permet de stoquer une variable 1 ou 2 qui va permettre le choix entre le tri a bulles et le tri par selection
    
    
    

    // A remplir 
    fichier fichier_lecture = "Liste.txt"; //Fichier où la liste doit etre triee
    fichier fichier_sortie = "Fichier_Out.txt"; //Fichier ou la liste sera triee


    FILE* fichier = NULL;
    fichier = fopen(fichier_lecture,"r+");

    if (fichier == NULL) //Vérification du fichier source
    {
        printf("\n\nImpossible d'ouvrir le fichier %s",fichier_lecture);
        printf("\nVerrifiez que vous avez saisie le bon nom de fichier en ligne 520");
        return 1;
    }
    if (tailleurl(fichier_sortie) < 3) //Vérification du fichier sortie, si il a une taille < 3, alors le nom du fichier est sûrement incorrect 
    {
        printf("\nAttention ! Verrifiez que vous avez saisie le bon nom de fichier en sortie en ligne 521");
        return 1;
    }

    int nombre_enregistrement = taille_fichier(fichier_lecture);
    int taille_max = taille_max_mot(fichier_lecture);
    if (N != nombre_enregistrement)
    {
        printf("\n\nATTENTION ! Pensez a changer la constante N a la ligne 16 qui permet le bon fonctionnement du programme, il faut mettre N a %i",nombre_enregistrement);
        return 2;
    }
    if (P != taille_max)
    {
        printf("\n\nATTENTION ! Pensez a changer la constante P a la ligne 17 qui permet le bon fonctionnement du programme, il faut mettre P a %i",taille_max);
        return 3;
    }

    printf("Voulez-vous faire un tri de niveau 1 ou de niveau 2 ? ");
    scanf("%i",&typetri);
    while(typetri != 1 && typetri != 2)
    {
        printf("Ereur de saisie ! Voulez-vous faire un tri de niveau 1 ou de niveau 2 ? ");
        scanf("%i",&typetri);
    }
    
    printf("Voulez-vous faire un tri a bulles (1) ou par selection (2) ? ");
    scanf("%i",&methodetri);
    while(methodetri != 1 && methodetri != 2)
    {
        printf("Ereur de saisie ! Voulez-vous faire un tri a bulles ou par selection ? ");
        scanf("%i",&methodetri);
    }

    if (typetri == 1)
    {
        tableau chaine;

        if (methodetri == 1)
        {
            FichierReadNiveau1(chaine, fichier_lecture); //Lecture du fichier, création du tableau, remplissage du tableau de 0, puis remplissage du tableau des caractères présent dans le fichier (1 ligne par mot)
            //affichetab(chaine); //Affichage du tableau pour vérificaion
            printf("\nRetransmission du fichier dans le tableau reussi !");

            clock_t start, end;
            double cpu_time_used;
            start = clock();
            triBullesNiveau1(chaine,0,N); //Tri croissante de la liste chaine avec le tri à Bulles
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("\n\nle temps d'execution est %f\n\n",cpu_time_used);


            printf("\nTri a bulles reussi !");
            //affichetab(chaine); //Affichage du tableau pour vérificaion
            FichierWriteNiveau1(chaine,fichier_sortie); //Ecriture de la liste dans un fichier text
            printf("\nRetransmission du tableau dans le fichier reussi !\n\n");
    
            return 0;
        }
        else
        {
            FichierReadNiveau1(chaine,fichier_lecture); //Lecture du fichier, création du tableau, remplissage du tableau de 0, puis remplissage du tableau des caractères présent dans le fichier (1 ligne par mot)
            printf("\nRetransmission du fichier dans le tableau reussi !");
            //affichetab(chaine); //Affichage du tableau pour vérificaion

            clock_t start, end;
            double cpu_time_used;
            start = clock();
            Tri_croissantTABNiveau1(chaine); //Tri croissante de la liste chaine avec le tri par selection
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("\n\nle temps d'execution est %f\n\n",cpu_time_used);

            printf("\nTri par selection reussi !");
            //affichetab(chaine); //Affichage du tableau pour vérificaion
            FichierWriteNiveau1(chaine,fichier_sortie); //Ecriture de la liste dans un fichier text
            printf("\nRetransmission du tableau dans le fichier reussi !\n\n");
            return 0;
        }
    }
    else
    {
        tableau nom;
        tableau prenom;
        tableau numEtud;

        if (methodetri == 1)
        {
            //Lecture du fichier text, remplissage des tableaux avec les données
            FichierReadNiveau2(nom,prenom,numEtud,fichier_lecture);
            printf("\nRetransmission du fichier dans le tableau reussi !");

            //affichetab(nom); //Affichage du tableau pour vérificaion
            //affichetab(prenom); //Affichage du tableau pour vérificaion
            //affichetab(numEtud); //Affichage du tableau pour vérificaion

            //Tri des tableau dans l'ordre croissant en fonction du nom
            clock_t start, end;
            double cpu_time_used;
            start = clock();
            triBullesNiveau2(nom, prenom, numEtud,0,N-1);
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("\n\nle temps d'execution est %f\n\n",cpu_time_used);

            printf("\nTri a bulles reussi !");

            //affichetab(nom); //Affichage du tableau pour vérificaion
            //affichetab(prenom); //Affichage du tableau pour vérificaion
            //affichetab(numEtud); //Affichage du tableau pour vérificaion

            //Création du fichier text avec les données des tableaux triées
            FichierWriteNiveau2(nom, prenom, numEtud, fichier_sortie);
            printf("\nRetransmission du tableau dans le fichier reussi !\n\n");
            return 0;
        }
        else
        {
            //Lecture du fichier text, remplissage des tableaux avec les données
            FichierReadNiveau2(nom,prenom,numEtud,fichier_lecture);
            printf("\nRetransmission du fichier dans le tableau reussi !");

            //affichetab(nom); //Affichage du tableau pour vérificaion
            //affichetab(prenom); //Affichage du tableau pour vérificaion
            //affichetab(numEtud); //Affichage du tableau pour vérificaion

            //Tri des tableau dans l'ordre croissant en fonction du nom
            clock_t start, end;
            double cpu_time_used;
            start = clock();
            Tri_croissantTABNiveau2(nom, prenom, numEtud);
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("\nLe temps d'execution est %f",cpu_time_used);

            printf("\nTri par selection reussi !");

            //affichetab(nom); //Affichage du tableau pour vérificaion
            //affichetab(prenom); //Affichage du tableau pour vérificaion
            //affichetab(numEtud); //Affichage du tableau pour vérificaion

            //Création du fichier text avec les données des tableaux triées
            FichierWriteNiveau2(nom, prenom, numEtud, fichier_sortie);
            printf("\nRetransmission du tableau dans le fichier reussi !\n\n");
            return 0;
        }
    }
}   
