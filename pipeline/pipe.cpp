#include "pipe.h"
#include"Utils.h"
using namespace std;

int pipe::MaxID = 0;

pipe::pipe()
{
    id = MaxID++;
}

istream& operator >> (istream& in, pipe& pipe_i)
{
    cout << "Введите длину(м) - ";
    pipe_i.length = GetCorrectNumber(0, 200);
    cout << "Введите диаметр(мм) - ";
    pipe_i.diameter = GetCorrectNumber(0, 200);
    cout << "Введите 1, если труба работает или 0 - если труба не работает - ";
    pipe_i.work = GetCorrectNumber(-1, 2);
    return in;
}

ostream& operator << (ostream& out, pipe& pipe_i)
{
    cout << "Труба:" << endl;
    cout << "Длина(м) - " << pipe_i.length << endl;
    cout << "Диаметр(мм) - " << pipe_i.diameter << endl;
    cout << (pipe_i.work ? "Работает" : "Не работает") << endl << endl;
    return out;
}
