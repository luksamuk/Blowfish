#
# Blowfish C++ implementation
#
# CC0 - PUBLIC DOMAIN
# This work is free of known copyright restrictions.
# http://creativecommons.org/publicdomain/zero/1.0/
#

CXX = g++ --std=c++11

all:
	$(CXX) blowfish.cpp main.cpp -o blowfish