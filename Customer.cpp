#include "Customer.h"
#include<conio.h>
using namespace std;
vector<Customer> list_customer;

Customer::Customer() {};

Customer::Customer(int id, string name, string address, string id_electric)
{
    this->setID(id);
    this->setName(name);
    this->setAddress(address);
    this->setIDElectric(id_electric);
}

// Thiet lap ID cho doi tuong thuoc kieu Customer
void Customer::setID(int id)
{
    this->ID = id;
}

//Thiet lap ten
void Customer::setName(string name)
{
    size_t size = name.length();
    name.copy(this->name, size);//copy noi dung của string vao mang char tương ứng
    this->name[size] = '\0';  //thêm ki tự kết thúc trong mảng char sau khi copy từ string
}

//Thiet lap dia chi
void Customer::setAddress(string address)
{
    size_t size = address.length();
    address.copy(this->address, size);
    this->address[size] = '\0';
}

//Thiet lap ma cong to dien
void Customer::setIDElectric(string id_electric)
{
    size_t size = id_electric.length();
    id_electric.copy(this->id_electric, size);
    this->id_electric[size] = '\0';
}

//Lay ra ten cua khach hang
string Customer::getName()
{
    return this->name;
}

//lay dia chi khach hang
string Customer::getAddress()
{
    return this->address;
}

//Lay ra ma cong to dien
string Customer::getIdElectric()
{
    return this->id_electric;
}

//Kiem tra id da ton tai hay chua
bool checkID(int id)
{
    for (Customer cus : list_customer)
    {
        if (cus.ID == id)
            return false;
    }
    return true;
}

//Nhap thong tin khach hang
Customer inputCus()
{
    int id;
    string name;
    string add;
    string id_electric;
    while (1)
    {
        cout << "Ma khach hang: ";
        cin >> id;
        //Kiem tra ma khach hang da ton tai hay chua
        bool check = checkID(id);
        //Neu da ton tai thi nhap lai
        if (check == false)
        {
            cout << "Ma khach hang da ton tai.Vui long nhan enter de nhap lai" << endl;
        }
        //Neu khong ton tai thi tiep tuc nhap vao thong tin khach hang
        else
            break;
    }
    cin.ignore();
    cout << "Ho va ten: ";
    getline(cin, name);
    cout << "Dia chi: ";
    getline(cin, add);
    cout << "Ma cong to dien: ";
    getline(cin, id_electric);
    Customer c(id, name, add, id_electric);
    return c;
}


//Them khach hang vao file KH.BIN
void addKH()
{
    char signal;
    ofstream f("KH.BIN", ios::app);
    while (1)
    {
        Customer cus;
        cus = inputCus();
        f.write((char*)&cus, sizeof(Customer));
        list_customer.push_back(cus);
        cout << "Nhan phim bat ky de tiep tuc hoac 1 de ket thuc nhap: "<<endl;
        signal = _getch();
        if (signal == '1')
            break;
    }
    f.close();
}

//Doc toan bo file KH.BIN luu vao vecto list_customer
void readFileKH()
{
    list_customer.clear();
    
    ifstream ifs("KH.BIN", ios::binary);
    Customer cus;
    while (!ifs.eof())
    {
        ifs.read((char*)&cus, sizeof(Customer));
        if (ifs.good())
        {
            list_customer.push_back(cus);
        }
    }
    ifs.close();
}

//Hien thi toan bo thong tin khach hang trong file khach hang
void displayAllCus()
{
    int stt = 0;
    cout << "|STT |        ID     |          Ho va Ten           |            Dia Chi           |Ma cong to|" << endl;
    for (Customer cus: list_customer)
    {
        stt++;
        cout << "|---------------------------------------------------------------------------------------------|" << endl;
        cout << "|"<<setw(4) << left << stt << "|" << setw(15) << left << cus.ID << "|";
        cout << setw(30) << left << cus.getName() << "|" << setw(30) << left << cus.getAddress() << "|" << setw(10) << left << cus.getIdElectric() << "|" << endl;
    }

}

//Sua thong tin cua khach hang trong file KH
void changeInforKH()
{
    /*int stt;
    cout << "Nhap vao so thu tu khach hang muon thay doi thong tin: ";
    cin >> stt;*/
    int ID;
    int pos = 0;
    char check;
    cout << "Nhap vao ma khach hang muon thay doi thong tin: ";
    cin >> ID;
    Customer newInforCus;
    cout << "Nhap vao thong tin thay doi:" << endl;
    do
    {
        cout << "Ban co muon thay doi ma khach hang hien tai (y/n): ";
        cin >> check;
        cin.ignore();
        if (check == 'n' || check == 'N')
        {
            newInforCus.ID = ID;
            cout << "Ho va ten: ";
            string name;
            getline(cin, name);
            newInforCus.setName(name);
            cout << "Dia chi: ";
            string add;
            getline(cin, add);
            newInforCus.setAddress(add);
            cout << "Ma cong to dien: ";
            string idE;
            getline(cin, idE);
            newInforCus.setIDElectric(idE);
        }
        else if (check == 'y' || check == 'Y')
            newInforCus = inputCus();
        else
        {
            cout << "Nhap sai vui long nhap lai: "<<endl;
        }

    } while (check != 'y' && check != 'Y' && check != 'n' && check != 'N');
    for (Customer cus : list_customer)
    {
        if (cus.ID == ID)
        {
            fstream f("KH.BIN");
            f.seekp(pos * sizeof(Customer));
            f.write((char*)&newInforCus, sizeof(Customer));
            f.close();
            list_customer[pos] = newInforCus;
            break;
        }
        pos++;
    }  
}


// Xoa thong tin khach hang bat ky
void deleteCustomer()
{
    ifstream ifs("KH.BIN");
    ofstream ofs("KH1.BIN");
    Customer cus;
    int ID;
    cout << "Nhap vao ID khach hang: ";
    cin >> ID;
    while (!ifs.eof())
    {
        ifs.read((char*)&cus, sizeof(Customer));
        if (ifs.good())
        {
            if (cus.ID != ID)
                ofs.write((char*)&cus, sizeof(Customer));
        }
    }
    ifs.close();
    ofs.close();
    remove("KH.BIN");
    rename("KH1.BIN", "KH.BIN");
    readFileKH();
}

//Tim kiem khach hang bang ID
Customer findByID(int ID)
{
    for (Customer cus:list_customer)
    {
        if (cus.ID == ID)
            return cus;
    }
}