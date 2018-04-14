#include "Graphe.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <queue>

using namespace std;


//Constructeur par défaut
Graphe::Graphe()
{

}


//Constructeur surchargé
Graphe::Graphe(int _ordre, int _nb_arcs, std::vector<Sommet> _vect_som, std::vector<Arc> _vect_arcs, int _nb_mois, bool _non_trop)
    :m_ordre(_ordre), m_nb_arcs(_nb_arcs), m_vect_som(_vect_som), m_vect_arcs(_vect_arcs),m_nb_mois(_nb_mois), m_nb_mois_temp(0), m_non_trophique(_non_trop)
{

}



//Destructeur
Graphe::~Graphe()
{

}




//Accesseurs
//getters
//getter qui retourne l'attribut "m_non_trop"
bool Graphe::getNonTrop()
{
    return m_non_trophique;
}

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

//getter qui retourne l'attribut "m_nb_mois"
int Graphe::getNbMois()
{
    return m_nb_mois;
}

//getter qui retourne l'attribut "m_nb_mois"
int Graphe::getNbMoisTemp()
{
    return m_nb_mois_temp;
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
void Graphe::setNonTrop(bool _nont)
{
    m_non_trophique=_nont;
}
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

//getter qui modifie l'attribut "m_nb_mois"
void Graphe::setNbMois(int nb_mois)
{
    m_nb_mois=nb_mois;
}

//getter qui modifie l'attribut "m_nb_mois_temp"
void Graphe::setNbMoisTemp(int nb_mois_temp)
{
    m_nb_mois_temp=nb_mois_temp;
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



/* lecture_ficher : sous-programme permettant de lire le graphe actuel dans un fichier
ENTREE :
    f : de type std::string
SORTIE
    aucune
*/
void Graphe::lecture_fichier(std::string f)
{
    ifstream fichier;
    fichier.open(f);

    //Initialisation des variables nécessaires à la lecture du fichier
    BITMAP* image;
    int ordre, nb_arcs, nb_mois;
    int num, n, x, y;
    int s1, s2;
    bool b1,b2, b3, nont, influ;
    float coeff,nourr;
    float r;
    std::string nom, nom_img;
    std::vector<Sommet> vec_som;
    std::vector<Arc> vec_arc;

    if(fichier)
    {

        //On lit l'ordre
        fichier>> nont;
        fichier>> nb_mois;
        fichier >> ordre;

        setNonTrop(nont);
        setNbMoisTemp(nb_mois);
        setNbMois(nb_mois);
        setOrdre(ordre);

        for(int i = 0; i<getOrdre(); i++)
        {
            //Sur une même ligne on lit le nom, le numéro, le N, le r et les coordonnées d'un sommet
            fichier>>nom;
            fichier>>num;
            fichier>>n;
            fichier>>r;
            fichier>>x;
            fichier>>y;
            fichier>>b1;
            fichier>>b2;
            fichier>>b3;
            fichier>>nourr;

            nom_img = nom + ".bmp";
            image = load_bitmap(nom_img.c_str(),NULL);
            if (!image)
            {
                allegro_message("prb allocation BITMAP ");
                std::cout<<nom_img;
                allegro_exit();
                exit(EXIT_FAILURE);
            }

            //On crée le sommet et on l'ajoute au vecteur de sommet
            Sommet s(nom, num, n, 0, r, x, y, image, b1, b2, false, n, 0,b1, b3,nourr);
            vec_som.push_back(s);
        }
        //On lit le nombre d'arcs
        fichier>>nb_arcs;
        setNbArcs(nb_arcs);

        for(int j=0; j<getNbArcs(); j++)
        {
            //on lit le numéro des deux sommets de l'arc
            fichier >> s1;
            fichier >> s2;
            fichier >> influ;


            Arc a(vec_som[s1], vec_som[s2], 0, true, 0, influ);
            //on entre tous les arcs dans un vecteur d'arcs
            vec_arc.push_back(a);

        }

        setVectArcs(vec_arc);
       calcul_para_post_modif(vec_som);


        //On affiche en console le graphe
        std::cout<<"*** GRAPHE ***"<<std::endl;
        std::cout<<"Ordre : "<<getOrdre()<<std::endl;
        std::cout<<"NB Arcs : "<<getNbArcs()<<std::endl<<std::endl;
        for(int i =0; i < getOrdre(); i++)
        {
            if(getVectSom()[i].getK()<=0)
            {
                vec_som[i].setK(2);
                vec_som[i].setKTemp(2);
                setVectSom(vec_som);
            }
            std::cout<<((getVectSom())[i]).getName()<<" "<<((getVectSom())[i]).getN()<<" "<<((getVectSom())[i]).getK()<<" "<<((getVectSom())[i]).getR()<<" "<<((getVectSom())[i]).getCoordX()<<" "<<((getVectSom())[i]).getCoordY()<<std::endl;
        }
        std::cout<<std::endl;
        for(int i=0; i<getNbArcs(); i++)
        {

            std::cout<<"Arc "<<(i+1)<<" : "<<((getVectArcs())[i]).getS1().getNumero()<< " et "<<((getVectArcs())[i]).getS2().getNumero()<<" ; coeff "<<((getVectArcs())[i]).getCoef()<<std::endl;
        }

        std::cout << "-------------------------------------" << std::endl;

        fichier.close();

    }
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
    afficher_console();
    ofstream fichier;
    fichier.open(f);
    bool b1, b2, b3, nont, influ;
    if(fichier)
    {
        if(m_non_trophique==true) nont = 1;
        else nont = 0;

        //On sauvegarde le booleen non trophique
        fichier<<nont<<std::endl;
        //On sauvegarde le mois
        fichier << getNbMois() << std::endl;

        //On sauvegarde l'ordre
        fichier << getOrdre() << std::endl;

        for(int i =0; i<getOrdre(); i++)
        {

            if((getVectSom()[i]).getAffSom() == 1) b1 =1;
            else b1 = 0;

            b2 = 0;

            if((getVectSom()[i]).getVeget() == 1) b3 =1;
            else b3 = 0;

            //On sauvegarde dans le fichier les 2 sommets de l'arete et le poids de celle-ci
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
            fichier << " ";
            fichier << b3;
            fichier << " ";
            fichier << getVectSom()[i].getNourriture();
            fichier << std::endl;
        }


        //on sauvegarde les arcs
        fichier<<getNbArcs()<<std::endl;

        //On sauvegarde les arcs
        for(int i = 0; i<getNbArcs(); i++)
        {
            if(m_vect_arcs[i].getInfluence()==true) influ=1;
            else influ = 0;

            fichier << (getVectArcs()[i]).getS1().getNumero();
            fichier << " ";
            fichier << (getVectArcs()[i]).getS2().getNumero();
            fichier << " ";
            fichier<< influ;
            fichier << std::endl;
        }

        fichier.close();

    }

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
    for(int i =0; i<getOrdre(); i++)
    {
       if(m_vect_som[i].getAffSom()==true) std::cout<<m_vect_som[i].getName()<<"  Sommet n_"<<m_vect_som[i].getNumero()<<std::endl;
    }
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
    std::cout<<"Lequel de ces parametres souhaitez-vous modifier ?(coefficient de portage(K), taux de croissance(R), Population(N) ou Nourriture(Q))"<<std::endl;
    std::cin>>choix;

    //Blindage
    //Tant que le choix saisi est différent de K, R ou N
    while(choix!= "K" && choix!="R" && choix!="N" && choix!="Q")
    {
        //Message d'erreur et demande de re-saisie
        std::cout<<"Mauvaise saisie du choix. Veuillez recommencer. (K, R, N ou Q)"<<std::endl;
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
        Sommet s((getVectSom()[som]).getName(), (getVectSom()[som]).getNumero(), (getVectSom()[som]).getN(), nouv, (getVectSom()[som]).getR(), (getVectSom()[som]).getCoordX(), (getVectSom()[som]).getCoordY(), (getVectSom()[som]).getImage(), (getVectSom()[som]).getAffSom(), (getVectSom()[som]).getSelect(),(getVectSom()[som]).getMarque(),(getVectSom()[som]).getN(),nouv,(getVectSom()[som]).getAffSomTemp(),(getVectSom()[som]).getVeget(), getVectSom()[som].getNourriture() );

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
        Sommet s((getVectSom()[som]).getName(), (getVectSom()[som]).getNumero(), nouv, (getVectSom()[som]).getK(), (getVectSom()[som]).getR(), (getVectSom()[som]).getCoordX(), (getVectSom()[som]).getCoordY(), (getVectSom()[som]).getImage(), (getVectSom()[som]).getAffSom(), (getVectSom()[som]).getSelect(),(getVectSom()[som]).getMarque(),nouv, (getVectSom()[som]).getKTemp(),(getVectSom()[som]).getAffSomTemp(),(getVectSom()[som]).getVeget(),getVectSom()[som].getNourriture());

        //Pour tous les sommets du graphe
        for(int i=0; i<getOrdre(); i++)
        {
            //On modifie le vecteur de sommets
            if (i==som) vec_som.push_back(s);
            else vec_som.push_back(getVectSom()[i]);
        }

        //Appel du sous-programme suivant pour modifier K et R dépendants de N
       // calcul_para_post_modif(vec_som);

    }

    //Si on choisit de modifier R
    if(choix=="R")
    {

        //Choix du nouveau R
        std::cout<<"R actuel pour "<<(getVectSom()[som]).getName()<<" : "<<(getVectSom()[som]).getR()<<std::endl;
        std::cout<<"Saisir nouveau R";
        std::cin>>nouv;

        //On crée un sommet avec les mêmes propriétés que celui à modifier sauf R qui a été actualisé
        Sommet s((getVectSom()[som]).getName(), (getVectSom()[som]).getNumero(), (getVectSom()[som]).getN(), (getVectSom()[som]).getK(), nouv, (getVectSom()[som]).getCoordX(), (getVectSom()[som]).getCoordY(), (getVectSom()[som]).getImage(), (getVectSom()[som]).getAffSom(), (getVectSom()[som]).getSelect(),(getVectSom()[som]).getMarque(), (getVectSom()[som]).getN(),(getVectSom()[som]).getK(),(getVectSom()[som]).getAffSomTemp(),(getVectSom()[som]).getVeget(),getVectSom()[som].getNourriture());

        //Pour tous les sommets du graphe
        for(int i=0; i<getOrdre(); i++)
        {
            //On modifie le vecteur de sommets
            if (i==som) vec_som.push_back(s);
            else vec_som.push_back(getVectSom()[i]);
        }
    }
        //Si on choisit de modifier Nourriture
    if(choix=="Q")
    {

        //Choix du nouveau R
        std::cout<<"Quantite de nourriture ingeree actuellement par "<<(getVectSom()[som]).getName()<<" : "<<(getVectSom()[som]).getNourriture()<<std::endl;
        std::cout<<"Saisir nouvelle Q";
        std::cin>>nouv;

        //On crée un sommet avec les mêmes propriétés que celui à modifier sauf R qui a été actualisé
        Sommet s((getVectSom()[som]).getName(), (getVectSom()[som]).getNumero(), (getVectSom()[som]).getN(), (getVectSom()[som]).getK(), getVectSom()[som].getR(), (getVectSom()[som]).getCoordX(), (getVectSom()[som]).getCoordY(), (getVectSom()[som]).getImage(), (getVectSom()[som]).getAffSom(), (getVectSom()[som]).getSelect(),(getVectSom()[som]).getMarque(), (getVectSom()[som]).getN(),(getVectSom()[som]).getK(),(getVectSom()[som]).getAffSomTemp(),(getVectSom()[som]).getVeget(),nouv);

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

    if(choix == "N" || choix =="Q") calcul_para_post_modif(m_vect_som);
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


    //on met les nouveau sommet dans les arcs
    Sommet so;
    for(int i=0; i<getOrdre();i++)
    {
        for(int j=0; j<getOrdre(); j++)
        {
            if(vec_arc[j].getS1().getNumero() == i)
            {
                so = vec_som[i];
                vec_arc[j].setS1(so);
            }
            else if(vec_arc[j].getS2().getNumero() == i)
            {
                so = vec_som[i];
                vec_arc[j].setS2(so);
            }
        }
    }
     //On calcule le coefficient de l'arc que l'on crée ensuite
        int comp = 0;
        for(int k=0; k<getNbArcs(); k++)
        {
            for(int l = 0; l<getNbArcs(); l++)
            {
                if(vec_arc[k].getS1().getNumero() == vec_arc[l].getS1().getNumero()&& vec_arc[k].getS1().getAffSom()==true && vec_arc[k].getS2().getAffSom()==true) comp++;
                if(l==getNbArcs()-1 && comp>0)
                {
                    // std::cout<<k<<" "<<compt<<std::endl;
                    float coeff = (float)(1)/(comp);
                    float nourr = (float)(1)/(vec_som[vec_arc[k].getS2().getNumero()].getNourriture());
                    coeff = (float)(coeff) *(nourr);
                    vec_arc[k].setCoef(coeff);
                }
                else if(comp<=0) vec_arc[k].setCoef(0);
            }
            comp = 0;
        }
        //On calcule le paramètre K des sommets
        std::vector<int> new_k;

        for(int i = 0; i<getOrdre(); i++)
        {
            //pour tous les arcs
            new_k.push_back(0);
            for(int k=0; k<getNbArcs(); k++)
            {
                //si il est affiché et que son influence est positive, on calcule le K
                if(vec_arc[k].getS2().getNumero()== i && vec_arc[k].getInfluence()==0)
                {
                    new_k[i] = new_k[i] + ((vec_arc[k].getCoef()) * (vec_arc[k].getS1().getN()));
                    //std::cout<<"\n"<<i<<" "<<new_k[i]<<" "<<vec_arc[k].getS1().getNumero()<<" "<<vec_arc[k].getS1().getN()<<std::endl;
                }

            }
            //si le nouveau k est à 0, on le met à 100000 pour les végétaux et à 2 pour les animaux
            if( new_k[i] == 0) vec_som[i].setK(2);
            else
            {
                vec_som[i].setK(new_k[i]);
            }
        }

    //On modifie les vecteurs de sommets et d'arcs du graphe avec les changements apportés
    setVectArcs(vec_arc);
    setVectSom(vec_som);
}




/*conservation_para : sous programme permettant de demander si on souhaite garder les paramètres tels qu'ils sont après simulation en temps réel
ENTREE : Aucune
SORTIE : Aucune
*/
void Graphe::conservation_para()
{
    int choix;
    int n,k;
    float coef;
    std::vector<Sommet> vec_s = getVectSom();
    std::vector<Arc> vec_a = getVectArcs();

    //On demande à l'utilisateur s'il veut conserver les paramètres après simulation en temps réel
    std::cout<<"Souhaitez vous conserver les paramètres des sommets (K, N, R) tels qu'ils sont ? (1 pour oui, 0 pour non)"<<std::endl;
    std::cin>>choix;

    //Tant que le choix n'est pas valide, on lui demande de recommencer la saisie
    while(choix!=(1) && choix!=0 )
    {
        std::cout<<"Choix non correct. Recommencer. 1 pour oui, 0 pour non"<<std::endl;
        std::cin>>choix;
    }
    //Si il refuse, on redonne au N, K, R, du sommet leur valeur initiale
    //et on repart du mois 0.
    if(choix == 0)
    {
        for(int i =0; i<getOrdre(); i++)
        {
            n = vec_s[i].getNTemp();
            k = vec_s[i].getKTemp();
            if (n>0) vec_s[i].setAffSom(true);
            else vec_s[i].setAffSom(false);
            vec_s[i].setN(n);
            vec_s[i].setK(k);
        }
        for(int j= 0; j<getNbArcs(); j++)
        {
            coef = vec_a[j].getCoefTemp();
            vec_a[j].setCoef(coef);
        }

        setNbMois(getNbMoisTemp());
        setVectSom(vec_s);
        setVectArcs(vec_a);
    }
    //si il accepte, on donne aux k, n, nb mois temporaires leur nouvelle valeur
    else
    {
        for(int i=0; i<getOrdre(); i++)
        {
            n = vec_s[i].getN();
            k = vec_s[i].getN();
            if(n>0) vec_s[i].setAffSom(true);
            else vec_s[i].setAffSom(false);
            vec_s[i].setNTemp(n);
            vec_s[i].setKTemp(k);
        }
        setNbMoisTemp(getNbMois());
    }

    //On affiche en console le graphe
    afficher_console();

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
    if(m_non_trophique==true) std::cout<<"Le graphe est non-trophique."<<std::endl;
    else std::cout<<"Le graphe est trophique."<<std::endl;
    std::cout<<std::endl<<"Ordre : "<<getOrdre()<<std::endl;
    std::cout<<"NB Arcs : "<<getNbArcs()<<std::endl;


    //Pour tous les sommets du graphe
    for(int i =0; i < getOrdre(); i++)
    {
        //Affichage des informations du sommet
        std::cout<<((getVectSom())[i]).getName()<<" "<<((getVectSom())[i]).getN();
        std::cout<<" "<<((getVectSom())[i]).getK()<<" "<<((getVectSom())[i]).getR();
        std::cout<<" "<<((getVectSom())[i]).getNourriture();
        std::cout<<" "<<((getVectSom())[i]).getCoordX()<<" "<<((getVectSom())[i]).getCoordY()<<std::endl;
    }

    std::cout<<std::endl;


    //Pour tous les arcs du graphe
    for(int i=0; i<getNbArcs(); i++)
    {
        //Affichage des informations de l'arc
        std::cout<<"Arc "<<(i+1)<<" : "<<((getVectArcs())[i]).getS1().getNumero()<< " et "<<((getVectArcs())[i]).getS2().getNumero()<<" ; coeff "<<((getVectArcs())[i]).getCoef()<<std::endl;
    }

    std::cout << "-------------------------------------" << std::endl;

}




/* afficher_sommets : sous-programme permettant d'afficher à l'écran les sommets du graphe
ENTREE :
    img : de type BITMAP*
SORTIE :
    aucune
*/
void Graphe::afficher_sommets(BITMAP* img)
{

    //Instance de deux int
    int n,r;

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
            // Si il n'est pas supprimé
           if(getVectSom()[i].getAffSom() == true)
           {
               //On affiche sa BITMAP
               draw_sprite(img, (getVectSom()[i]).getImage(), (getVectSom()[i]).getCoordX(), (getVectSom()[i]).getCoordY());

                //n prend la valeur du numéro du sommet
                n = (getVectSom()[i]).getNumero();

                //r prend la valeur de son R arrondie à l'entier
                r = int(getVectSom()[i].getR());

                //On affiche ses paramètres  N et nourriture
                textprintf(img,font, (getVectSom()[i]).getCoordX()+4, (getVectSom()[i]).getCoordY()+ getVectSom()[i].getImage()->h+4, makecol(0,0,0) ,"Population: %d",getVectSom()[i].getN() );
                (textprintf(img,font, (getVectSom()[i]).getCoordX()+4, (getVectSom()[i]).getCoordY()+ getVectSom()[i].getImage()->h + 16, makecol(0,0,0) ,"Consommation: %1.2f",getVectSom()[i].getNourriture() ));

                //On affiche le numéro du sommet au-dessus de son image
                textprintf(img,font, (getVectSom()[i]).getCoordX()+20, (getVectSom()[i]).getCoordY()-20, makecol(0,0,0), "Sommet n_%d", n);

                //Affichage d'un rectangle autour de l'image du sommet
                //Si le sommet est sélectionné
                if(getVectSom()[i].getSelect()) rect(screen, getVectSom()[i].getCoordX(), getVectSom()[i].getCoordY(), getVectSom()[i].getCoordX()+ getVectSom()[i].getImage()->w, getVectSom()[i].getCoordY()+getVectSom()[i].getImage()->h, makecol(0,255,0));
                //Sinon
                else rect(screen, getVectSom()[i].getCoordX(), getVectSom()[i].getCoordY(), getVectSom()[i].getCoordX()+ getVectSom()[i].getImage()->w, getVectSom()[i].getCoordY()+getVectSom()[i].getImage()->h, makecol(0,0,0));


           }
            //On affiche l'année auquel on est en haut à droite de l'écran
            textprintf(img,font, SCREEN_W - 100, 20 , makecol(0,200,100) ,"Mois n_%d",getNbMois() );

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
                        m_vect_arcs[j].afficher_arc(img);
                    }

                }


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
        if(multiple) m_vect_som[i].setSelect(0);

        //On affiche les sommets
        afficher_sommets(img);
    }



    //On regarde pour tous les sommets que la nouvelle position du sommet n'empiètera pas sur leur image
    //Pour tous les sommets
    for(int i=0; i<getOrdre(); i++)
    {

        //Si le sommet est différent de celui sélectionné
        if(i != n)
        {
            //si la souris n'est pas sur ou trop près d'un autre sommet ou sur la barre d'outils alors on change les coordonnées duu sommet
            if((x>getVectSom()[i].getCoordX()-getVectSom()[i].getImage()->w) && (x<getVectSom()[i].getCoordX()+ getVectSom()[i].getImage()->w))
            {

                if((y>getVectSom()[i].getCoordY() -getVectSom()[i].getImage()->h)&& (y<getVectSom()[i].getCoordY() + getVectSom()[i].getImage()->h))
                {
                    test = true;
                    s.setCoordX(getVectSom()[n].getCoordX());
                    s.setCoordY(getVectSom()[n].getCoordY());
                    i = getOrdre();
                }
            }

            else if (x < 125)
            {
                test = true;
                s.setCoordX(getVectSom()[n].getCoordX());
                s.setCoordY(getVectSom()[n].getCoordY());
                i = getOrdre();
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

    //Instance d'un vecteur d'arcs
    std::vector<Arc> vec_arc = getVectArcs();

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
                vec_som[i].setN(0);
            }
        }
    }

/*
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
*/
     //on met les nouveau sommet dans les arcs
    Sommet so;
    for(int i=0; i<getOrdre();i++)
    {
        for(int j=0; j<getOrdre(); j++)
        {
            if(vec_arc[j].getS1().getNumero() == i)
            {
                so = vec_som[i];
                vec_arc[j].setS1(so);
            }
            else if(vec_arc[j].getS2().getNumero() == i)
            {
                so = vec_som[i];
                vec_arc[j].setS2(so);
            }
        }
    }

    //On calcule le coefficient de l'arc que l'on crée ensuite
        int comp = 0;
        float coeff = (float)(1);
        for(int k=0; k<getNbArcs(); k++)
        {
            for(int l = 0; l<getNbArcs(); l++)
            {
                if(vec_arc[k].getS1().getNumero() == vec_arc[l].getS1().getNumero()&& vec_arc[k].getS1().getAffSom()==true && vec_arc[k].getS2().getAffSom()==true) comp++;
                if(l==getNbArcs()-1 && comp>0)
                {
                    // std::cout<<k<<" "<<compt<<std::endl;
                    float coeff = (float)(1)/(comp);
                    float nourr = (float)(1)/(vec_som[vec_arc[k].getS2().getNumero()].getNourriture());
                    coeff = (float)(coeff) *(nourr);
                    vec_arc[k].setCoef(coeff);
                }
                else if(comp<=0) vec_arc[k].setCoef(0);
            }
            comp = 0;
        }

        //On calcule le paramètre K des sommets
        std::vector<int> new_k;

        for(int i = 0; i<getOrdre(); i++)
        {
            new_k.push_back(0);
            for(int k=0; k<getNbArcs(); k++)
            {
                if(vec_arc[k].getS2().getNumero()== i )
                {
                    new_k[i] = new_k[i] + ((vec_arc[k].getCoef()) * (vec_arc[k].getS1().getN()));
                    std::cout<<i<<" "<<new_k[i]<<" "<<vec_arc[k].getS1().getNumero()<<" "<<vec_arc[k].getS1().getN()<<std::endl;
                }

            }
            if(vec_som[i].getVeget()==true && new_k[i] == 0) vec_som[i].setK(10000);
            else if(vec_som[i].getVeget()==false && new_k[i] == 0) vec_som[i].setK(2);
            else vec_som[i].setK(new_k[i]);
        }


    //Modifications des vecteurs de sommets et d'arcs du graphe
    setVectSom(vec_som);
    //setVectArcs(vec_arc);

    //Affichage des sommets
    afficher_sommets(img);
    //Affichage du graphe en console
    afficher_console();

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
    //Instance d'un vecteur de sommets
    std::vector<Sommet> vec_som= getVectSom();
    //Instance d'un vecteur d'arcs
    std::vector<Arc> vec_arc = getVectArcs();

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
    //Le sommet saisi par l'utilisateur reprend sa population originelle
    m_vect_som[som].setN(m_vect_som[som].getNTemp());

    }
         //on met les nouveau sommet dans les arcs
    Sommet so;
    for(int i=0; i<getOrdre();i++)
    {
        for(int j=0; j<getOrdre(); j++)
        {
            if(vec_arc[j].getS1().getNumero() == i)
            {
                so = m_vect_som[i];
                vec_arc[j].setS1(so);
            }
            else if(vec_arc[j].getS2().getNumero() == i)
            {
                so = m_vect_som[i];
                vec_arc[j].setS2(so);
            }
        }
    }

    //On calcule le coefficient de l'arc que l'on crée ensuite
    int comp = 0;
    float coeff = (float)(1);
    for(int k=0; k<getNbArcs(); k++)
    {
        for(int l = 0; l<getNbArcs(); l++)
        {
            if(vec_arc[k].getS1().getNumero() == vec_arc[l].getS1().getNumero()&& vec_arc[k].getS1().getAffSom()==true && vec_arc[k].getS2().getAffSom()==true) comp++;
            if(l==getNbArcs()-1 && comp>0)
            {
                // std::cout<<k<<" "<<compt<<std::endl;
                float coeff = (float)(1)/(comp);
                float nourr = (float)(1)/(vec_som[vec_arc[k].getS2().getNumero()].getNourriture());
                coeff = (float)(coeff) *(nourr);
                vec_arc[k].setCoef(coeff);
            }
            else if(comp<=0) vec_arc[k].setCoef(0);
        }
            //std::cout<<k<<" "<<compt<<std::endl;
        comp = 0;
    }
    //On calcule le paramètre K des sommets
    std::vector<int> new_k;

    for(int i = 0; i<getOrdre(); i++)
    {
        new_k.push_back(0);
        for(int k=0; k<getNbArcs(); k++)
        {
            if(vec_arc[k].getS2().getNumero()== i )
            {
                new_k[i] = new_k[i] + ((vec_arc[k].getCoef()) * (vec_arc[k].getS1().getN()));
                std::cout<<i<<" "<<new_k[i]<<" "<<vec_arc[k].getS1().getNumero()<<" "<<vec_arc[k].getS1().getN()<<std::endl;
            }
        }
        if(m_vect_som[i].getVeget()==true && new_k[i] == 0) m_vect_som[i].setK(10000);
        else if(m_vect_som[i].getVeget()==false && new_k[i] == 0) m_vect_som[i].setK(2);
        else m_vect_som[i].setK(new_k[i]);
    }

    afficher_console();
/*
    std::vector<Arc> vec_arc = getVectArcs();
    for(int i=0; i<getNbArcs(); i++)
    {
        if(m_vect_som[vec_arc[i].getS1().getNumero()].getAffSom() == true) vec_arc[i].setAffArc(true);
        else if(m_vect_som[vec_arc[i].getS2().getNumero()].getAffSom() == true) vec_arc[i].setAffArc(true);
        else vec_arc[i].setAffArc(false);
    }

    setVectArcs(vec_arc);
*/
}





/*temps reel : sous-programme permettant d'afficher en temps reel l'evolution du réseau écologique
ENTREE : deux images (le fond et le buffer) et un compteur (un entier)
SORTIE : Aucune
*/
void Graphe::temps_reel(BITMAP* img, BITMAP* img2, int compt)
{
    //On crée un vecteur de sommet et un vecteur d'arcs ainsi qu'un vecteur d'entier
    std::vector<Sommet> vec_som = getVectSom();
    std::vector<Arc> vec_arc = getVectArcs();
    //On crée deux booléens
    bool s = true;
    std::vector<bool> regen_veget;
    std::vector<bool> famine;
    //3 entiers;
    int new_n, nb_mois, num;


    //Si c'est le tout premier mois, les vecteurs de famine et de regeneration sont à 0 pour tous les sommets
    //les vecteurs de famine et de regeneration sont initialiser à 0
    for(int i= 0; i<getOrdre(); i++)
    {
        if(compt==0)
        {
            c_regen.push_back(0);
            c_famine.push_back(0);
        }
        famine.push_back(0);
        regen_veget.push_back(0);

    }

    //On parcourt le vecteur de sommet.
    //Si il est supprimé alors sa population devient nulle
    for(int i =0; i<getOrdre(); i++)
    {
        if(vec_som[i].getAffSom()==false) vec_som[i].setN(0);
        if(vec_som[i].getN() == 0) vec_som[i].setAffSom(false);
        else vec_som[i].setAffSom(true);
    }
    //On parcourt tous les sommets
    for(int i =0; i<getOrdre(); i++)
    {
        std::vector<int> vegetation;
        std::vector<int> nourriture;

        //Si l'espèce n'est pas disparue
        if(vec_som[i].getN()!=0)
        {
            //On calcule une partie de sa population à t+1 ( Nt+1 = Nt + Nt*r(1- N/K)
            new_n = vec_som[i].getN() +(int)((vec_som[i].getN() * vec_som[i].getR())*(1 - (vec_som[i].getN() / vec_som[i].getK())));
            //On parcourt les arcs
            for(int j =0; j<getNbArcs(); j++)
            {
                num = vec_som[i].getNumero();
                // si le sommet actuel est un végétal, on entre le numéro de l'arc donc c'est la proie dans son vecteur végétation
                if(vec_som[i].getVeget()==true)
                {
                    if(vec_arc[j].getS1().getNumero() == num)  vegetation.push_back(vec_arc[j].getS2().getNumero());
                }
                //sinon c'est un annimal, on entre le numero de l'arc dont c'est le chasseur dans son vecteur nourriture
                else if(vec_arc[j].getS2().getNumero() == num) nourriture.push_back(vec_arc[j].getS1().getNumero());

                 //on termine le calcul de la population à t+1 selon si ses prédecesseurs et ses successeurs
                if(i == vec_arc[j].getS2().getNumero() && vec_arc[j].getS1().getN() != 0) new_n = new_n + (vec_arc[j].getCoef() * vec_som[vec_arc[j].getS1().getNumero()].getN());
                else if((vec_arc[j].getS1().getNumero()==num )&& (vec_arc[j].getS2().getN() > 0)) new_n = new_n - (vec_arc[j].getCoef() * vec_som[vec_arc[j].getS2().getNumero()].getN());
            }
            std::cout<<"\n";
            //Si la nouvelle population d'une espèce est nulle alors on ne l'affiche plus
            //une population met 5 tours à disparaitre vraiment
            if(new_n<=0 && c_regen[i]<2)
            {
                new_n = vec_som[i].getK();
                vec_som[i].setAffSom(true);
            }
            else if(new_n<0)
            {
                new_n = 0;
                vec_som[i].setAffSom(false);
            }
            else vec_som[i].setAffSom(true);

            //On parcourt son vecteur de végétation
            // Si tous leur k est supérieure d'au moins 100 à leur population alors la regen_veget devient vrai
            for(int k = 0; k<vegetation.size(); k++)
            {
                if(vec_som[i].getN()<=0)
                {
                    if(vec_som[vegetation[k]].getN() >= vec_som[vegetation[k]].getK()-100)
                    {
                        regen_veget[i] = false;
                        k = vegetation.size();
                    }
                    else regen_veget[i] = true;
                }
            }
            //On parcourt son vecteur de proie
            // Si toutes leurs proies sont disparues alors la famine devient vraie
            for(int k = 0; k<nourriture.size(); k++)
            {
                if(vec_som[i].getN()>0)
                {
                    if(vec_som[nourriture[k]].getN() > 0 )
                    {
                        famine[i] = false;
                        k = nourriture.size();
                    }
                    else famine[i] = true;
                }
            }
            //Si on est pas en situation de famine ou de regeneration les vecteurs correspondanst passent à 0
            if (famine[i] == false) c_famine[i] = 0;
            //if (regen_veget[i] == false) c_regen[i] = 0;
            std::cout<<c_regen[i]<<" "<<c_famine[i]<<std::endl;
            //Sinon c'est un animal, si sa population est non nulle et qu'il est en période de famine
            if((famine[i]==true))
            {

                c_famine[i]++;
                //Si la famine dure depuis 2 mois, la population passe à 1à, ensuite à 5(cannibalisme), etc jusqu'à 0
                if(c_famine[i]==2) vec_som[i].setN(10);
                if(c_famine[i] == 3) vec_som[i].setN(5);
                if (c_famine[i] == 4) vec_som[i].setN(3);
                if (c_famine[i] == 5) vec_som[i].setN(1);
                if (c_famine[i] == 6)
                {
                    vec_som[i].setN(0);
                    c_famine[i] = 0;
                }
            }
            else if(new_n<0) new_n = 0;
            else if(new_n>10000) new_n = 10000;
            else vec_som[i].setN(new_n);
        }
    }
    //on calcule les nouveaux k et coeff
    calcul_para_post_modif(vec_som);
    vec_som = getVectSom();


    //on parcourt tous les arcs
    for(int j =0; j<getNbArcs(); j++)
    {
        if(vec_som[vec_arc[j].getS1().getNumero()].getAffSom() == false && vec_som[vec_arc[j].getS1().getNumero()].getN() == false) vec_arc[j].setAffArc(false);
        else vec_arc[j].setAffArc(true);
    }
    for(int i=0; i<getOrdre(); i++)
    {
        if(vec_som[i].getK()==0 && vec_som[i].getVeget()==true) vec_som[i].setK(100000);
        else if(vec_som[i].getK()==0) vec_som[i].setK(10);
    }

    //On parcourt le vecteur de sommet.
    //Si il est supprimé alors sa population devient nulle
    for(int i =0; i<getOrdre(); i++)
    {
        if(vec_som[i].getAffSom()==false) vec_som[i].setN(0);
        if(vec_som[i].getN() == 0) vec_som[i].setAffSom(false);
        else vec_som[i].setAffSom(true);
    }

    //on affiche le nouveau nombre de mois

    nb_mois = getNbMois();
    setNbMois(nb_mois+1);
    setVectSom(vec_som);
    setVectArcs(vec_arc);
    //on affiche l'évolution
    clear_bitmap(img2);
    blit(img, img2, 0,0,0,0,1024,768);
    afficher_console();
    afficher_sommets(img2);
    blit(img2,screen,0,0,0,0,1024,768);

  //  return s;
}





/*temps reel nont : sous-programme permettant d'afficher en temps reel l'evolution du réseau écologique si ils sont non trophique
ENTREE : deux images (le fond et le buffer) et un compteur (un entier)
SORTIE : Aucune
*/
void Graphe::temps_reel_nont(BITMAP* img, BITMAP* img2, int compt)
{
    //On crée un vecteur de sommet et un vecteur d'arcs ainsi qu'un vecteur d'entier
    std::vector<Sommet> vec_som = getVectSom();
    std::vector<Arc> vec_arc = getVectArcs();
    //On crée deux booléens
    bool s = true;
    //3 entiers;
    int new_n, new_k, nb_mois, num;
    new_k = 0;
    //1 float
    float new_coef;
    //
    std::vector<bool> respire;

    //Si c'est le tout premier mois, les vecteurs de famine
    //les vecteurs de respiration sont initialiser à 0
    for(int i= 0; i<getOrdre(); i++)
    {
        if(compt==0) c_famine.push_back(0);
        respire.push_back(0);

    }

    //On parcourt le vecteur de sommet.
    //Si il est supprimé alors sa population devient nulle
    for(int i =0; i<getOrdre(); i++)
    {
        if(vec_som[i].getAffSom()==false) vec_som[i].setN(0);
        if(vec_som[i].getN() == 0) vec_som[i].setAffSom(false);
        else vec_som[i].setAffSom(true);
    }
    //On parcourt tous les sommets
    for(int i =0; i<getOrdre(); i++)
    {
        std::vector<int> qui_respire;
        //Si l'espèce n'est pas disparue
        if(vec_som[i].getN()>0 && vec_som[i].getN()<10000000)
        {
            //On calcule une partie de sa population à t+1 ( Nt+1 = Nt + Nt*r(1- N/K)
            new_n = int(vec_som[i].getN() +((vec_som[i].getN() * vec_som[i].getR())*(1 - (vec_som[i].getN() / vec_som[i].getK()))));
            //On parcourt les arcs
            for(int j =0; j<getNbArcs(); j++)
            {
                num = vec_som[i].getNumero();
                //on termine le calcul de la population à t+1 selon si ses prédecesseurs et ses successeurs
                if(i == vec_arc[j].getS2().getNumero() && vec_arc[j].getS1().getN() != 0)
                {
                    if(vec_arc[j].getInfluence()==false) new_n = new_n + (vec_arc[j].getCoef() * vec_som[vec_arc[j].getS1().getNumero()].getN());
                    else
                    {
                        new_n = new_n - (vec_arc[j].getCoef() * vec_som[vec_arc[j].getS2().getNumero()].getN());
                        if(i==2) std::cout<<"in"<<std::endl;
                    }
                }
                 //si c'est un annimal, on entre le numero de l'arc dont c'est le chasseur dans son vecteur nourriture
                if(vec_arc[j].getS2().getNumero() == num) qui_respire.push_back(vec_arc[j].getS1().getNumero());


            }
            //Si la nouvelle population d'une espèce est nulle alors on ne l'affiche plus
            if(new_n<=0)
            {
                new_n = 0;
                vec_som[i].setAffSom(false);
            }
            else vec_som[i].setAffSom(true);

            //On parcourt son vecteur de proie
            // Si toutes leurs proies sont disparues alors la famine devient vraie
            for(int k = 0; k<qui_respire.size(); k++)
            {
                if(vec_som[i].getN()>0)
                {
                    if(vec_som[qui_respire[k]].getN() > 0 )
                    {
                        respire[i] = false;
                        k = qui_respire.size();
                    }
                    else respire[i] = true;
                }
            }
            //Si on est pas en situation de famine ou de regeneration les vecteurs correspondanst passent à 0
            if (respire[i] == false) c_famine[i] = 0;
            //Si c'est un animal, si sa population est non nulle et qu'il n'y a plus de quoi le faire vivre
            if((respire[i]==true))
            {
                c_famine[i]++;
                //Si ça dure depuis 2 mois, la population passe à 5, etc jusqu'à 0
                if(c_famine[i]==2) vec_som[i].setN(5);
                if(c_famine[i] == 3) vec_som[i].setN(2);
                if (c_famine[i] == 4) vec_som[i].setN(1);
                if (c_famine[i] == 5)
                {
                    vec_som[i].setN(0);
                    c_famine[i] = 0;
                }
            }
            //si rien de tout ça on affecte la nouvelle population
            else vec_som[i].setN(new_n);
        }
    }
    //on calcule les nouveaux k et coeff
    calcul_para_post_modif(vec_som);
    vec_som = getVectSom();

    //On parcourt le vecteur de sommet.
    //Si il est supprimé alors sa population devient nulle
    for(int i =0; i<getOrdre(); i++)
    {
        if(vec_som[i].getAffSom()==false) vec_som[i].setN(0);
        if(vec_som[i].getN() == 0) vec_som[i].setAffSom(false);
        else vec_som[i].setAffSom(true);
    }


    //on affiche le nouveau nombre de mois
    nb_mois = getNbMois();
    setNbMois(nb_mois+1);
    setVectSom(vec_som);
    setVectArcs(vec_arc);
    //on affiche l'évolution
    clear_bitmap(img2);
    blit(img, img2, 0,0,0,0,1024,768);
    afficher_console();
    afficher_sommets(img2);
    blit(img2,screen,0,0,0,0,1024,768);
}





/// Source : https://www.geeksforgeeks.org/strongly-connected-components/
//A appliquer à chaque graphe pour voir les composantes connexes
/* forte_co : sous-programme permettant de trouver les composantes connexes
ENTREE :
    g = le graphe dont on souhaite connaître les composantes fortement connexes
    img = BITMAP*
SORTIE :
    aucune
*/
void Graphe::forte_co(Graphe g, BITMAP* img, std::vector<int>& temp_x1, std::vector<int>& temp_y1, std::vector<int>& temp_x2, std::vector<int>& temp_y2, bool reduit)
{

    std::cout<<std::endl<<std::endl<<"*** FORTE CONNEXITE ***"<<std::endl;

    //Si on lance la forte connexité avec affichage des couleurs
    if(reduit==false)
    {
        //std::cout << "Debut forte co" << std::endl;
        //Pile de int ou de sommet
        std::stack<int> pile;
        int nb_connex = 0;
        std::vector<int> col_temp;
        std::vector<vector<int>> cpst_co;
        int c;

        //On crée un tableau de booleens de taille ordre qui sert de tableau de marquage
        bool marq[getOrdre()];
        //On l'initialise à false pour le premier DFS
        for(int i =0; i<getOrdre(); i++)
        {
            //On le met à faux
            marq[i]=false;
        }

        //std::cout << "premiers false ok" << std::endl;

        //Pour toutes les cases du tableau de marquage
        for(int i = 0; i<getOrdre(); i++)
        {
            //S'il n'est pas marqué
            if(marq[i]==false)
            {
                //std::cout << "Avant entree DFS" << std::endl;
                // On procède à un premier DFS
                DFS1(i, marq, pile);
                //std::cout << "premier DFS OK" << std::endl;
            }
        }

        //On initialise un vecteur d'arcs qui va recevoir les arcs inversés
        std::vector<Arc> vect_arc;

        //On inverse les sens de tous les arcs
        for(int i= 0; i<m_vect_arcs.size(); i++)
        {
            //On crée un arc partiel qui reçoit le sommet 2 en guise de sommet 1 et inversement
            Arc atemp(m_vect_arcs[i].getS2(),m_vect_arcs[i].getS1(),m_vect_arcs[i].getCoef(), m_vect_arcs[i].getAffArc(), m_vect_arcs[i].getCoefTemp(), m_vect_arcs[i].getInfluence());
            // On met cet arc dans le vecteur d'arcs
            vect_arc.push_back(atemp);
        }

        //On crée un graphe qui va avoir les arcs inversés
        //Il possède les mêmes propriétés que le graphe actuel sauf que ses arcs sont inversés
        Graphe g_inv(getOrdre(),getNbArcs(),getVectSom(),vect_arc, getNbMois(), getNonTrop());

        //std::cout << "arcs inverses" << std::endl;

        //On l'initialise à false pour le second DFS
        for(int i =0; i<getOrdre(); i++)
        {
            //On le met à faux
            marq[i]=false;
        }

        int nb = 0;
        //Tant que la pile n'est pas vide
        while(pile.empty() == false)
        {
            //On prend le sommet au dessus de la pile
            int s = pile.top();
            //On le retire de la pile
            pile.pop();
            //On affiche la composante fortement connexe
            if(marq[s]==false)
            {
                int col = makecol(rand()%256,rand()%256,rand()%256);
                g.getVectSom()[s].setCol(col);
                if (nb_connex==0) col_temp.push_back(col);
                for(int i=0; i<col_temp.size(); i++)
                {
                    if(col == col_temp[i]) nb++;
                }
                if (nb==0) col_temp.push_back(col);
                //On fait appel au deuxième DFS
                g_inv.DFS2(s,marq,col,g, img, temp_x1, temp_y1, temp_x2, temp_y2);
                //std::cout << "Sortie effectuée du 2eme DFS" << std::endl;
            }
        }
        for(int i = 0; i<col_temp.size(); i++)
        {
            std::vector<int> ligne;
            for(int j = 0; j<getOrdre(); j++)
            {
                if(j==0) c = g.getVectSom()[j].getCol();
                if(g.getVectSom()[j].getCol() == c)
                {
                    ligne.push_back(j);
                }
            }
            cpst_co.push_back(ligne);
        }
        std::cout<<"Il y a "<<nb<<" composante(s) fortement connexe dans ce graphe."<<std::endl;

    }
    //Si on lance la forte connexite avec affichage du graphe réduit
    else
    {
        //Pile de int ou de sommet
        std::stack<int> pile;
        int nb_connex = 0;
        std::vector<int> col_temp;
        std::vector<vector<int>> cpst_co;
        int c;
        std::vector<int> v_s;

        //On crée un tableau de booleens de taille ordre qui sert de tableau de marquage
        bool marq[getOrdre()];
        //On l'initialise à false pour le premier DFS
        for(int i =0; i<getOrdre(); i++)
        {
            //On le met à faux
            marq[i]=false;
        }

        //std::cout << "premiers false ok" << std::endl;

        //Pour toutes les cases du tableau de marquage
        for(int i = 0; i<getOrdre(); i++)
        {
            //S'il n'est pas marqué
            if(marq[i]==false)
            {
                //std::cout << "Avant entree DFS" << std::endl;
                // On procède à un premier DFS
                DFS1(i, marq, pile);
                //std::cout << "premier DFS OK" << std::endl;
            }
        }

        //On initialise un vecteur d'arcs qui va recevoir les arcs inversés
        std::vector<Arc> vect_arc;

        //On inverse les sens de tous les arcs
        for(int i= 0; i<m_vect_arcs.size(); i++)
        {
            //On crée un arc partiel qui reçoit le sommet 2 en guise de sommet 1 et inversement
            Arc atemp(m_vect_arcs[i].getS2(),m_vect_arcs[i].getS1(),m_vect_arcs[i].getCoef(), m_vect_arcs[i].getAffArc(), m_vect_arcs[i].getCoefTemp(), m_vect_arcs[i].getInfluence());
            // On met cet arc dans le vecteur d'arcs
            vect_arc.push_back(atemp);
        }

        //On crée un graphe qui va avoir les arcs inversés
        //Il possède les mêmes propriétés que le graphe actuel sauf que ses arcs sont inversés
        Graphe g_inv(getOrdre(),getNbArcs(),getVectSom(),vect_arc, getNbMois(), getNonTrop());

        //std::cout << "arcs inverses" << std::endl;

        //On l'initialise à false pour le second DFS
        for(int i =0; i<getOrdre(); i++)
        {
            //On le met à faux
            marq[i]=false;
        }

        int nb = 0;
        //Tant que la pile n'est pas vide
        while(pile.empty() == false)
        {
            //On prend le sommet au dessus de la pile
            int s = pile.top();
            //On le retire de la pile
            pile.pop();
            //On affiche la composante fortement connexe
            if(marq[s]==false)
            {
                int col = makecol(rand()%256,rand()%256,rand()%256);
                //On entre dans le vecteur de sommet les composantes ayant une couleur différente des autres
                if(col!=0) v_s.push_back(s);
                //Si c'est la premiere fois que la couleur est utilisée on l'entre dans le vecteur de couleur
                if (nb_connex==0)
                {
                    col_temp.push_back(col);
                }
                //Si la couleur utilisée est la même que l'une de celle du vecteur de couleur alor on compte une nouvelle
                //composante fortement connexe
                for(int i=0; i<col_temp.size(); i++)
                {
                    if(col == col_temp[i]) nb++;

                }
                //Si il n'y a encore aucune composantee qui possède cette couleur, on entre la couleur dans le vecteur de couleur
                if (nb==0) col_temp.push_back(col);
                g_inv.DFS2(s,marq,col,g, img, temp_x1, temp_y1, temp_x2, temp_y2);

                //std::cout << "Sortie effectuée du 2eme DFS" << std::endl;
            }
        }
        //On affiche le graphe réduit
        afficher_graphe_reduit(nb, g, v_s, img);
    }

}





/* afficher_graphe_reduit : sous-programme permettant d'afficher le graphe réduit
ENTREE :
    g  : de type Graphe, le graphe dont on souhaite connaître les composantes fortement connexes
    img : de type BITMAP*
    nb : de type int
    cpst_co : de type std::vector<int>
SORTIE :
    aucune
*/
void Graphe::afficher_graphe_reduit(int nb, Graphe g,std::vector<int> cpst_co, BITMAP* img)
{
    //Instance d'un vecteur de int
    std::vector<int> compteur;

    //Initialisation du vecteur à 0 pour tous les arcs
    for(int i=0; i<g.getNbArcs(); i++)
    {
        compteur.push_back(0);
    }

    //Affichage d'un rectangle blanc sur l'écran
    rectfill(screen, 126, 5, 1019, 763, makecol(255,255,255));

    //Pour tous les sommets du graphe réduit
    for(int i=0; i<nb; i++)
    {
          //n prend la valeur du numéro du sommet
            int n = cpst_co[i];
            int x =(g.getVectSom()[cpst_co[i]]).getCoordX()+20;
            int y = (g.getVectSom()[cpst_co[i]]).getCoordY()-20;
            (g.getVectSom()[cpst_co[i]]).setCoordX(x);
            (g.getVectSom()[cpst_co[i]]).setCoordY(y);
            //On affiche le numéro du sommet au-dessus de son image
            textprintf(screen,font, x, y, makecol(0,0,0), "Sommet n_%d", n);
    }

    //On affiche les arêtes reliant les sommets
    for(int i =0; i<nb-1; i++)
    {
        line(screen, (g.getVectSom()[cpst_co[i]]).getCoordX()+40, (g.getVectSom()[cpst_co[i]]).getCoordY(), (g.getVectSom()[cpst_co[i+1]]).getCoordX()+30, (g.getVectSom()[cpst_co[i+1]]).getCoordY(), makecol(0,255,20));
    }

    rest(2000);
}







/// Source : https://www.geeksforgeeks.org/strongly-connected-components/
/* DFS1 : sous-programme permettant d'effectuer le premier DFS
ENTREE :
    s : de type int, numero du sommet actuel
    marq[] : tableau de booleen qui contient les marquages
    pile : std::stack<int> pile de int, contenant les numéros de sommet
SORTIE :
    aucune
*/
void Graphe::DFS1(int s, bool marq[], std::stack<int> &pile)
{
    //std::cout << "Entree dans DFS réussie" <<std::endl;
    //On marque le sommet reçu en paramètres
    marq[s] = true;

    //Vecteur contenant les int contenant les numéros des sommets adjacent au sommet actuel
    std::vector<int> adj;

    //Parmi tous les arcs
    for(int i = 0; i< getVectArcs().size(); i++)
    {
        //std::cout << "Arc : " << i << std::endl;

        //Si le premier sommet est égal à s
        if(m_vect_arcs[i].getS1().getNumero() == s)
        {
            //On ajoute le deuxième sommet au vecteur d'adjacence
            adj.push_back(m_vect_arcs[i].getS2().getNumero());
            //std::cout << "Sommet " << m_vect_arcs[i].getS2().getNumero() << std::endl;
        }
    }


    //Pour tous les sommets adjacents
    for(int i = 0; i < adj.size(); i++)
    {
        //std::cout << "Sommet adjacent numéro " << adj[i] <<std::endl;
        //S'il n'est pas marqué
        if(!marq[adj[i]])
        {
            //On procède à un DFS récursif avec le premier DFS
            //std::cout << "Avant d'entrer dans recursive " << std::endl;
            DFS1(adj[i], marq, pile);
        }
    }

    //On met s dans la pile
    pile.push(s);

    //std::cout <<"Sur le point de sortir du DFS" << std::endl;
}






/// Source : https://www.geeksforgeeks.org/strongly-connected-components/
/* DFS2 : sous-programme permettant d'effectuer le second DFS
ENTREE :
    s : de type int, numero du sommet actuel
    marq[] : tableau de booleen qui contient les marquages
    col : int qui contient la couleur random
    img : BITMAP*
SORTIE :
    aucune
*/
void Graphe::DFS2(int s, bool marq[], int col, Graphe g,BITMAP* img, std::vector<int>& temp_x1, std::vector<int>& temp_y1, std::vector<int>& temp_x2, std::vector<int>& temp_y2)
{
    //On marque le sommet à true
    marq[s] = true;

    //On met le sommet de la couleur
    //Parmi tous les sommets
    for(int i =0; i<getOrdre(); i++)
    {
        //Si le numéro de sommet correspond
        if(m_vect_som[i].getNumero()==s)
        {
            //std::cout << "Le sommet " << m_vect_som[i].getNumero() << std::endl;
            //On fait un affichage spécial du sommet concerné avec col
            rectfill(img, m_vect_som[i].getCoordX(), m_vect_som[i].getCoordY(),m_vect_som[i].getCoordX()+m_vect_som[i].getImage()->w,m_vect_som[i].getCoordY()+m_vect_som[i].getImage()->h,col);
            temp_x1.push_back(m_vect_som[i].getCoordX());
            temp_x2.push_back(m_vect_som[i].getImage()->w);
            temp_y1.push_back(m_vect_som[i].getCoordY());
            temp_y2.push_back(m_vect_som[i].getImage()->h);
            //std::cout << "OOK" << std::endl;
        }
    }

    //Vecteur contenant les int contenant les numéros des sommets adjacent au sommet actuel
    std::vector<int> adj;

    //Parmi tous les arcs
    for(int i = 0; i< getVectArcs().size(); i++)
    {
        //Si le premier sommet est égal à s
        if(m_vect_arcs[i].getS1().getNumero() == s)
        {
            //On ajoute le deuxième sommet au vecteur d'adjacence
            adj.push_back(m_vect_arcs[i].getS2().getNumero());
        }
    }

    //Pour tous les sommets adjacents
    for(int i = 0; i < adj.size(); i++)
    {
        //S'il n'est pas marqué
        if(!marq[adj[i]])
        {
            //std::cout << "Avant d'entrer dans recursif" << std::endl;
            //On procède à un DFS récursif avec le second DFS
            DFS2(adj[i], marq, col, g, img, temp_x1, temp_y1, temp_x2, temp_y2);
        }
    }

    //std::cout << "Sortie du deuxième DFS" << std::endl;


}





/* k_connexite : sous-programme permettant de trouver la k-connexite du graphe
ENTREE:
    buffer : de type BITMAP*
SORTIE :
    aucune
*/
void Graphe::k_connexite(BITMAP* buffer)
{
    std::cout<<std::endl<<std::endl<<"*** K-CONNEXITE ***"<<std::endl;

    /** INITIALISATION **/
    //Instance de variables nécessaires à l'algorithme
    int verif=0;
    int kmin=0;
    int compt_aff=0;
    std::vector<int> somm_a_eff;
    std::queue<int> file_som;
    int tab[m_ordre];

    //Tant que la file n'est pas vide, on défile
    while(!somm_a_eff.empty())
        somm_a_eff.pop_back();

    //On efface le marquage de tous les sommets
    for(int m=0; m<m_ordre; m++)
        m_vect_som[m].setMarque(false);


    /** S'IL Y A PLUS QUE 2 SOMMETS AFFICHES **/
    //Pour tous les sommets, s'il est affiché on incrémente le compteur de sommets affichés
    for(int i=0; i<m_ordre; i++)
        if(m_vect_som[i].getAffSom()) compt_aff++;

    //Si il y en reste plus de 2
    if(compt_aff >2)
    {

        /** VERIFICATION QUE LE GRAPHE EST BIEN CONNEXE **/
        //Pour tous les sommets
        for(int m=0; m<m_ordre; m++)
        {
            //Si le sommet est affiché et non marqué
            if(!m_vect_som[m].getMarque() && m_vect_som[m].getAffSom())
            {
                //On incrémente le nombre de composantes connexes en effectuant un BFS
                verif++;
                BFS(m);
            }
        }

        //On efface le marquage de tous les sommets
        for(int k=0; k<m_ordre; k++)
            m_vect_som[k].setMarque(false);


        /** SI LE GRAPHE EST BIEN CONNEXE -> DEBUT DE L'ALGORITHME **/
        //Si le graphe est connexe
        if(verif == 1)
        {

            /** VERIFICATION DES SOMMETS CONCERNES PAR L'ALGORITHME == CEUX DEJA AFFICHES **/
            //Pour tous les sommets
            for(int i=0; i<m_ordre; i++)
            {
                //Si le sommet est affiché, la valeur de la case du tableau correspondant à son numéro vaut 0
                if(m_vect_som[i].getAffSom()) tab[i]=0;

                //Sinon elle prend la valeur de 1 et n'est pas considéré pour l'algorithme
                else tab[i]=1;

                //Si le sommet ne fait pas parti de ceux considérés
                if(tab[i]==1)
                {
                    //Pour tous les arcs
                    for(int j=0; j<m_nb_arcs; j++)
                    {
                        //Si ce sommet est l'un des sommets qui constitue l'arc, on efface l'arc
                        if(m_vect_arcs[j].getS1().getNumero() == i || m_vect_arcs[j].getS2().getNumero() == i)
                            m_vect_arcs[j].setAffArc(false);
                    }
                }
            }


            /** DETERMINATION DU DEGRE DE CHAQUE SOMMET CONCERNE **/
            //Instance d'un tableau de degré
            int tab_degre[m_ordre];

            //Pour tous les sommets, si le sommet fait parti de ceux considérés, on initialise son degré à 0
            for(int i=0; i<m_ordre; i++)
                if(tab[i]==0) tab_degre[i]=0;

            //Pour toutes les sommets
            for(int i=0; i<m_ordre; i++)
            {
                //S'il est considéré
                if(tab[i]==0)
                {
                    //Pour tous les arcs
                    for(int j=0; j<m_nb_arcs; j++)
                    {
                        //S'il le sommet constitue un sommet de l'arc, alors on incrémente son degré
                        if(m_vect_arcs[j].getS1().getNumero()==i || m_vect_arcs[j].getS2().getNumero()==i)
                            if(m_vect_arcs[j].getAffArc())
                                tab_degre[i]=tab_degre[i]+1;
                    }
                }
            }


            /** TRI DECROISSANT DES SOMMETS EN FONCTION DE LEUR DEGRE **/
            //Instance de données
            std::vector<int> sommets_tries;
            int temp;

            //Pour tous les sommets, s'il est considéré et affiché, on l'ajoute dans le vecteur de sommets triés
            for(int i=0; i<m_ordre; i++)
                if(tab[i]==0 && m_vect_som[i].getAffSom()) sommets_tries.push_back(i);

            //Pour tous les sommets du vecteur de sommets triés
            for(int j=0; j<sommets_tries.size(); j++)
            {
                //Pour tous les sommets -1 du vecteur de sommets triés
                for(int i=0; i<(sommets_tries.size())-1; i++)
                {
                    //Si le degré du sommet est inférieur au degré du sommet suivant
                    if(tab_degre[sommets_tries[i]] < tab_degre[sommets_tries[i+1]])
                    {
                        //On stocke ce sommet dans un int temporaire
                        temp = sommets_tries[i];

                        //Le sommet suivant prend sa place
                        sommets_tries[i] = sommets_tries[i+1];

                        //Le sommet prend la place du sommet suivant
                        sommets_tries[i+1] = temp;

                    }
                }
            }

            //Affichage des sommets triés en fonction de leur degré décroissant
            std::cout<<"Sommets tries (degre decroissant) :"<<std::endl;

            //Pour tous les sommets triés, on affiche son numéro et son degré
            for(int i=0; i<sommets_tries.size(); i++)
                std::cout<<"S"<<sommets_tries[i]<<" de degre "<<tab_degre[sommets_tries[i]]<<std::endl;

            //Pour tous les sommets triés, on l'ajoute à la file (enfiler)
            for(int i=0; i<sommets_tries.size(); i++)
                file_som.push(sommets_tries[i]);


            /** DANS LA FILE -> CALCUL DE LA CONNEXITE EN EFFACANT 1 OU PLUSIEURS SOMMETS (PLUSIEURS CAS) **/
            //Instance de données
            int sommet_actuel = file_som.front();
            int connexite=0;
            int compt=0;

            //Tant que le graphe est connexe
            while(connexite<=1)
            {
                //On efface le sommet actuel
                m_vect_som[sommet_actuel].setAffSom(false);

                //On défile le sommet actuel
                file_som.pop();

                //Pour tous les sommets
                for(int j=0; j<m_ordre; j++)
                {
                    //Si le sommet est affiché et non marqué
                    if(m_vect_som[j].getAffSom() && !m_vect_som[j].getMarque())
                    {
                        //On incrémente le nombre de composantes connexes en effectuant un BFS
                        connexite++;
                        BFS(j);
                    }
                }

                //Si la file n'est pas vide et que le graphe est connexe
                if(!file_som.empty() && connexite<=1)
                {
                    //On remet la connexité à 0
                    connexite=0;

                    //Pour tous les sommets, on efface le marquage
                    for(int m=0; m<m_ordre; m++)
                        m_vect_som[m].setMarque(false);

                    //On affiche le sommet actuel
                    m_vect_som[sommet_actuel].setAffSom(true);

                    //Le sommet_actuel devient le premier sommet de la file
                    sommet_actuel=file_som.front();
                }

                //Si la file n'est pas vide et que le graphe est non connexe --> ARRÊT DU PROGRAMME
                if(!file_som.empty() && connexite>1)
                {
                    //Tant que la file n'est pas vide, on défile
                    while(!file_som.empty())
                        file_som.pop();
                }

                //Si la file est vide mais que le graphe est connexe
                if(file_som.empty() && connexite==1)
                {
                    //Le sommet actuel est affiché
                    m_vect_som[sommet_actuel].setAffSom(true);

                    //On incrémente le compteur
                    compt++;

                    //Pour tous les sommets triés, on les enfile
                    for(int i=0; i<sommets_tries.size(); i++)
                        file_som.push(sommets_tries[i]);

                    //Pour i allant de 0 au compteur
                    for(int k=0; k<compt; k++)
                    {
                        //Le sommet actuel est le premier sommet de la file
                        sommet_actuel=file_som.front();

                        //On efface le sommet actuel
                        m_vect_som[sommet_actuel].setAffSom(false);

                        //On défile
                        file_som.pop();
                    }

                    //Le sommet actuel prend la valeur du premier sommet de la file
                    sommet_actuel=file_som.front();

                    //Pour tous les sommets, s'il est marqué, on efface son marquage
                    for(int lk=0; lk<m_ordre; lk++)
                        if(m_vect_som[lk].getMarque()) m_vect_som[lk].setMarque(false);

                    //La connexite vaut 0
                    connexite=0;
                }
            }

            //Pour tous les sommets
            for(int i=0; i<m_ordre; i++)
            {
                //S'il est effacé et considéré
                if(!m_vect_som[i].getAffSom() && tab[i]==0)
                {
                    //On incrémente kmin et on l'ajoute au vecteur des sommets à effacer
                    kmin++;
                    somm_a_eff.push_back(i);
                }
            }


            /** AFFICHAGE DU RESULTAT DE L'ALGORITHME **/
            std::cout<<"Le graphe est "<<kmin<<"-connexe et contient "<<connexite<<" composantes connexes."<<std::endl;
            std::cout<<"Il faut supprimer "<<somm_a_eff.size()<<" sommet(s)."<<std::endl;

            //Pour tous les sommets à effacer, on affiche son numéro
            for(int i=0; i<somm_a_eff.size(); i++)
                std::cout<<"Le sommet "<<somm_a_eff[i]<<" doit etre efface."<<std::endl;

            std::cout<<std::endl;

            //Affichage temporaire du résultat
            affichage_k_connexite();
            rest(3000);

            //Pour tous les sommets, s'il est considéré, on l'affiche
            for(int k=0; k<m_ordre; k++)
                if(tab[k] != 1) m_vect_som[k].setAffSom(true);
        }

        //Sinon, le graphe est déjà non connexe
        else std::cout<<"Le graphe n'est deja non-connexe."<<std::endl;
    }


    //Sinon, s'il reste 2 sommets
    else
    {
        std::cout<<"Meme en supprimant un sommet, le graphe sera connexe."<<std::endl;
        std::cout<<"On ne peut pas effectuer l'algorithme de k-connexite."<<std::endl<<std::endl;
    }
}





/* affichage_k_connexite : sous-programme permettant d'afficher les nouvelles composantes connexes
après suppression d'un/de plusieurs sommet(s)
ENTREE:
    aucune
SORTIE :
    aucune
*/
void Graphe::affichage_k_connexite()
{

    //Instance d'un vecteur de int
    std::vector<int> compteur;

    //Initialisation du vecteur à 0 pour tous les arcs
    for(int i=0; i<m_nb_arcs; i++)
    {
        compteur.push_back(0);
    }

    //Affichage d'un rectangle blanc sur l'écran
    rectfill(screen, 126, 5, 1019, 763, makecol(255,255,255));

    //Pour tous les sommets du graphe
    for(int i=0; i<getOrdre(); i++)
    {
        //Si ce sommet est affiché
        if(m_vect_som[i].getAffSom())
        {
            //On affiche sa BITMAP
            draw_sprite(screen, (getVectSom()[i]).getImage(), (getVectSom()[i]).getCoordX(), (getVectSom()[i]).getCoordY());

            //n prend la valeur du numéro du sommet
            int n = (getVectSom()[i]).getNumero();

            //On affiche le numéro du sommet au-dessus de son image
            textprintf(screen,font, (getVectSom()[i]).getCoordX()+20, (getVectSom()[i]).getCoordY()-20, makecol(0,0,0), "Sommet n_%d", n);

            //Pour tous les arcs
            for(int j=0; j<m_nb_arcs; j++)
            {
                //Si le sommet i est égale au sommet 1 de l'arc
                if(i == m_vect_arcs[j].getS1().getNumero())
                {
                    //On incrémente le compteur
                    compteur[j] = compteur[j] + 1;
                }

                //Si le sommet i est égale au sommet 2 de l'arc
                else if(i == m_vect_arcs[j].getS2().getNumero())
                {
                    //On incrémente de le compteur
                    compteur[j] = compteur[j] + 1;
                }
            }

            //Pour tous les arcs
            for(int j=0; j<m_nb_arcs; j++)
            {
                //Si le compteur de cet arc vaut 2 = si ses 2 sommets sont affichés
                if(compteur[j] == 2)
                {
                    //Alors l'arc est affiché
                    m_vect_arcs[j].setAffArc(true);
                    m_vect_arcs[j].afficher_arc(screen);
                }
            }
        }
    }
}






/* BFS : sous-programme permettant de marquer tous les sommets faisant parti de la même composante connexe
ENTREE:
    sommet_initial : de type int
SORTIE :
    aucune
*/
void Graphe::BFS(int sommet_initial)
{

    //DONNEES
    //Une file d'attente
    std::queue<int> file;

    //INITIALISATION
    //On "efface" le sommet de départ
    m_vect_som[sommet_initial].setMarque(true);

    //On enfile le sommet de départ
    file.push(sommet_initial);



    //BOUCLE
    //Tant que la file n'est pas vide
    while(!file.empty())
    {

        //On défile le premier sommet
        int Sommet_actuel = file.front();
        file.pop();


        //Pour chacun des sommets
        for(int i=0; i<m_ordre; i++)
        {

            //Si le sommet i est affiché
            if(m_vect_som[i].getAffSom())
            {

                //Si il est non marqué
                if(!m_vect_som[i].getMarque())
                {

                    //Pour tous les arcs
                    for(int j=0; j<m_nb_arcs; j++)
                    {

                        //Si l'arc est affiché
                        if(m_vect_arcs[j].getAffArc())
                        {


                            if(m_vect_arcs[j].getS1().getNumero() == Sommet_actuel && m_vect_arcs[j].getS2().getNumero() == i)
                            {
                                //m_vect_som[i].setAffSom(false);
                                m_vect_som[i].setMarque(true);
                                file.push(i);
                            }

                            else if(m_vect_arcs[j].getS1().getNumero() == i && m_vect_arcs[j].getS2().getNumero() == Sommet_actuel)
                            {
                                //m_vect_som[i].setAffSom(false);
                                m_vect_som[i].setMarque(true);
                                file.push(i);
                            }
                        }
                    }
                }
            }
        }
    }
}
