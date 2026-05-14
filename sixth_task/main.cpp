#include <iostream>
#include <vector>
#include "control_point.hpp"
#include "director.hpp"
#include "text_builder.hpp"
#include "penalty_builder.hpp"
int main() {
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    std::vector<ControlPoint> points = {
        {"Старт", 55.0, 37.0, KPType::Mandatory},
        {"Брод", 55.5, 36.5, KPType::Optional, 2.5},
        {"Финиш", 56.0, 38.0, KPType::Mandatory}
    };

    Director dir;

    TextKPBuilder textBuilder;
    dir.construct(points, textBuilder);
    std::cout << textBuilder.getResult();

    PenaltySumBuilder penaltyBuilder;
    dir.construct(points, penaltyBuilder);
    std::cout << "Суммарный штраф: " << penaltyBuilder.getResult() << " ч.\n";
    return 0;
}