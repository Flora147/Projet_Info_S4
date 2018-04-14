#include "Graphe.hpp"


//Constructeur surchargé
Graphe::Graphe(int _ordre, int_nb_arcs, std::vector<Sommet> _vect_som, std::vector<Arc> _vect_arcs)
    :m_ordre(_ordre), m_nb_arcs(_nb_arcs), m_vect_som(_vect_som), m_vect_arcs(_vect_arcs)
{

}



//Destructeur
Graphe::~Graphe()
{

}




//Accesseurs
//getters
//getter qui retourne l'attribut "m_ordre"
int Graphe::getOrdre()
{
    return m_ordre;
}

//getter qui retourne l'attribut "m_nb_arcs"
int Graphe::getNbArcs()
{
    return m_nb_arcs;
}

//getter qui retourne l'attribut "m_vect_som"
Sommet Graphe::getVectSom()
{
    return m_vect_som;
}

//getter qui retourne l'attribut "m_vect_arcs"
Arc Graphe::getVectArcs()
{
    return m_vect_arcs;
}


//setters
//getter qui modifie l'attribut "m_ordre"
void Graphe::setOrdre(int ordre)
{
    m_ordre=ordre;
}

//getter qui modifie l'attribut "m_nb_arcs"
void Graphe::setNbArcs(int nb_arcs)
{
    m_nb_arcs=nb_arcs;
}

//getter qui modifie l'attribut "m_vect_som"
void Graphe::setVectSom(std::vector<Sommet> vect_som)
{
    m_vect_som=vect_som;
}

//getter qui modifie l'attribut "m_vect_arcs"
void Graphe::setVectArcs(std::vector<Arcs> vect_arcs)
{
    m_vect_arcs=vect_arcs;
}
