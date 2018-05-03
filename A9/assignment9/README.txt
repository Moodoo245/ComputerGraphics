# Introduction to CS-341 Computer Graphics
GROUP: 24

## Assignment 9:

Using the Computer Graphics course theory slides here is how we solved each following problem:

#### Perlin noise in 1D
First we located the location of the nearest lower and upper grid. (integer grids, so we just floored our input value x). Then using the hash function on out grids we could get a pseudorandom gradients. Thereafter evaluating the linear functions with the distance from the grid points. Lastly using the OpenGl mix()-function to interpolate with the weight from the blending_weight_poly. 

#### Fractional brownian motion in 1D


#### Perlin noise in 2D


#### Fractional brownian motion in 2D


#### Turbulence in 2D


#### Textures
This what very straightforward since the description was very accurate. for the map we had to check if the altitude s was under the water level. Then all the textures where a interpolation between to colours, where the wood and marble had an element of turbulence. The wood also had an enforced geometry, implemented with the sinus function. 

#### Terrain



Collaborators:
Justinas Sukaitis (34%)
Håvard Bjørnøy (33%)
Sebastian Chevaleyre (33%)
