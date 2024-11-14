#include "pch.h"
#include "CppUnitTest.h"
#include "../lab 10.2 B.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
            const int N = 3;
            Student* students = new Student[N];

            // Заповнюємо тестові дані
            students[0].lname = "Петров";
            students[0].spec = CS;
            students[0].physics = 5;
            students[0].math = 4;
            students[0].programming = 5;

            students[1].lname = "Іванов";
            students[1].spec = IT;
            students[1].physics = 4;
            students[1].math = 5;
            students[1].numMethods = 4;

            students[2].lname = "Сидоров";
            students[2].spec = ME;
            students[2].physics = 3;
            students[2].math = 3;
            students[2].pedagogy = 4;

            // Сортуємо масив для коректної роботи бінарного пошуку
            Sort(students, N);

            // Тест 1: Пошук існуючого студента
            int result1 = BinSearch(students, N, "Петров", CS, 5);
            Assert::IsTrue(result1 != -1);

            // Тест 2: Пошук неіснуючого студента
            int result2 = BinSearch(students, N, "Невідомий", CS, 5);
            Assert::AreEqual(-1, result2);

            delete[] students;
		}
	};
}
