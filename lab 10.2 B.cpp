#include <iostream>
#include <string>
#include <Windows.h>
#include <iomanip>
using namespace std;

enum Spec { CS, IT, ME, PhIT, TR };  // Перелічувальний тип для спеціальностей студентів

// Масив рядків для відображення назв спеціальностей
string strSpec[] = { "Комп'ютернi науки", "Iнформатика", "Математика та економiка", "Фiзика та iнформатика", "Трудове навчання" };

// Структура для зберігання інформації про студента
struct Student {
    int number;     // Порядковий номер студента у групі
    string lname;   // Прізвище
    int kurs;       // Курс
    Spec spec;      // Спеціальність
    int physics;    // Оцінка з фізики
    int math;       // Оцінка з математики
    union {         // Об'єднання для третьої оцінки в залежності від спеціальності
        int programming;    // Оцінка з програмування (для CS)
        int numMethods;     // Оцінка з чисельних методів (для IT)
        int pedagogy;       // Оцінка з педагогіки (для решти спеціальностей)
    };
};

// Функція для введення даних про студентів
void Create(Student* s, int amSt) {
    int sp;
    for (int i = 0; i < amSt; i++) {
        s[i].number = i + 1;  // Встановлюємо порядковий номер студента

        cout << "Студент № " << s[i].number << ":" << endl;
        cout << "Прiзвище: ";
        cin >> s[i].lname;
        cout << "Курс: ";
        cin >> s[i].kurs;
        cout << "Спецiальнiсть (0 - Комп'ютернi науки, 1 - Iнформатика, 2 - Математика та економiка, "
            << "3 - Фiзика та iнформатика, 4 - Трудове навчання): ";
        cin >> sp;
        s[i].spec = (Spec)sp;
        cout << "Оцiнка з фiзики: ";
        cin >> s[i].physics;
        cout << "Оцiнка з математики: ";
        cin >> s[i].math;

        // Введення третьої оцінки залежно від спеціальності
        if (s[i].spec == CS) {
            cout << "Оцiнка з програмування: ";
            cin >> s[i].programming;
        }
        else if (s[i].spec == IT) {
            cout << "Оцiнка з чисельних методів: ";
            cin >> s[i].numMethods;
        }
        else {
            cout << "Оцiнка з педагогіки: ";
            cin >> s[i].pedagogy;
        }
        cout << endl;
    }
}

// Функція для виведення даних про студентів у табличному форматі
void Print(Student* s, int amSt) {
    cout << "--------------------------------------------------------------------------------------------------------\n";
    cout << "| № | Прiзвище      | Курс | Спецiальнiсть           | Фiзика | Матем. | Прог. | Чис.мет. | Педагог. |\n";
    cout << "--------------------------------------------------------------------------------------------------------\n";

    for (int i = 0; i < amSt; i++) {
        cout << "| " << setw(2) << right << s[i].number
            << " | " << setw(13) << left << s[i].lname
            << " | " << setw(4) << right << s[i].kurs
            << " | " << setw(22) << left << strSpec[s[i].spec]
            << " | " << setw(6) << right << s[i].physics
            << " | " << setw(6) << right << s[i].math
            << " | ";

        // Виведення третьої оцінки в відповідну колонку
        if (s[i].spec == CS)
            cout << setw(5) << right << s[i].programming << " | " << setw(8) << " " << " | " << setw(8) << " ";
        else if (s[i].spec == IT)
            cout << setw(5) << " " << " | " << setw(8) << right << s[i].numMethods << " | " << setw(8) << " ";
        else
            cout << setw(5) << " " << " | " << setw(8) << " " << " | " << setw(8) << right << s[i].pedagogy;

        cout << " |" << endl;
    }
    cout << "--------------------------------------------------------------------------------------------------------\n";
}

// Функція для фізичного сортування масиву студентів за спеціальністю, оцінкою з математики та прізвищем
void Sort(Student* p, const int N) {
    Student tmp;
    for (int i0 = 0; i0 < N - 1; i0++)
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
            if ((p[i1].spec > p[i1 + 1].spec) ||
                (p[i1].spec == p[i1 + 1].spec && p[i1].math > p[i1 + 1].math) ||
                (p[i1].spec == p[i1 + 1].spec && p[i1].math == p[i1 + 1].math &&
                    p[i1].lname > p[i1 + 1].lname)) {
                tmp = p[i1];
                p[i1] = p[i1 + 1];
                p[i1 + 1] = tmp;
            }
}

// Функція для індексного сортування масиву студентів
int* indexSort(Student* s, const int N) {
    int* P = new int[N];  // Масив індексів
    for (int i = 0; i < N; i++)
        P[i] = i;

    for (int i0 = 0; i0 < N - 1; i0++)
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
            if ((s[P[i1]].spec > s[P[i1 + 1]].spec) ||
                (s[P[i1]].spec == s[P[i1 + 1]].spec && s[P[i1]].math > s[P[i1 + 1]].math) ||
                (s[P[i1]].spec == s[P[i1 + 1]].spec && s[P[i1]].math == s[P[i1 + 1]].math &&
                    s[P[i1]].lname > s[P[i1 + 1]].lname)) {
                int tmp = P[i1];
                P[i1] = P[i1 + 1];
                P[i1 + 1] = tmp;
            }
    return P;
}

// Функція для виведення індексно відсортованого масиву студентів
void PrintIndexSorted(Student* s, int* P, const int N) {
    cout << "--------------------------------------------------------------------------------------------------------\n";
    cout << "| № | Прiзвище      | Курс | Спецiальнiсть           | Фiзика | Матем. | Прог. | Чис.мет. | Педагог. |\n";
    cout << "--------------------------------------------------------------------------------------------------------\n";

    for (int i = 0; i < N; i++) {
        cout << "| " << setw(2) << right << s[P[i]].number
            << " | " << setw(13) << left << s[P[i]].lname
            << " | " << setw(4) << right << s[P[i]].kurs
            << " | " << setw(22) << left << strSpec[s[P[i]].spec]
            << " | " << setw(6) << right << s[P[i]].physics
            << " | " << setw(6) << right << s[P[i]].math
            << " | ";

        if (s[P[i]].spec == CS)
            cout << setw(5) << right << s[P[i]].programming << " | " << setw(8) << " " << " | " << setw(8) << " ";
        else if (s[P[i]].spec == IT)
            cout << setw(5) << " " << " | " << setw(8) << right << s[P[i]].numMethods << " | " << setw(8) << " ";
        else
            cout << setw(5) << " " << " | " << setw(8) << " " << " | " << setw(8) << right << s[P[i]].pedagogy;

        cout << " |" << endl;
    }
    cout << "--------------------------------------------------------------------------------------------------------\n";
}

// Функція для бінарного пошуку студента за прізвищем, спеціальністю та оцінкою з фізики
int BinSearch(Student* s, const int N, const string lname, const Spec spec, const int physics) {
    int L = 0, R = N - 1, m;
    while (L <= R) {
        m = (L + R) / 2;
        if (s[m].lname == lname && s[m].spec == spec && s[m].physics == physics)
            return m;
        if ((s[m].spec < spec) ||
            (s[m].spec == spec && s[m].lname < lname) ||
            (s[m].spec == spec && s[m].lname == lname && s[m].physics < physics))
            L = m + 1;
        else
            R = m - 1;
    }
    return -1;
}
int main() {
    SetConsoleCP(1251);    // Для коректного введення українських символів у консолі
    SetConsoleOutputCP(1251); // Для коректного відображення українських символів у консолі

    int N; // Кількість студентів
    cout << "Введіть кількість студентів: ";
    cin >> N;

    Student* s = new Student[N]; // Динамічний масив студентів

    Create(s, N);   // Виклик функції для заповнення даних студентів
    cout << "\nСтворений список студентів:\n";
    Print(s, N);    // Виведення студентів у початковому порядку

    Sort(s, N);     // Фізичне сортування масиву студентів
    cout << "\nСписок студентів після фізичного сортування:\n";
    Print(s, N);    // Виведення студентів після фізичного сортування

    int* indexArray = indexSort(s, N);   // Індексне сортування
    cout << "\nСписок студентів після індексного сортування:\n";
    PrintIndexSorted(s, indexArray, N);  // Виведення студентів у порядку індексного сортування

    string searchLname;
    int searchSpec;
    int searchPhysics;

    cout << "\nВведіть дані для пошуку студента:\n";
    cout << "Прізвище: ";
    cin >> searchLname;
    cout << "Спеціальність (0 - Комп'ютернi науки, 1 - Iнформатика, 2 - Математика та економiка, "
        << "3 - Фiзика та iнформатика, 4 - Трудове навчання): ";
    cin >> searchSpec;
    cout << "Оцінка з фізики: ";
    cin >> searchPhysics;

    int foundIndex = BinSearch(s, N, searchLname, (Spec)searchSpec, searchPhysics);

    if (foundIndex != -1) {
        cout << "\nЗнайдено студента:\n";
        cout << "| № | Прiзвище      | Курс | Спецiальнiсть           | Фiзика | Матем. | Прог. | Чис.мет. | Педагог. |\n";
        cout << "--------------------------------------------------------------------------------------------------------\n";
        cout << "| " << setw(2) << right << s[foundIndex].number
            << " | " << setw(13) << left << s[foundIndex].lname
            << " | " << setw(4) << right << s[foundIndex].kurs
            << " | " << setw(22) << left << strSpec[s[foundIndex].spec]
            << " | " << setw(6) << right << s[foundIndex].physics
            << " | " << setw(6) << right << s[foundIndex].math
            << " | ";

        if (s[foundIndex].spec == CS)
            cout << setw(5) << right << s[foundIndex].programming << " | " << setw(8) << " " << " | " << setw(8) << " ";
        else if (s[foundIndex].spec == IT)
            cout << setw(5) << " " << " | " << setw(8) << right << s[foundIndex].numMethods << " | " << setw(8) << " ";
        else
            cout << setw(5) << " " << " | " << setw(8) << " " << " | " << setw(8) << right << s[foundIndex].pedagogy;

        cout << " |\n";
        cout << "--------------------------------------------------------------------------------------------------------\n";
    }
    else {
        cout << "\nСтудента не знайдено.\n";
    }

    delete[] s;          
    delete[] indexArray; 

    return 0;
}
