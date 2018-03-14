//=============================================================================
//
//   Exercise code for the lecture
//   "Introduction to Computer Graphics"
//   by Prof. Dr. Mario Botsch, Bielefeld University
//
//   Copyright (C) Computer Graphics Group, Bielefeld University.
//
//=============================================================================


//== INCLUDES =================================================================

#include "Plane.h"
#include <limits>
#include <cmath>

//== CLASS DEFINITION =========================================================


Plane::Plane(const vec3& _center, const vec3& _normal)
: center(_center), normal(_normal)
{
}


//-----------------------------------------------------------------------------


bool
Plane::
intersect(const Ray& _ray,
          vec3&      _intersection_point,
          vec3&      _intersection_normal,
          double&    _intersection_t ) const
{

	const vec3 &dir = _ray.direction;
    const vec3   oc = _ray.origin - center;

    // Check the dot product of the normal and raydirection to not divide with zero
    if (std::abs(dot(normal,dir)) < 1e-8) {
		return false;
		} else {
		// calculate the t from the implicit plane and explicit ray equation
    	double t = dot(normal, -oc)/dot(normal,dir);

    	_intersection_t = NO_INTERSECTION;
    	// if the intersection is behind the image plane, dont include it
    	if (t > 0) {
			_intersection_t = std::min(_intersection_t, t);
    	} else {
    		return false;
    	}
    	// alter the intersectionvariables and return true
    	_intersection_point  = _ray(_intersection_t);
    	_intersection_normal = normal;
    	return true;

		}

	// safety
    return false;
}


//=============================================================================
