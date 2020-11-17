#pragma once
#include<iostream>
class pipe
{
public:
    int id;                                //идентификатор
    float length;                                   //длина
    int diameter;                            //диаметр
    bool work;                                      //работает или нет

    friend std::ostream& operator << (std::ostream& out, pipe& pipe_i);
    friend std::istream& operator >> (std::istream& in, pipe& pipe_i);
};

