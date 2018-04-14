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
Graphe::Graphe(int _ordre, int _nb_arcs, std::vector<Sommet> _vect_som, std::vector<Arc> _vect_arcs, int _nb_mois)
    :m_ordre(_ordre), m_nb_arcs(_nb_arcs), m_vect_som(_vect_som), m_vect_arcs(_vect_arcs),m_nb_mois(_nb_mois), m_nb_mois_temp(0)
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




void Graphe::lecture_fichier(std::string f)
{
    ifstream fichier;
    fichier.open(f);

    //Initialisation des variables nécessaires à la lecture du fichier
    BITMAP* image;
    int ordre, nb_arcs, nb_mois;
    int num, n, x, y;
    int s1, s2;
    bool b1,b2, b3;
    float coeff;
    float r;
    std::string nom, nom_img;
    std::vector<Sommet> vec_som;
    std::vector<Arc> vec_arc;

    if(fichier)
    {

        //On lit l'ordre
        fichier>> nb_mois;
        setNbMoisTemp(nb_mois);
        setNbMois(nb_mois);
        fichier >> ordre;
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

            nom_img = nom + ".bmp";
            image = load_bitmap(nom_img.c_str(),NULL);
            if (!image)
            {
                allegro_message("prb allocation BITMAP ");
                allegro_exit();
                exit(EXIT_FAILURE);
            }

            //On crée le sommet et on l'ajoute au vecteur de sommet
            Sommet s(nom, num, n, 0, r, x, y, image, b1, b2, false, n, 0,b1, b3);
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

            //On calcule le coefficient de l'arc que l'on crée ensuite
            coeff = (float)(vec_som[s1].getN())/(vec_som[s2].getN());
            Arc a(vec_som[s1], vec_som[s2], coeff, true, coeff);
            //On peut à présent calculer le K des sommets du graphe
            vec_som[s2].setK(vec_som[s2].getK() + vec_som[s1].getN()*coeff);
            vec_som[s2].setKTemp(vec_som[s2].getK() + vec_som[s1].getN()*coeff);
            //on entre tous les arcs dans un vecteur d'arcs
            vec_arc.push_back(a);

        }
        //On remplit les vecteurs du graphe
        setVectSom(vec_som);
        setVectArcs(vec_arc);

        //On affiche en console le graphe
        std::cout<<"\n\nGraphe :"<<std::endl;
        std::cout<<"\nOrdre : "<<getOrdre()<<std::endl;
        std::cout<<"NB Arcs : "<<getNbArcs()<<"\n"<<std::endl;
        for(int i =0; i < getOrdre(); i++)
        {
            if(vec_som[i].getK()<=0)
            {
                vec_som[i].setK(1000000);
                vec_som[i].setKTemp(1000000);
                setVectSom(vec_som);
            }
            std::cout<<((getVectSom())[i]).getName()<<" "<<((getVectSom())[i]).getN()<<" "<<((getVectSom())[i]).getK()<<" "<<((getVectSom())[i]).getR()<<" "<<((getVectSom())[i]).getCoordX()<<" "<<((getVectSom())[i]).getCoordY()<<std::endl;
        }
        std::cout<<"\n\n";
        for(int i=0; i<getNbArcs(); i++)
        {

            std::cout<<"Arc "<<(i+1)<<" : "<<((getVectArcs())[i]).getS1().getNumero()<< " et "<<((getVectArcs())[i]).getS2().getNumero()<<" coeff "<<((getVectArcs())[i]).getCoef()<<std::endl;
        }

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
    bool b1, b2, b3;
    if(fichier)
    {
        //On sauvegarde le mois
        fichier << getNbMois() << std::endl;

        //On sauvegarde l'ordre
        fichier << getOrdre() << std::endl;

        for(int i =0; i<getOrdre(); i++)
        {

            if((getVectSom()[i]).getAffSom() == 1) b1 =1;
            else b1 = 0;

            if((getVectSom()[i]).getSelect() == 1) b2 =1;
            else b2 = 0;
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
            fichier << std::endl;
        }


        fichier<<getNbArcs()<<std::endl;


        for(int i = 0; i<getNbArcs(); i++)
        {
            fichier << (getVectArcs()[i]).getS1().getNumero();
            fichier << " ";
            fichier << (getVectArcs()[i]).getS2().getNumero();
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
        Sommet s((getVectSom()[som]).getName(), (getVectSom()[som]).getNumero(), (getVectSom()[som]).getN(), nouv, (getVectSom()[som]).getR(), (getVectSom()[som]).getCoordX(), (getVectSom()[som]).getCoordY(), (getVectSom()[som]).getImage(), (getVectSom()[som]).getAffSom(), (getVectSom()[som]).getSelect(),(getVectSom()[som]).getMarque(),(getVectSom()[som]).getN(),nouv,(getVectSom()[som]).getAffSomTemp(),(getVectSom()[som]).getVeget() );

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
        Sommet s((getVectSom()[som]).getName(), (getVectSom()[som]).getNumero(), nouv, (getVectSom()[som]).getK(), (getVectSom()[som]).getR(), (getVectSom()[som]).getCoordX(), (getVectSom()[som]).getCoordY(), (getVectSom()[som]).getImage(), (getVectSom()[som]).getAffSom(), (getVectSom()[som]).getSelect(),(getVectSom()[som]).getMarque(),nouv, (getVectSom()[som]).getKTemp(),(getVectSom()[som]).getAffSomTemp(),(getVectSom()[som]).getVeget());

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
        Sommet s((getVectSom()[som]).getName(), (getVectSom()[som]).getNumero(), (getVectSom()[som]).getN(), (getVectSom()[som]).getK(), nouv, (getVectSom()[som]).getCoordX(), (getVectSom()[som]).getCoordY(), (getVectSom()[som]).getImage(), (getVectSom()[som]).getAffSom(), (getVectSom()[som]).getSelect(),(getVectSom()[som]).getMarque(), (getVectSom()[som]).getN(),(getVectSom()[som]).getK(),(getVectSom()[som]).getAffSomTemp(),(getVectSom()[som]).getVeget());

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
    //Si il refuse, on redonne au N, K, R, du sommet leur valeur initiale et on repart du mois 0.
    if(choix == 0)
    {
        for(int i =0; i<getOrdre(); i++)
        {
            n = vec_s[i].getNTemp();
            k = vec_s[i].getKTemp();
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
               // masked_blit(img, (getVectSom()[i]).getImage(),(getVectSom()[i]).getCoordX(), (getVectSom()[i]).getCoordY(), (getVectSom()[i]).getCoordX(), (getVectSom()[i]).getCoordY(), (getVectSom()[i]).getImage()->w, (getVectSom()[i]).getImage()->h);

                //n prend la valeur du numéro du sommet
                n = (getVectSom()[i]).getNumero();

                //r prend la valeur de son R arrondie à l'entier
                r = int(getVectSom()[i].getR());

                //On affiche ses paramètres K, R et N
                textprintf(img,font, (getVectSom()[i]).getCoordX()+20, (getVectSom()[i]).getCoordY()+ getVectSom()[i].getImage()->h, makecol(0,0,0) ,"Population %d",getVectSom()[i].getN() );
                textprintf(img,font, (getVectSom()[i]).getCoordX()+20, (getVectSom()[i]).getCoordY()+ getVectSom()[i].getImage()->h + 20, makecol(0,0,0) ,"K : %d",getVectSom()[i].getK() );
                textprintf(img,font, (getVectSom()[i]).getCoordX()+20, (getVectSom()[i]).getCoordY()+ getVectSom()[i].getImage()->h + 40, makecol(0,0,0) ,"R : %d",r );

                //On affiche le numéro du sommet au-dessus de son image
                textprintf(img,font, (getVectSom()[i]).getCoordX()+20, (getVectSom()[i]).getCoordY()-20, makecol(0,0,0), "Sommet n_%d", n);

                //Affichage d'un rectangle autour de l'image du sommet
                //Si le sommet est sélectionné
                if(getVectSom()[i].getSelect()) rect(screen, getVectSom()[i].getCoordX(), getVectSom()[i].getCoordY(), getVectSom()[i].getCoordX()+ getVectSom()[i].getImage()->w, getVectSom()[i].getCoordY()+getVectSom()[i].getImage()->h, makecol(0,255,0));
                //Sinon
                else rect(screen, getVectSom()[i].getCoordX(), getVectSom()[i].getCoordY(), getVectSom()[i].getCoordX()+ getVectSom()[i].getImage()->w, getVectSom()[i].getCoordY()+getVectSom()[i].getImage()->h, makecol(0,0,0));


           }
            //On affiche le mois auquel on est en haut à droite de l'écran
            textprintf(img,font, SCREEN_W - 100, 20 , makecol(0,0,0) ,"Mois n_%d",getNbMois() );

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

    //Modifications des vecteurs de sommets et d'arcs du graphe
    setVectSom(vec_som);
    //setVectArcs(vec_arc);

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



/*temps reel : sous-programme permettant d'afficher en temps reel l'evolution du réseau écologique
ENTREE : deux images (le fond et le buffer) et un compteur (un entier)
SORTIE : Aucune
*/
void Graphe::temps_reel(BITMAP* img, BITMAP* img2, int compt)
{
    //On crée un vecteur de sommet et un vecteur d'arcs ainsi qu'un vecteur d'entier
    std::vector<Sommet> vec_som = getVectSom();
    std::vector<Arc> vec_arc = getVectArcs();
    std::vector<int> vegetation;
    //On crée deux booléens
    bool s = true;
    bool regen_veget = false;
    //3 entiers;
    int new_n, new_k, nb_mois;
    new_k = 0;
    //1 float
    float new_coef;

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
        //Si l'espèce n'est pas disparue
        if(vec_som[i].getN()!=0)
            {
            //On calcule une partie de sa population à t+1 ( Nt+1 = Nt + Nt*r(1- N/K)
            new_n = vec_som[i].getN() +(int)((vec_som[i].getN() * vec_som[i].getR())*(1 - (vec_som[i].getN() / vec_som[i].getK())));
            //On parcourt les arcs
            for(int j =0; j<getNbArcs(); j++)
            {
                // si le sommet actuel est un végétal, on entre le numéro de l'arc dans son vecteur végétation
                if(vec_som[i].getVeget()==true)
                {
                    if(i == vec_arc[j].getS1().getNumero())  vegetation.push_back(vec_arc[j].getS2().getNumero());
                }

                //on termine le calcul de la population à t+1 selon si ses prédecesseurs et ses successeurs
                if(i == vec_arc[j].getS2().getNumero() && vec_arc[j].getS1().getN() != 0) new_n = new_n + (vec_arc[j].getCoef() * vec_arc[j].getS1().getN());
                else if(i == vec_arc[j].getS1().getNumero() && vec_arc[j].getS2().getN() != 0)
                {
                    new_n = new_n - (vec_arc[j].getCoef() * vec_arc[j].getS2().getN());
                }
            }
            //Si la nouvelle population d'une espèce est nulle alors on ne l'affiche plus
            if(new_n<=0)
            {
                new_n = 0;
                vec_som[i].setAffSom(false);
            }
            else vec_som[i].setAffSom(true);
        }

        //Si l'espèce est un végétal, que ce n'est pas le premier mois et que sa population est inférieure ou égale à 0
        if((vec_som[i].getVeget()==true) && (compt> 0)&&(vec_som[i].getN()<=0))
        {
            //On parcourt son vecteur de végétation
            // Si tous leur k est supérieure d'au moins 100 à leur population alors la regen_veget devient vrai
            for(int k = 0; k<vegetation.size(); k++)
            {
                if(vec_som[vegetation[k]].getN() >= vec_som[vegetation[k]].getK()) regen_veget = false;
                else regen_veget = true;
            }
            //Si finalement après avoir regardé tous les successeurs, la regen_veget est vraie alors sa population passe à 1000
            if (regen_veget == true)
            {
                vec_som[i].setN(100);
                vec_som[i].setAffSom(true);
            }
            //else vec_som[i].setN(new_n);
        }
        //Sinon
        else vec_som[i].setN(new_n);
    }
    for(int j =0; j<getNbArcs(); j++)
    {
        new_coef = (float)(vec_arc[j].getS1().getN())/(vec_arc[j].getS2().getN());
        new_k= (new_coef*vec_arc[j].getS2().getN() + vec_som[vec_arc[j].getS2().getNumero()].getK());
        vec_arc[j].setCoef(new_coef);
        vec_som[vec_arc[j].getS2().getNumero()].setK(new_k);

        if(vec_som[vec_arc[j].getS1().getNumero()].getAffSom() == false && vec_som[vec_arc[j].getS1().getNumero()].getAffSom() == false) vec_arc[j].setAffArc(false);
        else vec_arc[j].setAffArc(true);
    }
    for(int i=0; i<getOrdre(); i++)
    {
        if(vec_som[i].getK()==0) vec_som[i].setK(1000000);
    }

    //On parcourt le vecteur de sommet.
    //Si il est supprimé alors sa population devient nulle
    for(int i =0; i<getOrdre(); i++)
    {
        if(vec_som[i].getAffSom()==false) vec_som[i].setN(0);
        if(vec_som[i].getN() == 0) vec_som[i].setAffSom(false);
        else vec_som[i].setAffSom(true);
    }


    nb_mois = getNbMois();
    setNbMois(nb_mois+1);
    setVectSom(vec_som);
    setVectArcs(vec_arc);
    clear_bitmap(img2);
    blit(img, img2, 0,0,0,0,1024,768);
    afficher_console();
    afficher_sommets(img2);
    blit(img2,screen,0,0,0,0,1024,768);

  //  return s;
}




/*temps reel : sous-programme permettant d'afficher en temps reel l'evolution du réseau écologique
ENTREE : deux images (le fond et le buffer) et un compteur (un entier)
SORTIE : Aucune
*/
/*void Graphe::temps_reel(BITMAP* img, BITMAP* img2, int compt)
{
    //On crée un vecteur de sommet et un vecteur d'arcs ainsi qu'un vecteur d'entier
    std::vector<Sommet> vec_som = getVectSom();
    std::vector<Arc> vec_arc = getVectArcs();
    std::vector<int> vegetation;
    //On crée deux booléens
    bool s = true;
    bool regen_veget = false;
    //3 entiers;
    int new_n, new_k, nb_mois;
    new_k = 0;
    //1 float
    float new_coef;

    //On parcourt le vecteur de sommet.
    //Si il est supprimé alors sa population devient nulle
    for(int i =0; i<getOrdre(); i++)
    {
        if(vec_som[i].getAffSom()==false) vec_som[i].setN(0);
        if(vec_som[i].getN() == 0) vec_som[i].setAffSom(false);
    }
    //On parcourt tous les sommets
    for(int i =0; i<getOrdre(); i++)
    {
        //Si l'espèce n'est pas disparue
        if(vec_som[i].getN()!=0)
            {
            //On calcule une partie de sa population à t+1 ( Nt+1 = Nt + Nt*r(1- N/K)
            new_n = vec_som[i].getN() +(int)((vec_som[i].getN() * vec_som[i].getR())*(1 - (vec_som[i].getN() / vec_som[i].getK())));
            //On parcourt les arcs
            for(int j =0; j<getNbArcs(); j++)
            {
                // si le sommet actuel est un végétal, on entre le numéro de l'arc dans son vecteur végétation
                if(vec_som[i].getVeget()==true)
                {
                    if(i == vec_arc[j].getS1().getNumero())  vegetation.push_back(vec_arc[j].getS2().getNumero());
                }

                //on termine le calcul de la population à t+1 selon si ses prédecesseurs et ses successeurs
                if(i == vec_arc[j].getS2().getNumero() && vec_arc[j].getS1().getN() != 0) new_n = new_n + (vec_arc[j].getCoef() * vec_arc[j].getS1().getN());
                else if(i == vec_arc[j].getS1().getNumero() && vec_arc[j].getS2().getN() != 0)
                {
                    new_n = new_n - (vec_arc[j].getCoef() * vec_arc[j].getS2().getN());
                }
            }
            //Si la nouvelle population d'une espèce est nulle alors on ne l'affiche plus
            if(new_n<=0)
            {
                new_n = 0;
                vec_som[i].setAffSom(false);
            }
            else vec_som[i].setAffSom(true);
        }

        //Si l'espèce est un végétal, que ce n'est pas le premier mois et que sa population est inférieure ou égale à 0
        if((vec_som[i].getVeget()==true) && (compt> 0)&&(vec_som[i].getN()<=0))
        {
            //On parcourt son vecteur de végétation
            // Si tous leur k est supérieure d'au moins 100 à leur population alors la regen_veget devient vrai
            for(int k = 0; k<vegetation.size(); k++)
            {
                if(vec_som[vegetation[k]].getN() >= vec_som[vegetation[k]].getK()) regen_veget = false;
                else regen_veget = true;
            }
            //Si finalement après avoir regardé tous les successeurs, la regen_veget est vraie alors sa population passe à 1000
            if (regen_veget == true)
            {
                vec_som[i].setN(100);
                vec_som[i].setAffSom(true);
            }
            //else vec_som[i].setN(new_n);
        }
        //Sinon
        else vec_som[i].setN(new_n);
    }
    for(int j =0; j<getNbArcs(); j++)
    {
        new_coef = (float)(vec_arc[j].getS1().getN())/(vec_arc[j].getS2().getN());
        new_k= (new_coef*vec_arc[j].getS2().getN() + vec_som[vec_arc[j].getS2().getNumero()].getK());
        vec_arc[j].setCoef(new_coef);
        vec_som[vec_arc[j].getS2().getNumero()].setK(new_k);

        if(vec_som[vec_arc[j].getS1().getNumero()].getAffSom() == false && vec_som[vec_arc[j].getS1().getNumero()].getAffSom() == false) vec_arc[j].setAffArc(false);
        else vec_arc[j].setAffArc(true);
    }
    for(int i=0; i<getOrdre(); i++)
    {
        if(vec_som[i].getK()==0) vec_som[i].setK(1000000);
    }

    nb_mois = getNbMois();
    setNbMois(nb_mois+1);
    setVectSom(vec_som);
    setVectArcs(vec_arc);
    clear_bitmap(img2);
    blit(img, img2, 0,0,0,0,1024,768);
    afficher_console();
    afficher_sommets(img2);
    blit(img2,screen,0,0,0,0,1024,768);

  //  return s;
}
*/





/// Source : https://www.geeksforgeeks.org/strongly-connected-components/
//A appliquer à chaque graphe pour voir les composantes connexes
/* forte_co : sous-programme permettant de trouver les composantes connexes
ENTREE :
    g = le graphe dont on souhaite connaître les composantes fortement connexes
    img = BITMAP*
SORTIE :
    aucune
*/
void Graphe::forte_co(Graphe g, BITMAP* img)
{
    std::cout << "Debut forte co" << std::endl;
    //Pile de int ou de sommet
    std::stack<int> pile;

    //On crée un tableau de booleens de taille ordre qui sert de tableau de marquage
    bool marq[getOrdre()];
    //On l'initialise à false pour le premier DFS
    for(int i =0; i<getOrdre(); i++)
    {
        //On le met à faux
        marq[i]=false;
    }

    std::cout << "premiers false ok" << std::endl;

    ///DFS prob
    //Pour toutes les cases du tableau de marquage
    for(int i = 0; i<getOrdre(); i++)
    {
        //S'il n'est pas marqué
        if(marq[i]==false)
        {
            std::cout << "Avant entree DFS" << std::endl;
            // On procède à un premier DFS
            DFS1(i, marq, pile);
            std::cout << "premier DFS OK" << std::endl;
        }
    }

    //On initialise un vecteur d'arcs qui va recevoir les arcs inversés
    std::vector<Arc> vect_arc;

    //On inverse les sens de tous les arcs
    for(int i= 0; i<m_vect_arcs.size(); i++)
    {
        //On crée un arc partiel qui reçoit le sommet 2 en guise de sommet 1 et inversement
        Arc atemp(m_vect_arcs[i].getS2(),m_vect_arcs[i].getS1(),m_vect_arcs[i].getCoef(), m_vect_arcs[i].getAffArc(), m_vect_arcs[i].getCoefTemp());
        // On met cet arc dans le vecteur d'arcs
        vect_arc.push_back(atemp);
    }

    //On crée un graphe qui va avoir les arcs inversés
    //Il possède les mêmes propriétés que le graphe actuel sauf que ses arcs sont inversés
    Graphe g_inv(getOrdre(),getNbArcs(),getVectSom(),vect_arc, getNbMois());

    //Le graphe prend les arcs inversés
    //m_vect_arcs=vect_arc;

    std::cout << "arcs inverses" << std::endl;

    //On l'initialise à false pour le second DFS
    for(int i =0; i<getOrdre(); i++)
    {
        //On le met à faux
        marq[i]=false;
    }

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
            //On fait appel au deuxième DFS
            g_inv.DFS2(s,marq,col,g, img);
            std::cout << "Sortie effectuée du 2eme DFS" << std::endl;
        }
    }


    std::cout << "Fin forte compo" << std::endl;
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
    std::cout << "Entree dans DFS réussie" <<std::endl;
    //On marque le sommet reçu en paramètres
    marq[s] = true;

    //Vecteur contenant les int contenant les numéros des sommets adjacent au sommet actuel
    std::vector<int> adj;

    //Parmi tous les arcs
    for(int i = 0; i< getVectArcs().size(); i++)
    {
        std::cout << "Arc : " << i << std::endl;

        //Si le premier sommet est égal à s
        if(m_vect_arcs[i].getS1().getNumero() == s)
        {
            //On ajoute le deuxième sommet au vecteur d'adjacence
            adj.push_back(m_vect_arcs[i].getS2().getNumero());
            std::cout << "Sommet " << m_vect_arcs[i].getS2().getNumero() << std::endl;
        }
    }


    //Pour tous les sommets adjacents
    for(int i = 0; i < adj.size(); i++)
    {
        std::cout << "Sommet adjacent numéro " << adj[i] <<std::endl;
        //S'il n'est pas marqué
        if(!marq[adj[i]])
        {
            //On procède à un DFS récursif avec le premier DFS
            std::cout << "Avant d'entrer dans recursive " << std::endl;
            DFS1(adj[i], marq, pile);
        }
    }

    //On met s dans la pile
    pile.push(s);

    std::cout <<"Sur le point de sortir du DFS" << std::endl;
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
void Graphe::DFS2(int s, bool marq[], int col, Graphe g,BITMAP* img)
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
            std::cout << "Le sommet " << m_vect_som[i].getNumero() << std::endl;
            //On fait un affichage spécial du sommet concerné avec col
            rectfill(img, m_vect_som[i].getCoordX(), m_vect_som[i].getCoordY(),m_vect_som[i].getCoordX()+130,m_vect_som[i].getCoordY()+130,col);
            std::cout << "OOK" << std::endl;
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
            std::cout << "Avant d'entrer dans recursif" << std::endl;
            //On procède à un DFS récursif avec le second DFS
            DFS2(adj[i], marq, col, g, img);
        }
    }

    std::cout << "Sortie du deuxième DFS" << std::endl;
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

            //Pour tous les sommets, on affiche son nom et son degré
            for(int i=0; i<m_ordre; i++)
                if(tab[i]==0) std::cout<<"S"<<i<<" de degre "<<tab_degre[i]<<std::endl;


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
