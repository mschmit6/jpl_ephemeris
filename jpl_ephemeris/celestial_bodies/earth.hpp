#ifndef JPL_EPHEMERIS_CELESTIAL_BODIES_EARTH_HPP
#define JPL_EPHEMERIS_CELESTIAL_BODIES_EARTH_HPP

/*!
 * \file jpl_ephemeris/celestial_bodies/earth.hpp
 * \brief Defines a static class for computing the position/velocity of Earth relative to the central body
 */

// standard library includes 
#include <array> 

// jpl_ephemeris includes 
#include "jpl_ephemeris/celestial_bodies/central_body.hpp"

namespace jpl_ephemeris {

//! Defines a static class for computing the position/velocity of Earth relative to the central body
class Earth {
    public: 

        //---------------------------------------
        // Constructors 
        //---------------------------------------

        //! Delete the default constructor
        Earth() = delete; 

        //! Delete the copy constructor 
        Earth(const Earth&) = delete;

        //! Delete the copy assignment operator 
        Earth& operator=(const Earth&) = delete;

        //---------------------------------------
        // Class Methods 
        //---------------------------------------

        /*!
         * \brief Return the position of the Earth relative to the specified CentralBody
         *
         * \param mjdj2k_tdb Modified Julian Date from the J2000 Epoch, in the TDB Time System
         * \param central_body Central body that the Earth measured relative to
         *
         * \return Position of the Earth relative to the specified CentralBody [km]
         */
        static std::array<double, 3> get_position(double mjdj2k_tdb, CentralBody central_body = CentralBody::Earth); 

        /*!
         * \brief Return the velocity of the Earth relative to the specified CentralBody
         *
         * \param mjdj2k_tdb Modified Julian Date from the J2000 Epoch, in the TDB Time System
         * \param central_body Central body that the Earth measured relative to
         *
         * \return Velocity of the Earth relative to the specified CentralBody [km/s]
         */
        static std::array<double, 3> get_velocity(double mjdj2k_tdb, CentralBody central_body = CentralBody::Earth); 
};

}  // namespace jpl_ephemeris

#endif