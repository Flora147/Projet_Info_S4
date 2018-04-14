#include <iostream>

#include "Graphe.hpp"

using namespace std;

int main()
{

    //Section A : initialisation allegro
    srand(time(NULL));
    allegro_init();
    install_keyboard();
    install_mouse();


    //Section B : ouverture mode grapique
    set_color_depth(desktop_color_depth());
    if(set_gfx_mode(GFX_AUTODETECT_WINDOWED,1024,768,0,0)!=0)
    {
        allegro_message("probleme mode graphique");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    show_mouse(screen);

    //Instance de variables
    int x,y;
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

    //Creation d'un menu, sou-menu et fond
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

    //Instance d'une BITMAP et affichage
    BITMAP* actuelle = menu;
    blit(actuelle, Buffer, 0, 0, 0,0,1024,768);

    //Tout le texte en allegro aura un fond transparent
    text_mode(-1);


    //SECTION C : BOUCLE DE JEU
    while(!key[KEY_ESC])
    {
        //Si clic gauche
        if(mouse_b&1)
        {
            //On conserve les coordonnées de la souris
            x = mouse_x;
            y = mouse_y;

            //Si on est sur un graphe cela signifie que l'on a sélectionné un sommet
            if(m==false) graphe.select_sommet(x, y);

            //On prend la couleur à l'endroit du clic gauche
            c = getpixel(sous_fond, mouse_x, mouse_y);

            //Si on est dans la barre outil et le clic est sur "Supprimer"
            if(c==makecol(255,0,0)) graphe.effacer_sommet(Buffer);

            //Si on est dans la barre outil et le clic est sur "Modifier"
            else if (c==makecol(0,0,0)) graphe.modifier_param();

            //Si on est dans la barre outil et le clic est sur "Ajouter"
            else if(c==makecol(0,255,0)) graphe.ajouter_sommet();

            //Si on appuie sur le graphe1
            else if(c==makecol(255,255,255))
            {
                //Si on est sur le menu
                if (m==true)
                {
                    //On ouvre ce graphe
                    nom ="faucon_et_hibiscus.txt";
                    graphe.lecture_fichier(nom);
                    actuelle = fond;
                    m = false;
                }
            }

            //Si on appuie sur le graphe2
            else if(c==makecol(0,0,255))
            {
                //Si on est sur le menu
               if (m==true)
                {
                    //On ouvre ce graphe
                    nom ="Tigre_et_plancton.txt";
                    graphe.lecture_fichier(nom);
                    actuelle = fond;
                    m = false;
                }
            }

            //Si on appuie sur le graphe3
            else if(c==makecol(255,255,0))
            {
                //Si on est sur le menu
                if (m==true)
                {
                    //On ouvre ce graphe
                    nom ="insectes_et_foret.txt";
                    graphe.lecture_fichier(nom);
                    actuelle = fond;
                    m = false;
                }
            }

            //Si on appuie sur "Quitter"
            else if(c==makecol(0,255,255))
            {
                //Si on est sur le menu
                if(m==true)
                {
                    //quitter
                    exit(0);
                }
            }

            //Si on est dans la barre outil et on appuie sur "Changer de graphe"
            else if(c==makecol(255,0,255))
            {
                //Le graphe est sauvegardé et on retourne sur le menu
                graphe.sauvegarde_fichier(nom);
                actuelle = menu;
                m = true;
            }

            //Si on est dans la barre outil et on appuie sur "k-connexité"
            else if(c==makecol(255,174,201))
            {
                //K-connexité
                graphe.k_connexite(Buffer);
            }

            //Si on est dans la barre outil et on appuie sur "forte connexité"
            else if(c==makecol(255,128,0))
            {
                //Forte connexite
                //Instance de variables
                std::vector<Sommet> non_d;
                std::vector<Arc> non_vis;
                int nouv_o = 0;
                int nou_arc = 0;

                //Pour tous les sommets du graphe
                for(int i=0; i<graphe.getOrdre(); i++)
                {
                    //Si le sommet est affiché
                    if(graphe.getVectSom()[i].getAffSom() == true)
                    {
                        //On l'ajout au vecteur de sommets
                        non_d.push_back(graphe.getVectSom()[i]);
                        //On incrémente le compteur correspondant au nombre de sommets affichés
                        nouv_o++;
                    }
                }

                //Pour tous les arc du graphe
                for(int j = 0; j<graphe.getNbArcs();j++)
                {
                    //Si l'arc est affiché
                    if((graphe.getVectArcs()[j].getS1().getAffSom()==true) && (graphe.getVectArcs()[j].getS1().getAffSom()==true))
                    {
                        //On l'ajoute au vecteur d'arcs
                        non_vis.push_back(graphe.getVectArcs()[j]);
                        //On incrémente le compteur correspondant au nombre d'arcs affichés
                        nou_arc++;
                    }
                }

                //Si le compteur sommet est différent du nombre de sommet du graphe
                if(nouv_o != graphe.getOrdre())
                {
                    //Pour i allant de 0 à ce nombre
                    for(int i = 0; i<nouv_o; i++)
                    {
                        //On modifie le numéro des sommets du vecteur de sommets
                        non_d[i].setNumero(i);
                    }
                }

                //On modifie tous les attributs du nouveau graphe
                graphe_temp.setOrdre(nouv_o);
                graphe_temp.setNbMois(graphe.getNbMois());
                graphe_temp.setNbMoisTemp(graphe.getNbMoisTemp());
                graphe_temp.setNbArcs(nou_arc);
                graphe_temp.setVectArcs(non_vis);
                graphe_temp.setVectSom(non_d);

                //On lance la forte connexité sur ce graphe
                graphe_temp.forte_co(graphe_temp, actuelle, temp_x1, temp_y1, temp_x2, temp_y2,false);
                f = 1;
            }

            //Si on est dans la barre outil et on appuie sur "temps réel"
            else if(c==makecol(34,177,76))
            {
                //Temps réel
                tps_reel = true;
            }

            rest(1000);
        }


        //Si clic gauche
        if(mouse_b&2)
        {
            //On conserve les coordonnées de la souris
            x = mouse_x;
            y = mouse_y;

            //Pour tous les sommets du graphe
            for(int i=0; i<graphe.getOrdre(); i++)
            {
                //Si le sommet est sélectionné
                if(graphe.getVectSom()[i].getSelect()==true)
                {
                    //On peut le bouger
                    graphe.bouger_sommet(Buffer, x, y, i);
                }
            }
            rest(1000);
        }

        //Si on a lancé la simulation en temps réel et qu'on appuie sur "ENTER"
        if((tps_reel == true )&&(key[KEY_ENTER]))
        {
            //Tant qu'on ne l'arrête pas
            while(tps_reel!= false)
            {
                //On lance la simulation
                if(graphe.getNonTrop()==false) graphe.temps_reel(actuelle, Buffer, compt);
                else graphe.temps_reel_nont(actuelle, Buffer, compt);
                rest(3000);

                //Si on arrete la simulation ("S"), on décide ou non de conserver les paramètres comme ils sont
                if (key[KEY_S])
                {
                    //Arrêt de la simulation
                    tps_reel = false;
                    graphe.conservation_para();
                }

                //Si on demande à modifier un paramètre ("P"), on le modifie avant de reprendre
                else if((key[KEY_P])) graphe.modifier_param();

                //Si on fait une pause ("SPACE"), on reprend la simulation uniquement si on appuie sur "S";
                else if(key[KEY_SPACE])
                {
                    while(!(key[KEY_R]))
                    {
                        compt2++;
                        if((key[KEY_P])) graphe.modifier_param();
                    }
                    compt2 = 0;
                }
                compt++;
            }
        }

        //Si on n'est pas sur le menu
        if(m==false)
        {
            //On affiche le rectangle de sélection/deselection autour des sommets
            for(int i =0; i<graphe.getOrdre();i++)
            {
                //Si le sommet est affiché
                if (graphe.getVectSom()[i].getAffSom()==true)
                {
                    //Si sélectionné -> rectangle vert, sinon noir
                    if(graphe.getVectSom()[i].getSelect()==true) rect(screen, graphe.getVectSom()[i].getCoordX(), graphe.getVectSom()[i].getCoordY(), graphe.getVectSom()[i].getCoordX()+ graphe.getVectSom()[i].getImage()->w, graphe.getVectSom()[i].getCoordY() + graphe.getVectSom()[i].getImage()->h, makecol(0,255,0));
                    else rect(screen, graphe.getVectSom()[i].getCoordX(), graphe.getVectSom()[i].getCoordY(), graphe.getVectSom()[i].getCoordX()+ graphe.getVectSom()[i].getImage()->w, graphe.getVectSom()[i].getCoordY()+graphe.getVectSom()[i].getImage()->h, makecol(0,0,0));
                }
            }

            //On affiche les sommets
            graphe.afficher_sommets(Buffer);

            //Forte connexité - couleurs
            if(f==1)
            {
                rest(2000);

                //Affichage
                blit(Buffer,screen,0,0,0,0,1024,768);
                blit(actuelle, Buffer, 0,0,0,0,1024,768);
                graphe.afficher_sommets(Buffer);

                //On retire les rectangles
                for(int i = 0; i<temp_x1.size(); i++)
                {
                    rest(500);
                    rectfill(actuelle, temp_x1[i], temp_y1[i],temp_x1[i]+temp_x2[i],temp_y1[i]+temp_y2[i],makecol(255,255,255));
                    blit(Buffer,screen,0,0,0,0,1024,768);
                    blit(actuelle, Buffer, 0,0,0,0,1024,768);
                    graphe.afficher_sommets(Buffer);
                }

                f++;
            }

            //Forte connexite - graphe réduit
            if (f==2)
            {
                //Instance de variables
                std::vector<Sommet> non_d;
                std::vector<Arc> non_vis;
                int nouv_o = 0;
                int nou_arc = 0;

                //Pour tous les sommets
                for(int i=0; i<graphe.getOrdre(); i++)
                {
                    //Si le sommet est affiché
                    if(graphe.getVectSom()[i].getAffSom() == true)
                    {
                        //On l'ajoute au vecteur de sommets
                        non_d.push_back(graphe.getVectSom()[i]);
                        //On incrémente le compteur correspondant au nombre de sommets affichés
                        nouv_o++;
                    }
                }

                //Pour tous les arcs
                for(int j = 0; j<graphe.getNbArcs();j++)
                {
                    //Si l'arc est affiché
                    if((graphe.getVectArcs()[j].getS1().getAffSom()==true) && (graphe.getVectArcs()[j].getS1().getAffSom()==true))
                    {
                        //On l'ajoute au vecteur d'arcs
                        non_vis.push_back(graphe.getVectArcs()[j]);
                        //On incrémente le compteur correspondant au nombre d'arcs affichés
                        nou_arc++;
                    }
                }

                //Si le compteur sommet est différent du nombre de sommet du graphe
                if(nouv_o != graphe.getOrdre())
                {
                    //Pour i allant de 0 à ce nombre
                    for(int i = 0; i<nouv_o; i++)
                    {
                        //On modifie le numéro des sommets du vecteur de sommets
                        non_d[i].setNumero(i);
                    }
                }

                //On modifie les attributs de ce graphe
                graphe_temp.setOrdre(nouv_o);
                graphe_temp.setNbMois(graphe.getNbMois());
                graphe_temp.setNbMoisTemp(graphe.getNbMoisTemp());
                graphe_temp.setNbArcs(nou_arc);
                graphe_temp.setVectArcs(non_vis);
                graphe_temp.setVectSom(non_d);

                //On lance la forte connexité sur ce graphe
                graphe_temp.forte_co(graphe_temp, actuelle, temp_x1, temp_y1, temp_x2, temp_y2,true);

                rest(2000);

                //Affichage
                blit(Buffer,screen,0,0,0,0,1024,768);
                blit(actuelle, Buffer, 0,0,0,0,1024,768);
                graphe.afficher_sommets(Buffer);

                //On retire les rectangles
                for(int i = 0; i<temp_x1.size(); i++)
                {
                    rest(500);
                    rectfill(actuelle, temp_x1[i], temp_y1[i],temp_x1[i]+temp_x2[i],temp_y1[i]+temp_y2[i],makecol(255,255,255));
                    rectfill(screen, 126, 5, 1019, 763, makecol(255,255,255));

                    //Affichage
                    blit(Buffer,screen,0,0,0,0,1024,768);
                    blit(actuelle, Buffer, 0,0,0,0,1024,768);
                    graphe.afficher_sommets(Buffer);
                }
                f=0;
            }
        }

        //Affichage
        blit(Buffer,screen,0,0,0,0,1024,768);
        blit(actuelle, Buffer, 0,0,0,0,1024,768);
    }

    //On sauvegarde le graphe
    graphe.sauvegarde_fichier(nom);

    return 0;

}
END_OF_MAIN();
