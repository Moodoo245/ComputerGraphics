//=============================================================================
//
//   Exercise code for the lecture "Introduction to Computer Graphics"
//     by Prof. Mario Botsch, Bielefeld University
//
//   Copyright (C) by Computer Graphics Group, Bielefeld University
//
//=============================================================================

#version 140

in vec3 v2f_normal;
in vec2 v2f_texcoord;
in vec3 v2f_light;
in vec3 v2f_view;

out vec4 f_color;

uniform sampler2D day_texture;
uniform sampler2D night_texture;
uniform sampler2D cloud_texture;
uniform sampler2D gloss_texture;
uniform bool greyscale;

const float shininess = 20.0;
const vec3  sunlight = vec3(1.0, 0.941, 0.898);

void main()
{
    vec3 r =  normalize((2.0 * dot(v2f_normal,v2f_light)) * v2f_normal - v2f_light);
    float cloudiness = texture(cloud_texture, v2f_texcoord).g;
    float daylight = max(dot(v2f_normal, v2f_light),0.0);

    // compute day color
    vec3 m_s = vec3(1.0,1.0,1.0);
    vec3 day_color = (0.2 * sunlight) * texture(day_texture, v2f_texcoord).rgb;
	if(dot(v2f_normal, v2f_light) > 0) {
		day_color += sunlight * texture(day_texture, v2f_texcoord).rgb * dot(v2f_normal, v2f_light);
	
		if(dot(r, v2f_view) > 0 && texture(gloss_texture, v2f_texcoord).r > 1e-6) day_color += (1.0 - cloudiness) * sunlight * m_s * pow(dot(r, v2f_view), shininess);
    }
    
    // compute cloud color
    vec3 cloud_color = (0.2 * sunlight) * texture(cloud_texture, v2f_texcoord).rgb;
	if(dot(v2f_normal, v2f_light) > 0) cloud_color += sunlight * texture(cloud_texture, v2f_texcoord).rgb * dot(v2f_normal, v2f_light);
    
    // compute day-cloud color
    vec3 dc_color = cloudiness * cloud_color + (1 - cloudiness) * day_color;

    // compute night color
    vec3 night_color = (1-cloudiness)*texture(night_texture, v2f_texcoord).rgb;

    // result
    vec3 color = daylight * dc_color + (1.0 - daylight) * night_color;

    // convert RGB color to YUV color and use only the luminance
    if (greyscale) color = vec3(0.299*color.r+0.587*color.g+0.114*color.b);

    // add required alpha value
    f_color = vec4(color, 1.0);
}
