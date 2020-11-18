#pragma once
#include<string>
#include<iostream>
class compressor_station
{
    int id;
public:
    static int MaxID;
    std::string name;                                    //���
    int manufactory;                       //�����. �����
    int manufactory_w;                     //�����. ������� �����
    float efficiency;                               //�������������

    compressor_station();

    friend std::ostream& operator << (std::ostream& out, compressor_station& CS_i);
    friend std::istream& operator >> (std::istream& in, compressor_station& CS_i);
}; 

