#include "Arc.hpp"


//Constructeur surchargé
Arc::Arc(Sommet _s1, Sommet _s2, float _Coef, bool _aff_arc)
    :m_s1(_s1), m_s2(_s2), m_Coef(_Coef), m_aff_arc(_aff_arc)
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
