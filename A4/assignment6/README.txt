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


#### Shading the earth



Collaborators:
Justinas Sukaitis (34%)
Håvard Bjørnøy (33%)
Sebastian Chevaleyre (33%)