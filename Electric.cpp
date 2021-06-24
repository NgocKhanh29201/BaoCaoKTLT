#include"Electric.h"
#include"Customer.h"
#include"ElectricBill.h"
#include<conio.h>
vector <Electric> list_elec_info;

//Nhap ID khach hang dong thoi kiem tra ID khach hang co ton tai trong file khach hang ko
void  Electric::setID()
{
    Customer c;
    int id;
    while (1)
    {
        cout << "Nhap vao ma khach hang: ";
        cin >> id;
        ifstream f("KH.BIN", ios::binary);
        while (!f.eof())
        {
            f.read((char*)&c, sizeof(Customer));
            //Neu Ma Id khach hang da ton tai thi tiep tuc chuong trinh
            if (c.ID == id)
            {
                this->ID = id;
                f.close();
                return;
            }
        }
        //Neu khong thi nhap lai 
        cout << "Ma khach hang vua nhap khong ton tai.Vui long nhap lai"<<endl;
    }
}

//thiet lap ngay chot dien
void Electric::setDay(string day)
{
    day.copy(this->day, day.length());
    this->day[day.length()] = '\0';
}

//Nhap thong tin chi so dien
Electric inputE()
{
    Electric e;
    string day;
    e.setID();
    cout << "Chi so dien: ";
    cin >> e.index_electric;
    cin.ignore();
    cout << "Ngay chot chi so dien:";
    getline(cin, day);
    e.setDay(day);
    cout << "Ky thu phi: ";
    cin >> e.period;
    return e;
}

//Doc file CSDIEN va luu vao list_elec_info
void readFileCSDIEN()
{
    list_elec_info.clear();
    Electric e;
    ifstream ifs("CSDIEN.BIN");
    while (!ifs.eof())
    {
        ifs.read((char*)&e, sizeof(Electric));
        if (ifs.good())
        {
            list_elec_info.push_back(e);
        }
    }
    ifs.close();
}


//Them doi tuong vao file CSDIEN
void addCSDIEN()
{
    char signal;
    //int position_add=0;
    fstream f("CSDIEN.BIN", ios::app);
    while (1)
    {
        Electric e;
        e = inputE();
        f.write((char*)&e, sizeof(Electric));
        list_elec_info.push_back(e);
        ElectricBill bill;
        bill = setBill(e);
        writeToFileHD(bill);
        cout << "An phim bat ki de tiep tuc /phim 1 de dung nhap.\n";
        signal =_getch();
        if (signal == '1')
            break;
    }
    f.close();
   
}
//Sua thong tin o file CSDIEN cua mot doi tuong bat ki 
void changeInforCSDIEN()
{
    int id_cus;
    int period;
    cout << "Nhap vao ma khach hang muon thay doi thong tin: ";
    cin >> id_cus;
    cout << "Nhap vao ky muon thay doi thong tin: ";
    cin >> period;
    int pos = 0;
    Electric new_info_elec;
    cout << "Nhap vao thong tin thay doi:" << endl;
    new_info_elec = inputE();
    fstream f("CSDIEN.BIN");
    for (Electric elec : list_elec_info)
    {
        if (elec.ID == id_cus && elec.period == period)
        {
            f.seekp(pos * sizeof(Electric));
            f.write((char*)&new_info_elec, sizeof(Electric));
            changeHOADON(new_info_elec, pos);
            list_elec_info[pos] =new_info_elec;
            //f.seekg(pos * sizeof(Electric));
            //f.read((char*)&elec, sizeof(Electric));
        }
        if (elec.ID == id_cus)
        {
            if (elec.period == period + 1)
            {
                changeHOADON(elec, pos);
                break;
            }
        }
        pos++;
    }
    f.close();
}

//Xoa thong tin cua mot chi so dien
void deleteElectric()
{
    ifstream ifs("CSDIEN.BIN");
    ofstream ofs("CSDIEN1.BIN");
    Electric elec;
    int stt;
    cout << "Nhap vao stt thong tin xoa: ";
    cin >> stt;
    int i=1;
    while (!ifs.eof())
    {
        ifs.read((char*)&elec, sizeof(Electric));
        if (i == stt)
        {
            i++;
            continue;
        }
        if (ifs.good())
        {
            ofs.write((char*)&elec, sizeof(Electric));
        }
        i++;
    }
    ifs.close();
    ofs.close();
    remove("CSDIEN.BIN");
    rename("CSDIEN1.BIN", "CSDIEN.BIN");
    deleteBill(stt);
    readFileCSDIEN();
}
void displayAllElecInfo()
{
    int stt = 0;
    cout << "|STT |    ID    |  Chi so  |    Ngay   |  Ky |" << endl;
    for (Electric elec : list_elec_info)
    {
        stt++;
        cout << "|--------------------------------------------|" << endl;
        //  printf("|%-4d|%-10d|%-10d|%-11d|%-5d|\n",stt, ID, index_electric, day, period);
        cout << "|" << setw(4) << left << stt << "|" << setw(10) << left << elec.ID << "|" << setw(10) << left << elec.index_electric << "|";
        cout << setw(11) << left << elec.day << "|" << setw(5) << elec.period << "|" << endl;
    }
}

//Ham tim thong tin ve dien cua mot khach hang trong mot ki xac dinh
Electric findElectricInfo(int id, int period)
{
    for (Electric elec : list_elec_info)
    {
        if (elec.ID == id && elec.period == period)
            return elec;
    }

}

Electric getInfoPrePeriod(int cur_id_cus, int cur_period)
{
    for (Electric elec_info : list_elec_info)
    {
        if (elec_info.ID == cur_id_cus)
        {
            if (elec_info.period == cur_period - 1)
                return elec_info;
        }
    }
}