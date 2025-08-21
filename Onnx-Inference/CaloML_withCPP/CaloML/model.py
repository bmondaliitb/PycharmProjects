"""
This is a DNN with a Gaussian Mixture (GM) as likelihood.

Loss function: negative log-likelihood assuming that the uncertainties (sigmas from the 
Gaussians) depend on the input features, i.e. an heteroscedastic loss.
Outputs: parameters of the gaussians that form the GM, which are the mean, sigma and alpha 
(weight). We have a total of 3*N_mix, where N_mix is the numer of mixtures of the GM (hyperparameter).
Prediction: mode of the GM.
Uncertainty: resulting uncertainty of the Gaussian mixture. It is interpreted as a systematic uncertainty.

Author: Isabel Sainz (based on the work of Lorenz Vogel)

"""


# standard Python imports
import numpy as np
import os, sys
import argparse

# PyTorch imports
import torch
from torch import nn
from torch.utils.data import Dataset
from torch.utils.data import DataLoader
from torch.utils.data import TensorDataset


def log_likelihood(x, mus, log_sigma2s, alphas):
    """
    Logarithm of the probability density of a Gaussian mixture distribution (log-likelihood).
    This construction uses the log-sum-exp method from PyTorch which is numerically
    more stable then just computing: log(prob) = log(sum_i alpha_i*Gauss(mu_i, sigma_i))
    """

    # calculate one-dimensional negative log-Gaussians
    # neg_log_gauss = -log(Gauss(mu_i, sigma_i))
    # neg_log_gauss : shape = (num_monte, batch_size, x_sample, 3)
    neg_log_gauss  = torch.pow(mus-x, 2.0)/(2.0*torch.exp(log_sigma2s)) + 0.5*log_sigma2s
    neg_log_gauss += 0.5*np.log(2.0*np.pi) # constant

    # log_prob_components = -neg_log_gauss_i + log(alpha_i)
    #                     = log(Gauss(mu_i, sigma_i)) + log(alpha_i)
    # log_prob_components : shape = (num_monte, batch_size, x_sample, 3)
    log_likelihood_components = -neg_log_gauss + torch.log(alphas)
    
    # log_prob = log(sum_i exp(log_prob_components_i))
    #          = log(sum_i exp(log(Gauss(mu_i, sigma_i)) + log(alpha_i)))
    # log_prob : shape = (num_monte, batch_size, x_sample)
    log_likelihood = torch.logsumexp(log_likelihood_components, dim=-1)

    return log_likelihood

    
def modes(_mus, _sigma2s, _alphas):
    alphas  = _alphas[None,:,:]
    sigma2s = _sigma2s[None,:,:]
    mus     = _mus[None,:,:]
    
    # select range to check for maxima
    x_min = 0.9*torch.min(mus, dim=-1)[0]#.cpu().detach().numpy()
    x_max = 1.1*torch.max(mus, dim=-1)[0]#.cpu().detach().numpy()
    x_min = torch.min(x_min, dim=0)[0].cpu().detach().numpy()
    x_max = torch.max(x_max, dim=0)[0].cpu().detach().numpy()
    
    # create array of ranges to check for maxima
    x_test = torch.from_numpy(np.linspace(x_min, x_max, num=1000)).to('cpu')
    x_test = torch.stack([x_test])
    
    # x_test  : shape = (x_sample, num_monte, batch_size)
    # mus     : shape = (num_monte, batch_size, num_mixtures)
    # sigma2s : shape = (num_monte, batch_size, num_mixtures)
    # alphas  : shape = (num_monte, batch_size, num_mixtures)

    # reshape parameters for likelihood computations
    x_test_reshaped  = torch.permute(x_test,  dims=(0, 2, 1))[:,:,:,None]
    mus_reshaped     = torch.permute(mus,     dims=(0, 1, 2))[:,:,None,:]
    sigma2s_reshaped = torch.permute(sigma2s, dims=(0, 1, 2))[:,:,None,:]
    alphas_reshaped  = torch.permute(alphas,  dims=(0, 1, 2))[:,:,None,:]

    # compute negative log-likelihood (NLL)
    neg_log_likelihood = -log_likelihood(x_test_reshaped, mus_reshaped, torch.log(sigma2s_reshaped), alphas_reshaped)
    neg_log_likelihood = torch.mean(neg_log_likelihood, dim=0) # mean over num_monte

    # choose x-point with largest likelihood value (= smallest NLL value)
    idxs  = torch.argmin(neg_log_likelihood, dim=-1, keepdim=True)
    modes = torch.gather(torch.squeeze(x_test_reshaped, dim=-1)[0,:,:], -1, idxs)

    # shape = (batch_size)
    predictions = torch.squeeze(modes, dim=-1)

    return predictions