#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <sstream>

using namespace ci;
using namespace ci::app;

namespace units
{
    constexpr double G          = 6.67430e-11;
    constexpr double PI         = 3.14159265358979323846;
    constexpr double c          = 299792458.0; // m/s
    constexpr double solarMass  = 1.989e30;
    constexpr double M          = solarMass * 4297000.0f;
    constexpr double r_s_m      = 2 * G * M / (c * c);
    constexpr float  lightMtoPx = 1.0f / float(c);
    constexpr float  lightPxToM = 1.0f / lightMtoPx;
    constexpr float  c_px       = float(c) * lightMtoPx;
}; // namespace units

class Lookout : public App
{
    void draw() override;
    void update() override;
};

void Lookout::draw() // main
{
}

void Lookout::update()
{
}

CINDER_APP(Lookout, RendererGl)