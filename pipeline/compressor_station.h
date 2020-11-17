#pragma once
#include<string>
#include<iostream>
class compressor_station
{
public:
    int id;                                //идентификатор
    std::string name;                                    //имя
    int manufactory;                       //колич. цехов
    int manufactory_w;                     //колич. рабочих цехов
    float efficiency;                               //эффективность

    friend std::ostream& operator << (std::ostream& out, compressor_station& CS_i);
    friend std::istream& operator >> (std::istream& in, compressor_station& CS_i);
}; 

