//
// Created by Caleb Kumar on 8/17/25.
//

#ifndef ALLPLANETS_H
#define ALLPLANETS_H
#include "Earth/Earth.h"
#include "Jupiter/Jupiter.h"
#include "Mars/Mars.h"
#include "Mercury/Mercury.h"
#include "Neptune/Neptune.h"
#include "Saturn/Saturn.h"
#include "Sun/Sun.h"
#include "Venus/Venus.h"
#include "Uranus/Uranus.h"

#include <memory>
#include <stdexcept>

namespace Planet
{
    enum class AllPlanets
    {
        Mercury,
        Venus,
        Earth,
        Mars,
        Jupiter,
        Saturn,
        Uranus,
        Neptune
    };

    struct PlanetSpec
    {
        AllPlanets  planet;
        const char* name;
        double      distFromSun_km;
        double      radius_km;
        double      mass_kg;
        double      scaleFactor = 100;
    };

    inline const PlanetSpec kSpecs[] = {
        {AllPlanets::Mercury, "Mercury", 5.8e7, 2440.0, 3.30e23},
        {AllPlanets::Venus, "Venus", 1.08e8, 6052.0, 4.87e24},
        {AllPlanets::Earth, "Earth", 1.50e8, 6371.0, 5.97e24,},
        {AllPlanets::Mars, "Mars", 2.27e8, 3389.0, 6.42e23},
        {AllPlanets::Jupiter, "Jupiter", 7.78e8, 69911.0, 1.90e27},
        {AllPlanets::Saturn, "Saturn", 1.433e9, 58232.0, 5.68e26},
        {AllPlanets::Uranus, "Uranus", 2.872e9, 25362.0, 8.68e25},
        {AllPlanets::Neptune, "Neptune", 4.495e9, 24622.0, 1.02e26},
    };

    inline std::unique_ptr<PlanetBase>
    createPlanet(const PlanetSpec& s, const glm::dvec3& sunPos, double orbitSizeScale)
    {
        const double distWs = s.distFromSun_km * orbitSizeScale;
        const dvec3  posWs  = sunPos + dvec3(distWs, 0.0, 0.0);

        switch (s.planet)
        {
        case AllPlanets::Mercury:
            return std::make_unique<Mercury>(posWs, s.radius_km, s.mass_kg, s.scaleFactor);
        case AllPlanets::Venus:
            return std::make_unique<Venus>(posWs, s.radius_km, s.mass_kg, s.scaleFactor);
        case AllPlanets::Earth:
            return std::make_unique<Earth>(posWs, s.radius_km, s.mass_kg, s.scaleFactor);
        case AllPlanets::Mars:
            return std::make_unique<Mars>(posWs, s.radius_km, s.mass_kg, s.scaleFactor);
        case AllPlanets::Jupiter:
            return std::make_unique<Jupiter>(posWs, s.radius_km, s.mass_kg, s.scaleFactor);
        case AllPlanets::Saturn:
            return std::make_unique<Saturn>(posWs, s.radius_km, s.mass_kg, s.scaleFactor);
        case AllPlanets::Uranus:
            return std::make_unique<Uranus>(posWs, s.radius_km, s.mass_kg, s.scaleFactor);
        case AllPlanets::Neptune:
            return std::make_unique<Neptune>(posWs, s.radius_km, s.mass_kg, s.scaleFactor);
        }
        throw std::runtime_error("Unknown PlanetKind");
    }

    inline const std::vector<std::unique_ptr<PlanetBase> > getAllPlanets(Sun& sun)
    {
        std::vector<std::unique_ptr<PlanetBase>> planets;
        planets.reserve(std::size(kSpecs));
        dvec3       sunPos = sun.getPlanetPosition_Ws();
        for (const auto& spec : kSpecs) {
            planets.emplace_back(createPlanet(spec, sunPos, units::orbitSizeScale));
        }
        return planets;
    }
} // namespace Planet
#endif // ALLPLANETS_H
