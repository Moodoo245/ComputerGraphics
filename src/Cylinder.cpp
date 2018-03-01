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

#include "Cylinder.h"
#include "SolveQuadratic.h"

#include <array>
#include <cmath>

//== IMPLEMENTATION =========================================================

bool
Cylinder::
intersect(const Ray&  _ray,
          vec3&       _intersection_point,
          vec3&       _intersection_normal,
          double&     _intersection_t) const
{

    const vec3 &dir = _ray.direction;
    const vec3   oc = _ray.origin - center;

    const double a = dot(dir, dir) - dot(dir, axis)*dot(dir, axis);
    const double b = dot(dir, oc) - dot(dir, axis)*dot(oc, axis);
    const double c = (dot(oc, oc)-radius*radius) - dot(oc, axis)*dot(oc, axis);
    
    std::array<double, 2> t;
    size_t nsol = solveQuadratic(a, 2*b, c, t);

    _intersection_t = NO_INTERSECTION;

    // Find the closest valid solution (in front of the viewer)
    for (size_t i = 0; i < nsol; ++i) {
      if (t[i] > 0){
	const vec3 point = _ray(t[i]);
	if (std::abs(dot(point - center,axis)) <= height/2) _intersection_t = std::min(_intersection_t, t[i]);
      }
    }

    if (_intersection_t == NO_INTERSECTION) return false;

    _intersection_point  = _ray(_intersection_t);
    _intersection_normal = (_intersection_point - center-dot(_intersection_point - center,axis)*axis) / radius;

    return true;
}
