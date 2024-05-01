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

#include <opencv2/opencv.hpp>

int Blurrowanie_Zdjec() {
    //ładujesz zdjecia jak plik
    cv::Mat zdjecie = cv::imread("nazwa_zdjecia.jpg"); //Mat to jest macierz zdjecia zamaist vectora lub tablicy

    if (image.empty())
    {
        std::cout << "Dupa nie zdjecie." << std::endl;
        return -1;
    }

    // Funkcja co robi blurr 
    cv::Mat zmienione_zdjecie;
    cv::GaussianBlur(image, zmienione_zdjecie, cv::Size(5, 5), 0); // Kernel i sigma podajemy 5,5 0 jest standardem i jest podane na stronie docs.opencv

    // pokazuje oba zdjecia
    cv::imshow("Zdjecie Przed", zdjecie);
    cv::imshow("Zdjecie Po", zmienione_zdjecie);
    cv::waitKey(0);

    return 0;
}