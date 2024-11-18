#include <iostream>
#include <ctime>
#include <vector>
#include <fftw3.h>

using namespace std;

// Function to perform FFT using FFTW
void performFFT(int signalSize) {
    // Allocate memory for complex input and output signals
    vector<fftw_complex> in(signalSize);
    vector<fftw_complex> out(signalSize);

    // Create FFTW plan
    fftw_plan plan_forward = fftw_plan_dft_1d(signalSize, in.data(), out.data(), FFTW_FORWARD, FFTW_ESTIMATE);

    // Generate random input signal
    for (int i = 0; i < signalSize; ++i) {
        in[i][0] = rand() / (double)RAND_MAX;
        in[i][1] = rand() / (double)RAND_MAX;
    }

    // Execute FFT
    fftw_execute(plan_forward);

    // Destroy plan
    fftw_destroy_plan(plan_forward);
}

// Scalability testing function
void testScalability() {
    const int numTestScenarios = 10;
    const int minSignalSize = 1024;
    const int maxSignalSize = 1 << 20;  // 1 million samples
    const int signalSizeIncrement = (maxSignalSize - minSignalSize) / numTestScenarios + 1;

    vector<int> signalSizes;
    vector<double> executionTimes;

    for (int i = 0; i < numTestScenarios; ++i) {
        int signalSize = minSignalSize + i * signalSizeIncrement;
        signalSizes.push_back(signalSize);

        // Measure execution time for the FFT operation
        double executionTime = 0.0;
        for (int j = 0; j < 3; ++j) {  // Average over 3 runs
            clock_t start = clock();
            performFFT(signalSize);
            clock_t end = clock();
            executionTime += static_cast<double>(end - start) / CLOCKS_PER_SEC;
        }
        executionTimes.push_back(executionTime / 3);

        cout << "Signal size: " << signalSize << ", Execution time: " << executionTime << " seconds" << endl;
    }

    // Display results
    cout << "\nScalability Test Results:" << endl;
    for (size_t i = 0; i < signalSizes.size(); ++i) {
        cout << "Signal size: " << signalSizes[i] << ", Execution time: " << executionTimes[i] << " seconds" << endl;
    }
}

int main() {
    testScalability();
    return 0;
}