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
    void mouseDown(MouseEvent event) override;
    void mouseDrag(MouseEvent event) override;
    void mouseUp(MouseEvent event) override;
    void keyDown(KeyEvent event) override;
    void keyUp(KeyEvent event) override;

  private:

    gl::BatchRef		mSphere;
    gl::TextureRef		mTexture;
    gl::GlslProgRef		mGlsl;
    CameraPersp   mCam;
    vec3          mCamPosition{500, 500, 500};
    float         mYaw         = glm::radians(-135.0f);
    float         mPitch       = glm::radians(-20.0f);
    float         mMoveSpeed   = 100.0f;
    float         mMouseSens   = 0.0025f;
    bool          mMouseActive = false;
    std::set<int> mActiveKeys;
    CameraUi      mCamUi;
    ivec2         mCursorPos;
    ivec2         mCursorPrev;
    float         mCamRotationX = 0.0f;
    float         mCamRotationY = 0.0f;
    vec3          mTarget       = vec3(0, 0, 0);
    bool          uiWantsMouse() const;

    std::vector<std::unique_ptr<Planet::PlanetBase>> mPlanets;
};

#endif // LOOKOUT_H
