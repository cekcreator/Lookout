#ifndef SUN_H
#define SUN_H
#pragma once
#include "../PlanetBase.h"
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"


using namespace ci;

namespace Planet
{

    class Sun : public PlanetBase
    {
      public:
        explicit Sun(const dvec3& position_Ws, double radius_km, double mass_kg)
            : PlanetBase(position_Ws, radius_km, mass_kg)
        {
        }

        void draw() override
        {
            gl::color(1, 0, 0, 1);
            gl::drawSphere(position_Ws, static_cast<float>(radius_Ws));
        }

        void update() override {}

        dvec3 getPlanetPosition_Ws() override
        {
            return position_Ws;
        }

    };
} // namespace Planet
#endif //SUN_H