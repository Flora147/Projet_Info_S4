#include "Sommet.hpp"


//Constructeur surchargé
Sommet::Sommet(std::string _name, int _numero, int _N, int _K, float _r, int _coord_x, int _coord_y, BITMAP _image, bool _aff_som, bool _select)
    :m_name(_name), m_numero(_numero), m_N(_N), m_K(_K), m_r(_r), m_coord_x(_coord_x), m_coord_y(_coord_y), m_image(_image), m_aff_som(_aff_som), m_select(_select)
{

}




//Destructeur
Sommet::~Sommet()
{

}




//Accesseurs
//getters
//getter qui retourne l'attribut "m_name"
std::string Sommet::getName()
{
    return m_name;
}

//getter qui retourne l'attribut "m_numero"
int Sommet::getNumero()
{
    return m_numero;
}

//getter qui retourne l'attribut "m_N"
int Sommet::getN()
{
    return m_N;
}

//getter qui retourne l'attribut "m_K"
int Sommet::getK()
{
    return m_K;
}

//getter qui retourne l'attribut "m_r"
float Sommet::getR()
{
    return m_r;
}

//getter qui retourne l'attribut "m_coord_x"
int Sommet::getCoordX()
{
    return m_coord_x;
}

//getter qui retourne l'attribut "m_coord_y"
int Sommet::getCoordY()
{
    return m_coord_y;
}

//getter qui retourne l'attribut "m_image"
BITMAP Sommet::getImage()
{
    return m_image;
}

//getter qui retourne l'attribut "m_aff_som"
bool Sommet::getAffSom()
{
    return m_aff_som;
}

//getter qui retourne l'attribut "m_select"
bool Sommet::getSelect()
{
    return m_select;
}


//setters
//setter qui modifie l'attribut "m_name"
void Sommet::setName(std::string name)
{
    m_name=name;
}

//setter qui modifie l'attribut "m_numero"
void Sommet::setNumero(int numero)
{
    m_numero=numero;
}

//setter qui modifie l'attribut "m_N"
void Sommet::setN(int N)
{
    m_N=N;
}

//setter qui modifie l'attribut "m_K"
void Sommet::setK(int K)
{
    m_K=K;
}

//setter qui modifie l'attribut "m_r"
void Sommet::setR(float r)
{
    m_r=r;
}

//setter qui modifie l'attribut "m_coord_x"
void Sommet::setCoordX(int coord_x)
{
    m_coord_x=coord_x;
}

//setter qui modifie l'attribut "m_coord_y"
void Sommet::setCoordY(int coord_y)
{
    m_coord_y=coord_y;
}

//setter qui modifie l'attribut "m_image"
void Sommet::setImage(BITMAP image)
{
    m_image=image;
}

//setter qui modifie l'attribut "m_aff_som"
void Sommet::setAffSom(bool aff_som)
{
    m_aff_som=aff_som;
}

//setter qui modifie l'attribut "m_select"
void Sommet::getSelect(bool select)
{
    m_select=select;
}
