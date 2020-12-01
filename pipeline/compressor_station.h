#pragma once
#include<string>
#include<iostream>
#include<fstream>
class compressor_station
{
    int id;
public:
    static int MaxID;
    std::string name;                                    //имя
    int manufactory;                       //колич. цехов
    int manufactory_w;                     //колич. рабочих цехов
    float efficiency;                               //эффективность

    compressor_station();

    void EditCS();

    friend std::ostream& operator << (std::ostream& out, const compressor_station& CS_i);
    friend std::istream& operator >> (std::istream& in, compressor_station& CS_i);
    friend std::ofstream& operator << (std::ofstream& OutFile, const compressor_station& CS_i);
    friend std::ifstream& operator >> (std::ifstream& InFile, compressor_station& CS_i);
}; 

