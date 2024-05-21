#ifndef JPL_EPHEMERIS_CHEBYSHEV_CHEBYSHEV_UTIL_HPP
#define JPL_EPHEMERIS_CHEBYSHEV_CHEBYSHEV_UTIL_HPP

/*!
 * \file jpl_ephemeris/chebyshev/chebyshev_transformation.hpp
 * \brief Utility functions for Chebyshev interpolation
 */

namespace jpl_ephemeris {

/*!
 * \brief Transform variable from the Chebyshev range of [-1, 1] to the range [lb, ub]
 *
 * \reference Numerical Recipes in Fortran 77: The Art of Scientific Computing, Page 186, Eq. 5.8.10
 *
 * \param x Variable in the Chebyshev range
 * \param lb Lower bound of the function range
 * \param ub Upper bound of the function range
 *
 * \return Variable in the range [lb, ub]
 */
double transform_from_chebyshev_range(double x, double lb, double ub);

/*!
 * \brief Transform variable from the range [lb, ub] to the Chebyshev range of [-1, 1]
 *
 * \reference Numerical Recipes in Fortran 77: The Art of Scientific Computing, Page 186, Eq. 5.8.10
 *
 * \param x Variable in the range [lb, ub]
 * \param lb Lower bound of the function range
 * \param ub Upper bound of the function range
 *
 * \return Variable in the Chebyshev range [-1, 1]
 */
double transform_to_chebyshev_range(double x, double lb, double ub);

}  // End namespace jpl_ephemeris

#endif
