#include "text_builder.hpp"
#include <iomanip>

void TextKPBuilder::buildHeader() {
    ss << "Список контрольных пунктов:\n";
}

void TextKPBuilder::buildKP(const ControlPoint& kp, int index) {
    ss << (index + 1) << ". " << kp.name
       << " (" << std::fixed << std::setprecision(4)
       << kp.latitude << ", " << kp.longitude << ")";
    if (kp.type == KPType::Mandatory)
        ss << " незачёт СУ\n";
    else
        ss << " штраф " << kp.penalty << " ч.\n";
}

std::string TextKPBuilder::getResult() const {
    return ss.str();
}