#ifndef AUTONOMOUS_CPP
#define AUTONOMOUS_CPP

#include "autonomous.h"

/**
 * <SC7> An Autonomous Win Point is awarded to any Alliance that has completed the
 * following tasks at the end of the Autonomous Period:
 *  a. Removed the Triball from the Alliance’s Match Load Zone that coincides with their
 *      Starting Tiles. For example, in Figure 21, the red Alliance must remove the Triball
 *      that begins in the bottom-left Match Load Zone, adjacent to Robot 1’s Starting Tiles.
 *  b. Scored at least one Alliance Triball in the Alliance’s own Goal.
 *  c. Ended the Autonomous Period with at least one Robot contacting their own Elevation Bar.
 *  d. Not violated any other rules.
 */

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
    switch (autMode) {
        case 0:
            noAuton();
            break;
        case 1:
            elevationBar();
            break;
        case 2:
            loadZone();
            break;
        case 3:
            scoreGoal();
            break;
        case 4:
            loadZoneAndBar();
            break;
        case 5:
            scoreGoalAndBar();
            break;
        case 6:
            autonTest();
            break;
        default:
            noAuton();
            break;
    }
}

// No Autonomous
void noAuton() {}

// Elevation Bar
void elevationBar() {}

// Load Zone
void loadZone() {}

// Score Goal
void scoreGoal() {}

// Load Zone + Bar
void loadZoneAndBar() {}

// Score Goal + Bar
void scoreGoalAndBar() {}

/**
 * @brief Synnchronous drive function that corrects for differences in friction
 * @param target The target voltage to drive at, [-12000, 12000]
 */
void driveStraight(int target) {  // adjust for differences in friction
    int leftAdj = 0;
    int rightAdj = 0;
    driveL.moveVoltage(target + leftAdj);
    driveR.moveVoltage(target + rightAdj);
}

/* Sample PID usage in autonomous:
 * Remember, class operations MUST be called within functions!
 * Voltage controls also bypass the internal VEX PID controller.
 * ---
 * In this function, the one drive targets the desired voltage, while
 * the other drive targets the first drive's voltage. This is to ensure
 * that the robot drives straight using PID.
 * ---
 * THIS IS UNTESTED CODE.
 */
void autonTest() {
    double kP = 0.6, kI = 1.2, kD = 0.0075, Ibound = 1000, outBound = 12000;
    PID autonL(kP, kI, kD, Ibound, outBound), autonR(kP, kI, kD, Ibound, outBound);
    PIDdriveStraight(6000, autonL, autonR);  // drive straight at half speed (12000
    pros::delay(1000);
    PIDdriveStraight(0, autonL, autonR);  // stop
}
void PIDdriveStraight(int target, PID PIDcontrollerL, PID PIDcontrollerR) {
    PIDcontrollerL.setTarget(target);  // in this case, units are voltage
    while (driveL.getVoltage() != target) {
        driveL.moveVoltage((int)PIDcontrollerL.calculatePID(driveL.getVoltage()));
        PIDcontrollerR.setTarget(driveL.getVoltage());
        driveR.moveVoltage((int)PIDcontrollerR.calculatePID(driveR.getVoltage()));
        pros::delay(20);
    }
}

#endif