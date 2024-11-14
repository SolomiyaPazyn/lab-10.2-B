#include <iostream>
#include <string>
#include <Windows.h>
#include <iomanip>
using namespace std;

enum Spec { CS, IT, ME, PhIT, TR };  // �������������� ��� ��� �������������� ��������

// ����� ����� ��� ����������� ���� ��������������
string strSpec[] = { "����'�����i �����", "I����������", "���������� �� ������i��", "�i���� �� i����������", "������� ��������" };

// ��������� ��� ��������� ���������� ��� ��������
struct Student {
    int number;     // ���������� ����� �������� � ����
    string lname;   // �������
    int kurs;       // ����
    Spec spec;      // ������������
    int physics;    // ������ � ������
    int math;       // ������ � ����������
    union {         // ��'������� ��� ������ ������ � ��������� �� ������������
        int programming;    // ������ � ������������� (��� CS)
        int numMethods;     // ������ � ��������� ������ (��� IT)
        int pedagogy;       // ������ � ��������� (��� ����� ��������������)
    };
};

// ������� ��� �������� ����� ��� ��������
void Create(Student* s, int amSt) {
    int sp;
    for (int i = 0; i < amSt; i++) {
        s[i].number = i + 1;  // ������������ ���������� ����� ��������

        cout << "������� � " << s[i].number << ":" << endl;
        cout << "��i�����: ";
        cin >> s[i].lname;
        cout << "����: ";
        cin >> s[i].kurs;
        cout << "����i����i��� (0 - ����'�����i �����, 1 - I����������, 2 - ���������� �� ������i��, "
            << "3 - �i���� �� i����������, 4 - ������� ��������): ";
        cin >> sp;
        s[i].spec = (Spec)sp;
        cout << "��i��� � �i����: ";
        cin >> s[i].physics;
        cout << "��i��� � ����������: ";
        cin >> s[i].math;

        // �������� ������ ������ ������� �� ������������
        if (s[i].spec == CS) {
            cout << "��i��� � �������������: ";
            cin >> s[i].programming;
        }
        else if (s[i].spec == IT) {
            cout << "��i��� � ��������� ������: ";
            cin >> s[i].numMethods;
        }
        else {
            cout << "��i��� � ���������: ";
            cin >> s[i].pedagogy;
        }
        cout << endl;
    }
}

// ������� ��� ��������� ����� ��� �������� � ���������� ������
void Print(Student* s, int amSt) {
    cout << "--------------------------------------------------------------------------------------------------------\n";
    cout << "| � | ��i�����      | ���� | ����i����i���           | �i���� | �����. | ����. | ���.���. | �������. |\n";
    cout << "--------------------------------------------------------------------------------------------------------\n";

    for (int i = 0; i < amSt; i++) {
        cout << "| " << setw(2) << right << s[i].number
            << " | " << setw(13) << left << s[i].lname
            << " | " << setw(4) << right << s[i].kurs
            << " | " << setw(22) << left << strSpec[s[i].spec]
            << " | " << setw(6) << right << s[i].physics
            << " | " << setw(6) << right << s[i].math
            << " | ";

        // ��������� ������ ������ � �������� �������
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

// ������� ��� ��������� ���������� ������ �������� �� ������������, ������� � ���������� �� ��������
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

// ������� ��� ���������� ���������� ������ ��������
int* indexSort(Student* s, const int N) {
    int* P = new int[N];  // ����� �������
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

// ������� ��� ��������� �������� ������������� ������ ��������
void PrintIndexSorted(Student* s, int* P, const int N) {
    cout << "--------------------------------------------------------------------------------------------------------\n";
    cout << "| � | ��i�����      | ���� | ����i����i���           | �i���� | �����. | ����. | ���.���. | �������. |\n";
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

// ������� ��� �������� ������ �������� �� ��������, ������������ �� ������� � ������
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
    SetConsoleCP(1251);    // ��� ���������� �������� ���������� ������� � ������
    SetConsoleOutputCP(1251); // ��� ���������� ����������� ���������� ������� � ������

    int N; // ʳ������ ��������
    cout << "������ ������� ��������: ";
    cin >> N;

    Student* s = new Student[N]; // ��������� ����� ��������

    Create(s, N);   // ������ ������� ��� ���������� ����� ��������
    cout << "\n��������� ������ ��������:\n";
    Print(s, N);    // ��������� �������� � ����������� �������

    Sort(s, N);     // Գ����� ���������� ������ ��������
    cout << "\n������ �������� ���� ��������� ����������:\n";
    Print(s, N);    // ��������� �������� ���� ��������� ����������

    int* indexArray = indexSort(s, N);   // �������� ����������
    cout << "\n������ �������� ���� ���������� ����������:\n";
    PrintIndexSorted(s, indexArray, N);  // ��������� �������� � ������� ���������� ����������

    string searchLname;
    int searchSpec;
    int searchPhysics;

    cout << "\n������ ��� ��� ������ ��������:\n";
    cout << "�������: ";
    cin >> searchLname;
    cout << "������������ (0 - ����'�����i �����, 1 - I����������, 2 - ���������� �� ������i��, "
        << "3 - �i���� �� i����������, 4 - ������� ��������): ";
    cin >> searchSpec;
    cout << "������ � ������: ";
    cin >> searchPhysics;

    int foundIndex = BinSearch(s, N, searchLname, (Spec)searchSpec, searchPhysics);

    if (foundIndex != -1) {
        cout << "\n�������� ��������:\n";
        cout << "| � | ��i�����      | ���� | ����i����i���           | �i���� | �����. | ����. | ���.���. | �������. |\n";
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
        cout << "\n�������� �� ��������.\n";
    }

    delete[] s;          
    delete[] indexArray; 

    return 0;
}
