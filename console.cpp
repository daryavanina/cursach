#include"coursework.hpp"
#include<iostream>
#include<functional>
#include<sstream>
#include<fstream>
#include<map>

int main(
    int argc,      // Number of strings in array argv
    char* argv[])  // Array of command-line argument strings
{
    std::cout.precision(7);
    double start = 1;
    double finish = 2;
    double step = 10;
    std::string fun = "";//function in map_fun
    std::string meth = "";//method number in map_meth
    start = std::stod(argv[1]);
    finish = std::stod(argv[2]);
    step = std::stod(argv[3]);
    fun += argv[4];
    meth += argv[5];
    Integral check = Integral(start, finish, step);

    std::map < std::string, std::function<double(double)>> map_fun{//map of functions
        {"sin",
                [](double x) {
                    return sin(x);
                }
        },
        {"cos",
                [](double x) {
                    return cos(x);
                }
        },
        {"sqx",
                [](double x) {
                    return x*x;
                }
        }
    };
    std::map < std::string, std::function<double(std::function<double(double)>, double, double, int)>> map_meth{//method map
        {"1", Left_Rect},
        {"2", Right_Rect},
        {"3", Trapezoid},
        {"4", Simpson}
    };

    if (!(map_fun.find(fun) == map_fun.end()) && map_meth.find(meth) == map_meth.end() ||
         (step<=0) || (finish<start)) {//abequacy check
        std::cout << "Incorrent data";
    }
    else {
        std::cout << MAINF(map_meth[meth],map_fun[fun], check);
        Out_to_Tex(check, fun, meth);
    }
    return 0;
}
