#ifndef POINTCLOUD_H_
#define POINTCLOUD_H_

#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>

enum class PointCloudType {
    XYZIR = 5,
    XYZIRDAT = 8
};

inline std::string PointCloudTypeToString(PointCloudType type) {
    switch (type) {
        case PointCloudType::XYZIR:    return "XYZIR";
        case PointCloudType::XYZIRDAT: return "XYZIRDAT";
        default:                       return "UNKNOWN";
    }
}

class PointCloud {
public:
    void Init(PointCloudType pc_type, size_t points_count) {
        pointcloud_type_ = pc_type;
        size_ = points_count;
        point_size_ = static_cast<size_t>(pc_type);
        points_.assign(size_ * point_size_, 0.0);
    }

    void AddPoint(const std::vector<double>& point, size_t index) {
        if (index >= size_) {
            throw std::out_of_range("point index out of range");
        }
        if (point.size() != point_size_) {
            throw std::runtime_error("Point has unsupported size = " + std::to_string(point.size()) +
                                     " for type " + PointCloudTypeToString(pointcloud_type_));
        }
        std::copy(point.begin(), point.end(), points_.begin() + point_size_ * index);
    }

    PointCloudType GetTypeEnum() const noexcept { return pointcloud_type_; }
    std::string GetType() const noexcept { return PointCloudTypeToString(pointcloud_type_); }
    size_t GetSize() const noexcept { return size_; }
    size_t GetPointSize() const noexcept { return point_size_; }
    const std::vector<double>& GetPoints() const noexcept { return points_; }
    std::vector<double>& GetPoints() noexcept { return points_; }

    double GetX(size_t point_index) const {
        return points_.at(point_index * point_size_);
    }
    double GetY(size_t point_index) const {
        return points_.at(point_index * point_size_ + 1);
    }
    double GetZ(size_t point_index) const {
        return points_.at(point_index * point_size_ + 2);
    }
    double GetIntensity(size_t point_index) const {
        return points_.at(point_index * point_size_ + 3);
    }
    double GetRing(size_t point_index) const {
        return points_.at(point_index * point_size_ + 4);
    }

    double GetDistance(size_t index) const {
        switch (pointcloud_type_) {
            case PointCloudType::XYZIR: {
                double x = GetX(index);
                double y = GetY(index);
                double z = GetZ(index);
                return std::hypot(x, y, z);
            }
            case PointCloudType::XYZIRDAT:
                return points_.at(index * point_size_ + 5);
            default:
                throw std::runtime_error("GetDistance not implemented for this point type");
        }
    }

    double GetAzimuth(size_t index) const {
        switch (pointcloud_type_) {
            case PointCloudType::XYZIR: {
                double x = GetX(index);
                double y = GetY(index);
                return std::atan2(y, x);
            }
            case PointCloudType::XYZIRDAT:
                return points_.at(index * point_size_ + 6);
            default:
                throw std::runtime_error("GetAzimuth not implemented for this point type");
        }
    }

private:
    PointCloudType pointcloud_type_;
    size_t size_ = 0;
    size_t point_size_ = 0;
    std::vector<double> points_;
};

inline void FillPointCloud(PointCloud* pc, size_t points_count,
                           PointCloudType point_type, const std::vector<double>& data) {
    size_t point_size = static_cast<size_t>(point_type);
    pc->Init(point_type, points_count);
    for (size_t i = 0; i < points_count; ++i) {
        auto begin = data.begin() + i * point_size;
        auto end = begin + point_size;
        pc->AddPoint(std::vector<double>(begin, end), i);
    }
}

#endif // POINTCLOUD_H_