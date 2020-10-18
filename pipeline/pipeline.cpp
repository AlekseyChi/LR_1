// pipeline.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include <iostream>
#include <fstream>

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
    float efficiency;                        //эффективность
};

void CheckInt(unsigned int &a)                                                      //проверка на целое число(int)
{
    cin >> a;
    if (cin.fail()) {
        cin.clear();
        while (cin.get() != '\n');                                      //очищаем введенные значения
        cout << "Введите в следующий раз целое число!" << endl;
        system("pause");
        CheckInt(a);
    };
};

void CheckFloat(float& a)                                                 //проверка на число с запятой(float)
{
    cin >> a;
    if (cin.fail()) {
        cin.clear();
        while (cin.get() != '\n');                                          //очищаем введенные значения
        cout << "Введите в следующий раз число!" << endl;
        system("pause");
        CheckFloat(a);
    };
};

void CheckBool(bool& a)                                                 //проверка на булевское значение(float)
{
    cin >> a;
    if (cin.fail()) {
        cin.clear();
        while (cin.get() != '\n');                                          //очищаем введенные значения
        cout << "Введите в следующий 1 или 0!" << endl;
        system("pause");
        CheckBool(a);
    };
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
    CheckInt(pipe_i.id);
    cout << "Введите длину(м) - ";
    CheckFloat(pipe_i.size_l);
    cout << "Введите диаметр(мм) - ";
    CheckInt(pipe_i.size_w);
    cout << "Введите 1, если труба работает или 0 - если труба не работает - ";
    CheckBool(pipe_i.work);
};

void PlusCS(compressor_station &CS_i)
{
    cout << "Введите идентификатор - ";
    CheckInt(CS_i.id);
    cout << "Введите название - ";
    cin >> CS_i.name;
    cout << "Введите количество цехов - ";
    CheckInt(CS_i.manufactory);
    cout << "Введите количество рабочих цехов - ";
    CheckInt(CS_i.manufactory_w);
    cout << "Введите эффективность - ";
    CheckFloat(CS_i.efficiency);
    if (CS_i.efficiency > 1 || CS_i.efficiency < 0) {
        cout << "Введите в следующий раз значение от 0 до 1!" << endl;
        system("Pause");
        PlusCS(CS_i);
    }
};

void Viewer(pipe& pipe_i, compressor_station& CS_i)
{
    if (pipe_i.size_w != 0) {
        cout << "Труба:" << endl;
        cout << "Идентификатор - " << pipe_i.id << endl;
        cout << "Длина(м) - " << pipe_i.size_l << endl;
        cout << "Диаметр(мм) - " << pipe_i.size_w << endl;
        cout << (pipe_i.work ? "Работает" : "Не работает") << endl << endl;
    }
    else {
        cout << "Нет введенных данных"<<endl<<endl;
    }

    if (CS_i.id != 0) {
    cout << "Компрессорная станция:" << endl;
    cout << "Идентификатор - " << CS_i.id << endl;
    cout << "Название - " << CS_i.name << endl;
    cout << "Количество цехов - " << CS_i.manufactory << endl;
    cout << "Количество рабочих цехов - " << CS_i.manufactory_w << endl;
    cout << "Эффективность - " << CS_i.efficiency << endl;
    }
    else {
        cout << "Нет введенных данных" << endl << endl;
    }
};

void Keep(pipe& pipe_i, compressor_station& CS_i)
{
        ofstream OutFile("вывод.txt", ios::app);
    if (pipe_i.size_w != 0) {
        OutFile << "Труба:" << endl;
        OutFile << "Идентификатор - " << pipe_i.id << endl;
        OutFile << "Длина(м) - " << pipe_i.size_l << endl;
        OutFile << "Диаметр(мм) - " << pipe_i.size_w << endl;
        OutFile << (pipe_i.work ? "Работает" : "Не работает") << endl << endl;
    }
    else {
        OutFile << "Нет введенных данных" << endl << endl;
    };

    if (CS_i.id != 0) {
    OutFile << "Компрессорная станция:" << endl;
    OutFile << "Идентификатор - " << CS_i.id << endl;
    OutFile << "Название - " << CS_i.name << endl;
    OutFile << "Количество цехов - " << CS_i.manufactory << endl;
    OutFile << "Количество рабочих цехов - " << CS_i.manufactory_w << endl;
    OutFile << "Эффективность - " << CS_i.efficiency << endl;
    }
    else {
        OutFile << "Нет введенных данных" << endl << endl;
    }
};

void Unload(pipe& pipe_i, compressor_station& CS_i)
{
    ifstream InFile("ввод.txt");
    if (!InFile.is_open())
        cout << "Файл не может быть открыт!\n";
    else {
        InFile >> pipe_i.id >> pipe_i.size_l >> pipe_i.size_w >> pipe_i.work;
        InFile >> CS_i.id >> CS_i.name >> CS_i.manufactory >> CS_i.manufactory_w >> CS_i.efficiency;
    }
};

int main()
{    
    pipe P;
    compressor_station CS;
    P.size_w = 0;
    CS.id = 0;
    unsigned int a;                                          //значение из меню
    setlocale(LC_ALL, "Russian");
    while (true) {
        Menu();
        cout << "Выберите действие - ";
            CheckInt(a);
            switch (a)
            {
            case 1:
                PlusPipe(P);
                break;
            case 2:
                PlusCS(CS);
                break;
            case 3:
                Viewer(P, CS);
                system("pause");
                break;
            case 4:
                PlusPipe(P);
                break;
            case 5:
                PlusCS(CS);
                break;
            case 6:
                Keep(P, CS);
                break;
            case 7:
                Unload(P, CS);
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


