# Introduction to CS-341 Computer Graphics
GROUP: 24

### Assignment 5:

Using the Computer Graphics course theory slides here is how we solved each following problem:

	Placing objects in the scene:
		update_body_positions():
		Since the angle_orbit is cumulating, the new position is just rotation over Y axis with the new angle_orbit value. 
		We iterate over every planet (moon is a satelite) to update its position by rotating over 
		the y axis and then all is left is to translate the moon's position with earth's position first and then rotate it
		just as we do with every other celestial body.
	
	Placing the eye in the scene:
		paint():
		The eye is oriented to be entered at the object and rotate around it given angle rotation from keyboard input. the distance from the object is given by input(and radius of object) except from the ship which have a constant distance from ship center. First we rotate around object like it is in origin to then translate out to the actual position.

	Rendering textures:
		draw_scene():
		As suggested in the pdf we used the sun rendering as an example for every celestial body, with using the color_shader. The same applies to the ship. The starry sky was implemented as a giant sphere, so it goes as a celestial body.

Collaborators:
Justinas Sukaitis (34%)
Håvard Bjørnøy (33%)
Sebastian Chevaleyre (33%)