#ifndef INITIALIZE_CPP
#define INITIALIZE_CPP

#include "main.h"

/*** TASK SAFETY ***/
// safety
void taskKill() {
    // if (buttonInterruptsTask.get_state() == pros::task_state_e_t::E_TASK_STATE_RUNNING) {
    //     buttonInterruptsTask.suspend();
    // }
    // if (cataSubhandlerTask.get_state() == pros::task_state_e_t::E_TASK_STATE_RUNNING) {
    //     cataSubhandlerTask.suspend();
    // }
    // if (intakeSubhandlerTask.get_state() == pros::task_state_e_t::E_TASK_STATE_RUNNING) {
    //     intakeSubhandlerTask.suspend();
    // }
}

/*** BEGIN PORTS AND CONTROLLER DECLARATIONS ***/
// controls
ControllerButton cataBtn = ControllerDigital::L1;
ControllerButton wingsBtn = ControllerDigital::L2;
ControllerButton armOutBtn = ControllerDigital::R1;
ControllerButton armInBtn = ControllerDigital::R2;
ControllerButton ptoBtn = ControllerDigital::B;
ControllerButton cataRevBtn = ControllerDigital::down;

// ports
// drive motors
int8_t driveLFPort = 1;
int8_t driveLBPort = 2;
int8_t driveRFPort = 11;
int8_t driveRBPort = 12;

// transmission motors
int8_t ptoFullLPort = 3;
int8_t ptoHalfLPort = 4;
int8_t ptoFullRPort = 13;
int8_t ptoHalfRPort = 14;

// intake motor
int8_t intakePort = 5;

// sensors (implicit conversion)
uint8_t autonSelectorPort = 'E';
uint8_t ptoSolenoidPort = 'C';
uint8_t wingsSolenoidPort = 'D';
// uint8_t sweepSolenoidPort = 'E';
// uint8_t lowHangSolenoidPort = 'F';
/*** END PORTS AND CONTROLLER DECLARATIONS ***/

// controller
Controller controller;

// motor
Motor driveLF(driveLFPort, true, driveSetting);
Motor driveLB(driveLBPort, true, driveSetting);
Motor driveRF(driveRFPort, false, driveSetting);
Motor driveRB(driveRBPort, false, driveSetting);

Motor ptoFullL(ptoFullLPort, true, driveSetting);
Motor ptoHalfL(ptoHalfLPort, false, driveSetting);
Motor ptoFullR(ptoFullRPort, true, driveSetting);
Motor ptoHalfR(ptoHalfRPort, false, driveSetting);

Motor intake(intakePort, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees);

// sensors
pros::adi::DigitalIn autonSelector(autonSelectorPort);

// solenoid
pros::adi::DigitalOut ptoSolenoid(ptoSolenoidPort);
pros::adi::DigitalOut wingsSolenoid(wingsSolenoidPort);
// pros::adi::DigitalOut sweepSolenoid(sweepSolenoidPort);
// pros::adi::DigitalOut lowHangSolenoid(lowHangSolenoidPort);

// motor groups
MotorGroup driveL({driveLF, driveLB});
MotorGroup driveR({driveRF, driveRB});
MotorGroup ptoGroup({ptoFullL, ptoFullR, ptoHalfL, ptoHalfR});
MotorGroup ptoGroupL({ptoFullL, ptoHalfL});
MotorGroup ptoGroupR({ptoFullR, ptoHalfR});

// drive
std::shared_ptr<ChassisController> drive4 = okapi::ChassisControllerBuilder()
                                                .withMotors(driveL, driveR)
                                                .withDimensions({AbstractMotor::gearset::green, (72.0 / 48.0)}, {{4_in, 12_in}, imev5GreenTPR})  // 4 inch wheels, 12 inch track width, where track width refers to the distance between the left and right wheels measured from the centers of the wheels
                                                .withMaxVelocity(200)
                                                .build();
std::shared_ptr<ChassisController> drive7 = okapi::ChassisControllerBuilder()
                                                .withMotors(ptoGroupL, ptoGroupR)
                                                .withDimensions({AbstractMotor::gearset::green, (72.0 / 48.0)}, {{4_in, 12_in}, imev5GreenTPR})  // this may cause issues
                                                .withMaxVelocity(200)
                                                .build();

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    taskKill(); // kill initialized programs
    driveL.setBrakeMode(AbstractMotor::brakeMode::brake);
    driveR.setBrakeMode(AbstractMotor::brakeMode::brake);
    ptoGroup.setBrakeMode(AbstractMotor::brakeMode::brake);
    intake.setBrakeMode(AbstractMotor::brakeMode::brake);
    // idk if i have to retract pneumatics but just in case ig
    ptoSolenoid.set_value(false);
    wingsSolenoid.set_value(false);
    // sweepSolenoid.set_value(false);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
    taskKill(); // auton -> disable -> opcontrol
    controller.setText(0, 0, "Disabled :/  ");
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
    taskKill(); // if comp cable is unplugged
    pros::delay(100);
}

#endif
