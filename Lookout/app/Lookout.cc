#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include "../Planets/AllPlanets.h"
#include "../helpers/units.h"
#include "Lookout.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include <algorithm>
#include <chrono>
#include <cinder/CinderImGui.h>
#include <cmath>
#include <cstring>
#include <fstream>
#include <imgui/imgui_internal.h>
#include <sstream>

using namespace ci;
using namespace ci::app;

void Lookout::keyDown(KeyEvent event)
{
    mActiveKeys.insert(event.getCode());
    if (event.getChar() == 'f')
    {
        setFullScreen(!isFullScreen());
    }
    else if (event.getCode() == KeyEvent::KEY_ESCAPE)
    {
        if (isFullScreen())
            setFullScreen(false);
        else
            quit();
    }
}

void Lookout::keyUp(KeyEvent event) { mActiveKeys.erase(event.getCode()); }

void Lookout::calcCamVectors()
{
    vec3 front;
    front.x     = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    front.y     = sin(glm::radians(mPitch));
    front.z     = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    mCamForward = normalize(front);
    mCamRight   = normalize(cross(mCamForward, mWorldUp));
    mCamUp      = normalize(cross(mCamRight, mCamForward));
}

void Lookout::camLookAt()
{
    vec3 center = mCamPos + mCamForward;
    mCam.lookAt(mCamPos, center, mCamUp);
}

void Lookout::setup()
{
    mCam.setPerspective(45.0f, getWindowAspectRatio(), 0.01f, 1000.0f);
    mCam.lookAt(vec3(10, 10, 10), vec3(0));

    vec3 dirToOrigin = normalize(vec3(0) - mCamPos);
    mYaw             = glm::degrees(atan2(dirToOrigin.z, dirToOrigin.x));
    mPitch           = glm::degrees(asin(dirToOrigin.y)); // y is sin(pitch)
    calcCamVectors();

    mPlanets = Planet::getAllPlanets();
}

void Lookout::update()
{
    mPlanets[0]->update();
    mPlanets[1]->update();
    mPlanets[2]->update();
    mPlanets[3]->update();
    mPlanets[4]->update();
    mPlanets[5]->update();
    mPlanets[6]->update();
    mPlanets[7]->update();
    mPlanets[8]->update();

    // for (auto &planet : mPlanets)
    // {
    //     planet->update();
    // }

    vec3 movement(0);
    if (mActiveKeys.contains(KeyEvent::KEY_w))
        movement += mCamForward;
    if (mActiveKeys.contains(KeyEvent::KEY_s))
        movement -= mCamForward;
    if (mActiveKeys.contains(KeyEvent::KEY_d))
        movement += mCamRight;
    if (mActiveKeys.contains(KeyEvent::KEY_a))
        movement -= mCamRight;
    if (mActiveKeys.contains(KeyEvent::KEY_q))
        movement -= mCamUp;
    if (mActiveKeys.contains(KeyEvent::KEY_e))
        movement += mCamUp;

    if (glm::length(movement) > 0.0f)
        mCamPos += glm::normalize(movement) * mSpeed;

    if (mActiveKeys.contains(KeyEvent::KEY_j))
        mYaw -= mLookSpeed;
    if (mActiveKeys.contains(KeyEvent::KEY_l))
        mYaw += mLookSpeed;
    if (mActiveKeys.contains(KeyEvent::KEY_i))
        mPitch += mLookSpeed;
    if (mActiveKeys.contains(KeyEvent::KEY_k))
        mPitch -= mLookSpeed;

    mPitch = glm::clamp(mPitch, -89.0f, 89.0f);

    calcCamVectors();
    camLookAt();
}

void Lookout::draw() // main
{
    gl::clear(Color(0, 0, 0));
    gl::enableDepthRead();
    gl::enableDepthWrite();
    gl::setMatrices(mCam);

    mPlanets[0]->draw();
    mPlanets[1]->draw();
    mPlanets[2]->draw();
    mPlanets[3]->draw();
    mPlanets[4]->draw();
    mPlanets[5]->draw();
    mPlanets[6]->draw();
    mPlanets[7]->draw();
    mPlanets[8]->draw();

    // for (auto &planet : mPlanets)
    // {
    //     std::cout << planet->getPlanetRadius_Ws() << std::endl;
    // }
}

CINDER_APP(Lookout, RendererGl)