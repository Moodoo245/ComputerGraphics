# Introduction to CS-341 Computer Graphics
GROUP: 24

## Assignment 11:

Using the Computer Graphics course guidelines here is how we solved each following problem:

#### Extracting control points
We use the fact that control points are simply derived from the polygon vertices using barycentric coordinates, or simply the middle of two other control points.
The only difficulty was that the provided cp vector had redundant points at the end.

#### Evaluating points on a piecewise Bézier curve
We use the de Casteljau algorithm on a matrix (could be done simply by overwriting one vector but the derivation are more explicit this way).
The edge case t=1 is covered but should not happen in Solarviewer.

#### Evaluating a tangent on a piecewise Bézier curve
Using the same code as the point evaluation but with reading the tangent on the matrix as advised in the guidelines.
The chain rule is used to cope for the t parameter ( p(t) = b(s(t)) => p'(t) = s'(t)*b'(s(t) ).

#### Placing the ship on the path
We know that the frame F is the local coordinates system of the ship, so we look for the rotation marix M so that Id*M = F, thus M = F ( mat4(xyzToFrame) ).

#### Constant space velocity
We know that dp = p'(t)*dt, therefore dt = 1/norm(p'(t)) * norm(dp) = 1/norm(tangent)*dS.

#### Making the eye follow the spaceship
We used same transformation as in placing the ship on the path (changing coordinates system).


Collaborators:
Justinas Sukaitis (34%)
Håvard Bjørnøy (33%)
Sebastian Chevaleyre (33%)
