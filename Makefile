all:
	cmake --preset=${JPL_EPHEM_PRESET} && cmake --build --preset=${JPL_EPHEM_PRESET} -j${NUM_COMPILE_CORES}

clean:
	rm -rf build
