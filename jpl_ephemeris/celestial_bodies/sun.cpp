#include "sun.hpp"

// standard library includes 
#include <stdexcept>

// jpl_ephemeris includes 
#include "jpl_ephemeris/celestial_bodies/ephemeris_tables/moon_gcrf_table.hpp"
#include "jpl_ephemeris/celestial_bodies/ephemeris_tables/earth_from_ssb_gcrf_table.hpp"
#include "jpl_ephemeris/celestial_bodies/ephemeris_tables/sun_from_ssb_gcrf_table.hpp"

namespace jpl_ephemeris {

//---------------------------------------
// Class Methods 
//---------------------------------------

std::array<double, 3> Sun::get_position(double mjdj2k_tdb, CentralBody central_body) {
    // Initialize return array for position
    std::array<double, 3> pos{0., 0., 0.}; 

    switch(central_body) {
        case CentralBody::SSB: {
            pos = SunFromSSBGCRFTable::get_position(mjdj2k_tdb);
            break;
        }
        case CentralBody::Sun: {
            break;
        }
        case CentralBody::Earth: {
            // Compute the position of the Earth and Sun relative to SSB
            std::array<double, 3> earth_from_ssb = EarthFromSSBGCRFTable::get_position(mjdj2k_tdb);
            std::array<double, 3> sun_from_ssb = SunFromSSBGCRFTable::get_position(mjdj2k_tdb);

            // Compute the position of the Sun relative to the Earth 
            for (int k = 0; k < 3; k++) {
                pos[k] = sun_from_ssb[k] - earth_from_ssb[k]; 
            }
            break;
        }
        case CentralBody::Moon: {
            // Compute the position of the Earth and Sun relative to SSB, and the Moon relative to Earth
            std::array<double, 3> earth_from_ssb = EarthFromSSBGCRFTable::get_position(mjdj2k_tdb);
            std::array<double, 3> sun_from_ssb = SunFromSSBGCRFTable::get_position(mjdj2k_tdb);
            std::array<double, 3> moon_from_earth = MoonGCRFTable::get_position(mjdj2k_tdb);

            // Compute the position of the Sun relative to the Moon 
            for (int k = 0; k < 3; k++) {
                pos[k] = sun_from_ssb[k] - earth_from_ssb[k] - moon_from_earth[k]; 
            }
            break;
        }
        default: {
            throw std::invalid_argument("Sun::get_position() - Unexpected input provided for CentralBody");
        }
    }

    return pos;
}

//--------------------------------------------------------------------------------------------------------------------------

std::array<double, 3> Sun::get_velocity(double mjdj2k_tdb, CentralBody central_body) {
    // Initialize return array for velocity
    std::array<double, 3> vel{0., 0., 0.}; 

    switch(central_body) {
        case CentralBody::SSB: {
            vel = SunFromSSBGCRFTable::get_velocity(mjdj2k_tdb);
            break;
        }
        case CentralBody::Sun: {
            break;
        }
        case CentralBody::Earth: {
            // Compute the velocity of the Earth and Sun relative to SSB
            std::array<double, 3> earth_from_ssb = EarthFromSSBGCRFTable::get_velocity(mjdj2k_tdb);
            std::array<double, 3> sun_from_ssb = SunFromSSBGCRFTable::get_velocity(mjdj2k_tdb);

            // Compute the velocity of the Sun relative to the Earth 
            for (int k = 0; k < 3; k++) {
                vel[k] = sun_from_ssb[k] - earth_from_ssb[k]; 
            }
            break;
        }
        case CentralBody::Moon: {
            // Compute the velocity of the Earth and Sun relative to SSB, and the Moon relative to Earth
            std::array<double, 3> earth_from_ssb = EarthFromSSBGCRFTable::get_velocity(mjdj2k_tdb);
            std::array<double, 3> sun_from_ssb = SunFromSSBGCRFTable::get_velocity(mjdj2k_tdb);
            std::array<double, 3> moon_from_earth = MoonGCRFTable::get_velocity(mjdj2k_tdb);

            // Compute the velocity of the Sun relative to the Moon 
            for (int k = 0; k < 3; k++) {
                vel[k] = sun_from_ssb[k] - earth_from_ssb[k] - moon_from_earth[k]; 
            }
            break;
        }
        default: {
            throw std::invalid_argument("Sun::get_velocity() - Unexpected input provided for CentralBody");
        }
    }

    return vel;
}

} // End namespace jpl_ephemeris