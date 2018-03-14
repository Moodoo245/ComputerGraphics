# Introduction to CS-341 Computer Graphics
GROUP: 23

Assignment 2:

Using the Computer Graphics course theory slides here is how we solved each following problem:
  Ambient lighting:
    This is a simple multiplication of the ambiance global constant and the material ambient color property.

    Diffuse lighting:

    Specular lighting:

    Shadows:
      Just like explained in the pdf, the shadows are just the ambient light. We only add the specular and diffuse
      lighting if the 'shadow ray' does not intersect.

    Reflections:
      Lastly the reflections are calculated by first checking the material mirror property.
      If it's not null and we haven't reached max reflection depth then we calculate the
      reflection color by recursion. For the recursion we create a new ray, which has origin =
      intersection point and direction = reflect of the old ray. We add a small amount to the origin point so
      that we wouldn't have the 'acne' which was described in the slides.


Collaborators and percentage of workload:
Håvard Bjørnøy (33%)
Justinas Sukaitis (33%)
Sebastien Chevaleyre (34%)
