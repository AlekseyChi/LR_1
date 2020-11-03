// pipeline.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct pipe                                         //труба
{
    int id;                                //идентификатор
    float length;                                   //длина
    int diameter;                            //диаметр
    bool work;                                      //работает или нет
};

struct compressor_station                           //компрессорная станция(кс)
{
    int id;                                //идентификатор
    string name;                                    //имя
    int manufactory;                       //колич. цехов
    int manufactory_w;                     //колич. рабочих цехов
    float efficiency;                               //эффективность
};

template <typename T>

T GetCorrectNumber(T left, T right)
{
    T x;
    while (((cin >> x)).fail() || x<left || x>right)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Ошибка при вводе!" << endl << "Введите команду: ";
    }
    return x;
}


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

pipe PlusPipe()
{
    pipe pipe_i;
    cout << "Введите идентификатор - ";
    pipe_i.id = GetCorrectNumber(0,100000);
    cout << "Введите длину(м) - ";
    pipe_i.length = GetCorrectNumber(0,200);
    cout << "Введите диаметр(мм) - ";
    pipe_i.diameter = GetCorrectNumber(0,200);
    cout << "Введите 1, если труба работает или 0 - если труба не работает - ";
    pipe_i.work = GetCorrectNumber(-1,2);
    return pipe_i;
};

compressor_station PlusCS()
{
    compressor_station CS_i;
    cout << "Введите идентификатор - ";
    CS_i.id = GetCorrectNumber(0,100000);
    cout << "Введите название - ";
    cin.ignore();
    getline(cin, CS_i.name);
    cout << "Введите количество цехов - ";
    CS_i.manufactory = GetCorrectNumber(0, 100000);
    cout << "Введите количество рабочих цехов - ";
    CS_i.manufactory_w = GetCorrectNumber(0,100000);
    cout << "Введите эффективность - ";
    CS_i.efficiency = GetCorrectNumber(0,1);
    return CS_i;
};

void ViewerPipe(const pipe& pipe_i)
{
    if (pipe_i.diameter != 0) {
        cout << "Труба:" << endl;
        cout << "Идентификатор - " << pipe_i.id << endl;
        cout << "Длина(м) - " << pipe_i.length << endl;
        cout << "Диаметр(мм) - " << pipe_i.diameter << endl;
        cout << (pipe_i.work ? "Работает" : "Не работает") << endl << endl;
    }
    else {
        cout << "Нет введенных данных!" << endl << endl;
    }
};

void ViewerCS(const compressor_station & CS_i)
{
    if (CS_i.id != 0) {
    cout << "Компрессорная станция:" << endl;
    cout << "Идентификатор - " << CS_i.id << endl;
    cout << "Название - " << CS_i.name << endl;
    cout << "Количество цехов - " << CS_i.manufactory << endl;
    cout << "Количество рабочих цехов - " << CS_i.manufactory_w << endl;
    cout << "Эффективность - " << CS_i.efficiency << endl;
    }
    else {
        cout << "Нет введенных данных!" << endl << endl;
    }
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

void VivodTrub(const pipe& pipe_i)
{
        ofstream OutFile;
        OutFile.open("вывод трубы.txt", ios::out);
        if (pipe_i.diameter != 0) {
            OutFile << "Труба:" << endl;
            OutFile << "Идентификатор - " << pipe_i.id << endl;
            OutFile << "Длина(м) - " << pipe_i.length << endl;
            OutFile << "Диаметр(мм) - " << pipe_i.diameter << endl;
            OutFile << (pipe_i.work ? "Работает" : "Не работает") << endl << endl;
        }
        else {
            OutFile << "Нет введенной трубы!" << endl << endl;
        };
        OutFile.close();
}

void VivodCS(const compressor_station& CS_i)
    {
    ofstream OutFile;
    OutFile.open("вывод КС.txt", ios::out);
    if (CS_i.id != 0) {
    OutFile << "Компрессорная станция:" << endl;
    OutFile << "Идентификатор - " << CS_i.id << endl;
    OutFile << "Название - " << CS_i.name << endl;
    OutFile << "Количество цехов - " << CS_i.manufactory << endl;
    OutFile << "Количество рабочих цехов - " << CS_i.manufactory_w << endl;
    OutFile << "Эффективность - " << CS_i.efficiency << endl;
    }
    else {
        OutFile << "Нет введенной КС!" << endl << endl;
    }
    OutFile.close();
};

pipe VvodTrub()
{
    pipe pipe_i;
    ifstream InFile;
    InFile.open("ввод трубы.txt", ios::in);
    if (!InFile.is_open())
        cout << "Файл не может быть открыт!\n";
    else {
        InFile >> pipe_i.id >> pipe_i.length >> pipe_i.diameter >> pipe_i.work;
    }
    InFile.close();
    return pipe_i;
};

compressor_station VvodCS()
{
    compressor_station CS_i;
    ifstream InFile;
    InFile.open("ввод КС.txt", ios::in);
    if (!InFile.is_open())
        cout << "Файл не может быть открыт!\n";
    else {
        InFile >> CS_i.id >> CS_i.name >> CS_i.manufactory >> CS_i.manufactory_w >> CS_i.efficiency;
    }
    InFile.close();
    return CS_i;
};

int main()
{    
    pipe P;
    compressor_station CS;
    bool PSled = 0;
    bool CSled = 0;
    setlocale(LC_ALL, "Russian");
    while (true) {
        Menu();
        cout << "Выберите действие - ";
            switch (GetCorrectNumber(0,10))
            {
            case 1:
                P = PlusPipe();
                PSled = 1;
                break;
            case 2:
                CS = PlusCS();
                CSled = 1;
                break;
            case 3:
                if (PSled) { ViewerPipe(P); system("pause");}
                else { cout << "ВВедите трубу!"; }
                break;
            case 4:
                if (CSled) { ViewerCS(CS); system("pause"); }
                else { cout << "Введите КС!"; }
                break;
            case 5: 
                if (PSled) { EditPipe(P); }
                else { cout << "Введите трубу!"; }
                break;
            case 6:
                if (CSled) { EditCS(CS); }
                else { cout << "Введите КС!"; }
                break;
            case 7:
                if (PSled) { VivodTrub(P); }
                else { cout << "Введите трубу!"; }
                break;
            case 8:
                if (CSled) { VivodCS(CS); }
                else { cout << "Введите КС!"; }
                break;
            case 9:
                P = VvodTrub();
                PSled = 1;
                break;
            case 10:
                CS = VvodCS();
                CSled = 1;
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


