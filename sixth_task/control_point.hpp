#ifndef CONTROL_POINT_H
#define CONTROL_POINT_H

#include <string>

enum class KPType { Mandatory, Optional };

struct ControlPoint {
    std::string name;
    double latitude;
    double longitude;
    KPType type;
    double penalty = 0.0;
};

#endif