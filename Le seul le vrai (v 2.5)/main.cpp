#include "grman/grman.h"
#include <iostream>
#include <stdlib.h>
#include "graph.h"

int main()
{

    int q, a,sommet_indic, arc_indic;
    sommet_indic=0;
    arc_indic=0;
    do
        {

            q = menu1();

            if(q==4)
                {
                    return 0;
                }

            ///Initialisation d'allegro.
            grman::init();
            ///Set de l'adresse du dossier contenant les images des sommets
            grman::set_pictures_path("pics");
            /// cr�ation du graph
            Graph g;

            ///Fichier 1 == oc�an
            if(q == 1)
                {
                    fichier("fichier1", g, a, sommet_indic, arc_indic);
                }

            ///Fichier 2 == Savane
            else if(q == 2)
                {
                    fichier("fichier2", g, a, sommet_indic, arc_indic);
                }

            ///Fichier 3 == For�t
            else if(q == 3)
                {
                    fichier("fichier3", g, a, sommet_indic, arc_indic);
                }
            system("CLS");

            if(q==1) {g.sauvegarde("fichier1");}
            if(q==2) {g.sauvegarde("fichier2");}
            if(q==3) {g.sauvegarde("fichier3");}

            grman::fermer_allegro();
        }while(q!=4);
}
END_OF_MAIN();


