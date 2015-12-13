#include "calculations.h"

using namespace cv;

void fillingUserdata(Vec<void*, 10>* userdata)
{
#pragma region Casting of the data

    Mat* rotationMatPtr = static_cast<Mat*>(userdata->val[3]);
    std::vector<Point2f>* sourceImagePointsPtr = static_cast<std::vector<Point2f>*>(userdata->val[5]);
    std::vector<Point2f>* sourceImagePointsShiftPtr = static_cast<std::vector<Point2f>*>(userdata->val[6]);
    Mat* intrinsicCameraMatPtr = static_cast<Mat*>(userdata->val[8]);
    Mat* image = static_cast<Mat*>(userdata->val[9]);

#pragma endregion

#pragma region Calculating the data

    // Fill the instrinsic camera parameter matrix
    Mat intrinsicCameraMat = (Mat_<double>(3, 3) <<
                                 ALPHA, 0, image->cols / 2,
                                 0, ALPHA, image->rows / 2,
                                 0, 0, 1);

    // Add the corners of the source image
    std::vector<Point2f> sourceImagePoints;
    sourceImagePoints.push_back(Point2f(0, 0));
    sourceImagePoints.push_back(Point2f(image->cols - 1, 0));
    sourceImagePoints.push_back(Point2f(0, image->rows - 1));
    sourceImagePoints.push_back(Point2f(image->cols - 1, image->rows - 1));

    // Calculating the new coordinates for the center of the image
    int xNeg = -image->cols / 2;
    int xPos = -xNeg;
    if (image->cols % 2 == 1)
        xPos -= 1;
    else
        xNeg += 1;

    int yNeg = -image->rows / 2;
    int yPos = -yNeg;
    if (image->rows % 2 == 1)
        yPos -= 1;
    else
        yNeg += 1;

    // Add the corners of the shifted image on the plan in the 3d room
    std::vector<Point2f> sourceImagePointsShift;
    sourceImagePointsShift.push_back(Point2f(xNeg, yNeg));
    sourceImagePointsShift.push_back(Point2f(xPos, yNeg));
    sourceImagePointsShift.push_back(Point2f(xNeg, yPos));
    sourceImagePointsShift.push_back(Point2f(xPos, yPos));
    sourceImagePointsShift.push_back(Point2f(0, 0));

    // Filling the rotation matrix

    Mat rotationMatX = (Mat_<double>(3, 3) <<
                            1, 0, 0,
                            0, cos(0), -sin(0),
                            0, sin(0), cos(0));
    Mat rotationMatY = (Mat_<double>(3, 3) <<
                            cos(0), 0, sin(0),
                            0, 1, 0,
                            -sin(0), 0, cos(0));
    Mat rotationMat = rotationMatX * rotationMatY;

#pragma endregion

#pragma region Save all

    *rotationMatPtr = rotationMat;
    *sourceImagePointsPtr = sourceImagePoints;
    *sourceImagePointsShiftPtr = sourceImagePointsShift;
    *intrinsicCameraMatPtr = intrinsicCameraMat;

#pragma endregion
}

void calcRotationMatCamera(void* userdata)
{
#pragma region Casting of the data

    Vec<void*, 10>* data = static_cast<Vec<void*, 10>*>(userdata);
    Vec3i* sphereCoordinates = static_cast<Vec3i*>(data->val[0]);
    Mat* rotationMat = static_cast<Mat*>(data->val[3]);

#pragma endregion

#pragma region Filling the rotation matrix
    
    // Rotationmatrix for the rotation on the x axis - using rho
    Mat rotMatX = (Mat_<double>(3, 3) <<
                    1, 0, 0,
                    0, cos(sphereCoordinates->val[1] * PI / 180), -sin(sphereCoordinates->val[1] * PI / 180),
                    0, sin(sphereCoordinates->val[1] * PI / 180), cos(sphereCoordinates->val[1] * PI / 180));
    // Rotationmatrix for the rotation on the y axis - using rho
    Mat rotMatY = (Mat_<double>(3, 3) <<
                    cos(sphereCoordinates->val[1] * PI / 180), 0, sin(sphereCoordinates->val[1] * PI / 180),
                    0, 1, 0,
                    -sin(sphereCoordinates->val[1] * PI / 180), 0, cos(sphereCoordinates->val[1] * PI / 180));
    // Rotationmatrix for the rotation on the Z axis - using theta
    Mat rotMatZ = (Mat_<double>(3, 3) <<
                    cos(sphereCoordinates->val[2] * PI / 180), -sin(sphereCoordinates->val[2] * PI / 180), 0,
                    sin(sphereCoordinates->val[2] * PI / 180), cos(sphereCoordinates->val[2] * PI / 180), 0,
                    0, 0, 1);

#pragma endregion

    *rotationMat = rotMatZ * rotMatY * rotMatX;
}

void calcRotationMatAffine(void* userdata)
{
#pragma region Casting of the data

    Vec<void*, 10>* data = static_cast<Vec<void*, 10>*>(userdata);
    Vec3i* affineTransValues = static_cast<Vec3i*>(data->val[1]);
    Mat* rotationMatAffine = static_cast<Mat*>(data->val[4]);
    Mat* image = static_cast<Mat*>(data->val[9]);

#pragma endregion

#pragma region Filling the rotation matrix

    // Filling the needed matrices
    Mat scalingMat = (Mat_<double>(2, 2) <<
        affineTransValues->val[2], 0,
        0, LAMBDA2);
    Mat rotMatAlpha = (Mat_<double>(2, 2) <<
        cos(affineTransValues->val[0] * PI / 180), -sin(affineTransValues->val[0] * PI / 180),
        sin(affineTransValues->val[0] * PI / 180), cos(affineTransValues->val[0] * PI / 180));
    Mat rotMatBetaPos = (Mat_<double>(2, 2) <<
        cos(affineTransValues->val[1] * PI / 180), -sin(affineTransValues->val[1] * PI / 180),
        sin(affineTransValues->val[1] * PI / 180), cos(affineTransValues->val[1] * PI / 180));
    Mat rotMatBetaNeg = (Mat_<double>(2, 2) <<
        cos(-affineTransValues->val[1] * PI / 180), -sin(-affineTransValues->val[1] * PI / 180),
        sin(-affineTransValues->val[1] * PI / 180), cos(-affineTransValues->val[1] * PI / 180));

    //Calculation for the augmented matrix
    Mat augmentedMat = rotMatAlpha * (rotMatBetaNeg * (scalingMat * rotMatBetaPos));

    //Fill the transormation matrix
    Mat transformMat = (Mat_<double>(3, 3) <<
        augmentedMat.at<double>(0, 0), augmentedMat.at<double>(0, 1), image->cols / 2,
        augmentedMat.at<double>(1, 0), augmentedMat.at<double>(1, 1), image->rows / 2,
        0, 0, 1);

#pragma endregion

    *rotationMatAffine = transformMat;
}

Mat calcCameraImage(void* userdata)
{
    calcCameraPosition(userdata);

#pragma region Casting of the data

    Vec<void*, 10>* data = static_cast<Vec<void*, 10>*>(userdata);
    Point3d* cameraPosition = static_cast<Point3d*>(data->val[2]);
    Mat* rotationMat = static_cast<Mat*>(data->val[3]);
    std::vector<Point2f>* sourceImagePoints = static_cast<std::vector<Point2f>*>(data->val[5]);
    std::vector<Point2f>* sourceImagePointsShift = static_cast<std::vector<Point2f>*>(data->val[6]);
    std::vector<Point2f>* cameraImagePoints = static_cast<std::vector<Point2f>*>(data->val[7]);
    Mat* intrinsicCameraMat = static_cast<Mat*>(data->val[8]);
    Mat* image = static_cast<Mat*>(data->val[9]);

#pragma endregion

#pragma region Calculate the new image points
    
    Mat extrinsicCameraMat = Mat_<double>(3, 3);
    // Fill the extrinsic camera parameter matrix
    for (int cY = 0; cY < 3; cY++)
        for (int cX = 0; cX < 2; cX++)
            extrinsicCameraMat.at<double>(cY, cX) = rotationMat->at<double>(cY, cX);
    extrinsicCameraMat.at<double>(0, 2) = cameraPosition->x;
    extrinsicCameraMat.at<double>(1, 2) = cameraPosition->y;
    extrinsicCameraMat.at<double>(2, 2) = cameraPosition->z;

    Mat homogeneousPoint3D = Mat_<double>(3, 1);
    // Fill the point vector from the image
    homogeneousPoint3D.at<double>(2, 0) = 1;

    Point2f actualPoint;
    std::vector<Point2f> destinationPoints;
    for (int c = 0; c < sourceImagePointsShift->size(); c++)
    {
        actualPoint = sourceImagePointsShift->at(c);
        homogeneousPoint3D.at<double>(0, 0) = actualPoint.x;
        homogeneousPoint3D.at<double>(1, 0) = actualPoint.y;

        Mat tempPoint = *intrinsicCameraMat * (extrinsicCameraMat * homogeneousPoint3D);

        if (tempPoint.at<double>(2, 0) != 0)
        {
            actualPoint.x = tempPoint.at<double>(0, 0) / tempPoint.at<double>(2, 0);
            actualPoint.y = tempPoint.at<double>(1, 0) / tempPoint.at<double>(2, 0);
        }

        if (c < sourceImagePointsShift->size() - 1)
            destinationPoints.push_back(actualPoint);
    }

#pragma endregion

#pragma region Transform the image

    //Create homography
    Mat homography = findHomography(*sourceImagePoints, destinationPoints);

    //Transform the source image
    Mat sourceImageWarped;
    warpPerspective(*image, sourceImageWarped, homography, Size(512, 512));

    //Save the data
    destinationPoints.push_back(actualPoint);
    *cameraImagePoints = destinationPoints;

#pragma endregion

    return sourceImageWarped;
}

void calcCameraPosition(void* userdata)
{
#pragma region Casting of the data

    Vec<void*, 10>* data = static_cast<Vec<void*, 10>*>(userdata);
    Vec3i* sphereCoordinates = static_cast<Vec3i*>(data->val[0]);
    Point3d* cameraPosition = static_cast<Point3d*>(data->val[2]);

#pragma endregion
    
#pragma region Calculating the new camera position

    //Calculate the lengt of the vector on the x-y-plane
    double lengthOnXY = sin(sphereCoordinates->val[1] * PI / 180) * sphereCoordinates->val[0];

    //Calculate the coordinates on the x and y axis with the vector
    cameraPosition->x = cos(sphereCoordinates->val[2] * PI / 180) * lengthOnXY;
    cameraPosition->y = sin(sphereCoordinates->val[2] * PI / 180) * lengthOnXY;
    //Calculate the coordinate on the z axis with theta
    cameraPosition->z = cos(sphereCoordinates->val[1] * PI / 180) * sphereCoordinates->val[0];

#pragma endregion
}

Mat calcAffineTransformation(void* userdata)
{
#pragma region Casting of the data

    Vec<void*, 10>* data = static_cast<Vec<void*, 10>*>(userdata);
    Mat* rotationMatAffine = static_cast<Mat*>(data->val[4]);
    std::vector<Point2f>* sourcePoints = static_cast<std::vector<Point2f>*>(data->val[5]);
    std::vector<Point2f>* cameraImagePoints = static_cast<std::vector<Point2f>*>(data->val[7]);
    Mat* image = static_cast<Mat*>(data->val[9]);

#pragma endregion

    if (cameraImagePoints->size() == 0)
        return Mat_<double>(1, 1) << ( 255 );

#pragma region Calculate the new image points

    //Fill the point vector from the image
    Mat homogeneousPoint2D = Mat_<double>(3, 1);
    homogeneousPoint2D.at<double>(2, 0) = 1;

    Point2f actualPoint;
    std::vector<Point2f> destinationPoints;
    for (int c = 0; c < cameraImagePoints->size(); c++)
    {
        actualPoint = cameraImagePoints->at(c);
        homogeneousPoint2D.at<double>(0, 0) = actualPoint.x;
        homogeneousPoint2D.at<double>(1, 0) = actualPoint.y;

        Mat tempPoint = *rotationMatAffine * homogeneousPoint2D;

        if (tempPoint.at<double>(2, 0) != 0)
        {
            actualPoint.x = tempPoint.at<double>(0, 0) / tempPoint.at<double>(2, 0);
            actualPoint.y = tempPoint.at<double>(1, 0) / tempPoint.at<double>(2, 0);
        }

        if (c < cameraImagePoints->size() - 1)
            destinationPoints.push_back(actualPoint);
    }

    //Centering of the image
    Point2f centerOffset = actualPoint - Point2f(255, 255);
    for (int c = 0; c < destinationPoints.size(); c++)
        destinationPoints.at(c) -= centerOffset;

#pragma endregion

#pragma region Transform the image

    //Create homography
    Mat homography = findHomography(*sourcePoints, destinationPoints, 0);

    //Transform the source image
    Mat sourceWarped;
    warpPerspective(*image, sourceWarped, homography, Size(512, 512));

#pragma endregion

    return sourceWarped;
}
