//
// Created by Caleb Kumar on 8/17/25.
//
#pragma once

#ifndef NEPTUNE_H
#define NEPTUNE_H
#include "../PlanetBase.h"
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"

using namespace ci;

namespace Planet
{

    class Neptune : public PlanetBase
    {
      public:
        gl::BatchRef   neptune;
        gl::TextureRef neptuneTexture;
        explicit Neptune(double distFromSun, double radius_km, double mass_kg)
            : PlanetBase(distFromSun, radius_km, mass_kg)
        {
            neptuneTexture = gl::Texture::create(loadImage(ci::app::loadAsset("neptune.jpeg")));
            position_Ws = dvec3(225.0, 0.0, 0.0);
            radius_Ws = 5.0;
        }

        void update() override
        {
            auto shader = gl::ShaderDef().texture().lambert();
            auto glsl   = gl::getStockShader(shader);
            auto sphere = geom::Sphere().radius(radius_Ws).center(position_Ws);
            neptune     = gl::Batch::create(sphere, glsl);
        }

        void draw() override
        {
            neptuneTexture->bind(0);
            neptune->draw();
        }

        dvec3 getPlanetPosition_Ws() override { return position_Ws; }
        double getPlanetRadius_Ws() override
        {
            return radius_Ws;
        }
    };
} // namespace Planet

#endif // NEPTUNE_H
