#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include"../lib/EGcolor.h"
using namespace std;

const int egCEDULA = 1719529438;
const string egNOMBRE_COMPLETO = "Esteban David Gomez Rocha";

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
            continue;
        }
        else
        {
            egCoordenada *egNuevaCoordenada = egCrearCoordenada(egCap, egGeo, egDet);
            egRaiz = egInsertarCoordenada(egRaiz, egNuevaCoordenada);
            egCapacidadTotal += egCap;
            egContador++;
        }
    }
    cout << "Capacidad total: " << egCapacidadTotal << endl;
    cout << "Cantidad de coordenadas: " << egContador << endl;
    egArchivo.close();
}

void egmostrarInformacion(egCoordenada *egRaiz)
{
    int egCapacidadTotal = 0;
    egCalcularCapacidadTotal(egRaiz, &egCapacidadTotal);
    cout << "Developer-Nombre: " << egNOMBRE_COMPLETO << endl;
    cout << "Developer-Cedula: " << egCEDULA << endl;
    cout << "Capacidad Bélica: " << egCapacidadTotal << endl;

    // Mostrar información de las coordenadas
    int egCantidadCoordenadas = 0;
    egCoordenada *egCoordenadas[Max_Coordenada];
    egSecuenciaCargaCoordenadas(egRaiz, egCoordenadas, &egCantidadCoordenadas);
    cout << "Coordenada-Total: " << egCantidadCoordenadas << endl;

    int egSumaSecuencia = 0;
    for (int i = 0; i < egCantidadCoordenadas; i++)
    {
        cout << "Coordenada-SecCarga[" << i << "]: " << egCoordenadas[i]->egCapacidadBelica << endl;
        egSumaSecuencia += egCoordenadas[i]->egCapacidadBelica;
    }

    if (egSumaSecuencia == egCapacidadTotal)
    {
        cout << "La suma de la secuencia de carga es igual a la capacidad total." << endl;
    }
    else
    {
        cout << "Error: La suma de la secuencia de carga no es igual a la capacidad total." << endl;
    }
}

void egCalcularCapacidadTotal(egCoordenada *egRaiz, int *egCapacidadTotal)
{
    if (egRaiz != NULL)
    {
        *egCapacidadTotal += egRaiz->egCapacidadBelica;
        egCalcularCapacidadTotal(egRaiz->egIzquierda, egCapacidadTotal);
        egCalcularCapacidadTotal(egRaiz->egDerecha, egCapacidadTotal);
    }
}
void egSecuenciaCargaCoordenadas(egCoordenada *egRaiz, egCoordenada *egCoordenadas[], int *egCantidadCoordenadas)
{
    if (egRaiz != NULL)
    {
        bool egCoordenadaRepetida = false;
        for (int i = 0; i < *egCantidadCoordenadas; i++)
        {
            if (egRaiz == egCoordenadas[i])
            {
                egCoordenadaRepetida = true;
                break;
            }
        }

        if (!egCoordenadaRepetida)
        {
            egCoordenadas[*egCantidadCoordenadas] = egRaiz; 
            (*egCantidadCoordenadas)++;                     
        }

        egSecuenciaCargaCoordenadas(egRaiz->egIzquierda, egCoordenadas, egCantidadCoordenadas);
        egSecuenciaCargaCoordenadas(egRaiz->egDerecha, egCoordenadas, egCantidadCoordenadas);
    }
}

int main()
{
    int egCedulaAutorizada;
        string egNombreCompletoAutorizado;
        cout << "Ingrese su cédula: ";
        cin >> egCedulaAutorizada;
        cout << "Ingrese su nombre completo: ";
        cin.ignore();
        getline(cin, egNombreCompletoAutorizado);
        if (egCedulaAutorizada == egCEDULA && egNombreCompletoAutorizado == egNOMBRE_COMPLETO)
        {
            egleerCoordenadas();
        }
        else
        {
            cout << "No está autorizado para ejecutar este programa." << endl;
        }
        return 0;
}