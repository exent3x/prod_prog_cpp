#include "crop_box_filter.hpp"
#include <cmath>
#include <algorithm>

namespace pointcloud_preprocessor {

CropBoxFilter::CropBoxFilter()
    : Filter("CropBoxFilter") {
}

std::unique_ptr<PointCloud> CropBoxFilter::Apply(const PointCloud* pc) {
    if (!pc) {
        logger_.log("Input point cloud is null");
        return nullptr;
    }

    const size_t point_size = pc->GetPointSize();
    const size_t num_points = pc->GetSize();
    const std::vector<double>& points = pc->GetPoints();

    std::vector<double> output;
    output.reserve(num_points * point_size);
    size_t output_points_count = 0;

    for (size_t i = 0; i < num_points; ++i) {
        size_t offset = i * point_size;
        double x = points[offset];
        double y = points[offset + 1];
        double z = points[offset + 2];

        if (!std::isfinite(x) || !std::isfinite(y) || !std::isfinite(z)) {
            logger_.log("Ignoring point containing NaN or Inf values");
            continue;
        }

        bool point_is_inside = (x > param_.min_x && x < param_.max_x &&
                                y > param_.min_y && y < param_.max_y &&
                                z > param_.min_z && z < param_.max_z);

        if ((!param_.negative && point_is_inside) || (param_.negative && !point_is_inside)) {
            output.insert(output.end(), points.begin() + offset,
                          points.begin() + offset + point_size);
            ++output_points_count;
        }
    }

    auto result = std::make_unique<PointCloud>();
    result->Init(pc->GetTypeEnum(), output_points_count);
    if (output_points_count > 0) {
        std::copy(output.begin(), output.end(), result->GetPoints().begin());
    }
    return result;
}

void CropBoxFilter::SetParams(const FilterParametr& param) {
    CropBoxParam new_param;
    new_param.min_x = param.GetParam("min_x", param_.min_x);
    new_param.max_x = param.GetParam("max_x", param_.max_x);
    new_param.min_y = param.GetParam("min_y", param_.min_y);
    new_param.max_y = param.GetParam("max_y", param_.max_y);
    new_param.min_z = param.GetParam("min_z", param_.min_z);
    new_param.max_z = param.GetParam("max_z", param_.max_z);
    new_param.negative = (param.GetParam("negative", param_.negative ? 1.0 : 0.0) != 0.0);

    if (new_param.min_x != param_.min_x || new_param.max_x != param_.max_x ||
        new_param.min_y != param_.min_y || new_param.max_y != param_.max_y ||
        new_param.min_z != param_.min_z || new_param.max_z != param_.max_z ||
        new_param.negative != param_.negative) {

        logger_.log("[paramCallback] Setting the minimum point to: " +
                    std::to_string(new_param.min_x) + " " +
                    std::to_string(new_param.min_y) + " " +
                    std::to_string(new_param.min_z));
        logger_.log("[paramCallback] Setting the maximum point to: " +
                    std::to_string(new_param.max_x) + " " +
                    std::to_string(new_param.max_y) + " " +
                    std::to_string(new_param.max_z));
        logger_.log("[paramCallback] Setting the filter negative flag to: " +
                    std::string(new_param.negative ? "true" : "false"));

        param_ = new_param;
    }

    Filter::SetParams(param);
}

}