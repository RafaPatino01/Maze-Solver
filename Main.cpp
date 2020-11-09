#include <iostream>
#include "Graph.h"
#include "FiFo.h"
#include <algorithm>

#include <stdint.h>
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define CHANNEL_NUM 1
#include "stb_image.h"
#include "stb_image_write.h"
using namespace std;

Graph Cuadricula(int pSize) {
    Graph Cuadricula = Graph(pSize*pSize);

    list<int> izquierda;
    list<int> derecha;
    
    for (int i = 1; i <= pSize; i++)
    {
        izquierda.push_back(i*pSize);
        derecha.push_back((pSize * (i + 1)) - 1);
    }

    for (int i = 0; i < pSize * pSize; i++)
    {
        if ((i > 0)&&(i < pSize - 1)) //Arriba
        {
            Cuadricula.addEdge(i, i-1); 
            Cuadricula.addEdge(i, i+1);
            Cuadricula.addEdge(i, i+pSize);
        }
        else if (find(izquierda.begin(), izquierda.end(), i) != izquierda.end()) //Izquierda
        {
            Cuadricula.addEdge(i, i + pSize);
            Cuadricula.addEdge(i, i - pSize);
            Cuadricula.addEdge(i, i + 1);
        }
        else if ((find(derecha.begin(), derecha.end(), i) != derecha.end()) && (i != ((pSize * pSize) - 1))) //Derecha
        {
            Cuadricula.addEdge(i, i + pSize);
            Cuadricula.addEdge(i, i - pSize);
            Cuadricula.addEdge(i, i - 1);
        }
        else if ((i > pSize * (pSize - 1)) && (i < (pSize * pSize) - 1)) //Abajo
        {
            Cuadricula.addEdge(i, i-1);
            Cuadricula.addEdge(i, i+1);
            Cuadricula.addEdge(i, i-pSize);
        }
        else if (i == 0) //CERO
        {
            Cuadricula.addEdge(i, i + 1);
            Cuadricula.addEdge(i, i + pSize);
        }
        else if (i == pSize - 1) // Arriba-Derecha
        {
            Cuadricula.addEdge(i, i - 1);
            Cuadricula.addEdge(i, i + pSize);
        }
        else if (i == pSize * (pSize - 1)) // Abajo-Izquierda
        {
            Cuadricula.addEdge(i, i - pSize);
            Cuadricula.addEdge(i, i + 1);
        }
        else if (i == (pSize * pSize) - 1) //Abajo-Derecha
        {
            Cuadricula.addEdge(i, i - pSize);
            Cuadricula.addEdge(i, i - 1);
        }
        else
        {
            Cuadricula.addEdge(i, i + 1);
            Cuadricula.addEdge(i, i - 1);
            Cuadricula.addEdge(i, i + pSize);
            Cuadricula.addEdge(i, i - pSize);
        }
    }

    return(Cuadricula);
}

Graph Laberinto(const char* pPath)
{
    int Width, Height, Bpp;
    list<int> Walls;
    uint8_t* read_img = stbi_load(pPath, &Width, &Height, &Bpp, 1);

    Graph Maze = Cuadricula(Width); //Crear Grafo de N*N


    for (int i = 0; i < Width* Height; i++)
    {
        if (read_img[i] == 0)
        {
            Maze.Adj_L[i].empty();
            Walls.push_back(i);
            for (int j = 0; j < Width * Height; j++)
            {
                Maze.Adj_L[j].remove(i);
            }
        }
    }
    return(Maze);
}

void ShowRute(Graph pMap, const char* pPath, int pStart, int pEnd)
{
    list<int> Camino = pMap.BFS(pStart, pEnd);

    int size = Camino.size();
    int Var;
    cout << "Ruta desde " << pStart << " hasta "<< pEnd << endl;



    int Width, Height, Bpp;
    uint8_t* Maze_Img = stbi_load(pPath, &Width, &Height, &Bpp, 1);

    for (int i = 0; i < size; i++)
    {
        Var = Camino.back();
        Camino.pop_back();
        cout << Var << endl;
        if (i == 0)
        {
            Maze_Img[Var] = 140;
        }
        else 
        {
            Maze_Img[Var] = 200;
        }
    }
    Maze_Img[Var] = 140;

    stbi_write_png("C:/Users/ESTAFETA PEROTE/Desktop/Tests/MazeSolved.png", Width, Height, CHANNEL_NUM, Maze_Img, Width * CHANNEL_NUM);

}

// To do:
// Medir eficiencia
// Generar maze aleatorio
int main()
{
    //Path
    const char* path = "C:/Users/ESTAFETA PEROTE/Desktop/Tests/Maze.png";

    Graph Mapa = Laberinto(path);
    ShowRute(Mapa, path, 0, 1024);
}
