#pragma once
#include "../helpers/units.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include <iostream>

namespace Planet
{
    using namespace ci;

    class PlanetBase
    {
      public:
        virtual void  draw()                 = 0;
        virtual void  update()               = 0;
        virtual dvec3 getPlanetPosition_Ws() = 0;
        virtual ~PlanetBase()                = default;
        double radius_Ws;

        PlanetBase(double distFromSun, double radius_km, double mass_kg)
            : distFromSun(distFromSun)
            , radius_km(radius_km)
            , mass_kg(mass_kg)
        {
            radius_Ws = 5.0 + (((radius_km - 4'880.0) / (690'820.0)) * (5.0));
            // double position_XWs = 0.0 + (((distFromSun - 57'909'227.0) / (4'440'487'214.0)) *
            // (10.0));
            double position_XWs;
            if (distFromSun == 0.0)
                position_XWs = 0.0;
            else
                position_XWs = 30.0 + ((std::log10(distFromSun) - std::log10(57'909'227.0)) / (std::log10(4'440'487'214.0) - std::log10(57'909'227.0))) * 30.0;
            position_Ws = {position_XWs, 0.0, 0.0};
        }

      protected:
        PlanetBase(const PlanetBase&)            = delete; // disables copying
        PlanetBase& operator=(const PlanetBase&) = delete;

        PlanetBase(PlanetBase&&) noexcept            = default; // enables assignment
        PlanetBase& operator=(PlanetBase&&) noexcept = default;

        // Physics (heliocentric, kilometers)
        double mass_kg{0.0};
        double radius_km{0.0};
        double distFromSun{0.0};

        // World space
        dvec3 position_Ws;
    };
} // namespace Planet