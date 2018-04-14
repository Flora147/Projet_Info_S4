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




void Graphe::lecture_fichier(std::string f)
{
    ifstream fichier;
    fichier.open(f);

    //Initialisation des variables nécessaires à la lecture du fichier
    BITMAP* image;
    int ordre, nb_arcs;
    int num, n, k, x, y;
    int s1, s2;
    bool b1,b2;
    float coeff;
    float r;
    char *img;
    std::string nom, nom_img;
    std::vector<Sommet> vec_som;
    std::vector<Arc> vec_arc;
    k = 0;

    if(fichier)
    {

        //On lit l'ordre
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

            nom_img = nom + ".bmp";
            image = load_bitmap(nom_img.c_str(),NULL);
            if (!image)
            {
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
                vec_som[i].setK(1000);
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

void Graphe::sauvegarde_fichier(std::string f)
{
    afficher_console();
    ofstream fichier;
    fichier.open(f);
    bool b1, b2;
    if(fichier)
    {
        //On sauvegarde l'ordre
        fichier << getOrdre() << std::endl;

        for(int i =0; i<getOrdre(); i++)
        {

            if((getVectSom()[i]).getAffSom() == true) b1 =1;
            else b1 = 0;

            if((getVectSom()[i]).getSelect() == true) b2 =1;
            else b2 = 0;

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
    }else std::cout << "Erreur fichier sauvegarde..." << std::endl << std::endl;

}
/*modifier_param : sous-programme permettant de choisir un sommet et d'en modifier un paramètre
ENTREE : Aucune
SORTIE : Aucune
*/
///Modification d'un paramètre d'un sommet
void Graphe::modifier_param()
{
    std::string choix, nouv_nom;
    int som, nouv;
    std::vector<Sommet> vec_som;

    //Saisie du sommet à modifier
    std::cout<<"Quel Sommet souhaitez vous modifier ? (numero) "<<std::endl;
    std::cin>>som;
    //Blindage
    while(som<0 || som>getVectSom().size())
    {
        std::cout<<"Mauvaise saisie du sommet à modifier. Veuillez recommencer. (numero)"<<std::endl;
        std::cin>>som;
    }

    //Saisie du paramètre à changer
    std::cout<<"Lequel de ces parametres souhaitez vous modifier ?(nom, K, R, N)"<<std::endl;
    std::cin>>choix;
    //Blindage
    while(choix!="nom" && choix!= "K" && choix!="R" && choix!="N")
    {
        std::cout<<"Mauvaise saisie du choix. Veuillez recommencer. (K, R, N)"<<std::endl;
        std::cin>>choix;
    }

    //Si on choisit de modifier K
    //On crée un sommet avec les mêmes propriétés que celui à modier sauf K qui a été actualisé
    //On l'intègre au vecteur de sommet
    //De même si le choix est N, R ou nom
    if(choix=="K")
    {
        std::cout<<"K actuel pour "<<(getVectSom()[som]).getName()<<" : "<<(getVectSom()[som]).getK()<<std::endl;
        std::cout<<"Saisir nouveau K"<<std::endl;
        std::cin>>nouv;
        Sommet s((getVectSom()[som]).getName(), (getVectSom()[som]).getNumero(), (getVectSom()[som]).getN(), nouv, (getVectSom()[som]).getR(), (getVectSom()[som]).getCoordX(), (getVectSom()[som]).getCoordY(), (getVectSom()[som]).getImage(), (getVectSom()[som]).getAffSom(), (getVectSom()[som]).getSelect());
        for(int i=0; i<getOrdre(); i++)
        {
            if (i==som) vec_som.push_back(s);
            else vec_som.push_back(getVectSom()[i]);
        }
    }
    if(choix=="N")
    {
        std::cout<<"N actuel pour "<<(getVectSom()[som]).getName()<<" : "<<(getVectSom()[som]).getN()<<std::endl;
        std::cout<<"Saisir nouveau N"<<std::endl;
        std::cin>>nouv;
        Sommet s((getVectSom()[som]).getName(), (getVectSom()[som]).getNumero(), nouv, (getVectSom()[som]).getK(), (getVectSom()[som]).getR(), (getVectSom()[som]).getCoordX(), (getVectSom()[som]).getCoordY(), (getVectSom()[som]).getImage(), (getVectSom()[som]).getAffSom(), (getVectSom()[som]).getSelect());
        for(int i=0; i<getOrdre(); i++)
        {
            if (i==som) vec_som.push_back(s);
            else vec_som.push_back(getVectSom()[i]);
        }
        calcul_para_post_modif(vec_som);

    }
    if(choix=="R")
    {
        std::cout<<"R actuel pour "<<(getVectSom()[som]).getName()<<" : "<<(getVectSom()[som]).getR()<<std::endl;
        std::cout<<"Saisir nouveau R"<<std::endl;
        std::cin>>nouv;
        Sommet s((getVectSom()[som]).getName(), (getVectSom()[som]).getNumero(), (getVectSom()[som]).getN(), (getVectSom()[som]).getK(), nouv, (getVectSom()[som]).getCoordX(), (getVectSom()[som]).getCoordY(), (getVectSom()[som]).getImage(), (getVectSom()[som]).getAffSom(), (getVectSom()[som]).getSelect());
        for(int i=0; i<getOrdre(); i++)
        {
            if (i==som) vec_som.push_back(s);
            else vec_som.push_back(getVectSom()[i]);
        }

    }
    setVectSom(vec_som);
    afficher_console();
}

/*calcul_para_post_modif : sous programme permettant de modifier le coefficient et le K des sommets après avoir modifier leur N
ENTREE : un vecteur de sommet vec_som
SORTIE : Aucune
*/
void Graphe::calcul_para_post_modif(std::vector<Sommet> vec_som)
{
    float coeff;
    std::vector<Arc> vec_arc;
    vec_arc = getVectArcs();
    int s1, s2;
    for(int i =0; i<getNbArcs(); i++)
    {
        s1 = getVectArcs()[i].getS1().getNumero();
        s2 = getVectArcs()[i].getS2().getNumero();
        //On calcule le nouveau coefficient
        coeff = (float)(vec_som[s1].getN())/(vec_som[s2].getN());
        //On peut à présent calculer le K des sommets du graphe
        vec_som[s2].setK(vec_som[s2].getK() + vec_som[s1].getN()*coeff);
        vec_arc[i].setCoef(coeff);
    }
    setVectArcs(vec_arc);
    setVectSom(vec_som);
}

/*afficher console : sous programme permettant d'afficher le graphe en console
ENTREE : Aucune
SORTIE : Aucune
*/
void Graphe::afficher_console()
{
    ///Affichage Console des paramètre de tous les sommets
    std::cout<<"\n\nGraphe :"<<std::endl;
    std::cout<<"\nOrdre : "<<getOrdre()<<std::endl;
    std::cout<<"NB Arcs : \n"<<getNbArcs()<<std::endl;
    for(int i =0; i < getOrdre(); i++)
    {
        std::cout<<((getVectSom())[i]).getName()<<" "<<((getVectSom())[i]).getN()<<" "<<((getVectSom())[i]).getK()<<" "<<((getVectSom())[i]).getR()<<" "<<((getVectSom())[i]).getCoordX()<<" "<<((getVectSom())[i]).getCoordY()<<std::endl;
    }
    std::cout<<"\n\n";
    for(int i=0; i<getNbArcs(); i++)
    {
        std::cout<<"Arc "<<(i+1)<<" : "<<((getVectArcs())[i]).getS1().getNumero()<< " et "<<((getVectArcs())[i]).getS2().getNumero()<<" coeff "<<((getVectArcs())[i]).getCoef()<<std::endl;
    }

}
/*afficher_sommets : sous programme permettant d'afficher à l'écran les sommets du graphe
ENTREE : l'image de fond
SORTIE : Aucune
*/
void Graphe::afficher_sommets(BITMAP* img)
{
    int n;
    for(int i=0; i<getOrdre(); i++)
    {
        draw_sprite(img, (getVectSom()[i]).getImage(),(getVectSom()[i]).getCoordX(),(getVectSom()[i]).getCoordY() );
        n = (getVectSom()[i]).getNumero();
        textprintf(img,font, (getVectSom()[i]).getCoordX()+20, (getVectSom()[i]).getCoordY()-20, makecol(255,255,255) ,"Sommet n° %d",n );
    }
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

                //INITIALISATION
                m_vect_arcs[i].setArrowX1(m_vect_arcs[i].getS2().getCoordX());
                m_vect_arcs[i].setArrowY1(m_vect_arcs[i].getS2().getCoordY());

                X2 = m_vect_arcs[i].getS2().getCoordX() - 10;
                Y2 = m_vect_arcs[i].getS2().getCoordY() - 10;

                X3 = m_vect_arcs[i].getS2().getCoordX() - 10;
                Y3 = m_vect_arcs[i].getS2().getCoordY() + 10;


                //AFFICHAGE DES FORMES
                triangle(buffer, m_vect_arcs[i].getArrowX1(), m_vect_arcs[i].getArrowY1(), X2, Y2, X3, Y3, makecol(255,0,0));
                line(buffer,m_vect_arcs[i].getArrowX1(),m_vect_arcs[i].getArrowY1(),m_vect_arcs[i].getS1().getCoordX(),m_vect_arcs[i].getS1().getCoordY(), makecol(255,0,0));


/*

            //TRACE DE LA LIGNE
           // line(screen,x2,y2,x1,y1, makecol(255,0,0));


            //On dessine une flèche dont le sommet 2 est la pointe de la flèche
            //On dessine la point de la flèches
            //On instancie des variables
            int X1,X2,X3,Y1,Y2,Y3;

            X1 = m_vect_arcs[i].getS2().getCoordX();
            Y1 = m_vect_arcs[i].getS2().getCoordY()+(m_vect_arcs[i].getS2().getImage()->h)/2;



            //TRACE DE LA FLECHE ET MODIFICATION DE LA LIGNE
            //Si le bout de la flèche au S1 est situé dans les y inférieurs par rapport à S2
            if(line_x2 > line_x1 && line_y2 < line_y1)
            {


            }


            //Si le bout de la flèche au S1 est situé dans les y supérieurs par rapport à S2
            if(line_x2 < line_x1 && line_y2 < line_y1)
            {

                X1 = m_vect_arcs[i].getS2().getCoordX() + m_vect_arcs[i].getS2().getImage()->w;
                Y1 = m_vect_arcs[i].getS2().getCoordY()+(m_vect_arcs[i].getS2().getImage()->h)/2;

                X2 = m_vect_arcs[i].getS2().getCoordX() - 10;
                Y2 = m_vect_arcs[i].getS2().getCoordY() - 10;

                X3 = m_vect_arcs[i].getS2().getCoordX() + 10;
                Y3 = m_vect_arcs[i].getS2().getCoordY() + 10;
            }


            //Si le bout de la flèche au S1 est situé dans les x inférieurs par rapport à S2
            if(line_x1 > line_x2 && line_y1 < line_y2)
            {

            }

            //Si le bout de la flèche au S1 est situé dans les x supérieurs par rapport à S2
            if(line_x1 < line_x2 && line_y1 < line_y2)
            {

            }



            if(((((pr->x)-(pr->rayon))<0)&&((pr->depx)<0)) || ((((pr->x)+(pr->rayon))>SCREEN_W)&&((pr->depx)>0)))
            {
                depX=-depX;
            }


            if(((((pr->y)-(pr->rayon))<0)&&((pr->depy)<0)) || ((((pr->y)+(pr->rayon))>SCREEN_H)&&((pr->depy)>0)))
            {
                depY=-depY;
            }

            X1 = X1 + depX;
            Y1 = Y1 + depY;
            X2 = X2 + depX;
            Y2 = Y2 + dep7;
            X3 = X3 + depX;
            Y3 = Y3 + depY;


            //Les coordonnées du premier sommet du triangle




            triangle(screen, x1, y1, x2, y2, x3, y3, makecol(255,0,0));*/
            }
    }
}
