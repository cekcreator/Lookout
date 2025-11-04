//
// Created by Caleb Kumar on 8/17/25.
//
#pragma once

#ifndef MARS_H
#define MARS_H
#include "../PlanetBase.h"
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"

using namespace ci;

namespace Planet
{

    class Mars : public PlanetBase
    {
      public:
        gl::BatchRef   mars;
        gl::TextureRef marsTexture;
        explicit Mars(double distFromSun, double radius_km, double mass_kg)
            : PlanetBase(distFromSun, radius_km, mass_kg)
        {
            marsTexture = gl::Texture::create(loadImage(ci::app::loadAsset("mars.jpg")));
            position_Ws = dvec3(105.0, 0.0, 0.0);
            radius_Ws = 2.75;
        }

        void update() override
        {
            auto shader = gl::ShaderDef().texture().lambert();
            auto glsl   = gl::getStockShader(shader);
            auto sphere = geom::Sphere().radius(radius_Ws).center(position_Ws);
            mars        = gl::Batch::create(sphere, glsl);
        }

        void draw() override
        {
            marsTexture->bind(0);
            mars->draw();
        }

        dvec3 getPlanetPosition_Ws() override
        {
            return position_Ws;
        }

        double getPlanetRadius_Ws() override
        {
            return radius_Ws;
        }
    };
} // namespace Planet

#endif // Mars_H
