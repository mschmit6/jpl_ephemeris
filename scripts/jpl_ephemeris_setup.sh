if [ -z "${JPL_EPHEMERIS}" ]; then
  echo "Error: JPL_EPHEMERIS must be set before running the jpl_ephemeris_setup shell script".
  exit 1
fi

get_num_compile_cores() {
    if [ "$(uname)" == "Darwin" ]; then
        # On Mac OS X
        num_cores=$(sysctl -n hw.logicalcpu )
    else
        # On Linux
        num_cores=$(nproc)
    fi
    
    if (( num_cores > 1 )); then
        echo $((num_cores - 1))
    else
        echo 1
    fi
}

# Set the number of cores as one less than the max number of cores
export NUM_COMPILE_CORES=$(get_num_compile_cores)

# Set the CPLUS_INCLUDE_PATH
if [ -z "${JPL_EPHEM_PRESET}" ]; then
  echo "Error: JPL_EPHEM_PRESET must be set in your shell script to either release or debug prior to running the jpl_ephemeris_setup shell script".
  exit 1
fi

# Set the CPLUS_INCLUDE_PATH environment variable to include the jpl_ephemeris
if [ -z "${CPLUS_INCLUDE_PATH}" ]; then
  export CPLUS_INCLUDE_PATH=$JPL_EPHEMERIS/build/${JPL_EPHEM_PRESET}/include
else 
  export CPLUS_INCLUDE_PATH=$CPLUS_INCLUDE_PATH:$JPL_EPHEMERIS/build/${JPL_EPHEM_PRESET}/include
fi

# Set the LIB environment variable to include the jpl_ephemeris
if [ -z "${LIB}" ]; then
  export LIB=$JPL_EPHEMERIS/build/${JPL_EPHEM_PRESET}/lib
else 
  export LIB=$LIB:$JPL_EPHEMERIS/build/${JPL_EPHEM_PRESET}/lib
fi

# Set the LD_LIBRARY_PATH environment variable to include the jpl_ephemeris
if [ -z "${LD_LIBRARY_PATH}" ]; then
  export LD_LIBRARY_PATH=$JPL_EPHEMERIS/build/${JPL_EPHEM_PRESET}/lib
else 
  export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$JPL_EPHEMERIS/build/${JPL_EPHEM_PRESET}/lib
fi

# Set the LIBRARY_PATH environment variable to include the jpl_ephemeris
if [ -z "${LIBRARY_PATH}" ]; then
  export LIBRARY_PATH=$JPL_EPHEMERIS/build/${JPL_EPHEM_PRESET}/lib
else 
  export LIBRARY_PATH=$LIBRARY_PATH:$JPL_EPHEMERIS/build/${JPL_EPHEM_PRESET}/lib
fi