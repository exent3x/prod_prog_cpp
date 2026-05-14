#ifndef PENALTY_BUILDER_HPP
#define PENALTY_BUILDER_HPP

#include "builder.hpp"

class PenaltySumBuilder : public KPBuilder {
public:
    void buildKP(const ControlPoint& kp, int index) override;
    double getResult() const;
private:
    double sum = 0.0;
};

#endif