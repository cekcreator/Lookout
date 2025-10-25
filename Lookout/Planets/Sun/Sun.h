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
        gl::BatchRef sun;
        gl::TextureRef sunTexture;
        explicit Sun(double distFromSun, double radius_km, double mass_kg)
            : PlanetBase(distFromSun, radius_km, mass_kg)
        {
            sunTexture = gl::Texture::create( loadImage( ci::app::loadAsset("sun.jpg")));
        }

        void update() override
        {
            auto shader = gl::ShaderDef().texture().lambert();
            auto glsl = gl::getStockShader(shader);
            auto sphere = geom::Sphere().radius(radius_Ws).center(position_Ws);
            sun = gl::Batch::create(sphere, glsl);
        }

        void draw() override
        {
            sunTexture->bind(0);
            sun->draw();
        }

        dvec3 getPlanetPosition_Ws() override
        {
            return position_Ws;
        }

    };
} // namespace Planet
#endif // SUN_H