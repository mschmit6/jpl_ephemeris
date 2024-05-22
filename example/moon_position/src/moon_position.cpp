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

void time_moon_position() {
    // Start recording runtime
    auto start = std::chrono::high_resolution_clock::now();

    // Get the position of the moon using jpl_ephemeris
    double mjdj2k_tdb = 0.0;
    double step = 30 / 86400.0; // step in days
    std::array<double, 3> moon_pos;

    for (unsigned int k = 0; k < 1000000; k++) {
        moon_pos = Moon::get_position(mjdj2k_tdb);
        mjdj2k_tdb += step;
    }

    // Start recording runtime
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count() * 1e-9;

    std::cout << std::setprecision(5) << "duration (sec) = " << duration << "\n";
}

void print_array(const std::string& prefix, const std::array<double, 3>& arr) {
    std::cout << prefix << std::setprecision(15) << " = [" << arr[0] << ", " << arr[1] << ", " << arr[2] << "]\n"; 
}

int main() {
    // Compute the position of the Moon w.r.t. the Sun
    double mjdj2k_tdb = 0.0;
    std::array<double, 3> moon_wrt_sun = Moon::get_position(mjdj2k_tdb, CentralBody::Sun); 

    print_array("moon_wrt_sun", moon_wrt_sun); 

    return 0;
}
