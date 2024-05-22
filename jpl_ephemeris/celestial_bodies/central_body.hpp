#ifndef JPL_EPHEMERIS_CELESTIAL_BODIES_CENTRAL_BODY_HPP
#define JPL_EPHEMERIS_CELESTIAL_BODIES_CENTRAL_BODY_HPP

/*!
 * \file jpl_ephemeris/celestial_bodies/central_body.hpp
 * \brief Defines enum class for specifying the central body used when computing the position/velocity of a Celestial Body
 */

namespace jpl_ephemeris {

//! Specifies the central body used when computing the position/velocity of a Celestial Body
enum class CentralBody : int {
    SSB = 0,    //!< Use the Solar System Barycenter (SSB) as the central body
    Sun = 1,    //!< Use the Sun as the central body 
    Earth = 2,  //!< Use Earth as the central body  
    Moon = 3,   //!< Use the Moon as the central body
};

}  // namespace jpl_ephemeris

#endif