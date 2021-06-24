#include"Customer.h"
#include"Electric.h"
#include"Price_electric.h"
#include"ElectricBill.h"
#include<windows.h>
#include<conio.h>
using namespace std;

const char read[10][7] = { "khong ","mot ","hai ","ba ","bon ","nam ",
"sau ", "bay ", "tam ","chin " };
int arr_save_num[10]; //mang luu cac thanh phan cua so can doc

//Xac dinh don vi doc cua cac chu so tai cac vi tri
string readingUnit(int pos) //pos la vi tri cua chu so
{
    string unit = "";
    if (pos == 7) return unit;
    switch (pos)
    {
        //Neu chu so o vi tri 2 thi don vi la "trieu",...
    case 1: unit = "trieu ";
        break;
    case 4:
        if (!((arr_save_num[pos] == 0) && (arr_save_num[pos - 1] == 0) && (arr_save_num[pos - 2] == 0)))
            unit = "nghin ";
        break;
    case 2:
        if (!(((arr_save_num[pos + 2] == 0) && (arr_save_num[pos + 1] == 0)) && (arr_save_num[pos] == 0)))
            unit = "tram ";
        break;
    case 5:
        if (!(((arr_save_num[pos + 2] == 0) && (arr_save_num[pos + 1] == 0)) && (arr_save_num[pos] == 0)))
            unit = "tram ";
        break;
        // Neu chu so o vi tri 3 va 6 ma co gia tri khac 0 thi  "muoi"
        // Con neu chu so sau no co gia tri khac 0 thi la "le"
    case 3: case 6:
        if (arr_save_num[pos] != 0)
            unit = "muoi ";
        else
        {
            if (arr_save_num[pos + 1] != 0)
                unit = "le ";
        }
        break;
    }
    return unit;
}

// Lay tung chu so trong so luu vao mang, vi du 1 230 450 => 1,2,3,0,4,5,0 
void numToArray(int num)
{
    int i;
    for (i = 1; i <= 7; i++)
        arr_save_num[i] = 0;
    i = 7;
    while (num != 0)
    {
        arr_save_num[i] = num % 10;
        num = num / 10;
        i--;
    }
}

// Chuyen tu chu so sang chu
string numToText(int num)
{
    string text;
    string unitText1;
    string unitText2;
    numToArray(num);
    // dat vi tri bat dau la 8
    int staPos = 8, i;
    for (i = 1; i <= 7; i++)
        if (arr_save_num[i] != 0)
        {
            staPos = i;
            break;
        }
    //Neu chu so bat dau la o vi tri thu 8 thi so do la "khong" vi so toi da la 9 999 999 
    if (staPos == 8)
    {
        unitText1 = "Khong";
        text.append(unitText1);
        return text;
    }
    for (i = staPos; i <= 7; i++)
    {

        switch (arr_save_num[i])
        {
            /*Neu chu so tai vi tri i la 1,2,3,4,6,7,8,hoac 9 va neu chu so hang chuc
            nghin va hang chuc khac 1 thi doc cac chu so do binh thuong	*/
        case 1: case 2: case 3: case  4: case  6: case 7: case 8: case 9:
            if (!((arr_save_num[i] == 1) && ((i == 6) || (i == 3))))
                unitText1 = read[arr_save_num[i]];
            unitText2 = readingUnit(i);
            text.append(unitText1);
            text.append(unitText2);
            break;

        case 5:
            /*Neu chu so hang don vi bang 5 va chu so hang chuc bang 0
            thi doc la "nam"; con neu chu so hang chuc khac 0 thi doc la "lam"*/
            if (i == 7)
            {
                if (arr_save_num[i - 1] == 0)
                {
                    unitText1 = "nam ";
                    text.append(unitText1);
                }
                else
                {
                    unitText1 = "lam ";
                    text.append(unitText1);
                }
            }
            else
            {
                /* Neu chu so hang nghin bang 5 va chu so hang chuc nghin
                bang 0 thi doc la "nam"; con neu hang chuc nghin khac 0
                thi doc la "lam"*/
                if (i == 4)
                {
                    if (arr_save_num[i - 1] == 0)
                    {
                        unitText1 = "nam ";
                        text.append(unitText1);
                    }
                    else
                    {
                        unitText1 = "lam ";
                        text.append(unitText1);
                    }
                }
                else
                {
                    unitText1 = read[arr_save_num[i]];
                    unitText2 = readingUnit(i);
                    text.append(unitText1);
                    text.append(unitText2);
                }
            }
            break;
        case 0:
            /* Neu chu so 0 nam o hang tram/hang chuc va : chu so hang don vi khac 0
            thi chu so 0 duoc doc la "khong"*/
            if (((i == 5) || (i == 2)) && ((arr_save_num[i + 2] != 0) || ((arr_save_num[i + 1] != 0))))
            {
                unitText1 = read[arr_save_num[i]];
                unitText2 = readingUnit(i);
                text.append(unitText1);
                text.append(unitText2);
            }
            break;
        }
    }
    return text;
}

void printBill(int customer_id, int period) 
{
	Customer customer = findByID(customer_id);
	Electric electric = findElectricInfo(customer_id,period);
    Electric elec_of_pre_period = getInfoPrePeriod(customer_id, period);
	ElectricBill electric_bill = setBill(electric);
    int money_of_tax = electric_bill.money * 0.1;
    int total_money = electric_bill.money + money_of_tax;
	cout << "------------------------------------------------------------------------------------------" << endl;
	cout << "				HOA DON TIEN DIEN" << endl;
	cout << "MA KHACH HANG: " << customer_id<< endl;
	cout << "TEN KHACH HANG: " << customer.getName() << endl;
	cout << "DIA CHI: " << customer.getAddress() << endl;
	cout << "MA CONG TO: " << customer.getIdElectric() << endl;
	cout << "KY: " << electric.period << endl;
	cout << "TU NGAY: " <<elec_of_pre_period.day<<"  ---  " << "DEN NGAY: " << electric.day << endl;
	cout << "DIEN NANG TIEU THU: " << electric_bill.electric_used << endl;
	cout << "TIEN DIEN: " << electric_bill.money <<"  dong"<< endl;
	cout << "THUE(10%): " <<money_of_tax <<"  dong"<< endl;
    cout << "TONG CONG TIEN THANH TOAN: " << total_money << " - "<<numToText(total_money)<<"dong" << endl;
	cout << "------------------------------------------------------------------------------------------" << endl;
}

void gotoxy(int column, int line)
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int move()
{
    char c = _getch();
    if ((int)c == -32)
        c = _getch();

    switch ((int)c) {
    case 80:
        return 1; // Xuong
    case 72:
        return 2; // len
    case 77:
        return 3; // Phai
    case 75:
        return 4; // Trai
    case 27:
        return 0; // Esc de thoat
    case 13:
        return 5; // Enter 
    default:
        return 0;
    }
}

class Menu
{
private:
    string* item;
    int _numberOfItem;
public:
    Menu();
    void printMenu();
    int numberOfItem()
    {
        return _numberOfItem;
    }
    string* getItem()
    {
        return item;
    }
};

Menu::Menu() {
    item = new string[16];
    _numberOfItem = 16;
    item[0] = "=============================MENU=========================================";
    item[1] = "Them thong tin khach hang vao file KH.BIN";
    item[2] = "Thay doi thong tin khach hang";
    item[3] = "Xoa thong tin khach hang";
    item[4] = "Hien thi toan bo thong tin khach hang";
    item[5] = "Them thong tin chi so dien vao file CSDIEN.BIN";
    item[6] = "Thay doi thong tin chi so dien trong file CSDIEN.BIN";
    item[7] = "Xoa thong tin chi so dien ";
    item[8] = "Hien thi thong tin chi so dien cua toan bo khach hang";
    item[9] = "Them thong tin gia dien vao file GIADIEN.BIN ";
    item[10] = "Thay doi thong tin gia dien trong file GIADIEN.BIN";
    item[11] = "Xoa thong tin gia dien";
    item[12] = "Hien thi bang don gia dien";
    item[13] = "Hien thi toan bo hoa don cua khach hang ";
    item[14] = "In hoa don cua khach hang voi dau vao la ma khach hang va ki thu phi";
    item[15] = "=====================||Nhan esc de thoat||================================";
}

void Menu::printMenu() {
    for (int i = 0; i < _numberOfItem; i++) {
        gotoxy(3, i);
        cout << item[i];
        Sleep(10);
    }
}

void deleteConsole()
{
    for (int i = 17; i < 100; i++)
    {
        gotoxy(0, i);
        for (int j = 0; j < 100; j++)
        {
            cout << " ";
        }
    }
}

void selection(int line)
{
    if (line == 1)	
        addKH();
    if (line == 2)	
        changeInforKH();
    if (line == 3)	
        deleteCustomer();
    if (line == 4)	
        displayAllCus();
    if (line == 5)	
        addCSDIEN();
    if (line == 6)	
        changeInforCSDIEN();
    if (line == 7)	
        deleteElectric();
    if (line == 8)	
        displayAllElecInfo();
    if (line == 9)	
        addGIADIEN();
    if (line == 10)	
        changeInforGIADIEN();
    if (line == 11)	
        deletePriceElectric();
    if (line == 12)	
        displayAllPriceElectric();
    if (line == 13)	
        displayAllBill();
    if (line == 14)
    {
        int id_cus;
        int period;
        cout << "Nhap vao ID: ";
        cin >> id_cus;
        cout << "Nhap vao ky: ";
        cin >> period;
        printBill(id_cus, period);
    }
}

int main()
{
    readFileGIADIEN();
    readFileCSDIEN();
    readFileKH();
    Menu menu;
    int x;
    int line = 1;
    bool exit = false;
    menu.printMenu();
    gotoxy(0, line);
    cout << (char)16;
    while (!exit) {

        if (_kbhit()) {
            x = move();
            gotoxy(0, line);
            cout << " ";
            switch (x) {
            case 1:
            case 3:
            {
                line++;
                if (line >= menu.numberOfItem()) line = 1;
                break;
            }
            case 2:
            case 4:
            {
                line--;
                if (line < 1) line = menu.numberOfItem() - 1;
                break;
            }
            case 5:
            {
                deleteConsole();
                gotoxy(0, 17);
                selection(line);
                break;
            }
            case 0:
                exit = true;
            }
            gotoxy(0, line);
            cout << (char)16;
        }
    }
    deleteConsole();
    system("cls");
    cout << "CAM ON DA SU DUNG CHUONG TRINH!";
    getchar();
    return 0;
}
