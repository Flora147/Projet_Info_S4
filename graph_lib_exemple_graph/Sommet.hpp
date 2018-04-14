#include <string>
#ifndef SOMMET_HPP_INCLUDED
#define SOMMET_HPP_INCLUDED

class Sommet
{

    private :
        //Attributs
        std::string m_name;
        int m_numero;
        int m_N;
        int m_K;
        float m_r;
        int m_coord_x;
        int m_coord_y;
        BITMAP m_image;
        bool m_aff_som;
        bool m_select;



    public :
        //Constructeur surchargé et destructeur
        Sommet(std::string _name, int _numero, int _N, int _K, float _r, int _coord_x, int _coord_y, BITMAP _image, bool _aff_som, bool _select);
        ~Sommet();


        //Accesseurs
            //getters
            std::string getName();
            int getNumero();
            int getN();
            int getK();
            float getR();
            int getCoordX();
            int getCoordY();
            BITMAP getImage();
            bool getAffSom();
            bool getSelect();

            //setters
            void setName(std::string name);
            void setNumero(int numero);
            void setN(int N);
            void setK(int K);
            void setR(float r);
            void setCoordX(int coord_x);
            void setCoordY(int coord_y);
            void setImage(BITMAP image);
            void setAffSom(bool aff_som);
            void getSelect(bool select);


};

#endif // SOMMET_HPP_INCLUDED
