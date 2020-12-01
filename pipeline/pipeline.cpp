// pipeline.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "pipe.h"
#include "compressor_station.h"
#include "Utils.h"


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
        << "0.Выход" << endl;
};

void EditPipe(pipe& pipe_i)
{
    pipe_i.EditPipe();
}

void EditCS(compressor_station& CS_i) 
{
    CS_i.EditCS();
}

void DelPipe(vector <pipe>& groupP) {
    int x;
    bool y = 1;
    cout << "Введите индекс, который надо удалить:";
    while (y) {
        x = GetCorrectNumber(1, 100000);
        groupP.erase(groupP.begin() + x - 1);
        if (groupP.size() > 0)
        {
            cout << endl << "Нужно ли удалять ещё? (1 - да,0 - нет): ";
            y = GetCorrectNumber(0, 1);
        }
        else y = 0;
    }
}

void DelCS(vector <compressor_station>& CS_i) {
    int x;
    bool y = 1;
    cout << "Введите индекс, который надо удалить:";
    while (y) {
        x = GetCorrectNumber(1, 100000);
        CS_i.erase(CS_i.begin() + x - 1);
        if (CS_i.size() > 0)
        {
            cout << endl << "Нужно ли удалять ещё? (1 - да,0 - нет): ";
            y = GetCorrectNumber(0, 1);
        }
        else y = 0;
    }
}

pipe& SelectGroup(vector<pipe>& g)
{
    cout << "Введите индекс: ";
    unsigned int index = GetCorrectNumber(1u, g.size());
    return g[index - 1];
}

compressor_station& SelectGroup(vector<compressor_station>& g)
{
    cout << "Введите индекс: ";
    unsigned int index = GetCorrectNumber(1u, g.size());
    return g[index - 1];
}

vector <int> FindCSByName(const vector<compressor_station>& group, string name)
{
    vector <int> res;
    int i = 0;
    for (auto& s : group)
    {
        if (s.name == name)
            res.push_back(i);
        i++;
    }
    return res;
}

int main()
{    
    pipe P;
    compressor_station CS;
    vector <compressor_station> groupCS;
    vector <pipe> groupP;
    bool PSled = 0;
    bool CSled = 0;
    setlocale(LC_ALL, "Russian");
    while (true) {
        Menu();
        cout << "Выберите действие - ";
            switch (GetCorrectNumber(0,12))
            {
            case 1:
                cin >> P;
                groupP.push_back(P);
                PSled = 1;
                break;
            case 2:
                cin >> CS;
                groupCS.push_back(CS);
                CSled = 1;
                break;
            case 3:
            {
                if (PSled)
                {
                    for (auto& P : groupP)
                        cout << P << endl;
                    system("pause");
                }
                else { cout << "ВВедите трубу!"; }
                break;
            }
            case 4:
            {
                if (CSled)
                {
                    for (auto& CS : groupCS)
                        cout << CS << endl;
                    system("pause");
                }
                else { cout << "Введите КС!"; }
                break;
            }
            case 5: 
                if (PSled) { EditPipe(SelectGroup(groupP)); }
                else { cout << "Введите трубу!"; }
                break;
            case 6:
                if (CSled) { EditCS(SelectGroup(groupCS)); }
                else { cout << "Введите КС!"; }
                break;
            case 7:
            {
                cout << "Введите название файла для сохранения: ";
                string Name;
                cin >> Name;
                Name += ".txt";
                if (PSled) {
                    ofstream FOut;
                    FOut.open(Name, ios::out);
                    if (FOut.is_open())
                    {
                        FOut << groupP.size() << endl;
                        for (pipe& P : groupP)
                            FOut << P;
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
                if (CSled) {
                    ofstream fout;
                    fout.open("вывод КС.txt", ios::out);
                    if (fout.is_open())
                    {
                        fout << groupCS.size() << endl;
                        for (compressor_station& CS : groupCS)
                            fout << CS;
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
                    int i;
                    InFile >> i;
                    groupP.resize(i);
                    for (pipe& P : groupP)
                        InFile >> P;
                    InFile.close();
                }
                PSled = 1;
                break;
            }
            case 10:
            {
                cout << "Введите название файла для загрузки: ";
                string Name;
                cin >> Name;
                Name += ".txt";
                ifstream fin;
                fin.open("ввод КС.txt", ios::in);
                if (!fin.is_open())
                    cout << "Файл не может быть открыт!\n";
                else {
                    int i;
                    fin >> i;
                    groupP.resize(i);
                    for (pipe& P : groupP)
                        fin >> P;
                    fin.close();
                }
                CSled = 1;
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
            case 0:
                exit(0);
                break;
            default:
                cout << "Введите верное число!" << endl;
                system("pause");
                break;
            }
    }
}


