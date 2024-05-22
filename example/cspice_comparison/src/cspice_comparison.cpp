// Standard Library Includes
#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// cspice includes
#include <cspice/SpiceUsr.h>

// jpl_ephemeris includes
#include <jpl_ephemeris.hpp>
using namespace jpl_ephemeris; 

//--------------------------------------------------------------------------------------------------------------------------

std::array<double, 3> compute_cspice_pos(double mjdj2k_tdb, CentralBody targ, CentralBody central_body) {
    // Start recording runtime
    auto start = std::chrono::high_resolution_clock::now();

    // Set the appropriate target string
    std::string targ_str; 
    switch (targ) {
        case CentralBody::Moon: {
            targ_str = "MOON";
            break;
        }
        case CentralBody::Sun: {
            targ_str = "SUN";
            break;
        }
        case CentralBody::Earth: {
            targ_str = "EARTH";
            break;
        }
        default: {
            throw std::invalid_argument("compute_cspice_pos() - Invalid value provided for targ.");
        }
    }

    // Set the appropriate central_body_str
    std::string central_body_str; 
    switch (central_body) {
        case CentralBody::SSB: {
            central_body_str = "SSB";
            break;
        }
        case CentralBody::Moon: {
            central_body_str = "MOON";
            break;
        }
        case CentralBody::Sun: {
            central_body_str = "SUN";
            break;
        }
        case CentralBody::Earth: {
            central_body_str = "EARTH";
            break;
        }
        default: {
            throw std::invalid_argument("compute_cspice_pos() - Invalid value provided for targ.");
        }
    }

    // Don't correct for aberration
    SpiceDouble et = mjdj2k_tdb * 86400.0; // Seconds past J2000 Epoch in TDB time system
    std::string abcorr = "NONE";
    std::string frame = "J2000";

    SpiceDouble pos[3];
    SpiceDouble lt;

    spkpos_c(targ_str.c_str(), et, frame.c_str(), abcorr.c_str(), central_body_str.c_str(), pos, &lt);

    return std::array<double, 3>{pos[0], pos[1], pos[2]};
}

//--------------------------------------------------------------------------------------------------------------------------

std::array<double, 3> compute_jpl_ephem_pos(double mjdj2k_tdb, CentralBody targ, CentralBody central_body) {
    switch (targ) {
        case CentralBody::Moon: {
            return Moon::get_position(mjdj2k_tdb, central_body); 
        }
        case CentralBody::Sun: {
            return Sun::get_position(mjdj2k_tdb, central_body); 
        }
        case CentralBody::Earth: {
            return Earth::get_position(mjdj2k_tdb, central_body); 
        }
        default: {
            throw std::invalid_argument("compute_jpl_ephem_pos() - Invalid value provided for targ.");
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------

void print_array(const std::string& prefix, const std::array<double, 3>& arr) {
    std::cout << prefix << std::setprecision(15) << " = [" << arr[0] << ", " << arr[1] << ", " << arr[2] << "]\n"; 
}

//--------------------------------------------------------------------------------------------------------------------------

double compute_error(const std::array<double, 3>& truth, const std::array<double, 3>& est) {
    double err = 0.; 
    for (unsigned int k = 0; k < 3; k++) {
        err += std::pow(est[k] - truth[k], 2); 
    }
    return std::sqrt(err); 
}

//--------------------------------------------------------------------------------------------------------------------------

std::string to_string(CentralBody cb) {
    switch (cb) {
        case CentralBody::SSB: {
            return "SSB"; 
        }
        case CentralBody::Sun: {
            return "Sun"; 
        }
        case CentralBody::Earth: {
            return "Earth"; 
        }
        case CentralBody::Moon: {
            return "Moon"; 
        }
        default: {
            throw std::invalid_argument("to_string() - Invalid value provided for CentralBody");
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------

void accuracy_test(double mjdj2k_tdb, double step, const std::array<CentralBody, 3>& target_bodies, 
                   const std::array<CentralBody, 4>& central_bodies, double err_tol = 1e-6) {

    // Quick struct to store any errors above the specified tolerance
    struct EphemerisErrorEntry {
        EphemerisErrorEntry(double mjdj2k_tdb, CentralBody central_body, CentralBody tgt_body, 
                       const std::array<double, 3>& cspice_pos, const std::array<double, 3>& jpl_ephem_pos, double err) :
                       mjdj2k_tdb(mjdj2k_tdb), central_body(central_body), tgt_body(tgt_body), cspice_pos(cspice_pos), 
                       jpl_ephem_pos(jpl_ephem_pos), err(err){

                       }

        double mjdj2k_tdb; 
        CentralBody central_body;
        CentralBody tgt_body; 
        std::array<double, 3> cspice_pos;
        std::array<double, 3> jpl_ephem_pos;
        double err; 
    };

    std::vector<EphemerisErrorEntry> error_entries; 
    while (mjdj2k_tdb <= 35000) {
        for (CentralBody central_body : central_bodies) {
            for (CentralBody tgt_body : target_bodies) {
                // Compute the position of the Moon w.r.t. the Sun
                std::array<double, 3> cspice_pos = compute_cspice_pos(mjdj2k_tdb, tgt_body, central_body); 

                // Compute the position of the Sun w.r.t. the Moon
                std::array<double, 3> jpl_ephem_pos = compute_jpl_ephem_pos(mjdj2k_tdb, tgt_body, central_body); 

                // Compute the error:
                double err = compute_error(cspice_pos, jpl_ephem_pos); 

                if (err > err_tol) {
                    error_entries.emplace_back(mjdj2k_tdb, central_body, tgt_body, cspice_pos, jpl_ephem_pos, err); 
                }
            }
        }

        mjdj2k_tdb += step; 
    }

    // Print out any occurrences where the error was above the tolerance 
    if (error_entries.size() == 0) {
        std::cout << "No errors exceeded the tolerance of " + std::to_string(err_tol) + " km\n\n"; 
    } else {
        for (const auto& err_entry : error_entries) {
            std::cout << "mjdj2k_tdb = " << err_entry.mjdj2k_tdb << "\n"; 
            std::cout << "central_body = " << to_string(err_entry.central_body) << "\n"; 
            std::cout << "tgt_body = " << to_string(err_entry.tgt_body) << "\n"; 
            print_array("cspice_pos", err_entry.cspice_pos); 
            print_array("jpl_ephem_pos", err_entry.jpl_ephem_pos); 
            std::cout << "mjdj2k_tdb = " << err_entry.err << "\n\n"; 
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------

void compute_runtimes(double mjdj2k_tdb_0, double step, const std::array<CentralBody, 3>& target_bodies, 
                   const std::array<CentralBody, 4>& central_bodies, double err_tol = 1e-6) {

    // Record runtime for cspice library 
    auto start = std::chrono::high_resolution_clock::now();
    double mjdj2k_tdb = mjdj2k_tdb_0;
    while (mjdj2k_tdb <= 35000) {
        for (CentralBody central_body : central_bodies) {
            for (CentralBody tgt_body : target_bodies) {
                // Compute the position of the Moon w.r.t. the Sun
                std::array<double, 3> cspice_pos = compute_cspice_pos(mjdj2k_tdb, tgt_body, central_body); 
            }
        }

        mjdj2k_tdb += step; 
    }
    auto stop = std::chrono::high_resolution_clock::now();
    double duration_cspice = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() * 1e-6;

    // Record runtime for jpl_ephemeris library 
    start = std::chrono::high_resolution_clock::now();
    mjdj2k_tdb = mjdj2k_tdb_0;
    while (mjdj2k_tdb <= 35000) {
        for (CentralBody central_body : central_bodies) {
            for (CentralBody tgt_body : target_bodies) {
                // Compute the position of the Sun w.r.t. the Moon
                std::array<double, 3> jpl_ephem_pos = compute_jpl_ephem_pos(mjdj2k_tdb, tgt_body, central_body); 
            }
        }

        mjdj2k_tdb += step; 
    }
    stop = std::chrono::high_resolution_clock::now();
    double duration_jpl_ephem = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() * 1e-6;

    std::cout << "CSPICE Runtime:    " << std::to_string(duration_cspice) << " sec\n"; 
    std::cout << "jpl_ephem Runtime: " << std::to_string(duration_jpl_ephem) << " sec\n"; 
    std::cout << "Speedup:           " << std::to_string(duration_cspice / duration_jpl_ephem) << "\n\n"; 
}

//--------------------------------------------------------------------------------------------------------------------------

int main() {
    // Load in the SPK kernel from https://ssd.jpl.nasa.gov/ftp/eph/planets/bsp/
    furnsh_c("src/de430_1850-2150.bsp");
    
    // Set inputs
    double mjdj2k_tdb = 0.0;
    double step = 1000; 
    std::array<CentralBody, 3> target_bodies{CentralBody::Sun, CentralBody::Earth, CentralBody::Moon}; 
    std::array<CentralBody, 4> central_bodies{CentralBody::SSB, CentralBody::Sun, CentralBody::Earth, CentralBody::Moon}; 

    // Run the accuracy test
    accuracy_test(mjdj2k_tdb, step, target_bodies, central_bodies);

    // Now compute runtimes
    compute_runtimes(mjdj2k_tdb, 100, target_bodies, central_bodies);
    return 0;
}
