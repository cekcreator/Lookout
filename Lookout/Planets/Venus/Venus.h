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
        gl::BatchRef   venus;
        gl::TextureRef venusTexture;
        explicit Venus(double distFromSun, double radius_km, double mass_kg)
            : PlanetBase(distFromSun, radius_km, mass_kg)
        {
            venusTexture = gl::Texture::create(loadImage(ci::app::loadAsset("venus.jpg")));
            position_Ws = dvec3(55.0, 0.0, 0.0);
            radius_Ws = 3.0;
        }

        void update() override
        {
            auto shader = gl::ShaderDef().texture().lambert();
            auto glsl   = gl::getStockShader(shader);
            auto sphere = geom::Sphere().radius(radius_Ws).center(position_Ws);
            venus       = gl::Batch::create(sphere, glsl);
        }

        void draw() override
        {
            venusTexture->bind(0);
            venus->draw();
        }

        dvec3 getPlanetPosition_Ws() override { return position_Ws; }
        double getPlanetRadius_Ws() override
        {
            return radius_Ws;
        }
    };
} // namespace Planet

#endif // VENUS_H
