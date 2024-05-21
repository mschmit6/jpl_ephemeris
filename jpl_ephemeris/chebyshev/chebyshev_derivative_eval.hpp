#ifndef JPL_EPHEMERIS_CHEBYSHEV_CHEBYSHEV_DERIVATIVE_EVAL_HPP
#define JPL_EPHEMERIS_CHEBYSHEV_CHEBYSHEV_DERIVATIVE_EVAL_HPP

/*!
 * \file jpl_ephemeris/chebyshev/chebyshev_derivative_eval.hpp
 * \brief Functions to evaluate the derivative of a Chebyshev polynomial using Clenshaw's recurrence formula.
 */

// Standard Library Includes
#include <array>
#include <stdexcept>

// jpl_ephemeris Includes
#include "jpl_ephemeris/chebyshev/chebyshev_util.hpp"

namespace jpl_ephemeris {

/*!
 * \brief Evaluate the derivative of the Chebyshev polynomial at the specified value, x, which must be in the range [lb, ub],
 * using Clenshaw's recurrence formula.
 *
 * \reference Numerical Recipes in Fortran 77: The Art of Scientific Computing, Page 189, Routine chder
 *
 * \param x Value at which the Chebyshev polynomial is to be evaluated at
 * \param lb Lower bound of the function range
 * \param ub Upper bound of the function range
 * \param coeff Chebyshev coefficients evaluated using chebyshev_coefficients function
 * \param extrapolation_tol Tolerance for the maximum distance x can be outside of [lb, ub] range before exception is thrown.
 *
 * \return Corresponding Chebyshev coefficient values
 *
 * \tparam N Size of the array
 *
 * \throws std::invalid_argument If coeff has less than one value, or if extrapolation occurs
 */
template<size_t N>
double chebyshev_derivative_eval(double x, double lb, double ub, const std::array<double, N>& coeff,
                                 double extrapolation_tol = 1e-6) {
    // Error checking
    if (N < 1) {
        throw std::invalid_argument("chebyshev_derivative_eval() - Size of coeff array must be greater than zero.");
    } else if (x < lb && std::abs(x - lb) > extrapolation_tol) {
        throw std::invalid_argument("chebyshev_derivative_eval() - Value provided for x is outside of the lower bound for "
                                    "the interpolant.");
    } else if (x > ub && std::abs(x - ub) > extrapolation_tol) {
        throw std::invalid_argument("chebyshev_derivative_eval() - Value provided for x is outside of the upper bound for "
                                    "the interpolant.");
    }

    // Perform change of variables
    double y  = transform_to_chebyshev_range(x, lb, ub);
    double y2 = 2. * y;

    // Apply Clenshaw's recurrence formula in reverse to preserve small numbers
    double d = 0., dd = 0., sv = 0.;
    double dp = 0., ddp = 0., svp = 0.;

    for (unsigned int k = N - 1; k >= 1; k--) {
        // Compute the derivative coefficient values
        svp = dp;
        dp  = y2 * dp - ddp + 2. * d;
        ddp = svp;

        // Compute the coefficient values, which are required by the derivative
        sv = d;
        d  = y2 * d - dd + coeff[k];
        dd = sv;
    }

    // Normalize to the interval ub - lb
    double factor = 2. / (ub - lb);
    return factor * (y * dp - ddp + d);
}

/*!
 * \brief Evaluate the derivative of the Chebyshev polynomial at the specified value, x, which must be in the range [lb, ub],
 * using Clenshaw's recurrence formula.
 *
 * \note The lb, ub, and Chebyshev coefficients are stored in the same array here, which is used for planetary
 * coefficients from CSpice
 *
 * \reference Numerical Recipes in Fortran 77: The Art of Scientific Computing, Page 189, Routine chder
 *
 * \param x Value at which the Chebyshev polynomial is to be evaluated at
 * \param lb_ub_coeff Vector containing lb, ub, and Chebyshev coefficients evaluated using chebyshev_coefficients function
 * \param extrapolation_tol Tolerance for the maximum distance x can be outside of [lb, ub] range before exception is thrown.
 *
 * \return Corresponding Chebyshev coefficient values
 *
 * \tparam N Size of the array
 *
 * \throws std::invalid_argument If coeff has less than one value, or if extrapolation occurs
 */
template<size_t N>
double chebyshev_derivative_eval(double x, const std::array<double, N>& lb_ub_coeff, double extrapolation_tol = 1e-6) {

    // Error Checking
    if (N < 3) {
        throw std::invalid_argument("chebyshev_derivative_eval() - Size of lb_ub_coeff array must be greater than or equal "
                                    "to three.");
    }

    // Extract lb, ub, and coefficients
    double lb = lb_ub_coeff[0];
    double ub = lb_ub_coeff[1];
    std::array<double, N - 2> coeff;
    for (unsigned int k = 0; k < N - 2; k++) {
        coeff[k] = lb_ub_coeff[k + 2];
    }

    // Evaluate the Chebyshev polynomial
    return chebyshev_derivative_eval(x, lb, ub, coeff, extrapolation_tol);
}

}  // End namespace jpl_ephemeris

#endif
