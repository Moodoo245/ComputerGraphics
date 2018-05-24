//=============================================================================
//
//   Exercise code for the lecture "Introduction to Computer Graphics"
//     by Prof. Mario Botsch, Bielefeld University
//
//   Copyright (C) by Computer Graphics Group, Bielefeld University
//
//=============================================================================

#include "solar_viewer.h"
#include "glmath.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <array>

//=============================================================================


Solar_viewer::Solar_viewer(const char* _title, int _width, int _height)
    : GLFW_window(_title, _width, _height),
      unit_sphere_(50), //level of tesselation

      /** Use the following for better planet distances/sizes (but still not realistic)
      * To get a true-to-scale solar system, planets would be 20x smaller, and their distance to the sun would be ~11x larger
      * For example r_mercury/r_sun = 0.0034 and distance_mercury_to_sun/r_sun = 33.3
      **/
      //  sun_    (0.0f,              2.0f*(float)(M_PI)/26.0f,   1.0f,    0.0f),
      //  mercury_(2.0f*(float)(M_PI)/116.0f,  2.0f*(float)(M_PI)/58.5f,   0.068f, -3.1f),
      //  venus_  (2.0f*(float)(M_PI)/225.0f,  2.0f*(float)(M_PI)/243.0f,  0.174f,   -7.2f),
      //  earth_  (2.0f*(float)(M_PI)/365.0f,  2.0f*(float)(M_PI),        0.182f,   -9.8f),
      //  moon_   (2.0f*(float)(M_PI)/27.0f,   0.0f,  0.048f,   -0.5f),
      //  mars_   (2.0f*(float)(M_PI)/687.0f,  2.0f*(float)(M_PI)*24.0f/25.0f, 0.098f,-13.8f),
      //  stars_  (0.0f, 0.0f, 30.0f, 0.0f)

      // Even more unrealistic placement/sizing for nicer visualization.
      sun_    (0.0,              2.0*M_PI/26.0,   1.0f,    0.0f),
      mercury_(2.0*M_PI/116.0f,  2.0*M_PI/58.5,   0.075f, -1.4f),
      venus_  (2.0*M_PI/225.0f,  2.0*M_PI/243.0,  0.2f,   -2.2f),
      earth_  (2.0*M_PI/365.0f,  2.0*M_PI,        0.25,   -3.3f),
      moon_   (2.0*M_PI/27.0f,   0.0,  0.04,   -0.4f),
      mars_   (2.0*M_PI/687.0f,  2.0*M_PI*24.0/25.0, 0.15,-5.0f),
      stars_  (0.0, 0.0, 21.0, 0.0)
{
    // start animation
    timer_active_ = true;
    time_step_ = 1.0f/24.0f; // one hour

    // rendering parameters
    greyscale_     = false;
    fovy_ = 45;
    near_ = 0.01f;
    far_  = 20;

    // viewing angle
    planet_to_look_at_ = &sun_;
    x_angle_ = -90.0f;
    y_angle_ = 0.0f;
    dist_factor_ = 9.0f;

    ship_.pos_ = planet_to_look_at_->pos_ - vec4(0.0f, 0.0f, dist_factor_*planet_to_look_at_->radius_, 0.0f);
    ship_.direction_ = vec4(0.0f, 0.0f, 1.0f,0.0f);
    in_ship_ = false;

    srand((unsigned int)time(NULL));
}

//-----------------------------------------------------------------------------

void
Solar_viewer::
keyboard(int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        // Change view between the various bodies with keys 1..6
        if ((key >= GLFW_KEY_1) && (key <= GLFW_KEY_6)) {
            std::array<const Planet *, 6> bodies = { &sun_, &mercury_, &venus_, &earth_, &moon_, &mars_};
            in_ship_ = false;
            planet_to_look_at_ = bodies.at(key - GLFW_KEY_1);
        }
        switch (key)
        {
            // Key 7 switches to viewing the ship.
            case GLFW_KEY_7:
            {
                planet_to_look_at_ = NULL;
                in_ship_ = true;
                break;
            }

			case GLFW_KEY_8:
			{
				dist_factor_ -= 1.0;
				dist_factor_ = static_cast<float>(fmax(dist_factor_, -2.5));
				break;
			}

			case GLFW_KEY_9:
			{
				dist_factor_ += 1.0;
				dist_factor_ = static_cast<float>(fmin(dist_factor_, 20.0));
				break;
			}

            case GLFW_KEY_R:
            {
                randomize_planets();
                break;
            }

            case GLFW_KEY_G:
            {
                greyscale_ = !greyscale_;
                break;
            }

            case GLFW_KEY_W:
            {
                if (in_ship_)
                    ship_.accelerate(0.001f);
                break;
            }
            case GLFW_KEY_S:
            {
                if (in_ship_)
                    ship_.accelerate(-0.001f);
                break;
            }
            case GLFW_KEY_A:
            {
                if (in_ship_)
                    ship_.accelerate_angular(0.02f);
                break;
            }
            case GLFW_KEY_D:
            {
                if (in_ship_)
                    ship_.accelerate_angular(-0.02f);
                break;
            }

            case GLFW_KEY_C:
                curve_display_mode_ = CurveDisplayMode((int(curve_display_mode_) + 1) % int(CURVE_SHOW_NUM_MODES));
                break;
            case GLFW_KEY_T:
                ship_path_frame_.toggleParallelTransport();
                std::cout << (ship_path_frame_.usingParallelTransport() ? "enabled" : "diabled") << " parallel transport" << std::endl;
                break;

            case GLFW_KEY_LEFT:
            {
                y_angle_ -= 10.0;
                break;
            }

            case GLFW_KEY_RIGHT:
            {
                y_angle_ += 10.0;
                break;
            }

            case GLFW_KEY_DOWN:
            {
                x_angle_ += 10.0;
                break;
            }

            case GLFW_KEY_UP:
            {
                x_angle_ -= 10.0;
                break;
            }

            case GLFW_KEY_SPACE:
            {
                timer_active_ = !timer_active_;
                break;
            }

            case GLFW_KEY_P:
            case GLFW_KEY_KP_ADD:
            case GLFW_KEY_EQUAL:
            {
                time_step_ *= 2.0f;
                std::cout << "Time step: " << time_step_ << " days\n";
                break;
            }

            case GLFW_KEY_M:
            case GLFW_KEY_KP_SUBTRACT:
            case GLFW_KEY_MINUS:
            {
                time_step_ *= 0.5f;
                std::cout << "Time step: " << time_step_ << " days\n";
                break;
            }

            case GLFW_KEY_ESCAPE:
            {
                glfwSetWindowShouldClose(window_, GL_TRUE);
                break;
            }
        }
    }
}

// Update the current positions of the celestial bodies based their angular distance
// around their orbits. This position is needed to set up the camera in the scene
// (see Solar_viewer::paint)
void Solar_viewer::update_body_positions() {
	std::array<Planet *, 4> bodies = { &mercury_, &venus_, &earth_, &mars_ };
	for (int i = 0; i < 4; i++) {

		bodies[i]->pos_ = vec4(bodies[i]->distance_*cos(bodies[i]->angle_orbit_),
			bodies[i]->pos_.y,
			bodies[i]->distance_*(-sin(bodies[i]->angle_orbit_)),
			bodies[i]->pos_.w);
	}
	moon_.pos_ = vec4(earth_.pos_.x + moon_.distance_*cos(moon_.angle_orbit_),
		moon_.pos_.y,
		earth_.pos_.z + moon_.distance_*(-sin(moon_.angle_orbit_)),
		moon_.pos_.w);
}

//-----------------------------------------------------------------------------


void Solar_viewer::timer()
{
    if (timer_active_) {
        sun_.time_step(time_step_);
        mercury_.time_step(time_step_);
        venus_.time_step(time_step_);
        earth_.time_step(time_step_);
        moon_.time_step(time_step_);
        mars_.time_step(time_step_);
        update_body_positions();

        ship_.update_ship();

        // Desired ship speed (in units of Euclidean distance per animation
        // frame, not curve parameter distance). This is the (constant)
        // Euclidean step length we want the ship to make during each time step.
        const float ship_speed = 0.01;
        /** \todo
         * Assignment 11, Task 5
         * Advance the curve evaluation parameter "ship_path_param_"
         * so that the ship moves by (approximately) Euclidean distance
         * `ship_speed` in this frame.
         **/
        ship_path_param_ +=  ship_speed/(norm(ship_path_.tangent(ship_path_param_)));
        if (ship_path_param_ >= 1) { ship_path_param_ = 0; }
        vec3 tangent = ship_path_.tangent(ship_path_param_);
        ship_path_frame_.alignTo(tangent);
    }
}


//-----------------------------------------------------------------------------


void Solar_viewer::resize(int _width, int _height)
{
    width_  = _width;
    height_ = _height;
    glViewport(0, 0, _width, _height);
}

//-----------------------------------------------------------------------------


void Solar_viewer::initialize()
{
    // set initial state
    glClearColor(1,1,1,0);
    glEnable(GL_DEPTH_TEST);

    // Allocate textures
    sun_    .tex_.init(GL_TEXTURE0, GL_TEXTURE_2D, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT);
    mercury_.tex_.init(GL_TEXTURE0, GL_TEXTURE_2D, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT);
    venus_  .tex_.init(GL_TEXTURE0, GL_TEXTURE_2D, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT);

    earth_  .tex_.init(GL_TEXTURE0, GL_TEXTURE_2D, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT);
    earth_.night_.init(GL_TEXTURE1, GL_TEXTURE_2D, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT);
    earth_.cloud_.init(GL_TEXTURE2, GL_TEXTURE_2D, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT);
    earth_.gloss_.init(GL_TEXTURE3, GL_TEXTURE_2D, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT);

    moon_   .tex_.init(GL_TEXTURE0, GL_TEXTURE_2D, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT);
    mars_   .tex_.init(GL_TEXTURE0, GL_TEXTURE_2D, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT);
    stars_  .tex_.init(GL_TEXTURE0, GL_TEXTURE_2D, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT);
    ship_   .tex_.init(GL_TEXTURE0, GL_TEXTURE_2D, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT);

    sunglow_.tex_.init(GL_TEXTURE0, GL_TEXTURE_2D, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT);

    // Load/generate textures
    sun_    .tex_.loadPNG(TEXTURE_PATH "/sun.png");
    mercury_.tex_.loadPNG(TEXTURE_PATH "/mercury.png");
    venus_  .tex_.loadPNG(TEXTURE_PATH "/venus.png");

    earth_  .tex_.loadPNG(TEXTURE_PATH "/day.png");
    earth_.night_.loadPNG(TEXTURE_PATH "/night.png");
    earth_.cloud_.loadPNG(TEXTURE_PATH "/clouds.png");
    earth_.gloss_.loadPNG(TEXTURE_PATH "/gloss.png");

    moon_   .tex_.loadPNG(TEXTURE_PATH "/moon.png");
    mars_   .tex_.loadPNG(TEXTURE_PATH "/mars.png");
    stars_  .tex_.loadPNG(TEXTURE_PATH "/stars2.png");

    ship_.     load_model(TEXTURE_PATH "/spaceship.off");
    ship_   .tex_.loadPNG(TEXTURE_PATH "/ship.png");

    sunglow_.tex_.createSunBillboardTexture();

    // setup shaders
    color_shader_.load(SHADER_PATH "/color.vert", SHADER_PATH "/color.frag");
    phong_shader_.load(SHADER_PATH "/phong.vert", SHADER_PATH "/phong.frag");
    earth_shader_.load(SHADER_PATH "/earth.vert", SHADER_PATH "/earth.frag");
      sun_shader_.load(SHADER_PATH   "/sun.vert", SHADER_PATH   "/sun.frag");

    solid_color_shader_.load(SHADER_PATH "/solid_color.vert", SHADER_PATH "/solid_color.frag");

    ship_path_renderer_.initialize();
    ship_path_cp_renderer_.initialize();
    ship_path_frame_.initialize();

    ship_path_.set_control_polygon(control_polygon_, true);
    ship_path_renderer_.sample(ship_path_);
    ship_path_cp_renderer_.setPoints(ship_path_.bezier_control_points());
}
//-----------------------------------------------------------------------------


void Solar_viewer::paint()
{
    // clear framebuffer and depth buffer first
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	vec4      up = vec4(0, 1, 0, 0);
	vec4     eye;
	vec4  center;
	vec4 new_eye;

	// the you are in the ship we must see everything in the perspective of the ship
	if (in_ship_)
	{
		// put eye slightly above and behind spaceship
		eye = vec4(0, 0.012, -0.05, 1.0);
		center = vec4(ship_path_(ship_path_param_),1.0);
		new_eye = mat4::rotate_y(y_angle_)* mat4(ship_path_frame_.xyzToFrame())*eye;
		up = mat4::rotate_y(y_angle_)* mat4(ship_path_frame_.xyzToFrame())*up;

	}
	// else check which planet you're looking at
	else
	{
		// put eye on z-axis some distance planet_to_look_at
		eye = vec4(0, 0, dist_factor_*planet_to_look_at_->radius_, 1.0);
		center = planet_to_look_at_->pos_;
		// rotate in x and y around origin
		new_eye = mat4::rotate_y(y_angle_)*mat4::rotate_x(x_angle_)*eye;
		up = mat4::rotate_y(y_angle_)*mat4::rotate_x(x_angle_)*up;
	}

	// translate with respect to the center
	new_eye = mat4::translate(vec3(center))*new_eye;

	mat4    view = mat4::look_at(vec3(new_eye), vec3(center), vec3(up));

    /** \todo
     * Assignment 11, Task 6
     * Paste your viewing/navigation code from assignment 5 here, then
     * update the view matrix calculation for in_ship_ == true to account for the new
     * ship orientation (instead of using `ship_.pos_` and `ship_.angle_` to define the
     * eye coordinate system, you need to use `ship_path_(ship_path_param_)` and
     * `ship_path_frame_`.
     * Recall that we use a hard-coded viewing radius of 0.01f for the ship.
     */
    

	 // create billboardplane normal
	vec3     n_b = sun_.pos_ - vec3(new_eye);
	n_b = normalize(n_b);

	// update billboard angles
	billboard_x_angle_ = -90 + acos(n_b.y)*(180.0 / M_PI);
	billboard_y_angle_ = atan2(n_b.x, n_b.z)*(180.0 / M_PI);


    mat4 projection = mat4::perspective(fovy_, (float)width_/(float)height_, near_, far_);
    draw_scene(projection, view);

}


//-----------------------------------------------------------------------------


void Solar_viewer::draw_scene(mat4& _projection, mat4& _view)
{
    switch (curve_display_mode_) {
        case CURVE_SHOW_PATH_FRAME:
            ship_path_frame_.draw(solid_color_shader_, _projection * _view, ship_path_(ship_path_param_));
        case CURVE_SHOW_PATH_CP:
            solid_color_shader_.use();
            solid_color_shader_.set_uniform("modelview_projection_matrix", _projection * _view);
            solid_color_shader_.set_uniform("color", vec4(0.8, 0.8, 0.8, 1.0));
            ship_path_cp_renderer_.draw();
        case CURVE_SHOW_PATH:
            solid_color_shader_.use();
            solid_color_shader_.set_uniform("modelview_projection_matrix", _projection * _view);
            solid_color_shader_.set_uniform("color", vec4(1.0, 0.0, 0.0, 1.0));
            ship_path_renderer_.draw();
        default:
            break;
    }

    // the matrices we need: model, modelview, modelview-projection, normal
    mat4 m_matrix;
    mat4 mv_matrix;
    mat4 mvp_matrix;
    mat3 n_matrix;

    // the sun is centered at the origin and -- for lighting -- considered to be a point, so that is the light position in world coordinates
    vec4 light = vec4(0.0, 0.0, 0.0, 1.0); //in world coordinates
    // convert light into camera coordinates
    light = _view * light;

    static float sun_animation_time = 0;
    if (timer_active_) sun_animation_time += 0.01f;

    // render sun
    m_matrix = mat4::rotate_y(sun_.angle_self_) * mat4::scale(sun_.radius_);
    mv_matrix = _view * m_matrix;
    mvp_matrix = _projection * mv_matrix;
    sun_shader_.use();
    sun_shader_.set_uniform("modelview_projection_matrix", mvp_matrix);
    sun_shader_.set_uniform("t", sun_animation_time, true /* Indicate that time parameter is optional;
                                                             it may be optimized away by the GLSL    compiler if it's unused. */);
    sun_shader_.set_uniform("tex", 0);
    sun_shader_.set_uniform("greyscale", (int)greyscale_);
    sun_.tex_.bind();
    unit_sphere_.draw();

	//render stars
	m_matrix = mat4::translate(stars_.pos_)* mat4::rotate_y(stars_.angle_self_) * mat4::scale(stars_.radius_);
	mv_matrix = _view * m_matrix;
	mvp_matrix = _projection * mv_matrix;
	color_shader_.use();
	color_shader_.set_uniform("modelview_projection_matrix", mvp_matrix);
	color_shader_.set_uniform("tex", 0);
	color_shader_.set_uniform("greyscale", (int)greyscale_);
	stars_.tex_.bind();
	unit_sphere_.draw();
	
	// draw all spheres
	std::array<Planet *, 4> bodies = { &mercury_, &venus_, &mars_, &moon_ };
	for (int i = 0; i < 4; i++) {
		m_matrix = mat4::translate(bodies[i]->pos_)* mat4::rotate_y(bodies[i]->angle_self_) * mat4::scale(bodies[i]->radius_);
		mv_matrix = _view * m_matrix;
		mvp_matrix = _projection * mv_matrix;
		n_matrix = transpose(inverse(mat3(mv_matrix)));

		phong_shader_.use();
		phong_shader_.set_uniform("modelview_projection_matrix", mvp_matrix);
		phong_shader_.set_uniform("modelview_matrix", mv_matrix);
		phong_shader_.set_uniform("normal_matrix", n_matrix);
		phong_shader_.set_uniform("light_position", light);

		phong_shader_.set_uniform("tex", 0);
		phong_shader_.set_uniform("greyscale", (int)greyscale_);
		bodies[i]->tex_.bind();
		unit_sphere_.draw();
	}
	// draw earth
	m_matrix = mat4::translate(earth_.pos_) * mat4::rotate_y(earth_.angle_self_) * mat4::scale(earth_.radius_);
	mv_matrix = _view * m_matrix;
	mvp_matrix = _projection * mv_matrix;
	n_matrix = transpose(inverse(mat3(mv_matrix)));
	earth_shader_.use();
	earth_shader_.set_uniform("modelview_projection_matrix", mvp_matrix);
	earth_shader_.set_uniform("modelview_matrix", mv_matrix);
	earth_shader_.set_uniform("normal_matrix", n_matrix);
	earth_shader_.set_uniform("light_position", light);
	earth_shader_.set_uniform("day_texture", 0);
	earth_shader_.set_uniform("night_texture", 1);
	earth_shader_.set_uniform("cloud_texture", 2);
	earth_shader_.set_uniform("gloss_texture", 3);
	earth_shader_.set_uniform("greyscale", (int)greyscale_);
	earth_.night_.bind();
	earth_.cloud_.bind();
	earth_.gloss_.bind();
	earth_.tex_.bind();
	unit_sphere_.draw();
	// draw spaceship
	m_matrix = mat4::translate(ship_path_(ship_path_param_)) * mat4(ship_path_frame_.xyzToFrame()) * mat4::scale(ship_.radius_);
	mv_matrix = _view * m_matrix;
	mvp_matrix = _projection * mv_matrix;
	n_matrix = transpose(inverse(mat3(mv_matrix)));

	phong_shader_.use();
	phong_shader_.set_uniform("modelview_projection_matrix", mvp_matrix);
	phong_shader_.set_uniform("modelview_matrix", mv_matrix);
	phong_shader_.set_uniform("normal_matrix", n_matrix);
	phong_shader_.set_uniform("light_position", light);

	phong_shader_.set_uniform("tex", 0);
	phong_shader_.set_uniform("greyscale", (int)greyscale_);
	ship_.tex_.bind();
	ship_.draw();

    /** \todo
     * Assignment 11, Task 4:
     * Update the model matrix for your ship so that the ship is placed
     * on the `ship_path_` curve and oriented to face along the path's tangent
     * vector, `ship_path_frame_.t`. Also, the ship should be rotated so that
     * vertical axis agrees with `ship_path_frame_.up`.
     * Note, in its local coordinate system, the ship's forward direction is +z
     * and its up direction is +y.
    **/

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// draw billboard sunglow_
	m_matrix = mat4::translate(sun_.pos_)* mat4::rotate_y(billboard_y_angle_)* mat4::rotate_x(billboard_x_angle_) * mat4::scale(sun_.radius_ * 3);
	mv_matrix = _view * m_matrix;
	mvp_matrix = _projection * mv_matrix;
	color_shader_.use();
	color_shader_.set_uniform("modelview_projection_matrix", mvp_matrix);
	color_shader_.set_uniform("tex", 0);
	color_shader_.set_uniform("greyscale", (int)greyscale_);
	sunglow_.tex_.bind();
	sunglow_.draw();


	glDisable(GL_BLEND);

    // check for OpenGL errors
    glCheckError();
}

void Solar_viewer::randomize_planets()
{
    std::cout << "Randomizing planets..." << std::endl;
    float temp_dt = time_step_;
    time_step_ = (float)(rand()%20000);
    timer();
    time_step_ = temp_dt;
}


//=============================================================================
