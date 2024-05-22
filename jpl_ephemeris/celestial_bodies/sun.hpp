#ifndef JPL_EPHEMERIS_CELESTIAL_BODIES_SUN_HPP
#define JPL_EPHEMERIS_CELESTIAL_BODIES_SUN_HPP

/*!
 * \file jpl_ephemeris/celestial_bodies/sun.hpp
 * \brief Defines a static class for computing the position/velocity of the Sun relative to the central body
 */

// standard library includes 
#include <array> 

// jpl_ephemeris includes 
#include "jpl_ephemeris/celestial_bodies/central_body.hpp"

namespace jpl_ephemeris {

//! Defines a static class for computing the position/velocity of the Sun relative to the central body
class Sun {
    public: 

        //---------------------------------------
        // Constructors 
        //---------------------------------------

        //! Delete the default constructor
        Sun() = delete; 

        //! Delete the copy constructor 
        Sun(const Sun&) = delete;

        //! Delete the copy assignment operator 
        Sun& operator=(const Sun&) = delete;

        //---------------------------------------
        // Class Methods 
        //---------------------------------------

        /*!
         * \brief Return the position of the Sun relative to the specified CentralBody
         *
         * \param mjdj2k_tdb Modified Julian Date from the J2000 Epoch, in the TDB Time System
         * \param central_body Central body that the Sun measured relative to
         *
         * \return Position of the Sun relative to the specified CentralBody [km]
         */
        static std::array<double, 3> get_position(double mjdj2k_tdb, CentralBody central_body = CentralBody::Earth); 

        /*!
         * \brief Return the velocity of the Sun relative to the specified CentralBody
         *
         * \param mjdj2k_tdb Modified Julian Date from the J2000 Epoch, in the TDB Time System
         * \param central_body Central body that the Sun measured relative to
         *
         * \return Velocity of the Sun relative to the specified CentralBody [km/s]
         */
        static std::array<double, 3> get_velocity(double mjdj2k_tdb, CentralBody central_body = CentralBody::Earth); 
};

}  // namespace jpl_ephemeris

#endif