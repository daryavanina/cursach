#pragma once

#include<iostream>
#include<functional>
#include<map>

/**
* @brief Класс для вычисления интеграла численным методом
*/
class Integral {
public:
    Integral() = default;
    Integral(const Integral& rhs);
    Integral(const double start, const double finish, const double step);
    Integral& operator=(const Integral& rhs) = default;
    ~Integral() = default;

   /* double Left_Rect(std::function<double(double)> f, double a, double b, double n);

    double Right_Rect(std::function<double(double)> f, double a, double b, double n);

    double Trapezoid(std::function<double(double)> f, double a, double b, double n);

    double Simpson(std::function<double(double)> f, double a, double b, double n);
    */


    /**
    * @brief функция для вывода численного ответа
    * @param method метод для вычисления интеграла
    * @param function подынтегральная функция
    * @param rhs вычисляемый интеграл
    * @return
    */
    double MAINF(std::function<double(std::function<double(double)>, double, double, double)> method,
        std::function<double(double)> function,
        const Integral& rhs);

    /**
    * @brief функция для вывода в Tex
    * @param rhs вычисляемый интеграл
    * @param fun подынтегральная функция
    * @param meth метод, которым вычисляется интеграл
    */
    void Out_to_Tex(const Integral& rhs, const std::string fun, const std::string meth);

    /**
    * @brief функция, хранящая метод, с помощью которого считается интеграал
    * @param meth метод, которым вычисляется интеграл
    * @return численный ответ или 0, в случае если подынтегральной функции нет
    */
    std::function<double(std::function<double(double)>, double, double, int)>
        Method(const std::string meth);


public:
    //! Начало отрезка интегрирования
    double start_{ 0 };
    //! Конец отрезка интегрирования
    double finish_{ 0 };
    //! Шаг, с которым высчитывается интеграл (количество прямоугольников на отрезке)
    double step_{ 1 };
};
