#ifndef POINTCLOUD_PREPROCESSOR__CROP_BOX_FILTER_HPP_
#define POINTCLOUD_PREPROCESSOR__CROP_BOX_FILTER_HPP_

#include "../filter.hpp"
#include <memory>

namespace pointcloud_preprocessor {

class CropBoxFilter : public Filter {
public:
    CropBoxFilter();
    std::unique_ptr<PointCloud> Apply(const PointCloud* pc) override;
    void SetParams(const FilterParametr& param) override;

private:
    struct CropBoxParam {
        double min_x{0.0};
        double max_x{0.0};
        double min_y{0.0};
        double max_y{0.0};
        double min_z{0.0};
        double max_z{0.0};
        bool negative{false};
    } param_;
};

}

#endif  // POINTCLOUD_PREPROCESSOR__CROP_BOX_FILTER_HPP_