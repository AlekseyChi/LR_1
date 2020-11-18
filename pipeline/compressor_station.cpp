#include "compressor_station.h"
#include"Utils.h"
using namespace std;

int compressor_station::MaxID = 0;

compressor_station::compressor_station()
{
    id = MaxID++;
}

istream& operator >> (istream& in, compressor_station& CS_i)
{
    cout << "������� �������� - ";
    cin.ignore();
    getline(cin, CS_i.name);
    cout << "������� ���������� ����� - ";
    CS_i.manufactory = GetCorrectNumber(0, 100000);
    cout << "������� ���������� ������� ����� - ";
    CS_i.manufactory_w = GetCorrectNumber(0, 100000);
    while (CS_i.manufactory_w > CS_i.manufactory)
    {
        cout << "������� �����. ���. ����� ������ ������ ����������: ";
        CS_i.manufactory_w = GetCorrectNumber(0, 100000);
    }
    cout << "������� ������������� - ";
    CS_i.efficiency = GetCorrectNumber(0.0, 1.0);
    return in;
}

ostream& operator << (ostream& out, compressor_station& CS_i)
{
    cout << CS_i.id << endl;
    cout << "������������� �������:" << endl;
    cout << "�������� - " << CS_i.name << endl;
    cout << "���������� ����� - " << CS_i.manufactory << endl;
    cout << "���������� ������� ����� - " << CS_i.manufactory_w << endl;
    cout << "������������� - " << CS_i.efficiency << endl;
    return out;
}