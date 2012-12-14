//
//  Location.cpp
//  broc
//
//  Created by Shu Chiun Cheah on 4/13/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#include "Location.h"

//
// constructor/destructor
//
Location::Location(double lat, double lon)
: latitude(lat)
, longitude(lon)
{
    
}

Location::~Location()
{
    
}

//
// pre-defined locations
//
Location Location::SanFrancisco()
{
    return Location(37.78991830, -122.41261368);
}