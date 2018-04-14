#include "Arc.hpp"



//Construteur par défaut
Arc::Arc()
    :m_s1(" ",0,0,0,0,0,0,NULL,false,false,false,0,0,false, false), m_s2(" ",0,0,0,0,0,0,NULL,false,false,false,0,0,false,false), m_Coef(0),m_Coef_temp(0), m_aff_arc(false),m_arrow_x1(0), m_arrow_y1(0), m_line_s1_x(0), m_line_s1_y(0)
{

}


//Constructeur surchargé
Arc::Arc(Sommet _s1, Sommet _s2, float _Coef, bool _aff_arc, float _coef_temp)
    :m_s1(_s1), m_s2(_s2), m_Coef(_Coef), m_Coef_temp(_coef_temp),m_aff_arc(_aff_arc),m_arrow_x1(0), m_arrow_y1(0), m_line_s1_x(0), m_line_s1_y(0)
{

}



//Destructeur
Arc::~Arc()
{

}




//Accesseurs
//getters
//getter qui retourne l'attribut "m_s1"
Sommet Arc::getS1()
{
    return m_s1;
}

//getter qui retourne l'attribut "m_s2"
Sommet Arc::getS2()
{
    return m_s2;
}

//getter qui retourne l'attribut "m_Coef"
float Arc::getCoef()
{
    return m_Coef;
}

//getter qui retourne l'attribut "m_Coef_temp"
float Arc::getCoefTemp()
{
    return m_Coef_temp;
}

//getter qui retourne l'attribut "m_aff_arc"
bool Arc::getAffArc()
{
    return m_aff_arc;
}

//getter qui retourne l'attribut "m_arrow_x1"
int Arc::getArrowX1()
{
    return m_arrow_x1;
}

//getter qui retourne l'attribut "m_arrow_y1"
int Arc::getArrowY1()
{
    return m_arrow_y1;
}

//getter qui retourne l'attribut "m_line_s1_x"
int Arc::getLine_S1_X()
{
    return m_line_s1_x;
}

//getter qui retourne l'attribut "m_line_s1_y"
int Arc::getLine_S1_Y()
{
    return m_line_s1_y;
}

//setters
//setter qui modifie l'attribut "m_s1"
void Arc::setS1(Sommet s1)
{
    m_s1=s1;
}

//setter qui modifie l'attribut "m_s2"
void Arc::setS2(Sommet s2)
{
    m_s2=s2;
}

//setter qui modifie l'attribut "m_Coef"
void Arc::setCoef(float Coef)
{
    m_Coef=Coef;
}

//setter qui modifie l'attribut "m_Coef"
void Arc::setCoefTemp(float Coef_t)
{
    m_Coef_temp=Coef_t;
}

//setter qui modifie l'attribut "m_aff_arc"
void Arc::setAffArc(bool aff_arc)
{
    m_aff_arc=aff_arc;
}


//setter qui modifie l'attribut "m_arrow_x1"
void Arc::setArrowX1(int arrow_x1)
{
    m_arrow_x1=arrow_x1;
}

//setter qui modifie l'attribut "m_arrow_y1"
void Arc::setArrowY1(int arrow_y1)
{
    m_arrow_y1=arrow_y1;
}

//setter qui modifie l'attribut "m_line_s1_x"
void Arc::setLine_S1_X(int line_s1_x)
{
    m_line_s1_x=line_s1_x;
}

//setter qui modifie l'attribut "m_line_s1_y"
void Arc::setLine_S1_Y(int line_s1_y)
{
    m_line_s1_y=line_s1_y;
}




/* afficher_arcs : sous-programme permettant d'afficher un arc à afficher entre 2 sommets
ENTREE :
    buffer : de type BITMAP*
SORTIE :
    aucune
*/
void Arc::afficher_arc(BITMAP* buffer)
{

    if(getAffArc())
    {

        //Variables temporaires
        int X2, X3, Y2, Y3;


        //INITIALISATION
        setArrowX1(getS2().getCoordX());
        setArrowY1(getS2().getCoordY());

        setLine_S1_X(getS1().getCoordX());
        setLine_S1_Y(getS1().getCoordY());

        X2 = getArrowX1() - 8;
        Y2 = getArrowY1() - 8;

        X3 = getArrowX1() - 8;
        Y3 = getArrowY1() + 8;


        //AJUSTEMENT
        //TRACE DE LA FLECHE ET MODIFICATION DE LA LIGNE
        //CAS 1
        if(getArrowX1() > getS1().getCoordX() && getArrowY1() > getS1().getCoordY())
        {

            setArrowX1(getS2().getCoordX() + (getS2().getImage()->w)/2);
            setArrowY1(getS2().getCoordY() - 22);

            X2 = getArrowX1() - 8;
            Y2 = getArrowY1() - 16;

            X3 = getArrowX1() - 16;
            Y3 = getArrowY1() - 8;

            setLine_S1_X(getS1().getCoordX() + (getS1().getImage()->w));
            setLine_S1_Y(getS1().getCoordY() + (getS1().getImage()->h)/2 +5);

        }



        //CAS 2
        else if(getArrowX1() < getS1().getCoordX() && getArrowY1() < getS1().getCoordY())
        {

            setArrowX1(getS2().getCoordX() + (getS2().getImage()->w));
            setArrowY1(getS2().getCoordY() + (getS2().getImage()->h)/2 -5);

            X2 = getArrowX1() + 8;
            Y2 = getArrowY1() + 16;

            X3 = getArrowX1() + 16;
            Y3 = getArrowY1() + 8;

            setLine_S1_X(getS1().getCoordX() + (getS1().getImage()->w)/2);
            setLine_S1_Y(getS1().getCoordY() - 22);

        }



        //CAS 3
        else if(getArrowX1() < getS1().getCoordX() && getArrowY1() > getS1().getCoordY())
        {

            setArrowX1(getS2().getCoordX() + (getS2().getImage()->w)/2 +5);
            setArrowY1(getS2().getCoordY() - 22);

            X2 = getArrowX1() + 16;
            Y2 = getArrowY1() - 8;

            X3 = getArrowX1() + 8;
            Y3 = getArrowY1() - 16;

            setLine_S1_X(getS1().getCoordX());
            setLine_S1_Y(getS1().getCoordY() + (getS1().getImage()->h)/2);

        }


        //CAS 4
        else if(getArrowX1() > getS1().getCoordX() && getArrowY1() < getS1().getCoordY())
        {

            setArrowX1(getS2().getCoordX());
            setArrowY1(getS2().getCoordY() + (getS2().getImage()->h)/2);

            X2 = getArrowX1() - 16;
            Y2 = getArrowY1() + 8;

            X3 = getArrowX1() - 8;
            Y3 = getArrowY1() + 16;

            setLine_S1_X(getS1().getCoordX() + (getS1().getImage()->w/2));
            setLine_S1_Y(getS1().getCoordY() - 22);

        }



        //CAS 5
        else if(getArrowX1() == getS1().getCoordX() && getArrowY1() > getS1().getCoordY())
        {

            setArrowX1(getS2().getCoordX() + (getS2().getImage()->w)/2);
            setArrowY1(getS2().getCoordY() - 22);

            X2 = getArrowX1() + 8;
            Y2 = getArrowY1() - 8;

            X3 = getArrowX1() - 8;
            Y3 = getArrowY1() - 8;

            setLine_S1_X(getS1().getCoordX() + (getS1().getImage()->w)/2);
            setLine_S1_Y(getS1().getCoordY() + (getS1().getImage()->h));

        }


        //CAS 6
        else if(getArrowX1() > getS1().getCoordX() && getArrowY1() == getS1().getCoordY())
        {

            setArrowX1(getS2().getCoordX());
            setArrowY1(getS2().getCoordY() + (getS2().getImage()->h)/2);

            X2 = getArrowX1() - 8;
            Y2 = getArrowY1() - 8;

            X3 = getArrowX1() - 8;
            Y3 = getArrowY1() + 8;

            setLine_S1_X(getS1().getCoordX() + (getS1().getImage()->w));
            setLine_S1_Y(getS1().getCoordY() + (getS1().getImage()->h)/2);

        }


        //CAS 7
        else if(getArrowX1() == getS1().getCoordX() && getArrowY1() < getS1().getCoordY())
        {

            setArrowX1(getS2().getCoordX() + (getS2().getImage()->w)/2);
            setArrowY1(getS2().getCoordY() + (getS2().getImage()->h));

            X2 = getArrowX1() - 8;
            Y2 = getArrowY1() + 8;

            X3 = getArrowX1() + 8;
            Y3 = getArrowY1() + 8;

            setLine_S1_X(getS1().getCoordX() + (getS1().getImage()->w)/2);
            setLine_S1_Y(getS1().getCoordY() - 22);

        }


        //CAS 8
        else if(getArrowX1() < getS1().getCoordX() && getArrowY1() == getS1().getCoordY())
        {

            setArrowX1(getS2().getCoordX() + (getS2().getImage()->w));
            setArrowY1(getS2().getCoordY() + (getS2().getImage()->h)/2);

            X2 = getArrowX1() + 8;
            Y2 = getArrowY1() - 8;

            X3 = getArrowX1() + 8;
            Y3 = getArrowY1() + 8;

            setLine_S1_X(getS1().getCoordX());
            setLine_S1_Y(getS1().getCoordY() + (getS1().getImage()->h)/2);

        }


        //AFFICHAGE DES FORMES
        triangle(buffer, getArrowX1(), getArrowY1(), X2, Y2, X3, Y3, makecol(255,0,0));
        line(buffer, (X2+X3)/2, (Y2+Y3)/2, getLine_S1_X(), getLine_S1_Y(), makecol(255,0,0));
        textprintf(buffer,font,(getLine_S1_X()+getArrowX1())/2 -40,(getLine_S1_Y()+getArrowY1())/2, makecol(100,0,255) ,"Coef=%1.2f",getCoef());

    }
}

