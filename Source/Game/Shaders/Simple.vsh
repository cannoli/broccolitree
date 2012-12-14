//
//  Simple.vsh
//  broc
//
//  Created by Shu Chiun Cheah on 3/10/12.
//  Copyright (c) 2012 Shunobi. All rights reserved.
//

attribute vec4 position;
attribute vec3 normal;

varying lowp vec4 colorVarying;

uniform mat4 modelViewProjectionMatrix;
uniform vec4 diffuseColor;
void main()
{
//    vec3 eyeNormal = normalize(normalMatrix * normal);
    vec3 eyeNormal = normalize(normal);
    vec3 lightPosition = vec3(0.4, 0.2, 1.0);
    
    float nDotVP = max(0.0, dot(eyeNormal, normalize(lightPosition)));
                 
    colorVarying = diffuseColor * nDotVP;
    
    gl_Position = modelViewProjectionMatrix * position;
}
