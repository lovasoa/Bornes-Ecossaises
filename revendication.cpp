#include <cstdlib>

#include "Def.h"

using namespace std;

bool reperage_revendication (t_BORNES bornes, int num_borne_choisie, int num_player) // on compte à partir de 0 !
{
    if ( bornes[num_borne_choisie].zones_borne[num_player].nbre_cartes == 3
         && bornes[num_borne_choisie].zones_borne[(num_player+1)%2].nbre_cartes == 3) return true;
    else return false;
}



// comparaison des cartes d'une borne pleine.
int comparaison (t_borne borne_revendiquee, int num_player)
{
    t_tableau_cartes cartes_player_1 = borne_revendiquee.zones_borne [0].tableau_cartes; 
    t_tableau_cartes cartes_player_2 = borne_revendiquee.zones_borne [1].tableau_cartes;
    /* Ces deux lignes de codes ne passaient pas chez moi (problème d'initialisation de tableau), et chez vous? 
    J'ai quand même réussi à les modifier et maintenant le jeu tourne niquel ;) */
    
    
    // que 2 cas.... pas besoin de créer un tableau pour s'épargner une ligne.


    tri (cartes_player_1); tri (cartes_player_2);

    int force_1 = force_combinaison (cartes_player_1);
    int force_2 = force_combinaison (cartes_player_2);

    if (force_1 > force_2)return 1;
    else if (force_2 > force_1) return 2;
    else return departager(cartes_player_1, cartes_player_2, num_player);

}

// Tri des cartes (de 3 cartes....)
void tri (t_tableau_cartes cartes)
{
    int i;
    // tri à bulle minimaliste... seulement 3 cartes.
    for (i=0; i<2; i++)
    {
        if (cartes[i].num_carte > cartes[i+1].num_carte) permuter (cartes, i);
    }
    if (cartes[0].num_carte > cartes[1].num_carte) permuter (cartes, 0);
}

void permuter (t_tableau_cartes cartes, int i)
{
    t_carte temp;
    temp = cartes[i];
    cartes[i] = cartes[i+1];
    cartes [i+1] = temp;
}

// attribution des valeurs des ensembles de 3 cartes.
int force_combinaison (t_tableau_cartes cartes)
{
    int force;

    if (meme_couleur(cartes))
    {
        if (consecutives(cartes)) force = 4;
        else force = 2;
    }
    else if (meme_valeur(cartes)) force = 3;
    else if (consecutives(cartes)) force = 1;
    else force = 0;
    return force;
}

// fonctions secondaires.
bool meme_couleur (t_tableau_cartes cartes)
{
    int i = 0;
    while (cartes[i].couleur == cartes[i+1].couleur && i < 3) i++;
    if (i == 2) return true;
    else return false;
}

bool consecutives (t_tableau_cartes cartes)
{
    int i=0;

    while (cartes[i+1].num_carte - cartes[i].num_carte == 1 && i < 3) i++;
    if (i == 2) return true;
    else return false;
}

bool meme_valeur (t_tableau_cartes cartes)
{
    if (cartes[0].num_carte == cartes[1].num_carte && cartes[1].num_carte == cartes[2].num_carte) return true;
    else return false;
}

int departager (t_tableau_cartes cartes_player_1, t_tableau_cartes cartes_player_2, int num_player)
{
    int i = 2;
    int borne_revendiquee_possession;
    while (cartes_player_1[i].num_carte == cartes_player_2[i].num_carte && i > 0) i--;
    if (cartes_player_1[i].num_carte > cartes_player_2[i].num_carte) borne_revendiquee_possession = 1;
    else if (cartes_player_1[i].num_carte < cartes_player_2[i].num_carte) borne_revendiquee_possession = 2;
    else borne_revendiquee_possession = (num_player+1)%2 + 1; // Revendication "automatique" après son tour si borne remplie.
                                                        // Le joueur dont c'est le tour a posé sa carte en dernier donc perd.
    return borne_revendiquee_possession;

}










