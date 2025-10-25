//
// Created by Caleb Kumar on 8/17/25.
//
#pragma once

#ifndef URANUS_H
#define URANUS_H
#include "../PlanetBase.h"
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"

using namespace ci;

namespace Planet
{

    class Uranus : public PlanetBase
    {
      public:
        gl::BatchRef   uranus;
        gl::TextureRef uranusTexture;
        explicit Uranus(double distFromSun, double radius_km, double mass_kg)
            : PlanetBase(distFromSun, radius_km, mass_kg)
        {
            uranusTexture = gl::Texture::create(loadImage(ci::app::loadAsset("uranus.jpg")));
        }

        void update() override
        {
            auto shader = gl::ShaderDef().texture().lambert();
            auto glsl   = gl::getStockShader(shader);
            auto sphere = geom::Sphere().radius(radius_Ws).center(position_Ws);
            uranus      = gl::Batch::create(sphere, glsl);
        }

        void draw() override
        {
            uranusTexture->bind(0);
            uranus->draw();
        }

        dvec3 getPlanetPosition_Ws() override { return position_Ws; }
    };
} // namespace Planet

#endif // URANUS_H
