// coursework.h : включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта.

#pragma once

#include<iostream>
#include<functional>

class Integral {
public:
    Integral() = default;
    //explicit Integral(const int rhs);
    Integral(const Integral& rhs);
    Integral(const double start, const double finish, const double step);
    Integral& operator=(const Integral& rhs) = default;
    ~Integral() = default;

public:
    double start_{ 0 };
    double finish_{ 0 };
    double step_{ 1 };
};

double Left_Rect(std::function<double(double)> f, double a, double b, double n);
double Right_Rect(std::function<double(double)> f, double a, double b, double n);
double Trapezoid(std::function<double(double)> f, double a, double b, double n);
double Simpson(std::function<double(double)> f, double a, double b, double n);

double MAINF(std::function<double(double)> f,
    std::function<double(std::function<double(double)>, double, double, int)> g,
    const Integral& rhs);

void Out_to_Tex_LeftRect(const Integral& rhs, const std::string fun, const int meth);
// TODO: установите здесь ссылки на дополнительные заголовки, требующиеся для программы.
