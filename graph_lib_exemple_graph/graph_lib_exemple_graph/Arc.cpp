#include "Arc.hpp"



//Construteur par défaut
Arc::Arc()
    :m_s1(" ",0,0,0,0,0,0,NULL,false,false), m_s2(" ",0,0,0,0,0,0,NULL,false,false), m_Coef(0), m_aff_arc(false),m_arrow_x1(0), m_arrow_y1(0), m_line_s1_x(0), m_line_s1_y(0)
{

}


//Constructeur surchargé
Arc::Arc(Sommet _s1, Sommet _s2, float _Coef, bool _aff_arc)
    :m_s1(_s1), m_s2(_s2), m_Coef(_Coef), m_aff_arc(_aff_arc),m_arrow_x1(0), m_arrow_y1(0), m_line_s1_x(0), m_line_s1_y(0)
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



/*
void Arc::afficher_arc(BITMAP* buffer)
{

    //Variables temporaires
    int X2, X3, Y2, Y3;


    //INITIALISATION
    setArrowX1(getS2().getCoordX());
    setArrowY1(getS2().getCoordY());

    X2 = getArrowX1() - 10;
    Y2 = getArrowY1() - 10;

    X3 = getArrowX1() - 10;
    Y3 = getArrowY1() + 10;


    //AJUSTEMENT
    //TRACE DE LA FLECHE ET MODIFICATION DE LA LIGNE
    //CAS 1
    if(getArrowX1() > m_vect_arcs[i].getS1().getCoordX() && m_vect_arcs[i].getArrowY1() > m_vect_arcs[i].getS1().getCoordY())
    {

        setArrowX1(m_vect_arcs[i].getS2().getCoordX() + (m_vect_arcs[i].getS2().getImage()->w)/2);
        setArrowY1(m_vect_arcs[i].getS2().getCoordY() - 25);

        setLine_S1_X(m_vect_arcs[i].getS1().getCoordX() + (m_vect_arcs[i].getS1().getImage()->w)/2);
        setLine_S1_Y(m_vect_arcs[i].getS1().getCoordY() + (m_vect_arcs[i].getS1().getImage()->h));

        X2 = getArrowX1() - 10;
        Y2 = getArrowY1() - 20;

        X3 = getArrowX1() - 20;
        Y3 = getArrowY1() - 10;

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
