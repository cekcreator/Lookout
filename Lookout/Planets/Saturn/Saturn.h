//
// Created by Caleb Kumar on 8/17/25.
//
#pragma once
#ifndef Saturn_H
#define Saturn_H
#pragma once
#include "../PlanetBase.h"
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"


using namespace ci;

namespace Planet
{

    class Saturn : public PlanetBase
    {
    public:
        gl::BatchRef   saturn;
        gl::TextureRef saturnTexture;
        explicit Saturn(double distFromSun, double radius_km, double mass_kg)
            : PlanetBase(distFromSun, radius_km, mass_kg)
        {
            saturnTexture = gl::Texture::create(loadImage(ci::app::loadAsset("saturn.jpg")));
            position_Ws = dvec3(165.0, 0.0, 0.0);
            radius_Ws = 7.0;
        }

        void update() override
        {
            auto shader = gl::ShaderDef().texture().lambert();
            auto glsl   = gl::getStockShader(shader);
            auto sphere = geom::Sphere()
                              .radius(radius_Ws)
                              .center(position_Ws);
            saturn = gl::Batch::create(sphere, glsl);
        }

        void draw() override
        {
            saturnTexture->bind(0);
            saturn->draw();
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


#endif //SATURN_H
