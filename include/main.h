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

#define driveSetting AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees

extern int autMode;

void taskKill();
extern pros::Task buttonInterruptsTask;
// extern pros::Task armAutonTask;
// extern pros::Task cataSubhandlerTask;
// extern pros::Task intakeSubhandlerTask;

extern Controller controller;

extern ControllerButton cataBtn;
extern ControllerButton armOutBtn;
extern ControllerButton armInBtn;
extern ControllerButton ptoBtn;
extern ControllerButton wingsBtn;

extern Motor driveLF;
extern Motor driveLB;
extern Motor driveRF;
extern Motor driveRB;

extern Motor ptoFullL;
extern Motor ptoHalfL;
extern Motor ptoFullR;
extern Motor ptoHalfR;

extern Motor intake;

extern pros::adi::DigitalIn autonSelector;
extern pros::adi::DigitalOut ptoSolenoid;
extern pros::adi::DigitalOut wingsSolenoid;
// extern pros::adi::DigitalOut sweepSolenoid;
// extern pros::adi::DigitalOut lowHangSolenoid;

extern MotorGroup driveL;
extern MotorGroup driveR;
extern MotorGroup ptoGroup;

extern std::shared_ptr<ChassisController> drive4;
extern std::shared_ptr<ChassisController> drive7;

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
