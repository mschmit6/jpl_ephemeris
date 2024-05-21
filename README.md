# JPL Ephemeris Library
This library is a C++ implementation of the DE438 JPL ephemeris files. The coefficients for the Chebyshev polynomials 
are compiled into the C++ code to allow for much faster execution speeds than you get when computing the position 
of celestial bodies using NASA's CSPICE tool. You can modify the code to use a different DE table, if necessary. 

# Dependencies 
The JPL Ephemeris tool is designed to run on a unix or linux system (not windows). To properly compile the code, you will 
need the following:

- A C++ compiler that supports C++20
- CMake version >3.20

# Compiling the Library 
To properly compile the JPL Ephemeris library, you need to add the following to your shell script:

```
export JPL_EPHEM_PRESET="release"                     # Set the CMAKE Preset, either "release" or "debug" for now
export JPL_EPHEMERIS=/path/to/jpl_ephemeris
source $JPL_EPHEMERIS/scripts/jpl_ephemeris_setup.sh
```

You then navigate to the jpl_ephemeris directory, and run `make` at the command line (which simply neatly calls the CMake 
compile commands). 

# Running the Example
The example files all have a Makefile associated with them. Simply navigate to the example that you want to run and 
run the `make` command. This will generate a ".exe" file (the extension is purely to allow the .gitignore file to 
ignore any compiled objects). You can then run the compiled executable at the command line. For instance, for the 
moon_position example, you would run:

```
./moon_position.exe
```