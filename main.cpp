#include <iostream>
#include "Polynomial.h"

struct poly_t;

#ifndef MARMOSET_TESTING
int main();
#endif

#ifndef MARMOSET_TESTING
int main() {

    double r = 2;

    poly_t poly_1 {nullptr, 0};
    double const init_coeffs1[] = {2,7,6}; //{2,1};//;
    unsigned int const init_degree1 = 2;
    poly_t poly_2 {nullptr, 0};
    double const init_coeffs2[] = {3,2};//{5, 7, 2, 13, 1};
    unsigned int const init_degree2 = 1;

    init_poly(poly_1, init_coeffs1, init_degree1);
    init_poly(poly_2, init_coeffs2, init_degree2);

    //std::cout << std::endl;
    //std::cout << "d " << poly_divide(poly_1, -1) << std::endl;

    poly_diff(poly_1);
    for (unsigned int i = 0; i <= poly_1.degree; i++){
        std::cout << poly_1.a_coeffs[i] << std::endl;
    }

    destroy_poly(poly_1);
    return 0;
}
#endif

void init_poly( poly_t &p, double const init_coeffs[], unsigned int const init_degree){
    delete[] p.a_coeffs;
    p.degree = init_degree;
    p.a_coeffs = new double[init_degree + 1];
    for (unsigned int i = 0; i < (init_degree + 1); i++){
        p.a_coeffs[i] = init_coeffs[i];
    }

}

void destroy_poly(poly_t &p){
    delete[] p.a_coeffs;
    p.degree = 0;
    p.a_coeffs = nullptr;
}

unsigned int poly_degree(poly_t const &p){
    int x;
    if (p.a_coeffs == nullptr){
        throw 0;
    }else {
        return p.degree;
    }

}

double poly_coeff(poly_t const &p, unsigned int n){
    if (p.a_coeffs == nullptr){
        throw 0;
    }else {
        return p.a_coeffs[n];
    }
}

double poly_val(poly_t const &p, double const x){
    double total = 0;
    if (p.a_coeffs == nullptr){
        throw 0;
    }else {
        for(unsigned int i = p.degree + 1; i > 0; i--){
            total = total + p.a_coeffs[i - 1];
            if (i != 1){
                total = total*x;
            }
        }
    }
    return total;
}

void poly_add(poly_t &p, poly_t const &q){
    int d;
    if (p.a_coeffs == nullptr||q.a_coeffs == nullptr){
        throw 0;
    }
    if (p.degree > q.degree){
        d = p.degree;
    }else {
        d = q.degree;
    }
    if(p.degree == q.degree){
        for (int i = d; i >= 0; i--){
            if (p.a_coeffs[i] + q.a_coeffs[i] == 0 && i > 0){
                d --;
            }
        }

    }
    double *new_coeff = new double [d + 1]{0};
    for(int i = 0; i <= p.degree; i++){
        new_coeff[i] = p.a_coeffs[i];
    }
    for(int i = 0; i <= q.degree; i++){
        new_coeff[i] += q.a_coeffs[i];
    }
    delete[] p.a_coeffs;
    p.a_coeffs = new_coeff;
    p.degree = d;
    new_coeff = nullptr;

}

void poly_subtract(poly_t &p, poly_t const &q){ //CHECK AGAIN LATER YOU LAZY ASS BITCH
    int d;
    if (p.a_coeffs == nullptr||q.a_coeffs == nullptr){
        throw 0;
    }
    if (p.degree > q.degree){
        d = p.degree;
    }else {
        d = q.degree;
    }
    if(p.degree == q.degree){
        for (int i = d; i >= 0; i--){
            if (p.a_coeffs[i] - q.a_coeffs[i] == 0 && i > 0){
                d --;
            }
        }

    }
    double *new_coeff = new double [d + 1]{0};
    for(int i = 0; i <= p.degree; i++){
        new_coeff[i] = p.a_coeffs[i];
    }
    for(int i = 0; i <= q.degree; i++){
        new_coeff[i] -= q.a_coeffs[i];
    }
    delete[] p.a_coeffs;
    p.a_coeffs = new_coeff;
    p.degree = d;
    new_coeff = nullptr;

}

void poly_multiply(poly_t &p, poly_t const &q){
    if (p.a_coeffs == nullptr||q.a_coeffs == nullptr){
        throw 0;
    }else {
        double *new_coeff {new double[p.degree + q.degree + 1]{}};
        for (unsigned int i = 0; i <= p.degree; i++){
            for(unsigned int j = 0; j <= q.degree; j++){
                new_coeff[i + j] = new_coeff[i + j] + (p.a_coeffs[i]*q.a_coeffs[j]);
            }
        }
        delete[] p.a_coeffs;
        p.a_coeffs = new_coeff;
        p.degree += q.degree;
        new_coeff = nullptr;
    }
}

double poly_divide(poly_t &p, double r){
    double sum = 0;
    if (p.a_coeffs == nullptr){
        throw 0;
    }else {
        if (p.degree == 0){
            sum = p.a_coeffs[0];
            return sum;
        }else {
            double *new_coeff = {new double[p.degree]{}};
            for (int i = p.degree-1; i >= 0; i--){
                sum += p.a_coeffs[i+1];
                new_coeff[i] = sum;
                sum *= r;
            }
            sum += p.a_coeffs[0];
            delete[] p.a_coeffs;
            p.a_coeffs = new_coeff;
            new_coeff = nullptr;
            p.degree--;
            return sum;
        }

    }
}


void poly_diff(poly_t &p){
    if (p.a_coeffs == nullptr){
        throw 0;
    }else {
        double *new_coeff = new double[p.degree];
        for (unsigned int i = p.degree; i > 0; i--){
            //std::cout << i << std::endl;
            new_coeff[i-1] = p.a_coeffs[i]*i;
            //std::cout << new_coeff[i-1] << " ";
            //std::cout << " x " << std::endl;
        }
        delete[] p.a_coeffs;
        p.a_coeffs = new_coeff;
        p.degree--;
        new_coeff = nullptr;
    }
}
double poly_approx_int(poly_t const &p, double a, double b, unsigned int n){
    double height = (b - a)/n;
    double area = 0;
    if (p.a_coeffs == nullptr){
        throw 0;
    }else {
        area = area + poly_val(p, (a + 0*height));
        for (unsigned int i = 1; i < n; i++){
            area = area + 2*poly_val(p, (a + i*height));
        }
        area = area + poly_val(p, (a + n*height));
        area = area*(height/2);
    }
    return area;
}
