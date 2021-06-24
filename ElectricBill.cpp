
#include"Price_electric.h"
#include"ElectricBill.h"
#include<iomanip>
#include<vector>
using namespace std;
vector<int> eUsed;
vector<int> price;

//doc toan bo file GIADIEN luu chi so va gia lan luot vao eUsed va Price
void readFileGIADIEN()
{
	eUsed.clear();
	price.clear();
	PriceElectric level_of_index_elec;
	ifstream ifs("GIADIEN.BIN");
	while (!ifs.eof())
	{
		ifs.read((char*)&level_of_index_elec, sizeof(PriceElectric));
		eUsed.push_back(level_of_index_elec.electric_use);
		price.push_back(level_of_index_elec.price);
	}
	ifs.close();
}

void ElectricBill::setID(int ID)
{
	this->ID = ID;
}

void ElectricBill::setPeriod(int cur_period)
{
	this->period = cur_period;
}

void ElectricBill::setElectricUsed(int preElectricIndex, int curElectricIndex)
{
	this->electric_used = curElectricIndex - preElectricIndex;
}


// Tinh tien dien trong mot ky
void ElectricBill::setMoney()
{
	//tinh tien dien
	int money=0;
	int i;
	int electric_used = this->electric_used;
	for (int i = 0; i < eUsed.size(); i++)
	{
		if (i == 0)
		{
			if (electric_used > eUsed[i])
			{
				money = eUsed[0] * price[0];
				electric_used -= eUsed[0];
			}
			else
			{
				money = electric_used * price[i];
				break;
			}
		}
		else
		{
			if (electric_used <= eUsed[i] - eUsed[i - 1])
			{
				money += electric_used * price[i];
				break;
			}
			else
			{
				money += (eUsed[i] - eUsed[i - 1]) * price[i];
				electric_used -= eUsed[i] - eUsed[i - 1];
			}
			if (i + 1 == eUsed.size())
				money += electric_used * price[i];
		}
	}
	this->money = money;
}

//Thiet lap thong tin hoa don tu thong tin ve dien cua mot ma khach hang
ElectricBill setBill(Electric cur_period)
{
	ElectricBill bill;
	bill.setID(cur_period.ID);
	bill.setPeriod(cur_period.period);
	int cur_index_elec = cur_period.index_electric;
	int pre_index_elec;

	// Neu chi so dien nhap vao cua ky 1 thi phai nhap so dien truoc day:
	if (cur_period.period == 1)
	{
		cout << "Nhap vao chi so dien cua cong to truoc do:";
		cin >> pre_index_elec;
	}
	else
	{
		Electric pre_period = getInfoPrePeriod(cur_period.ID, cur_period.period);
		pre_index_elec = pre_period.index_electric;
	}
	bill.setElectricUsed(pre_index_elec, cur_index_elec);
	bill.setMoney();
	return bill;
}


//ghi vao thong tin hoa don vao file
void writeToFileHD(ElectricBill bill)
{
	ofstream ofs("HOADON.BIN", ios::app);
	if (ofs.good())
	{
		ofs.write((char*)&bill, sizeof(ElectricBill));
	}
	ofs.close();
}


// Thay doi thong tin hoa don cua ki hien tại và kì sau đó khi thong tin chi so dien ky hien tại bị thay đo bi thay doi
void changeHOADON(Electric infor_elec_change,int position )
{
	fstream f("HOADON.BIN");
	ElectricBill cur_bill_change;
	cur_bill_change = setBill(infor_elec_change);
	f.seekp(position * sizeof(ElectricBill));
	f.write((char*)&cur_bill_change, sizeof(ElectricBill));
	f.close();
}

//Xoa thong tin hoa don khi thong tin o chi so dien bi xoa
void deleteBill(int position)
{
	ofstream ofs("HOADON1.BIN");
	ifstream ifs("HOADON.BIN");
	ElectricBill bill;
	int run = 0;
	while (!ifs.eof())
	{
		ifs.read((char*)&bill, sizeof(ElectricBill));
		if (run != position - 1)
		{
			if (ifs.good())
			{
				ofs.write((char*)&bill, sizeof(ElectricBill));
				run++;
			}
		}
	}
	ifs.close();
	ofs.close();
	remove("HOADON.BIN");
	rename("HOADON1.BIN", "HOADON.BIN");
}

//Doc va hien thi toan bo file Hoa Don
void displayAllBill()
{
	ifstream ifs("HOADON.BIN");
	ElectricBill bill;
	cout << "|    ID    |  ky | Dien nang tieu thu |   Thanh Tien(dong) |" << endl;
	while (!ifs.eof())
	{
		ifs.read((char*)&bill, sizeof(ElectricBill));
		if (ifs.good())
		{
			cout << "|----------------------------------------------------------|" << endl;
			cout << "|" << setw(10) << left << bill.ID << "|" << setw(5) << left << bill.period << "|";
			cout << setw(20) << left << bill.electric_used << "|" << setw(20) << left << bill.money << "|" << endl;
		}
	}
	ifs.close();
}
