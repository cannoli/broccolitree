//
//  Location.h
//  broc
//
//  Created by Shu Chiun Cheah on 4/13/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#ifndef broc_Location_h
#define broc_Location_h

class Location
{
public:
    Location(double lat=37.78991830, double lon=-122.41261368);
    ~Location();

    double latitude;
    double longitude;
    
    static Location SanFrancisco();
};

#endif
