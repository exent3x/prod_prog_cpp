#include "director.hpp"

void Director::construct(const std::vector<ControlPoint>& points, KPBuilder& builder) {
    builder.buildHeader();
    for (size_t i = 0; i < points.size(); ++i)
        builder.buildKP(points[i], static_cast<int>(i));
    builder.buildFooter();
}