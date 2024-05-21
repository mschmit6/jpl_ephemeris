#include "jpl_ephemeris_table.hpp"

// Standard Library Includes
#include <stdexcept>

namespace jpl_ephemeris {

unsigned int JPLEphemerisTable::get_index(double mjdj2k_tdb, double days_per_poly) {
    if (mjdj2k_tdb < start_mjdj2k_ || mjdj2k_tdb > stop_mjdj2k_) {
        throw std::out_of_range("JPLEphemerisTable::get_index() - Value provided for mjdj2k is outside of the valid range "
                                "for the Chebyshev polynomial coefficients. Valid range: 1/1/2000 12:00:00 to 1/1/2100 "
                                "12:00:00.");
    }

    return static_cast<unsigned int>((mjdj2k_tdb - start_mjdj2k_) / days_per_poly);
}

}  // End namespace jpl_ephemeris
