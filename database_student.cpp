#include <iostream>
#include <windows.h>
#include <cstring>
#include <fstream>
#include <iomanip>

using namespace std;

const int AR_SIZE = 50;
const int FAMILY_SIZE = 50;
const int NAME_SIZE = 50;
const int OTCH_SIZE = 50;

struct student {
    char family[FAMILY_SIZE]{ "No Fam" };
    char name[NAME_SIZE]{ "No Name" };
    char otch[OTCH_SIZE]{ "No Otch" };
    int kurs{};
    struct {
        int mat{};
        int angeom{};
        int inzhgraph{};
        int vp{};
    } grade{};
};

void main_menu(student group[AR_SIZE]);
void addData(student group[AR_SIZE]);
void inputKlav(student group[AR_SIZE]);
void outputDataTable(student group[AR_SIZE]);
void DeleteData(student group[AR_SIZE]);
void outputData(student group[AR_SIZE]);
void printRequest(student group[AR_SIZE]);
void Edit(student group[AR_SIZE]);
void Sort(student group[AR_SIZE]);
void outputSort(student temp[AR_SIZE]);
void outputToFile(student group[AR_SIZE]);
void inputFromFile(student group[AR_SIZE]);
void TxtToBin(student group[AR_SIZE]);
void BinToBase(student group[AR_SIZE]);
int check_digit(char*);

int main()
{
    student group[AR_SIZE];
    setlocale(LC_ALL, "Russian");
    main_menu(group);
    return 0;
}

void main_menu(student group[AR_SIZE]) {
    enum Num_of_commands {
        INPUT = 1,
        EDIT,
        DELET,
        SORT,
        OUTPUT,
        REQUEST,
        BDTOBIN,
        EXIT
    };
    bool good_ind = 0;
    int ind_menu = 0;
    system("cls");
    cout << "\n";
    cout << "|=============================================|\n";
    cout << "|-----------База данных студентов-------------|\n";
    cout << "|=============================================|\n";
    cout << "|-----|---------------------------------------|\n";
    cout << "|  1  |Добавление записи;                     |\n";
    cout << "|-----|---------------------------------------|\n";
    cout << "|  2  |Изменение записи;                      |\n";
    cout << "|-----|---------------------------------------|\n";
    cout << "|  3  |Удаление записи;                       |\n";
    cout << "|-----|---------------------------------------|\n";
    cout << "|  4  |Сортировка;                            |\n";
    cout << "|-----|---------------------------------------|\n";
    cout << "|  5  |Вывод данных;                          |\n";
    cout << "|-----|---------------------------------------|\n";
    cout << "|  6  |Средний балл любого курса(запрос);     |\n";
    cout << "|-----|---------------------------------------|\n";
    cout << "|  7  |Перевод текстового файла БД в бинарный;|\n";
    cout << "|-----|---------------------------------------|\n";
    cout << "|  8  |Выход;                                 |\n";
    cout << "|-----|---------------------------------------|\n";
    cout << "\n";
    cout << " Введите нужный элемент меню: ";
    if (!(cin >> ind_menu) || (cin.peek() != '\n')) {
        cin.clear();
        while (cin.get() != '\n');
        MessageBox(nullptr, TEXT("Ошибка! Введено неверное значение пункта меню.\nПожалуйста, введите верное значение пункта меню."), TEXT("Ошибка"), MB_OK);
        main_menu(group);
    }
    switch (ind_menu) {
    case INPUT:
        addData(group);
        break;
    case EDIT:
        Edit(group);
        break;
    case DELET:
        DeleteData(group);
        break;
    case SORT:
        Sort(group);
        break;
    case OUTPUT:
        outputData(group);
        break;
    case REQUEST:
        printRequest(group);
        break;
    case BDTOBIN:
        TxtToBin(group);
        break;
    case EXIT:
        system("cls");
        exit(0);
        break;
    default:
        MessageBox(nullptr, TEXT("Ошибка! Введено неверное значение пункта меню.\nПожалуйста, введите верное значение пункта меню."), TEXT("Ошибка"), MB_OK);
        main_menu(group);
        break;
    }
}

void addData(student group[AR_SIZE]) {
    enum Num_of_commands {
        INPUTKLAV = 1,
        INPUTTEXT,
        BINTOBASE,
        MAINMENU
    };
    int index_appData = 0;
    system("cls");
    cout << "\n";
    cout << "|=============================================|\n";
    cout << "|-----------База данных студентов-------------|\n";
    cout << "|=============================================|\n";
    cout << "|----------Раздел добавления данных-----------|\n";
    cout << "|---------------------------------------------|\n";
    cout << "|-----|---------------------------------------|\n";
    cout << "|  1  |Ввод с клавиатуры;                     |\n";
    cout << "|-----|---------------------------------------|\n";
    cout << "|  2  |Ввод из текстового файла;              |\n";
    cout << "|-----|---------------------------------------|\n";
    cout << "|  3  |Ввод из бинарного файла;               |\n";
    cout << "|-----|---------------------------------------|\n";
    cout << "|  4  |Выход в главное меню;                  |\n";
    cout << "|-----|---------------------------------------|\n\n";
    outputDataTable(group);
    cout << "\n Введите нужный пункт меню: ";
    cin >> index_appData;
    switch (index_appData) {
    case INPUTKLAV:
        inputKlav(group);
        break;
    case INPUTTEXT:
        inputFromFile(group);
        break;
    case BINTOBASE:
        BinToBase(group);
        break;
    case MAINMENU:
        main_menu(group);
        break;
    default:
        MessageBox(nullptr, TEXT("Ошибка! Введено неверное значение пункта меню.\nВы перенесены в главное меню."), TEXT("Warning"), MB_OK);
        main_menu(group);
        break;
    }
}

void inputKlav(student group[AR_SIZE]) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int Free{};
    int kurs, m, a, i, v = 0;
    bool check = 1;
    char fam[FAMILY_SIZE], name[NAME_SIZE], ot[OTCH_SIZE];
    for (int i = 0; i < AR_SIZE; i++) {
        if (group[i].kurs == 0) {
            Free = i;
            break;
        }
    }
    cin.ignore(100, '\n');
    system("cls");
    cout << "\n";
    cout << "|=============================================|\n";
    cout << "|-----------База данных студентов-------------|\n";
    cout << "|=============================================|\n";
    cout << "|----------Раздел добавления данных-----------|\n";
    cout << "|---------------------------------------------|\n\n";
    cout << "Введите Фамилию студента: ";
    cin.getline(fam, FAMILY_SIZE);
    cout << "Введите имя студента: ";
    cin.getline(name, NAME_SIZE);
    cout << "Введите отчество студента: ";
    cin.getline(ot, OTCH_SIZE);
    cout << "Введите курс студента: ";
    if (!(cin >> kurs) || (cin.peek() != '\n')) {
        cin.clear();
        while (cin.get() != '\n');
        MessageBox(nullptr, TEXT("Ошибка! Введено неверное значение пункта меню.\nПожалуйста, введите верное значение пункта меню."), TEXT("Ошибка"), MB_OK);
        main_menu(group);
    }
    cout << "Введите оценку за Математический анализ: ";
    if (!(cin >> m) || (cin.peek() != '\n')) {
        cin.clear();
        while (cin.get() != '\n');
        MessageBox(nullptr, TEXT("Ошибка! Введено неверное значение пункта меню.\nПожалуйста, введите верное значение пункта меню."), TEXT("Ошибка"), MB_OK);
        main_menu(group);
    }
    cout << "Введите оценку за Аналитическую геометрию: ";
    if (!(cin >> a) || (cin.peek() != '\n')) {
        cin.clear();
        while (cin.get() != '\n');
        MessageBox(nullptr, TEXT("Ошибка! Введено неверное значение пункта меню.\nПожалуйста, введите верное значение пункта меню."), TEXT("Ошибка"), MB_OK);
        main_menu(group);
    }
    cout << "Введите оценку за Инженерную графику: ";
    if (!(cin >> i) || (cin.peek() != '\n')) {
        cin.clear();
        while (cin.get() != '\n');
        MessageBox(nullptr, TEXT("Ошибка! Введено неверное значение пункта меню.\nПожалуйста, введите верное значение пункта меню."), TEXT("Ошибка"), MB_OK);
        main_menu(group);
    }
    cout << "Введите оценку за Высокоуровневое программирование: ";
    if (!(cin >> v) || (cin.peek() != '\n')) {
        cin.clear();
        while (cin.get() != '\n');
        MessageBox(nullptr, TEXT("Ошибка! Введено неверное значение пункта меню.\nПожалуйста, введите верное значение пункта меню."), TEXT("Ошибка"), MB_OK);
        main_menu(group);
    }
    if (kurs < 1 || kurs>6 || v < 1 || v>5 || i < 1 || i>5 || a < 1 || a>5 || m < 1 || m>5 || check_digit(fam) == 0 || check_digit(name) == 0 || check_digit(ot) == 0) check = 0;
    if (check) {
        strcpy_s(group[Free].family, FAMILY_SIZE, fam);
        strcpy_s(group[Free].name, NAME_SIZE, name);
        strcpy_s(group[Free].otch, FAMILY_SIZE, ot);
        group[Free].kurs = kurs;
        group[Free].grade.mat = m;
        group[Free].grade.angeom = a;
        group[Free].grade.inzhgraph = i;
        group[Free].grade.vp = v;
        MessageBox(nullptr, TEXT("Запись успешно добавлена!"), TEXT("Успех"), MB_OK);
        main_menu(group);
    }
    else {
        MessageBox(nullptr, TEXT("Один из параметров указан неверно!\nЗапись не добавлена. Пожалуйста, вводите верные данные."), TEXT("Ошибка"), MB_OK);
        main_menu(group);
    }
}

void outputData(student group[AR_SIZE]) {
    enum Num_of_commands {
        OUTTABLE = 1,
        OUTFILE,
        MAINMENU
    };
    int index_outputData = 0;
    system("cls");
    cout << "\n";
    cout << "|=============================================|\n";
    cout << "|-----------База данных студентов-------------|\n";
    cout << "|=============================================|\n";
    cout << "|----------Раздел вывода информации-----------|\n";
    cout << "|---------------------------------------------|\n";
    cout << "|-----|---------------------------------------|\n";
    cout << "|  1  |Вывод в виде таблицы;                  |\n";
    cout << "|-----|---------------------------------------|\n";
    cout << "|  2  |Вывод данных в файл;                   |\n";
    cout << "|-----|---------------------------------------|\n";
    cout << "|  3  |Выход в главное меню;                  |\n";
    cout << "|-----|---------------------------------------|\n\n";
    cout << "Введите нужный пункт меню: ";
    if (!(cin >> index_outputData) || (cin.peek() != '\n')) {
        cin.clear();
        while (cin.get() != '\n');
        MessageBox(nullptr, TEXT("Ошибка! Введено неверное значение пункта меню.\nПожалуйста, введите верное значение пункта меню."), TEXT("Ошибка"), MB_OK);
        outputData(group);
    }
    switch (index_outputData) {
    case OUTTABLE:
        cout << endl;
        outputDataTable(group);
        cout << endl;
        system("pause");
        cin.get();
        main_menu(group);
        break;
    case OUTFILE:
        outputToFile(group);
        break;
    case MAINMENU:
        main_menu(group);
        break;
    default:
        MessageBox(nullptr, TEXT("Ошибка! Введено неверное значение пункта меню.\nВы перенесены в главное меню."), TEXT("Warning"), MB_OK);
        main_menu(group);
        break;
    }
}

void outputDataTable(student group[AR_SIZE]) {
    int Free{};
    for (int i = 0; i < AR_SIZE; i++) {
        if (group[i].kurs == 0) {
            Free = i;
            break;
        }
    }
    cout << "|----------------------------------------Данные в базе в данный момент---------------------------------------|\n|============================================================================================================|\n";
    cout << "№ |" << setw(15) << "Фамилия |" << setw(15) << "Имя |" << setw(18) << "Отчество |" << setw(11) << "Курс |" << setw(12) << "Мат.Анализ |" << setw(12) << "Ан.Геом. |" << setw(12) << "Инж.Граф. |" << setw(12) << "Выс.Прог. |" << endl;
    cout << "--|--------------|--------------|-----------------|----------|-----------|-----------|-----------|-----------|\n";
    for (int i = 0; i < Free; i++) {
        cout << i + 1 << " |" << setw(13) << group[i].family << " |" << setw(13) << group[i].name << " |" << setw(16) << group[i].otch << " |" << setw(9) << group[i].kurs << " |" << setw(10) << group[i].grade.mat << " |" << setw(10) << group[i].grade.angeom << " |" << setw(10) << group[i].grade.inzhgraph << " |" << setw(10) << group[i].grade.vp << " |" << endl;
        cout << "--|--------------|--------------|-----------------|----------|-----------|-----------|-----------|-----------|\n";
    }
    cout << "|============================================================================================================|\n";
}

void printRequest(student group[AR_SIZE]) {
    int count{};
    int sum{}, c{};
    double sr{};
    int num{};
    system("cls");
    cout << "|=============================================|\n";
    cout << "|-----------База данных студентов-------------|\n";
    cout << "|=============================================|\n";
    cout << "|---------------Раздел запроса----------------|\n";
    cout << "|---------------------------------------------|\n\n";
    cout << "Введите номер курса для расчета среднего балла: ";
    if (!(cin >> num) || (cin.peek() != '\n')) {
        cin.clear();
        while (cin.get() != '\n');
        MessageBox(nullptr, TEXT("Ошибка! Введено неверное значение курса.\nВы возвращены в главное меню."), TEXT("Ошибка"), MB_OK);
        main_menu(group);
    }
    cout << "\n";
    for (int i = 0; i < AR_SIZE; i++) {
        if ((group[i].grade.mat != 0) && (group[i].kurs == num)) {
            count++;
        }
    }
    if (count > 0) {
        for (int i = 0; i < AR_SIZE; i++) {
            if ((group[i].grade.mat != 0) && (group[i].kurs == num)) {
                sum += group[i].grade.mat + group[i].grade.angeom + group[i].grade.inzhgraph + group[i].grade.vp;
                c += 4;
            }
        }
        sr = double(sum) / double(c);
        cout << "Средний балл " << num << " курса = " << sr << endl << endl;
    }
    else {
        cout << "Недостаточно данных для вычислений." << endl << endl;
    }
    system("pause");
    cin.get();
    main_menu(group);
}


void Edit(student group[AR_SIZE]) {
    enum Num_of_Commands {
        FAMILY = 1,
        NAME,
        OTCH,
        KURS,
        MAT,
        ANALGEOM,
        INZHGRAPH,
        VP
    };
    system("cls");
    int edit_num = 0;
    int edit_num_tek = 0;
    cout << "\n";
    cout << "|=============================================|\n";
    cout << "|-----------База данных студентов-------------|\n";
    cout << "|=============================================|\n";
    cout << "|--------------Изменение записи---------------|\n";
    cout << "|---------------------------------------------|\n\n";
    outputDataTable(group);
    cout << "\n\nВведите номер студента для изменения записи: ";
    if (!(cin >> edit_num) || (cin.peek() != '\n')) {
        cin.clear();
        while (cin.get() != '\n');
        MessageBox(nullptr, TEXT("Ошибка! Введено неверное значение пункта меню.\nПожалуйста, введите верное значение пункта меню."), TEXT("Ошибка"), MB_OK);
        main_menu(group);
    }
    if ((edit_num > 0) && (group[edit_num - 1].kurs != 0) && (edit_num <= AR_SIZE)) {
        system("cls");
        cout << " Выбран студент №" << edit_num << endl;
        cout << " 1) Фамилия: " << group[edit_num - 1].family << endl;
        cout << " 2) Имя: " << group[edit_num - 1].name << endl;
        cout << " 3) Отчество: " << group[edit_num - 1].otch << endl;
        cout << " 4) Курс: " << group[edit_num - 1].kurs << endl;
        cout << " 5) Мат. Анализ: " << group[edit_num - 1].grade.mat << endl;
        cout << " 6) Аналит. Геометрия: " << group[edit_num - 1].grade.angeom << endl;
        cout << " 7) Инж. графика: " << group[edit_num - 1].grade.inzhgraph << endl;
        cout << " 8) Высокоур. Программирование: " << group[edit_num - 1].grade.vp << endl << endl;
        cout << " Введите номер для изменения нужного параметра: ";
        cin >> edit_num_tek;
        cout << "\n\n";
        char edit_temp[FAMILY_SIZE];
        switch (edit_num_tek) {
        case FAMILY:
            cout << " Выбран параметр для изменения - Фамилия\n Текущая фамилия: ";
            cout << group[edit_num - 1].family << endl;
            cout << " Введите новую фамилию: ";
            cin >> edit_temp;
            if (check_digit(edit_temp) == 1) {
                strcpy_s(group[edit_num - 1].family, FAMILY_SIZE, edit_temp);
                MessageBox(nullptr, TEXT("Фамилия успешно изменена. Вы возвращены в главное меню."), TEXT("Успех"), MB_OK);
                main_menu(group);
            }
            else {
                MessageBox(nullptr, TEXT("Ошибка! Введено неверное значение параметра.\nПожалуйста, указывайте верные параметры."), TEXT("Ошибка"), MB_OK);
                main_menu(group);
            }
            break;
        case NAME:
            cout << " Выбран параметр для изменения - Имя\n Текущее имя: ";
            cout << group[edit_num - 1].name << endl;
            cout << " Введите новое имя: ";
            cin >> edit_temp;
            if (check_digit(edit_temp) == 1) {
                strcpy_s(group[edit_num - 1].name, NAME_SIZE, edit_temp);
                MessageBox(nullptr, TEXT("Имя успешно изменено. Вы возвращены в главное меню."), TEXT("Успех"), MB_OK);
                main_menu(group);
            }
            else {
                MessageBox(nullptr, TEXT("Ошибка! Введено неверное значение параметра.\nПожалуйста, указывайте верные параметры."), TEXT("Ошибка"), MB_OK);
                main_menu(group);
            }
            break;
        case OTCH:
            cout << " Выбран параметр для изменения - Отчество\n Текущее отчество: ";
            cout << group[edit_num - 1].otch << endl;
            cout << " Введите новое отчество: ";
            cin >> edit_temp;
            if (check_digit(edit_temp) == 1) {
                strcpy_s(group[edit_num - 1].otch, OTCH_SIZE, edit_temp);
                MessageBox(nullptr, TEXT("Отчество успешно изменено. Вы возвращены в главное меню."), TEXT("Успех"), MB_OK);
                main_menu(group);
            }
            else {
                MessageBox(nullptr, TEXT("Ошибка! Введено неверное значение параметра.\nПожалуйста, указывайте верные параметры."), TEXT("Ошибка"), MB_OK);
                main_menu(group);
            }
            break;
        case KURS:
            cout << " Выбран параметр для изменения - Курс\n Текущий курс: ";
            cout << group[edit_num - 1].kurs << endl;
            cout << " Введите новый курс: ";
            cin >> group[edit_num - 1].kurs;
            MessageBox(nullptr, TEXT("Курс успешно изменен. Вы возвращены в главное меню."), TEXT("Успех"), MB_OK);
            main_menu(group);
            break;
        case MAT:
            cout << " Выбран параметр для изменения - Отметка по математическому анализу\n Текущая отметка: ";
            cout << group[edit_num - 1].grade.mat << endl;
            cout << " Введите новую отметку: ";
            cin >> group[edit_num - 1].grade.mat;
            MessageBox(nullptr, TEXT("Отметка успешно изменена. Вы возвращены в главное меню."), TEXT("Успех"), MB_OK);
            main_menu(group);
            break;
        case ANALGEOM:
            cout << " Выбран параметр для изменения - Отметка по аналитической геометрии\n Текущая отметка: ";
            cout << group[edit_num - 1].grade.angeom << endl;
            cout << " Введите новую отметку: ";
            cin >> group[edit_num - 1].grade.angeom;
            MessageBox(nullptr, TEXT("Отметка успешно изменена. Вы возвращены в главное меню."), TEXT("Успех"), MB_OK);
            main_menu(group);
            break;
        case INZHGRAPH:
            cout << " Выбран параметр для изменения - Отметка по инженерной графике\n Текущая отметка: ";
            cout << group[edit_num - 1].grade.inzhgraph << endl;
            cout << " Введите новую отметку: ";
            cin >> group[edit_num - 1].grade.inzhgraph;
            MessageBox(nullptr, TEXT("Отметка успешно изменена. Вы возвращены в главное меню."), TEXT("Успех"), MB_OK);
            main_menu(group);
            break;
        case VP:
            cout << " Выбран параметр для изменения - Отметка по высокоуровневому программированию\n Текущая отметка: ";
            cout << group[edit_num - 1].grade.vp << endl;
            cout << " Введите новую отметку: ";
            cin >> group[edit_num - 1].grade.vp;
            MessageBox(nullptr, TEXT("Отметка успешно изменена. Вы возвращены в главное меню."), TEXT("Успех"), MB_OK);
            main_menu(group);
            break;
        default:
            MessageBox(nullptr, TEXT("Введен неверный номер пункта меню. Вы возвращены в главное меню."), TEXT("Ошибка"), MB_OK);
            main_menu(group);
        }
    }
    else {
        MessageBox(nullptr, TEXT("Введен неверный номер студента. Вы возвращены в главное меню."), TEXT("Ошибка"), MB_OK);
        main_menu(group);
    }
}


void DeleteData(student group[AR_SIZE]) {
    int delete_num = 0;
    int delete_num_tek = 0;
    int free = 0;
    system("cls");
    cout << "\n";
    cout << "|=============================================|\n";
    cout << "|-----------База данных студентов-------------|\n";
    cout << "|=============================================|\n";
    cout << "|--------------Удаление записи----------------|\n";
    cout << "|---------------------------------------------|\n\n";
    outputDataTable(group);
    cout << "\n\n";
    cout << "Введите номер студента для удаления из БД: ";
    if (!(cin >> delete_num) || (cin.peek() != '\n')) {
        cin.clear();
        while (cin.get() != '\n');
        MessageBox(nullptr, TEXT("Ошибка! Введено неверное значение номера студента.\nПожалуйста, введите верное значение номера студента."), TEXT("Ошибка"), MB_OK);
        main_menu(group);
    }
    if (delete_num > 0 && group[delete_num - 1].kurs != 0 && delete_num <= AR_SIZE) {
        system("cls");
        cout << " Выбран студент для удаления №" << delete_num << " " << group[delete_num - 1].family << " " << group[delete_num - 1].name << endl;
        cout << " 1) Удалить\n 2) Отменить удаление\n\n Вы уверены, что хотите удалить данную запись? ";
        if (!(cin >> delete_num_tek) || (cin.peek() != '\n')) {
            cin.clear();
            while (cin.get() != '\n');
            MessageBox(nullptr, TEXT("Ошибка! Введено неверное значение пункта удаления.\nВы возвращены назад."), TEXT("Ошибка"), MB_OK);
            DeleteData(group);
        }
        if (delete_num_tek == 1) {
            int count = 0;
            for (int i = 0; i < AR_SIZE; i++) {
                if (group[i].kurs != 0) count++;
            }
            strcpy_s(group[delete_num - 1].family, FAMILY_SIZE, "No Fam");
            strcpy_s(group[delete_num - 1].name, NAME_SIZE, "No Name");
            strcpy_s(group[delete_num - 1].otch, OTCH_SIZE, "No Otch");
            group[delete_num - 1].kurs = 0;
            group[delete_num - 1].grade.mat = 0;
            group[delete_num - 1].grade.angeom = 0;
            group[delete_num - 1].grade.inzhgraph = 0;
            group[delete_num - 1].grade.vp = 0;
            free = delete_num - 1;
            if (delete_num != count) {
                for (int i = free; i != count - 1; i++) {
                    group[i] = group[i + 1];
                }
                strcpy_s(group[count - 1].family, FAMILY_SIZE, "No Fam");
                strcpy_s(group[count - 1].name, NAME_SIZE, "No Name");
                strcpy_s(group[count - 1].otch, OTCH_SIZE, "No Otch");
                group[count - 1].kurs = 0;
                group[count - 1].grade.mat = 0;
                group[count - 1].grade.angeom = 0;
                group[count - 1].grade.inzhgraph = 0;
                group[count - 1].grade.vp = 0;
            }
            MessageBox(nullptr, TEXT("Удаление завершено! Вы возвращены в главное меню."), TEXT("Удаление"), MB_OK);
            main_menu(group);
        }
        else if (delete_num_tek == 2) {
            MessageBox(nullptr, TEXT("Удаление отменено. Вы возвращены в главное меню."), TEXT("Удаление"), MB_OK);
            main_menu(group);
        }
        else {
            MessageBox(nullptr, TEXT("Введен неверный номер. Вы возвращены в главное меню."), TEXT("Ошибка"), MB_OK);
            main_menu(group);
        }

    }
    else {
        MessageBox(nullptr, TEXT("Введен неверный номер студента. Вы возвращены в главное меню."), TEXT("Ошибка"), MB_OK);
        main_menu(group);
    }
}

void Sort(student group[AR_SIZE]) {
    student* temp = new student[50];
    student* tmps = new student[1];
    enum Num_of_Commands {
        FAMILY_SORT = 1,
        NAME_SORT,
        OTCH_SORT,
        KURS_SORT,
        MAT_SORT,
        ANALGEOM_SORT,
        INZHGRAPH_SORT,
        VP_SORT
    };
    system("cls");
    int sort_index = 0;
    int tmp = 0;
    int Free{};
    for (int i = 0; i < AR_SIZE; i++) {
        if (group[i].kurs == 0) {
            Free = i;
            break;
        }
    }
    cout << "\n";
    cout << "|=============================================|\n";
    cout << "|-----------База данных студентов-------------|\n";
    cout << "|=============================================|\n";
    cout << "|-----------------Сортировка------------------|\n";
    cout << "|---------------------------------------------|\n\n";
    outputDataTable(group);
    cout << "\n\n";
    cout << "1) Сортировка по фамилии.\n";
    cout << "2) Сортировка по имени.\n";
    cout << "3) Сортировка по отчеству.\n";
    cout << "4) Сортировка по курсу.\n";
    cout << "5) Сортировка по отметке Мат.Анализа.\n";
    cout << "6) Сортировка по отметке Аналит. Геометрии.\n";
    cout << "7) Сортировка по отметке Инж. Графики.\n";
    cout << "8) Сортировка по отметке Высок. Прогр.\n\n";
    cout << "Введите номер нужного поля для сортировки: ";
    if (!(cin >> sort_index) || (cin.peek() != '\n')) {
        cin.clear();
        while (cin.get() != '\n');
        MessageBox(nullptr, TEXT("Ошибка! Введено неверное значение пункта удаления.\nВы возвращены назад."), TEXT("Ошибка"), MB_OK);
        DeleteData(group);
    }
    switch (sort_index) {
    case FAMILY_SORT:
        temp = group;
        for (int i = 0; i < Free; i++) {
            for (int j = (Free - 1); j >= (i + 1); j--) {
                if (temp[j].family[0] < temp[j - 1].family[0]) {
                    tmps[0] = temp[j];
                    temp[j] = temp[j - 1];
                    temp[j - 1] = tmps[0];
                }
            }
        }
        outputSort(temp);
        system("pause");
        cin.get();
        main_menu(group);
        break;
    case NAME_SORT:
        temp = group;
        for (int i = 0; i < Free; i++) {
            for (int j = (Free - 1); j >= (i + 1); j--) {
                if (temp[j].name[0] < temp[j - 1].name[0]) {
                    tmps[0] = temp[j];
                    temp[j] = temp[j - 1];
                    temp[j - 1] = tmps[0];
                }
            }
        }
        system("cls");
        outputSort(temp);
        system("pause");
        cin.get();
        main_menu(group);
        break;
    case OTCH_SORT:
        temp = group;
        for (int i = 0; i < Free; i++) {
            for (int j = (Free - 1); j >= (i + 1); j--) {
                if (temp[j].otch[0] < temp[j - 1].otch[0]) {
                    tmps[0] = temp[j];
                    temp[j] = temp[j - 1];
                    temp[j - 1] = tmps[0];
                }
            }
        }
        system("cls");
        outputSort(temp);
        system("pause");
        cin.get();
        main_menu(group);
        break;
    case KURS_SORT:
        temp = group;
        for (int i = 0; i < Free; i++) {
            for (int j = (Free - 1); j >= (i + 1); j--) {
                if (temp[j].kurs < temp[j - 1].kurs) {
                    tmps[0] = temp[j];
                    temp[j] = temp[j - 1];
                    temp[j - 1] = tmps[0];
                }
            }
        }
        system("cls");
        outputSort(temp);
        system("pause");
        cin.get();
        main_menu(group);
        break;
    case MAT_SORT:
        temp = group;
        for (int i = 0; i < Free; i++) {
            for (int j = (Free - 1); j >= (i + 1); j--) {
                if (temp[j].grade.mat < temp[j - 1].grade.mat) {
                    tmps[0] = temp[j];
                    temp[j] = temp[j - 1];
                    temp[j - 1] = tmps[0];
                }
            }
        }
        system("cls");
        outputSort(temp);
        system("pause");
        cin.get();
        main_menu(group);
        break;
    case ANALGEOM_SORT:
        temp = group;
        for (int i = 0; i < Free; i++) {
            for (int j = (Free - 1); j >= (i + 1); j--) {
                if (temp[j].grade.angeom < temp[j - 1].grade.angeom) {
                    tmps[0] = temp[j];
                    temp[j] = temp[j - 1];
                    temp[j - 1] = tmps[0];
                }
            }
        }
        system("cls");
        outputSort(temp);
        system("pause");
        cin.get();
        main_menu(group);
        break;
    case INZHGRAPH_SORT:
        temp = group;
        for (int i = 0; i < Free; i++) {
            for (int j = (Free - 1); j >= (i + 1); j--) {
                if (temp[j].grade.inzhgraph < temp[j - 1].grade.inzhgraph) {
                    tmps[0] = temp[j];
                    temp[j] = temp[j - 1];
                    temp[j - 1] = tmps[0];
                }
            }
        }
        system("cls");
        outputSort(temp);
        system("pause");
        cin.get();
        main_menu(group);
        break;
    case VP_SORT:
        temp = group;
        for (int i = 0; i < Free; i++) {
            for (int j = (Free - 1); j >= (i + 1); j--) {
                if (temp[j].grade.vp < temp[j - 1].grade.vp) {
                    tmps[0] = temp[j];
                    temp[j] = temp[j - 1];
                    temp[j - 1] = tmps[0];
                }
            }
        }
        system("cls");
        outputSort(temp);
        system("pause");
        cin.get();
        main_menu(group);
        break;
    default:
        MessageBox(nullptr, TEXT("Введен неверный номер. Вы возвращены в главное меню."), TEXT("Ошибка"), MB_OK);
        main_menu(group);
        break;
    }
}

void outputSort(student temp[AR_SIZE]) {
    system("cls");
    cout << "Сортировка по выбранному параметру успешно выполнена!\n\n";
    outputDataTable(temp);
    cout << "\n\n";
}

void outputToFile(student group[AR_SIZE]) {
    system("cls");
    int Free{};
    for (int i = 0; i < AR_SIZE; i++) {
        if (group[i].kurs == 0) {
            Free = i;
            break;
        }
    }
    cout << "\n";
    cout << "|=============================================|\n";
    cout << "|-----------База данных студентов-------------|\n";
    cout << "|=============================================|\n";
    cout << "|------------Вывод данных в файл--------------|\n";
    cout << "|---------------------------------------------|\n\n";
    if (Free != 0) {
        ofstream fout;
        fout.open("BASE_STUDENT.txt");
        for (int i = 0; i < Free; i++) {
            fout << group[i].family << endl;
            fout << group[i].name << endl;
            fout << group[i].otch << endl;
            fout << group[i].kurs << endl;
            fout << group[i].grade.mat << endl;
            fout << group[i].grade.angeom << endl;
            fout << group[i].grade.inzhgraph << endl;
            fout << group[i].grade.vp << endl;
        }
        fout.close();
        MessageBox(nullptr, TEXT("Запись в файл успешно выполнена!\nВы возвращены в главное меню."), TEXT("Успех"), MB_OK);
        main_menu(group);
    }
    else {
        MessageBox(nullptr, TEXT("Ошибка! База данных пуста. Запись невозможна.\nВы возвращены в главное меню."), TEXT("Ошибка"), MB_OK);
        main_menu(group);
    }
}

void inputFromFile(student group[AR_SIZE]) {
    system("cls");
    int Free{};
    for (int i = 0; i < AR_SIZE; i++) {
        if (group[i].kurs == 0) {
            Free = i;
            break;
        }
    }
    cout << "\n";
    cout << "|=============================================|\n";
    cout << "|-----------База данных студентов-------------|\n";
    cout << "|=============================================|\n";
    cout << "|------------Ввод данных из файла-------------|\n";
    cout << "|---------------------------------------------|\n\n";
    ifstream inf("BASE_STUDENT.txt");
    int c = Free;
    if (!inf.is_open()) {
        MessageBox(nullptr, TEXT("Ошибка! Не удалось открыть файл. Запись невозможна.\nВы возвращены в главное меню."), TEXT("Ошибка"), MB_OK);
        main_menu(group);
    }
    else {
        while (inf) {
            inf >> group[c].family;
            inf >> group[c].name;
            inf >> group[c].otch;
            inf >> group[c].kurs;
            inf >> group[c].grade.mat;
            inf >> group[c].grade.angeom;
            inf >> group[c].grade.inzhgraph;
            inf >> group[c].grade.vp;
            c++;
        }
        inf.close();
        outputDataTable(group);
        MessageBox(nullptr, TEXT("Запись из файла успешно выполнена!"), TEXT("Успех"), MB_OK);
        system("pause");
        cin.get();
        main_menu(group);
    }
}

void TxtToBin(student group[AR_SIZE]) {
    system("cls");
    cout << "\n";
    cout << "|=============================================|\n";
    cout << "|-----------База данных студентов-------------|\n";
    cout << "|=============================================|\n";
    cout << "|-----Перевод текстового файла в бинарный-----|\n";
    cout << "|---------------------------------------------|\n\n";
    int n = AR_SIZE;
    ifstream in("BASE_STUDENT.txt");
    ofstream out("BASE_BIN.bin", ios::binary);
    student tm;
    if (in.is_open()) {
        for (int i = 0; i < n; i++) {
            in >> tm.family;
            in >> tm.name;
            in >> tm.otch;
            in >> tm.kurs;
            in >> tm.grade.mat;
            in >> tm.grade.angeom;
            in >> tm.grade.inzhgraph;
            in >> tm.grade.vp;
            out.write((char*)&tm, sizeof(student));
        }
        out.close();
        in.close();
        MessageBox(nullptr, TEXT("Запись завершена!\nВы возвращены в главное меню."), TEXT("Успех"), MB_OK);
        main_menu(group);
    }
    else {
        MessageBox(nullptr, TEXT("Ошибка! Не удалось открыть файл. Запись невозможна.\nВы возвращены в главное меню."), TEXT("Ошибка"), MB_OK);
        main_menu(group);
    }
}

void BinToBase(student group[AR_SIZE]) {
    system("cls");
    cout << "\n";
    cout << "|=============================================|\n";
    cout << "|-----------База данных студентов-------------|\n";
    cout << "|=============================================|\n";
    cout << "|--------Загрузка БД из бинарного файла-------|\n";
    cout << "|---------------------------------------------|\n\n";
    int n = AR_SIZE;
    bool check = 0;
    int stop = 0;
    ifstream in("BASE_BIN.bin", ios::binary || ios::in);
    if (in.is_open()) {

        for (int i = 0; i < n; i++) {
            student tm;
            in.read((char*)&tm, sizeof(tm));
            if (tm.family[0] == '\0') break;
            strcpy_s(group[i].family, FAMILY_SIZE, tm.family);
            strcpy_s(group[i].name, FAMILY_SIZE, tm.name);
            strcpy_s(group[i].otch, FAMILY_SIZE, tm.otch);
            group[i].kurs = tm.kurs;
            group[i].grade.mat = tm.grade.mat;
            group[i].grade.angeom = tm.grade.angeom;
            group[i].grade.inzhgraph = tm.grade.inzhgraph;
            group[i].grade.vp = tm.grade.vp;
        }
        in.close();
        outputDataTable(group);
        MessageBox(nullptr, TEXT("Загрузка БД из бинарного файла выполнена!\nВы возвращены в главное меню."), TEXT("Успех"), MB_OK);
        main_menu(group);
    }
    else {
        MessageBox(nullptr, TEXT("Ошибка! Не удалось открыть файл. Запись невозможна.\nВы возвращены в главное меню."), TEXT("Ошибка"), MB_OK);
        main_menu(group);
    }
}

int check_digit(char* str) {
    for (size_t i = 0; i < strlen(str); i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            return 0;
            break;
        }
    }
    return 1;
}