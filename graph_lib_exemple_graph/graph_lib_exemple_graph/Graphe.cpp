#include "Graphe.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>

using namespace std;


//Constructeur par défaut
Graphe::Graphe()
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




/* lecture_fichier : sous-programme permettant de lire le fichier et d'instancier les attributs des classes
ENTREE :
    f : de type std::string
SORTIE
    aucune
*/
void Graphe::lecture_fichier(std::string f)
{

    //Fichier
    ifstream fichier;
    fichier.open(f);

    //Instance des variables nécessaires à la lecture du fichier
    BITMAP* image;
    int ordre, nb_arcs;
    int num, n, x, y;
    int s1, s2;
    bool b1, b2;
    float coeff;
    float r;
    std::string nom, nom_img;
    std::vector<Sommet> vec_som;
    std::vector<Arc> vec_arc;


    //Si le fichier est ouvert
    if(fichier)
    {

        //On lit l'ordre
        fichier >> ordre;
        setOrdre(ordre);

        //Pour i allant de 0 au nombre de sommets du graphe
        for(int i = 0; i<getOrdre(); i++)
        {

            //Sur une même ligne on lit le nom, le numéro, le N, le r, les coordonnées d'un sommet
            // et 2 booléens indiquant la sélection et l'affichage
            fichier>>nom;
            fichier>>num;
            fichier>>n;
            fichier>>r;
            fichier>>x;
            fichier>>y;
            fichier>>b1;
            fichier>>b2;

            //Instance du nom de l'image
            nom_img = nom + ".bmp";
            image = load_bitmap(nom_img.c_str(),NULL);

            //Si l'image ne se charge pas
            if (!image)
            {
                //Message d'erreur
                allegro_message("prb allocation BITMAP ");
                allegro_exit();
                exit(EXIT_FAILURE);
            }

            //On crée le sommet et on l'ajoute au vecteur de sommet
            Sommet s(nom, num, n, 0, r, x, y, image, b1, b2);
            vec_som.push_back(s);
        }


        //On lit le nombre d'arcs
        fichier>>nb_arcs;
        setNbArcs(nb_arcs);

        //Pour i allant de 0 au nombre d'arcs du graphe
        for(int j=0; j<getNbArcs(); j++)
        {

            //on lit le numéro des deux sommets de l'arc
            fichier >> s1;
            fichier >> s2;

            //On calcule le coefficient de l'arc que l'on crée ensuite
            coeff = (float)(vec_som[s1].getN())/(vec_som[s2].getN());
            Arc a(vec_som[s1], vec_som[s2], coeff, true);

            //On peut à présent calculer le K des sommets du graphe
            vec_som[s2].setK(vec_som[s2].getK() + vec_som[s1].getN()*coeff);

            //on entre tous les arcs dans un vecteur d'arcs
            vec_arc.push_back(a);

        }


        //On remplit les vecteurs du graphe avec ceux créés juste au-dessus
        setVectSom(vec_som);
        setVectArcs(vec_arc);


        //On affiche en console le graphe
        std::cout<<std::endl<<std::endl<<"*** GRAPHE ***"<<std::endl;
        std::cout<<std::endl<<"Ordre : "<<getOrdre()<<std::endl;
        std::cout<<"NB Arcs : "<<getNbArcs()<<std::endl<<std::endl;


        //Pour tous les sommets du graphe
        for(int i =0; i < getOrdre(); i++)
        {

            //Si le K du sommet est inférieur ou égale à 0
            if(vec_som[i].getK()<=0)
            {

                //Il vaut désormais 1000
                vec_som[i].setK(1000);
                setVectSom(vec_som);
            }

            //Affichage des informations de chaque sommet pour vérifier si la lecture du fichier est bonne
            std::cout<<((getVectSom())[i]).getName()<<" "<<((getVectSom())[i]).getN()<<" "<<((getVectSom())[i]).getK()<<" "<<((getVectSom())[i]).getR()<<" "<<((getVectSom())[i]).getCoordX()<<" "<<((getVectSom())[i]).getCoordY()<<std::endl;
        }

        std::cout<<std::endl<<std::endl;


        //Pour tous les arcs du graphe
        for(int i=0; i<getNbArcs(); i++)
        {

            //Affichage des informations de l'arc pour vérifier la bonne lecture du fichier
            std::cout<<"Arc "<<(i+1)<<" : "<<((getVectArcs())[i]).getS1().getNumero()<< " et "<<((getVectArcs())[i]).getS2().getNumero()<<" ; coeff "<<((getVectArcs())[i]).getCoef()<<std::endl;
        }

        //Fermeture du fichier
        fichier.close();

    }

    //Sinon, message d'erreur d'ouverture du fichier
    else std::cout << "Erreur ouverture fichier chargement graphe " << std::endl;

}





/* sauvegarde_ficher : sous-programme permettant de sauvegarder le graphe actuel dans un fichier
ENTREE :
    f : de type std::string
SORTIE
    aucune
*/
void Graphe::sauvegarde_fichier(std::string f)
{

    //On affiche les infos du graphe sur la console pour vérifier si la sauvegarde fonctionne
    afficher_console();

    //Fichier
    ofstream fichier;
    fichier.open(f);

    //Instance de 2 booléens
    bool b1, b2;


    //Si le fichier est ouvert
    if(fichier)
    {

        //On écrit l'ordre du graphe dans le fichier
        fichier << getOrdre() << std::endl;

        //Pour tous les sommets du graphe
        for(int i =0; i<getOrdre(); i++)
        {

            //Si le sommet est affiché, b1 vaut 1
            if((getVectSom()[i]).getAffSom() == 1) b1=1;
            //Sinon 0
            else b1=0;

            //Si le sommet est sélectionné, b2 vaut 1
            if((getVectSom()[i]).getSelect() == 1) b2=1;
            //Sinon 0
            else b2=0;

            //On écrit dans le fichier les informations du sommet
            fichier << ((getVectSom())[i]).getName();
            fichier << " ";
            fichier << (getVectSom()[i]).getNumero();
            fichier << " ";
            fichier << ((getVectSom())[i]).getN();
            fichier << " ";
            fichier << (getVectSom()[i]).getR();
            fichier << " ";
            fichier << (getVectSom()[i]).getCoordX();
            fichier << " ";
            fichier << (getVectSom()[i]).getCoordY();
            fichier << " ";
            fichier << b1;
            fichier << " ";
            fichier << b2;
            fichier << std::endl;
        }


        //On écrit le nombre d'arcs du graphe dans le fichier
        fichier<<getNbArcs()<<std::endl;

        //Pour tous les arcs du graphes
        for(int i = 0; i<getNbArcs(); i++)
        {

            //On écrit dans le fichier son sommet 1 et son sommet 2
            fichier << (getVectArcs()[i]).getS1().getNumero();
            fichier << " ";
            fichier << (getVectArcs()[i]).getS2().getNumero();
            fichier << std::endl;
        }

        //On ferme le fichier
        fichier.close();

    }

    ////Sinon, message d'erreur d'ouverture du fichier
    else std::cout << "Erreur fichier sauvegarde..." << std::endl << std::endl;

}





/* modifier_param : sous-programme permettant de choisir un sommet et d'en modifier un paramètre
ENTREE :
    aucune
SORTIE :
    aucune
*/
void Graphe::modifier_param()
{

    //Instance de données
    std::string choix, nouv_nom;
    int som, nouv;
    std::vector<Sommet> vec_som;


    //Saisie du sommet à modifier
    std::cout<<"Quel sommet souhaitez-vous modifier ? (numero) "<<std::endl;
    std::cin>>som;

    //Blindage
    //Tant que le numéro saisi n'existe pas
    while(som<0 || som>getVectSom().size())
    {

        //Message d'erreur et demande de re-saisie
        std::cout<<"Mauvaise saisie du sommet a modifier. Veuillez recommencer. (numero)"<<std::endl;
        std::cin>>som;
    }


    //Saisie du paramètre à changer
    std::cout<<"Lequel de ces parametres souhaitez-vous modifier ?(K, R ou N)"<<std::endl;
    std::cin>>choix;

    //Blindage
    //Tant que le choix saisi est différent de K, R ou N
    while(choix!= "K" && choix!="R" && choix!="N")
    {
        //Message d'erreur et demande de re-saisie
        std::cout<<"Mauvaise saisie du choix. Veuillez recommencer. (K, R ou N)"<<std::endl;
        std::cin>>choix;
    }


    //Si on choisit de modifier K
    if(choix=="K")
    {

        //Choix du nouveau K
        std::cout<<"K actuel pour "<<(getVectSom()[som]).getName()<<" : "<<(getVectSom()[som]).getK()<<std::endl;
        std::cout<<"Saisir nouveau K : ";
        std::cin>>nouv;

        //On crée un sommet avec les mêmes propriétés que celui à modifier sauf K qui a été actualisé
        Sommet s((getVectSom()[som]).getName(), (getVectSom()[som]).getNumero(), (getVectSom()[som]).getN(), nouv, (getVectSom()[som]).getR(), (getVectSom()[som]).getCoordX(), (getVectSom()[som]).getCoordY(), (getVectSom()[som]).getImage(), (getVectSom()[som]).getAffSom(), (getVectSom()[som]).getSelect());

        //Pour tous les sommets du graphe
        for(int i=0; i<getOrdre(); i++)
        {
            //On modifie le vecteur de sommets
            if (i==som) vec_som.push_back(s);
            else vec_som.push_back(getVectSom()[i]);
        }
    }


    //Si on choisit de modifier N
    if(choix=="N")
    {

        //Choix du nouveau N
        std::cout<<"N actuel pour "<<(getVectSom()[som]).getName()<<" : "<<(getVectSom()[som]).getN()<<std::endl;
        std::cout<<"Saisir nouveau N";
        std::cin>>nouv;

        //On crée un sommet avec les mêmes propriétés que celui à modifier sauf N qui a été actualisé
        Sommet s((getVectSom()[som]).getName(), (getVectSom()[som]).getNumero(), nouv, (getVectSom()[som]).getK(), (getVectSom()[som]).getR(), (getVectSom()[som]).getCoordX(), (getVectSom()[som]).getCoordY(), (getVectSom()[som]).getImage(), (getVectSom()[som]).getAffSom(), (getVectSom()[som]).getSelect());

        //Pour tous les sommets du graphe
        for(int i=0; i<getOrdre(); i++)
        {
            //On modifie le vecteur de sommets
            if (i==som) vec_som.push_back(s);
            else vec_som.push_back(getVectSom()[i]);
        }

        //Appel du sous-programme suivant pour modifier K et R dépendants de N
        calcul_para_post_modif(vec_som);

    }

    //Si on choisit de modifier R
    if(choix=="R")
    {

        //Choix du nouveau R
        std::cout<<"R actuel pour "<<(getVectSom()[som]).getName()<<" : "<<(getVectSom()[som]).getR()<<std::endl;
        std::cout<<"Saisir nouveau R";
        std::cin>>nouv;

        //On crée un sommet avec les mêmes propriétés que celui à modifier sauf R qui a été actualisé
        Sommet s((getVectSom()[som]).getName(), (getVectSom()[som]).getNumero(), (getVectSom()[som]).getN(), (getVectSom()[som]).getK(), nouv, (getVectSom()[som]).getCoordX(), (getVectSom()[som]).getCoordY(), (getVectSom()[som]).getImage(), (getVectSom()[som]).getAffSom(), (getVectSom()[som]).getSelect());

        //Pour tous les sommets du graphe
        for(int i=0; i<getOrdre(); i++)
        {
            //On modifie le vecteur de sommets
            if (i==som) vec_som.push_back(s);
            else vec_som.push_back(getVectSom()[i]);
        }

    }


    //On modifie le vecteur de sommets du graphe avec les changements apportés
    setVectSom(vec_som);

    //On affiche les infos du graphe sur la console pour voir les modifications
    afficher_console();

}






/* calcul_para_post_modif : sous-programme permettant de modifier le coefficient et le K des sommets après avoir modifié leur N
ENTREE :
    vec_som : de type vecteur de sommets
SORTIE :
    aucune
*/
void Graphe::calcul_para_post_modif(std::vector<Sommet> vec_som)
{

    //Instance de données
    float coeff;
    std::vector<Arc> vec_arc;
    vec_arc = getVectArcs();
    int s1, s2;


    //Pour tous les arcs du graphe
    for(int i =0; i<getNbArcs(); i++)
    {

        //Instance des 2 sommets formant l'arc
        s1 = getVectArcs()[i].getS1().getNumero();
        s2 = getVectArcs()[i].getS2().getNumero();

        //On calcule le nouveau coefficient de l'arc
        coeff = (float)(vec_som[s1].getN())/(vec_som[s2].getN());

        //On peut à présent calculer le K du 2ème sommet de l'arc
        vec_som[s2].setK(vec_som[s2].getK() + vec_som[s1].getN()*coeff);
        vec_arc[i].setCoef(coeff);
    }


    //On modifie les vecteurs de sommets et d'arcs du graphe avec les changements apportés
    setVectArcs(vec_arc);
    setVectSom(vec_som);
}





/* afficher console : sous-programme permettant d'afficher les infos du graphe en console
ENTREE :
    aucune
SORTIE :
    aucune
*/
void Graphe::afficher_console()
{

    //Affichage des infos principales du graphe
    std::cout<<std::endl<<std::endl<<"*** GRAPHE ***"<<std::endl;
    std::cout<<std::endl<<"Ordre : "<<getOrdre()<<std::endl;
    std::cout<<"NB Arcs : "<<getNbArcs()<<std::endl<<std::endl;


    //Pour tous les sommets du graphe
    for(int i =0; i < getOrdre(); i++)
    {
        //Affichage des informations du sommet
        std::cout<<((getVectSom())[i]).getName()<<" "<<((getVectSom())[i]).getN()<<" "<<((getVectSom())[i]).getK()<<" "<<((getVectSom())[i]).getR()<<" "<<((getVectSom())[i]).getCoordX()<<" "<<((getVectSom())[i]).getCoordY()<<std::endl;
    }


    std::cout<<std::endl<<std::endl;


    //Pour tous les arcs du graphe
    for(int i=0; i<getNbArcs(); i++)
    {
        //Affichage des informations de l'arc
        std::cout<<"Arc "<<(i+1)<<" : "<<((getVectArcs())[i]).getS1().getNumero()<< " et "<<((getVectArcs())[i]).getS2().getNumero()<<" ; coeff "<<((getVectArcs())[i]).getCoef()<<std::endl;
    }

}





/* afficher_sommets : sous-programme permettant d'afficher à l'écran les sommets du graphe
ENTREE :
    img : de type BITMAP*
SORTIE :
    aucune
*/
void Graphe::afficher_sommets(BITMAP* img)
{

    //Instance d'un int
    int n;

    //Instance d'un vecteur de int
    std::vector<int>compteur;

    //Initialisation du vecteur à 0
    for(int i=0; i<m_nb_arcs; i++)
    {
        compteur.push_back(0);
    }


    //Pour tous les sommets du graphe
    for(int i=0; i<getOrdre(); i++)
    {

        //Si le sommet est affiché
        if(getVectSom()[i].getAffSom())
        {

            //Pour tous les arcs
            for(int j=0; j<m_nb_arcs; j++)
            {

                //Si le sommet i est égale au sommet 1 de l'arc
                if(i == m_vect_arcs[j].getS1().getNumero())
                {
                    compteur[j] = compteur[j] + 1;
                }

                //Si le sommet i est égale au sommet 2 de l'arc
                else if(i == m_vect_arcs[j].getS2().getNumero())
                {
                    compteur[j] = compteur[j] + 1;
                }
            }

            //Pour tous les arcs
            for(int j=0; j<m_nb_arcs; j++)
            {

                //Si le compteur de cet arc vaut 2
                if(compteur[j] == 2)
                {
                    //Alors il est affiché
                    m_vect_arcs[j].setAffArc(true);
                }

            }


            //On affiche sa BITMAP
            draw_sprite(img, (getVectSom()[i]).getImage(), (getVectSom()[i]).getCoordX(), (getVectSom()[i]).getCoordY());

            //n prend la valeur du numéro du sommet
            n = (getVectSom()[i]).getNumero();

            //On affiche le numéro du sommet au-dessus de son image
            textprintf(img,font, (getVectSom()[i]).getCoordX()+20, (getVectSom()[i]).getCoordY()-20, makecol(0,0,0), "Sommet n_%d", n);

            //Affichage d'un rectangle autour de l'image du sommet
            //Si le sommet est sélectionné
            if(getVectSom()[i].getSelect()) rect(screen, getVectSom()[i].getCoordX(), getVectSom()[i].getCoordY(), getVectSom()[i].getCoordX()+ getVectSom()[i].getImage()->w, getVectSom()[i].getCoordY()+getVectSom()[i].getImage()->h, makecol(0,255,0));
            //Sinon
            else rect(screen, getVectSom()[i].getCoordX(), getVectSom()[i].getCoordY(), getVectSom()[i].getCoordX()+ getVectSom()[i].getImage()->w, getVectSom()[i].getCoordY()+getVectSom()[i].getImage()->h, makecol(0,0,0));

        }

    }

}





/* bouger_sommet : sous-programme permettant de bouger un sommet de place
ENTREE :
    img : de type BITMAP*
    x : de type int
    y : de type int
    n : de type int
SORTIE :
    aucune
*/
void Graphe::bouger_sommet(BITMAP *img, int x, int y, int n)
{

    //Instance de 2 booléens
    bool test = false;
    bool multiple = false;


    //On crée un sommet correspondant au sommet que l'on souhaite bouger mais avec les nouvelles coordonnées
    Sommet s = (getVectSom()[n]);
    s.setCoordX(x);
    s.setCoordY(y);

    // On crée un vecteur de sommets
    std::vector<Sommet> vec_som;


    //Si plusieurs sommets sont sélectionnés
    if(getVectSom()[n].getSelect() == true) multiple = true;

    //Pour tous les sommets du graphe
    for(int i=0; i<getOrdre(); i++)
    {
        //Si plusieurs sommets sont sélectionnés alors le premier dans l'ordre des numéros est sélectionné et les autres sont désélectionnés
        if(multiple==true) m_vect_som[i].setSelect(0);

        //On affiche les sommets
        afficher_sommets(img);
    }



    //On regarde pour tous les sommets que la nouvelle position du sommet n'empiètera pas sur leur image
    //Pour tous les sommets
    for(int i=0; i<getOrdre(); i++)
    {

        //Si le sommet est différent de celui sélectionné
        if(i!=n)
        {

            if((x>getVectSom()[i].getCoordX()-getVectSom()[i].getImage()->w) && (x<getVectSom()[i].getCoordX()+ getVectSom()[i].getImage()->w))
            {

                if((y>getVectSom()[i].getCoordY() -getVectSom()[i].getImage()->h)&& (y<getVectSom()[i].getCoordY() + getVectSom()[i].getImage()->h))
                {
                    test = true;
                    s.setCoordX(getVectSom()[n].getCoordX());
                    s.setCoordY(getVectSom()[n].getCoordY());
                    i =getOrdre();
                }
            }

            else if (x<125)
            {
                test ==true;
                s.setCoordX(getVectSom()[n].getCoordX());
                s.setCoordY(getVectSom()[n].getCoordY());
                i =getOrdre();
            }
        }
    }


    //On remplit le vecteur de sommets de la fonction avec les sommets du graphe selon les modifications faites
    for(int i=0; i<getOrdre(); i++)
    {
        if (i==n) vec_som.push_back(s);
        else vec_som.push_back(getVectSom()[i]);
    }

    //On donne au vecteur de sommets du graphe les valeurs du vecteur de sommets de la fonction
    setVectSom(vec_som);

    //On affiche les sommets
    afficher_sommets(img);
}






/* select_sommet : sous-programme permettant de sélectionner les sommets (le prgm est précédé d'un mouse_b&1)
ENTREE :
    aucune
SORTIE :
    aucune
*/
void Graphe::select_sommet(int mx, int my)
{

    //Pour tous les sommets
    for (int i=0; i<m_ordre; i++)
    {

       //Si le clic est sur l'image du sommet
        if (mx>m_vect_som[i].getCoordX() && mx<(m_vect_som[i].getCoordX()+m_vect_som[i].getImage()->w) && my>m_vect_som[i].getCoordY() && my<(m_vect_som[i].getCoordY()+m_vect_som[i].getImage()->h))
        {

            //Si le sommet n'est pas déjà sélectionné (--> SELECTION)
            if(! m_vect_som[i].getSelect())
            {
                //Le sommet est sélectionné
                m_vect_som[i].setSelect(true);

                //Il est encadré d'un carré vert
                rect(screen, m_vect_som[i].getCoordX(), m_vect_som[i].getCoordY(), m_vect_som[i].getCoordX()+m_vect_som[i].getImage()->w, m_vect_som[i].getCoordY()+m_vect_som[i].getImage()->h, makecol(0,255,0));

                //On affiche les informations du sommet
                std::cout<<"*** INFORMATIONS DU SOMMET SELECTIONNE ***"<<std::endl;
                m_vect_som[i].afficher_infos();

                std::cout<<std::endl;

            }


            //Si le sommet est déjà sélectionné (--> DESELECTION)
            else if(m_vect_som[i].getSelect())
            {
                //Le sommet est désélectionné
                m_vect_som[i].setSelect(false);

                //Il est encadré d'un carré noir
                rect(screen, m_vect_som[i].getCoordX(), m_vect_som[i].getCoordY(), m_vect_som[i].getCoordX()+m_vect_som[i].getImage()->w, m_vect_som[i].getCoordY()+m_vect_som[i].getImage()->h, makecol(0,0,0));
            }

        }

    }

}





/* effacer_sommet : sous-programme permettant d'effacer un ou plusieurs sommets
ENTREE :
    aucune
SORTIE :
    aucune
*/
void Graphe::effacer_sommet(BITMAP* img)
{

    //Instance d'un vecteur de sommets
    std::vector<Sommet> vec_som = getVectSom();

    //Instance d'un compteur
    int compteur=0;


    //Pour tous les sommets
    for(int i=0; i<m_ordre; i++)
    {

        //Si le sommet est sélectionné
        if(vec_som[i].getSelect())
        {
            //On incrémente le compteur
            compteur++;
        }
    }


    //Si le compteur est différent de 0
    if(compteur != 0)
    {

        //Pour tous les sommets
        for(int i=0; i<getOrdre(); i++)
        {

            //Si le sommet est sélectionné
            if(vec_som[i].getSelect())
            {

                //On met son affichage et sa sélection à faux
                vec_som[i].setAffSom(false);
                vec_som[i].setSelect(false);
            }
        }
    }


    //Instance d'un vecteur d'Arcs
    std::vector<Arc> vec_arc = getVectArcs();

    //Pour tous les arcs
    for(int i=0; i<getNbArcs(); i++)
    {
        //Si le sommet 1 et /ou le sommet 2 de l'arc n'est pas affiché alors l'arc n'est pas affiché
        if(!(vec_som[vec_arc[i].getS1().getNumero()].getAffSom()) || !(vec_som[vec_arc[i].getS2().getNumero()].getAffSom())) vec_arc[i].setAffArc(false);

        //Si le sommet 2 de l'arc n'est pas affiché alors l'arc n'est pas affiché
        //if() vec_arc[i].setAffArc(false);
    }


    //Modifications des vecteurs de sommets et d'arcs du graphe
    setVectSom(vec_som);
    setVectArcs(vec_arc);

    //Affichage des sommets
    afficher_sommets(img);

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
            std::cout<<"Quel sommet voulez-vous ajouter parmis ceux affiches ci dessous ? (numero)"<<std::endl;
            for(int i=0; i<getOrdre(); i++)
            {
                if(m_vect_som[i].getAffSom()==false) std::cout<<m_vect_som[i].getName()<<" : numero "<<m_vect_som[i].getNumero()<<std::endl;
            }
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

    std::vector<Arc> vec_arc = getVectArcs();
    for(int i=0; i<getNbArcs(); i++)
    {
        if(m_vect_som[vec_arc[i].getS1().getNumero()].getAffSom() == true) vec_arc[i].setAffArc(true);
        else if(m_vect_som[vec_arc[i].getS2().getNumero()].getAffSom() == true) vec_arc[i].setAffArc(true);
        else vec_arc[i].setAffArc(false);
    }
    setVectArcs(vec_arc);

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






/* afficher_arcs : sous-programme permettant d'afficher les arcs à afficher entre 2 sommets
ENTREE :
    buffer : de type BITMAP*
SORTIE :
    aucune
*/
/*
void Graphe::afficher_arcs(BITMAP* buffer)
{
    //Variables temporaires
    int X2, X3, Y2, Y3;


    //Pour tous les arcs du vecteur d'arcs
    for(int i=0; i<m_nb_arcs; i++)
    {

        //SI LE BOOLEEN AFFICHER DE l'ARC EST A VRAI
        if(m_vect_arcs[i].getAffArc())
        {

            //Instance d'une variable coeff
            float coeff = m_vect_arcs[i].getCoef();

            //INITIALISATION
            m_vect_arcs[i].setArrowX1(m_vect_arcs[i].getS2().getCoordX());
            m_vect_arcs[i].setArrowY1(m_vect_arcs[i].getS2().getCoordY());

            X2 = m_vect_arcs[i].getArrowX1() - 10;
            Y2 = m_vect_arcs[i].getArrowY1() - 10;

            X3 = m_vect_arcs[i].getArrowX1() - 10;
            Y3 = m_vect_arcs[i].getArrowY1() + 10;


            //AJUSTEMENT
            //TRACE DE LA FLECHE ET MODIFICATION DE LA LIGNE
            //CAS 1
            if(m_vect_arcs[i].getArrowX1() > m_vect_arcs[i].getS1().getCoordX() && m_vect_arcs[i].getArrowY1() > m_vect_arcs[i].getS1().getCoordY())
            {

                m_vect_arcs[i].setArrowX1(m_vect_arcs[i].getS2().getCoordX() + (m_vect_arcs[i].getS2().getImage()->w)/2);
                m_vect_arcs[i].setArrowY1(m_vect_arcs[i].getS2().getCoordY() - 25);

                m_vect_arcs[i].setLine_S1_X(m_vect_arcs[i].getS1().getCoordX() + (m_vect_arcs[i].getS1().getImage()->w)/2);
                m_vect_arcs[i].setLine_S1_Y(m_vect_arcs[i].getS1().getCoordY() + (m_vect_arcs[i].getS1().getImage()->h));

                X2 = m_vect_arcs[i].getArrowX1() - 10;
                Y2 = m_vect_arcs[i].getArrowY1() - 20;

                X3 = m_vect_arcs[i].getArrowX1() - 20;
                Y3 = m_vect_arcs[i].getArrowY1() - 10;

            }



            //CAS 2
            else if(m_vect_arcs[i].getArrowX1() < m_vect_arcs[i].getS1().getCoordX() && m_vect_arcs[i].getArrowY1() < m_vect_arcs[i].getS1().getCoordY())
            {

                m_vect_arcs[i].setArrowX1(m_vect_arcs[i].getS2().getCoordX() + (m_vect_arcs[i].getS2().getImage()->w)/2);
                m_vect_arcs[i].setArrowY1(m_vect_arcs[i].getS2().getCoordY() + (m_vect_arcs[i].getS2().getImage()->h));

                X2 = m_vect_arcs[i].getArrowX1() + 10;
                Y2 = m_vect_arcs[i].getArrowY1() + 20;

                X3 = m_vect_arcs[i].getArrowX1() + 20;
                Y3 = m_vect_arcs[i].getArrowY1() + 10;

                m_vect_arcs[i].setLine_S1_X(m_vect_arcs[i].getS1().getCoordX() + (m_vect_arcs[i].getS1().getImage()->w)/2);
                m_vect_arcs[i].setLine_S1_Y(m_vect_arcs[i].getS1().getCoordY() - 25);

            }



            //CAS 3
            else if(m_vect_arcs[i].getArrowX1() < m_vect_arcs[i].getS1().getCoordX() && m_vect_arcs[i].getArrowY1() > m_vect_arcs[i].getS1().getCoordY())
            {

                m_vect_arcs[i].setArrowX1(m_vect_arcs[i].getS2().getCoordX() + (m_vect_arcs[i].getS2().getImage()->w)/2);
                m_vect_arcs[i].setArrowY1(m_vect_arcs[i].getS2().getCoordY() - 25);

                X2 = m_vect_arcs[i].getArrowX1() + 20;
                Y2 = m_vect_arcs[i].getArrowY1() - 10;

                X3 = m_vect_arcs[i].getArrowX1() + 10;
                Y3 = m_vect_arcs[i].getArrowY1() - 20;

                m_vect_arcs[i].setLine_S1_X(m_vect_arcs[i].getS1().getCoordX() + (m_vect_arcs[i].getS1().getImage()->w)/2);
                m_vect_arcs[i].setLine_S1_Y(m_vect_arcs[i].getS1().getCoordY() + (m_vect_arcs[i].getS1().getImage()->h));

            }


            //CAS 4
            else if(m_vect_arcs[i].getArrowX1() > m_vect_arcs[i].getS1().getCoordX() && m_vect_arcs[i].getArrowY1() < m_vect_arcs[i].getS1().getCoordY())
            {

                m_vect_arcs[i].setArrowX1(m_vect_arcs[i].getS2().getCoordX() + (m_vect_arcs[i].getS2().getImage()->w)/2);
                m_vect_arcs[i].setArrowY1(m_vect_arcs[i].getS2().getCoordY() + (m_vect_arcs[i].getS2().getImage()->h));

                X2 = m_vect_arcs[i].getArrowX1() - 20;
                Y2 = m_vect_arcs[i].getArrowY1() + 10;

                X3 = m_vect_arcs[i].getArrowX1() - 10;
                Y3 = m_vect_arcs[i].getArrowY1() + 20;

                m_vect_arcs[i].setLine_S1_X(m_vect_arcs[i].getS1().getCoordX() + (m_vect_arcs[i].getS1().getImage()->w)/2);
                m_vect_arcs[i].setLine_S1_Y(m_vect_arcs[i].getS1().getCoordY() - 25);

            }



            //CAS 5
            else if(m_vect_arcs[i].getArrowX1() == m_vect_arcs[i].getS1().getCoordX() && m_vect_arcs[i].getArrowY1() > m_vect_arcs[i].getS1().getCoordY())
            {

                m_vect_arcs[i].setArrowX1(m_vect_arcs[i].getS2().getCoordX() + (m_vect_arcs[i].getS2().getImage()->w)/2);
                m_vect_arcs[i].setArrowY1(m_vect_arcs[i].getS2().getCoordY() - 25);

                X2 = m_vect_arcs[i].getArrowX1() + 10;
                Y2 = m_vect_arcs[i].getArrowY1() - 10;

                X3 = m_vect_arcs[i].getArrowX1() - 10;
                Y3 = m_vect_arcs[i].getArrowY1() - 10;

                m_vect_arcs[i].setLine_S1_X(m_vect_arcs[i].getS1().getCoordX() + (m_vect_arcs[i].getS1().getImage()->w)/2);
                m_vect_arcs[i].setLine_S1_Y(m_vect_arcs[i].getS1().getCoordY() + (m_vect_arcs[i].getS1().getImage()->h));

            }


            //CAS 6
            else if(m_vect_arcs[i].getArrowX1() > m_vect_arcs[i].getS1().getCoordX() && m_vect_arcs[i].getArrowY1() == m_vect_arcs[i].getS1().getCoordY())
            {

                m_vect_arcs[i].setArrowX1(m_vect_arcs[i].getS2().getCoordX());
                m_vect_arcs[i].setArrowY1(m_vect_arcs[i].getS2().getCoordY() + (m_vect_arcs[i].getS2().getImage()->h)/2);

                X2 = m_vect_arcs[i].getArrowX1() - 10;
                Y2 = m_vect_arcs[i].getArrowY1() - 10;

                X3 = m_vect_arcs[i].getArrowX1() - 10;
                Y3 = m_vect_arcs[i].getArrowY1() + 10;

                m_vect_arcs[i].setLine_S1_X(m_vect_arcs[i].getS1().getCoordX() + (m_vect_arcs[i].getS1().getImage()->w));
                m_vect_arcs[i].setLine_S1_Y(m_vect_arcs[i].getS1().getCoordY() + (m_vect_arcs[i].getS1().getImage()->h)/2);

            }


            //CAS 7
            else if(m_vect_arcs[i].getArrowX1() == m_vect_arcs[i].getS1().getCoordX() && m_vect_arcs[i].getArrowY1() < m_vect_arcs[i].getS1().getCoordY())
            {

                m_vect_arcs[i].setArrowX1(m_vect_arcs[i].getS2().getCoordX() + (m_vect_arcs[i].getS2().getImage()->w)/2);
                m_vect_arcs[i].setArrowY1(m_vect_arcs[i].getS2().getCoordY() + (m_vect_arcs[i].getS2().getImage()->h));

                X2 = m_vect_arcs[i].getArrowX1() - 10;
                Y2 = m_vect_arcs[i].getArrowY1() + 10;

                X3 = m_vect_arcs[i].getArrowX1() + 10;
                Y3 = m_vect_arcs[i].getArrowY1() + 10;

                m_vect_arcs[i].setLine_S1_X(m_vect_arcs[i].getS1().getCoordX() + (m_vect_arcs[i].getS1().getImage()->w)/2);
                m_vect_arcs[i].setLine_S1_Y(m_vect_arcs[i].getS1().getCoordY() - 25);

            }


            //CAS 8
            else if(m_vect_arcs[i].getArrowX1() < m_vect_arcs[i].getS1().getCoordX() && m_vect_arcs[i].getArrowY1() == m_vect_arcs[i].getS1().getCoordY())
            {

                m_vect_arcs[i].setArrowX1(m_vect_arcs[i].getS2().getCoordX() + (m_vect_arcs[i].getS2().getImage()->w));
                m_vect_arcs[i].setArrowY1(m_vect_arcs[i].getS2().getCoordY() + (m_vect_arcs[i].getS2().getImage()->h)/2);

                X2 = m_vect_arcs[i].getArrowX1() + 10;
                Y2 = m_vect_arcs[i].getArrowY1() - 10;

                X3 = m_vect_arcs[i].getArrowX1() + 10;
                Y3 = m_vect_arcs[i].getArrowY1() + 10;

                m_vect_arcs[i].setLine_S1_X(m_vect_arcs[i].getS1().getCoordX());
                m_vect_arcs[i].setLine_S1_Y(m_vect_arcs[i].getS1().getCoordY() + (m_vect_arcs[i].getS1().getImage()->h)/2);



            }


            //AFFICHAGE DES FORMES
            triangle(buffer, m_vect_arcs[i].getArrowX1(), m_vect_arcs[i].getArrowY1(), X2, Y2, X3, Y3, makecol(255,0,0));
            line(buffer, (X2+X3)/2, (Y2+Y3)/2, m_vect_arcs[i].getLine_S1_X(), m_vect_arcs[i].getLine_S1_Y(), makecol(255,0,0));
            textprintf(buffer,font,(m_vect_arcs[i].getLine_S1_X()+m_vect_arcs[i].getArrowX1())/2 -40,(m_vect_arcs[i].getLine_S1_Y()+m_vect_arcs[i].getArrowY1())/2, makecol(100,0,255) ,"Coef=%1.2f",coeff);

        }
    }
}
*/
