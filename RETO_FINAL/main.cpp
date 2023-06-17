// Santos Alejandro Arellano Olarte A01643742
#include <iostream>
#include <vector>
#include "serie.cpp"
#include "episodio.cpp"
#include "video.cpp"
#include "pelicula.cpp"
#include <sstream>
#include <fstream>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <thread>


#include <limits> // Aqui va el include para que funcione el forzarInt

using namespace std;
 
void imprimirConRetardo(const std::string& texto, int retardo) { // Funcion para imprimir con retardo
    for (char c : texto) {
        std::cout << c;
        std::this_thread::sleep_for(std::chrono::milliseconds(retardo)); // Retardo de 30 milisegundos
    }
}



vector<Serie> cargarSeries()  // Funcion para cargar las series
{
    vector<Serie> series;
    string str;
    string file = "Series.txt"; // Se abre el archivo de series
    ifstream s(file);

    if (s.is_open()) // Si el archivo esta abierto
    {
        while (getline(s, str)) // Se lee el archivo
        {
            stringstream ss(str);
            string line[4];

            int i = 0;

            while (i < 4 && getline(ss, line[i++], ';')) // Se separan los datos por ;
                ;

            Serie s(
                line[0],
                line[1],
                line[2],
                stoi(line[3])); // Se crea una nueva serie

            series.push_back(s); // Se agrega la serie al vector de series
        }
    }

    return series;
}

vector<Pelicula *> cargarPeliculas() // Funcion para cargar las peliculas
{
    vector<Pelicula *> peliculas; // Vector de apuntadores a peliculas
    string str;
    string file1 = "Peliculas.txt";     // Se abre el archivo de peliculas
    ifstream s1(file1); // Se abre el archivo de peliculas

    if (s1.is_open())
    {
        while (getline(s1, str))
        {
            stringstream ss(str);
            string line[5];

            int i = 0;

            while (i < 5 && getline(ss, line[i++], ';')) // Se separan los datos por ;
                ;

            Pelicula *p = new Pelicula( // Se crea una nueva pelicula
                line[0],
                line[1],
                line[2],
                line[3],
                line[4]);

            peliculas.push_back(p);
        }
    }

    return peliculas;
}


vector<Episodio *> cargarEpisodios(vector<Serie> &series) // Funcion para cargar los episodios de las series
{
    vector<Episodio *> episodios; // Vector de apuntadores a episodios
    string str;
    string file2 = "Episodios";
    ifstream s2(file2);

    if (s2.is_open())
    {
        while (getline(s2, str))
        {
            stringstream ss(str);
            string line[6];

            int i = 0;

            while (i < 6 && getline(ss, line[i++], ';'))
                ;

            Episodio *ep = new Episodio( // Se crea un nuevo episodio
                line[0],
                line[1],
                line[2],
                line[3],
                line[4],
                stoi(line[5])); // Se convierte el string a int

            episodios.push_back(ep);
        }

//Asignar Genero a Episodios (composicion de clase Episodio);
        for (int i = 0; i < series.size(); i++)
        {
            for (int j = 0; j < episodios.size(); j++)
            {
                string epId = episodios[j]->getID(); // Se obtiene el id del episodio
                string sId = series[i].getID(); // Se obtiene el id de la serie
                if (epId == sId)
                {
                    string g = series[i].getGenero();
                    string s = series[i].getNombre();
                    episodios[j]->setGenero(g);
                    episodios[j]->setSerie(s);
                }
            }
        }

//Asignar Episodios a Series (composicion de clase Serie);
        for (int i = 0; i < series.size(); i++)
        {
            vector<Episodio *> episodios_Serie;
            for (int j = 0; j < episodios.size(); j++)
            {
                string epId = episodios[j]->getID();
                string sId = series[i].getID();
                if (epId == sId)
                {
                    episodios_Serie.push_back(episodios[j]);
                }
            }

            series[i].setEpisodios(episodios_Serie);
        }
    }

    return episodios;
}

vector<Video *> cargarVideos(vector<Pelicula *> peliculas, vector<Episodio *> episodios) // Funcion para cargar los videos
{
    vector<Video *> videos;
    videos.reserve(peliculas.size() + episodios.size()); // Se reserva el espacio para los videos
    videos.insert(videos.end(), peliculas.begin(), peliculas.end());
    videos.insert(videos.end(), episodios.begin(), episodios.end()); // Se insertan las peliculas y los episodios al vector de videos

    return videos;
}


//Funcion para forzar un entero en la entrada de datos del usuario (no acepta letras)
double forzarDouble()
{
    double valDouble;
    cin >> valDouble;

    while (true)
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Se ignora el limite de la entrada de datos
            cout << "\n";
            cout << "╔════════════════════════════════╗" << endl; 
            cout << "║                                ║" << endl;
            cout << "║ Ingresar solo valores numéricos║" << endl;
            cout << "║   Intenta de nuevo             ║" << endl;
            cout << "║                                ║" << endl;
            cout << "╚════════════════════════════════╝" << endl;
            cout << "\n";

            
            cin >> valDouble;
            cout << endl;
        }
        else
        {
            return valDouble;
            break;
        }
    }
}

//Funcion para forzar un entero en la entrada de datos del usuario (no acepta letras)
double verificarRango(int valor, int menor, int mayor)
{
    while (1)
    {
        valor = forzarDouble();
        if (valor >= menor && valor <= mayor) // Se verifica que el valor este dentro del rango
        {
            break;
        }
        else
        {
            cout << "\n";
            cout << "         ╔════════════════════════════════════════════════════╗" << endl;
            cout << "         ║                                                    ║" << endl;
            cout << "         ║      Valor ingresado fuera del rango.              ║" << endl;
            cout << "         ║      Intenta de nuevo.                             ║" << endl;
            cout << "         ║                                                    ║" << endl;
            cout << "         ║                 ╭─────────────────╮                ║" << endl;
            cout << "         ║                 │       ____      │                ║" << endl;
            cout << "         ║                 │    \\ ಠ︵ಠ  /   │                ║" << endl;
            cout << "         ║                 │     \\_____/    │                ║" << endl;
            cout << "         ║                 │      /   \\     │                ║" << endl;
            cout << "         ║                 │     │     │     │                ║" << endl;
            cout << "         ║                 │     │     │     │                ║" << endl;
            cout << "         ║                 │_____|_____|_____|                ║" << endl;
            cout << "         ║                                                    ║" << endl;
            cout << "         ╚════════════════════════════════════════════════════╝" << endl;
cout << "\n";

            
        }
    }
    return valor;
}

//Funcion para forzar un entero en la entrada de datos del usuario (no acepta letras)
double verificarRango(double calificacion)
{
    while (1)
    {
        calificacion = forzarDouble();
        if (calificacion >= 0 && calificacion <= 10)
        {
            break;
        }
        else
        {
            cout << "\n";
            cout << "         ╔════════════════════════════════════════════════════╗" << endl;
            cout << "         ║                                                    ║" << endl;
            cout << "         ║      Valor ingresado fuera del rango.              ║" << endl;
            cout << "         ║      Intenta de nuevo.                             ║" << endl;
            cout << "         ║                                                    ║" << endl;
            cout << "         ║                 ╭─────────────────╮                ║" << endl;
            cout << "         ║                 │       ____      │                ║" << endl;
            cout << "         ║                 │    \\ ಠ︵ಠ  /   │                ║" << endl;
            cout << "         ║                 │     \\_____/    │                ║" << endl;
            cout << "         ║                 │      /   \\     │                ║" << endl;
            cout << "         ║                 │     │     │     │                ║" << endl;
            cout << "         ║                 │     │     │     │                ║" << endl;
            cout << "         ║                 │_____|_____|_____|                ║" << endl;
            cout << "         ║                                                    ║" << endl;
            cout << "         ╚════════════════════════════════════════════════════╝" << endl;
        }
    }
    return calificacion;
}

//Funcion para forzar un entero en la entrada de datos del usuario (no acepta letras)
void modificarArchivoEpisodios(vector<Episodio *> v)
{
    ofstream ofs("Episodios.txt", ofstream::trunc);
    for (int i = 0; i < v.size(); i++)
    {
        string str = v[i]->getID() + ";" + v[i]->getIdEpisodio() + ";" + v[i]->getNombre() + ";" + v[i]->getDuracion() + ";" + v[i]->getCalificacion() + ";" + to_string(v[i]->getTemporada()) + "\n";
        ofs << str;
    }
    ofs.close();
}

// Funcion para modificar el archivo de peliculas
void modificarArchivoPeliculas(vector<Pelicula *> v)
{
    ofstream ofs("Peliculas.txt", ofstream::trunc);
    for (int i = 0; i < v.size(); i++)
    {
        string str = v[i]->getID() + ";" + v[i]->getNombre() + ";" + v[i]->getDuracion() + ";" + v[i]->getGenero() + ";" + v[i]->getCalificacion() + "\n";
        ofs << str;
    }
    ofs.close();
}

//Funcion para separar las secciones en los menus
void espaciado()
{
    cout << "\n--------------------------------------------" << endl;
}

int main()

{
    std::vector<std::string> generos;
    generos.push_back("Accion");
    generos.push_back("Drama");
    generos.push_back("Misterio");
    generos.push_back("Suspenso");
    generos.push_back("Terror");
    generos.push_back("Comedia");
    generos.push_back("Ciencia Ficcion");
    generos.push_back("Fantasia");
    generos.push_back("Animacion");
    generos.push_back("Musical");
    generos.push_back("Documental");
    generos.push_back("Infantil");
    generos.push_back("Romance");
    vector<Serie> series;
    vector<Pelicula *> peliculas;
    vector<Episodio *> episodios;
    vector<Video *> videos;

    bool ciclarMenu = 1;
    int hayArchivos = 0;

    std::string title[] = {
        "░██████╗███████╗███╗░░██╗░██████╗░█████╗░████████╗███████╗░█████╗░",
        "██╔════╝██╔════╝████╗░██║██╔════╝██╔══██╗╚══██╔══╝██╔════╝██╔══██╗",
        "╚█████╗░█████╗░░██╔██╗██║╚█████╗░███████║░░░██║░░░█████╗░░██║░░╚═╝",
        "░╚═══██╗██╔══╝░░██║╚████║░╚═══██╗██╔══██║░░░██║░░░██╔══╝░░██║░░██╗",
        "██████╔╝███████╗██║░╚███║██████╔╝██║░░██║░░░██║░░░███████╗╚█████╔╝",
        "╚═════╝░╚══════╝╚═╝░░╚══╝╚═════╝░╚═╝░░╚═╝░░░╚═╝░░░╚══════╝░╚════╝░"
    };

    int numLines = sizeof(title) / sizeof(title[0]);

    for (int i = 0; i < numLines; i++) {
        for (int j = 0; j < title[i].length(); j++) {
            std::cout << title[i][j];
            std::this_thread::sleep_for(std::chrono::milliseconds(3)); // Pausa de 30 milisegundos
        }
        std::cout << std::endl;
    }


    while (ciclarMenu)
    {

           
            
        cout << "=============================================" << endl;
        cout << "| Opciones disponibles:                     |" << endl;
        cout << "| 1. Cargar archivo de datos                 |" << endl;
        cout << "| 2. Mostrar Todo El Catálogo con Calificaciones o género |" << endl;
        cout << "| 3. Mostrar Películas o Capítulos con una Calificación Mínima Determinada |" << endl;
        cout << "| 4. Mostrar las películas con cierta calificación              |" << endl;
        cout << "| 5. Calificar un video                      |" << endl;
        cout << "| 6. Salir                                   |" << endl;
        cout << "=============================================" << endl;

        cout << "       \\                   /" << endl;
cout << "        \\                 /" << endl;
cout << "         \\               /" << endl;
cout << "          \\             /" << endl;
cout << "           \\           /" << endl;
cout << "            \\         /" << endl;
cout << "             \\       /" << endl;
cout << "              \\     /" << endl;
cout << "               \\   /" << endl;
cout << "                \\ /" << endl;
cout << "    _____________|_____________" << endl;
cout << "   /                           \\" << endl;
cout << "  /                             \\" << endl;
cout << " |  Ingresa la opción del menú:  |" << endl;
cout << "  \\                             /" << endl;
cout << "   \\___________________________/" << endl;

        int opcion;
        opcion = verificarRango(opcion, 1, 6);

        if (opcion == 1)
        {
            espaciado();

            if (hayArchivos == 0)
            {
  
  cout << "--------------------------------------------" << endl;
cout << "     Se han cargado los archivos exitosamente" << endl;
cout << "              \\o/" << endl;
cout << "                |" << endl;
cout << "              / \\" << endl;
cout << "--------------------------------------------" << endl;

                series = cargarSeries();
                peliculas = cargarPeliculas();
                episodios = cargarEpisodios(series);
                videos = cargarVideos(peliculas, episodios);
                hayArchivos = 1;
            }
            else
            {
                cout << "\nLos archivos ya estan cargados ^^ " << endl;
            }
        }

        else if (opcion == 2) // Mostrar los videos en general con una cierta calificación o de un cierto género
        {
            espaciado();
            if (hayArchivos == 1)
            {

                cout << "\nHas selecionado la opcion 2" << endl;

                cout << "\nQuieres ver videos por calificacion o por genero?" << endl;
                cout << "1. Calificacion" << endl;
                cout << "2. Genero" << endl;

                cout << " |  Ingresa la opción que deseas:  |" << endl;

                int opcionMenu2;
                opcionMenu2 = verificarRango(opcionMenu2, 1, 2);

                vector<Video *> videosAMostrar; //Aqui se van a guardar los videos que cumplan la condicion
                bool hayVideos = 0;             // Variable que permite verificar si hay videos o no con la califacion

                if (opcionMenu2 == 1)
                { // User escogio ver videos por calificacion
                    cout << "Ingresa la calificacion de la cual deseas buscar videos : ";

                    double cali;
                    cali = verificarRango(cali);                            // Se verifica que la calificacion del user sea correcta
                    string calificacion = to_string(cali * 1).substr(0, 3); // Se convierte la calificacion del user a string
                    // Explicar que te redondea la calificacion con un decimal
                    cout << "\nLa calificacion que ingresaste es: " << calificacion << endl;

                    for (int i = 0; i < videos.size(); i++)
                    {
                        if (videos[i]->getCalificacion() == calificacion) // Se itera en el ciclo en busca de la calificacion del user
                        {
                            videosAMostrar.push_back(videos[i]);
                            hayVideos = 1; // Si hay videos
                        }
                    }
                }
                else if (opcionMenu2 == 2)
                { // User escogio ver videos por genero

                    cout << "\nLista de generos disponibles:" << endl;
                    for (int i = 0; i < generos.size(); i++) // Se muestran los generos disponibles
                        cout << i + 1 << "." << generos[i] << endl;

                    cout << "\nIngrese el genero del cual deseas buscar videos : ";
                    int genero; // Se guarda el genero que haya escogido el user
                    genero = verificarRango(genero, 1, generos.size());

                    for (int i = 0; i < videos.size(); i++)
                    {
                        if (videos[i]->getGenero() == generos[genero - 1]) // Se itera en el ciclo en busca del genero del user
                        {
                            videosAMostrar.push_back(videos[i]);
                            hayVideos = 1; // Si hay videos
                        }
                    }
                }

                if (hayVideos == 1)
                {
                    cout << "\nMostrando videos (De calificacion mayor a menor):\n"
                         << endl;
                    sort(videosAMostrar.begin(), videosAMostrar.end(), cmpVideos); //Ordenar videos por calificacion ascendente
                    for (int i = 0; i < videosAMostrar.size(); i++)
                    {
                        cout << videosAMostrar[i]->muestraDatos() << endl; // Aqui se muestran los videos que hayan sido encontrados por genero o por calificacion
                    }
                }
                else
                {
                    cout << " \n\nNo hay videos con la calificacion ingresada {-_ -}" << endl; // En caso de que no haya videos, se imprime el mensaje
                }
            }
            else
            {
                cout << "No han cargado los archivos" << endl;
            }
        }

        else if (opcion == 3) // Mostrar los episodios de una determinada serie con una calificacion determinada
        {
            espaciado();
            if (hayArchivos)
            {
                cout << "\nHas seleccionado opcion 3" << endl;

                cout << "\nA continuacion se muestan las series: " << endl
                     << endl; // Se muestran las series que hay
                for (int i = 0; i < series.size(); i++)
                    cout << i + 1 << ". " << series[i].mostrarDatos();

                cout << "\nIngresa el numero de la serie que desees: ";
                int opcionSerie;
                opcionSerie = verificarRango(opcionSerie, 1, series.size());

                cout << "\nSeleccionaste: " << endl;
                cout << series[opcionSerie - 1].mostrarDatos() << endl; // Se muestra la serie que escogio el user
                cout << "Ahora selecciona la calificacion a buscar en dicha serie: ";

                double cali;
                cali = verificarRango(cali);                            // Se verifica que la calificacion del user sea correcta
                string calificacion = to_string(cali * 1).substr(0, 3); // Se convierte la calificacion del user a string
                cout << "\nLa calificacion que ingresaste es: " << calificacion << endl;

                vector<Episodio *> episodiosAMostrar; // Vector en donde se guardaran los episodios a mostrar
                bool hayEpisodios = 0;                // Variable que permite verificar si hay videos  no con la califacion

                // Vector que guarda los episodios de la serie seleccionada
                vector<Episodio *> episodiosSerie = series[opcionSerie - 1].getEpisodios();

                // Se guardan los episodios de la serie que tengan la calificacion que pide el user

                for (auto ptr_episodio : episodiosSerie)
                { // Se guardan los episodios de la serie que tengan la calificacion que pide el user

                    if (ptr_episodio->getCalificacion() == calificacion)
                    {
                        episodiosAMostrar.push_back(ptr_episodio);
                        hayEpisodios = 1;
                    }
                }

                if (hayEpisodios == 1)
                {
                    cout << "\nMostrando videos " << endl;
                    for (auto ptr_video : episodiosAMostrar) // Aqui se muestran los videos que hayan sido encontrados por genero o por calificacion
                        cout << ptr_video->muestraDatos() << endl;
                }
                else
                {
                    cout << "\n\nNo hay videos con la calificacion ingresada {-_ -} " << calificacion << endl; // En caso de que no haya videos, se imprime el mensaje
                }
            }
            else
            {
                cout << "\nNo han cargado los archivos" << endl;
            }
        }

        else if (opcion == 4) // Mostrar las peliculas con cierta calificacion
        {
            espaciado();
            if (hayArchivos)
            {
                cout << "\nEstas en la opcion 4" << endl;
                // Preguntar la calificacion de la pelicula que quiere ver

                cout << "\nIntroduce la calificacion a buscar : ";

                double cali;
                cali = verificarRango(cali);                     // Se verifica que la calificacion del user sea correcta
                string calif = to_string(cali * 1).substr(0, 3); // Se convierte la calificacion del user a string
                cout << "\nLa calificacion que ingresaste es: " << calif << endl;

                vector<Pelicula *> temp;
                for (int i = 0; i < peliculas.size(); i++)
                {
                    // llamar al vector peliculas y hacer un loop para verficar que lo que ingrese cumpla con una pelicula
                    // IMPORTANTE, se sustrae el salto de linea con substr
                    if (peliculas[i]->getCalificacion().substr(0, 3) == calif)
                    {
                        // ir guardando las peliculas que cumplan con la condicion en un vector temporal
                        temp.push_back(peliculas[i]);
                    }
                }

                if (temp.size() > 0)
                {
                    //Imprime todas las peliculas con la calificacion
                    cout << "Estas son las peliculas con una calificacion de: " << calif << endl;
                    for (int i = 0; i < temp.size(); i++)
                    {
                        // mostrar dicho vector tempoarl
                        cout << i + 1 << ". Nombre de la Pelicula: " << temp[i]->getNombre() << ", Duracion: " << temp[i]->getDuracion() << " hrs, Genero: " << temp[i]->getGenero() << endl;
                    }
                }
                else
                {
                    // mostrar que no hay peliculas que cumplan con esa calificacion en caso contrario
                    cout << "\nNo se encontro ninguna pelicula con una calificacion de: " << calif << endl;
                }
            }
            else
            {
                cout << "No han cargado los archivos" << endl;
            }
        }

        else if (opcion == 5) // Calificar un video
        {
            espaciado();
            if (hayArchivos)
            {
                cout << "\nEstas en la opcion 5" << endl;
                // Preguntar si serie o pelicula
                int opcionCalif;
                cout << "\nCalificar:\n1. Episodio de una Serie\n2. Pelicula\n\nIngresa el numero de la opcion deseada : ";
                opcionCalif = verificarRango(opcionCalif, 1, 2);

                //forzar Int y limites

                // mostrar lo que sea el caso
                if (opcionCalif == 1)
                {

                    cout << "\nEstas son las series disponibles: " << endl;
                    for (int i = 0; i < series.size(); i++)
                    {
                        //Imprime las series
                        cout << i + 1 << ". " << series[i].getNombre() << endl;
                    }
                    cout << "\nElige la opcion  que quieras : ";
                    int serie;
                    serie = verificarRango(serie, 1, series.size());

                    //forzarInt y limites

                    cout << "\nEstos son los episodios de " << series[serie - 1].getNombre() << ": " << endl;
                    vector<Episodio *> temp = series[serie - 1].getEpisodios();
                    for (int i = 0; i < temp.size(); i++)
                    {
                        //Imprime nombres de los episodios y su calificacion de la serie seleccionada
                        cout << i + 1 << ". " << temp[i]->getNombre() << ", Calificacion: " << temp[i]->getCalificacion() << endl;
                    }

                    cout << "\nElige el episodio  a calificar : ";
                    int episodio;
                    // El rango maximo de esta opcion depende de cuantos episodios tenga la serie
                    episodio = verificarRango(episodio, 1, series[serie - 1].getEpisodios().size());

                    //forzarInt y limites

                    //Muestra calificacion original del episodio antes de modificar
                    cout << "La calificacion actual del episodio es de: " << temp[episodio - 1]->getCalificacion() << endl;

                    //forzarInt convierte string a double solo para verificar rango deseado

                    cout << "Introduce la nueva calificacion : ";

                    double cali;
                    cali = verificarRango(cali);                            // Se verifica que la calificacion del user sea correcta
                    string calificacion = to_string(cali * 1).substr(0, 3); // Se convierte la calificacion del user a string
                    cout << "\nLa calificacion que ingresaste es: " << calificacion << endl;

                    series[serie - 1].getEpisodios()[episodio - 1]->setCalificacion(calificacion);


                    modificarArchivoEpisodios(episodios); // Se modifica el archivo de episodios

                    cout << "\nLa nueva calificacion es: " << temp[episodio - 1]->getCalificacion() << endl;

                    cout << "Los cambios se han realizado" << endl;
                }
                else if (opcionCalif == 2)
                {
                    cout << "\nEstas son las peliculas disponibles: " << endl;
                    for (int i = 0; i < peliculas.size(); i++)
                    {
                        cout << i + 1 << ". " << peliculas[i]->getNombre() << ", Calificacion: " << peliculas[i]->getCalificacion() << endl;
                    }
                    cout << "\nElige la pelicula a calificar : ";
                    int pelicula;
                    pelicula = verificarRango(pelicula, 1, peliculas.size());
                    cout << "\nLa calificacion actual de la pelicula es de: " << peliculas[pelicula - 1]->getCalificacion() << endl;

                    cout << "Introduce la nueva calificacion : ";

                    double cali;
                    cali = verificarRango(cali);                            // Se verifica que la calificacion del user sea correcta
                    string calificacion = to_string(cali * 1).substr(0, 3); // Se convierte la calificacion del user a string
                    cout << "\nLa calificacion que ingresaste es: " << calificacion << endl;

                    peliculas[pelicula - 1]->setCalificacion(calificacion);

                    modificarArchivoPeliculas(peliculas);

                    cout << "\nLa nueva calificacion de la pelicula es de: " << peliculas[pelicula - 1]->getCalificacion() << endl;

                    cout << "Los cambios se han realizado" << endl;
                }
            }
            else
            {
                cout << "No han cargado los archivos" << endl;
            }
        }

        else if (opcion == 6) // Salir
        {
            cout << "\nGracias por utilizar SensTec, tu confiable servicio de Streaming" << endl;
cout << "Hasta luego" << endl;
cout << "───────────▒▒▒▒▒▒▒▒" << endl;
cout << "─────────▒▒▒──────▒▒▒" << endl;
cout << "────────▒▒───▒▒▒▒──▒░▒" << endl;
cout << "───────▒▒───▒▒──▒▒──▒░▒" << endl;
cout << "──────▒▒░▒──────▒▒──▒░▒" << endl;
cout << "───────▒▒░▒────▒▒──▒░▒" << endl;
cout << "────────▒▒▒▒▒▒▒───▒▒" << endl;
cout << "────────────────▒▒▒" << endl;
cout << "────▒▒▒▒────────▒▒" << endl;
cout << "──▒▒▒░░▒▒▒─────▒▒──▓▓▓▓▓▓▓▓" << endl;
cout << "─▒▒─────▒▒▒────▒▒▓▓▓▓▓░░░░░▓▓──▓▓▓▓" << endl;
cout << "▒───▒▒────▒▒─▓▓▒░░░░░░░░░█▓▒▓▓▓▓░░▓▓▓" << endl;
cout << "░▒▒───▒──▓▓▓░▒░░░░░░████▓▓▒▒▓░░░░░░▓▓" << endl;
cout << "──▒▒▒▒──▓▓░░░░░░███████▓▓▓▒▒▒▒▓▓▓▓▓░░▓▓" << endl;
cout << "───────▓▓░░░░░░███████▓▓▓▒▒▒▒▒▓───▓▓░▓▓" << endl;
cout << "────▓▓░░░░░░███████▓▓▓▒▒▒▒▒▒▒▓───▓░░▓▓" << endl;
cout << "───▓▓░░░░░██████▓▓▓▓▒▒▒▒▒▒▒▒▒▓▓▓▓░░▓▓" << endl;
cout << "───▓▓▓░████▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓" << endl;
cout << "────▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓" << endl;
cout << "────▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓" << endl;
cout << "─────▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓" << endl;
cout << "──────▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓" << endl;
cout << "────────▓▓▓▓▓▓▒▒▒▒▒▓▓▓▓" << endl;
cout << endl;


            ciclarMenu = 0;
        }

        else
        {
            cout << "Valor ingresado invalida" << endl;
            cout << "Intente de nuevo" << endl;
        }

        espaciado();
        cout << endl;

    } // Fin del while del menu principal (ciclarMenu)

    return 0;
}