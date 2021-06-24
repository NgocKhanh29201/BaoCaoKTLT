#ifndef CUSTOMER_H 
#define CUSTOMER_H
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<iomanip>
using namespace std;

class Customer
{
public:
    int ID; //Ma so khach hang
private:
    char name[50]; //Ten khach hang
    char address[100];  //dia chi
    char id_electric[50];    //Ma cong to dien
public:
    Customer();
    Customer(int, string, string, string);
    void setID(int);
    void setName(string);
    void setAddress(string);
    void setIDElectric(string);
    string getName();
    string getAddress();
    string getIdElectric();
};
bool checkID(int);
Customer inputCus();
void addKH();
void readFileKH();
void changeInforKH();
void deleteCustomer();
void displayAllCus();
Customer findByID(int ID);
#endif
