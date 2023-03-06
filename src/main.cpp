#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <EGcolor.h>
using namespace std;

// Constantes globales
const int CEDULA = 1719529438;
const string EGNOMBRE_COMPLETO = "Esteban David Gómez Rocha";

// Estructura para la coordenada
struct egCoordenada
{
    int egCapacidadBelica;
    string egGeoLocalizacion;
    string egdetalleArsenal;
    egCoordenada *egIzquierda;
    egCoordenada *egDerecha;
};

// Función para crear un nuevo nodo de coordenada
egCoordenada *egCrearCoordenada(int egCap, string egGeo, string egDet)
{
    egCoordenada *egNuevaCoordenada = new egCoordenada;
    egNuevaCoordenada->egCapacidadBelica = egCap;
    egNuevaCoordenada->egGeoLocalizacion = egGeo;
    egNuevaCoordenada->egdetalleArsenal = egDet;
    egNuevaCoordenada->egIzquierda = NULL;
    egNuevaCoordenada->egDerecha = NULL;
    return egNuevaCoordenada;
}

// Función para insertar una coordenada en el árbol binario de búsqueda
egCoordenada *egInsertarCoordenada(egCoordenada *egRaiz, egCoordenada *egNuevaCoordenada)
{
    // Si la raíz es NULL, se inserta la coordenada como la raíz
    if (egRaiz == NULL)
    {
        return egNuevaCoordenada;
    }
    // Si la capacidad bélica de la nueva coordenada es menor que la raíz,
    // se inserta en el subárbol izquierdo
    if (egNuevaCoordenada->egCapacidadBelica < egRaiz->egCapacidadBelica)
    {
        egRaiz->egIzquierda = egInsertarCoordenada(egRaiz->egIzquierda, egNuevaCoordenada);
    }
    // Si la capacidad bélica de la nueva coordenada es mayor que la raíz,
    // se inserta en el subárbol derecho
    else if (egNuevaCoordenada->egCapacidadBelica > egRaiz->egCapacidadBelica)
    {
        egRaiz->egDerecha = egInsertarCoordenada(egRaiz->egDerecha, egNuevaCoordenada);
    }
    // Si la capacidad bélica es igual, se descarta la coordenada duplicada
    return egRaiz;
}

// Función para leer el egArchivo de coordenadas
void leerCoordenadas()
{
    ifstream egArchivo("egCoordenadas.txt");
    string egLinea;
    int egContador = 0;
    int egCapacidadTotal = 0;
    egCoordenada *egRaiz = NULL;
    while (getline(egArchivo, egLinea))
    {
        // Mostrar loading de carga
        cout << "Loading: " << egContador << "%" << endl;
        // Comprobar si la línea es una coordenada
        stringstream ss(egLinea);
        int egCap;
        string egGeo, egDet;
        if (!(ss >> egCap >> egGeo >> egDet))
        {
            // Mostrar error en rojo si la línea no es una coordenada
            cout << "\033[31mError: La egLinea " << egContador + 1 << " no es una coordenada\033[0m" << endl;
        }
        else
        {
            // Mostrar coordenada en verde y agregarla al árbol
            egCoordenada *egNuevaCoordenada = egCrearCoordenada(egCap, egGeo, egDet);
            egRaiz = egInsertarCoordenada(egRaiz, egNuevaCoordenada);
            egCapacidadTotal += egCap;
            cout << "\033[32m" << egLinea << "\033[0m" << endl;
        }
        egContador++;
    }
    // Mostrar el total de la capacidad y la cantidad de coordenadas
    cout << "Capacidad total: " << egCapacidadTotal << endl;
    cout << "Cantidad de coordenadas: " << egContador << endl;
    // Cerrar el egArchivo
    egArchivo.close();
}

int main()
{
    leerCoordenadas();
    return 0;
}