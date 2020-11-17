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
        << "9.Загрузить трубу" << endl
        << "10.Загрузить КС" << endl
        << "0.Выход" << endl;
};

void EditPipe(pipe& pipe_i)
{
    cout << "Изменить работу трубы?(да - 1, нет - 0):";
    bool i = GetCorrectNumber(-1,2);
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

void VivodTrub(ofstream& OutFile, const pipe& pipe_i)
{
    OutFile << "Труба:" << endl;
    OutFile << "Идентификатор - " << pipe_i.id << endl;
    OutFile << "Длина(м) - " << pipe_i.length << endl;
    OutFile << "Диаметр(мм) - " << pipe_i.diameter << endl;
    OutFile << (pipe_i.work ? "Работает" : "Не работает") << endl << endl;
}

void VivodCS(ofstream& OutFile, const compressor_station& CS_i)
{
    OutFile << "Компрессорная станция:" << endl;
    OutFile << "Идентификатор - " << CS_i.id << endl;
    OutFile << "Название - " << CS_i.name << endl;
    OutFile << "Количество цехов - " << CS_i.manufactory << endl;
    OutFile << "Количество рабочих цехов - " << CS_i.manufactory_w << endl;
    OutFile << "Эффективность - " << CS_i.efficiency << endl;
};

pipe VvodTrub(ifstream& InFile)
{
    pipe pipe_i;
        InFile >> pipe_i.id >> pipe_i.length >> pipe_i.diameter >> pipe_i.work;
    return pipe_i;
};

compressor_station VvodCS(ifstream& InFile)
{
    compressor_station CS_i;
        InFile >> CS_i.id >> CS_i.name >> CS_i.manufactory >> CS_i.manufactory_w >> CS_i.efficiency;
    return CS_i;
};

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
            switch (GetCorrectNumber(0,10))
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
                if (PSled) 
                { 
                    for (auto& P: groupP)
                        cout << P << endl; 
                    system("pause");
                }
                else { cout << "ВВедите трубу!"; }
                break;
            case 4:
                if (CSled) 
                { 
                    for (auto& CS : groupCS)
                        cout << CS << endl; 
                    system("pause"); 
                }
                else { cout << "Введите КС!"; }
                break;
            case 5: 
                if (PSled) { EditPipe(SelectGroup(groupP)); }
                else { cout << "Введите трубу!"; }
                break;
            case 6:
                if (CSled) { EditCS(SelectGroup(groupCS)); }
                else { cout << "Введите КС!"; }
                break;
            case 7:
                if (PSled) { 
                    ofstream FOut;
                    FOut.open("вывод трубы.txt", ios::out);
                    if (FOut.is_open())
                        {
                        for (pipe P : groupP)
                            VivodTrub(FOut, P);
                        FOut.close();
                        }
                    }
                else { cout << "Введите трубу!"; }
                break;
            case 8:
                if (CSled) {
                    ofstream fout;
                    fout.open("вывод КС.txt", ios::out);
                    if (fout.is_open())
                    {
                        for (compressor_station CS : groupCS)
                            VivodCS(fout, CS);
                        fout.close();
                    }
                }
                else { cout << "Введите КС!"; }
                break;
            case 9:
            {
                ifstream InFile;
                InFile.open("ввод трубы.txt", ios::in);
                if (!InFile.is_open())
                    cout << "Файл не может быть открыт!\n";
                else {
                    int i;
                    InFile >> i;
                    while (i--)
                        groupP.push_back(VvodTrub(InFile));
                    InFile.close();
                }
                PSled = 1;
                break;
            }
            case 10:
            {
                ifstream fin;
                fin.open("ввод КС.txt", ios::in);
                if (!fin.is_open())
                    cout << "Файл не может быть открыт!\n";
                else {
                    int i;
                    fin >> i;
                    while (i--)
                        groupCS.push_back(VvodCS(fin));
                    fin.close();
                }
                CSled = 1;
                break;
            }
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


