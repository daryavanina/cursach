#include"coursework.hpp"
#include<iostream>
#include<functional>
#include<sstream>
#include<fstream>
#include<map>

int main(){
//    int argc,      // Number of strings in array argv
//    char* argv[])  // Array of command-line argument strings
//{
    std::cout.precision(7);
    double start = 1, finish = 2, step = 10;

    char meth = '1';//номер метода в map_meth
    std::string fun = "sin";//функция в map_fun
    /*start = std::stod(argv[1]);
    finish = std::stod(argv[2]);
    step = std::stod(argv[3]);
    fun += argv[4];
    meth = *argv[5];*/
    Integral check = Integral(start, finish, step);
    /*  enum class Fun {
          sinn = 1,
          f2
      }etype;
      Fun var;
      int num = 0;
      num = static_cast<int>(Fun::f2);
      std::cout << num;
      enum class Meth { Left_R = 1, m2, m3};*/

    std::map < std::string, std::function<double(double)>> map_fun{//map функций
        {"sin",
                [](double x) {
                    return sin(x);
                }
        }
    };

    std::map < char, std::function<double(std::function<double(double)>, double, double, int)>> map_meth{//map методов
        {'1', Left_Rect },
        {'2', Right_Rect},
        {'3', Trapezoid},
        {'4', Simpson}
    };

    std::cout << MAINF(map_fun[fun], map_meth[meth], check);
    Out_to_Tex_LeftRect(check, fun, meth);

    return 0;
}