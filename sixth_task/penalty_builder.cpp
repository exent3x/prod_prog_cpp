#include "penalty_builder.hpp"

void PenaltySumBuilder::buildKP(const ControlPoint& kp, int /*index*/) {
    if (kp.type == KPType::Optional)
        sum += kp.penalty;
}

double PenaltySumBuilder::getResult() const {
    return sum;
}