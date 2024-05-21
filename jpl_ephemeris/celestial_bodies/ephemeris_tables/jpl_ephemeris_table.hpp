#ifndef JPL_PLANETS_JPL_EPHEMERIS_JPL_CB_TABLE_HPP
#define JPL_PLANETS_JPL_EPHEMERIS_JPL_CB_TABLE_HPP

/*!
 * \file jpl_ephemeris/celestial_bodies/jpl_ephemeris_table.hpp
 * \brief Base class for any JPL Celestial-Body (CB) table
 *
 * \note Resource: https://www.celestialprogramming.com/jpl-ephemeris-format/jpl-ephemeris-format.html
 */

namespace jpl_ephemeris {

//! Base class for any JPL Celestial-Body (CB) table
class JPLEphemerisTable {

    protected:

        //---------------------------------------
        // Constructors
        //---------------------------------------

        //! Delete Default constructor
        JPLEphemerisTable() = delete;

        //! Delete Assignment operator
        JPLEphemerisTable& operator=(const JPLEphemerisTable&) = delete;

        //---------------------------------------
        // Class Methods
        //---------------------------------------

        /*!
         * \brief Get the index corresponding to the Chebyshev polynomial coefficients
         *
         * \param mjdj2k_tdb Modified Julian Date from the J2000 Epoch in the TDB TimeSystem
         * \param days_per_poly Number of days covered by each set of polynomial coefficients
         *
         * \return Table lookup index
         */
        static unsigned int get_index(double mjdj2k_tdb, double days_per_poly);

        //---------------------------------------
        // Class Attributes
        //---------------------------------------

        //! Lower bound on MJD J2K in the TDB time system [days]
        static constexpr double start_mjdj2k_ = -8.5;

        //! Upper bound on MJD J2K in the TDB time system [days]
        static constexpr double stop_mjdj2k_ = 36535.5;

};

}  // End namespace jpl_ephemeris

#endif
