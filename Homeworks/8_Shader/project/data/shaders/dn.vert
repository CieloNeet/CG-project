#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec3 aTangent;

out VS_OUT {
    vec3 WorldPos;
    vec2 TexCoord;
    mat3 TBN;
} vs_out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform sampler2D displacementmap;
uniform float displacement_coefficient;

void main()
{
    // TODO HW8 - 0_displacement_normal | calculate displacement
    vec3 Displacement=texture(displacementmap,aTexCoord).rgb;
    //Displacement = 1.0f * Displacement + vec3(1.0,1.0,1.0);
    float displacement=texture(displacementmap,aTexCoord).r;
    float deepth=displacement_coefficient*displacement;
    //vec4 worldPos = model * vec4(aPos+displacement_coefficient*Displacement, 1.0);
    //vec4 worldPos = model * vec4(aPos + vec3(0.0, displacement_coefficient * displacement, 0.0), 1.0);
    vec4 worldPos = model * vec4(aPos + deepth*aNormal, 1.0);
    vs_out.WorldPos = worldPos.xyz /worldPos.w;
	
    vs_out.TexCoord = aTexCoord;
	
	mat3 normalMatrix = transpose(inverse(mat3(model)));
	
    // TODO HW8 - 0_displacement_normal | calculate TBN
    vec3 N = normalize(normalMatrix * aNormal);
    vec3 T = normalize(normalMatrix * aTangent);
	T = normalize(T - dot(T, N) * N);
    vec3 B = cross(T, N);
	vs_out.TBN = mat3(T, B, N);

    gl_Position = projection * view * worldPos;
}
