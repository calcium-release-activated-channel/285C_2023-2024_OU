#ifndef OPCONTROL_CPP
#define OPCONTROL_CPP

#include "opcontrol.h"

#include "main.h"
#include "pid.h"

pros::Task buttonInterruptsTask = pros::Task(buttonInterrupts_fn, (void*)"", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Button Interrupt Manager");

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
    taskKill();  // in case bot disconnects or we go from auton -> driver

    controller.clearLine(0);
    // battery warning
    if ((int)pros::battery::get_capacity() < 35 || controller.getBatteryLevel() < 30) {
        pros::delay(100);
        controller.rumble(".");
        pros::delay(100);
        controller.setText(0, 0, "Battery Low! ");
    }

    // define opcontrol vars and reset from auton
    wingsDeployed = false;
    wingsSolenoid.set_value(wingsDeployed);

    // run task(s)
    buttonInterruptsTask.resume();

    while (true) {
        driveL.move((int)(127 * controller.getAnalog(ControllerAnalog::leftY)));
        driveR.move((int)(127 * controller.getAnalog(ControllerAnalog::rightY)));
        pros::delay(20);
    }
}

void buttonInterrupts_fn(void* param) {
    double 
        kp = 20.0,
        ki = 0.0,
        kd = 0.5,  // 1.5
        ibound = 0,
        obound = 600;
    PID fwPID(kp, ki, kd, ibound, obound);
    fwPID.setTarget(500);
    // int log = 0;

    while (true) {
        if (fwBtn.isPressed() && !fwSlow.isPressed()) {
            fw.moveVelocity(600);
            double x = fw.getActualVelocity();
            // fw.moveVelocity(fwPID.calculatePID(x));
            // if (log++ % 3 == 0) {
            printf("%d,%.1f\n", pros::millis(), x);
            // }
        }
        if (fwBtn.changedToReleased() || fwSlow.changedToReleased())
            fw.moveVelocity(0);
        if (fwSlow.isPressed() && !fwBtn.isPressed())
            fw.moveVelocity(450);
        if (intakeBtn.isPressed() && !outtakeBtn.isPressed())
            intake.moveVelocity(600);
        if (outtakeBtn.isPressed() && !intakeBtn.isPressed())
            intake.moveVelocity(-600);
        if (intakeBtn.changedToReleased() || outtakeBtn.changedToReleased())
            intake.moveVelocity(0);
        if (wingsBtn.changedToPressed()) {
            wingsDeployed = !wingsDeployed;
            wingsSolenoid.set_value(wingsDeployed);
        }
        if (endgameBtn.changedToPressed()) {
            elevSolenoid.set_value(true);
            pros::delay(500);
            wingsSolenoid.set_value(true);
        }
        pros::delay(20);
    }
}

#endif
