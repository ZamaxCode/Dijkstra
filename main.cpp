#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <fstream>
#include "Grafo.h"
#define V 16

using namespace std;

void cargarGrafo();
int** crearTabla(int tablaEtq[V][V]);
int minDistance(int dist[], bool sptSet[]);
int darSolucion(int dist[], int n, int dest);
int dijkstra(int tablaEtq[V][V], int src, int dest);
Grafo<string> grf;
string camino[V];

int main()
{
    int dirInicial,dirRest,dirCasa, result1,result2;
    char inicial,rest,casa;
    int tablaEtq[V][V];

    cargarGrafo();
    crearTabla(tablaEtq);

    do{
        for(int i=0;i<V;i++)
            camino[i].clear();

        system("CLS");
        cout<<" ______________________________________"<<endl;
        cout<<"|Lista de Casas\t|Lista de restaurantes|"<<endl;
        cout<<"|B\t\t|A                    |"<<endl;
        cout<<"|C\t\t|H                    |"<<endl;
        cout<<"|D\t\t|N                    |"<<endl;
        cout<<"|E\t\t|                     |"<<endl;
        cout<<"|F\t\t|                     |"<<endl;
        cout<<"|G\t\t|                     |"<<endl;
        cout<<"|I\t\t|                     |"<<endl;
        cout<<"|J\t\t|                     |"<<endl;
        cout<<"|K\t\t|                     |"<<endl;
        cout<<"|L\t\t|                     |"<<endl;
        cout<<"|M\t\t|                     |"<<endl;
        cout<<"|O\t\t|                     |"<<endl;
        cout<<"|P\t\t|                     |"<<endl;
        cout<<"|_______________|_____________________|"<<endl<<endl;

        cout<<"En donde te encuentras: ";
        cin>>inicial;
        inicial=toupper(inicial);
        cout<<"A que restaurante debes ir: ";
        cin>>rest;
        rest=toupper(rest);
        cout<<"A donde lo debes entregar: ";
        cin>>casa;
        casa=toupper(casa);

        dirInicial=inicial-65;
        dirRest=rest-65;
        dirCasa=casa-65;

        cout<<endl<<endl;

        result1=dijkstra(tablaEtq, dirInicial, dirRest);
        cout<<"Actual\tRestaurante"<<endl;
        cout<<inicial<<"\t"<<rest<<endl;
        cout<<"Distancia a recorrer: "<<result1<<" metros."<<endl;
        cout<<camino[dirRest]<<rest<<endl<<endl;
        for(int i=0;i<V;i++)
            camino[i].clear();

        result2=dijkstra(tablaEtq, dirRest, dirCasa);
        cout<<"Restaurante\tCasa"<<endl;
        cout<<rest<<"\t\t"<<casa<<endl;
        cout<<"Distancia a recorrer: "<<result2<<" metros."<<endl;
        cout<<camino[dirCasa]<<casa<<endl<<endl;
        for(int i=0;i<V;i++)
            camino[i].clear();

        cout<<endl<<"Distancia total: "<<result1+result2<<" metros."<<endl<<endl;

        system("PAUSE");
    }while(1);


    return 0;
}

void cargarGrafo()
{
    fstream ciudad;
    ciudad.open("ciudad.txt",ios::in);
    string vertice1, vertice2,peso;

    while(!ciudad.eof())
    {
        getline(ciudad,vertice1,',');
        getline(ciudad,vertice2,',');
        getline(ciudad,peso,'\n');
        if(ciudad.eof())
            break;
        grf.crearArista(vertice1,vertice2,atoi(peso.c_str()));
    }
    ciudad.close();
}

int** crearTabla(int tablaEtq[V][V])
{
    string v1,v2;
    for(int i=0;i<V;i++)
    {
        v1=i+65;
        for(int j=0;j<V;j++)
        {
            v2=j+65;
            if(grf.existeArista(v1,v2))
            {
                tablaEtq[i][j]=grf.pesoArista(v1,v2);
            }
            else
            {
                tablaEtq[i][j]=0;
            }
        }
    }
}

int minDistance(int dist[], bool sptSet[])
{
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

int darSolucion(int dist[], int n, int dest)
{
    for (int i = 0; i < V; i++)
        if(i==dest)
            return dist[i];
}

int dijkstra(int tablaEtq[V][V], int src, int dest)
{
    int dist[V];
    bool sptSet[V];
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
    dist[src] = 0;
    for (int count = 0; count < V - 1; count++)
    {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;
        for (int v = 0; v < V; v++)
            if (!sptSet[v] && tablaEtq[u][v] && dist[u] != INT_MAX && dist[u] + tablaEtq[u][v] < dist[v])
                {
                    dist[v] = dist[u] + tablaEtq[u][v];
                    if(sptSet[dest]==false)
                    {
                        camino[v]=camino[u];
                        camino[v]+=u+65;
                        camino[v]+=',';
                    }
                }
    }
    int resultado=darSolucion(dist, V, dest);
    return resultado;
}
