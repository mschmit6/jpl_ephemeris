#include "chebyshev_util.hpp"

namespace jpl_ephemeris {

double transform_from_chebyshev_range(double x, double lb, double ub) {
    return x * 0.5 * (ub - lb) + 0.5 * (ub + lb);
}

//--------------------------------------------------------------------------------------------------------------------------

double transform_to_chebyshev_range(double x, double lb, double ub) {
    return (x - 0.5 * (ub + lb)) / (0.5 * (ub - lb));
}

}  // End namespace jpl_ephemeris
