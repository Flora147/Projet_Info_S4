#ifndef GRAPHE_HPP_INCLUDED
#define GRAPHE_HPP_INCLUDED
#include "Sommet.hpp"
#include "Arc.hpp"
#include <vector>


class Graphe
{

    private :
        //Attributs
        int m_ordre;
        int m_nb_arcs;
        std::vector<Sommet> m_vect_som;
        std::vector<Arc> m_vect_arcs;


    public :
        //Constructeur surchagé et destructeur
        Graphe(int _ordre, int _nb_arcs, std::vector<Sommet> _vect_som, std::vector<Arc> _vect_arcs);
        ~Graphe();


        //Accesseurs
        //getters
        int getOrdre();
        int getNbArcs();
        Sommet getVectSom();
        Arc getVectArcs();

        //setters
        void setOrdre(int ordre);
        void setNbArcs(int nb_arcs);
        void setVectSom(std::vector<Sommet> vect_som);
        void setVectArcs(std::vector<Arcs> vect_arcs);


};

#endif // GRAPHE_HPP_INCLUDED
