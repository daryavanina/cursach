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
    Integral(const double start, const double finish, const int step);
    Integral& operator=(const Integral& rhs) = default;
    ~Integral() = default;


public:
    //! Начало отрезка интегрирования
    double start_{ 0 };
    //! Конец отрезка интегрирования
    double finish_{ 0 };
    //! Шаг, с которым высчитывается интеграл (количество прямоугольников на отрезке)
    int step_{ 1 };
    
};

/**
* @brief Функция для вычисления интеграла методом левых прямоугольников
* @param f подынтегральная функция
* @param a начало отрезка интегрирования
* @param b конец отрезка интегрирования
* @param n количество прямоугольников в отрезке
* @return численное значения интеграла
*/
double Left_Rect(std::function<double(double)> f, double a, double b, double n);

/**
* @brief Функция для вычисления интеграла методом правых прямоугольников
* @param f подынтегральная функция
* @param a начало отрезка интегрирования
* @param b конец отрезка интегрирования
* @param n количество прямоугольников в отрезке
* @return численное значения интеграла
*/
double Right_Rect(std::function<double(double)> f, double a, double b, double n);

/**
* @brief Функция для вычисления интеграла методом трапеций
* @param f подынтегральная функция
* @param a начало отрезка интегрирования
* @param b конец отрезка интегрирования
* @param n количество трапеций в отрезке
* @return численное значения интеграла
*/
double Trapezoid(std::function<double(double)> f, double a, double b, double n);

/**
* @brief Функция для вычисления интеграла методом Симпсона
* @param f подынтегральная функция
* @param a начало отрезка интегрирования
* @param b конец отрезка интегрирования
* @param n количество криволинейных трапеций в отрезке
* @return численное значения интеграла
*/
double Simpson(std::function<double(double)> f, double a, double b, double n);

/**
* @brief функция для вывода численного ответа
* @param метод для вычисления интеграла
* @param подынтегральная функция
* @param вычисляемый интеграл
* @return
*/
double MAINF(std::function<double(std::function<double(double)>, double, double, double)> method,
    std::function<double(double)> function,
    const Integral& rhs);

/**
* @brief функция для вывода в Tex
* @param вычисляемый интеграл
* @param подынтегральная функция
* @param метод, которым вычисляется интеграл
*/
void Out_to_Tex(const Integral& rhs, const std::string fun, const std::string meth);
