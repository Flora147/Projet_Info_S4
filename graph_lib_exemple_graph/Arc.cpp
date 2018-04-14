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

