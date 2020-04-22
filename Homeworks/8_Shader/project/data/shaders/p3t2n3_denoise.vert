#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

out VS_OUT {
    vec3 WorldPos;
    vec2 TexCoord;
    vec3 Normal;
} vs_out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform sampler2D displacementmap;
uniform float displacement_bias;
uniform float displacement_scale;
uniform float displacement_lambda;
uniform bool have_denoise;

void main()
{
    // TODO: HW8 - 1_denoise | denoise
    vec4 worldPos;
    if(!have_denoise){
       float eta = texture(displacementmap,aTexCoord).r;
       float deepth = displacement_lambda * (displacement_bias + displacement_scale * eta);
       worldPos = model * vec4(aPos - aNormal * deepth, 1.0);
    }
    else{
       worldPos = model * vec4(aPos , 1.0);
    }
    
	
	vs_out.WorldPos = worldPos.xyz / worldPos.w;
    vs_out.TexCoord = aTexCoord;
    vs_out.Normal = normalize(transpose(inverse(mat3(model))) * aNormal);
	
    gl_Position = projection * view * worldPos;
}
