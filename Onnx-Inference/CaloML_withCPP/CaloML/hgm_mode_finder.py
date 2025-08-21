# hgm_mode_finder.py
import numpy as np
import os
from scipy.optimize import fsolve
from scipy.stats import norm

def find_gmm_modes(alphas: np.ndarray, mus: np.ndarray, sigmas: np.ndarray, initial_guesses: np.ndarray = None) -> np.ndarray:
    """
    Finds all modes (local maxima) of a 1D Gaussian Mixture Model (GMM).

    The modes are found by locating the roots of the first derivative of the GMM's
    probability density function (PDF) using a numerical solver. Only roots that
    correspond to local maxima (i.e., where the second derivative is negative)
    are returned.

    Args:
        alphas (np.ndarray): Mixture weights for the GMM components. Shape (n_components,).
        mus (np.ndarray): Means for the GMM components. Shape (n_components,).
        sigmas (np.ndarray): Standard deviations for the GMM components. Shape (n_components,).
        initial_guesses (np.ndarray, optional): Initial points for the root-finding
            algorithm. If None, the component means (`mus`) are used as initial guesses.

    Returns:
        np.ndarray: A sorted array containing the x-values of the found modes.
    """
    # The first derivative of the GMM PDF. A mode exists where this is zero.
    def gmm_pdf_derivative(x: np.ndarray) -> np.ndarray:
        # The derivative of a gaussian N(x|m,s) is N(x|m,s) * -(x-m)/s^2
        # We sum this over all components, weighted by alpha.
        # Reshaping for broadcasting allows for efficient computation
        x_r = np.asarray(x).reshape(-1, 1) # (n_guesses, 1)
        a_r = alphas.reshape(1, -1) # (1, n_components)
        m_r = mus.reshape(1, -1)
        s_r = sigmas.reshape(1, -1)
        
        pdf_vals = norm.pdf(x_r, loc=m_r, scale=s_r)
        derivative_term = -(x_r - m_r) / (s_r**2)
        return np.sum(a_r * pdf_vals * derivative_term, axis=1)

    # The second derivative of the GMM PDF, used to verify a maximum.
    def gmm_pdf_second_derivative(x: np.ndarray) -> np.ndarray:
        # The second derivative of a gaussian N(x|m,s) is N(x|m,s) * ((x-m)^2/s^4 - 1/s^2)
        x_r = np.asarray(x).reshape(-1, 1)
        a_r = alphas.reshape(1, -1)
        m_r = mus.reshape(1, -1)
        s_r = sigmas.reshape(1, -1)

        pdf_vals = norm.pdf(x_r, loc=m_r, scale=s_r)
        second_derivative_term = ((x_r - m_r)**2 / (s_r**4)) - (1 / (s_r**2))
        return np.sum(a_r * pdf_vals * second_derivative_term, axis=1)

    if initial_guesses is None:
        # Component means are good starting points to find modes.
        # We can also add midpoints between means as guesses to find modes between components.
        sorted_mus = np.sort(mus)
        mid_points = (sorted_mus[:-1] + sorted_mus[1:]) / 2
        initial_guesses = np.concatenate([mus, mid_points])

    # Find roots of the first derivative using the initial guesses.
    found_roots, _, ier, _ = fsolve(gmm_pdf_derivative, initial_guesses, full_output=True)
    
    if ier != 1: # fsolve did not converge
        return np.array([])

    # Filter for unique roots (rounding is a simple way to group close roots)
    unique_roots = np.unique(np.round(found_roots, decimals=5))

    # A mode must be a maximum, so the second derivative must be negative.
    second_deriv_vals = gmm_pdf_second_derivative(unique_roots)
    modes = unique_roots[second_deriv_vals < 0]

    return np.sort(modes)


def main():
    """
    Main function to load HGM model outputs and find GMM modes for each event.
    """
    folder_out = '/remote/gpu05/sainz/nn-topocluster-calibration/out/hgm-mc16-opt/hgm-mc16-87e5-mix6'
    
    print(f"[info] Loading data from: {folder_out}")
    try:
        alphas_tst = np.load(f'{folder_out}/final_alphas_tst.npy')
        mus_tst = np.load(f'{folder_out}/final_mus_tst.npy')
        sigmas_tst = np.load(f'{folder_out}/final_sigmas_tst.npy')
    except FileNotFoundError as e:
        print(f"[error] Could not find .npy file: {e}. Please check the path in `folder_out`.")
        return

    folder_in = f'{folder_out}/postprocessing'
    os.makedirs(folder_in, exist_ok=True)
    
    print('[info] Starting peak (mode) finder loop with improved method')
    ntopo, nmix = mus_tst.shape
    
    all_modes, n_modes = [], []

    for t in range(ntopo):
        if (t % 10000 == 0) and t > 0:
            print(f'[info] ... processed {t}/{ntopo} topo-clusters')
        
        modes = find_gmm_modes(alphas_tst[t], mus_tst[t], sigmas_tst[t])
        all_modes.append(modes)
        n_modes.append(len(modes))
    
    print(f'[info] ... processed {ntopo}/{ntopo} topo-clusters')

    mode_peaks = np.full((ntopo, nmix), np.nan)
    for i, modes in enumerate(all_modes):
        num_to_store = min(len(modes), nmix)
        if num_to_store > 0:
            mode_peaks[i, :num_to_store] = modes[:num_to_store]

    output_modes_path = f'{folder_in}/final_modes_model_scipy.npy'
    output_nmodes_path = f'{folder_in}/final_multimodality_scipy.npy'
    
    print(f"[info] Saving found modes to: {output_modes_path}")
    np.save(output_modes_path, mode_peaks)
    print(f"[info] Saving number of modes to: {output_nmodes_path}")
    np.save(output_nmodes_path, np.array(n_modes))
    print("[info] Mode finding complete.")

if __name__ == "__main__":
    main()

