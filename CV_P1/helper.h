#ifndef MULTISET_H
#define MULTISET_H

#include "opencv2/imgproc/imgproc.hpp"

#include <map>

// Struct for the comparsion in the multiset for Vec3f in pairs
struct compareVec3d
{
    // Using own comparsion method (less)
    bool operator()(const cv::Vec3d& left, const cv::Vec3d& right) const;
};
// multimap with Vec3d as key and Point as value. Compared with the struct
typedef std::multimap<cv::Vec3d, cv::Point, compareVec3d> Vec3dPointMap;

// Calculation the length of a Vec3d
double lengthVec3d(cv::Vec3d vec);

#endif // MULTISET_H
