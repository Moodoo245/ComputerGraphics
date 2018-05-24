#include "bezier.h"
#include <utility>
#include <cmath>
#include <array>

// Calculate a point one of the Bezier curve segments
// @param bp_offset  index into bezier_control_points_ of the first of four
//                   control points defining the Bezier segment we want to evaluate.
// @param t          parametric distance along the curve at which to evaluate
vec3 PiecewiseBezier::eval_bezier(int bp_offset, float t) const {
    /** \todo
     * Assignment 11, Task 2a:
     * Evaluate the cubic Bezier polygon defined by control points
     * bezier_control_points_[bp_offset..bp_offset + 4] at parameter t in [0, 1]
     **/
  std::vector <std::vector<vec3> > bezierMatrix(4, std::vector<vec3>(4, vec3(0,0,0)));
  for(int i = 0; i < 4; i++){
    bezierMatrix[0][i] = bezier_control_points_[bp_offset+i];
  }
  for(int i = 1; i < 4; i++){
    for(int j = 0; j < 4-i; j++){
      bezierMatrix[i][j] = (1-t)*bezierMatrix[i-1][j] + t*bezierMatrix[i-1][j+1];
    }
  }
  return bezierMatrix[3][0];
}

// Calculate a tangent at point at one of the Bezier curve segments
// @param bp_offset  index into bezier_control_points_ of the first of four
//                   control points defining the Bezier segment we want to compute
//                   the tangent at
// @param t          parametric distance along the curve at which to evaluate
vec3 PiecewiseBezier::eval_bezier_tangent(int bp_offset, float t) const {
    /** \todo
     * Assignment 11, Task 3a:
     * Evaluate the tangent vector at "t" of the cubic Bezier polygon
     * defined by control points bezier_control_points_[bp_offset..bp_offset + 4]
     * Recall, the tangent vector for a curve c(t) is given by the derivative of
     * this curve, c'(t).
     **/
    std::vector <std::vector<vec3> > bezierMatrix(3, std::vector<vec3>(4, vec3(0,0,0)));
    for(int i = 0; i < 4; i++){
      bezierMatrix[0][i] = bezier_control_points_[bp_offset+i];
    }
    for(int i = 1; i < 3; i++){
      for(int j = 0; j < 4-i; j++){
	bezierMatrix[i][j] = (1-t)*bezierMatrix[i-1][j] + t*bezierMatrix[i-1][j+1];
      }
    }
    return 3.0*(bezierMatrix[2][1]-bezierMatrix[2][0]);
}

std::vector<vec3> PiecewiseBezier::control_polygon_to_bezier_points(std::vector<vec3> const& cp) {
    std::vector<vec3> bezier_pts;
    /** \todo
     * Assignment 11, Task 1:
     * Determine the Bezier control points from the uniform cubic spline
     * control points "cp" as visualized in Lecture 12 slide 22.
     * Note, the last control point of one Bezier segment is shared with the first control
     * point of the next, and you should not generate the duplicate control points.
     * This means, Bezier segment 0 should be controlled by bezier_pts 0, 1, 2, 3;
     *                    segment 1 should be controlled by bezier_pts 3, 4, 5, 6;
     *                    segment 2 should be controlled by bezier_pts 6, 7, 8, 9;
     * and so on.
     **/
    size_t numSegments = cp.size()-3;
    bezier_pts.resize(3*numSegments + 1 );

    for(int i = 0; i < numSegments-1; i++) {
      bezier_pts[3*i+2] = (cp[i] + 2.0*cp[i+1]) / 3.0;
      bezier_pts[3*i+4] = (cp[i+2] + 2.0*cp[i+1]) / 3.0;
      bezier_pts[3*i+3] = (bezier_pts[3*i+2] + bezier_pts[3*i+4]) / 2.0; 
    }
    bezier_pts[3*numSegments - 4] = (cp[numSegments-2] + 2.0*cp[numSegments-1]) / 3.0;
    bezier_pts[3*numSegments - 2] = (2.0*cp[numSegments-1] + cp[0]) / 3.0;
    bezier_pts[3*numSegments - 3] = (bezier_pts[3*numSegments - 4] + bezier_pts[3*numSegments - 2]) / 2.0;
    bezier_pts[1] = (cp[1] + 2.0*cp[0]) / 3.0;
    bezier_pts[3*numSegments - 1] = (cp[numSegments-1] + 2.0*cp[0]) / 3.0;
    bezier_pts[0] = (bezier_pts[1] + bezier_pts[3*numSegments - 1]) / 2.0;
    bezier_pts[3*numSegments] = bezier_pts[0];
    
    return bezier_pts;
}

vec3 PiecewiseBezier::eval_piecewise_bezier_curve(float t) const {
    /** \todo
     *  Assignment 11, Task 2b:
     *  The argument t is in the interval [0, 1] which corresponds to the whole curve.
     *  The whole curve is defined by piecewise Bezier curves, which are each in turn
     *  parameterized by t_s in [0, 1]. Select appropriate control points and map the value t
     *  such that you evaluate the correct point on the correct Bezier segment. Note that
     *  the current code only evaluates the very first Bezier segment.
     */
  int n = num_segments();
  int offset = floor(n*t);
  return eval_bezier(3*offset,n*(t-offset/((float)n)));
}

vec3 PiecewiseBezier::operator()(float t) const {
    return eval_piecewise_bezier_curve(t);
}

vec3 PiecewiseBezier::tangent(float t) const {
    /** \todo
     *  Assignment 11, Task 3b:
     *  The argument t is in the interval [0, 1] which corresponds to the whole curve.
     *  The whole curve is defined by piecewise Bezier curves, which are each in turn
     *  parameterized by t_s in [0, 1]. Select appropriate control points and map the value t
     *  such that you evaluate the correct point on the correct Bezier segment. Note that
     *  the current code only evaluates the very first Bezier segment.
     *  Also, remember to use the chain rule when computing the tangent!
     */
  int n = num_segments();
  int offset = floor(n*t);
  return n*eval_bezier_tangent(3*offset,n*(t-offset/((float)n)));
}

void PiecewiseBezier::set_control_polygon(const std::vector<vec3> &control_polygon, bool loop) {
    control_polygon_ = control_polygon;
    if(loop) {
        control_polygon_.push_back(control_polygon[0]);
        control_polygon_.push_back(control_polygon[1]);
        control_polygon_.push_back(control_polygon[2]);
    }

    bezier_control_points_ = control_polygon_to_bezier_points(control_polygon_);
}
