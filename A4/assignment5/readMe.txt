# Introduction to CS-341 Computer Graphics
GROUP: 24

### Assignment 3:

Using the Computer Graphics course theory slides here is how we solved each following problem:

	Placing objects in the scene:
		update_body_positions():
		Since the angle_orbit is cumulating, the new position is just rotation over Y axis with the new angle_orbit value. 
		We iterate over every planet (moon is a satelite) to update its position by rotating over 
		the y axis and then all is left is to translate the moon's position with earth's position first and then rotate it
		just as we do with every other celestial body.
	
	Placing the eye in the scene:
		paint():
		