// Standard Library Includes
#include <array>

// jpl_ephemeris includes
#include <jpl_ephemeris.hpp>
using namespace jpl_ephemeris; 

int main() {

    // Compute the Sun's position relative to Earth at the specified time
    double mjdj2k_tdb = 1000.5;
    std::array<double, 3> sun_pos = Sun::get_position(mjdj2k_tdb, CentralBody::Earth); 
    return 0;
}


