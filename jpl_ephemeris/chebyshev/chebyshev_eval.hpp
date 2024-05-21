#ifndef JPL_EPHEMERIS_CHEBYSHEV_CHEBYSHEV_EVAL_HPP
#define JPL_EPHEMERIS_CHEBYSHEV_CHEBYSHEV_EVAL_HPP

/*!
 * \file jpl_ephemeris/chebyshev/chebyshev_eval.hpp
 * \brief Functions to evaluate a Chebyshev polynomial using Clenshaw's recurrence formula.
 */

// Standard Library Includes
#include <array>
#include <stdexcept>

// jpl_ephemeris Includes
#include "jpl_ephemeris/chebyshev/chebyshev_util.hpp"

namespace jpl_ephemeris {

/*!
 * \brief Evaluate the Chebyshev polynomial at the specified value, x, which must be in the range [lb, ub], using
 * Clenshaw's recurrence formula.
 *
 * \reference Numerical Recipes in Fortran 77: The Art of Scientific Computing, Page 187-188, Routine chebev
 *
 * \param x Value at which the Chebyshev polynomial is to be evaluated at
 * \param lb Lower bound of the function range
 * \param ub Upper bound of the function range
 * \param coeff Chebyshev coefficients evaluated using chebyshev_coefficients function
 * \param order Order of the Chebyshev polynomial to use (order = N - 1)
 * \param coeff_0_factor Factor to multiply coeff[0] by. Numerical Recipes has this at 0.5, but for CSpice the coeff[0]
 *     has already been multiplied by 0.5, so set factor to 1.0
 * \param extrapolation_tol Tolerance for the maximum distance x can be outside of [lb, ub] range before exception is thrown.
 *
 * \return Corresponding Chebyshev coefficient values
 *
 * \tparam N Size of the array
 *
 * \throws std::invalid_argument If coeff has less than one value, or if extrapolation occurs
 */
template<size_t N>
double chebyshev_eval_order(double x, double lb, double ub, const std::array<double, N>& coeff, size_t order = N - 1,
                            double coeff_0_factor = 0.5, double extrapolation_tol = 1e-6) {
    // Make sure incorrect value for N wasn't provided
    if (order > N - 1) {
        order = N - 1;
    }

    // Error checking
    if (order < 1 || N < 1) {
        throw std::invalid_argument("chebyshev_eval() - Size of coeff vector must be greater than zero.");
    } else if (x < lb && std::abs(x - lb) > extrapolation_tol) {
        throw std::invalid_argument("chebyshev_eval() - Value provided for x is outside of the lower bound for the "
                                    "interpolant.");
    } else if (x > ub && std::abs(x - ub) > extrapolation_tol) {
        throw std::invalid_argument("chebyshev_eval() - Value provided for x is outside of the upper bound for the "
                                    "interpolant.");
    }

    // Perform change of variables
    double y  = transform_to_chebyshev_range(x, lb, ub);
    double y2 = 2. * y;

    // Apply Clenshaw's recurrence formula in reverse to preserve small numbers
    double d = 0., dd = 0., sv = 0.;
    for (unsigned int k = order; k >= 1; k--) {
        sv = d;
        d  = y2 * d - dd + coeff[k];
        dd = sv;
    }

    // To be compatible with CSpice, don't multiply coeff[0] by 0.5
    return y * d - dd + coeff_0_factor * coeff[0];
}

/*!
 * \brief Evaluate the Chebyshev polynomial at the specified value, x, which must be in the range [lb, ub], using
 * Clenshaw's recurrence formula.
 *
 * \reference Numerical Recipes in Fortran 77: The Art of Scientific Computing, Page 187-188, Routine chebev
 *
 * \param x Value at which the Chebyshev polynomial is to be evaluated at
 * \param lb Lower bound of the function range
 * \param ub Upper bound of the function range
 * \param coeff Chebyshev coefficients evaluated using chebyshev_coefficients function
 * \param coeff_0_factor Factor to multiply coeff[0] by. Numerical Recipes has this at 0.5, but for CSpice the coeff[0]
 *     has already been multiplied by 0.5, so set factor to 1.0
 * \param extrapolation_tol Tolerance for the maximum distance x can be outside of [lb, ub] range before exception is thrown.
 *
 * \return Corresponding Chebyshev coefficient values
 *
 * \tparam N Size of the array
 *
 * \throws std::invalid_argument If coeff has less than one value, or if extrapolation occurs
 */
template<size_t N>
double chebyshev_eval(double x, double lb, double ub, const std::array<double, N>& coeff, double coeff_0_factor = 0.5,
                      double extrapolation_tol = 1e-6) {
    return chebyshev_eval_order(x, lb, ub, coeff, N - 1, coeff_0_factor, extrapolation_tol);
}

/*!
 * \brief Evaluate the Chebyshev polynomial at the specified value, x, which must be in the range [lb, ub], using
 * Clenshaw's recurrence formula.
 *
 * \note The lb, ub, and Chebyshev coefficients are stored in the same array here, which is used for planetary
 * coefficients from CSpice
 *
 * \reference Numerical Recipes in Fortran 77: The Art of Scientific Computing, Page 187-188, Routine chebev
 *
 * \param x Value at which the Chebyshev polynomial is to be evaluated at
 * \param lb_ub_coeff Array containing lb, ub, and Chebyshev coefficients evaluated using chebyshev_coefficients function
 * \param coeff_0_factor Factor to multiply coeff[0] by. Numerical Recipes has this at 0.5, but for CSpice the coeff[0]
 *     has already been multiplied by 0.5, so set factor to 1.0
 * \param extrapolation_tol Tolerance for the maximum distance x can be outside of [lb, ub] range before exception is thrown.
 *
 * \return Corresponding Chebyshev coefficient values
 *
 * \tparam N Size of the array
 *
 * \throws std::invalid_argument If coeff has less than one value, or if extrapolation occurs
 */
template<size_t N>
double chebyshev_eval(double x, const std::array<double, N>& lb_ub_coeff, double coeff_0_factor = 0.5,
                      double extrapolation_tol = 1e-6) {

    // Error Checking
    if (N < 3) {
        throw std::invalid_argument("chebyshev_eval() - Size of lb_ub_coeff array must be greater than or equal to three.");
    }

    // Extract lb, ub, and coefficients
    double lb = lb_ub_coeff[0];
    double ub = lb_ub_coeff[1];
    std::array<double, N - 2> coeff;
    for (unsigned int k = 0; k < N - 2; k++) {
        coeff[k] = lb_ub_coeff[k + 2];
    }

    // Evaluate the Chebyshev polynomial
    return chebyshev_eval(x, lb, ub, coeff, coeff_0_factor, extrapolation_tol);
}

}  // End namespace jpl_ephemeris

#endif
