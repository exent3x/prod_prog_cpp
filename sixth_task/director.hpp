#ifndef DIRECTOR_HPP
#define DIRECTOR_HPP

#include <vector>
#include "control_point.hpp"
#include "builder.hpp"

class Director {
public:
    void construct(const std::vector<ControlPoint>& points, KPBuilder& builder);
};

#endif