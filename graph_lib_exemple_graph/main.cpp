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
    if(set_gfx_mode(GFX_AUTODETECT,1024,768,0,0)!=0)
    {
        allegro_message("probleme mode graphique");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    show_mouse(screen);

    int x,y, x1, y1;
    int c;
    int f = 0;
    int compt = 0;
    int compt2 = 0;
    std::vector<int> temp_x1;
    std::vector<int> temp_x2;
    std::vector<int> temp_y1;
    std::vector<int> temp_y2;
    bool m = true;
    bool tps_reel = false;
    std::string nom;
    Graphe graphe;
    Graphe graphe_temp;
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
                    graphe.lecture_fichier(nom);
                    actuelle = fond;
                    m = false;
                }
            }


            else if(c==makecol(0,0,255))
            {
               if (m==true)
                {
                    nom ="Tigre_et_plancton.txt";
                    graphe.lecture_fichier(nom);
                    actuelle = fond;
                    m = false;
                }
            }


            else if(c==makecol(255,255,0))
            {
                if (m==true)
                {
                    nom ="insectes_et_foret.txt";
                    graphe.lecture_fichier(nom);
                    actuelle = fond;
                    m = false;
                }
            }


            else if(c==makecol(0,255,255))
            {
                if(m==true)
                {
                    //quitter
                    exit(0);
                }
            }


            else if(c==makecol(255,0,255))
            {
                graphe.sauvegarde_fichier(nom);
                actuelle = menu;
                m = true;
            }

            else if(c==makecol(255,174,201))
            {
                //K-connexité
                graphe.k_connexite(Buffer);
            }

            else if(c==makecol(255,128,0))
            {
                //Forte connexite
                std::vector<Sommet> non_d;
                std::vector<Arc> non_vis;
                int nouv_o = 0;
                int nou_arc = 0;
                for(int i=0; i<graphe.getOrdre(); i++)
                {
                    if(graphe.getVectSom()[i].getAffSom() == true)
                    {
                        non_d.push_back(graphe.getVectSom()[i]);
                        nouv_o++;
                    }
                }
                for(int j = 0; j<graphe.getNbArcs();j++)
                {
                    if((graphe.getVectArcs()[j].getS1().getAffSom()==true) && (graphe.getVectArcs()[j].getS1().getAffSom()==true))
                    {
                        non_vis.push_back(graphe.getVectArcs()[j]);
                        nou_arc++;
                    }
                }
                if(nouv_o != graphe.getOrdre())
                {
                    for(int i = 0; i<nouv_o; i++)
                    {
                        non_d[i].setNumero(i);
                    }
                }
                graphe_temp.setOrdre(nouv_o);
                graphe_temp.setNbMois(graphe.getNbMois());
                graphe_temp.setNbMoisTemp(graphe.getNbMoisTemp());
                graphe_temp.setNbArcs(nou_arc);
                graphe_temp.setVectArcs(non_vis);
                graphe_temp.setVectSom(non_d);
                graphe_temp.forte_co(graphe_temp, actuelle, temp_x1, temp_y1, temp_x2, temp_y2);
                f = 1;
            }

            else if(c==makecol(34,177,76))
            {
                //Temps réel
                tps_reel = true;
            }

            rest(1000);
        }


        if(mouse_b&2)
        {
            x = mouse_x;
            y = mouse_y;


            for(int i=0; i<graphe.getOrdre(); i++)
            {

                if(graphe.getVectSom()[i].getSelect()==true)
                {
                    graphe.bouger_sommet(Buffer, x, y, i);
                }
            }

            rest(1000);
        }
        //Si On a lancé la simulation en temps réel
        if((tps_reel == true )&&(key[KEY_ENTER]))
        {
            //Tant qu'on ne l'arrete pas on continue
           while(tps_reel!= false)
            {
                // on lance la simulation
                graphe.temps_reel(actuelle, Buffer, compt);
                rest(1500);
                //Si on arrete la simulation on décide ou non de conservaer les paramètres comme ils sont
                if (key[KEY_S])
                {
                    tps_reel = false;
                    graphe.conservation_para();
                }
                // si on demande à modifier un paramètre, on le modifie avant de reprendre
                else if((key[KEY_P])) graphe.modifier_param();
                //Si on fait une pause, on reprend la simulation uniquement si il y a un appui sur s;
                else if(key[KEY_SPACE])
                {
                    while(!(key[KEY_R]))
                        compt2++;
                    compt2 = 0;
                }
                compt++;
            }
        }


        if(m==false)
        {
            graphe.afficher_sommets(Buffer);

            if(f==1)
            {
               rest(2000);

                blit(Buffer,screen,0,0,0,0,1024,768);
                blit(actuelle, Buffer, 0,0,0,0,1024,768);
                graphe.afficher_sommets(Buffer);
                //On retire les rectangles
                for(int i = 0; i<temp_x1.size(); i++)
                {
                    rest(500);
                    rectfill(actuelle, temp_x1[i], temp_y1[i],temp_x1[i]+temp_x2[i],temp_y1[i]+temp_y2[i],makecol(255,255,255));
                    //clear(actuelle);
                    blit(Buffer,screen,0,0,0,0,1024,768);
                    blit(actuelle, Buffer, 0,0,0,0,1024,768);
                    graphe.afficher_sommets(Buffer);
                }
                //graphe.afficher_sommets(Buffer);
                f=0;
            }

        }

        blit(Buffer,screen,0,0,0,0,1024,768);
        blit(actuelle, Buffer, 0,0,0,0,1024,768);
    }


    graphe.sauvegarde_fichier(nom);

    return 0;

}
END_OF_MAIN();
