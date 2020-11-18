#pragma once
#include<iostream>
class pipe
{
    int id;
public:
    static int MaxID;
    float length;                                   //�����
    int diameter;                            //�������
    bool work;                                      //�������� ��� ���

    pipe();

    friend std::ostream& operator << (std::ostream& out, pipe& pipe_i);
    friend std::istream& operator >> (std::istream& in, pipe& pipe_i);
};

