#include<locale>
#include <iostream>
#include <math.h>

double set_the_equation(double a, double b, double c) {
    // функция позволяет посмотреть вид уравнения
    if ((a > 0) || (a < 0)) {
        if ((b < 0) && (c < 0)) {
            std::cout << a << "x^2 " << b << "x " << c << "\n";
        }
        else if ((b > 0) && (c > 0)) {
            std::cout << a << "x^2 + " << b << "x + " << c << "\n";
        }
        else if ((b < 0) && (c > 0)) {
            std::cout << a << "x^2 " << b << "x + " << c << "\n";
        }
        else if ((b > 0) && (c < 0)) {
            std::cout << a << "x^2 + " << b << "x " << c << "\n";
        }
        else if ((b == 0) && (c < 0)) {
            std::cout << a << "x^2 " << c << "\n";
        }
        else if ((c == 0) && (b < 0)) {
            std::cout << a << "x^2 " << b << "x " << "\n";
        }
        else if ((b == 0) && (c > 0)) {
            std::cout << a << "x^2 + " << c << "\n";
        }
        else if ((c == 0) && (b > 0)) {
            std::cout << a << "x^2 + " << b << "x " << "\n";
        }
    }
    else {
        if ((b < 0) && (c < 0)) {
            std::cout << b << "x " << c << "\n";
        }
        else if ((b > 0) && (c > 0)) {
            std::cout << b << "x + " << c << "\n";
        }
        else if ((b < 0) && (c > 0)) {
            std::cout << b << "x + " << c << "\n";
        }
        else if ((b > 0) && (c < 0)) {
            std::cout << b << "x " << c << "\n";
        }
        else if ((b == 0) && (c < 0)) {
            std::cout << c << "\n";
        }
        else if ((c == 0) && (b < 0)) {
            std::cout << b << "x " << "\n";
        }
        else if ((b == 0) && (c > 0)) {
            std::cout << c << "\n";
        }
        else if ((c == 0) && (b > 0)) {
            std::cout << b << "x " << "\n";
        }
    }

    return 0;
}

double get_D(double a, double b, double c) {
    // функция считает дискриминант
    double discriminant = 0;
    discriminant = ( pow(b,2) - (4 * a * c) );

    return discriminant;
}

double real_roots(double a, double b, double c, double root_of_discriminant) {
    // функция считает действительные корни
    double x = 0;
    double x_1 = 0;
    double x_2 = 0;
    
    if (root_of_discriminant == 0) {
        x = ( (-b) / (2 * a) );
        std::cout << "Квадратное уравнение имеет один корень:" << "\n" << "x = " << x;
    }
    else {
        x_1 = (((-b) + root_of_discriminant) / (2 * a));
        x_2 = (((-b) - root_of_discriminant) / (2 * a));
        std::cout << "Квадратное уравнение имеет два корня:" << "\n" << "x_1 = " << x_1 << "\n" << "x_2 = " << x_2;
    }
    return 0;
}

double complex_roots(double a, double b, double c, double discriminant) {
    // функция считает комплексные корни
    double complex = 0;
    complex = sqrt((-1) * discriminant);

    double x_c = 0;
    x_c = (complex / (2 * a));
    double x_r = 0;
    x_r = ( (-b) / (2 * a) );

    std::cout << "x_1 = " << x_r << " + " << x_c << "*i" << "\n" << "x_2 = " << x_r << " - " << x_c << "*i";

    return 0;
}

double conditions_square(double a, double b, double c) {
    // функция проверяет дискриминант для полного квадратного уравнения
    double discriminant = 0;
    discriminant = get_D(a, b, c);
        if (discriminant < 0) {
            std::cout << "Дискриминант D < 0" << "\n" << "Корни комплексные:" << "\n";
            complex_roots(a, b, c, discriminant);
        }
        else {
            double root_of_discriminant = 0;
            root_of_discriminant = sqrt(discriminant);
            std::cout << "D = " << discriminant << "\n";
            real_roots(a, b, c, root_of_discriminant);
        }
        return 0;
}

double a_0(double b, double c) {
    // функция для неполного квадратного уравнения, при а = 0
    double x = 0;
    x = ( (-c) / b );
    std::cout << "Один корень:" << "\n" << "x = " << x;

    return x;
}

double b_0(double a, double c) {
    // функция для неполного квадратного уравнения, при b = 0
    double x = 0;
    double value = 0;
    value = ( (-c) / a );

    if (value > 0) {
        std::cout << "Корни вещественные:" << "\n";
        x = sqrt(value);
        std::cout << "x_1 = " << x << "\n" << "x_2 = -" << x;
    }
    else {
        std::cout << "Корни комплексные:" << "\n";
        double value_ = 0;
        value_ = ( (-1) * value);

        x = sqrt(value_);
        std::cout << "x_1 = " << x << "*i" << "\n" << "x_2 = -" << x << "*i";
    }
    return 0;
}

double c_0(double a, double b) {
    // функция для неполного квадратного уравнения, при c = 0
    double x_2 = 0;
    x_2 = ( (-b) / a );
    std::cout << "x_1 = 0" << "\n" << "x_2 = " << x_2;
    
    return 0;
}

void conditions_partial(double a, double b, double c) {
    // функция проверяет условия для неполного квадратного уравнения
    if ( (a == 0) && (b == 0) && (c == 0) ) {
        std::cout << "Значение х - может быть любым";
    }
    else if ( (a == 0) && (b == 0) ) {
        std::cout << "Если с = 0 -> значении х - может быть любым, иначе выражение неверное.";
    }
    else if ( ((a == 0) && (c == 0)) || ((b == 0) && (c == 0)) ) {
        std::cout << "Один корень" << "\n" << "x = 0";
    }
    else if (a == 0) {
        a_0(b, c);
    }
    else if (b == 0) {
        b_0(a, c);
    }
    else if (c == 0) {
        c_0(a, b);
    }
}

void solve(double a, double b, double c) {
    // функция определяет вид уравнения
    set_the_equation(a, b, c);
    if ( (a == 0) || (b == 0) || (c == 0) ) {
        std::cout << "Введеное квадратное уравнение является неполным!" << "\n";
        conditions_partial(a, b, c);
    }
    else {
        std::cout << "Введеное квадратное уравнение является полным." << "\n";
        conditions_square(a, b, c);
    }
}

int main() {
    setlocale(LC_CTYPE, "Russian");
    double a = 0;
    double b = 0;
    double c = 0;

    std::cout << "Введите коэффициенты квадратного уравнения:" << "\n";
    std::cout << "a = ";
    std::cin >> a;
    std::cout << "b = ";
    std::cin >> b;
    std::cout << "c = ";
    std::cin >> c;

    solve(a, b, c);
    return 0;
}