//
// Created by Caleb Kumar on 8/17/25.
//
#pragma once

#ifndef VENUS_H
#define VENUS_H
#include "../PlanetBase.h"
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"


using namespace ci;

namespace Planet
{

    class Venus final : public PlanetBase
    {
    public:
        explicit Venus(const dvec3& position_Ws, double radius_km, double mass_kg, double scaleFactor)
            : PlanetBase(position_Ws, radius_km, mass_kg, scaleFactor)
        {
        }

        void draw() override
        {
            gl::clear();
            gl::color(1, 0, 0, 1);
            gl::drawSphere(position_Ws, radius_Ws);
        }

        void update() override {}

        dvec3 getPlanetPosition_Ws() override
        {
            return position_Ws;
        }
    };
} // namespace Planet


#endif //VENUS_H
