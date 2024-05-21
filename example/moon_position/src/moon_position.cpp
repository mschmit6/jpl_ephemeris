// Standard Library Includes
#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// jpl_ephemeris includes
#include <jpl_ephemeris.hpp>

int main() {
    // Start recording runtime
    auto start = std::chrono::high_resolution_clock::now();

    // Get the position of the moon using jpl_ephemeris
    double mjdj2k_tdb = 0.0;
    double step = 30 / 86400.0; // step in days
    std::array<double, 3> moon_pos;
    std::vector<double> runtimes;

    for (unsigned int k = 0; k < 1000000; k++) {
        // Start recording runtime
        auto start_local = std::chrono::high_resolution_clock::now();

        moon_pos = jpl_ephemeris::MoonGCRFTable::get_position(mjdj2k_tdb);
        mjdj2k_tdb += step;

        // Start recording runtime
        auto stop_local = std::chrono::high_resolution_clock::now();
        double duration_local = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_local - start_local).count() * 1e-9;
        runtimes.push_back(duration_local);
    }


    // Start recording runtime
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count() * 1e-9;

    //std::cout << std::setprecision(20) << "moon_pos = [" << moon_pos[0] << ", " << moon_pos[1] << ", " << moon_pos[2] << "]\n";
    std::cout << std::setprecision(5) << "duration (sec) = " << duration << "\n";

    std::ofstream file;
    file.open("RuntimePerCall.txt");

    file << std::setprecision(20);

    for (unsigned int k = 0; k < runtimes.size(); k++)
    {
        file << runtimes[k] << "\n";
    }

    file.close();
    return 0;
}
