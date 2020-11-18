#pragma once
#include<iostream>
class pipe
{
    int id;
public:
    static int MaxID;
    float length;                                   //длина
    int diameter;                            //диаметр
    bool work;                                      //работает или нет

    pipe();

    friend std::ostream& operator << (std::ostream& out, pipe& pipe_i);
    friend std::istream& operator >> (std::istream& in, pipe& pipe_i);
};

