#ifndef JPL_EPHEMERIS_CELESTIAL_BODIES_EPHEMERIS_TABLES_EARTH_FROM_EMB_GCRF_TABLE_HPP
#define JPL_EPHEMERIS_CELESTIAL_BODIES_EPHEMERIS_TABLES_EARTH_FROM_EMB_GCRF_TABLE_HPP

/*!
 * \file jpl_ephemeris/celestial_bodies/ephemeris_tables/earth_from_emb_gcrf_table.hpp
 * \brief Static class containing the CSpice Chebyshev polynomial coefficients required to compute the high-fidelity position
 * of the Earth relative to the Earth-Moon Barycenter (EMB) in the GCRF frame.
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
 * of the Earth relative to the Earth-Moon Barycenter (EMB) in the GCRF frame.
 * 
 * \attention This uses the DE430 JPL Ephemeris tables
 */
class EarthFromEMBGCRFTable : public JPLEphemerisTable {
    public:

        //---------------------------------------
        // Constructors
        //---------------------------------------

        //! Default constructor
        EarthFromEMBGCRFTable() = delete;

        //! Assignment operator
        EarthFromEMBGCRFTable& operator=(const EarthFromEMBGCRFTable&) = delete;

        //---------------------------------------
        // Class Methods
        //---------------------------------------

        /*!
         * \brief Return the position of the Earth relative to the Earth-Moon Barycenter (EMB) in the GCRF frame
         *
         * \param mjdj2k_tdb Modified Julian Date from the J2000 Epoch, in the TDB Time System
         *
         * \return Position of the Earth relative to the Earth-Moon Barycenter (EMB) in the GCRF frame [km]
         */
        static std::array<double, 3> get_position(double mjdj2k_tdb);

        /*!
         * \brief Return the velocity of the Earth relative to the Earth-Moon Barycenter (EMB) in the GCRF frame
         *
         * \param mjdj2k_tdb Modified Julian Date from the J2000 Epoch, in the TDB Time System
         *
         * \return Velocity of the Earth relative to the Earth-Moon Barycenter (EMB) in the GCRF frame [km/s]
         */
        static std::array<double, 3> get_velocity(double mjdj2k_tdb);

    private:

        //---------------------------------------
        // Class Attributes
        //---------------------------------------

        //! Number of days covered by each set of polynomial coefficients
        static constexpr double days_per_poly_ = 4;

        //! Chebyshev polynomial coefficients for the x-coordinate [km]
        static std::array<std::array<double, 15>, 9136> x_interp_;

        //! Chebyshev polynomial coefficients for the y-coordinate [km]
        static std::array<std::array<double, 15>, 9136> y_interp_;

        //! Chebyshev polynomial coefficients for the z-coordinate [km]
        static std::array<std::array<double, 15>, 9136> z_interp_;
};

}  // End namespace jpl_ephemeris

#endif
