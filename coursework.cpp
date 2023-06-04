#include"coursework.hpp"
#define _USE_MATH_DEFINES
#define eps 0.001
#include<functional>
#include<cmath>
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
    start_ = start;
    finish_ = finish;
    step_ = step;
}

double Integral::MAINF(std::function<double(std::function<double(double)>, double, double, double)> method,
    std::function<double(double)> function,
    const Integral& rhs) {
    return method(function, rhs.start_,rhs.finish_,rhs.step_);
}

std::function<double(std::function<double(double)>, double, double, int)>
Integral::Method(const std::string meth) {
    std::map < std::string, std::function<double(std::function<double(double)>, double, double, int)>> map_meth{//method map
       {"1",
            [](std::function<double(double)> f, double a, double b, double n) {
            double step = (b - a) / n;
            double area = 0.0;
            for (int i = 0; i <= n - 1; ++i) {
                area += f(a + i * step) * step;
                }
            return area;
            }
       },
       {"2",
            [](std::function<double(double)> f, double a, double b, double n) {
            double step = (b - a) / n;
            double area = 0.0;
            for (int i = 1; i <= n; i++) {
                area += f(a + i * step) * step;
            }
            return area;
            }
       },
       {"3",
            [](std::function<double(double)> f, double a, double b, double n) {
            double step = (b - a) / n;
            double area = f(a) + f(b);
            for (int i = 1; i <= n - 1; i++) {
                area += 2 * f(a + i * step);
            }
            area *= step / 2;
            return area;
            }
       },
       {"4",
            [](std::function<double(double)> f, double a, double b, double n) {
            double step = (b - a) / n;
            double area = f(a) + f(b);
            int k = 0;
            for (int i = 1; i <= n - 1; i++) {
                k = 2 + 2 * (i % 2);
            area += k * f(a + i * step);
            }
            area *= step / 3;
            return area;
            }
       }
    };


    if (map_meth.find(meth) == map_meth.end()) {
        return 0;
    }
    else {
        return map_meth[meth];
    }
};

void Integral::Out_to_Tex(const Integral& rhs, const std::string fun, const std::string meth) {
    double start = rhs.start_;
    double finish = rhs.finish_;
    double step = rhs.step_;
    double stepForTex = 0;
    stepForTex = (finish - start) / step;

    std::map < std::string, std::function<std::string(std::string)>> Out_Tex_fun{
        {"sin",
               [](std::string x) {
                    std::string s = "";
                    s += "\\draw[blue, samples = 1000]   plot(\\x, {sin(\\x r) }) node[right]{$f(x) = \\sin x$ }; %function\n";
                    s += "\\draw[->](";
                    s += x;
                    s += ", -1.5) -- (";
                    s += x;
                    s += ", 1.5)node[above]{$f(x)$};% arrow Oy\n";
                    s += "\\foreach \\y in{-1,...,1} % Oy designation\n";
                    s += "\\draw[white!50!black](";
                    s += x;
                    s += "cm-2pt, \\y cm) -- (";
                    s += x;
                    s += "cm+2pt, \\y cm) node[anchor = east, font = \\tiny]{$\\y$};\n";
                    return s;
               }
        },
        {"cos",
            [](std::string x) {
                    std::string s = "";
                    s += "\\draw[blue, samples = 1000]   plot(\\x, {cos(\\x r) }) node[right]{$f(x) = \\sin x$ }; %function\n";
                    s += "\\draw[->](";
                    s += x;
                    s += ", -1.5) -- (";
                    s += x;
                    s += ", 1.5)node[above]{$f(x)$};% arrow Oy\n";
                    s += "\\foreach \\y in{-1,...,1} % Oy designation\n";
                    s += "\\draw[white!50!black](";
                    s += x;
                    s += "cm-2pt, \\y cm) -- (";
                    s += x;
                    s += "cm+2pt, \\y cm) node[anchor = east, font = \\tiny]{$\\y$};\n";
                    return s;
                    }
        },
        {"sqx",
                [](std::string x) {
                    std::string s = "";
                    s += "\\draw[blue, samples = 1000]   plot(\\x, {\\x*\\x}) node[right]{$f(x) = x^2$ }; %function\n";
                    s += "\\draw[->](";
                    s += x;
                    s += ", -1.5) -- (";
                    s += x;
                    s += ", 1.5)node[above]{$f(x)$};% arrow Oy\n";
                    s += "\\foreach \\y in{-1,...,1} % Oy designation\n";
                    s += "\\draw[white!50!black](";
                    s += x;
                    s += "cm-2pt, \\y cm) -- (";
                    s += x;
                    s += "cm+2pt, \\y cm) node[anchor = east, font = \\tiny]{$\\y$};\n";
                    return s;
                    }
        }
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

    std::map < std::string, std::string> Out_Tex_meth{
        {"1",
            "\\foreach \\x in{" + std::to_string(start) + "," + std::to_string(start + stepForTex) + ",...," +
            std::to_string(finish - eps) + " }% left rectangels\n" +
            "     \\draw[red, thick](\\x, 0) rectangle(\\x + " + std::to_string(stepForTex) + ", {" + fun_for_meth[fun]("x") + "});\n "
        },
        {"2",
            "\\foreach \\x in{" + std::to_string(start) + "," + std::to_string(start + stepForTex) + ",...," +
            std::to_string(finish - eps) + " }% right rectangels\n" +
            "     \\draw[red, thick](\\x, 0) rectangle(\\x + " + std::to_string(stepForTex) + ", {" + fun_for_meth[fun]("x + " +
            std::to_string(stepForTex)) + "});\n"
        },
        {"3",
            "\\foreach \\x in{" + std::to_string(start) + "," + std::to_string(start + stepForTex) + ",...," +
            std::to_string(finish - eps) + " }%trapezoids\n" +
            "     \\draw[red, thick](\\x, 0) -- (\\x,{" + fun_for_meth[fun]("x") + "}) -- (\\x + " + std::to_string(stepForTex) + ",{" +
            fun_for_meth[fun]("x+"+ std::to_string(stepForTex)) + "}) -- \n" + "     (\\x+" + std::to_string(stepForTex) + 
            ",0) -- cycle;\n"
        },
        {"4",
            "\\foreach \\x in{" + std::to_string(start) + "," + std::to_string(start + stepForTex) + ",...," +
            std::to_string(finish - eps) + " }% Simpson\n" +
            "     \\draw[red, thick](\\x,{" + fun_for_meth[fun]("x") + "}) -- (\\x,0) -- (\\x + " + std::to_string(stepForTex) +
            ",0) --(\\x+" + std::to_string(stepForTex) + ",{" + fun_for_meth[fun]("x+" + std::to_string(stepForTex)) +
            "}) (\\x,{" + fun_for_meth[fun]("x") + "}) parabola bend(\\x + " + std::to_string(stepForTex / 2) + ",{" +
            fun_for_meth[fun]("x+" + std::to_string(stepForTex / 2)) + "}) (\\x + " + std::to_string(stepForTex) +
            ",{" + fun_for_meth[fun]("x+" + std::to_string(stepForTex)) + "});\n"
        }
    };

    std::ofstream out;
    out.open("tex.tex");
    if (out.is_open()) {
        out << "\\documentclass{article}\n";
        out << "\\usepackage{tikz}\n";
        out << "\\usepackage{pgfplots}\n";
        out << "\\begin{document}\n";
        out << "\\begin{tikzpicture}[domain = ";
        out << start - 0.5 << ":" << finish + 0.5;
        out << ", scale = 1]\n";
        out << "\\draw[->](";
        out << start - 2;
        out << ", 0) -- (";
        out << finish + 2.5;
        out << ", 0)node[right] {$x$};% arrow Ox\n";
        std::string x_for_arrowOy = "";
        if (start * finish <= 0 || (std::abs(start) - 2 <= 0) || (std::abs(finish) - 2 <= 0)) {//oy on 0 
            x_for_arrowOy = "0";
        }
        else {
            if (finish > 0) {
                x_for_arrowOy = std::to_string(start - 1);
            }
            else {
                x_for_arrowOy = std::to_string(finish + 1);
            }
        }
        out << Out_Tex_fun[fun](x_for_arrowOy);
        out << "\\foreach \\x in{";
        out << (int)start - 1;
        out << ", ...,";
        out << (int)finish + 1;
        out << " }% Ox designation\n";
        out << "     \\draw[white!50!black](\\x cm, 2pt) -- (\\x cm, -2pt) node[anchor = north, font = \\tiny]{$\\x$};\n";
        out << "\\draw(";
        out << finish;
        out << ", 2pt) -- (";
        out << finish;
        out << ", -2pt) node[anchor = south west,font=\\tiny]{";
        out << finish;
        out << "}; % finish dashes\n";
        out << "\\draw(";
        out << start;
        out << ", 2pt) -- (";
        out << start;
        out << ", -2pt) node[anchor = south east,font=\\tiny]{";
        out << start;
        out << "}; % start dashes\n";
        out << Out_Tex_meth[meth];
        out << "\\end{tikzpicture}\n";
        out << "\\end{document}";
    }
    out.close();
}
