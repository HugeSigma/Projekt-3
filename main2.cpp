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