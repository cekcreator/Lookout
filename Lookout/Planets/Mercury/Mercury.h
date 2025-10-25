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
        gl::BatchRef   mercury;
        gl::TextureRef mercuryTexture;

        explicit Mercury(double distFromSun, double radius_km, double mass_kg)
            : PlanetBase(distFromSun, radius_km, mass_kg)
        {
            mercuryTexture = gl::Texture::create(loadImage(ci::app::loadAsset("sun.jpg")));
        }

        void update() override
        {
            auto shader = gl::ShaderDef().texture().lambert();
            auto glsl   = gl::getStockShader(shader);
            auto sphere = geom::Sphere().radius(radius_Ws).center(position_Ws);
            mercury     = gl::Batch::create(sphere, glsl);
        }

        void draw() override
        {
            mercuryTexture->bind(0);
            mercury->draw();
        }

        dvec3 getPlanetPosition_Ws() override { return position_Ws; }
    };
} // namespace Planet

#endif // MERCURY_H
