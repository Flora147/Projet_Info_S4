#ifndef ARC_HPP_INCLUDED
#define ARC_HPP_INCLUDED
#include "Sommet.hpp"

class Arc
{

    private :
        //Attributs
        Sommet m_s1;
        Sommet m_s2;
        float m_Coef;
        bool m_aff_arc;


    public :
        //Constructeur surchargé et destructeur
        Arc();
        Arc(Sommet _s1, Sommet _s2, float _Coef, bool _aff_arc);
        ~Arc();


        //Accesseurs
        //getters
        Sommet getS1();
        Sommet getS2();
        float getCoef();
        bool getAffArc();

        //setters
        void setS1(Sommet s1);
        void setS2(Sommet s2);
        void setCoef(float Coef);
        void setAffArc(bool aff_arc);

};

#endif // ARC_HPP_INCLUDED
