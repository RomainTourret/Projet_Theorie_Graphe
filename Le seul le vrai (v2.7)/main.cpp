#include "grman/grman.h"
#include <iostream>
#include <stdlib.h>
#include "graph.h"

int main()
{

    int q, a, sommet_indic, arc_indic,num;
    sommet_indic=0;
    arc_indic=0;
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

        g.chargement("fichier1");
         while ( !key[KEY_ESC] )
            {

                /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
                g.update();
                if( key[KEY_RIGHT] )
                    {
                        std::cout << "1. Ajout sommet" << std::endl;
                        std::cout << "2. Ajout arc" << std::endl;
                        std::cout << "3. Retour menu" << std::endl;
                        std::cout << "4. Supprimer un arc" << std::endl;
                        std::cin >> a;


                        if(a==1)
                        {
                            g.ajouterSommet("fichier1", sommet_indic);
                        }
                        else if(a==2)
                        {
                            g.ajouterArc("fichier1", arc_indic);
                        }
                        if (a==4)
                        {
                            std::cout << " Quel arc voulez vous supprimer ?" << std::endl;
                            std::cin >> num;

                            g.test_remove_edge(num);
                        }
                    }
                /// Mise à jour générale (clavier/souris/buffer etc...)
                grman::mettre_a_jour();
            }
    }
    else if(q == 2)
    {
        g.chargement("fichier2");
         while ( !key[KEY_ESC] )
            {

                /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
                g.update();
                if( key[KEY_RIGHT] )
                    {
                        std::cout << "1. Ajout sommet" << std::endl;
                        std::cout << "2. Ajout arc" << std::endl;
                        std::cout << "3. Retour menu" << std::endl;
                        std::cin >> a;


                        if(a==1)
                        {
                            g.ajouterSommet("fichier2", sommet_indic);
                        }
                        else if(a==2)
                        {
                            g.ajouterArc("fichier2", arc_indic);
                        }
                    }
                /// Mise à jour générale (clavier/souris/buffer etc...)
                grman::mettre_a_jour();
            }
    }
    else if(q == 3)
    {
        g.chargement("fichier3");
         while ( !key[KEY_ESC] )
            {

                /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
                g.update();
                if( key[KEY_RIGHT] )
                    {
                        std::cout << "1. Ajout sommet" << std::endl;
                        std::cout << "2. Ajout arc" << std::endl;
                        std::cout << "3. Retour menu" << std::endl;
                        std::cin >> a;


                        if(a==1)
                        {
                            g.ajouterSommet("fichier3", sommet_indic);
                        }
                        else if(a==2)
                        {
                            g.ajouterArc("fichier3", arc_indic);
                        }
                    }
                /// Mise à jour générale (clavier/souris/buffer etc...)
                grman::mettre_a_jour();
            }
    }
    system("CLS");


    if(q==1) {g.sauvegarde("fichier1");}
    if(q==2) {g.sauvegarde("fichier2");}
    if(q==3) {g.sauvegarde("fichier3");}

    grman::fermer_allegro();
    }while(q!=4);

}
END_OF_MAIN();


