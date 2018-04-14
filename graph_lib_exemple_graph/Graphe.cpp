#include "Graphe.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>

using namespace std;

//Constructeur par défaut
Graphe::Graphe()
    :m_ordre(0), m_nb_arcs(0), m_vect_som(NULL), m_vect_arcs(NULL)
{

}
//Constructeur surchargé
Graphe::Graphe(int _ordre, int _nb_arcs, std::vector<Sommet> _vect_som, std::vector<Arc> _vect_arcs)
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
std::vector<Sommet> Graphe::getVectSom()
{
    return m_vect_som;
}

//getter qui retourne l'attribut "m_vect_arcs"
std::vector<Arc> Graphe::getVectArcs()
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
void Graphe::setVectArcs(std::vector<Arc> vect_arcs)
{
    m_vect_arcs=vect_arcs;
}

void Graphe::lecture_fichier(std::string f)
{
    ifstream fichier;
    fichier.open(f);

    if(fichier)
    {
        BITMAP* Menu = load_bitmap("Menu.bmp",NULL);
        if (!Menu)
        {
            allegro_message("prb allocation BITMAP menu");
            allegro_exit();
            exit(EXIT_FAILURE);
        }

        int ordre, nb_arcs;
        std::vector<Sommet> vec_som;
        std::vector<Arc> vec_arc;

        fichier >> ordre;
        setOrdre(ordre);
        for(int i = 0; i<getOrdre(); i++)
        {
            int num, n, k, x, y;
            float r;
            std::string nom;

            k = 0;
            fichier>>nom;
            fichier>>num;
            fichier>>n;
            fichier>>r;
            fichier>>x;
            fichier>>y;

            Sommet s(nom, num, n,k, r, x, y, Menu, true, false);
            vec_som.push_back(s);
        }
        fichier >> nb_arcs;
        setNbArcs(nb_arcs);
        for(int i=0; i<getNbArcs(); i++)
        {
            int s1, s2;
            float coeff;

            fichier >> s1;
            fichier >> s2;

            coeff = (vec_som[s1].getN())/(vec_som[s2].getN());
            Arc a(vec_som[s1], vec_som[s2], coeff, true);
            vec_arc.push_back(a);
        }

        setVectSom(vec_som);
        setVectArcs(vec_arc);

        fichier.close();
        std::cout<<"Graphe :"<<std::endl;
        std::cout<<"\n\nOrdre : "<<getOrdre()<<std::endl;
        std::cout<<"\n\nNB Arcs : "<<getNbArcs()<<std::endl;
        for(int i =0; i < getOrdre(); i++)
        {
            std::cout<<((getVectSom())[i]).getName()<<" "<<((getVectSom())[i]).getN()<<" "<<((getVectSom())[i]).getR()<<" "<<((getVectSom())[i]).getCoordX()<<" "<<((getVectSom())[i]).getCoordY()<<std::endl;
        }
        for(int i=0; i<getNbArcs(); i++)
        {

            std::cout<<"Arc "<<i+1<<" : "<<((getVectArcs())[i]).getS1())<< " et "<<(((getVectArcs())[i]).getS2())<<" coeff "<<((getVectArcs())[i]).getCoef()<<std::endl;
        }
    }
    else std::cout << "Erreur ouverture fichier chargement graphe kruskal" << std::endl;

}
