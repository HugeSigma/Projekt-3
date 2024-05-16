#include <pybind11/pybind11.h>
#include <pybind11/stl.h> //konwersja wektora na listy
#include <vector>
#include <matplot/matplot.h>
#include <cmath>
#include <cstring>
#include <AudioFile.h>

namespace mp = matplot;
namespace py = pybind11;

const int f_probkowania = 48;
const double PI = 3.14159265359;

std::vector<double> sinus(double f, double time) //f - czestotliwosc
{
    std::vector<double> x = mp::linspace(0, time, time*f_probkowania);
    std::vector<double> y = mp::transform(x, [&](auto x) { return sin(f*x*2*PI); });
    mp::plot(x, y);
    mp::xlabel("t_{s}");
    mp::ylabel("value");
    mp::show();
    return y;
}
std::vector<double> cosinus(double f, double time) //f - czestotliwosc
{
    std::vector<double> x = mp::linspace(0, time, time*f_probkowania);
    std::vector<double> y = mp::transform(x, [&](auto x) { return cos(f*x*2*PI); });
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

std::vector<double> krzywa_gaussa(double sigma, double m, int time) //m to mediana
{
    std::vector<double> x = mp::linspace(0, time, time * f_probkowania);
    std::vector<double> kernel = mp::transform(x, [&](auto x) { return ((1 / (sigma * sqrt(2 * PI))) * exp(-pow((x-m), 2) / (2 * sigma * sigma))); });
    mp::plot(x, kernel);
    mp::show();
   
    return kernel;
}

std::vector<double> wzmocnienie_dzwieku(std::string nazwa, double k, std::string zapis)
{
    AudioFile<double> audioFile;
    audioFile.load(nazwa);

    std::vector<double> y;
    int channel = 0;
    int n = audioFile.getNumSamplesPerChannel();

    for (int i = 0; i < n; i++)
    {
        audioFile.samples[channel][i] *= k;
        y.push_back(audioFile.samples[channel][i]);
    }

    audioFile.save(zapis);

    mp::plot(y);
    mp::show();

    return y;

}

std::vector<double> wzmocnienie(std::vector<double>& funkcja, double k)
{
    for (int i = 0; i < funkcja.size(); i++) funkcja[i] *= k;

    mp::plot(funkcja);
    mp::show();

    return funkcja;
}

std::vector<double> autokorelacja(std::vector<double>& funkcja)
{
    std::vector<double> funkcja2 = funkcja;

    std::vector<double> skorelowany(funkcja.size()+funkcja2.size()-1);

    for (int i = 0; i < funkcja.size(); ++i)
    {
        for (int j = funkcja2.size()-1; j > 0; --j)
        {
            skorelowany[i+(funkcja2.size()-j-1)] += funkcja[i] * funkcja2[j];
        }
    }

    std::vector<double> x = mp::linspace(0, skorelowany.size(), skorelowany.size() * f_probkowania);

    mp::plot(x, skorelowany);
    mp::show();

    return skorelowany;
}

std::vector<double> korelacja(std::vector<double>& funkcja, std::vector<double>& funkcja2)
{
    std::vector<double> skorelowany(funkcja.size() + funkcja2.size() - 1);

    for (int i = 0; i < funkcja.size(); ++i)
    {
        for (int j = funkcja2.size() - 1; j > 0; --j)
        {
            skorelowany[i + (funkcja2.size() - j - 1)] += funkcja[i] * funkcja2[j];
        }
    }

    std::vector<double> x = mp::linspace(0, skorelowany.size(), skorelowany.size() * f_probkowania);

    mp::plot(x, skorelowany);
    mp::show();

    return skorelowany;
}

std::vector<double> wykres_dzwieku(const std::string nazwa)
{
    AudioFile<double> audioFile;
    audioFile.load(nazwa);
    audioFile.printSummary();

    std::vector<double> y;

    for (const auto& sampel : audioFile.samples[0])
    {
        double sample = sampel;
        y.push_back(sample);
    }

    mp::plot(y);
    mp::show();

    return y;
}

PYBIND11_MODULE(cmake_example, m) {
    m.def("sinus", &sinus);
    m.def("cosinus", &cosinus);
    m.def("prostokatny", &prostokatny);
    m.def("pila", &pila);
    m.def("convolution", &convolution);
    m.def("krzywa_gaussa", &krzywa_gaussa);
    m.def("wzmocnienie", &wzmocnienie);
    m.def("wzmocnienie_dzwieku", &wzmocnienie_dzwieku);
    m.def("autokorelacja", &autokorelacja);
    m.def("korelacja", &korelacja);
    m.def("wykres_dzwieku", &wykres_dzwieku);
}
