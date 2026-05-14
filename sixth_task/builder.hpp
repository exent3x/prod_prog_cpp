#ifndef BUILDER_HPP
#define BUILDER_HPP

#include "control_point.hpp"

class KPBuilder {
public:
    virtual ~KPBuilder() = default;
    virtual void buildHeader() {}
    virtual void buildKP(const ControlPoint& kp, int index) = 0;
    virtual void buildFooter() {}
};

#endif