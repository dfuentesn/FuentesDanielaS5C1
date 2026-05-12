#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <array>

const int DIM = 3; //Ahora la dimension del sistema es 3 (S I R)

double tf = 60.0;  // Tiempo final
const double B = 1e-3;  //Mi parametro beta, uso B por comodidad
const double r = 1e-1;

std::array<double, DIM> f(double t, std::array<double, DIM> y){
    double S = y[0], I = y[1], R = y[2];
    return {-B*S*I, (B*S*I) - (r*I), r*I };
}

//Como no hay una funcion para las sumas, aca realizaso una para la suma de dos arreglos
std::array<double, DIM> arr_sum(std::array<double, DIM> a, std::array<double, DIM> b){
    std::array<double, DIM> result;
    for (int i = 0; i < DIM; i++) result[i] = a[i] + b[i];
    return result;
}

//Lo mismo pero para multiplicacion con escalares
std::array<double, DIM> arr_mul(double s, std::array<double, DIM> a){
    std::array<double, DIM> result;
    for (int i = 0; i < DIM; i++) result[i] = s * a[i];
    return result;
}

void euler(int N, double t0, std::array<double, DIM> y0, double h, std::ofstream &file){

    double t = t0;
    std::array<double, DIM> y = y0;

    for (int i = 0; i < N; i++){
        file << t << " " << y[0] << " " << y[1] << " " << y[2] << "\n";
        
        y = arr_sum(y, arr_mul(h, f(t, y)));
        t = t + h;
    }
}

void runge_kutta_4(int N, double t0, std::array<double, DIM> y0, double h, std::ofstream &file){

    double t = t0;
    std::array<double, DIM> y = y0;

    for (int i = 0; i < N; i++){
        file << t << " " << y[0] << " " << y[1] << " " << y[2] << "\n";

        std::array<double, DIM> k1 = arr_mul(h, f(t, y));
        std::array<double, DIM> k2 = arr_mul(h, f(t + h/2.0, arr_sum(y, arr_mul(0.5, k1))));
        std::array<double, DIM> k3 = arr_mul(h, f(t + h/2.0, arr_sum(y, arr_mul(0.5, k2))));
        std::array<double, DIM> k4 = arr_mul(h, f(t + h, arr_sum(y, k3)));

        std::array<double, DIM> dy;
        for (int j = 0; j < DIM; j++)
            dy[j] = (k1[j] + 2*k2[j] + 2*k3[j] + k4[j]) / 6.0;

        y = arr_sum(y, dy);
        
        t = t + h;
    }
}

int main(){

    int N3 = 1000;
    double t0 = 0.0;
    std::array<double, DIM> y0 = {9100.0, 900.0, 0.0}; //S(0), I(0), R(0)

    double h = (tf - t0) / (N3 - 1);

    std::ofstream file_euler("sir_euler.dat");
    std::ofstream file_rk4("sir_rk4.dat");

    euler(N3, t0, y0, h, file_euler);
    runge_kutta_4(N3, t0, y0, h, file_rk4);

    file_euler.close();
    file_rk4.close();

    std::cout << "Datos guardados en sir_euler.dat y sir_rk4.dat\n";

    return 0;
}