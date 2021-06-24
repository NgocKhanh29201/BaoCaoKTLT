#ifndef PRICE_H 
#define PRICE_H
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;
class PriceElectric
{   
public:
    int electric_use;  //dien nang tieu thu
    int price;
    void setElectricUse();
    void setPrice();
};
void addGIADIEN();
void displayAllPriceElectric();
void changeInforGIADIEN();
void deletePriceElectric();
#endif
