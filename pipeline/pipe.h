#pragma once
#include<iostream>
#include<fstream>
class pipe
{
    int id;
public:
    static int MaxID;
    float length;                                   //длина
    int diameter;                            //диаметр
    bool work;                                      //работает или нет

    pipe();

    void EditPipe();

    friend std::ostream& operator << (std::ostream& out, const pipe& pipe_i);
    friend std::istream& operator >> (std::istream& in, pipe& pipe_i);
    friend std::ofstream& operator << (std::ofstream& OutFile, const pipe& pipe_i);
    friend std::ifstream& operator >> (std::ifstream& InFile, pipe& pipe_i);
};

