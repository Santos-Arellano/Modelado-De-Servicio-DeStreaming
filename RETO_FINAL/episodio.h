// Santos Alejandro Arellano Olarte A01643742

#pragma once
#include <iostream>
#include "video.h"

using namespace std;

class Episodio : public Video
{

private:
    string m_idEpisodio;
    int m_temporada;
    string m_serie;

public:
// Constructor de la clase Episodio
    Episodio(string, string, string, string, string, int);
    string getIdEpisodio();
    int getTemporada();
    void setSerie(string);
    string getSerie();
    void setGenero(string);
    virtual string muestraDatos();
};