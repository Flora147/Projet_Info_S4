#ifndef GRAPHE_HPP_INCLUDED
#define GRAPHE_HPP_INCLUDED
#include "Sommet.hpp"
#include "Arc.hpp"
#include <vector>
#include <stack>

class Graphe
{

    private :
        //Attributs
        int m_ordre;
        int m_nb_arcs;
        int m_nb_mois;
        int m_nb_mois_temp;
        std::vector<Sommet> m_vect_som;
        std::vector<Arc> m_vect_arcs;
        std::vector<int> c_regen;
        std::vector<int> c_famine;


    public :
        //Constructeur surchagé et destructeur
        Graphe();
        Graphe(int _ordre, int _nb_arcs, std::vector<Sommet> _vect_som, std::vector<Arc> _vect_arcs, int _nb_mois);
        ~Graphe();


        //Accesseurs
        //getters
        int getOrdre();
        int getNbArcs();
        int getNbMois();
        int getNbMoisTemp();
        std::vector<Sommet> getVectSom();
        std::vector<Arc> getVectArcs();

        //setters
        void setOrdre(int ordre);
        void setNbArcs(int nb_arcs);
        void setNbMois(int nb_mois);
        void setNbMoisTemp(int nb_mois_temp);
        void setVectSom(std::vector<Sommet> vect_som);
        void setVectArcs(std::vector<Arc> vect_arcs);

        //Sous-Programmes
        void lecture_fichier(std::string f);
        void sauvegarde_fichier(std::string f);
        void afficher_console();
        void afficher_sommets(BITMAP* img);
        void bouger_sommet(BITMAP* img, int x, int y, int n);
        void modifier_param();
        void calcul_para_post_modif(std::vector<Sommet> vec_som);
        void select_sommet(int mx, int my);
        void effacer_sommet(BITMAP* img);
        void ajouter_sommet();
        void recalcul_parametres();
        //void afficher_arcs(BITMAP* buffer);

        //FORTE CONNEXITE
        void DFS1(int s, bool marq[], std::stack<int> &pile);
        void DFS2(int s, bool marq[], int col, Graphe g,BITMAP* img, std::vector<int>& temp_x1, std::vector<int>& temp_y1, std::vector<int>& temp_x2, std::vector<int>& temp_y2);
        void forte_co(Graphe g,BITMAP* img, std::vector<int>& temp_x1, std::vector<int>& temp_y1, std::vector<int>& temp_x2, std::vector<int>& temp_y2);

        //TEMPS REEL
        void temps_reel(BITMAP* img, BITMAP* img2, int compt);
        void conservation_para();

        //K_CONNEXITE
        void k_connexite(BITMAP* buffer);
        void BFS(int sommet_initial);

};

#endif // GRAPHE_HPP_INCLUDED
