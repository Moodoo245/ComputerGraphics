//=============================================================================
//
//   Exercise code for the lecture "Introduction to Computer Graphics"
//     by Prof. Mario Botsch, Bielefeld University
//
//   Copyright (C) by Computer Graphics Group, Bielefeld University
//
//=============================================================================

#version 140

uniform vec3 light_position; // Eye-space light position

in vec3  v2f_ec_vertex;
in vec3  v2f_normal;
in float v2f_height;

out vec4 f_color;

const vec3  sunlight = vec3(1.0, 0.941, 0.898);
// Small perturbation to prevent "z-fighting" on the water on some machines...
const float terrain_water_level    = -0.03125 + 1e-6;
const vec3  terrain_color_water    = vec3(0.29, 0.51, 0.62);
const vec3  terrain_color_mountain = vec3(0.8, 0.5, 0.4);
const vec3  terrain_color_grass    = vec3(0.33, 0.43, 0.18);

void main()
{
	const vec3 ambient = 0.2 * sunlight; // Ambient light intensity
	float height = v2f_height;

    /**
	 * \todo Compute the terrain color ("material") and shininess based on the height as
	 * described in the handout.
	 *
	 * Water:
	 *		color = terrain_color_water
	 *		shininess = 8.0
	 * Ground:
	 *		color = interpolate between terrain_color_grass and terrain_color_mountain, weight is (height - terrain_water_level)*2
	 * 		shininess = 0.5
     */

	vec3 material;
	float shininess;

	if(v2f_height <= terrain_water_level) {
		material = terrain_color_water;
		shininess = 8.0;
	}else{
		material = mix(terrain_color_grass, terrain_color_mountain, 2*(v2f_height - terrain_water_level));
		shininess = 0.5;
	}


	

    /**
	 * \todo Paste your Phong fragment shading code from assignment 6/7 here,
	 * altering it to use the terrain color as the ambient, diffuse, and
	 * specular materials.
     */

	vec3 color = material * ambient;

	vec3 v2f_light = normalize(light_position - v2f_ec_vertex);
	vec3 v2f_view = normalize(-v2f_ec_vertex);	

	vec3 light_ray = v2f_ec_vertex - light_position;
	

	vec3 r =  normalize((2.0 * dot(v2f_normal,v2f_light)) * v2f_normal - v2f_light);
	
	if(dot(v2f_normal, v2f_light) > 0) {
		color += sunlight * material * dot(v2f_normal, v2f_light);
	
		if(dot(r, v2f_view) > 0) color += sunlight * material * pow(dot(r, v2f_view), shininess);
	
	}	
	
	f_color = vec4(color, 1.0);
}
