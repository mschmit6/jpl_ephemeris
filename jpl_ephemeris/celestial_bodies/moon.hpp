#ifndef JPL_EPHEMERIS_CELESTIAL_BODIES_MOON_HPP
#define JPL_EPHEMERIS_CELESTIAL_BODIES_MOON_HPP

/*!
 * \file jpl_ephemeris/celestial_bodies/moon.hpp
 * \brief Defines a static class for computing the position/velocity of the Moon relative to the central body
 */

// standard library includes 
#include <array> 

// jpl_ephemeris includes 
#include "jpl_ephemeris/celestial_bodies/central_body.hpp"

namespace jpl_ephemeris {

//! Defines a static class for computing the position/velocity of the Moon relative to the central body
class Moon {
    public: 

        //---------------------------------------
        // Constructors 
        //---------------------------------------

        //! Delete the default constructor
        Moon() = delete; 

        //! Delete the copy constructor 
        Moon(const Moon&) = delete;

        //! Delete the copy assignment operator 
        Moon& operator=(const Moon&) = delete;

        //---------------------------------------
        // Class Methods 
        //---------------------------------------

        /*!
         * \brief Return the position of the Moon relative to the specified CentralBody
         *
         * \param mjdj2k_tdb Modified Julian Date from the J2000 Epoch, in the TDB Time System
         * \param central_body Central body that the Moon measured relative to
         *
         * \return Position of the Moon relative to the specified CentralBody [km]
         */
        static std::array<double, 3> get_position(double mjdj2k_tdb, CentralBody central_body = CentralBody::Earth); 

        /*!
         * \brief Return the velocity of the Moon relative to the specified CentralBody
         *
         * \param mjdj2k_tdb Modified Julian Date from the J2000 Epoch, in the TDB Time System
         * \param central_body Central body that the Moon measured relative to
         *
         * \return Velocity of the Moon relative to the specified CentralBody [km/s]
         */
        static std::array<double, 3> get_velocity(double mjdj2k_tdb, CentralBody central_body = CentralBody::Earth); 
};

}  // namespace jpl_ephemeris

#endif