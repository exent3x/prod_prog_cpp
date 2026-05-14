#ifndef POINTCLOUD_H_
#define POINTCLOUD_H_

#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>

class PointCloud {
public:
    void Init(const std::string& pc_type, size_t points_count) {
        if (pc_type != "XYZIR" && pc_type != "XYZIRDAT") {
            throw std::runtime_error("unknown pointcloud type");
        }
        pointcloud_type_ = pc_type;
        size_ = points_count;
        point_size_ = (pc_type == "XYZIR") ? 5 : 8;
        points_.assign(size_ * point_size_, 0.0);
    }

    void AddPoint(const std::vector<double>& point, size_t index) {
        if (index >= size_) {
            throw std::out_of_range("point index out of range");
        }
        size_t expected_size = point_size_;
        if (point.size() != expected_size) {
            throw std::runtime_error("Point has unsupported size = " + std::to_string(point.size()) +
                                     " for type " + pointcloud_type_);
        }
        std::copy(point.begin(), point.end(), points_.begin() + point_size_ * index);
    }

    const std::string& GetType() const noexcept { return pointcloud_type_; }
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

private:
    std::string pointcloud_type_;
    size_t size_ = 0;
    size_t point_size_ = 0;
    std::vector<double> points_;
};

inline void FillPointCloud(PointCloud* pc, size_t points_count,
                           const std::string& point_type, const std::vector<double>& data) {
    size_t point_size = (point_type == "XYZIR") ? 5 : 8;
    pc->Init(point_type, points_count);
    for (size_t i = 0; i < points_count; ++i) {
        auto begin = data.begin() + i * point_size;
        auto end = begin + point_size;
        pc->AddPoint(std::vector<double>(begin, end), i);
    }
}

#endif // POINTCLOUD_H_