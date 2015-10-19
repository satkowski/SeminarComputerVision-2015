#include "multiset.h"

bool compareVec3d::operator()(const std::pair<cv::Point, cv::Vec3d>& left, const std::pair<cv::Point, cv::Vec3d>& right) const
{
    // Calculate the length of the vectors
    float leftSum = abs(left.second.val[0]) + abs(left.second.val[1]) + abs(left.second.val[2]);
    float rightSum = abs(right.second.val[0]) + abs(right.second.val[1]) + abs(right.second.val[2]);
    //Return if the left vector is less the right or not
    return leftSum < rightSum;
}

std::pair<cv::Point, cv::Vec3d> findPointVec3fQueueElement(PointVec3fQueue* queue, cv::Point key)
{
    PointVec3fQueue::iterator elemIter = queue->begin();
    for (unsigned int i = 0; i < queue->size(); i++)
    {
        if (key == elemIter->first)
            return *elemIter;
        ++elemIter;
    }
    return std::pair<cv::Point, cv::Vec3d>(cv::Point(-1, -1), cv::Vec3f(0, 0));
}
