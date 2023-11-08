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

// decl tasks
// pros::Task armAutonTask = pros::Task(armAutonTask_fn, (void*)"", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Button Interrupt Manager");

void autonomous() {
    taskKill(); // in case we ever go from driver -> auton -> driver
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

// Elevation Bar: +
void elevationBar() {}

// Load Zone: LEFT
void loadZone() {
    drive4->moveVelocity(-200);
    pros::delay(500);


    // drive4->moveDistance(-24_in); //back robot out of starting tile
    // drive4->turnAngle(45_deg); //turn robot to face load zone
    // drive4->moveDistance(34_in); //move robot to load zone or 24*sqrt(2)
    // intake.moveVelocity(100); //start intake
    // pros::delay(2800);
    // intake.moveVelocity(0); //stop intake
    // drive4->moveDistance(-14_in); //move robot back to intersection of tile
    // intake.moveVelocity(-100);     // start intake
    // pros::delay(2800);
    // intake.moveVelocity(0);  // stop intake
    // drive4->turnAngle(180_deg);
    // drive4->moveDistance(-14_in);
}

// Score Goal: RIGHT
void scoreGoal() {
    drive4->getModel()->tank(200, 200);
    pros::delay(1000);
    drive4->getModel()->tank(0, 0);
}

// Load Zone + Bar: LEFT+
void loadZoneAndBar() {
    drive4->moveDistance(-24_in);  // back robot out of starting tile
    drive4->turnAngle(45_deg);    // turn robot to face load zone
    drive4->moveDistance(34_in);   // move robot to load zone or 24*sqrt(2)
    intake.moveVelocity(100);      // start intake
    pros::delay(2800);
    intake.moveVelocity(0);        // stop intake
    drive4->moveDistance(-34_in);  // back robot out of load zone
    intake.moveVelocity(-100);     // release ball
    pros::delay(1272);
    intake.moveVelocity(0);        // keep arm up for elevation
    drive4->turnAngle(-45_deg);     // move toward elevation bar
    drive4->moveDistance(24_in);
    drive4->turnAngle(-90_deg);
    drive4->moveDistance(24_in);
}

// Score Goal + Bar: RIGHT+
void scoreGoalAndBar() {}

/**
 * @brief Synnchronous drive function that corrects for differences in friction
 * @param target The target voltage to drive at, [-12000, 12000]
 */
void driveStraight(int target) {  // adjust for differences in friction
    int leftAdj = 1.06,
        rightAdj = 1;
    driveL.moveVoltage(target * leftAdj);
    driveR.moveVoltage(target * rightAdj);
}

void autonTest() {
    drive4->getModel()->tank(0, 0); // use only 4m drive
    while (true) {
        ptoGroup.moveVelocity(200);
        pros::delay((int)(2000.0 / 3.3));
    }
}

#endif