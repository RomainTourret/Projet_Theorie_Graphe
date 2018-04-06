#include "grman/grman.h"
#include <iostream>
#include <stdlib.h>
#include "graph.h"

int main()
{

    int q, a, sommet_indic;
    sommet_indic=0;
    do{

    std::cout << "Bienvenue, veuillez rentrer votre choix :" << std::endl;
    std::cout << "Océan : 1" << std::endl;
    std::cout << "Savane : 2"<< std::endl;
    std::cout << "foret : 3"<< std::endl;
    std::cout << "Quitter : 4" << std::endl;

        do
        {
            std::cin >> q;
        }while( q!=1 && q!=2 && q!=3 && q!=4 );

    if(q==4)
    {
        return 0;
    }
    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    /// Le nom du répertoire où se trouvent les images à charger
    grman::set_pictures_path("pics");


    /// Un exemple de graphe
    Graph g;
    if(q == 1)
    {

            while ( !key[KEY_ESC] )
        {

            /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
            g.update();

            if (key[KEY_RIGHT])
            {
                std::cout << "1. Ajout sommet" << std::endl;
                std::cout << "2. Ajout arc" << std::endl;
                std::cout << "3. Retour menu" << std::endl;
                std::cin >> a;
                if(a==1)
                {
                    g.ajouterSommet("fichier1", sommet_indic);
                }
            }

            /// Mise à jour générale (clavier/souris/buffer etc...)
            grman::mettre_a_jour();
        }
    }
    if(q == 2)
    {
        g.chargement("fichier2");
    }
    if(q == 3)
    {
        g.chargement("fichier3");
    }
    system("CLS");


  while ( !key[KEY_ESC] )
        {

            /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
            g.update();
            /// Mise à jour générale (clavier/souris/buffer etc...)
            grman::mettre_a_jour();
        }
    /*/// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement à des frameworks plus avancés )
    while ( !key[KEY_ESC] )
    {
        /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
        g.update();
        /// Mise à jour générale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();
    }*/
    if(q==1) {g.sauvegarde("fichier1");}
    if(q==2) {g.sauvegarde("fichier2");}
    if(q==3) {g.sauvegarde("fichier3");}

    grman::fermer_allegro();
    }while(q!=4);

}
END_OF_MAIN();


