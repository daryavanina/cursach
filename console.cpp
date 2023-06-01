#include"coursework.cpp"
#include<iostream>
#include<functional>
#include<sstream>
#include<fstream>
#include<map>

int main(    //){
    int argc,      // Number of strings in array argv
    char* argv[])  // Array of command-line argument strings
{
    std::cout.precision(7);
    double start = 1, finish = 2, step = 10;
    char meth = '1';//номер метода в map_meth
    std::string fun = "";//функция в map_fun
    start = std::stod(argv[1]);
    finish = std::stod(argv[2]);
    step = std::stod(argv[3]);
    fun += argv[4];
    meth = *argv[5];
    Integral check = Integral(start, finish, step);

    std::map < std::string, std::function<double(double)>> map_fun{//map функций
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
    std::map < char, std::function<double(std::function<double(double)>, double, double, int)>> map_meth{//map методов
        {'1', Left_Rect },
        {'2', Right_Rect},
        {'3', Trapezoid},
        {'4', Simpson}
    };
    if (!(map_fun.contains(fun) && map_meth.contains(meth)) || (step<=0) || (finish<start)) {
        std::cout << "Incorrent data";
    }
    else {
        std::cout << MAINF(map_fun[fun], map_meth[meth], check);
        Out_to_Tex(check, fun, meth);
    }
    return 0;
}