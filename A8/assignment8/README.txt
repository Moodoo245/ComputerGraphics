# Introduction to CS-341 Computer Graphics
GROUP: 24

## Assignment 8:

Using the Computer Graphics course theory slides here is how we solved each following problem:

#### Grammar expansion
Using the `rules` unordered dict we checked if a symbol has a expansion rule to it. It not we just return the symbol as is. Also made the structure which it passes through the symbols and expand one the sentence in iterations

#### Drawing
translated the symbols to drawing actions, tracking the position the of the "pen", current direction, and saving previous states after branching makes us able to draw the tree. If any unknown symbol(or F) is in the rule it is understood as drawing a line in the direction it is facing. With this the deterministic approach now works.



Collaborators:
Justinas Sukaitis (33%)
Håvard Bjørnøy (34%)
Sebastian Chevaleyre (33%)
