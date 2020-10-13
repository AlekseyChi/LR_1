// pipeline.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include <iostream>

using namespace std;

struct pipe                                         //труба
{
    unsigned int id;                                //идентификатор
    float size_l;                                   //длина
    unsigned int size_w;                            //диаметр
    bool work;                                      //работает или нет
};

struct compressor_station                           //компрессорная станция(кс)
{
    unsigned int id;                                //идентификатор
    string name;                                    //имя
    unsigned int manufactory;                       //колич. цехов
    unsigned int manufactory_w;                     //колич. рабочих цехов
    unsigned int efficiency;                        //эффективность
};

void check(int &a)                                                      //проверка на число
{
    int i = 1;
    do {
        cin.clear();
        if (i==2)
        cin.ignore(1000, '\n');

        if ( i == 2) {
            i = 2;
            cin >> a;
        }
        else {
            cout << "Введите правильное значние - ";
            cin >> a;
        }
    } while (cin.fail());
};

void Menu()                                         //Меню
{
    system("CLS");
    cout << "1.Добавить трубу" << endl
        << "2.Добавит КС" << endl
        << "3.Просмотр всех объектов" << endl
        << "4.Редактировать трубу" << endl
        << "5.Редактировать КС" << endl
        << "6.Сохранить" << endl
        << "7.Загрузить" << endl
        << "0.Выход" << endl;
};

void PlusPipe(pipe &pipe_i)
{
    cout << "Введите идентификатор - ";
    cin >> pipe_i.id;
    cout << "Введите длину(м) - ";
    cin >> pipe_i.size_l;
    cout << "Введите диаметр(мм) - ";
    cin >> pipe_i.size_w;
    cout << "Введите 1, если труба работает или 0 - если труба не работает - ";
    cin >> pipe_i.work;
};

void PlusCS(compressor_station &CS_i)
{
    cout << "Введите идентификатор - ";
    cin >> CS_i.id;
    cout << "Введите название - ";
    cin >> CS_i.name;
    cout << "Введите количество цехов - ";
    cin >> CS_i.manufactory;
    cout << "Введите количество рабочих цехов - ";
    cin >> CS_i.manufactory_w;
    cout << "Введите эффективность - ";
    cin >> CS_i.efficiency;
};

void Viewer(pipe& pipe_i, compressor_station& CS_i)
{
    cout << "Труба:" << endl;
    cout << "Введите идентификатор - " << pipe_i.id << endl;
    cout << "Введите длину(м) - " << pipe_i.size_l << endl;
    cout << "Введите диаметр(мм) - " << pipe_i.size_w << endl;
    cout << "Введите 1, если труба работает или 0 - если труба не работает - " << pipe_i.work << endl;

    cout << "Компрессорная станция:" << endl;
    cout << "Введите идентификатор - " << CS_i.id << endl;
    cout << "Введите название - " << CS_i.name << endl;
    cout << "Введите количество цехов - " << CS_i.manufactory << endl;
    cout << "Введите количество рабочих цехов - " << CS_i.manufactory_w << endl;
    cout << "Введите эффективность - " << CS_i.efficiency << endl;
    system("pause");
};

void EditPipe()
{
    cout << " ";
};

void EditCS()
{
    cout << " ";
};

void Keep()
{
    cout << " ";
};

void Unload()
{
    cout << " ";
};

void InputArg()                                //работа с меню
{
    pipe P;
    compressor_station CS;

    Menu();

    int a;                                          //значение из меню
    cout << "Выберите действие - ";
    check(a);

    switch (a)
    {
    case 1:
        PlusPipe(P);
        break;
    case 2:
        PlusCS(CS);
        break;
    case 3:
        Viewer(P,CS);
        break;
    case 4:
        EditPipe();
        break;
    case 5:
        EditCS();
        break;
    case 6:
        Keep();
        break;
    case 7:
        Unload();
        break;
    case 0:
        exit(0);
        break;
    default:
        cout << "Введите верное число"<<endl;
        int b;
        cin >> b;
        InputArg();
        break;
    }
};

int main()
{    
    setlocale(LC_ALL, "Russian");
    while (true) {
        InputArg();
    }
}


