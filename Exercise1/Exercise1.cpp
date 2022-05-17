#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <random>
#include <sstream>
using namespace std;


struct Student
{
    string recBookNum;
    string groupNum;
    string fullName;
};

vector<Student> FillStudentsArr();
void PrintStudent(Student& student);
size_t BarrierSearch(vector<Student>& students, Student& desStudent);
Student LinearSearch(const vector<Student>& students, const string& desRecBookNum);
template <typename T>
std::string toString(T val);
vector<Student> FillArr();

int main()
{
    //создаем массив
    vector<Student> students = FillArr();

    //Вводим номер книжки искомого студента
    Student desStudent;
    cout << "Write desired record book number(6 numbers): ";
    cin >> desStudent.recBookNum;

    //Линейный поиск
    auto start = chrono::high_resolution_clock::now();
    LinearSearch(students, desStudent.recBookNum);
    auto end = chrono::high_resolution_clock::now();

    //Вывод
    PrintStudent(desStudent);
    auto dur = end - start;
    cout << "Linear search time: " << fixed << chrono::duration_cast<chrono::microseconds>(dur).count() << "ms\n";

    //Вводим информацию для поиска с барьером
    cout << "Write desired student info: \n";
    cin >> desStudent.recBookNum >> desStudent.groupNum;
    getline(cin, desStudent.fullName);
    if (desStudent.fullName[0] == ' ')
    {
        desStudent.fullName.erase(0, 1);
    }

    //Поиск барьером
    start = chrono::high_resolution_clock::now();
    BarrierSearch(students, desStudent);
    end = chrono::high_resolution_clock::now();
    dur = end - start;

    //Вывод
    cout << "Index of desired student: ";
    cout << "\nBarier search time: " << fixed << chrono::duration_cast<chrono::microseconds>(dur).count() << "ms\n";
}

//111111 1111 Gregory Jhon Hause
//222222 2222 Dmitriy Lotte Knovs
//333333 3333 Genry Mabel Dohan



Student LinearSearch(const vector<Student>& students, const string& desRecBookNum)
{
    for (int i = 0; i < students.size(); i++)
    {
        if (students[i].recBookNum == desRecBookNum) return students[i];
    }
    return Student{ "","","" };
}

size_t BarrierSearch(vector<Student>& students, Student& desStudent)
{
    size_t length = students.size();
    students[length - 1] = desStudent;
    size_t i = 0;
    while (students[i].recBookNum != desStudent.recBookNum)
    {
        i++;
    }
    return i < length ? i : -1;
}

void PrintStudent(Student& student)
{
    cout << "Student record book number: " << student.recBookNum
        << "\nStudent group number: " << student.groupNum
        << "\nStudent full name" << student.fullName << endl;
}

vector<Student> FillStudentsArr()
{
    int size = 0;
    while (size <= 0)
    {
        cout << "Enter number of students: ";
        cin >> size;
        if (size <= 0)
            cout << "\nOops! Invalid size!\n";
    }
    vector<Student> students(size);
    cout << "Fill a table {Student record book number, Student group number, Student full name}:\n";
    for (int i = 0; i < size; i++)
    {
        cin >> students[i].recBookNum >> students[i].groupNum;
        getline(cin, students[i].fullName);
        if (students[i].fullName[0] == ' ')
        {
            students[i].fullName.erase(0, 1);
        }
    }
    return students;
}

vector<Student> FillArr()
{
    int size = 1000000;
    int len = 6;
    vector<Student> students(size);
    std::string tmp_s;
    int temp = 0;
    int tlen;
    for (int i = 0; i < size; i++)
    {
        tmp_s = toString(temp);
        tlen = len - tmp_s.length();
        for (int i = 0; i < tlen; i++)
        {
            tmp_s = '0' + tmp_s;
        }
        students[i].recBookNum = tmp_s;
        students[i].groupNum = "1234";
        students[i].groupNum = "Gregory Jhon Hause";
        temp++;
    }

    return students;
}

template <typename T>
std::string toString(T val)
{
    std::ostringstream oss;
    oss << val;
    return oss.str();
}