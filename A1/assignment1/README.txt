# Introduction to CS-341 Computer Graphics
GROUP: 23

Assignment 1:
We used the slides in the class, the code from spheres.cpp as inspiration and cylinder_equations.txt. We used the knowledge about the explicit equation for the ray and derived implicit equations for the plane and cylinder. Combining these and solving for the unknown.

Plane:
The plane is a one-order polynomial, therefore the equations have one or zero solutions, making it pretty straightforward.
1. Check the dot product of the normal and raydirection to not divide with zero
2. calculate the t from the implicit plane and explicit ray equation
3. if the intersection is behind the image plane, don't include it
4. alter the intersectionvariables

Cylinder:
The cylinder is more complicated since it is a second degree polynomial. We used the solveQuadratic()-function to solve the equation. Do to this we sorted the terms by degree and stored them constants a,b and c. Then we solved with solveQuadratic(a,b, c, t), where t is the unknown variable. After solving the quadratic equation we eliminate the solutions that are outside the height constraint, behind the image plane. The nearest solution(the nearest intersection) is returned to the variable _intersection_point.

The derivation of the intersection equation is found in the pdf. 


Collaborators and percentage of workload:
Håvard Bjørnøy (33%)
Justinas Sukaitis (33%)
Sebastien Chevaleyre (34%)

