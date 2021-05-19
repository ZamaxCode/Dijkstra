#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

#include <iostream>
#include <map>
#include <stdexcept>

using namespace std;

template<typename T>
class Grafo
{
public:
    Grafo(bool d = true)
    {
        digrafo = d;
    }
    bool existeArista(const T& origen, const T& destino);
    void crearArista(const T& origen, const T& destino, int costo);
    void imprimirGrafo();
    int pesoArista(const T& origen, const T& destino);

private:
    map<T, map<T, int>> grafo;
    bool digrafo;
};
#endif // GRAPH_H

template<typename T>
bool Grafo<T>::existeArista(const T &origen, const T &destino)
{
    if (grafo.find(origen) != grafo.end())
    {
        if (grafo[origen].find(destino) != grafo[origen].end())
        {
            return true;
        }
        return false;
    }
    return false;
}

template<typename T>
void Grafo<T>::crearArista(const T& origen, const T& destino, int costo)
{
    map<T, int> destinies;

    if (digrafo)
    {
        if (grafo.find(origen) != grafo.end())
        {
            destinies = grafo[origen];
        }
        destinies[destino] = costo;

        grafo[origen] = destinies;
    }
    else
    {
        map<T, int> o_d;
        map<T, int> d_o;
        if (grafo.find(origen) != grafo.end())
        {
            o_d = grafo[origen];
        }
        o_d[destino] = costo;
        if (grafo.find(destino) != grafo.end())
        {
            d_o = grafo[destino];
        }
        d_o[origen] = costo;

        grafo[origen] = o_d;
        grafo[destino] = d_o;
    }
}

template<typename T>
void Grafo<T>::imprimirGrafo()
{
    typename map<T, map<T, int>>::iterator it;

    it = grafo.begin();

    while(it != grafo.end())
    {
        typename map<T, int>::iterator itDest;
        itDest = grafo[it->first].begin();
        while(itDest != grafo[it->first].end())
        {
            cout <<"(" <<it->first <<"," <<itDest->first <<"," <<itDest->second <<")"<<endl;
            ++itDest;
        }
        ++it;
    }
}

template<typename T>
int Grafo<T>::pesoArista(const T& origen, const T& destino)
{
    if (!existeArista(origen, destino))
    {
        throw invalid_argument("La arista no existe");
    }
    return grafo[origen][destino];
}

