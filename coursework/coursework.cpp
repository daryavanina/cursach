//#ifndef UNTITLED_RATIONAL_H
//#define UNTITLED_RATIONAL_H
//#endif //UNTITLED_RATIONAL_H
//#include <iosfwd>

#include"coursework.hpp"

#define _USE_MATH_DEFINES
#define eps 0.001
#include<functional>
#include <cmath>
#include<string>
#include<map>
#include<sstream>
#include<fstream>

Integral::Integral(const Integral& rhs)
{
    start_ = rhs.start_;
    finish_ = rhs.finish_;
    step_ = rhs.step_;
}

Integral::Integral(const double start, const double finish, const double step) {
    if (step <= 0)
        throw std::invalid_argument("Creating incorrect step");
    if (finish < start)
        throw std::invalid_argument("Incorrect integration limits");
    start_ = start;
    finish_ = finish;
    step_ = step;
}

double Left_Rect(std::function<double(double)> f, double a, double b, double n) {//интеграл левыми прямоугольниками
    double step = (b - a) / n;  
    double area = 0.0;  
    for (int i = 0; i <= n - 1; ++i) {
        area += f(a + i * step) * step; 
    }
    return area;
}
double Right_Rect(std::function<double(double)> f, double a, double b, double n) {//интеграл правыми треугольниками
    double step = (b - a) / n;  
    double area = 0.0;  
    for (int i = 1; i <= n; i++) {
        area += f(a + i * step) * step; 
    }
    return area;
}
double Trapezoid(std::function<double(double)> f, double a, double b, double n) {//интеграл трапециями
    double step = (b - a) / n;  
    double area = f(a) + f(b);  
    for (int i = 1; i <= n - 1; i++) {
        area += 2 * f(a + i * step); 
    }
    area *= step / 2;
    return area;
}
double Simpson(std::function<double(double)> f, double a, double b, double n) {//интеграл методом Симпсона
    double step = (b - a) / n;  
    double area = f(a)+f(b);  
    int k = 0;
    for (int i = 1; i <= n - 1; i++) {
        k = 2 + 2 * (i % 2);
        area += k * f(a + i * step); 
    }
    area *= step / 3;
    return area;
}

//double square_x(double x) {//функция от x^2
//    return x*x;
//}
//
//double line3x2(double x) {//функция от 3x+2
//    return 3*x+2;
//}
//
//std::function<double(double)> sine = [](double x) {//функц для второго способа
//    return sin(x);
//};

//double LeftR_sin2(const Integral& rhs) {//второй способ
//    return Left_Rect(sine, rhs.start_, rhs.finish_, rhs.step_);
//}
//
//double LeftR_sin1(const Integral& rhs) {//лефтр - первый способ
//        return Left_Rect(
//            [](double x) {
//                 return sin(x);
//            },
//               rhs.start_, rhs.finish_, rhs.step_);
//    }

double MAINF(std::function<double(double)> f,
    std::function<double(std::function<double(double)>, double, double, int)> g,
    const Integral& rhs) {
    return g(f, rhs.start_,rhs.finish_,rhs.step_);
}

void Out_to_Tex_LeftRect(const Integral& rhs, const std::string fun, const int meth) {
    double start = rhs.start_;
    double finish = rhs.finish_;
    double step = rhs.step_;
    double stepForTex = 0;
    stepForTex = (finish - start) / step;
    std::ofstream out;
    out.open("tex.tex");
    if (out.is_open()) {
        out << "\\documentclass{article}\n\
        \\usepackage{tikz}\n\
        \\usepackage{pgfplots}\n\
        \\begin{document}\n\
        \\begin{tikzpicture} [domain = ";
        out << start - 2 << ":" << finish + 2;
        out << ", scale = 1]\n\
        \\clip (";
        out << start - 2;
        out << ", -2) rectangle(";
        out << finish + 4;
        out << ", 2.5); \n\
        \\draw[thick](0, -1.5) -- (0, 1.5)node[above]{$f(x)$}; % Oy axis\n\
        \\draw[thick](";
        out << start - 1.5;
        out << ", 0) -- (";
        out << finish + 1.5;
        out << ", 0)node[right]{$x$}; % Ox axis\n\
        \\draw[->](0, 0) -- (0, 1.5); % arrow Oy\n\
        \\draw[->](0, 0) -- (";
        out << finish + 1.5;
        out << ", 0);% arrow Ox\n\
    \\foreach \\x in{0,...,";
        out << (int)start - 1;
        out << " }% Ox designation<0\n\
        \\draw[gray!70!white](\\x cm, 2pt) -- (\\x cm, -2pt) node[anchor = north]{$\\x$};%dashes on Ox\n\
    \\foreach \\x in{0,...,";
        out << (int)finish + 1;
        out << " }% Ox designation>0\n\
        \\draw[gray!70!white](\\x cm, 2pt) -- (\\x cm, -2pt) node[anchor = north]{$\\x$};%dashes on Ox\n\
    \\draw(";
        out << finish;
        out << ", 2pt) -- (";
        out << finish;
        out << ", -2pt) node[anchor = south west]{";
        out << finish;
        out << "}; % finish dashes\n\
\\draw(";
        out << start;
        out << ", 2pt) -- (";
        out << start;
        out << ", -2pt) node[anchor = south east]{";
        out << start;
        out << "}; % start dashes\n\
    \\foreach \\y in{-1,...,1}% Oy designation\n\
        \\draw[gray!70!white](2pt, \\y cm) -- (-2pt, \\y cm) node[anchor = east]{$\\y$};%dashes on Oy\n\
\n\
    \\draw[blue, samples = 1000]   plot(\\x, {";
        out << fun;
        out << "(\\x r) }) node[right]{$f(x) = \\";
        out << fun;
        out << " x$ }; % function\n\
\n\
        \\foreach \\x in{";
        out << start << "," << start + stepForTex << ",...," << finish + eps;
        out << " }% lines with steps\n\
        \\draw[gray, very thin](\\x, -1.1) -- (\\x, 1.1);\n\
\n\
        \\foreach \\x in{";
        out << start << "," << start + stepForTex << ",...," << finish - eps;
        out << " }% rectangels\n\
        \\draw[red, thick](\\x, 0) rectangle(\\x + ";
        out << stepForTex;
        out << ", {";
        out << fun;
        out << "(deg(\\x)) }); \n\
\n\
    \\end{tikzpicture}\n\
        \\end{document}";
    }
    out.close();
}

