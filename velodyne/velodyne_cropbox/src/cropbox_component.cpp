#include "velodyne_cropbox/cropbox_component.hpp"

#include <pcl_conversions/pcl_conversions.h>
#include <rclcpp_components/register_node_macro.hpp>

namespace velodyne_cropbox
{

CropBoxComponent::CropBoxComponent(const rclcpp::NodeOptions & options)
: Node("cropbox_component", options)
{
  // Declare parameters with default values
  x_min_ = this->declare_parameter("x_min", -10.0);
  x_max_ = this->declare_parameter("x_max", 10.0);
  y_min_ = this->declare_parameter("y_min", -10.0);
  y_max_ = this->declare_parameter("y_max", 10.0);
  z_min_ = this->declare_parameter("z_min", -2.0);
  z_max_ = this->declare_parameter("z_max", 2.0);
  negative_ = this->declare_parameter("negative", false);

  // Configure CropBox filter
  Eigen::Vector4f min_point(x_min_, y_min_, z_min_, 1.0);
  Eigen::Vector4f max_point(x_max_, y_max_, z_max_, 1.0);
  crop_box_.setMin(min_point);
  crop_box_.setMax(max_point);
  crop_box_.setNegative(negative_);

  // Create subscription with QoS profile for sensor data
  auto qos = rclcpp::SensorDataQoS();
  subscription_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
    "input", qos,
    std::bind(&CropBoxComponent::pointCloudCallback, this, std::placeholders::_1));

  // Create publisher
  publisher_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("output", qos);

  RCLCPP_INFO(this->get_logger(),
    "CropBox initialized with range: X[%.2f, %.2f], Y[%.2f, %.2f], Z[%.2f, %.2f], Negative: %s",
    x_min_, x_max_, y_min_, y_max_, z_min_, z_max_, negative_ ? "true" : "false");
}

void CropBoxComponent::pointCloudCallback(
  const sensor_msgs::msg::PointCloud2::SharedPtr msg)
{
  // Convert ROS message to PCL point cloud
  pcl::PointCloud<pcl::PointXYZI>::Ptr cloud_in(new pcl::PointCloud<pcl::PointXYZI>);
  pcl::fromROSMsg(*msg, *cloud_in);

  // Apply CropBox filter
  pcl::PointCloud<pcl::PointXYZI>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZI>);
  crop_box_.setInputCloud(cloud_in);
  crop_box_.filter(*cloud_filtered);

  // Convert back to ROS message
  sensor_msgs::msg::PointCloud2 output_msg;
  pcl::toROSMsg(*cloud_filtered, output_msg);
  output_msg.header = msg->header;

  // Publish filtered cloud
  publisher_->publish(output_msg);

  // Log statistics (throttled to 1Hz)
  RCLCPP_INFO_THROTTLE(this->get_logger(), *this->get_clock(), 1000,
    "CropBox: Input %zu pts -> Output %zu pts (%.1f%%)",
    cloud_in->size(), cloud_filtered->size(),
    cloud_in->size() > 0 ? (cloud_filtered->size() * 100.0 / cloud_in->size()) : 0.0);
}

}  // namespace velodyne_cropbox

// Register the component with the ROS system to allow it to be dynamically loaded
RCLCPP_COMPONENTS_REGISTER_NODE(velodyne_cropbox::CropBoxComponent)
