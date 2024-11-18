
#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>

// Function to perform Discrete Fourier Transform (DFT)
void dft(const std::vector<double>& x, std::vector<double>& X) {
    const size_t N = x.size();

    for (size_t k = 0; k < N; ++k) {
        double sum_re = 0.0;
        double sum_im = 0.0;

        for (size_t n = 0; n < N; ++n) {
            const double angle = -2.0 * M_PI * k * n / static_cast<double>(N);
            const double cos_term = std::cos(angle);
            const double sin_term = std::sin(angle);
            sum_re += x[n] * cos_term;
            sum_im += x[n] * sin_term;
        }

        X[k] = sum_re;
        X[N + k] = sum_im;
    }
}

// Function to perform scalability testing of DFT
void scalabilityTest() {
    const std::vector<size_t> signalSizes = { 1024, 2048, 4096, 8192, 16384 };
    std::cout << "Scalability Testing of DFT:\n";
    std::cout << "Signal Size | Execution Time (ms)\n";
    std::cout << "----------- | --------------------\n";

    for (const size_t signalSize : signalSizes) {
        std::vector<double> x(signalSize);
        // Generate random input signal
        for (size_t i = 0; i < signalSize; ++i) {
            x[i] = std::rand() / static_cast<double>(RAND_MAX);
        }

        std::vector<double> X(signalSize * 2);

        clock_t start = clock();

        // Perform DFT
        dft(x, X);

        clock_t end = clock();
        double executionTime = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0;

        std::cout << signalSize << "            | " << executionTime << "\n";
    }
}
 
int main() {
    scalabilityTest();
    return 0;
}
 