#pragma once
#include<iostream>
class pipe
{
public:
    int id;                                //�������������
    float length;                                   //�����
    int diameter;                            //�������
    bool work;                                      //�������� ��� ���

    friend std::ostream& operator << (std::ostream& out, pipe& pipe_i);
    friend std::istream& operator >> (std::istream& in, pipe& pipe_i);
};

