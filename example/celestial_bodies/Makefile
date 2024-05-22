CC = g++

CFLAGS_BASE = -std=c++17 -m64 -fPIC -Wno-psabi
CFLAGS_REL = -O3
CFLAGS_DBG = -g -Wall -Wextra

INCLUDE =
LDFLAGS = -ljpl_ephemeris

# Point the OBJS to the source file for the test
OBJS = src/celestial_bodies.o

# Set the name of the executable
EXEC = celestial_bodies.exe

# --- SHOULD not need to modify code beyond this line --- #

CFLAGS = $(CFLAGS_BASE) $(CFLAGS_REL)

all: $(EXEC)

debug:
	$(eval CFLAGS= $(CFLAGS_BASE) $(CFLAGS_DBG))

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

new:
	rm -rf src/*.o
	rm -f $(EXEC)
