//
// Created by Caleb Kumar on 8/17/25.
//
#pragma once

#ifndef JUPITER_H
#define JUPITER_H
#include "../PlanetBase.h"
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"


using namespace ci;

namespace Planet
{

    class Jupiter final : public PlanetBase
    {
    public:
        gl::BatchRef   jupiter;
        gl::TextureRef jupiterTexture;
        explicit Jupiter(double distFromSun, double radius_km, double mass_kg)
        : PlanetBase(distFromSun, radius_km, mass_kg)
        {
            jupiterTexture = gl::Texture::create(loadImage(ci::app::loadAsset("jupiter.jpg")));
        }

        void update() override
        {
            auto shader = gl::ShaderDef().texture().lambert();
            auto glsl   = gl::getStockShader(shader);
            auto sphere = geom::Sphere()
                              .radius(radius_Ws)
                              .center(position_Ws);
            jupiter = gl::Batch::create(sphere, glsl);
        }

        void draw() override
        {
            jupiterTexture->bind(0);
            jupiter->draw();
        }

        dvec3 getPlanetPosition_Ws() override
        {
            return position_Ws;
        }
    };
} // namespace Planet


#endif //JUPITER_H
