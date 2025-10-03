//
// Created by Caleb Kumar on 8/18/25.
//
#pragma once
#ifndef LOOKOUT_H
#define LOOKOUT_H
#define _USE_MATH_DEFINES
#include "../Planets/AllPlanets.h"
#include "../helpers/units.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "imgui/imgui.h"

#include <cinder/CameraUi.h>

using namespace ci;
using namespace ci::app;

class Lookout : public App
{
  public:
    void setup() override;
    void draw() override;
    void update() override;
    // void mouseDown(MouseEvent event) override;
    // void mouseDrag(MouseEvent event) override;
    // void mouseUp(MouseEvent event) override;
    void keyDown(KeyEvent event) override;
    void keyUp(KeyEvent event) override;
    void calcCamVectors();
    void camLookAt();

  private:
    CameraPersp   mCam;
    vec3          mCamPos     = vec3{200, 200, 200};
    vec3          mCamForward = vec3{0, 0, -1};
    vec3          mCamUp      = vec3{0, 1, 0};
    vec3          mCamRight   = vec3{1, 0, 0};
    vec3          mWorldUp    = vec3{0, 1, 0};
    float         mYaw;
    float         mPitch;
    float         mSpeed     = 10.0f;
    float         mLookSpeed = 3.0f;
    std::set<int> mActiveKeys;

    std::vector<std::unique_ptr<Planet::PlanetBase>> mPlanets;
};

#endif // LOOKOUT_H
