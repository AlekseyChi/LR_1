#include "pipe.h"
#include"Utils.h"
using namespace std;
istream& operator >> (istream& in, pipe& pipe_i)
{
    cout << "������� ������������� - ";
    pipe_i.id = GetCorrectNumber(0, 100000);
    cout << "������� �����(�) - ";
    pipe_i.length = GetCorrectNumber(0, 200);
    cout << "������� �������(��) - ";
    pipe_i.diameter = GetCorrectNumber(0, 200);
    cout << "������� 1, ���� ����� �������� ��� 0 - ���� ����� �� �������� - ";
    pipe_i.work = GetCorrectNumber(-1, 2);
    return in;
}

ostream& operator << (ostream& out, pipe& pipe_i)
{
    cout << "�����:" << endl;
    cout << "������������� - " << pipe_i.id << endl;
    cout << "�����(�) - " << pipe_i.length << endl;
    cout << "�������(��) - " << pipe_i.diameter << endl;
    cout << (pipe_i.work ? "��������" : "�� ��������") << endl << endl;
    return out;
}
