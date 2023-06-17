// Santos Alejandro Arellano Olarte A01643742

#pragma once // Para que el compilador lo incluya solo una vez

#include <iostream> 

using namespace std; 

class Video // Clase abstracta
{
protected:
    string m_id;
    string m_nombre;
    string m_duracion;
    string m_genero;
    string m_calificacion;

public:
    string getID();
    string getNombre();
    string getDuracion();
    string getGenero();
    string getCalificacion();
    //Sobre carga de operadores para comparar Videos
    friend bool operator>(const Video &, const Video &);
    bool cmpVideos(const Video *, const Video *);
    void setCalificacion(string);
    virtual string muestraDatos() = 0;
};
