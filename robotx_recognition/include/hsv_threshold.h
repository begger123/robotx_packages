#ifndef HSV_THRESHOLD_H_INCLUDED
#define HSV_THRESHOLD_H_INCLUDED

#include <array>

class hsv_threshold
{
public:
  hsv_threshold(std::string name,double min_h,double max_h,double min_s,double max_s,double min_v,double max_v):target_buoy_name(name)
  {
    this->min_h = min_h;
    this->max_h = max_h;
    this->min_s = min_s;
    this->max_s = max_s;
    this->min_v = min_v;
    this->max_v = max_v;
  }
  void get_threshold(double& min_h,double& max_h,double& min_s,double& max_s,double& min_v,double& max_v)
  {
    min_h = this->min_h;
    max_h = this->max_h;
    min_s = this->min_s;
    max_s = this->max_s;
    min_v = this->min_v;
    max_v = this->max_v;
  }
  const std::string target_buoy_name;
private:
  double min_h;
  double max_h;
  double min_s;
  double max_s;
  double min_v;
  double max_v;
};

#endif
