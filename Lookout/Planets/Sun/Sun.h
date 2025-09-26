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
        explicit Sun(const dvec3& position_Ws, double radius_km, double mass_kg)
            : PlanetBase(position_Ws, radius_km, mass_kg)
        {
            sunTexture = gl::Texture::create( loadImage( ci::app::loadAsset("sun.jpg")));
        }

        void update() override
        {
            sunTexture->bind(0);

            auto shader = gl::ShaderDef().texture().lambert();
            auto glsl = gl::getStockShader(shader);
            auto sphere = geom::Sphere().radius(static_cast<float>(radius_km) * units::planetSizeScale).center(position_Ws);
            sun = gl::Batch::create(sphere, glsl);
        }

        void draw() override
        {
            sun->draw();
        }

        dvec3 getPlanetPosition_Ws() override
        {
            return position_Ws;
        }

    };
} // namespace Planet
#endif // SUN_H