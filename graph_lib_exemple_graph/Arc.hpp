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
        float m_Coef_temp;
        bool m_aff_arc;
        bool m_influence;
        int m_arrow_x1;
        int m_arrow_y1;
        int m_line_s1_x;
        int m_line_s1_y;



    public :
        //Constructeur surchargé et destructeur
        Arc();
        Arc(Sommet _s1, Sommet _s2, float _Coef, bool _aff_arc, float _coef_temp, bool _influ);
        ~Arc();


        //Accesseurs
        //getters
        Sommet getS1();
        Sommet getS2();
        float getCoef();
        float getCoefTemp();
        bool getAffArc();
        bool getInfluence();
        int getArrowX1();
        int getArrowY1();
        int getLine_S1_X();
        int getLine_S1_Y();

        //setters
        void setS1(Sommet s1);
        void setS2(Sommet s2);
        void setCoef(float Coef);
        void setCoefTemp(float Coef_t);
        void setAffArc(bool aff_arc);
        void setInflu(bool influ);
        void setArrowX1(int arrow_x1);
        void setArrowY1(int arrow_y1);
        void setLine_S1_X(int line_s1_x);
        void setLine_S1_Y(int line_s1_y);
        void afficher_arc(BITMAP* buffer);

};

#endif // ARC_HPP_INCLUDED
