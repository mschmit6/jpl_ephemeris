#include "earth_from_ssb_gcrf_table.hpp"

// Standard Library Includes
#include <array>

// jpl_ephemeris includes
#include "jpl_ephemeris/celestial_bodies/ephemeris_tables/earth_from_emb_gcrf_table.hpp"
#include "jpl_ephemeris/celestial_bodies/ephemeris_tables/emb_from_ssb_gcrf_table.hpp"
#include "jpl_ephemeris/chebyshev/chebyshev_derivative_eval.hpp"
#include "jpl_ephemeris/chebyshev/chebyshev_eval.hpp"

namespace jpl_ephemeris {

//---------------------------------------
// Class Methods
//---------------------------------------

std::array<double, 3> EarthFromSSBGCRFTable::get_position(double mjdj2k_tdb) {
    // Compute the position of the Earth relative to SSB
    std::array<double, 3> emb_from_ssb   = EMBFromSSBGCRFTable::get_position(mjdj2k_tdb);
    std::array<double, 3> earth_from_emb = EarthFromEMBGCRFTable::get_position(mjdj2k_tdb);

    std::array<double, 3> earth_from_ssb{0., 0., 0.}; 
    for (unsigned int k = 0; k < 3; k++) {
        earth_from_ssb[k] = earth_from_emb[k] + emb_from_ssb[k];
    }
    return earth_from_ssb;
}

//--------------------------------------------------------------------------------------------------------------------------

std::array<double, 3> EarthFromSSBGCRFTable::get_velocity(double mjdj2k_tdb) {
    // Compute the position of the Earth relative to SSB
    std::array<double, 3> emb_from_ssb   = EMBFromSSBGCRFTable::get_velocity(mjdj2k_tdb);
    std::array<double, 3> earth_from_emb = EarthFromEMBGCRFTable::get_velocity(mjdj2k_tdb);

    std::array<double, 3> earth_from_ssb{0., 0., 0.}; 
    for (unsigned int k = 0; k < 3; k++) {
        earth_from_ssb[k] = earth_from_emb[k] + emb_from_ssb[k];
    }
    return earth_from_ssb;
}

}  // namespace jpl_ephemeris
