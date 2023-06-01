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

Integral::Integral(const double start, const double finish, const int step) {
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

double MAINF(std::function<double(double)> f,
    std::function<double(std::function<double(double)>, double, double, double)> g,
    const Integral& rhs) {
    return g(f, rhs.start_,rhs.finish_,rhs.step_);
}

void Out_to_Tex(const Integral& rhs, const std::string fun, const int meth) {
    double start = rhs.start_;
    double finish = rhs.finish_;
    int step = rhs.step_;
    double stepForTex = 0;
    stepForTex = (finish - start) / step;

    std::map < std::string, std::string> Out_Tex_fun{
        {"sin",
                "\\draw[blue, samples = 1000]   plot(\\x, {sin(\\x r) }) node[right]{$f(x) = \\sin x$ }; % function\n"},
        {"cos",
                "\\draw[blue, samples = 1000]   plot(\\x, {cos(\\x r) }) node[right]{$f(x) = \\cos x$ }; % function\n"},
        {"sqx",
                "\\draw[blue, samples = 1000]   plot(\\x, {\\x*\\x }) node[right]{$f(x) = \\ x^2 $ }; % function\n"}
    };

    std::map<std::string, std::function<std::string(std::string)>> fun_for_meth{
        {"sin",
                [](std::string var) {
                return "sin(deg(\\" + var + "))";
                }
        },
        {"cos",
                [](std::string var) {
                return "cos(deg(\\" + var + "))";
                }
        },
        {"sqx",
                [](std::string var) {
                return "((\\" + var + ")*(\\" + var + "))";
                }
        }
    };

    std::map < char, std::string> Out_Tex_meth{
        {'1',
            "\\foreach \\x in{" + std::to_string(start) + "," + std::to_string(start + stepForTex) + ",...," + std::to_string(finish - eps) +
            " }% left rectangels\n\
            \\draw[red, thick](\\x, 0) rectangle(\\x + " + std::to_string(stepForTex) + ", {" + fun_for_meth[fun]("x") + "});"
        },
        {'2',
             "\\foreach \\x in{" + std::to_string(start) + "," + std::to_string(start + stepForTex) + ",...," + std::to_string(finish - eps) +
            " }% right rectangels\n\
            \\draw[red, thick](\\x, 0) rectangle(\\x + " + std::to_string(stepForTex) + ", {" + fun_for_meth[fun]("x+" + std::to_string(stepForTex)) + "});"
        },
        {'3',
            "\n\ \\foreach \\x in{" + std::to_string(start) + "," + std::to_string(start + stepForTex) + ",...," + std::to_string(finish - eps) +
            " }%trapezoids\n\
            \\draw[red, thick](\\x, 0) -- (\\x,{" + fun_for_meth[fun]("x") + "}) -- (\\x+" + std::to_string(stepForTex) + ",{" + fun_for_meth[fun]("x+"+ std::to_string(stepForTex))
            + "}) -- (\\x+" + std::to_string(stepForTex) + ",0) -- cycle;"
        },
        {'4',
            "\\foreach \\x in{" + std::to_string(start) + "," + std::to_string(start + stepForTex) + ",...," + std::to_string(finish - eps) +
            " }% Simpson\n\
            \\draw[red, thick](\\x,{" + fun_for_meth[fun]("x") + "}) -- (\\x,0) -- (\\x+" + std::to_string(stepForTex) + ",0) --(\\x+" + std::to_string(stepForTex) +
            ",{" + fun_for_meth[fun]("x+" + std::to_string(stepForTex)) + "}) (\\x,{" + fun_for_meth[fun]("x") + "}) parabola bend(\\x + " + std::to_string(stepForTex / 2) 
            + ",{" + fun_for_meth[fun]("x+" + std::to_string(stepForTex / 2)) + "}) (\\x + " + std::to_string(stepForTex) + ",{" 
            + fun_for_meth[fun]("x+" + std::to_string(stepForTex)) + "});"
        }
    };

    std::ofstream out;
    out.open("tex.tex");
    if (out.is_open()) {
        out << "\\documentclass{article}\n\
        \\usepackage{tikz}\n\
        \\usepackage{pgfplots}\n\
        \\begin{document}\n\
        \\begin{tikzpicture} [domain = ";
        out << start - 0.5 << ":" << finish + 0.5;
        out << ", scale = 1]\n";
        if (start * finish >= 0) {
            out<<"\\draw[->](";
            out << start - 1;
            out << ", -5) -- (";
            out << start - 1;
            out << ", 5)node[above]{$f(x)$}; % arrow Oy\n";
            out << "\\foreach \\y in{-1,...,1} % Oy designation\n\
                    \\draw[white!50!black](";
            out << start - 1;
            out << "cm-2pt, \\y cm) -- (";
            out << start - 1;
            out << "cm+2pt, \\y cm) node[anchor = east,font=\\tiny]{$\\y$};%dashes on Oy\n";
        }
        else {
            out << "\\draw[->](0, -5) -- (0, 5)node[above]{$f(x)$}; % arrow Oy\n";
            out<<"\\foreach \\y in{-4,...,4} % Oy designation\n\
                  \\draw[white!50!black](-2pt, \\y cm) -- (2pt, \\y cm) node[anchor = east,font=\\tiny]{$\\y$};%dashes on Oy\n";
        }
        out<<"\\draw[->](";
        out << start - 1.5;
        out << ", 0) -- (";
        out << finish + 1.5;
        out << ", 0)node[right] {$x$};% arrow Ox\n\
    \\foreach \\x in{";
        out << (int)start - 1;
        out << ", ...,";
        out << (int)finish + 1;
        out << " }% Ox designation\n\
        \\draw[white!50!black](\\x cm, 2pt) -- (\\x cm, -2pt) node[anchor = north,font=\\tiny]{$\\x$};%dashes on Ox\n\
    \\draw(";
        out << finish;
        out << ", 2pt) -- (";
        out << finish;
        out << ", -2pt) node[anchor = south west,font=\\tiny]{";
        out << finish;
        out << "}; % finish dashes\n\
\\draw(";
        out << start;
        out << ", 2pt) -- (";
        out << start;
        out << ", -2pt) node[anchor = south east,font=\\tiny]{";
        out << start;
        out << "}; % start dashes\n";
        out << "\n";
        out << Out_Tex_fun[fun];
        out << Out_Tex_meth[meth];
        out<<"\n\\\end{tikzpicture}\n\
        \\end{document}";
    }
    out.close();
}