#ifndef JPL_EPHEMERIS_CELESTIAL_BODIES_EPHEMERIS_TABLES_EARTH_FROM_SSB_GCRF_TABLE_HPP
#define JPL_EPHEMERIS_CELESTIAL_BODIES_EPHEMERIS_TABLES_EARTH_FROM_SSB_GCRF_TABLE_HPP

/*!
 * \file jpl_ephemeris/celestial_bodies/ephemeris_tables/earth_from_ssb_gcrf_table.hpp
 * \brief Static class containing the CSpice Chebyshev polynomial coefficients required to compute the high-fidelity position
 * of the Earth relative to the Solar System Barycenter (SSB) in the GCRF frame.
 *
 * \note Resource: https://www.celestialprogramming.com/jpl-ephemeris-format/jpl-ephemeris-format.html
 */

// Standard Library Includes
#include <array>

// jpl_ephemeris Includes
#include "jpl_ephemeris/celestial_bodies/ephemeris_tables/jpl_ephemeris_table.hpp"

namespace jpl_ephemeris {

/*!
 * \brief Static class containing the CSpice Chebyshev polynomial coefficients required to compute the high-fidelity position
 * of the Earth relative to the Solar System Barycenter (SSB) in the GCRF frame.
 * 
 * \attention This uses the DE430 JPL Ephemeris tables
 */
class EarthFromSSBGCRFTable : public JPLEphemerisTable {
    public:

        //---------------------------------------
        // Constructors
        //---------------------------------------

        //! Default constructor
        EarthFromSSBGCRFTable() = delete;

        //! Assignment operator
        EarthFromSSBGCRFTable& operator=(const EarthFromSSBGCRFTable&) = delete;

        //---------------------------------------
        // Class Methods
        //---------------------------------------

        /*!
         * \brief Return the position of the Earth relative to the Solar System Barycenter (SSB) in the GCRF frame
         *
         * \param mjdj2k_tdb Modified Julian Date from the J2000 Epoch, in the TDB Time System
         *
         * \return Position of the Earth relative to the Solar System Barycenter (SSB) in the GCRF frame [km]
         */
        static std::array<double, 3> get_position(double mjdj2k_tdb);

        /*!
         * \brief Return the velocity of the Earth relative to the Solar System Barycenter (SSB) in the GCRF frame
         *
         * \param mjdj2k_tdb Modified Julian Date from the J2000 Epoch, in the TDB Time System
         *
         * \return Velocity of the Earth relative to the Solar System Barycenter (SSB) in the GCRF frame [km/s]
         */
        static std::array<double, 3> get_velocity(double mjdj2k_tdb);
};

}  // End namespace jpl_ephemeris

#endif
