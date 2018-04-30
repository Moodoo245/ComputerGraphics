# Introduction to CS-341 Computer Graphics
GROUP: 24

## Assignment 7:

Using the Computer Graphics course theory slides here is how we solved each following problem:

#### Building projection and view matrices for shadow cube map
We created projection matrix with the perspective function.
The view matrix was constructed by transforming the light position into eye coord. Thereafter defining up vector and where to look in eye coordinates by checking which cube face is activated. Then use look_at function to define the lights view.


#### Shadowmap
Calculate the norm of the vector

#### Phong shadow
We modify the assignement 6 code so that it doesn't do the ambient and does the specular and diffused only if it is not obstructed i.e. 
the length from the light source to the vertex is shorter than the value in the shadowmap. Not forgetting to multiply so that we don't have 
any shadow acne. 

Collaborators:
Justinas Sukaitis (33%)
Håvard Bjørnøy (34%)
Sebastian Chevaleyre (33%)
