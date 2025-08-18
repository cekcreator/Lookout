//
// Created by Caleb Kumar on 8/17/25.
//
#pragma once
namespace units
{
    constexpr double G         = 6.67430e-11;
    constexpr double c         = 299792458.0; // m/s
    constexpr double solarMass = 1.989e30;
    constexpr double M         = solarMass * 4297000.0;
    constexpr double sunRadius = 695700; // km
    // distance to the furthest point on plutos orbit
    constexpr double furthestDistance = 5906380000; // km
    constexpr double planetSizeScale  = 100 / sunRadius;
    constexpr double orbitSizeScale   = 10000 / furthestDistance;
} // namespace units
