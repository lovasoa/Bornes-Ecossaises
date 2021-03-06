#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include "Def.h"

/* OPTIMISATION POSSIBLES :
IA brelan : ne pas reconstruire le tableau des cartes inutiles à chaque fois --> compliqué.. dépend du joeur, et le caractère utile ou pas varie en fonction de la main du joueur et du remplissage de la born...
Prendre en compte le fait de viser 3 bornes consécutives --> construire les brelands les plus probables sur 3 bornes consécutives. (commencons en mettant les3 premières cartes côte à côte).
1 Tri pour tous les cas
placer les brelans en fonction de ce que fait l'adversaire --> brelan probable sur combinaisons pouvant gagner (durdur...)
*/


using namespace std;

int main()
{
    srand(time(NULL));
    string jeu_vs_IA;
    string joue_avant_IA;
    bool tour_IA = true;
    // variables de test
    int nbre_essais=0, nbre_essais_tot;
    int j_1_vict = 0, j_2_vict = 0;
    cout << "combien de tests voulez vous faire ?" << endl;
    cin >> nbre_essais_tot;

    cout << "Voulez vous jouer contre l'ordinateur ?" << endl;
    cin >> jeu_vs_IA;
    if (jeu_vs_IA == "oui")
    {
        cout << "voulez vous commencer ?" << endl;
        cin >> joue_avant_IA;
        if (joue_avant_IA == "oui") tour_IA = false;
    }



while (j_1_vict != 1){
    tour_IA = false;
    t_tableau_hand  hands;
    t_pioche pioche;
    t_BORNES bornes;
    t_choix_IA choix_IA;
    bool nouvel_essai = false;
    bool revendication = false;
    //bool tour_IA = true;
    bool test_IA_vs_IA = true;

    int num_player = 0, cartes_piochees_debut = 0;
    int num_carte_choisie, num_borne_choisie;
    int fin_jeu = 0;


    initialisation_pioche(pioche);

    cartes_piochees_debut = distribution_pioche_debut (pioche, hands, cartes_piochees_debut);
    initialisation_bornes (bornes);


    while (fin_jeu == 0)
    {
        if (tour_IA)
        {
            choix_IA = IA_brelan(bornes, num_player, hands);
            num_borne_choisie = choix_IA.num_borne_choisie;
            num_carte_choisie = choix_IA.num_carte_choisie;
            tour_IA = false;
        }

        else if (test_IA_vs_IA)
        {
            choix_IA = IA_rand(bornes, num_player, hands);
            num_borne_choisie = choix_IA.num_borne_choisie;
            num_carte_choisie = choix_IA.num_carte_choisie;
            tour_IA = true;
        }
        else
        {
            cout << "c'est au tour du joueur " << num_player + 1 << " de jouer." << endl << endl;

            cout << "quelle carte voulez vous jouer ? Sur quelle borne ?" << endl;
            cin >> num_carte_choisie >> num_borne_choisie;
            cout << endl << endl;

            nouvel_essai = choix_borne (bornes, num_player, hands, num_carte_choisie - 1, num_borne_choisie - 1);
            if (!nouvel_essai) tour_IA = true;
        }

            // si le joueur a fait un choix licite, il reçoit une carte,
            // on passe au joueur suivant et la pioche a diminée d'une carte.
        if (nouvel_essai == false)
        {
            revendication = reperage_revendication(bornes, num_borne_choisie - 1, num_player);

            if (cartes_piochees_debut < TOTAL_CARTES)
            {
                recevoir_carte(pioche, hands, num_player, cartes_piochees_debut);
                cartes_piochees_debut++;
            }

            if (revendication && nouvel_essai == false) // inutile de recomparer si le joueur ne fait que
                                                        // rejouer après un choix illicite.
            {
            bornes[num_borne_choisie-1].possession = comparaison(bornes[num_borne_choisie-1], num_player);
            fin_jeu = conditions_victoire (bornes);
            }

            num_player = (num_player+1)%2;
        }
    }
    if (fin_jeu == 1) {/*cout << "Le Joueur 1 est victorieux !" << endl;*/ j_1_vict ++;}
    else {/*cout << "Le joueur 2 est victorieux !" << endl;*/ j_2_vict++;}
    affichage (hands, bornes);
    nbre_essais ++;
    cout << nbre_essais << endl;
}
 cout << " % victoires joueur 1 = " << (float) j_1_vict / nbre_essais << endl;
 cout << " % victoires joueur 2 = " << (float) j_2_vict / nbre_essais << endl;
 return 0;
}
