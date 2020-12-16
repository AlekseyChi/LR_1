// pipeline.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include <iostream>
#include <fstream>
#include <string>
#include "pipe.h"
#include "compressor_station.h"
#include "Utils.h"
#include "unordered_map"

struct PCS
{
    int idP;
    int idCS;
};

using namespace std;

void Menu()                                         
{
    system("CLS");
    cout << "1.Добавить трубу" << endl
        << "2.Добавит КС" << endl
        << "3.Просмотр трубы" << endl
        << "4.Просмотр КС" << endl
        << "5.Редактировать трубу" << endl
        << "6.Редактировать КС" << endl
        << "7.Сохранить трубу" << endl
        << "8.Сохранить КС" << endl
        << "9.Загрузить из файла трубу" << endl
        << "10.Загрузить из файла КС" << endl
        << "11.Удалить трубу" << endl
        << "12.Удалить КС" << endl
        << "13.Поиск КС по названию" << endl
        << "14.Поиск трубы по признаку 'времонте'" << endl
        << "15.Пакетное редактирование труб" << endl
        << "16.Создать газотранспортную сеть" << endl
        << "17.Топологическая сортировка" << endl
        << "18.Загрузить газотранспортную сеть" << endl
        << "19.Сохранить газотранспортную сеть" << endl
        << "20.Показать газотранспортную сети" << endl
        << "21.Удалить газотранспортную сети" << endl
        << "22.Удалить КС из газотранспортной сети" << endl
        << "0.Выход" << endl;
};

void PrintPipe(unordered_map<int, pipe>& groupP)
{
    if (groupP.size() > 0)
    {
        for (auto& P : groupP)
            cout << P.second << endl;
        system("pause");
    }
    else { cout << "ВВедите трубу!"; }
}

void PrintCS(unordered_map<int, compressor_station>& groupCS)
{
    if (groupCS.size() > 0)
    {
        for (auto& CS : groupCS)
            cout << CS.second << endl;
        system("pause");
    }
    else { cout << "ВВедите трубу!"; }
}

void EditPipe(pipe& pipe_i)
{   
    cout << "Изменить работу трубы?(да - 1, нет - 0):";
    bool i = GetCorrectNumber(0, 1);
    if (i == 1) {
        pipe_i.work = !pipe_i.work;
    }
}

void EditCS(compressor_station& CS_i) 
{
    cout << "Добавить рабочую КС?(да - 1, нет - 0):";
    bool i = GetCorrectNumber(-1, 2);
    if (i == 1 && CS_i.manufactory > CS_i.manufactory_w) {
        CS_i.manufactory_w++;
    }
    cout << "Убрать рабочую КС?(да - 1, нет - 0):";
    i = GetCorrectNumber(-1, 2);
    if (i == 1 && CS_i.manufactory > CS_i.manufactory_w) {
        CS_i.manufactory_w--;
    }
}

void DelPipe(unordered_map<int, pipe>& groupP) 
{
    size_t a = 1;
    if (groupP.size() > 0)
    {
        for (auto& P : groupP)
            cout << P.second << endl;
        system("pause");
    }
    else { cout << "ВВедите трубу!"; }

    if (groupP.size() > 0) {
        int number;
        do {
            cout << "Введите ID КС, которую нужно удалить: ";
            number = GetCorrectNumber(a, groupP.size());
        } while (groupP.find(number) == groupP.end());
        groupP.erase(groupP.find(number));
    }
}

void DelCS(unordered_map<int, compressor_station>& CS_i) 
{
    size_t a = 1;
    if (CS_i.size() > 0)
    {
        for (auto& P : CS_i)
            cout << P.second << endl;
        system("pause");
    }
    else { cout << "ВВедите трубу!"; }

    if (CS_i.size() > 0) {
        int number;
        do {
            cout << "Введите ID КС, которую нужно удалить: ";
            number = GetCorrectNumber(a, CS_i.size());
        } while (CS_i.find(number) == CS_i.end());
        CS_i.erase(CS_i.find(number));
    }
}

pipe& SelectPipe(unordered_map<int, pipe>& g)
{
    size_t a = 1;
    cout << "Введите индекс: ";
    unsigned int index = GetCorrectNumber(a, g.size());
    return g[index];
}

compressor_station& SelectCS(unordered_map<int, compressor_station>& g)
{
    size_t a = 1;
    cout << "Введите индекс: ";
    unsigned int index = GetCorrectNumber(a, g.size());
    return g[index];
}

template<typename PC,typename T>
using FilterCS = bool(*)(PC& CS, T param);

bool CheckByName(compressor_station& CS, string param)
{
    return CS.name == param;
}

template<typename PC,typename T>
vector <int> FindByFilter(unordered_map<int, PC>& group, FilterCS<PC, T> f, T param)
{
    vector <int> res;
    res.reserve(group.size());
    for (auto& pipe : group)
    {
        if (f(pipe.second, param))
            res.push_back(pipe.first);
    }
    return res;
}

bool CheckByWork(pipe& P, bool param)
{
    return P.work == param;
}

bool CheckByLength(pipe& P, float param)
{
    return P.length == param;
}

bool CheckByDiam(pipe& P, int param)
{
    return P.diameter == param;
}

void DisplayGraph(unordered_map<int, vector<PCS>>& Graph, unordered_map<int, pipe>& groupP, unordered_map<int, compressor_station>& groupCS)
{
    for (auto& el : Graph)
    {
        cout << "КС с ID " << el.first << " соединен с: ";
        for (auto cs = el.second.begin(); cs != el.second.end(); cs++)
        {
            cout << cs->idCS << " кс длиной " << groupP[cs->idP].length;
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
    }
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

void InputGraphFromFile(unordered_map<int, vector<PCS>>& graph, string str)
{

    ifstream fin(string(str) + ".txt");
    if (!fin.is_open())
        cout << "Файл не может быть открыт!\n";
    else
    {
        int buff;
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
        cout << "Ввели из файла данные";
        fin.close();
    }

}

void OutputGraphToFile(unordered_map<int, vector<PCS>> graph, string str)
{

    ofstream fout;
    fout.open(string(str) + ".txt");
    if (!fout.is_open())
        cout << "Файл не может быть открыт!\n";
    else
    {

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
        cout << "Вывели в файл данные";
        fout.close();
    }
}

void DeleteCSGraph(unordered_map<int, vector<PCS>>& graph, unordered_map<int, compressor_station>& groupCS)
{
    size_t a = 1;
    int idCS1 = -1;
    while (groupCS.find(idCS1) == groupCS.end())
    {
        cout << "Введите Id Кс необходимую отключить: ";
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
    cout << "Удален!" << endl;
}

int main()
{    
    unordered_map<int, pipe> groupP;
    unordered_map<int, compressor_station> groupCS;
    unordered_map<int, vector<PCS>> Graph;
    size_t a = 1;
    setlocale(LC_ALL, "Russian");
    while (true) {
        Menu();
        cout << "Выберите действие - ";
            switch (GetCorrectNumber(0,22))
            {
            case 1:
            {
                pipe P;
                cin >> P;
                groupP.insert(pair<int, pipe>(P.GetId(), P));
                break;
            }
            case 2:
            {
                compressor_station CS;
                cin >> CS;
                groupCS.insert(pair<int, compressor_station>(CS.GetId(), CS));
                break;
            }
            case 3:
            {
                PrintPipe(groupP);
                break;
            }
            case 4:
            {
                PrintCS(groupCS);
                break;
            }
            case 5: 
                if (groupP.size()>0) { EditPipe(SelectPipe(groupP)); }
                else { cout << "Введите трубу!"; }
                break;
            case 6:
                if (groupCS.size()>0) { EditCS(SelectCS(groupCS)); }
                else { cout << "Введите КС!"; }
                break;
            case 7:
            {
                cout << "Введите название файла для сохранения: ";
                string Name;
                cin >> Name;
                Name += ".txt";
                if (groupP.size()>0) {
                    ofstream FOut;
                    FOut.open(Name, ios::out);
                    if (FOut.is_open())
                    {
                        FOut << groupP.size() << endl;
                        for (auto& P : groupP)
                            FOut << P.second;
                        FOut.close();
                    }
                }
                else { cout << "Введите трубу!"; }
                break;
            }
            case 8:
            {
                cout << "Введите название файла для сохранения: ";
                string Name;
                cin >> Name;
                Name += ".txt";
                if (groupCS.size()>0) {
                    ofstream fout;
                    fout.open(Name, ios::out);
                    if (fout.is_open())
                    {
                        fout << groupCS.size() << endl;
                        for (auto& CS : groupCS)
                            fout << CS.second;
                        fout.close();
                    }
                }
                else { cout << "Введите КС!"; }
                break;
            }
            case 9:
            {
                cout << "Введите название файла для загрузки: ";
                string Name;
                cin >> Name;
                Name += ".txt";
                ifstream InFile;
                InFile.open(Name, ios::in);
                if (!InFile.is_open())
                    cout << "Файл не может быть открыт!\n";
                else {
                    groupP.erase(groupP.begin(), groupP.end());
                    int i;
                    InFile >> i;
                    for (int j = 1; j <= i; ++j)
                    {
                        pipe P;
                        InFile >> P;
                        groupP.insert(pair<int, pipe>(P.GetId(), P));
                    }
                    InFile.close();
                }
                break;
            }
            case 10:
            {
                cout << "Введите название файла для загрузки: ";
                string Name;
                cin >> Name;
                Name += ".txt";
                ifstream fin;
                fin.open(Name, ios::in);
                if (!fin.is_open())
                    cout << "Файл не может быть открыт!\n";
                else {
                    int i;
                    fin >> i;
                    groupCS.erase(groupCS.begin(), groupCS.end());
                    for (int j = 1; j <= i; ++j)
                    {
                        compressor_station cs;
                        fin >> cs;
                        groupCS.insert(pair<int, compressor_station>(cs.GetId(), cs));
                    }
                    fin.close();
                }
                break;
            }
            case 11:
            {
                DelPipe(groupP);
                break;
            }
            case 12:
                DelCS(groupCS);
                break;
            case 13:
            {
                string name;
                cout << "Введите название КС: ";
                cin.ignore();
                getline(cin, name);
                for (int i : FindByFilter(groupCS, CheckByName, name))
                    cout << groupCS[i];
                system("pause");
                break;
            }
            case 14:
            {
                bool name;
                cout << "Искать рабочие трубы(1), не рабочие(0): ";
                cin >> name;
                for (int i : FindByFilter(groupP, CheckByWork, name))
                    cout << groupP[i];
                system("pause");
                break;
            }
            case 15:
            {
                bool j;
                cout << "Чтобы найти трубы по параметру введите 1, по промежутку - 0: ";
                j = GetCorrectNumber(0, 1);
                if (j) {
                    cout << "Выберете параметр поиска" << endl
                        << "1. Длина" << endl
                        << "2. Работа" << endl;
                    switch (GetCorrectNumber(1,3))
                    {
                        case 1:
                        {
                            cout << "Введите длину, необходимую заменить - ";
                            float c = GetCorrectNumber(1.0, 100000.0);
                            cout << "Введите новую длину - ";
                            float b = GetCorrectNumber(1.0, 100000.0);
                            for (int i : FindByFilter(groupP, CheckByLength, c))
                                groupP[i].length = b;
                        }
                            break;
                        case 2:
                        {
                            cout << "Введите работу, необходимую заменить - ";
                            bool c = GetCorrectNumber(0, 1);
                            cout << "Введите новую работу - ";
                            bool b = GetCorrectNumber(0, 1);
                            for (int i : FindByFilter(groupP, CheckByWork, c))
                                groupP[i].work = b;
                        }
                            break;
                    }
                }
                else {
                    int a, b;
                    int right = groupP.size();
                    cout << "Введите начальный индекс: ";
                    a = GetCorrectNumber(0, right);
                    cout << "Введите конечный индекс: ";
                    b = GetCorrectNumber(a, right);
                    cout << "Выберете параметр изменения" << endl
                        << "1. Длинна" << endl
                        << "2. Ширина" << endl
                        << "3. Работа" << endl
                        << "0. Вернутся обратно" << endl;
                    switch (GetCorrectNumber(0, 3)) {
                    case 1:
                    {
                        cout << "Введите длинну - ";
                        float c = GetCorrectNumber(0, 1000000);
                        for (int i = a; i < b; i++) {
                            groupP[i].length = c;
                        }
                        break;
                    }
                    case 2:
                    {
                        cout << "Введите диаметр - ";
                        int c = GetCorrectNumber(0, 1000000);
                        for (int i = a; i < b; i++) {
                            groupP[i].diameter = c;
                        }
                        break;
                    }
                    case 3:
                    {
                        cout << "Введите работу - ";
                        bool c = GetCorrectNumber(0, 1);
                        for (int i = a; i < b; i++) {
                            groupP[i].work = c;
                        }
                        break;
                    }
                    }
                }
            }
                break;
            case 16:
            {
                int i;
                int j = 0;
                PCS pcs;
                PrintPipe(groupP);
                PrintCS(groupCS);
                if (groupCS.size() > 1 && groupP.size()>0)
                {
                    cout << "Введите колество труб: ";
                    i = GetCorrectNumber(a, groupP.size());
                    while (i > 0) {
                        cout << "Введите id КС, от которой идёт труба: ";
                        int idCS1 = GetCorrectNumber(a, groupCS.size());
                        cout << "Введите id КС, в которую идёт труба: ";
                        pcs.idCS = GetCorrectNumber(a, groupCS.size());
                        cout << "Введите id трубы: ";
                        pcs.idP = GetCorrectNumber(a, groupP.size());

                        Graph[idCS1].push_back(pcs);
                        i--;
                    }
                    DisplayGraph(Graph,groupP,groupCS);
                }
                else
                {
                    cout << "Невозможно выполнить операцию";
                };
                system("pause");
                break;
            }
            case 17:
            {
                if (!searchForCycle(Graph))
                {
                    unordered_map<int, bool> count;
                    vector<int> ans;
                    topologicalSort(Graph, count, ans);
                    for (auto index = ans.begin(); index != ans.end(); index++)
                    {
                        cout << *index;
                        if (index + 1 != ans.end()) cout << " -> ";
                    }
                    system("pause");
                }
                else
                {
                    cout << "Граф цикличный!" << endl;
                }
            system("pause");
                break;
            }
            case 18:
            {
                string str;
                cout << "Введите название файла: ";
                cin >> str;
                InputGraphFromFile(Graph, str);

                system("pause");
                break;
                break;
            }
            case 19:
            {
                string str;
                cout << "Введите название файла: ";
                cin >> str;
                OutputGraphToFile(Graph, str);

                system("pause");
                break;
            }
            case 20:
            {
                DisplayGraph(Graph, groupP, groupCS);
                system("pause");
                break;
            }
            case 21:
            {
                Graph.clear();
                break;
            }
            case 22:
            {
                PrintCS(groupCS);
                DeleteCSGraph(Graph, groupCS);
                system("pause");
                break;
            }
            case 0:
                exit(0);
                break;
            default:
                cout << "Введите верное число!" << endl;
                break;
            }
    }
}


