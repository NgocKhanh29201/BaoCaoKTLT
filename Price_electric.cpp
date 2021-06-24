#include"Price_electric.h"
#include"ElectricBill.h"
#include<conio.h>

using namespace std;
void PriceElectric::setElectricUse()
{   
    cout << "Dien nang tieu thu: ";
    cin >> this->electric_use;
}
void PriceElectric::setPrice()
{ 
        cout << "Nhap vao gia :";
        cin >> this->price;
}

//Hien thi toan bo file gia dien
void displayAllPriceElectric ()
{
    int stt=1;
    PriceElectric p;
    ifstream ifs("GIADIEN.BIN", ios::binary);
    cout << "STT\tDien nang\tGia" << endl;
    while (!ifs.eof())
    {
        ifs.read((char*)&p, sizeof(PriceElectric));
        if (ifs.good())
        {
            cout << stt << "\t" << p.electric_use << "\t\t" << p.price << endl;
            stt++;
        }
    }
    ifs.close();
}
//Them thong tin moc chi so dien va gia dien tuong ung
void addGIADIEN()
{
    PriceElectric p;
    char check;
    ofstream f("GIADIEN.BIN", ios::app);
    while (1)
    {
        p.setElectricUse();
        p.setPrice();
        if (f.good())
        {
            f.write((char*)&p, sizeof(PriceElectric));
        }
        cout << "An phim bat ky de tiep tuc/ 1 de ket thuc nhap\n";
        check = _getch();
        if (check == '1')
        {
            return;
        }
    }
    f.close();
    readFileGIADIEN();
}

//Thay doi thong tin cua file gia dien tai mot vi tri xac dinh
void changeInforGIADIEN()
{
    int stt;
    cout << "Nhap vao so thu tu thong tin muon thay doi: ";
    cin >> stt;
    cout << "Thong tin thay doi:" << endl;
    PriceElectric price;
    price.setElectricUse();
    price.setPrice();
    fstream f("GIADIEN.BIN");
    f.seekp((stt - 1) * sizeof(PriceElectric));
    f.write((char*)&price, sizeof(PriceElectric));
    f.close();
    readFileGIADIEN();
    
}

//Xoa thong tin 1 gia dien
void deletePriceElectric()
{
        ifstream ifs("GIADIEN.BIN");
        ofstream ofs("GIADIEN1.BIN");
        PriceElectric price;
        int moc_chi_so_dien;
        cout << "Nhap vao moc chi so dien can xoa: ";
        cin >> moc_chi_so_dien;
        while (!ifs.eof())
        {
            ifs.read((char*)&price, sizeof(PriceElectric));
            if (ifs.good())
            {
                if (price.electric_use != moc_chi_so_dien)
                    ofs.write((char*)&price, sizeof(PriceElectric));
            }
        }
        ifs.close();
        ofs.close();
        remove("GIADIEN.BIN");
        rename("GIADIEN1.BIN", "GIADIEN.BIN");
        readFileGIADIEN();
}