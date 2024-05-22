// Standard Library Includes
#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// jpl_ephemeris includes
#include <jpl_ephemeris.hpp>
using namespace jpl_ephemeris; 

void print_array(const std::string& prefix, const std::array<double, 3>& arr) {
    std::cout << prefix << std::setprecision(15) << " = [" << arr[0] << ", " << arr[1] << ", " << arr[2] << "]\n"; 
}

int main() {
    // Use J2000 ish Epoch
    double mjdj2k_tdb = 0.0;

    // Compute the position of the Moon w.r.t. the Sun
    std::array<double, 3> moon_wrt_sun = Moon::get_position(mjdj2k_tdb, CentralBody::Sun); 
    print_array("moon_wrt_sun", moon_wrt_sun); 

    // Compute the position of the Sun w.r.t. the Moon
    std::array<double, 3> sun_wrt_sun = Sun::get_position(mjdj2k_tdb, CentralBody::Moon); 
    print_array("sun_wrt_sun", sun_wrt_sun); 

    return 0;
}
