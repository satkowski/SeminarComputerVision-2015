#ifndef MULTISET_H
#define MULTISET_H

#include "opencv2/imgproc/imgproc.hpp"

#include <set>

//Struct for the comparsion in the multiset for Vec3f in pairs
struct compareVec3d
{
    //Using own comparsion method
    bool operator()(const std::pair<cv::Point, cv::Vec3d>& left, const std::pair<cv::Point, cv::Vec3d>& right) const;
};

typedef std::multiset<std::pair<cv::Point, cv::Vec3d>, compareVec3d> PointVec3fQueue;

std::pair<cv::Point, cv::Vec3d> findPointVec3fQueueElement(cv::Point key);

#endif // MULTISET_H
