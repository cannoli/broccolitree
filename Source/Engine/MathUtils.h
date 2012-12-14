//
//  MathUtils.h
//  broc
//
//  Created by Shu Chiun Cheah on 5/14/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

#ifndef broc_MathUtils_h
#define broc_MathUtils_h

extern float RandomFrac();
extern int Max(int firstNum, int secondNum);
extern unsigned int RandomWithinRange(unsigned int min, unsigned int max);
extern int RandomIntWithinPercent(int baseline, float percent, int min);
extern float RandomFloatWithinPercent(float baseline, float percent, float min);

#endif
