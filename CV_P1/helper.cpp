#include "helper.h"

bool compareVec3d::operator()(const cv::Vec3d& left, const cv::Vec3d& right) const
{
    //Return if the left vector is less the right or not
    return lengthVec3d(left) < lengthVec3d(right);
}

double lengthVec3d(cv::Vec3d vec)
{
    return sqrt(vec.val[0] * vec.val[0] +
                vec.val[1] * vec.val[1] +
                vec.val[2] * vec.val[2]);
}

double lengthVec3b(cv::Vec3b vec)
{
    cv::Vec3d vector = static_cast<cv::Vec3d>(vec);
    return lengthVec3d(vector);
}