#include "grman/grman.h"
#include <iostream>

#include "graph.h"
#include "Graphe.hpp"

using namespace std;

int main()
{
    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    /// Le nom du r�pertoire o� se trouvent les images � charger
    grman::set_pictures_path("pics");

    /// Un exemple de graphe
    Graph g;
    g.make_example();
/*
    std::string nom;
    Graphe graphe;
    std::cout<<"Saisir nom fichier (faucon_et_hibiscus.txt)"<<std::endl;
    std::cin>>nom;
    graphe.lecture_fichier(nom);
*/
    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement � des frameworks plus avanc�s )
    while ( !key[KEY_ESC] )
    {
        /// Il faut appeler les m�thodes d'update des objets qui comportent des widgets
        g.update();

        /// Mise � jour g�n�rale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();
    }

    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();


