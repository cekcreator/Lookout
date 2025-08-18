//
// Created by Caleb Kumar on 8/17/25.
//
#pragma once

#ifndef MERCURY_H
#define MERCURY_H
#include "../PlanetBase.h"
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"


using namespace ci;

namespace Planet
{

    class Mercury : public PlanetBase
    {
    public:
        explicit Mercury(const dvec3& position_Ws, double radius_km, double mass_kg, double scaleFactor)
            : PlanetBase(position_Ws, radius_km, mass_kg)
        {
            scaleFactor = scaleFactor;
            radius_Ws = radius_Ws * scaleFactor;
        }

        void draw() override
        {
            gl::color(1, 0, 0, 1);
            std::cout << radius_Ws << std::endl;
            gl::drawSphere(position_Ws, radius_Ws);
        }

        void update() override {}

        dvec3 getPlanetPosition_Ws() override
        {
            return position_Ws;
        }
    };
} // namespace Planet


#endif //MERCURY_H
