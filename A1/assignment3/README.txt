# Introduction to CS-341 Computer Graphics
GROUP: 23

### Assignment 3:

Using the Computer Graphics course theory slides here is how we solved each following problem:






    Intersection with bounding boxes: 
We look at the legal values of parameter t for which the ray point origin+t*direction is between two parallel faces of the bounding box. This set of values is an interval for each pair of faces of the box. We then just have to look at the succesive intersection of all these intervals for positive values of t and check if the result is empty. If not empty, it means that there is an interval in which the ray is inside the 3 faces at the same time and therefore inside the box.


Collaborators and percentage of workload:
Håvard Bjørnøy
Justinas Sukaitis
Sebastien Chevaleyre
