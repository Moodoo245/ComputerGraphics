# Introduction to CS-341 Computer Graphics
GROUP: 24

### Assignment 3:

Using the Computer Graphics course theory slides here is how we solved each following problem:

    Compute normals:
We first initialise the vertices so we can calculate the the vertices normal while looping through the triangles. By adding that one triangles normal contribution to the corner vertices with the angle weight. This way we only iterate through every triangle once. Afterwards we iterate through the vertices to normalize them.


    Ray-Triangle intersection:
      We find the intersection in 2step process. First we simplify the triangle by perceiving it just as if it
      was a plane, for this we take any point of the 3 points of the triangle and the norm of the triangle.

      After this we already have the t, the normal of the intersection and most importantly the point of
      the intersection.

      Now we do the 2nd step where as shown in the course, by calculating the areas of the triangle between the
      intersection point, we find the Barycentric coordinates i.e. a,b,c. If any of these are 0, it means our
      intersection point is not in the triangle else we intersected with the triangle.

      Finally as asked we check the draw_mode_ to select which shading to apply i.e. which normal we return
      for the specific point.



    Intersection with bounding boxes:
We look at the legal values of parameter t for which the ray point origin+t*direction is between two parallel faces of the bounding box. This set of values is an interval for each pair of faces of the box. We then just have to look at the succesive intersection of all these intervals for positive values of t and check if the result is empty. If not empty, it means that there is an interval in which the ray is inside the 3 faces at the same time and therefore inside the box.


Collaborators and percentage of workload:
Håvard Bjørnøy 33%
Justinas Sukaitis 34%
Sebastien Chevaleyre 33%
