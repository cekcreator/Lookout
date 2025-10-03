//
// Created by Caleb Kumar on 8/17/25.
//
#pragma once

#ifndef EARTH_H
#define EARTH_H
#include "../PlanetBase.h"
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"


using namespace ci;

namespace Planet
{

    class Earth final : public PlanetBase
    {
    public:
        gl::BatchRef earth;
        gl::TextureRef earthTexture;
        explicit Earth(const dvec3& position_Ws, double radius_km, double mass_kg, double scaleFactor = 1.0)
            : PlanetBase(position_Ws, radius_km, mass_kg, scaleFactor)
        {
            earthTexture = gl::Texture::create( loadImage( ci::app::loadAsset("checkerboard.png")));
        }

        void update() override
        {

            auto shader = gl::ShaderDef().texture().lambert();
            auto glsl = gl::getStockShader(shader);
            auto sphere = geom::Sphere().radius(static_cast<float>(radius_km) * units::planetSizeScale).center(position_Ws);
            earth = gl::Batch::create(sphere, glsl);
        }

        void draw() override
        {
            earthTexture->bind(0);
            earth->draw();
        }

        dvec3 getPlanetPosition_Ws() override
        {
            return position_Ws;
        }
    };
} // namespace Planet


#endif //EARTH_H
