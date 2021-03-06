#include "grman/grman.h"
#include <iostream>

#include "graph.h"
#include "Graphe.hpp"

using namespace std;

int main()
{
    /*/// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    /// Le nom du r�pertoire o� se trouvent les images � charger
    grman::set_pictures_path("pics");

    /// Un exemple de graphe
    Graph g;
    g.make_example();
*/
//    graphe.calcul_K();

  /*  /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement � des frameworks plus avanc�s )
    while ( !key[KEY_ESC] )
    {
        /// Il faut appeler les m�thodes d'update des objets qui comportent des widgets
        g.update();

        /// Mise � jour g�n�rale (clavier/souris/buffer etc...)
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
    if(set_gfx_mode(GFX_AUTODETECT_WINDOWED,1024,768,0,0)!=0)
    {
        allegro_message("probleme mode graphique");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    show_mouse(screen);

    int x,y, x1, y1;
    int c;
    bool m = true;
    std::string nom;
    Graphe graphe;
    BITMAP* Buffer= create_bitmap(1024,768);

    BITMAP* menu = load_bitmap("Menu.bmp", NULL);
    if(!menu)
    {
        allegro_message("prb allocation BITMAP Menu");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    BITMAP* fond = load_bitmap("fond.bmp", NULL);
    if(!fond)
    {
        allegro_message("prb allocation BITMAP fond");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    BITMAP* sous_fond = load_bitmap("sous_menu.bmp", NULL);
    if(!sous_fond)
    {
        allegro_message("prb allocation BITMAP sous-fond");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    BITMAP* actuelle = menu;
    blit(actuelle, Buffer, 0, 0, 0,0,1024,768);

   // nom ="faucon_et_hibiscus.txt";
    //graphe.lecture_fichier("faucon_et_hibiscus.txt");

    //std::cout<<"Saisir nom fichier (faucon_et_hibiscus.txt)"<<std::endl;
    //std::cin>>nom;
    //graphe.lecture_fichier(nom);

    text_mode(-1);

    while(!key[KEY_ESC])
    {
        if(mouse_b&1)
        {
            x = mouse_x;
            y = mouse_y;

            if(m==false) graphe.select_sommet(x, y);

            c = getpixel(sous_fond, mouse_x, mouse_y);
            if(c==makecol(255,0,0)) graphe.effacer_sommet(Buffer);
            else if (c==makecol(0,0,0)) graphe.modifier_param();
            else if(c==makecol(0,255,0)) graphe.ajouter_sommet();
            else if(c==makecol(255,255,255))
            {
                if (m==true)
                {
                    nom ="faucon_et_hibiscus.txt";
                    graphe.lecture_fichier("faucon_et_hibiscus.txt");
                    actuelle = fond;
                    m = false;
                }
            }
            else if(c==makecol(0,0,255))
            {
               if (m==true)
                {
                   // nom ="faucon_et_hibiscus.txt";
                    //graphe.lecture_fichier("faucon_et_hibiscus.txt");
                    actuelle = fond;
                    m = false;
                }
            }
            else if(c==makecol(255, 255,0 ))
            {
                if (m==true)
                {
                    //nom ="faucon_et_hibiscus.txt";
                    //graphe.lecture_fichier("faucon_et_hibiscus.txt");
                    actuelle = fond;
                    m = false;
                }
            }
            else if(c==makecol(0, 255, 255))
            {
                //quitter
            }
            else if(c==makecol(255,0,255))
            {
                graphe.sauvegarde_fichier(nom);
                actuelle = menu;
                m = true;
            }

            rest(1000);
        }

        if(mouse_b&2)
        {
            x = mouse_x;
            y = mouse_y;
            for(int i=0;i<graphe.getOrdre(); i++)
            {
                if(graphe.getVectSom()[i].getSelect()==true)
                {
                    graphe.bouger_sommet(Buffer, x, y, i);
                }
            }
            rest(1000);
        }

        if(m==false) graphe.afficher_sommets(Buffer);
        blit(Buffer,screen,0,0,0,0,1024,768);
        blit(actuelle, Buffer, 0,0,0,0,1024,768);
    }

    graphe.sauvegarde_fichier(nom);
    return 0;
}
END_OF_MAIN();
