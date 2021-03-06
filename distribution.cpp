#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Def.h"

using namespace std;

void initialisation_pioche (t_pioche pioche)
{
    int i,j;
    string couleurs[NB_COULEURS] = {"Roug", "Jaun", "Vert", "Bleu", "Noir", "Marr"};
    for (i=0; i<NB_COULEURS; i++)
    {
        for (j=0; j<CARTES_PAR_COULEUR; j++) {pioche[i*CARTES_PAR_COULEUR + j].couleur = couleurs[i];
                                              pioche[i*CARTES_PAR_COULEUR + j].num_carte = j+1;}

    }
}

// distribution d'une carte aléatoire
t_carte distribution_pioche (t_pioche pioche, int cartes_piochees_debut)
{
    t_carte carte_vide;
    carte_vide.couleur = "    "; carte_vide.num_carte = 0;

    t_carte carte_piochee;
    int place_carte_choisie;

    place_carte_choisie = rand() % (TOTAL_CARTES - cartes_piochees_debut) ;

    carte_piochee = pioche[place_carte_choisie];

    pioche [place_carte_choisie] = pioche [TOTAL_CARTES - cartes_piochees_debut -1];
    pioche [TOTAL_CARTES - cartes_piochees_debut -1] = carte_vide;

    return carte_piochee;

}


// formation des paquets de 6 cartes
int distribution_pioche_debut (t_pioche pioche, t_tableau_hand hands, int cartes_piochees_debut)
{
    int i;
    for (i=0; i<6; i++)
    {
        hands[0][i] = distribution_pioche(pioche, cartes_piochees_debut);
            cartes_piochees_debut++;

        hands[1][i] = distribution_pioche(pioche, cartes_piochees_debut);
            cartes_piochees_debut++;
    }
    return cartes_piochees_debut;
}

// distribution d'une carte pour remplacer la carte jouée par le joueur
void recevoir_carte (t_pioche pioche, t_tableau_hand hands, int num_player, int cartes_piochees_debut)
{
    int i=0;
    // repérage de la première carte vide.
    while (hands[num_player][i].num_carte != 0) i++;
    hands[num_player][i] = distribution_pioche(pioche, cartes_piochees_debut);
}




