#pragma once

#include<iostream>
#include<functional>

class Integral {
public:
    Integral() = default;
    Integral(const Integral& rhs);
    Integral(const double start, const double finish, const int step);
    Integral& operator=(const Integral& rhs) = default;
    ~Integral() = default;

public:
    double start_{ 0 };
    double finish_{ 0 };
    int step_{ 1 };
};

double Left_Rect(std::function<double(double)> f, double a, double b, double n);
double Right_Rect(std::function<double(double)> f, double a, double b, double n);
double Trapezoid(std::function<double(double)> f, double a, double b, double n);
double Simpson(std::function<double(double)> f, double a, double b, double n);

double MAINF(std::function<double(double)> f,
    std::function<double(std::function<double(double)>, double, double, double)> g,
    const Integral& rhs);

void Out_to_Tex(const Integral& rhs, const std::string fun, const int meth);