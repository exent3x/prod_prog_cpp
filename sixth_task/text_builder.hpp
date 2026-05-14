#ifndef TEXT_BUILDER_HPP
#define TEXT_BUILDER_HPP

#include "builder.hpp"
#include <sstream>
#include <string>

class TextKPBuilder : public KPBuilder {
public:
    void buildHeader() override;
    void buildKP(const ControlPoint& kp, int index) override;
    std::string getResult() const;
private:
    std::ostringstream ss;
};

#endif