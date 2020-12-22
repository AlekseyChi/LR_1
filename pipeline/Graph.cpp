#include <iostream>
#include <fstream>
#include <string>
#include "pipe.h"
#include "compressor_station.h"
#include "Utils.h"
#include "unordered_map"
#include "Graph.h"

using namespace std;

void DisplayGraph(unordered_map<int, vector<PCS>>& Graph, unordered_map<int, pipe>& groupP, unordered_map<int, compressor_station>& groupCS)
{
    for (auto& el : Graph)
    {
        cout << "�� � ID " << el.first << " �������� �: ";
        for (auto cs = el.second.begin(); cs != el.second.end(); cs++)
        {
            cout << cs->idCS << " �� ������ " << groupP[cs->idP].length;
            if (cs + 1 != el.second.end()) cout << ", ";
        }
        cout << endl;
    }
}

void dfs(int v, unordered_map<int, vector<PCS>>& g, unordered_map<int, bool>& count, vector<int>& ans) {
    count[v] = true;
    vector<PCS> arr;
    if (g.find(v) != g.end()) {

        arr = g[v];
        for (auto& el : arr) {
            int to = el.idCS;

            if (!count[to])
                dfs(to, g, count, ans);
        }
    }
    ans.push_back(v);
}

void topologicalSort(unordered_map<int, vector<PCS>>& g, unordered_map<int, bool>& count, vector<int>& ans) {
    for (auto& el : g)
    {
        count[el.first] = false;
        for (auto& p1 : el.second)
        {
            count[p1.idCS] = false;
        }
    };
    ans.clear();
    for (auto& el : count)
        if (!el.second)
            dfs(el.first, g, count, ans);
    reverse(ans.begin(), ans.end());
}

bool dfs2(int v, unordered_map<int, vector<PCS>>& g, unordered_map<int, int>& cl, int& cycle_st) {
    cl[v] = 1;
    if (g.find(v) == g.end())
    {
        return false;
    }
    for (size_t i = 0; i < g[v].size(); ++i) {
        int to;

        to = g[v][i].idCS;
        if (cl[to] == 0) {
            if (dfs2(to, g, cl, cycle_st))  return true;
        }
        else if (cl[to] == 1) {
            cycle_st = to;
            return true;
        }
    }
    cl[v] = 2;
    return false;
}

bool searchForCycle(unordered_map<int, vector<PCS>>& graph)
{
    unordered_map<int, int> p;
    int cycle_st, cycle_end;
    for (auto& el : graph)
    {
        p[el.first] = 0;
    }
    cycle_st = -1;
    for (auto& el : p)
        if (!el.second)
            if (dfs2(el.first, graph, p, cycle_st)) break;
    if (cycle_st == -1) return false;
    else return true;
}

void InputGraphFromFile(unordered_map<int, vector<PCS>>& graph, unordered_map<int, pipe>& groupP, unordered_map<int, compressor_station>& groupCS, string str)
{

    ifstream fin;
    fin.open(str + ".txt", ios::in);
    if (!fin.is_open())
        cout << "���� �� ����� ���� ������!\n";
    else
    {
        int buff;
        groupP.erase(groupP.begin(), groupP.end());
        fin >> buff;
        for (int j = 1; j <= buff; ++j)
        {
            pipe P;
            fin >> P;
            groupP.insert(pair<int, pipe>(P.GetId(), P));
        }

        fin >> buff;
        groupCS.erase(groupCS.begin(), groupCS.end());
        for (int j = 1; j <= buff; ++j)
        {
            compressor_station cs;
            fin >> cs;
            groupCS.insert(pair<int, compressor_station>(cs.GetId(), cs));
        }
        while (fin >> buff)
        {
            int CSid1;
            fin >> CSid1;
            for (int i = 0; i < buff; i++)
            {
                int CSid2;
                fin >> CSid2;
                int Pipeid;
                fin >> Pipeid;
                PCS pair1;
                pair1.idCS = CSid2;
                pair1.idP = Pipeid;
                graph[CSid1].push_back(pair1);
            }
        }

        cout << "����� �� ����� ������" << endl;
        fin.close();
    }

}

void OutputGraphToFile(const unordered_map<int, vector<PCS>>& graph, const unordered_map<int, pipe>& groupP, const unordered_map<int, compressor_station>& groupCS, string str)
{
    ofstream fout;
    fout.open(str + ".txt");
    if (!fout.is_open())
        cout << "���� �� ����� ���� ������!\n";
    else
    {
        fout << groupP.size() << endl;
        for (auto& P : groupP)
            fout << P.second;
        fout << endl;
        fout << groupCS.size() << endl;
        for (auto& CS : groupCS)
            fout << CS.second;
        fout << endl;
        for (auto& el : graph)
        {
            fout << el.second.size() << " ";
            fout << el.first << " ";
            for (auto cs = el.second.begin(); cs != el.second.end(); cs++)
            {
                fout << cs->idCS << " " << cs->idP << " ";
            }
            fout << endl;
        }

        cout << "������ � ���� ������" << endl;
        fout.close();
    }
}

void DeleteCSGraph(unordered_map<int, vector<PCS>>& graph, unordered_map<int, compressor_station>& groupCS)
{
    size_t a = 1;
    int idCS1 = -1;
    while (groupCS.find(idCS1) == groupCS.end())
    {
        cout << "������� Id �� ����������� ���������: ";
        idCS1 = GetCorrectNumber(a, groupCS.size());
    }
    if (graph.find(idCS1) != graph.end())
    {
        graph.erase(idCS1);
    }
    for (auto el = graph.begin(); el != graph.end(); el++)
    {
        for (auto it = 0; it < el->second.size(); it++)
        {
            if (el->second[it].idCS == idCS1) {
                el->second.erase(el->second.begin() + it);
            }
        }
    }
    cout << "������!" << endl;
}