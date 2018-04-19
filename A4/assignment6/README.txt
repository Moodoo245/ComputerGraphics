# Introduction to CS-341 Computer Graphics
GROUP: 24

## Assignment 6:

Using the Computer Graphics course theory slides here is how we solved each following problem:

#### Billboarding
- Implemented a billboard in draw_scene() with the color_shader so we could see how the code affected the plane.
- Used glBlendfunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) to render the transparency of the billboard.
- Edited createSunBillboardTexture() in texture.cpp with a fitting color of the glow plus a additional function calc_transparency(int row), int col, int width) that calculated the distance from center and set the transparency as a function of distance.
- Lastly we implemented the orientation of the billboard facing the eye. Calculated the normal of the billboard plane by subtracting the eye position from the sun position. The using trigonometry to calculate the different angles from the information in the normal. Thereafter scaling from radians to degrees.

#### Phong lighting model
-Implemented phong.vert and phong.frag using the course slides.
-phong.vert computes view, light, normal
-phong.frag computes r using the mirror equation we saw in the previous weeks and does phong shading
-Modified draw_scene() such that the celestial bodies(except earth) and the ship use phong shading
-normal matrix is the transpose of the inverse of the modelview_matrix as seen in the course

#### Shading the earth
Using Phong lighting as a base, implemented earth shader according to assignment document steps:
- earth.vert is a copy of phong.vert.
- earth.frag computes color based on the four earth textures, with cloudiness (cloud luminance) interpolating between day color and cloud color, and daylight ( n.l ) interpolating between day and night.
- In solar_viewer.cpp, earth is rendered using the earth shader. Parameters are the same with phonng exept that each texture has to be properly binded.


Collaborators:
Justinas Sukaitis (33%)
Håvard Bjørnøy (33%)
Sebastian Chevaleyre (34%)
