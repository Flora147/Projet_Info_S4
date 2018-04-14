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
        /*for(int i =0; i < getOrdre(); i++)
        {
            std::cout<<((getVectSom())[i]).getName()<<" "<<((getVectSom())[i]).getN()<<" "<<((getVectSom())[i]).getR()<<" "<<((getVectSom())[i]).getCoordX()<<" "<<((getVectSom())[i]).getCoordY()<<std::endl;
        }
        for(int i=0; i<getNbArcs(); i++)
        {

            std::cout<<"Arc "<<i+1<<" : "<<((getVectArcs())[i]).getS1())<< " et "<<(((getVectArcs())[i]).getS2())<<" coeff "<<((getVectArcs())[i]).getCoef()<<std::endl;
        }*/
    }
    else std::cout << "Erreur ouverture fichier chargement graphe kruskal" << std::endl;

}





/* select_sommet : sous-programme permettant de sélectionner les sommets (le prgm est précédé d'un mouse_b&1)
ENTREE :
    aucune
SORTIE :
    aucune
*/
void Graphe::select_sommet()
{

    //Pour tous les sommets
    for (int i=0; i<m_ordre; i++)
    {

       //Si le clic est sur l'image du sommet
        if (mouse_x>m_vect_som[i].getCoordX() && mouse_x<(m_vect_som[i].getCoordX()+m_vect_som[i].getImage()->w) && mouse_y>m_vect_som[i].getCoordY() && mouse_y<(m_vect_som[i].getCoordY()+m_vect_som[i].getImage()->h))
        {

            //Si le sommet n'est pas déjà sélectionné (--> SELECTION)
            if(! m_vect_som[i].getSelect())
            {
                //Le sommet est sélectionné
                m_vect_som[i].setSelect(true);

                //Il est entouré d'un carré vert
                rect(screen, m_vect_som[i].getCoordX(), m_vect_som[i].getCoordY(), m_vect_som[i].getCoordX()+m_vect_som[i].getImage()->w, m_vect_som[i].getCoordY()+m_vect_som[i].getImage()->h, makecol(0,255,0));

                //On affiche le sommet
                std::cout<<"*** INFORMATIONS DU SOMMET SELECTIONNE ***"<<std::endl;
                m_vect_som[i].afficher_infos();

                std::cout<<std::endl;

            }


            //Si le sommet est déjà sélectionné (--> DESELECTION)
            if(m_vect_som[i].getSelect())
            {
                //Le sommet est désélectionné
                m_vect_som[i].setSelect(false);

                //On efface le carré (on le met en blanc)
                rect(screen, m_vect_som[i].getCoordX(), m_vect_som[i].getCoordY(), m_vect_som[i].getCoordX()+m_vect_som[i].getImage()->w, m_vect_som[i].getCoordY()+m_vect_som[i].getImage()->h, makecol(0,0,0));

            }

        }

    }

}





/* effacer_sommet : sous-programme permettant d'effacer des sommets
ENTREE :
    aucune
SORTIE :
    aucune
*/
void Graphe::effacer_sommet()
{

    //Instance d'un compteur
    int compteur=0;


    //Pour tous les sommets
    for(int i=0; i<m_ordre; i++)
    {

        //Si le sommet est sélectionné
        if(m_vect_som[i].getSelect())
        {

            //On incrémente le compteur
            compteur++;

        }
    }


    //Si le compteur est différent de 0
    if(compteur != 0)
    {

        //Pour tous les sommets
        for(int i=0; i<m_ordre; i++)
        {

            //Si le sommet est sélectionné
            if(m_vect_som[i].getSelect())
            {

                //On met son affichage à nul
                m_vect_som[i].setAffSom(false);

            }
        }
    }

}




/* ajouter_sommet : sous-programme permettant d'ajouter un sommet au graphe
ENTREE :
    aucune
SORTIE :
    aucune
*/
void Graphe::ajouter_sommet()
{

    //Instance de compteurs et d'un int
    int compteur=0;
    int compteur1=0;
    int som;



    //Pour tous les sommets
    for(int i=0; i<m_ordre; i++)
    {

        //Si le sommet n'est pas affiché
        if(! m_vect_som[i].getAffSom())
        {

            //On affiche ses infos dans la console
            m_vect_som[i].afficher_infos();

            //On incrémente le compteur
            compteur++;
        }
    }


    //Si le compteur est différent de 0
    if(compteur != 0)
    {

        //Tant que le compteur 1 est nul
        while(compteur1==0)
        {

            //On demande à l'utilisateur quel sommet il souhaite ajouter
            std::cout<<"Quel sommet voulez-vous ajouter parmis ceux affiches ? (entrez le numero)"<<std::endl;
            std::cin>>som;


            //Pour tous les sommets
            for(int i=0; i<m_ordre; i++)
            {

                //Si le sommet n'est pas affiché
                if(! m_vect_som[i].getAffSom())
                {

                    //Si le sommet correspond à celui entré par l'utilisateur
                    if(i==som)
                    {

                        //On incrémente le compteur1
                        compteur1++;
                    }
                }
            }
        }


        //Le sommet saisi par l'utilisateur est affiché
        m_vect_som[som].setAffSom(true);

    }
}





/* recalcul_paramètres : sous-programme permettant le changement des paramètres N et K en temps réel
ENTREE :
    aucune
SORTIE :
    aucune
*/
void Graphe::recalcul_parametres()
{

    //Re-calcul de N
        //Instance d'un New_N
        int New_N;
        //Instance d'un vecteur d'arcs temporaires
        std::vector<Arc> vect_arcs_temp2;


        //Pour tous les sommets
        for(int j=0; j<m_ordre; j++)
        {

            //Pour tous les arcs
            for(int i=0; i<m_nb_arcs; i++)
            {

                //Si le numéro du premier sommet de l'arc correspond au numéro j
                if(m_vect_arcs[i].getS1().getNumero() == j)
                {

                    //On ajoute cet arc au vecteur temporaire
                    vect_arcs_temp2.push_back(m_vect_arcs[i]);
                }
            }


            //Pour tous les arcs du vecteur temporaire
            for (int i=0; i<vect_arcs_temp2.size(); i++)
            {

                //On calcule le nouveau N
                New_N = m_vect_som[j].getN() + m_vect_som[j].getR() * m_vect_som[j].getN() * (1 - (m_vect_som[j].getN() / m_vect_som[j].getK())) - vect_arcs_temp2[i].getCoef() * vect_arcs_temp2[i].getS2().getN();
                m_vect_som[j].setN(New_N);

                //Si N du sommet est inférieur ou égale à 0
                if(m_vect_som[j].getN() <= 0)
                {

                    //On l'égalise à zéro
                    m_vect_som[j].setN(0);

                    //On met l'affichage du sommet à faux
                    m_vect_som[j].setAffSom(false);
                }

            }

        }



    //Re-calcul de K
        //Instance d'un nouveau K
        int New_K;
        //Instance d'un vecteur d'arcs temporaire
        std::vector<Arc> vect_arcs_temp;


        //Pour tous les sommets
        for(int j=0; j<m_ordre; j++)
        {

            //Pour tous les arcs
            for(int i=0; i<m_nb_arcs; i++)
            {

                //Si le deuxième sommet de l'arc correspond au sommet j
                if(m_vect_arcs[i].getS2().getNumero() == j)
                {

                    //On ajoute cet arc au vecteur temporaire
                    vect_arcs_temp.push_back(m_vect_arcs[i]);
                }
            }

            //Pour tous les sommets du vecteur temporaire
            for (int i=0; i<vect_arcs_temp.size(); i++)
            {

                //On calcule le nouveau K
                New_K = m_vect_som[j].getK() + vect_arcs_temp[i].getCoef() * vect_arcs_temp[i].getS1().getN();
                m_vect_som[j].setK(New_K);
            }

        }

}
