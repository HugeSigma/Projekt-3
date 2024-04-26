#include <pybind11/pybind11.h>
#include <pybind11/stl.h> //konwersja wektora na listy
#include <vector>
#include <matplot/matplot.h>
#include <cmath>

namespace mp = matplot;
namespace py = pybind11;

int add(int i, int j) {
    return i + j;
}
int subtract(int i, int j) {
    return i - j;
}
int multiply(int i, int j) {
    return i * j;
}
int divide(int i, int j) {
    return i/ j;
}
std::vector<double> funkcja()
{
    std::vector<double> x = mp::linspace(0, 10, 100);
    std::vector<double> y = mp::transform(x, [](auto x) { return sin(x); });
    mp::plot(x, y);
    mp::show();
    return y;
}

PYBIND11_MODULE(cmake_example, m) {
    m.def("add", &add);
    m.def("multiply", &multiply);
    m.def("divide", &divide);
    m.def("subtract", &subtract);
    m.def("funkcja", &funkcja);
}
