#ifndef ELECTRIC_H 
#define ELECTRIC_H
#include<iostream>
#include<fstream>
using namespace std;
class Electric
{
public:
    int ID; //ma Khach hang 
    int index_electric; //chi so dien 
    char day[15]; // ngay chot chi so dien 
    int period; //ky thu phi
    void setID();
    void setDay(string);
};
Electric inputE();
void addCSDIEN();
void readFileCSDIEN();
void changeInforCSDIEN();
void deleteElectric();
void displayAllElecInfo();
Electric getInfoPrePeriod(int, int);
Electric findElectricInfo(int,int);
#endif
