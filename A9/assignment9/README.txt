# Introduction to CS-341 Computer Graphics
GROUP: 24

## Assignment 9:

Using the Computer Graphics course theory slides here is how we solved each following problem:

#### Perlin noise in 1D
First we located the location of the nearest lower and upper grid. (integer grids, so we just floored our input value x). 
Then using the hash function on out grids we could get a pseudorandom gradients. 
Thereafter evaluating the linear functions with the distance from the grid points. 
Lastly using the OpenGl mix()-function to interpolate with the weight from the blending_weight_poly. 

#### Fractional brownian motion in 1D
Using the function given in the notes, we just do a for loop over the octaves and sum up the partial fbms

#### Perlin noise in 2D
Directly apply the Perlin_Diagram.pdf, again using OpenGl mix()-function to interpolate with the weight from the blending_weight_poly.

#### Fractional brownian motion in 2D
Same as 1d 

#### Turbulence in 2D
The turbulence function is exactly the same as the fbm, except that we sum up abs values

#### Textures
This what very straightforward since the description was very accurate. 
For the map we had to check if the altitude s was under the water level. 
Then all the textures where a interpolation between to colors, where the wood and marble had an element of turbulence. 
The wood also had an enforced geometry, implemented with the sinus function. 

#### Terrain
We map (gx, gy) to a square [0.5, 0.5]^2 in the xy plane to find the correct (x,y) coordinates
Then we apply (gx, gy) in height map to get the z coord. If it's lower than WATER_LEVEL, then we set it to water level
In the 2nd loop we create for each vertex 2 triangles as asked in the pdf and add them to the faces collection of triangles
After having done the terrain.frag and compute normals (which was basically copy paste from previous assignments), 
p.s.: I adjusted grid size to (256, 256) to make the resolution a bit better


Collaborators:
Justinas Sukaitis (34%)
Håvard Bjørnøy (33%)
Sebastian Chevaleyre (33%)
