#include "graph.h"
#include <fstream>
#include <stdlib.h>

/***************************************************
                    VERTEX
****************************************************/

/// Le constructeur met en place les éléments de l'interface
VertexInterface::VertexInterface(int idx, int x, int y, std::string pic_name, int pic_idx)
{
    // La boite englobante
    m_top_box.set_pos(x, y);
    m_top_box.set_dim(130, 100);
    m_top_box.set_moveable();

    // Le slider de réglage de valeur
    m_top_box.add_child( m_slider_value );
    m_slider_value.set_range(0.0 , 100.0); // Valeurs arbitraires, à adapter...
    m_slider_value.set_dim(20,80);
    m_slider_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);

    // Label de visualisation de valeur
    m_top_box.add_child( m_label_value );
    m_label_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Down);

    // Une illustration...
    if (pic_name!="")
    {
        m_top_box.add_child( m_img );
        m_img.set_pic_name(pic_name);
        m_img.set_pic_idx(pic_idx);
        m_img.set_gravity_x(grman::GravityX::Right);
    }

    // Label de visualisation d'index du sommet dans une boite
    m_top_box.add_child( m_box_label_idx );
    m_box_label_idx.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Down);
    m_box_label_idx.set_dim(20,12);
    m_box_label_idx.set_bg_color(BLANC);

    m_box_label_idx.add_child( m_label_idx );
    m_label_idx.set_message( std::to_string(idx) );
}


/// Gestion du Vertex avant l'appel à l'interface
void Vertex::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_value vers le slider associé
    m_interface->m_slider_value.set_value(m_value);

    /// Copier la valeur locale de la donnée m_value vers le label sous le slider
    m_interface->m_label_value.set_message( std::to_string( (int)m_value) );
}


/// Gestion du Vertex après l'appel à l'interface
void Vertex::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_value locale
    m_value = m_interface->m_slider_value.get_value();
}



/***************************************************
                    EDGE
****************************************************/

/// Le constructeur met en place les éléments de l'interface
EdgeInterface::EdgeInterface(Vertex& from, Vertex& to)
{
    // Le WidgetEdge de l'interface de l'arc
    if ( !(from.m_interface && to.m_interface) )
    {
        std::cerr << "Error creating EdgeInterface between vertices having no interface" << std::endl;
        throw "Bad EdgeInterface instanciation";
    }
    m_top_edge.attach_from(from.m_interface->m_top_box);
    m_top_edge.attach_to(to.m_interface->m_top_box);
    m_top_edge.reset_arrow_with_bullet();

    // Une boite pour englober les widgets de réglage associés
    m_top_edge.add_child(m_box_edge);
    m_box_edge.set_dim(24,60);
    m_box_edge.set_bg_color(BLANCBLEU);

    // Le slider de réglage de valeur
    m_box_edge.add_child( m_slider_weight );
    m_slider_weight.set_range(0.0 , 100.0); // Valeurs arbitraires, à adapter...
    m_slider_weight.set_dim(16,40);
    m_slider_weight.set_gravity_y(grman::GravityY::Up);

    // Label de visualisation de valeur
    m_box_edge.add_child( m_label_weight );
    m_label_weight.set_gravity_y(grman::GravityY::Down);

}


/// Gestion du Edge avant l'appel à l'interface
void Edge::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_weight vers le slider associé
    m_interface->m_slider_weight.set_value(m_weight);

    /// Copier la valeur locale de la donnée m_weight vers le label sous le slider
    m_interface->m_label_weight.set_message( std::to_string( (int)m_weight ) );
}

/// Gestion du Edge après l'appel à l'interface
void Edge::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_weight locale
    m_weight = m_interface->m_slider_weight.get_value();
}



/***************************************************
                    GRAPH
****************************************************/

/// Ici le constructeur se contente de préparer un cadre d'accueil des
/// éléments qui seront ensuite ajoutés lors de la mise ne place du Graphe
GraphInterface::GraphInterface(int x, int y, int w, int h)
{
    m_top_box.set_dim(1000,740);
    m_top_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);

    m_top_box.add_child(m_tool_box);
    m_tool_box.set_dim(80,720);
    m_tool_box.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_tool_box.set_bg_color(BLANCBLEU);

///creer une boite pour sauvegarder
    m_tool_box.add_child(m_tool_sauve);
    m_tool_sauve.set_dim(70,50);
    m_tool_sauve.set_posy(60);
    m_tool_sauve.set_gravity_x(grman::GravityX::Left);
    m_tool_sauve.add_child(m_label_sauve);
    m_tool_sauve.set_bg_color(ROUGESOMBRE);



    m_top_box.add_child(m_main_box);
    m_main_box.set_dim(908,720);
    m_main_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_main_box.set_bg_color(BLANCJAUNE);
}


/// Méthode spéciale qui construit un graphe arbitraire (démo)
/// Cette méthode est à enlever et remplacer par un système
/// de chargement de fichiers par exemple.
/// Bien sûr on ne veut pas que vos graphes soient construits
/// "à la main" dans le code comme ça.
void Graph::ecosysteme1()
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
    // La ligne précédente est en gros équivalente à :
    // m_interface = new GraphInterface(50, 0, 750, 600);

    /// Les sommets doivent être définis avant les arcs
    // Ajouter le sommet d'indice 0 de valeur 30 en x=200 et y=100 avec l'image clown1.jpg etc...
    add_interfaced_vertex(0,  30.0, 200, 100, "Organisme_unicellulaire.jpg");
    add_interfaced_vertex(1, 60.0, 400, 100, "Crevette.jpg");
    add_interfaced_vertex(2,  100.0, 600, 100, "Petits_poissons.jpg");
    add_interfaced_vertex(3, 60.0, 700, 300, "Maquereau.jpg");
    add_interfaced_vertex(4,  0.0, 500, 400, "Thon.jpg");
    add_interfaced_vertex(5,  100.0, 300, 400, "Requin.jpg");


    /// Les arcs doivent être définis entre des sommets qui existent !
    // AJouter l'arc d'indice 0, allant du sommet 1 au sommet 2 de poids 50 etc...
    add_interfaced_edge(0, 1, 0, 50.0);
    add_interfaced_edge(1, 2, 1, 50.0);
    add_interfaced_edge(2, 3, 2, 50.0);
    add_interfaced_edge(3, 4, 3, 50.0);
    add_interfaced_edge(4, 4, 2, 50.0);
    add_interfaced_edge(5, 5, 4, 50.0);
}


void Graph::ecosysteme2()
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
    // La ligne précédente est en gros équivalente à :
    // m_interface = new GraphInterface(50, 0, 750, 600);

    /// Les sommets doivent être définis avant les arcs
    // Ajouter le sommet d'indice 0 de valeur 30 en x=200 et y=100 avec l'image clown1.jpg etc...
    add_interfaced_vertex(0,  30.0, 400, 200, "Vegetaux.jpg");
    add_interfaced_vertex(1, 60.0, 0, 0, "Dromadaire.jpg");
    add_interfaced_vertex(2,  100.0, 700, 200, "Gazelle.jpg");
    add_interfaced_vertex(3, 60.0, 400, 0, "Addax.jpg");
    add_interfaced_vertex(4,  0.0, 600, 0, "Guepard.jpg");
    add_interfaced_vertex(5,  100.0, 350, 350, "Fourmi.jpg");
    add_interfaced_vertex(6,  100.0, 150, 450, "Scorpion.jpg");
    add_interfaced_vertex(7,  100.0, 600, 350, "Gerbille.jpg");
    add_interfaced_vertex(8,  100.0, 750, 400, "Fennec.jpg");


    /// Les arcs doivent être définis entre des sommets qui existent !
    // AJouter l'arc d'indice 0, allant du sommet 1 au sommet 2 de poids 50 etc...
    add_interfaced_edge(0, 1, 0, 50.0);
    add_interfaced_edge(1, 2, 0, 50.0);
    add_interfaced_edge(2, 3, 0, 50.0);
    add_interfaced_edge(3, 5, 0, 50.0);
    add_interfaced_edge(4, 7, 0, 50.0);
    add_interfaced_edge(5, 6, 5, 50.0);
    add_interfaced_edge(6, 7, 5, 50.0);
    add_interfaced_edge(7, 8, 7, 50.0);
    add_interfaced_edge(8, 4, 2, 50.0);
    add_interfaced_edge(9, 4, 3, 50.0);
}

void Graph::ecosysteme3()
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
    // La ligne précédente est en gros équivalente à :
    // m_interface = new GraphInterface(50, 0, 750, 600);

    /// Les sommets doivent être définis avant les arcs
    // Ajouter le sommet d'indice 0 de valeur 30 en x=200 et y=100 avec l'image clown1.jpg etc...
    add_interfaced_vertex(0,  30.0, 375, 615, "végétaux.jpg");
    add_interfaced_vertex(1,  30.0, 375, 475, "papillon.jpg");
    add_interfaced_vertex(2,  30.0, 375, 350, "araignée.jpg");
    add_interfaced_vertex(6,  30.0, 375, 200, "rouge_gorge.jpg");
    add_interfaced_vertex(7,  30.0, 550, 200, "lapin.jpg");
    add_interfaced_vertex(8,  30.0, 750, 200, "musaraigne.jpg");
    add_interfaced_vertex(5,  30.0, 200, 200, "grenouille.jpg");
    add_interfaced_vertex(4,  30.0, 0, 200, "herisson.jpg");
    add_interfaced_vertex(3,  30.0, 100, 400, "hanneton.jpg");
    add_interfaced_vertex(9,  30.0, 0, 0, "renard.jpg");
    add_interfaced_vertex(10,  30.0, 750, 0, "chouette.jpg");
    add_interfaced_vertex(11,  30.0, 375, 0, "loup.jpg");


    /// Les arcs doivent être définis entre des sommets qui existent !
    // AJouter l'arc d'indice 0, allant du sommet 1 au sommet 2 de poids 50 etc...
    add_interfaced_edge(0, 1, 0, 50.0);
    add_interfaced_edge(1, 2, 1, 50.0);
    add_interfaced_edge(2, 6, 2, 50.0);
    add_interfaced_edge(3, 7, 0, 50.0);
    add_interfaced_edge(4, 8, 1, 50.0);
    add_interfaced_edge(5, 8, 2, 50.0);
    add_interfaced_edge(6, 5, 2, 50.0);
    add_interfaced_edge(7, 5, 1, 50.0);
    add_interfaced_edge(8, 3, 0, 50.0);
    add_interfaced_edge(9, 9, 0, 50.0);
    add_interfaced_edge(10, 6, 3, 50.0);
    add_interfaced_edge(11, 4, 3, 50.0);
    add_interfaced_edge(12, 9, 4, 50.0);
    add_interfaced_edge(13, 9, 5, 50.0);
    add_interfaced_edge(14, 9, 6, 50.0);
    add_interfaced_edge(15, 9, 7, 50.0);
    add_interfaced_edge(16, 9, 8, 50.0);
    add_interfaced_edge(17, 10, 4, 50.0);
    add_interfaced_edge(18, 10, 5, 50.0);
    add_interfaced_edge(19, 10, 6, 50.0);
    add_interfaced_edge(20, 10, 7, 50.0);
    add_interfaced_edge(21, 10, 8, 50.0);
    add_interfaced_edge(22, 11, 9, 50.0);
    add_interfaced_edge(23, 11, 7, 50.0);
}


/// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
void Graph::update()
{
    if (!m_interface)
        return;

    for (auto &elt : m_vertices)
        elt.second.pre_update();

    for (auto &elt : m_edges)
        elt.second.pre_update();

    m_interface->m_top_box.update();

    for (auto &elt : m_vertices)
        elt.second.post_update();

    for (auto &elt : m_edges)
        elt.second.post_update();

}

/// Aide à l'ajout de sommets interfacés
void Graph::add_interfaced_vertex(int idx, double value, int x, int y, std::string pic_name, int pic_idx )
{
    if ( m_vertices.find(idx)!=m_vertices.end() )
    {
        std::cerr << "Error adding vertex at idx=" << idx << " already used..." << std::endl;
        throw "Error adding vertex";
    }
    // Création d'une interface de sommet
    VertexInterface *vi = new VertexInterface(idx, x, y, pic_name, pic_idx);
    // Ajout de la top box de l'interface de sommet
    m_interface->m_main_box.add_child(vi->m_top_box);
    // On peut ajouter directement des vertices dans la map avec la notation crochet :
    m_vertices[idx] = Vertex(value, vi);
}

/// Aide à l'ajout d'arcs interfacés
void Graph::add_interfaced_edge(int idx, int id_vert1, int id_vert2, double weight)
{
    if ( m_edges.find(idx)!=m_edges.end() )
    {
        std::cerr << "Error adding edge at idx=" << idx << " already used..." << std::endl;
        throw "Error adding edge";
    }

    if ( m_vertices.find(id_vert1)==m_vertices.end() || m_vertices.find(id_vert2)==m_vertices.end() )
    {
        std::cerr << "Error adding edge idx=" << idx << " between vertices " << id_vert1 << " and " << id_vert2 << " not in m_vertices" << std::endl;
        throw "Error adding edge";
    }

    EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]);
    m_interface->m_main_box.add_child(ei->m_top_edge);
    m_edges[idx] = Edge(weight, ei);
    m_edges[idx].m_from = id_vert1;
    m_edges[idx].m_to = id_vert2;
    m_vertices[id_vert1].m_out.push_back(idx);
    m_vertices[id_vert2].m_in.push_back(idx);
}

void Graph::sauvegarde(std::string NomFichier)
{
    std::string number;
    int pos_sommetx;
    int pos_sommety;

    std::ofstream fichier(NomFichier+".txt",std::ios::out);

    if(fichier)
    {
        fichier<< m_vertices.size()<<std::endl;
        fichier<<m_edges.size()<<std::endl;

        for(auto&el:m_vertices)
        {
            fichier<<el.first<<std::endl;
            fichier<<el.second.m_value<<std::endl;
            pos_sommetx=el.second.m_interface->m_top_box.get_posx()+2;
            pos_sommety=el.second.m_interface->m_top_box.get_posy()+2;
            fichier<<pos_sommetx<<std::endl;
            fichier<<pos_sommety<<std::endl;
            number=std::to_string(el.first+1);
            fichier<<el.second. m_interface->m_img.get_pic_name() <<std::endl;

        }


        for(auto&el:m_edges)

        {
            fichier<<el.first<<std::endl;
            fichier<<el.second.m_to<<std::endl;
            fichier<<el.second.m_from<<std::endl;
            fichier<<el.second.m_weight<<std::endl;

        }
        std::cout<<"Sauvegarde"<<std::endl;


    }
    else
    {
        throw std::string("il n'existe pas de fichier portant ce nom");
    }
    fichier.close();
}

void Graph::chargement(std::string NomFichier)
{
    std::ifstream fichier(NomFichier+".txt");
    if(fichier)
    {
        m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
        int nb_sommet;
        int nb_arete;
        fichier>>nb_sommet;
        fichier>>nb_arete;
        std::string nom_photo;
        int n1,n2,n3,n4;
        int a1,a2,a3,a4;
         for(int i=0;i<nb_sommet;i++)
       {
           fichier>>n1;
           fichier>>n2;
           fichier>>n3;
           fichier>>n4;
           fichier>> nom_photo;
           add_interfaced_vertex(n1, n2, n3, n4, nom_photo);
       }

       for(int i=0;i<nb_arete;i++)
       {
           fichier>>a1;
           fichier>>a2;
           fichier>>a3;
           fichier>>a4;
           add_interfaced_edge(a1, a2, a3, a4);
       }


    }
    fichier.close();
}


void Graph::creerGraph() ///Permet à l'utilisateur de créer un graph en entier
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
    // La ligne précédente est en gros équivalente à :
    // m_interface = new GraphInterface(50, 0, 750, 600);
    int k;
    int b = 0; //nb de sommets désirés
    do
    {
        std::cout << "Que voulez vous faire ?" << std::endl;
        std::cout << "1. Ajouter un sommet" << std::endl;
        std::cout << "2. Ajouter un arc" << std::endl;
        std::cout << "3. Revenir au menu" << std::endl;
        std::cin >> k;
        std::system("CLS");                 ///SYSTEM CLS ICI
    }while(k != 1 && k != 2 && k != 3);

    if(k == 1)
    {
        int a;
        ///Ajout d'un sommet
        //add_interfaced_vertex(0,  30.0, 400, 200, "Vegetaux.jpg");  (numéro sommet, poid, abscisse, ordonnée)
        do
        {
            ///Choix de l'utilisateur
            std::cout << "1. Ajout d'un sommet" << std::endl;
            std::cout << "2. Revenir en arriere" << std::endl;
            std::cin >> a;
            std::system("CLS");             ///SYSTEM CLS ICI
        }while(a != 1 && a != 2);
        if(a == 1)
        {
            std::cout << "Combien de sommets (8 maximum) ?" << std::endl;
            do{
                std::cin >> b;  ///Annonce du nb de sommets désirés par l'utilisateur
            }while(b == 0 && b > 8);
            for(int i = 0 ; i < b-1 ; i++)
            {
                double z;
                std::string m;

                std::cout << "Voici la liste des populations disponibles :" << std::endl;
                std::cout << "1.chouette    2.Fennec    3.Guepard   4.loup  5.renard" << std::endl;
                std::cout << "6.Requin      7.Scorpion  8.araignée  9.Addax 10.Dromadaire" << std::endl;
                std::cout << "11.Crevette   12.Petits_Poissons      13.Organisme_unicellulaire" << std::endl;
                std::cout << "14.Fourmi     15.Hanneton 16.papillon 17.rouge_gorge" << std::endl;
                std::cout << "18.lapin      19.Gazelle  20.Gerbille 21.Grenouille" << std::endl;
                std::cout << "22.Thon       23.Vegetaux 24.Maquereau    25.musaraigne" << std::endl;
                std::cout << std::endl;
                std::cout << "Rentrez le nom EXACT en respectant majuscule, tiret,etc." << std::endl;
                std::cin >> m;
                m = m + ".jpg";
                std::cout << "Quantite ?";
                std::cin >> z;
                add_interfaced_vertex(i, z, 0, 0, m);
                system("CLS");                  ///SYSTEM CLS ICI
            }
        }
    }

    /*if(k == 2)
    {
        ///Ajout d'un arc
        //add_interfaced_edge(0, 1, 0, 50.0); (numéro arc, prédateur, victime, poid)
        if(b == 0)
        {
            std::cout >> "Aucun sommet de créer. Retour." >> std::endl;
        }
        else
        {
            std::cout >> "rentrez les numéros des sommets dans cet ordre : X mange Y" >> std::endl;
            std::cin >> ;
            std::cin >> ;
        }
    }*/

    if(k == 3)
    {
        ///sortie
    }
}

void Graph::ajouterSommet(std::string NomFichier, int sommet_indic)
{
    std::string nom_sommet;
    int nb_sommet;
    int z;
        std::cout << "Voici la liste des populations disponibles :" << std::endl;
        std::cout << "1.chouette    2.Fennec    3.Guepard   4.loup  5.renard" << std::endl;
        std::cout << "6.Requin      7.Scorpion  8.araignée  9.Addax 10.Dromadaire" << std::endl;
        std::cout << "11.Crevette   12.Petits_Poissons      13.Organisme_unicellulaire" << std::endl;
        std::cout << "14.Fourmi     15.Hanneton 16.papillon 17.rouge_gorge" << std::endl;
        std::cout << "18.lapin      19.Gazelle  20.Gerbille 21.Grenouille" << std::endl;
        std::cout << "22.Thon       23.Vegetaux 24.Maquereau    25.musaraigne" << std::endl;
        std::cout << std::endl;
        std::cout << "Rentrez le nom EXACT en respectant majuscule, tiret,etc." << std::endl;

        std::cin >> nom_sommet;
        nom_sommet = nom_sommet + ".jpg";
        std::cout << "Quantite ? ";
        std::cin >> z;

    std::ifstream fichier(NomFichier+".txt");

    //std::cout<<nb_sommet<<std::endl;

    if(fichier.is_open())
    {
        fichier>>nb_sommet;
        //std::cout<<nb_sommet<<std::endl;
    }

    add_interfaced_vertex(nb_sommet+sommet_indic, z, 0, 0,nom_sommet);
    sommet_indic+=1;
}

void Graph::ajouterArc(std::string NomFichier, int arc_indic)
{
    int nb_sommet;
    int nb_arc;
    int sommet1,sommet2;
    std::cout << "rentrez les numéros des sommets dans cet ordre : X mange Y" << std::endl;
    std::cin >> sommet1;
    std::cin >> sommet2;

    std::ifstream fichier(NomFichier+".txt");
    if(fichier.is_open())
    {
        fichier>>nb_sommet;
        fichier>>nb_arc;
    }
    int a1;

    for(auto&el:m_edges)
        {
            a1=el.first;
        }


    add_interfaced_edge(a1+1, sommet1, sommet2, 50.0);
    arc_indic++;

}

void Graph::test_remove_edge(int eidx)
{
    /// référence vers le Edge à enlever
    Edge &remed=m_edges.at(eidx);

    std::cout << "Removing edge " << eidx << " " << remed.m_from << "->" << remed.m_to << " " << remed.m_weight << std::endl;

    /// Tester la cohérence : nombre d'arc entrants et sortants des sommets 1 et 2
    std::cout << m_vertices[remed.m_from].m_in.size() << " " << m_vertices[remed.m_from].m_out.size() << std::endl;
    std::cout << m_vertices[remed.m_to].m_in.size() << " " << m_vertices[remed.m_to].m_out.size() << std::endl;
    std::cout << m_edges.size() << std::endl;

    /// test : on a bien des éléments interfacés
    if (m_interface && remed.m_interface)
    {
    /// Ne pas oublier qu'on a fait ça à l'ajout de l'arc :
    // EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]);
    //m_interface->m_main_box.add_child(ei->m_top_edge);
    //m_edges[idx] = Edge(weight, ei);
    /// Le new EdgeInterface ne nécessite pas de delete car on a un shared_ptr
    /// Le Edge ne nécessite pas non plus de delete car on n'a pas fait de new (sémantique par valeur)
    /// mais il faut bien enlever le conteneur d'interface m_top_edge de l'arc de la main_box du graphe
    m_interface->m_main_box.remove_child( remed.m_interface->m_top_edge );
    }

    /// Il reste encore à virer l'arc supprimé de la liste des entrants et sortants des 2 sommets to et from !
    /// References sur les listes de edges des sommets from et to
    std::vector<int> &vefrom = m_vertices[remed.m_from].m_out;
    std::vector<int> &veto = m_vertices[remed.m_to].m_in;
    vefrom.erase( std::remove( vefrom.begin(), vefrom.end(), eidx ), vefrom.end() );
    veto.erase( std::remove( veto.begin(), veto.end(), eidx ), veto.end() );

    /// Le Edge ne nécessite pas non plus de delete car on n'a pas fait de new (sémantique par valeur)
    /// Il suffit donc de supprimer l'entrée de la map pour supprimer à la fois l'Edge et le EdgeInterface
    /// mais malheureusement ceci n'enlevait pas automatiquement l'interface top_edge en tant que child de main_box !
    m_edges.erase( eidx );

    /// Tester la cohérence : nombre d'arc entrants et sortants des sommets 1 et 2
    std::cout << m_vertices[remed.m_from].m_in.size() << " " << m_vertices[remed.m_from].m_out.size() << std::endl;
    std::cout << m_vertices[remed.m_to].m_in.size() << " " << m_vertices[remed.m_to].m_out.size() << std::endl;
    std::cout << m_edges.size() << std::endl;

/*
     for(int i=eidx; i<m_edges.size()+1; i++)
     {
         //g.m_edge[i]=g.m_edge[i+1];
         m_edges.at(i)=m_edges.at(i+1);
     }

     int a;
     a=m_edges.size();
     m_edges.erase(a);
*/
}
