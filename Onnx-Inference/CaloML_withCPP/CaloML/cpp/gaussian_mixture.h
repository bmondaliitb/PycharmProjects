// gaussian_mixture.h

#ifndef GAUSSIAN_MIXTURE_H
#define GAUSSIAN_MIXTURE_H

#include <vector>

/**
 * @brief Calculates the logarithm of the probability density of a Gaussian mixture distribution.
 *
 * This function uses a numerically stable log-sum-exp approach.
 *
 * @param x The input value.
 * @param mus A vector of mean values for each Gaussian component (length 3).
 * @param log_sigma2s A vector of the logarithm of the variance for each component (length 3).
 * @param alphas A vector of the mixture weights for each component (length 3).
 * @return The log-likelihood of x.
 */
double log_likelihood(double x, const std::vector<double>& mus, const std::vector<double>& log_sigma2s, const std::vector<double>& alphas);

/**
 * @brief Finds the modes (peaks) of the Gaussian mixture distribution.
 *
 * It does this by finding the maximum of the likelihood function over a specified range.
 *
 * @param mus A vector of mean values for each Gaussian component (length 3).
 * @param sigma2s A vector of the variance for each component (length 3).
 * @param alphas A vector of the mixture weights for each component (length 3).
 * @return The predicted mode of the distribution.
 */
double modes(const std::vector<double>& mus, const std::vector<double>& sigma2s, const std::vector<double>& alphas);

#endif // GAUSSIAN_MIXTURE_H
