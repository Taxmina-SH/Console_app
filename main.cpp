#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <algorithm>

using namespace std;


struct FIO
{
   string lastName,
      forstName,
      patronymic;
};
struct Date
{
   int day,
      month,
      year;
};
struct Address
{
   string street;
   int numFlat;
};

class Person
{
protected:
   FIO fio;
   Date date;
   Address address;

public:
   
   Person()
   {
      address.street = "";
      address.numFlat = 0;

      date.day = 0;
      date.month = 0;
      date.year = 0;

      fio.forstName = "";
      fio.lastName = "";
      fio.patronymic = "";
   }
   Person(FIO fio, Date date, Address address)
   {
      this->address.street = address.street;
      this->address.numFlat = address.numFlat;

      this->date.day = date.day;
      this->date.month = date.month;
      this->date.year = date.year;

      this->fio.forstName = fio.forstName;
      this->fio.lastName = fio.lastName;
      this->fio.patronymic = fio.patronymic;
   }
   virtual void DataEntry()
   {
      cout << "\nФИО: ";
      cin >> fio.forstName >> fio.lastName >> fio.patronymic;

      cout << "Дата рождения: ";
     cin >> date.day >> date.month >> date.year;

      cout << "Адрес проживания: ";
      cin >> address.street >> address.numFlat;
   }
   virtual void Print_Info() const
   {
      cout << "ФИО: " << fio.forstName << " " << fio.lastName << " " << fio.patronymic << endl;
      cout << "Дата рождения: " << date.day << "." << date.month << "." << date.year << endl;
      cout << "Адрес проживания: " << address.street << ", " << address.numFlat << endl;
   }
   ~Person() {};
};

class Student : public Person
{
private:
   string university;
   string specialization;
   Date startStudy;
public:
   Student()
   {
      startStudy.day = 0;
      startStudy.month = 0;
      startStudy.year = 0;

      university = "Не указан";
      specialization = "Не указан";
   }
   Student(string university, string specialization, Date startStudy,
      FIO fio, Date date, Address address) :
      Person(fio, date, address)
   {
      this->university = university;
      this->specialization = specialization;

      this->startStudy.day = startStudy.day;
      this->startStudy.month = startStudy.month;
      this->startStudy.year = startStudy.year;
   }
   void DataEntry() override
   {
      Person::DataEntry();
      cout << "Университет: "; cin >> university;
      cout << "Специализация: "; cin >> specialization;
      cout << "Начало обучения: ";
      cin >> startStudy.day >> startStudy.month >> startStudy.year;

   }
   friend ostream& operator<<(ostream& out, const Student& student)
   {
      out << "ФИО: " << student.fio.forstName << " " << student.fio.lastName
         << " " << student.fio.patronymic << endl;
      out << "Дата рождения: " << student.date.day << "." << student.date.month
         << "." << student.date.year << endl;
      out << "Адрес проживания: " << student.address.street << ", "
         << student.address.numFlat << endl;
      out << "Университет: " << student.university << endl;
      out << "Специализация: " << student.specialization << endl;
      out << "Начало обучения: " << student.startStudy.day << "."
         << student.startStudy.month << "." << student.startStudy.year << endl;

      return out;
   }
   static void SurtLastName(vector<Student>& st)
   {
      sort(st.begin(), st.end(), [](const Student& a, const Student& b)
      {
         return a.fio.forstName < b.fio.forstName;
      });
   }
   ~Student() {};
};


class Employee : public Person
{
private:
   string company;
   string position;
   double salary;
public:
   Employee()
   {
      company = "Не указан";
      position = "Не указан";
      salary = 0;
   }
   Employee(string company, string position, double salary,
      FIO fio, Date date, Address address) :
      Person(fio, date, address)
   {
      this->company = company;
      this->position = position;
      this->salary = salary;
   }
   void Print_Info() const override
   {
      Person::Print_Info();
      cout << "Компания: " << company << endl;
      cout << "Положение: " << position << endl;
      cout << "Зарплата: " << salary << endl;
   }
   friend istream& operator>>(istream& in, Employee& employee)
   {
      cout << "ФИО: ";
      in >> employee.fio.forstName >> employee.fio.lastName
         >> employee.fio.patronymic;
      cout << "Дата рождения: ";
      in >> employee.date.day >> employee.date.month
         >> employee.date.year;
     cout << "Адрес проживания: ";
      in >> employee.address.street >> employee.address.numFlat;
      cout << "Компания: ";
      in >> employee.company;
      cout << "Положение: ";
      in >> employee.position;
      cout << "Зарплата: ";
      in >> employee.salary;
      if (employee.salary < 0)
         throw invalid_argument("Зарплата не может быть отрицательной");
      return in;
   }
   static void SurtLastName(vector<Employee>& em)
   {
      sort(em.begin(), em.end(), [](const Employee& a, const Employee& b)
         {
            return a.fio.forstName < b.fio.forstName;
         });
   }
   ~Employee() {};
};

int DateChange()
{
   cout << "Под каким номером: ";
   int numCh;
   cin >> numCh;

   return numCh;
}

int choice;
void Menu()
{
   cout << "Выберите действие: \n"
      << "0. Выход из программы\n"
      << "1. Ввод данных студента\n"
      << "2. Вывод данных студента\n"
      << "3. Ввод данных работника\n"
      << "4. Вывод данных работника\n"
      << "5. Добавление данных\n"
      << "6. Удаление данных\n"
      << "7. Изменение данных\n"
      << "8. Сортировать по фамилии\n"
      << "Ваш выбор: ";
    cin >> choice;
}


int main() {
   SetConsoleCP(1251);
   SetConsoleOutputCP(1251);

   Menu();
   cout << endl;
   int size_student = 0;
   vector<Student> st;


   int size_employee = 0;
   vector<Employee> em;

   while (choice != 0)
   {
      int num = 0, data_change;
      switch (choice)
      {
      case 1:
         system("cls");
         cout << "Введите количество студентов: ";
         cin >> size_student;
         system("cls");
         st.resize(size_student);
         for (int i = 0; i < size_student; i++)
         {
            cout << "\nВведите данные " << i + 1 << "-ого студента" << endl;
            st[i].DataEntry();
            system("cls");

         }
         system("cls");
         Menu();
         break;
      case 2:
         system("cls");
         if (size_student == 0)
            cout << "Список студентов пуст" << endl;
         else
         {
            for (int i = 0; i < size_student; i++)
            {
               cout << "\nДанные " << i + 1 << "-ого студента" << endl;
               cout << st[i];
               cout << "____________________________________________" << endl;
            }
         }
         system("pause");
         system("cls");
         Menu();
         break;
      case 3:
         int i;
         system("cls");
         cout << "Введите количество работников: ";
         cin >> size_employee;
         system("cls");
         em.resize(size_employee);
         i = 0;
         while (i < size_employee)
         {
            try
            {
               for (; i < size_employee; i++)
               {
                  cout << "Введите данные " << i + 1 << "-ого работника\n\n";
                  cin >> em[i];
                  system("cls");
               }
            }
            catch (const invalid_argument& e)
            {
               cout << "Ошибка: " << e.what() << endl;
               cout << "Введите данные заново" << endl;
               system("pause");
               system("cls");
            }
         }
         system("cls");
         Menu();
         break;
      case 4:
         system("cls");
         if (size_employee == 0)
            cout << "Список работников пуст" << endl;
         else
         {
            for (int i = 0; i < size_employee; i++)
            {
               cout << "\nДанные " << i + 1 << "-ого работника" << endl;
               em[i].Print_Info();
               cout << "____________________________________________" << endl;
            }
         }
         system("pause");
         system("cls");
         Menu();
         break;
      case 5:
         system("cls");
         cout << "В какой список хотите добавить данные\n"
            << "1. студента\n"
            << "2. работника\n"
            << "3. Назад\n";
         cin >> num;
         system("cls");
         if (num == 1)
         {
            size_student++;
            st.resize(size_student);
            st[size_student - 1].DataEntry();
         }
         else if (num == 2)
         {
            size_employee++;
            em.resize(size_employee);
            cin >> em[size_employee - 1];
         }
         else {
            system("cls");
            Menu();
         }
         break;
      case 6:
         system("cls");
         cout << "Чьи данные хотите удалить\n"
            << "1. студента\n"
            << "2. работника\n"
            << "3. Назад\n";
         cin >> num;
         system("cls");
         if (num == 1 || num == 2)
            data_change = DateChange();
         if (num == 1)
         {
            st.erase(st.begin() + num - 1);
            cout << "Данные удалены" << endl;
            system("pause");
            size_student--;
         }
         else if (num == 2)
         {
            em.erase(em.begin() + num - 1);
            cout << "Данные удалены" << endl;
            system("pause");
            size_employee--;
         }
         else {
            system("cls");
            Menu();
         }
         break;
      case 7:
         system("cls");
         cout << "Чьи данные вы хотите поменять\n"
            << "1. студента\n"
            << "2. работника\n"
            << "3. Назад\n";
         cin >> data_change;
         num = DateChange();
         system("cls");
         if (data_change == 1)
            st[num - 1].DataEntry();
         else if (data_change == 2)
            cin >> em[num - 1];

         system("cls");
         Menu();
         
         break;
      case 8:
         system("cls");
         cout << "Чьи данные вы хотите отфильтровать\n"
            << "1. студента\n"
            << "2. работника\n"
            << "3. Назад\n";
         cin >> num;
         system("cls");

         if (num == 1) {
            Student::SurtLastName(st);
            cout << "Готово!" << endl;
            system("pause");

         }
         else if (num == 2)
         {
            Employee::SurtLastName(em);
            cout << "Готово!" << endl;
            system("pause");

         }
         system("cls");
         Menu();
         break;
      default:
         cout << "Неверная команда! Попробуйте снова" << endl;
         Menu();
         break;
      }
   }
   cout << "\nРабота завершена!" << endl;

   return 0;
}
