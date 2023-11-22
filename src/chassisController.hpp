#pragma once

#include <memory>
#include <vector>

#include "main.h"
#include "okapi/api.hpp"
#include "api.h"

#include "units.hpp"

enum Gearset
{
    RED = 0,
    GREEN,
    BLUE
};

class ChassisController
{
public:
    ChassisController(std::vector<pros::Motor>& motors, units::Length wheelTrack, units::Length wheelDiameter, Gearset gearset, bool odometryEnabled = 0)
    : motors(motors), wheelTrack(wheelTrack), wheelDiameter(wheelDiameter), gearset(gearset) {}

    void moveDistance(units::Length distance);
    void turnAngle(units::Angle angle);
    void moveDistanceAsync(units::Length distance);
    void turnAngleAsync(units::Angle angle);
    void waitUntilSettled();
    void waitUntilSettledAsync();
    void stop();
    void setMaxVelocity(int velocity);
    void setTurnMaxVelocity(int velocity);

protected:
    std::vector<pros::Motor> motors;
    bool odometryEnabled = 0;

    units::Length wheelTrack, wheelDiameter;

    Gearset gearset = Gearset::GREEN;
};


class ChassisControllerBuilder : public ChassisController
{
public:
    ChassisControllerBuilder();

    ChassisControllerBuilder withMotors(pros::Motor FL, pros::Motor FR, pros::Motor BL, pros::Motor BR)
    {
        this->motors = {FL, FR, BL, BR};
        return *this;
    }

    ChassisControllerBuilder withDimensions(Gearset gearset, units::Length wheelDiameter, units::Length wheelTrack, double encTicks)
    {
        this->wheelTrack = wheelTrack.convert(units::meter);
        this->wheelDiameter = wheelDiameter.convert(units::meter);
        return *this;
    }

    ChassisController build() { return ChassisController(this->motors, this->wheelTrack, this->wheelDiameter, this->gearset); }

private:
    std::vector<pros::Motor> motors;

    units::Length wheelTrack, wheelDiameter;

    Gearset gearset = Gearset::GREEN;

};