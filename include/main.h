/**
 * \file main.h
 *
 * Contains common definitions and header files used throughout your PROS
 * project.
 *
 * \copyright Copyright (c) 2017-2023, Purdue University ACM SIGBots.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PROS_MAIN_H_
#define _PROS_MAIN_H_

/**
 * If defined, some commonly used enums will have preprocessor macros which give
 * a shorter, more convenient naming pattern. If this isn't desired, simply
 * comment the following line out.
 *
 * For instance, E_CONTROLLER_MASTER has a shorter name: CONTROLLER_MASTER.
 * E_CONTROLLER_MASTER is pedantically correct within the PROS styleguide, but
 * not convienent for most student programmers.
 */
#define PROS_USE_SIMPLE_NAMES

/**
 * If defined, C++ literals will be available for use. All literals are in the
 * pros::literals namespace.
 *
 * For instance, you can do `4_mtr = 50` to set motor 4's target velocity to 50
 */
#define PROS_USE_LITERALS

#include "api.h"

/**
 * You should add more #includes here
 */
#include "okapi/api.hpp"
#include "pros/apix.h"

/**
 * If you find doing pros::Motor() to be tedious and you'd prefer just to do
 * Motor, you can use the namespace with the following commented out line.
 *
 * IMPORTANT: Only the okapi or pros namespace may be used, not both
 * concurrently! The okapi namespace will export all symbols inside the pros
 * namespace.
 */
// using namespace pros;
// using namespace pros::literals;
using namespace okapi;

/**
 * Prototypes for the competition control tasks are redefined here to ensure
 * that they can be called from user code (i.e. calling autonomous from a
 * button press in opcontrol() for testing purposes).
 */
#ifdef __cplusplus
extern "C" {
#endif

#define motorSetting AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees

extern int autMode;

void taskKill();
extern pros::Task buttonInterruptsTask;

extern Controller controller;

extern ControllerButton fwBtn;
extern ControllerButton fwRevBtn;
extern ControllerButton intakeBtn;
extern ControllerButton outtakeBtn;
extern ControllerButton wingsBtn;

extern Motor driveLF;
extern Motor driveLU;
extern Motor driveLB;
extern Motor driveRF;
extern Motor driveRU;
extern Motor driveRB;

extern Motor fw;
extern Motor intake;

// ADIDigitalIn is for V3 (deprecated in V4)
extern pros::ADIDigitalIn autonSelector;
extern pros::Imu imuObj;
extern pros::ADIDigitalOut elevSolenoid;
extern pros::ADIDigitalOut wingsSolenoid;

extern MotorGroup driveL;
extern MotorGroup driveR;

extern std::shared_ptr<ChassisController> drive;

void autonomous();
void initialize();
void disabled();
void competition_initialize();
void opcontrol();

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
/**
 * You can add C++-only headers here
 */
// #include <iostream>
#endif

#endif  // _PROS_MAIN_H_
