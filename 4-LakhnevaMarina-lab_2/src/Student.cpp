// class studen in public: /*pair<int, string> some_student(string filename, int num, string name_abbreviation);*/
 
//pair<int, string> student::some_student(string filename_, int num_, string name_abbreviation_) {
//    filename = filename_;
//
//    num = num_;
//    name_abbreviation = name_abbreviation_;
//
//    ifstream fin(filename_);
//    fin >> num_;
//    fin >> name_abbreviation_;
//    fin.close();
//    return pair<int, string>(num_, name_abbreviation_);
//
//}

#include<locale>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std; // используем, чтобы упростить запись - std :: string и тд.

class student { 
    // базовый класс
public:
    student(char* n);
    vector<vector<int>> coefficients(string filename, int str);
    int get_sqrt_D(vector<vector<int>> coeff, int str);
    void print(student* A, int result);
private:
    string filename;

    char full_name[20];
    int str;
};

class bad_student : public student { // производный класс
public:
    bad_student(char* n) : student(n) {};
    pair<double, double> decision(double root_of_discriminant, int str);
};

class average_student : public student { // производный класс
public:
    average_student(char* n) : student(n) {};
    pair<double, double> real_roots_with_error(vector<vector<int>> coeff, double root_of_discriminant, int str);
};

class good_student : public student { // производный класс
public:
    good_student(char* n) : student(n) {};
    pair<double, double> real_roots(vector<vector<int>> coeff, double root_of_discriminant, int str);
};

class Teacher : public good_student { // производный класс
public:
    Teacher(char* n) : good_student(n) {};
    int check(student* A, double x_1, double x_2, vector<vector<int>> coeff, int str);
};

student::student(char* n) {
    strcpy_s(full_name, strlen(n) + 1, n);
}

vector<vector<int>> student::coefficients(string filename_, int str_) {
    // функция считывает из файла коэффициенты квадратного уравнения
    filename = filename_;
    str = str_;

    int size_ = 3;
    vector<vector<int>> coeff;
    coeff.assign(size_, vector<int>(size_));

    ifstream fin(filename_);
    for (int i = 0; i <= str_; i++) {
        for (int j = 0; j < size_; j++) {
            fin >> coeff[i][j];
        }
    }
    fin.close();
    return coeff;
}

int student::get_sqrt_D(vector<vector<int>> coeff, int str) {
    // функция считает дискриминант
    int a = coeff[str][0];
    int b = coeff[str][1];
    int c = coeff[str][2];
    double discriminant = (b * b - (4 * a * c));
    double root_of_discriminant = sqrt(discriminant);
    return root_of_discriminant;
}

pair<double, double> bad_student:: decision(double root_of_discriminant, int str) {
    int x_1 = 0;
    int x_2 = 0;
    return pair<double, double>(x_1, x_2);
}

pair<double, double> average_student::real_roots_with_error(vector<vector<int>> coeff, double root_of_discriminant, int str) {
    // функция считает действительные корни
    int a = coeff[str][0];
    int b = coeff[str][1];
    int c = coeff[str][2];
    double x_1 = 0;
    double x_2 = 0;

    if (root_of_discriminant == 0) {
        x_1 = ((-b) / (2 * a));
        x_2 = x_1;
        //std::cout << "Квадратное уравнение имеет один корень:" << "\n" << "x = " << x_1;
    }
    else {
        x_1 = (((-b) + root_of_discriminant) / (2 * a));
        x_2 = (((-b) - root_of_discriminant) / (4 * a)); // ОШИБКА
        //std::cout << "Квадратное уравнение имеет два корня:" << "\n" << "x_1 = " << x_1 << "\n" << "x_2 = " << x_2;
    }
    return pair<double, double>(x_1, x_2);
}

pair<double, double> good_student::real_roots(vector<vector<int>> coeff, double root_of_discriminant, int str) {
    // функция считает действительные корни
    int a = coeff[str][0];
    int b = coeff[str][1];
    int c = coeff[str][2];
    double x_1 = 0;
    double x_2 = 0;

    if (root_of_discriminant == 0) {
        x_1 = ((-b) / (2 * a));
        x_2 = x_1;
        //std::cout << "Квадратное уравнение имеет один корень:" << "\n" << "x = " << x_1;
    }
    else {
        x_1 = (((-b) + root_of_discriminant) / (2 * a));
        x_2 = (((-b) - root_of_discriminant) / (2 * a));
        //std::cout << "Квадратное уравнение имеет два корня:" << "\n" << "x_1 = " << x_1 << "\n" << "x_2 = " << x_2;
    }
    return pair<double, double>(x_1, x_2);
}

int Teacher::check(student* full_name, double x_1, double x_2, vector<vector<int>> coeff, int str) {
    // функция преподаватель: проверяет корни
    int point = 0;
    int sqr_D = get_sqrt_D (coeff, str);
    auto x = real_roots(coeff, sqr_D, str);

    if ((x.first == x_1) && (x.second == x_2)) {
        point = 1;
    }
    else {
        point = 0;
    }
    return point;
}

void student::print(student* full_name, int result) {
    cout << full_name->full_name << " : "<< result << "/3" << "\n";
}

int main() {
    setlocale(LC_CTYPE, "Russian");

    bad_student bad((char*)"Алеша Попович");
    average_student average((char*)"Добрыня Никитич");
    good_student good((char*)"Илья Муромец");

    Teacher genius((char*)"Князь Киевский");

    vector<vector<int>> coeff(3);

    int b = 0; // счетчик верных решений
    bad_student* student_1 = &bad;
    for (int i = 0; i < 3; i++) {
        coeff = bad.coefficients("coefficients_.txt", i);
        double sqrt_discriminant = bad.get_sqrt_D(coeff, i);
        auto x = bad.decision(sqrt_discriminant, i); // x.first x.second
        b += genius.check(student_1, x.first, x.second, coeff, i);
    }

    int a = 0; // счетчик верных решений
    average_student* student_2 = &average;
    for (int i = 0; i < 3; i++) {
        coeff = average.coefficients("coefficients_.txt", i);
        double sqrt_discriminant = average.get_sqrt_D(coeff, i);
        auto x = average.real_roots_with_error(coeff, sqrt_discriminant, i);
        a += genius.check(student_2, x.first, x.second, coeff, i);
    }

    int g = 0; // счетчик верных решений
    good_student* student_3 = &good;
    for (int i = 0; i < 3; i++) {
        coeff = good.coefficients("coefficients_.txt", i);
        double sqrt_discriminant = good.get_sqrt_D(coeff, i);
        auto x = good.real_roots(coeff, sqrt_discriminant, i); 
        g += genius.check(student_3, x.first, x.second, coeff, i);
    }

    bad.print(student_1, b);
    average.print(student_2, a);
    good.print(student_3, g);
    return 1;
}