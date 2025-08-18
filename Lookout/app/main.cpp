#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include "../Planets/AllPlanets.h"
#include "../helpers/units.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstring>
#include <fstream>
#include <sstream>

using namespace ci;
using namespace ci::app;

class Lookout : public App
{
    void draw() override;
    void update() override;
};

void Lookout::draw() // main
{
    gl::clear();

    CameraPersp cam;
    // look from then look at
    cam.lookAt(vec3(500, 500, 500), vec3(0, 0, 0));
    gl::setMatrices(cam);

    Planet::Sun sun(dvec3(0, 0, 0), units::sunRadius, 1.989e30);
    sun.draw();
    std::cout << sun.radius_Ws << std::endl;

    auto planets = getAllPlanets(sun);

    // for (const auto& planet : planets)
    // {
    //     std::cout << planet->getPlanetPosition_Ws() << std::endl;
    //     planet->draw();
    // }


}

void Lookout::update() {}

CINDER_APP(Lookout, RendererGl)