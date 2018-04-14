#include <string>
#include <allegro.h>
#ifndef SOMMET_HPP_INCLUDED
#define SOMMET_HPP_INCLUDED

class Sommet
{

    private :
        //Attributs
        std::string m_name;
        int m_numero;
        int m_N;
        int m_N_temp;
        int m_K;
        int m_K_temp;
        int m_col;
        float m_r;
        int m_coord_x;
        int m_coord_y;
        float m_nourriture;
        BITMAP* m_image;
        bool m_aff_som;
        bool m_aff_som_temp;
        bool m_select;
        bool m_marque;
        bool m_veget;



    public :
        //Constructeur surchargé et destructeur
        Sommet();
        Sommet(std::string _name, int _numero, int _N, int _K, float _r, int _coord_x, int _coord_y, BITMAP* _image, bool _aff_som, bool _select, bool _marque,int _N_temp, int _K_temp,bool _aff_temp, bool _veget, float _nourr);
        ~Sommet();


        //Accesseurs
            //getters
            std::string getName();
            int getNumero();
            int getN();
            int getNTemp();
            int getK();
            int getKTemp();
            int getCol();
            float getR();
            int getCoordX();
            int getCoordY();
            BITMAP* getImage();
            bool getAffSom();
            bool getAffSomTemp();
            bool getSelect();
            bool getMarque();
            bool getVeget();
            float getNourriture();


            //setters
            void setName(std::string name);
            void setNumero(int numero);
            void setN(int N);
            void setNTemp(int Nt);
            void setK(int K);
            void setKTemp(int Kt);
            void setR(float r);
            void setCol(int c);
            void setCoordX(int coord_x);
            void setCoordY(int coord_y);
            void setImage(BITMAP* image);
            void setAffSom(bool aff_som);
            void setAffSomTemp(bool aff_temp);
            void setSelect(bool select);
            void setMarque(bool marque);
            void setVeget(bool v);
            void setNourriture(float nourr);


            //Méthodes
            void afficher_infos();


};

#endif // SOMMET_HPP_INCLUDED
