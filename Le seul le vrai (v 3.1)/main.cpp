#include "grman/grman.h"
#include <iostream>
#include <stdlib.h>
#include "graph.h"

int main()
{

    int q;
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
            /// création du graph
            Graph g;

            ///Fichier 1 == océan
            if(q == 1)
                {
                    g.chargement("fichier1");
                    while(!key[KEY_ESC])
                   {

                        g.update(g, "fichier1");
                        grman::mettre_a_jour();
                   }
                   g.sauvegarde("fichier1");
                    //fichier("fichier1", g, sommet_indic, arc_indic);
                }

            ///Fichier 2 == Savane
            else if(q == 2)
                {
                    g.chargement("fichier2");
                    while(!key[KEY_ESC])
                   {

                        g.update(g, "fichier2");
                        grman::mettre_a_jour();
                   }
                   g.sauvegarde("fichier2");
                   // fichier("fichier2", g, sommet_indic, arc_indic);
                }

            ///Fichier 3 == Forêt
            else if(q == 3)
                {
                    g.chargement("fichier3");
                    while(!key[KEY_ESC])
                   {

                        g.update(g, "fichier3");
                        grman::mettre_a_jour();
                   }
                   g.sauvegarde("fichier3");
                   // fichier("fichier3", g, sommet_indic, arc_indic);
                }
            system("CLS");

            if(q==1) {g.sauvegarde("fichier1");}
            if(q==2) {g.sauvegarde("fichier2");}
            if(q==3) {g.sauvegarde("fichier3");}

            grman::fermer_allegro();
        }while(q!=4);
}
END_OF_MAIN();


