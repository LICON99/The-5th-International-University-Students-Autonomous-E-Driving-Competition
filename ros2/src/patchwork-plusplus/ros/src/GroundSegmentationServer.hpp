// Patchwork++
#include "patchwork/patchworkpp.h"

// ROS 2
#include <string>

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <std_msgs/msg/header.hpp>

namespace patchworkpp_ros {

class GroundSegmentationServer : public rclcpp::Node {
 public:
  /// GroundSegmentationServer constructor
  GroundSegmentationServer() = delete;
  explicit GroundSegmentationServer(const rclcpp::NodeOptions &options);

 private:
  /// Register new frame
  void EstimateGround(const sensor_msgs::msg::PointCloud2::ConstSharedPtr &msg);

  /// Apply ROI filtering to point cloud
  Eigen::MatrixX3f ApplyROI(const Eigen::MatrixX3f &cloud);

  /// Stream the point clouds for visualization
  void PublishClouds(const Eigen::MatrixX3f &est_ground,
                     const Eigen::MatrixX3f &est_nonground,
                     const std_msgs::msg::Header header_msg);

 private:
  /// Data subscribers.
  rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr pointcloud_sub_;

  /// Data publishers.
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr cloud_publisher_;
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr ground_publisher_;
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr nonground_publisher_;

  /// Patchwork++
  std::unique_ptr<patchwork::PatchWorkpp> Patchworkpp_;

  std::string base_frame_{"base_link"};

  /// ROI parameters (경진대회 환경 기준)
  double roi_x_min_{0.5};    // 전방 최소 거리 (m)
  double roi_x_max_{20.0};   // 전방 최대 거리 (m)
  double roi_y_min_{-3.0};   // 좌측 한계 (m)
  double roi_y_max_{3.0};    // 우측 한계 (m)
  double roi_z_min_{0.1};    // 높이 최소 (m, 지면 위)
  double roi_z_max_{2.0};    // 높이 최대 (m, PE드럼 커버)
};

}  // namespace patchworkpp_ros
