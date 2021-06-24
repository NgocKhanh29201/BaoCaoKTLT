#ifndef BILL_H
#define BILL_H
#include<iostream>
#include<fstream>
#include"Electric.h"
class ElectricBill
{
public:
	int ID;
	int period;
	int electric_used;
	int money;
	void setID(int);
	void setPeriod(int);
	void setElectricUsed(int, int);
	void setMoney();
	friend void writeToFileHD(ElectricBill);
};
ElectricBill setBill(Electric);
void displayAllBill();
void changeHOADON(Electric, int);
void deleteBill(int);
void readFileGIADIEN();
#endif
