// Santos Alejandro Arellano Olarte A01643742

#pragma once
#include <iostream>
#include <vector>
#include "episodio.h"

using namespace std;

class Serie
{

protected:
    string m_id;
    string m_nombre;
    string m_genero;
    int m_temporadas;
    vector<Episodio *> m_episodios; // Vector de apuntadores a episodios (clase Episodio)

public:
    Serie(string, string, string, int);
    string getID();
    string getNombre();
    string getGenero();
    int getTemporadas();
    vector<Episodio *> getEpisodios(); // Regresa el vector de apuntadores a episodios
    void setEpisodios(vector<Episodio *>); // Asigna el vector de apuntadores a episodios
    string mostrarEpisodios();
    string mostrarDatos();
};