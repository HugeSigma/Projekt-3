#include <pybind11/pybind11.h>
#include <pybind11/stl.h> //konwersja wektora na listy
#include <vector>
#include <matplot/matplot.h>
#include <cmath>
#include <AudioFile.h>

namespace mp = matplot;
namespace py = pybind11;

const int f_probkowania = 48;

std::vector<double> sinus(double f, double time) //f - czestotliwosc
{
    std::vector<double> x = mp::linspace(0, time, time*f_probkowania);
    std::vector<double> y = mp::transform(x, [&](auto x) { return sin(f*x); });
    mp::plot(x, y);
    mp::xlabel("t_{s}");
    mp::ylabel("value");
    mp::show();
    return y;
}
std::vector<double> cosinus(double f, double time) //f - czestotliwosc
{
    std::vector<double> x = mp::linspace(0, time, time*f_probkowania);
    std::vector<double> y = mp::transform(x, [&](auto x) { return cos(f*x); });
    mp::plot(x, y);
    mp::xlabel("t_{s}");
    mp::ylabel("value");
    mp::show();
    return y;
}
std::vector<double> pila(double f, double time, double max_value = 1) //f - czestotliwosc
{
    std::vector<double> x = mp::linspace(0, time, time * f_probkowania);
    std::vector<double> y = mp::transform(x, [&](auto x) { return ((x*f+0.5 - floor(x*f+0.5))*2*max_value - max_value); });
    mp::plot(x, y);
    mp::xlabel("t_{s}");
    mp::ylabel("value");
    mp::show();
    return y;
}

std::vector<double> prostokatny(double f, double time, double max_value = 1) //f - czestotliwosc
{
    std::vector<double> x = mp::linspace(0, time, time * f_probkowania);
    std::vector<double> y = mp::transform(x, [&](auto x) { return (((x * f + 0.5 - floor(x * f + 0.5)) * 2 * max_value - max_value) > 0 ? max_value : 0 - max_value); });
    mp::plot(x, y);
    mp::xlabel("t_{s}");
    mp::ylabel("value");
    mp::show();
    return y;
}

std::vector<double> convolution(std::vector<double>& funkcja, std::vector<double>& kernel)
{
    std::vector<double> Wygladzony(funkcja.size());
    double time = funkcja.size();

    for (int i = 0; i < funkcja.size(); ++i)
    {
        double sum = 0.0;
        for (int j = kernel.size(); j > 0; --j)
        {
            if (i >= j) sum += funkcja[i - j] * kernel[j];
        }
        Wygladzony[i] = sum;
    }

    std::vector<double> x = mp::linspace(0, time, time * f_probkowania);

    mp::plot(x, Wygladzony);
    mp::show();
    return Wygladzony;
}


PYBIND11_MODULE(cmake_example, m) {
    m.def("sinus", &sinus);
    m.def("cosinus", &cosinus);
    m.def("prostokatny", &prostokatny);
    m.def("pila", &pila);
    m.def("convolution", &convolution);
}
