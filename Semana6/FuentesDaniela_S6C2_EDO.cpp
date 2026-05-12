#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <array>

const int DIM = 1; //Dimension del sistema, en este caso es 1

double tf = 2.0; //Tiempo final

// dy/dt = -y(t)
std::array<double, DIM> f(double t, std::array<double, DIM> y){
    return {-y[0]};
}

double f_exacta(double t){
    return std::exp(-t);
}

// Como no hay una funcion para las sumas, aca realizaso una para la suma de dos arreglos
std::array<double, DIM> arr_sum(std::array<double, DIM> a, std::array<double, DIM> b){
    std::array<double, DIM> result;
    for (int i = 0; i < DIM; i++) result[i] = a[i] + b[i];
    return result;
}

// Lo mismo pero para multiplicacion con escalares
std::array<double, DIM> arr_mul(double s, std::array<double, DIM> a){
    std::array<double, DIM> result;
    for (int i = 0; i < DIM; i++) result[i] = s * a[i];
    return result;
}

void euler(int N, double t0, std::array<double, DIM> y0, double h, std::ofstream &file){

    double t = t0;
    std::array<double, DIM> y = y0;

    for (int i = 0; i < N; i++){

        double y_exacta = f_exacta(t);
        double error = std::fabs(y[0] - y_exacta);

        file << t << " " << y[0] << " " << y_exacta << " " << error << "\n";

        y = arr_sum(y, arr_mul(h, f(t, y)));
        t = t + h;
    }
}

void runge_kutta_4(int N, double t0, std::array<double, DIM> y0, double h, std::ofstream &file){

    double t = t0;
    std::array<double, DIM> y = y0;

    for (int i = 0; i < N; i++){

        double y_exacta = f_exacta(t);
        double error = std::fabs(y[0] - y_exacta);

        std::array<double, DIM> k1 = arr_mul(h, f(t, y));
        std::array<double, DIM> k2 = arr_mul(h, f(t + h/2.0, arr_sum(y, arr_mul(0.5, k1))));
        std::array<double, DIM> k3 = arr_mul(h, f(t + h/2.0, arr_sum(y, arr_mul(0.5, k2))));
        std::array<double, DIM> k4 = arr_mul(h, f(t + h, arr_sum(y, k3)));

        file << t << " " << y[0] << " " << y_exacta << " " << error << "\n";

        std::array<double, DIM> dy;
        for (int j = 0; j < DIM; j++)
            dy[j] = (k1[j] + 2*k2[j] + 2*k3[j] + k4[j]) / 6.0;

        y = arr_sum(y, dy);
        
        t = t + h;
    }
}

int main(){

    double t0 = 0.0;
    std::array<double, DIM> y0 = {1.0};

    int N1 = 200; // numero de puntos (h pequeño)
    int N2 = 100; // numero de puntos (h grande)

    double h1 = (tf - t0) / (N1 - 1);
    double h2 = (tf - t0) / (N2 - 1);

    std::ofstream file1("euler_h1.dat");
    std::ofstream file2("euler_h2.dat");
    std::ofstream file3("rk4_h1.dat");
    std::ofstream file4("rk4_h2.dat");

    euler(N1, t0, y0, h1, file1);
    euler(N2, t0, y0, h2, file2);

    runge_kutta_4(N1, t0, y0, h1, file3);
    runge_kutta_4(N2, t0, y0, h2, file4);

    file1.close();
    file2.close();
    file3.close();
    file4.close();

    std::cout << "Datos guardados en euler_h1.dat, euler_h2.dat, rk4_h1.dat, rk4_h2.dat\n";

    return 0;
}