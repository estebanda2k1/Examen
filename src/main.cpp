#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include"../lib/EGcolor.h"
using namespace std;

const int CEDULA = 1719529438;
const string EGNOMBRE_COMPLETO = "Esteban David Gómez Rocha";

struct egCoordenada
{
    int egCapacidadBelica;
    string egGeoLocalizacion;
    string egdetalleArsenal;
    egCoordenada *egIzquierda;
    egCoordenada *egDerecha;
};

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

egCoordenada *egInsertarCoordenada(egCoordenada *egRaiz, egCoordenada *egNuevaCoordenada)
{
    if (egRaiz == NULL)
    {
        return egNuevaCoordenada;
    }
    if (egNuevaCoordenada->egCapacidadBelica < egRaiz->egCapacidadBelica)
    {
        egRaiz->egIzquierda = egInsertarCoordenada(egRaiz->egIzquierda, egNuevaCoordenada);
    }
    else if (egNuevaCoordenada->egCapacidadBelica > egRaiz->egCapacidadBelica)
    {
        egRaiz->egDerecha = egInsertarCoordenada(egRaiz->egDerecha, egNuevaCoordenada);
    }
    return egRaiz;
}

void egleerCoordenadas()
{
    ifstream egArchivo("../files/egCoordenadasUcranianas.txt");
    string egLinea;
    int egContador = 0;
    int egCapacidadTotal = 0;
    egCoordenada *egRaiz = NULL;
    while (getline(egArchivo, egLinea))
    {
        cout << "Loading: " << egContador << "%" << endl;
        stringstream ss(egLinea);
        int egCap;
        string egGeo, egDet;
        if (!(ss >> egCap >> egGeo >> egDet))
        {
            cout << "\033[31mError: La egLinea " << egContador + 1 << " no es una coordenada\033[0m" << endl;
        }
        else
        {
            egCoordenada *egNuevaCoordenada = egCrearCoordenada(egCap, egGeo, egDet);
            egRaiz = egInsertarCoordenada(egRaiz, egNuevaCoordenada);
            egCapacidadTotal += egCap;
            cout << "\033[32m" << egLinea << "\033[0m" << endl;
        }
        egContador++;
    }
    cout << "Capacidad total: " << egCapacidadTotal << endl;
    cout << "Cantidad de coordenadas: " << egContador << endl;
    egArchivo.close();
}

int main()
{
    egleerCoordenadas();
    return 0;
}