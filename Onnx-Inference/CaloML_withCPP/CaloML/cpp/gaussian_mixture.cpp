// gaussian_mixture.cpp

#include "gaussian_mixture.h"
#include <cmath>
#include <vector>
#include <numeric>
#include <algorithm>
#include <limits>

// Helper function for logsumexp
double log_sum_exp(const std::vector<double>& vec) {
    if (vec.empty()) {
        return -std::numeric_limits<double>::infinity();
    }
    double max_val = *std::max_element(vec.begin(), vec.end());
    double sum = 0.0;
    for (double val : vec) {
        sum += std::exp(val - max_val);
    }
    return max_val + std::log(sum);
}

double log_likelihood(double x, const std::vector<double>& mus, const std::vector<double>& log_sigma2s, const std::vector<double>& alphas) {
    // Ensure vectors have the correct size
    if (mus.size() != 3 || log_sigma2s.size() != 3 || alphas.size() != 3) {
        // Handle error appropriately in a real application
        return -1.0; 
    }

    std::vector<double> log_likelihood_components(3);

    for (int i = 0; i < 3; ++i) {
        // Calculate one-dimensional negative log-Gaussian
        double neg_log_gauss = std::pow(mus[i] - x, 2.0) / (2.0 * std::exp(log_sigma2s[i])) + 0.5 * log_sigma2s[i];
        neg_log_gauss += 0.5 * std::log(2.0 * M_PI); // M_PI is a common constant for pi

        // log_prob_components = -neg_log_gauss_i + log(alpha_i)
        log_likelihood_components[i] = -neg_log_gauss + std::log(alphas[i]);
    }

    // log_prob = log(sum_i exp(log_prob_components_i))
    return log_sum_exp(log_likelihood_components);
}


double modes(const std::vector<double>& mus, const std::vector<double>& sigma2s, const std::vector<double>& alphas) {
    // Ensure vectors have the correct size
    if (mus.size() != 3 || sigma2s.size() != 3 || alphas.size() != 3) {
        // Handle error appropriately in a real application
        return -1.0;
    }

    // Select range to check for maxima
    double x_min = 0.9 * (*std::min_element(mus.begin(), mus.end()));
    double x_max = 1.1 * (*std::max_element(mus.begin(), mus.end()));

    // Create array of ranges to check for maxima
    const int num_points = 1000;
    std::vector<double> x_test(num_points);
    double step = (x_max - x_min) / (num_points - 1);
    for (int i = 0; i < num_points; ++i) {
        x_test[i] = x_min + i * step;
    }

    // Pre-calculate log of sigma2s
    std::vector<double> log_sigma2s(3);
    for(size_t i = 0; i < sigma2s.size(); ++i) {
        log_sigma2s[i] = std::log(sigma2s[i]);
    }

    double min_neg_log_likelihood = std::numeric_limits<double>::infinity();
    double mode = 0.0;

    // Find the x-point with the largest likelihood value
    for (double x : x_test) {
        double nll = -log_likelihood(x, mus, log_sigma2s, alphas);
        if (nll < min_neg_log_likelihood) {
            min_neg_log_likelihood = nll;
            mode = x;
        }
    }

    return mode;
}
