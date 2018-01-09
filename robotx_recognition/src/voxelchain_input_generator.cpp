//headers in this package
#include <voxelchain_input_generator.h>


voxelchain_input_generator::voxelchain_input_generator()
{
  euclidean_clusters_sub_ = nh_.subscribe(ros::this_node::getName()+"/clusters", 1,
    &voxelchain_input_generator::euclidean_clusters_callback, this);
}

voxelchain_input_generator::~voxelchain_input_generator()
{

}

void voxelchain_input_generator::euclidean_clusters_callback(robotx_msgs::EuclideanClusters msg)
{
  robotx_msgs::VoxelChainInputs voxel_chain_inputs;
  for(auto clusterd_pointcloud_ptr = msg.clusters.begin(); clusterd_pointcloud_ptr != msg.clusters.end(); ++clusterd_pointcloud_ptr)
  {
    voxel_chain_inputs.inputs.push_back(generate_voxel_chain_input(*clusterd_pointcloud_ptr));
  }
}

robotx_msgs::VoxelChainInput voxelchain_input_generator::generate_voxel_chain_input(sensor_msgs::PointCloud2 cluster_pointcloud)
{
  robotx_msgs::VoxelChainInput voxel_chain_input;
  pcl::PointCloud<pcl::PointXYZ>::Ptr target_pointcloud = get_pcl_pointcloud(cluster_pointcloud);
  std::array<pcl::PointXYZ,2> bounding_box = get_bounding_box(target_pointcloud);
  return voxel_chain_input;
}

pcl::PointCloud<pcl::PointXYZ>::Ptr voxelchain_input_generator::get_pcl_pointcloud(sensor_msgs::PointCloud2 pointcloud_msg)
{
  pcl::PCLPointCloud2 pcl_pc2;
  pcl_conversions::toPCL(pointcloud_msg,pcl_pc2);
  pcl::PointCloud<pcl::PointXYZ>::Ptr pcl_pointcloud(new pcl::PointCloud<pcl::PointXYZ>);
  pcl::fromPCLPointCloud2(pcl_pc2, *pcl_pointcloud);
  return pcl_pointcloud;
}

std::array<pcl::PointXYZ,2> voxelchain_input_generator::get_bounding_box(pcl::PointCloud<pcl::PointXYZ>::Ptr clusterd_pointcloud)
{
  std::array<pcl::PointXYZ,2> bounding_box;
  pcl::MomentOfInertiaEstimation <pcl::PointXYZ> feature_extractor;
  feature_extractor.setInputCloud(clusterd_pointcloud);
  pcl::PointXYZ min_point,max_point;
  feature_extractor.getAABB(min_point, max_point);
  bounding_box[0] = min_point;
  bounding_box[1] = max_point;
  return bounding_box;
}
