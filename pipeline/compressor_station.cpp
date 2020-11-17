#include "compressor_station.h"
#include"Utils.h"
using namespace std;

istream& operator >> (istream& in, compressor_station& CS_i)
{
    cout << "������� ������������� - ";
    CS_i.id = GetCorrectNumber(0, 100000);
    cout << "������� �������� - ";
    cin.ignore();
    getline(cin, CS_i.name);
    cout << "������� ���������� ����� - ";
    CS_i.manufactory = GetCorrectNumber(0, 100000);
    cout << "������� ���������� ������� ����� - ";
    CS_i.manufactory_w = GetCorrectNumber(0, 100000);
    cout << "������� ������������� - ";
    CS_i.efficiency = GetCorrectNumber(0, 1);
    return in;
}

ostream& operator << (ostream& out, compressor_station& CS_i)
{
    cout << "������������� �������:" << endl;
    cout << "������������� - " << CS_i.id << endl;
    cout << "�������� - " << CS_i.name << endl;
    cout << "���������� ����� - " << CS_i.manufactory << endl;
    cout << "���������� ������� ����� - " << CS_i.manufactory_w << endl;
    cout << "������������� - " << CS_i.efficiency << endl;
    return out;
}