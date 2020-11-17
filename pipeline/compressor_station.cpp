#include "compressor_station.h"
#include"Utils.h"
using namespace std;

istream& operator >> (istream& in, compressor_station& CS_i)
{
    cout << "Введите идентификатор - ";
    CS_i.id = GetCorrectNumber(0, 100000);
    cout << "Введите название - ";
    cin.ignore();
    getline(cin, CS_i.name);
    cout << "Введите количество цехов - ";
    CS_i.manufactory = GetCorrectNumber(0, 100000);
    cout << "Введите количество рабочих цехов - ";
    CS_i.manufactory_w = GetCorrectNumber(0, 100000);
    cout << "Введите эффективность - ";
    CS_i.efficiency = GetCorrectNumber(0, 1);
    return in;
}

ostream& operator << (ostream& out, compressor_station& CS_i)
{
    cout << "Компрессорная станция:" << endl;
    cout << "Идентификатор - " << CS_i.id << endl;
    cout << "Название - " << CS_i.name << endl;
    cout << "Количество цехов - " << CS_i.manufactory << endl;
    cout << "Количество рабочих цехов - " << CS_i.manufactory_w << endl;
    cout << "Эффективность - " << CS_i.efficiency << endl;
    return out;
}