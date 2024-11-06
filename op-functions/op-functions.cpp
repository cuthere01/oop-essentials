#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <conio.h>
#include <Windows.h>
#include <locale.h>
#include <stdlib.h>

using namespace std;
struct date { int d, m, y, h, min; };
struct aero {
    string city;
    string num;
    date dr;
};
struct card {
    string name;
    string surname;
    string patronymic;
    int price;
    aero info;
};

ostream& operator<<(ostream& out, card& z);
int operator>(card v, card w)
{
    if (v.surname > w.surname) return 1;
    if ((v.surname == w.surname) && (v.name > w.name)) return 1;
    if ((v.surname == w.surname) && (v.name == w.name) && (v.patronymic > w.patronymic)) return 1;
    return 0;
}
ostream& operator<<(ostream& out, card& z)
{
    string fio;
    fio = z.surname + " " + z.name + " " + z.patronymic;
    out << setw(38) << fio << " | " << setw(8) << z.price << " | " << setw(16)
        << z.info.city << " | " << setw(11) << z.info.num << " | " << setw(4) << z.info.dr.d
        << " | " << setw(5) << z.info.dr.m << " | " << setw(5) << z.info.dr.y << " | " << setw(2) << z.info.dr.h << ":" << setw(2) << z.info.dr.min << " | \n";
    return out;
}

class masA
{
private:
    card* px;
    int n;
public:

    // Специальные методы класса:
    masA() :px(NULL), n(0) {};
    masA(masA& z);
    ~masA() { if (px != NULL) delete[]px; }
    masA& operator=(masA& z);

    // Методы класса masA:
    void inputFile();
    void addaero();
    void deleteaero();
    void output();
    void outputFile();
    void sortName();
    void sortPrice();
    void sortCity();
    friend ostream& operator<<(ostream& out, masA& z);
};

ostream& operator<<(ostream& out, masA& z)
{
    int i;
    // Вывод заголовка таблицы (массива структур)
    out << "   _________________________________________________________________________________________________________________________\n";
    out << "  |     |                                        |          |                  |             |     Дата и время вылета      |\n";
    out << "  |  №  |                 Ф.И.О.                 |   Цена   | Пункт назначения | Номер рейса |______________________________| \n";
    out << "  |     |                                        |          |                  |             | День | Месяц |  Год  | Время |\n";
    out << "  |_____|________________________________________|__________|__________________|_____________|______|_______|_______|_______|\n";
    out << "  |     |                                        |          |                  |             |      |       |       |       |\n";

    // Вывод строк таблицы
    for (i = 0; i < z.n; i++)
        out << "  | " << setw(3) << i + 1 << " | " << z.px[i];
    // out<<z.px[i]  это перегруженная операция вывода для структуры 
    // типа card
    out << "  |_____|________________________________________|__________|__________________|_____________|______|_______|_______|_______|\n";
    system("pause");
    return out;
}

masA::masA(masA& z)
{
    int i;
    n = z.n;
    if (z.px == NULL) px = NULL;
    else
    {
        px = new card[n];
        if (px == NULL)
        {
            cout << "Нет памяти\n";
            system("pause");
            exit(1);
        }
        for (i = 0; i < n; i++)
            px[i] = z.px[i];
        cout << "Копирование завершено" << endl;
        system("pause");
    }
}
masA& masA :: operator=(masA& z)
{
    int i;
    if (this == &z) return *this;
    if (px != NULL) delete[]px;
    n = z.n;
    if (z.px == NULL) px = NULL;
    else {
        px = new card[n];
        if (px == NULL) {
            cout << "нет памяти.\n";
            cout << "операция присваивания.\n";
            system("pause"); return z;
        }
        for (i = 0; i < n; i++)
            px[i] = z.px[i];
    }
    return *this;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void masA::inputFile()   //  ввод исходного массива структур из файла
{
    ifstream fin;
    string file;
    // string iniz;
    card t;
    cout << "Имя входного файла: ";
    cin >> file;
    fin.open(file.c_str());

    //  Защита от неправильного ввода имени файла
    if (fin.fail()) {
        cout << file << " не открывается\n";
        system("pause");
        return;
    }

    n = 0;
    if (px != NULL) { delete[] px; px = NULL; }     // очистка массива

    while (1)
    {
        fin >> t.surname >> t.name >> t.patronymic >> t.price >> t.info.city >> t.info.num >> t.info.dr.d >> t.info.dr.m >> t.info.dr.y >> t.info.dr.h >> t.info.dr.min;
        if (fin.fail()) break;
        n++;
    }
    fin.close();
    fin.open(file.c_str());
    if (fin.fail()) {
        cout << file << "повторно не открывается\n";
        n = 0;  system("pause"); return;
    }
    px = new card[n];
    if (px == NULL) {
        cout << "Нет памяти.\n"; fin.close();
        cout << "Ввести фаил не удается.\n";
        n = 0;  system("pause"); return;
    }
    for (int i = 0; i < n; i++) // !!!!!
    {
        fin >> px[i].surname >> px[i].name >> px[i].patronymic >> px[i].price >> px[i].info.city >> px[i].info.num >> px[i].info.dr.d >> px[i].info.dr.m >> px[i].info.dr.y >> px[i].info.dr.h >> px[i].info.dr.min;
    }
    fin.close();
    cout << "Файл введен " << endl;
    //getch();
    system("pause");
}

void masA::addaero()
{
    setlocale(LC_ALL, "");
    int i;
    card t, * p;
    p = new card[n + 1];                          // выделение памяти для нового массива
    if (p == NULL) {
        cout << "нет памяти.\n";
        cout << "Добавить не удается.\n";
        system("pause"); return;
    }

    cout << "ФИО:"; cin >> t.surname >> t.name >> t.patronymic;
    cout << "Цена билета:"; cin >> t.price;
    cout << "Пункт назначения:"; cin >> t.info.city;
    cout << "Номер рейса:"; cin >> t.info.num;
    cout << "Дата и время вылета.\n";
    cout << "День:";   cin >> t.info.dr.d;
    cout << "Месяц:"; cin >> t.info.dr.m;
    cout << "Год:";  cin >> t.info.dr.y;
    cout << "Часы:";  cin >> t.info.dr.h;
    cout << "Минуты:";  cin >> t.info.dr.min;
    for (i = 0; i < n; i++)
        p[i] = px[i];                         // копирования старого массива в новый
    p[n] = t;                                  // добавление новой записи в массив структур
    n++;                                     // увеличение счетчика количества записей

    if (px != NULL) delete[] px; // удаление старого массива
    px = p;                                   // адрес нового массива заносится в px

    cout << "Запись добавлена.\n";
    system("pause");
}

void masA::deleteaero()
{
    int j, i;
    card* p;
    char ch;

    output();                 //  вызов на экран массива структур
    cout << "Номер удаленой стороки:";
    cin >> j;
    /*if (cin.fail())
    {
        string s;
        cin.clear();
        cin >> s;
        cout << "Это не номер строки \n";
        system("pause"); //getch();
        return;
    }*/

    if (j < 1 || j >= n) {
        cout << "Ошибка: нет такой строки.\n";
        system("pause"); //getch(); 
        return;
    }
    j--; //  переход от номера удаленной строки к ее индексу
    cout << j + 1 << "-я строка:\n";
    cout << px[j].surname << " " << px[j].name << " " << px[j].patronymic << " " << px[j].price << " " << px[j].info.city << " " << px[j].info.num << " " << px[j].info.dr.d << " " << px[j].info.dr.m
        << " " << px[j].info.dr.y << endl;

    cout << "Удалить?(y/n):"; cin >> ch;
    if (ch == 'n') return;               //     отказ удаления строки
    if (ch != 'y') { cout << "Ошибка ответа на вопрос. \n"; system("pause"); return; }

    //   Выполнение удаления строки     
    if (ch == 'y')
    {
        p = new card[n - 1];
        if (p == NULL) {
            cout << "Нет памяти.\n ";
            cout << "Удалить не удается.\n";
            system("pause"); return;
        }
        for (i = 0; i < j; i++)
            p[i] = px[i];
        for (i = j + 1; i < n; i++)
            p[i - 1] = px[i];
        delete[] px;           // удаление старого массива
        px = p;                    // адрес нового массива заносится в поле px
        n--;                       //  уменьшение счетчика количества записей
    }
    cout << "Запись удалена.\n";
    //getch();
    system("pause");
}

void masA::sortPrice()               // по году рождения
{
    int i, fl, nn;
    card t;
    nn = n;                                       // вводим копию размера массива
    do {
        fl = 0; nn--;
        for (i = 0; i < nn; i++)
            if (px[i].price < px[i + 1].price)
            {
                fl = 1;  t = px[i];
                px[i] = px[i + 1];
                px[i + 1] = t;
            }
    } while (fl == 1);
    cout << "Массив структур упорядочен по цене\n";
    //getch();
    system("pause");
}

void masA::sortName()
{
    int i, fl, nn;
    card t;

    nn = n;
    do {
        fl = 0; nn--;
        for (i = 0; i < nn; i++)
            if (px[i] > px[i + 1])   //  это перегруженная операция  “>”
            {
                fl = 1; t = px[i];
                px[i] = px[i + 1];
                px[i + 1] = t;
            }

    } while (fl == 1);
    cout << "Массив структур упорядочен по ФИО в алфавитном порядке\n";
    //getch();
    system("pause");
}

void masA::sortCity()            // сортировка по дате рождения
{
    int fl, i, nn;
    card t;

    nn = n;
    do {
        fl = 0; nn--;
        for (i = 0; i < nn; i++)
            if (px[i].info.city > px[i + 1].info.city) ////!!!
            {
                fl = 1; t = px[i];
                px[i] = px[i + 1];
                px[i + 1] = t;
            }
    } while (fl == 1);
    cout << "Массив структур упорядочен по пункту назначения\n";
    //getch();
    system("pause");
}

void masA::output()
{
    int i;
    string fio;
    // Вывод заголовка таблицы (массива структур)
    cout << "   _________________________________________________________________________________________________________________________\n";
    cout << "  |     |                                        |          |                  |             |     Дата и время вылета      |\n";
    cout << "  |  №  |                 Ф.И.О.                 |   Цена   | Пункт назначения | Номер рейса |______________________________| \n";
    cout << "  |     |                                        |          |                  |             | День | Месяц |  Год  | Время |\n";
    cout << "  |_____|________________________________________|__________|__________________|_____________|______|_______|_______|_______|\n";
    cout << "  |     |                                        |          |                  |             |      |       |       |       |\n";
    // Вывод строк таблицы
    for (i = 0; i < n; i++)
    {
        fio = px[i].surname + " " + px[i].name + " " + px[i].patronymic;
        cout << "  | " << setw(3) << i + 1 << " | " << setw(38) << fio << " | " << setw(8) << px[i].price << " | " << setw(16)
            << px[i].info.city << " | " << setw(11) << px[i].info.num << " | " << setw(4) << px[i].info.dr.d
            << " | " << setw(5) << px[i].info.dr.m << " | " << setw(5) << px[i].info.dr.y << " | " << setw(2) << px[i].info.dr.h << ":" << setw(2) << px[i].info.dr.min << " | \n";
    }
    cout << "  |_____|________________________________________|__________|__________________|_____________|______|_______|_______|_______|\n";

    //getch();
    system("pause");
}

void masA::outputFile()
{
    ofstream fout;
    string file;
    int i;
    string fio;
    cout << "Имя выходного файла:";   cin >> file;
    fout.open(file.c_str()); ///!!!!

    //  Защита от неправильного ввода имени файла
    if (fout.fail()) {
        cout << file << "не создается.\n";
        system("pause");
        return;
    }

    //    // Вывод заголовка
    fout << "   _________________________________________________________________________________________________________________________\n";
    fout << "  |     |                                        |          |                  |             |     Дата и время вылета      |\n";
    fout << "  |  №  |                 Ф.И.О.                 |   Цена   | Пункт назначения | Номер рейса |______________________________| \n";
    fout << "  |     |                                        |          |                  |             | День | Месяц |  Год  | Время |\n";
    fout << "  |_____|________________________________________|__________|__________________|_____________|______|_______|_______|_______|\n";
    fout << "  |     |                                        |          |                  |             |      |       |       |       |\n";
    // Вывод строк таблицы
    for (i = 0; i < n; i++)
    {
        fio = px[i].surname + " " + px[i].name + " " + px[i].patronymic;
        fout << "  | " << setw(3) << i + 1 << " | " << setw(38) << fio << " | " << setw(8) << px[i].price << " | " << setw(16)
            << px[i].info.city << " | " << setw(11) << px[i].info.num << " | " << setw(4) << px[i].info.dr.d
            << " | " << setw(5) << px[i].info.dr.m << " | " << setw(5) << px[i].info.dr.y << " | " << setw(2) << px[i].info.dr.h << ":" << setw(2) << px[i].info.dr.min << " | \n";

    }
    fout << "  |_____|________________________________________|__________|__________________|_____________|______|_______|_______|_______|\n";
    fout.close();
    cout << "Массив структур сохранен в фаил\n";
    system("pause");
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "");
    masA a;
    int j;

    while (1)
    {
        system("cls");
        cout << "1. Ввод исх. массива из файла\n";
        cout << "2. Вывод исх. массива на экран\n";
        cout << "3. Вывод исх. массива в текстовой файл\n";
        cout << "4. Добавить запись в исх. массив\n";
        cout << "5. Удалить запись из исх. массива\n";
        cout << "6. Сортировка исх. массива по Ф.И.О.\n";
        cout << "7. Сортировка исх. массива по пункту назначения\n";
        cout << "8. Сортировка исх. массива по цене\n";
        cout << "9. Проверка конструктора копирования для masА\n";
        cout << "10. Проверка перегр-й операции присваивания для masА\n";
        cout << "11. Выход из программы\n";
        cout << "Ваш выбор (1-11): ";
        cin >> j;
        //    Защита от неправильного ввода пункта меню
        if (cin.fail())
        {
            string s;
            cin.clear();
            cin >> s;
            cout << "Это не пункт меню\n";
            system("pause");
            continue;          //   K следующей итерации
        }
        //    Реализация выбранного пункта меню
        switch (j)
        {
        case 1: a.inputFile(); break;
        case 2: cout << a; break;
        case 3: a.outputFile(); break;
        case 4: a.addaero(); break;
        case 5: a.deleteaero(); break;
        case 6: a.sortName(); break;
        case 7: a.sortCity(); break;
        case 8: a.sortPrice(); break;
        case 9:
        {
            masA b(a);
            cout << a;
            cout << b;
        } break;
        case 10:
        {
            masA f, d;
            f = d = a;
            cout << f; cout << d; cout << a;
        } break;
        case 11: cout << "Конец работы\n"; return 0;
        default: cout << "Нет такого пункта в меню\n"; system("pause"); break;
        } // конец switch()
    } // конец while()
} // конец main()
