// main.cpp

#include <iostream>
#include <vector>
#include "gaussian_mixture.h"

int main() {
    // --- Test Case 1 ---
    // Define the parameters for the Gaussian mixture model
    // These values suggest peaks around 5 and 15.
    std::vector<double> mus1 = {5.0, 15.0, 10.0};
    std::vector<double> sigma2s1 = {1.5, 1.0, 5.0};
    std::vector<double> alphas1 = {0.45, 0.45, 0.1}; // Strong weights on the first two components

    // Calculate the mode
    double predicted_mode1 = modes(mus1, sigma2s1, alphas1);

    // Print the result
    std::cout << "--- Test Case 1 ---" << std::endl;
    std::cout << "mus: {5.0, 15.0, 10.0}" << std::endl;
    std::cout << "sigma2s: {1.5, 1.0, 5.0}" << std::endl;
    std::cout << "alphas: {0.45, 0.45, 0.1}" << std::endl;
    std::cout << "Predicted mode: " << predicted_mode1 << std::endl;
    std::cout << std::endl;


    // --- Test Case 2 ---
    // A second test case where the mode should be around 20
    std::vector<double> mus2 = {2.0, 8.0, 20.0};
    std::vector<double> sigma2s2 = {2.0, 3.0, 0.5}; // Very narrow peak at 20
    std::vector<double> alphas2 = {0.1, 0.2, 0.7}; // Strongest weight on the third component

    // Calculate the mode
    double predicted_mode2 = modes(mus2, sigma2s2, alphas2);

    // Print the result
    std::cout << "--- Test Case 2 ---" << std::endl;
    std::cout << "mus: {2.0, 8.0, 20.0}" << std::endl;
    std::cout << "sigma2s: {2.0, 3.0, 0.5}" << std::endl;
    std::cout << "alphas: {0.1, 0.2, 0.7}" << std::endl;
    std::cout << "Predicted Mode: " << predicted_mode2 << std::endl;


    return 0;
}
