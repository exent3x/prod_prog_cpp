#ifndef POINTCLOUD_PREPROCESSOR__FILTER_HPP_
#define POINTCLOUD_PREPROCESSOR__FILTER_HPP_

#include "Logger.h"
#include "PointCloud.h"

#include <string>
#include <cmath>
#include <unordered_map>
#include <memory>

namespace pointcloud_preprocessor {

class FilterParametr {
public:
    FilterParametr() = default;
    explicit FilterParametr(std::unordered_map<std::string, double> params) : params_(std::move(params)) {}

    void ChangeParam(const std::string& param_name, double param_val) {
        params_[param_name] = param_val;
    }

    double GetParam(const std::string& param_name) const {
        return params_.at(param_name);
    }

    double GetParam(const std::string& param_name, double default_val) const noexcept {
        auto it = params_.find(param_name);
        return (it != params_.end()) ? it->second : default_val;
    }

private:
    std::unordered_map<std::string, double> params_;
};

class Filter {
public:
    explicit Filter(const std::string& filter_name = "pointcloud_preprocessor_filter")
        : filter_name_(filter_name), logger_(filter_name_) {}

    virtual ~Filter() = default;

    const std::string& GetFilterName() const noexcept { return filter_name_; }

    double GetDistance(const PointCloud* pc, size_t index) const {
        if (!pc) return 0.0;
        if (pc->GetType() == "XYZIR") {
            double x = pc->GetX(index);
            double y = pc->GetY(index);
            double z = pc->GetZ(index);
            return std::hypot(x, y, z);
        }
        return pc->GetPoints().at(index * pc->GetPointSize() + 5);
    }

    double GetAzimuth(const PointCloud* pc, size_t index) const {
        if (!pc) return 0.0;
        if (pc->GetType() == "XYZIR") {
            double x = pc->GetX(index);
            double y = pc->GetY(index);
            return std::atan2(y, x);
        }
        return pc->GetPoints().at(index * pc->GetPointSize() + 6);
    }
    virtual std::unique_ptr<PointCloud> Apply(const PointCloud* pc) = 0;

    virtual void SetParams(const FilterParametr& param) {
        params_ = param;
    }

    const FilterParametr& GetFilterParam() const noexcept {
        return params_;
    }

protected:
    std::string filter_name_;
    Logger logger_;
    FilterParametr params_;
};

}

#endif  // POINTCLOUD_PREPROCESSOR__FILTER_HPP_