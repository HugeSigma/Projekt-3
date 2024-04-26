#include <pybind11/pybind11.h>
#include <pybind11/stl.h> //konwersja wektora na listy
#include <vector>
#include <matplot/matplot.h>
#include <cmath>

namespace mp = matplot;
namespace py = pybind11;

const int precision = 10;

std::vector<double> sinus(double f, double time) //f - czestotliwosc
{
    std::vector<double> x = mp::linspace(0, time, time*precision);
    std::vector<double> y = mp::transform(x, [&](auto x) { return sin(f*x); });
    mp::plot(x, y);
    mp::xlabel("t_{s}");
    mp::ylabel("value");
    mp::show();
    return y;
}
std::vector<double> cosinus(double f, double time) //f - czestotliwosc
{
    std::vector<double> x = mp::linspace(0, time, time*precision);
    std::vector<double> y = mp::transform(x, [&](auto x) { return cos(f*x); });
    mp::plot(x, y);
    mp::xlabel("t_{s}");
    mp::ylabel("value");
    mp::show();
    return y;
}
std::vector<double> pila(double f, double time, double max_value = 1) //f - czestotliwosc
{
    std::vector<double> x = mp::linspace(0, time, time * precision);
    std::vector<double> y = mp::transform(x, [&](auto x) { return max_value*(x - floor(x)); });
    mp::plot(x, y);
    mp::xlabel("t_{s}");
    mp::ylabel("value");
    mp::show();
    return y;
}

std::vector<double> prostokatny(double f, double time, double max_value = 1) //f - czestotliwosc
{
    std::vector<double> x = mp::linspace(0, time, time * precision);
    std::vector<double> y = mp::transform(x, [&](auto x) { return ((x - floor(x)) > 0 ? max_value : 0 - max_value); });
    mp::plot(x, y);
    mp::xlabel("t_{s}");
    mp::ylabel("value");
    mp::show();
    return y;
}


PYBIND11_MODULE(cmake_example, m) {
    m.def("sinus", &sinus);
    m.def("cosinus", &cosinus);
    m.def("prostokatny", &prostokatny);
    m.def("pila", &pila);
}
