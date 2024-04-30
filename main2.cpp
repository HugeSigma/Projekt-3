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

std::vector<double> krzywa_gaussa(double sigma, int czas)
{
    std::vector<double> kernel(czas);
    double sum = 0.0;

    for (int i = 0; i < czas; ++i)
    {
        int x = i - czas / 2;
        kernel[i] = exp(-(x * x) / (2 * sigma * sigma)) / (sqrt(2 * M_PI) * sigma);
        sum += kernel[i];
    }
    for (int i = 0; i < czas; ++i)
    {
        kernel[i] /= sum;
    }

    return kernel;
}