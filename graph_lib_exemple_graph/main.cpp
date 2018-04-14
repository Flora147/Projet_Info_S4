#include "grman/grman.h"
#include <iostream>

#include "graph.h"
#include "Graphe.hpp"

using namespace std;

int main()
{
    /*/// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    /// Le nom du répertoire où se trouvent les images à charger
    grman::set_pictures_path("pics");

    /// Un exemple de graphe
    Graph g;
    g.make_example();
*/
//    graphe.calcul_K();

  /*  /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement à des frameworks plus avancés )
    while ( !key[KEY_ESC] )
    {
        /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
        g.update();

        /// Mise à jour générale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();
    }

    grman::fermer_allegro();
*/

//Section E : initialisation allegro
    srand(time(NULL));
    allegro_init();
    install_keyboard();
    install_mouse();

    //Section F : ouverture mode grapique
    set_color_depth(desktop_color_depth());
    if(set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0)!=0)
    {
        allegro_message("probleme mode graphique");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    show_mouse(screen);

    int x,y;
    std::string nom;
    Graphe graphe;
    BITMAP* Buffer= create_bitmap(1024,768);
    BITMAP* fond = load_bitmap("fond.bmp", NULL);
    if(!fond)
    {
        allegro_message("prb allocation BITMAP ");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    blit(fond, Buffer, 0, 0, 0,0,800,600);
    std::cout<<"Saisir nom fichier (faucon_et_hibiscus.txt)"<<std::endl;
    std::cin>>nom;
    graphe.lecture_fichier(nom);


    while(!key[KEY_ESC])
    {
        if(mouse_b&1)
        {
            x = mouse_x;
            y = mouse_y;

            if((x<100)&&(100<y<193)) //modif para
            {
                graphe.modifier_param();
            }
            else if((x<100)&&(193<y<288)) //ajout sommet
            {
                std::cout<<"ajout";
            }
        }
        blit(Buffer,screen,0,0,0,0,1024,768);
    }
   // graphe.sauvegarde_fichier(nom);


    return 0;
}
END_OF_MAIN();
