#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <fstream>

using namespace std;



vector<vector<int>> createSuccessorsList(int V, int E, vector<vector<int>> succesors);
vector<vector<int>> createSuccessorsListF(int V, int E, vector<vector<int>> successors);
vector<int> hamiltonianS(int V, int current, vector<vector<int>> successors, bool visited[], vector<int> path);
void HcycleS(int V, vector<vector<int>> successors);
vector<int> hamiltonianM(int V, int current, int **macierzSasiedztwa, bool visited[], vector<int> path);
void HcycleM(int V, int **macierzSasiedztwa);
void DirectedEuler(vector<vector<int>> successors);
void undirectedEuler(int **macierzSasiedztwa,int V);
int cinInt();
int cinV(int V);


int main()
{
    char o;
    int V, E, Vin, Vout;
    int **macierzSasiedztwa;
    bool *visited = nullptr;
    vector<vector<int>> successors;
    fstream file;

    do
    {
        cout << "1 - graf nieskierowany z klawiatury\t\t\t2 - graf nieskierowany z pliku\n3 - graf skierowany z klawiatury\t\t\t4 - graf skierowany z pliku\n";
        cout << "5 - znajdz cykl hamiltona dla grafu nieskierowanego\t6 - znajdz cykl hamiltona dla grafu skierowanego\n";
        cout << "7 - znajdz cykl eulera dla grafu nieskierowanego\t8 - znajdz cykl eulera dla grafu skierowanego\n";
        cout << "x - zakoncz dzialanie programu.\n";
        cin >> o;

        switch(o)
        {
        case '1':
        {
            cout << "Podaj liczbe wierzcholkow i krawedzi:\n";
            V = cinInt();
            E = cinInt();

            macierzSasiedztwa = new int* [V];

            for(int i=0; i<V; i++)
            {
                macierzSasiedztwa[i] = new int[V];
                for(int j=0; j<V; j++)
                {
                    macierzSasiedztwa[i][j] = 0;
                }
            }

            for(int i=0; i<E; i++)
            {
                Vout = cinV(V);
                Vin = cinV(V);
                macierzSasiedztwa[Vout-1][Vin-1] = 1;
                macierzSasiedztwa[Vin-1][Vout-1] = 1;
            }
            visited = new bool[V];
            for(int i=0; i<V; i++)
            {
                visited[i] = false;
            }

            cout<<"Macierz sasiedztwa:\n    ";
            for(int i=0; i<V; i++)
            {
                cout<<i+1<<"|";
            }
            cout<<"\n   ";
            for(int i=0; i<V*2; i++)
            {
                cout<<"_";
            }
            cout<<"\n";
            for(int i=0; i<V; i++)
            {
                cout<<i+1<<"  |";
                for(int j=0; j<V; j++)
                {
                    cout << macierzSasiedztwa[i][j] <<" ";
                }
                cout<<"\n";
            }
            cout<<"\n\n\n";
            break;
        }
        case '2':
        {
            cout << "\nDane wczytane z pliku dane.txt\n";
            file.open("dane.txt", ios::in);

            file >> V;
            file >> E;

            macierzSasiedztwa = new int* [V];

            for(int i=0; i<V; i++)
            {
                macierzSasiedztwa[i] = new int[V];
                for(int j=0; j<V; j++)
                {
                    macierzSasiedztwa[i][j] = 0;
                }
            }

            while(1)
            {
                file >> Vout;
                file >> Vin;
                macierzSasiedztwa[Vout-1][Vin-1] = 1;
                macierzSasiedztwa[Vin-1][Vout-1] = 1;
                if(file.eof())
                {
                    break;
                }
            }
            visited = new bool[V];

            for(int i=0; i<V; i++)
            {
                visited[i] = false;
            }

            file.close();
            cout<<"Macierz sasiedztwa:\n    ";
            for(int i=0; i<V; i++)
            {
                cout<<i+1<<"|";
            }
            cout<<"\n   ";
            for(int i=0; i<V*2; i++)
            {
                cout<<"_";
            }
            cout<<"\n";
            for(int i=0; i<V; i++)
            {
                cout<<i+1<<"  |";
                for(int j=0; j<V; j++)
                {
                    cout << macierzSasiedztwa[i][j] <<" ";
                }
                cout<<"\n";
            }
            cout<<"\n\n";
            break;
        }
        case '3':
        {
            cout << "Podaj liczbe wierzcholkow i krawedzi: " << endl;
            V = cinInt();
            E = cinInt();
            vector<vector<int>> successorstmp(V);
            successors = createSuccessorsList(V, E, successorstmp);
            break;
        }
        case '4':
        {
            file.open("dane.txt", ios::in);
            file >> V >> E;
            vector<vector<int>> successorstmp(V);
            file.close();
            successors = createSuccessorsListF(V, E, successorstmp);
            cout << "Graf zostal wygenerowany.\n\n";
            break;
        }
        case '5':
        {
            HcycleM(V, macierzSasiedztwa);
            break;
        }
        case '6':
        {
            HcycleS(V, successors);
            break;
        }
        case '7':
        {
            undirectedEuler(macierzSasiedztwa, V);
            break;
        }
        case '8':
        {
            DirectedEuler(successors);
            break;
        }
        case 'x':
            cout << "\nProgram zakonczony.";
            break;
        default:
            cout << "Program nie obsluguje podanej operacji\n\n";
            break;
        }

        cout << "\n\n";
    }while(o != 'x');

    return 0;
}

vector<vector<int>> createSuccessorsList(int V, int E, vector<vector<int>> successors)
{
    int a, b;
    for(int i=0; i<E; i++)
    {
        a = cinV(V) - 1;
        b = cinV(V) - 1;
        successors[a].push_back(b);
    }
    return successors;
}

vector<vector<int>> createSuccessorsListF(int V, int E, vector<vector<int>> successors)
{
    fstream file;
    file.open("dane.txt", ios::in);
    int tmp;
    file >> tmp;
    file >> tmp;
    int a, b;
    for(int i=0; i<E; i++)
    {
        file >> a;
        file >> b;
        a--;
        b--;

        if(file.eof())
            break;

        successors[a].push_back(b);
    }
    file.close();

    return successors;
}

vector<int> hamiltonianS(int V, int current, vector<vector<int>> successors, bool visited[], vector<int> path)
{
    visited[current] = 1;
    //cout << current+1 << "| ";
    for(int i=0; i<successors[current].size(); i++)
    {
        if(!visited[successors[current][i]])
        {
            path.push_back(successors[current][i]);
            path = hamiltonianS(V, successors[current][i], successors, visited, path);
        }
    }
    bool allVerticesVisited = 1;
    for(int i=0; i<V; i++)
    {
        if(!visited[i])
            allVerticesVisited = 0;
    }
    if(!allVerticesVisited)
    {
        //cout << " siemano ";
        path.pop_back();
        visited[current] = 0;
    }
    return path;
}

void HcycleS(int V, vector<vector<int>> successors)
{
    bool visited[V] = {0};
    bool cycle = 0;
    vector<int> path;
    int start = 0;
    path.push_back(start);

    path = hamiltonianS(V, start, successors, visited, path);

    if(!path.empty())
    {
        for(int i=0; i<successors[path.back()].size(); i++)
        {
            if(successors[path.back()][i] == start)
                cycle = 1;
        }
    }

    if(cycle == 1)
    {
        cout << "Znaleziony cykl hamiltona:\n";
        for(int i=0; i<path.size(); i++)
        {
            cout << path[i] + 1 << ", ";
        }
        cout << start + 1;
    }
    else
    {
        cout << "Graf wejsciowy nie zawiera cyklu hamiltona.\n";
    }
}

vector<int> hamiltonianM(int V, int current, int **macierzSasiedztwa, bool visited[], vector<int> path)
{
    visited[current] = 1;
    //cout << current+1 << "| ";
    for(int i=0; i<V; i++)
    {
        if(macierzSasiedztwa[current][i] == 1 && !visited[i])
        {
            path.push_back(i);
            path = hamiltonianM(V, i, macierzSasiedztwa, visited, path);
        }
    }
    bool allVerticesVisited = 1;
    for(int i=0; i<V; i++)
    {
        if(!visited[i])
            allVerticesVisited = 0;
    }
    if(!allVerticesVisited)
    {
        //cout << " siemano ";
        path.pop_back();
        visited[current] = 0;
    }
    return path;
}

void HcycleM(int V, int **macierzSasiedztwa)
{
    bool visited[V] = {0};
    vector<int> path;
    int start = 0;
    path.push_back(start);

    path = hamiltonianM(V, start, macierzSasiedztwa, visited, path);

    if(!path.empty())
    {
        if(macierzSasiedztwa[path.back()][start] == 1)
        {
            cout << "\nZnaleziony cykl hamiltona:\n";
            for(int i=0; i<path.size(); i++)
            {
                cout << path[i] + 1 << ", ";
            }
            cout << start + 1;
        }
    }
    else
    {
        cout << "Graf wejsciowy nie zawiera cyklu hamiltona.\n";
    }
}

void DirectedEuler(vector<vector<int>> successors)
{
    int sum = 0;
    int *outDegrees = new int[successors.size()];
    for (int i=0; i<successors.size(); i++)
    {
        //find the count of edges to keep track
        //of unused edges
        outDegrees[i] = successors[i].size();
        sum+=outDegrees[i];
    }
    int nextV;

    stack<int> currentPath;
    vector<int> finalCircuit;

    currentPath.push(0);

    int currentV = 0;
    while(!currentPath.empty())
    {
        if(outDegrees[currentV])
        {
            currentPath.push(currentV);
            nextV = successors[currentV].back();

            outDegrees[currentV]--;
            successors[currentV].pop_back();
            currentV = nextV;
        }
        else
        {
            finalCircuit.push_back(currentV);

            currentV = currentPath.top();
            currentPath.pop();
        }
    }

    if(finalCircuit[0] == finalCircuit[finalCircuit.size()-1])
    {
        for(int i=finalCircuit.size()-1;i>=0;i--)
        {
            cout << finalCircuit[i]+1 << ", ";
        }
        cout << "\n";
    }
    else
    {
        cout<<"Graf wejsciowy nie zawiera cyklu\n\n";
    }
}

void undirectedEuler(int **macierzSasiedztwa, int V)
{
    int sum = 0;
    int *outDegrees = new int[V];
    for (int i=0; i<V; i++)
    {
        outDegrees[i]=0;
        for(int j=0;j<V;j++)
        {
            outDegrees[i]+=macierzSasiedztwa[i][j];
        }
    }

    int nextV;

    stack<int> currentPath;
    vector<int> finalCircuit;

    currentPath.push(0);

    int currentV = 0;
    while(!currentPath.empty())
    {
        if(outDegrees[currentV])
        {
            currentPath.push(currentV);
            for(int i=0;i<V;i++)
            {
                if(macierzSasiedztwa[currentV][i])
                {
                    nextV = i;
                }
            }

            outDegrees[currentV]--;
            outDegrees[nextV]--;
            macierzSasiedztwa[currentV][nextV]=0;
            macierzSasiedztwa[nextV][currentV]=0;
            currentV = nextV;

            /*
            currentPath.push(currentV);
            nextV = successors[currentV].back();

            outDegrees[currentV]--;
            successors[currentV].pop_back();
            currentV = nextV;*/
        }
        else
        {
            finalCircuit.push_back(currentV);

            currentV = currentPath.top();
            currentPath.pop();
        }
    }

    if(finalCircuit[0] == finalCircuit[finalCircuit.size()-1])
    {
        for(int i=finalCircuit.size()-1; i>=0; i--)
        {
            cout << finalCircuit[i]+1 << ", ";
        }
        cout << "\n";
    }
    else
    {
        cout<<"Graf wejsciowy nie zawiera cyklu\n\n\n";
    }
}

int cinInt()
{
    int x;
    while(!(cin >> x))
    {
        cin.clear();
        cin.sync();
        cout << "Podaj liczbe: \n";
    }
    return x;
}

int cinV(int V)
{
    int x;
    while(!(cin >> x) && x <= V && x >= 0)
    {
        cin.clear();
        cin.sync();
        cout << "Podales nie istniejacy wierzcholek. Podaj liczbe mniejsza lub rowna V: \n";
    }
    return x;
}
