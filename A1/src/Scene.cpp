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
#include "Scene.h"

#include "Plane.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Mesh.h"

#include <limits>
#include <map>
#include <functional>
#include <stdexcept>

//-----------------------------------------------------------------------------

Image Scene::render()
{
  // allocate new image.
  Image img(camera.width, camera.height);

  // here comes the main ray tracing loop
  for (int x=0; x<int(camera.width); ++x)
  {
    for (int y=0; y<int(camera.height); ++y)
    {
      Ray ray = camera.primary_ray(x,y);

      // compute color by tracing this ray
      vec3 color = trace(ray, 0);

      // avoid over-saturation
      color = min(color, vec3(1, 1, 1));

      // store pixel color
      img(x,y) = color;
    }
  }

  // Note: compiler will elide copy.
  return img;
}

//-----------------------------------------------------------------------------

vec3 Scene::trace(const Ray& _ray, int _depth)
{
  // stop if recursion depth (=number of reflection) is too large
  if (_depth > max_depth) return vec3(0,0,0);

  // Find first intersection with an object. If an intersection is found,
  // it is stored in object, point, normal, and t.
  Object_ptr  object;
  vec3        point;
  vec3        normal;
  double      t;
  if (!intersect(_ray, object, point, normal, t))
  {
    return background;
  }

  // compute local Phong lighting (ambient+diffuse+specular)
  vec3 color = lighting(point, normal, -_ray.direction, object->material);


  /**
  * Compute reflections by recursive ray tracing:
  * - check whether `object` is reflective by checking its `material.mirror`
  * - check recursion depth
  */

  // check if the material is mirrorlike
  double a = object -> material.mirror;

  if( a > 0 && (_depth < max_depth)){
    vec3 reflected_color = vec3(0,0,0);
    //generate reflected ray, compute its color contribution, and mix it with
    //the color computed by local Phong lighting
    vec3 r = reflect(_ray.direction, normal);
    Ray reflect_ray = Ray(point + 1e-6 * normal, r);
    reflected_color = trace(reflect_ray, _depth+1);
    color = ((1 - a)* color + a * reflected_color);
    //the color computed by local Phong lighting (use `object->material.mirror` as weight)
    //check whether your recursive algorithm reflects the ray `max_depth` times
  }
  return color;
}

//-----------------------------------------------------------------------------

bool Scene::intersect(const Ray& _ray, Object_ptr& _object, vec3& _point, vec3& _normal, double& _t)
{
  double  t, tmin(Object::NO_INTERSECTION);
  vec3    p, n;

  for (const auto &o: objects) // for each object
  {
    if (o->intersect(_ray, p, n, t)) // does ray intersect object?
    {
      if (t < tmin) // is intersection point the currently closest one?
      {
        tmin = t;
        _object = o.get();
        _point  = p;
        _normal = n;
        _t      = t;
      }
    }
  }

  return (tmin != Object::NO_INTERSECTION);
}

vec3 Scene::lighting(const vec3& _point, const vec3& _normal, const vec3& _view, const Material& _material)
{

  /**
  * Compute the Phong lighting:
  * - start with global ambient contribution*/
  vec3 color = ambience * _material.ambient;
  /* - for each light source (stored in vector `lights`) add diffuse and specular contribution
  * - only add diffuse and specular light if object is not in shadow */
  for (Light _light : lights)
  {
    Ray _ray = Ray(_point + 1e-12 * _normal, _light.position - _point);
    Object_ptr  object;
    vec3        point;
    vec3        normal;
    double      t;

    if ( !(intersect(_ray, object, point, normal, t) &&
    (distance(_ray.origin, _light.position) > distance(_ray.origin, point))))
    {
      color += _light.color * (_material.diffuse*std::max(dot(_normal,_ray.direction),0.0) + _material.specular*pow(std::max(0.0,dot(mirror(_ray.direction, _normal),_view)), _material.shininess)); //TO MODIFY
    }
  }
  /* You can look at the classes `Light` and `Material` to check their attributes. Feel free to use
  * the existing vector functions in vec3.h e.g. mirror, reflect, norm, dot, normalize
  */

  // visualize the normal as a RGB color for now.
  //vec3 color = (_normal + vec3(1)) / 2.0;

  return color;
}

//-----------------------------------------------------------------------------

void Scene::read(const std::string &_filename)
{
  std::ifstream ifs(_filename);
  if (!ifs)
  throw std::runtime_error("Cannot open file " + _filename);

  const std::map<std::string, std::function<void(void)>> entityParser = {
    {"depth",      [&]() { ifs >> max_depth; }},
    {"camera",     [&]() { ifs >> camera; }},
    {"background", [&]() { ifs >> background; }},
    {"ambience",   [&]() { ifs >> ambience; }},
    {"light",      [&]() { lights .emplace_back(ifs); }},
    {"plane",      [&]() { objects.emplace_back(new    Plane(ifs)); }},
    {"sphere",     [&]() { objects.emplace_back(new   Sphere(ifs)); }},
    {"cylinder",   [&]() { objects.emplace_back(new Cylinder(ifs)); }},
    {"mesh",       [&]() { objects.emplace_back(new     Mesh(ifs, _filename)); }}
  };

  // parse file
  std::string token;
  while (ifs && (ifs >> token) && (!ifs.eof())) {
    if (token[0] == '#') {
      ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }

    if (entityParser.count(token) == 0)
    throw std::runtime_error("Invalid token encountered: " + token);
    entityParser.at(token)();
  }
}


//=============================================================================
