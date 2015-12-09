#include "calculations.h"

using namespace cv;

void fillingUserdata(Vec<void*, 9>* userdata)
{
#pragma region Casting of the data

    Mat* rotationMatPtr = static_cast<Mat*>(userdata->val[2]);
    std::vector<Point2f>* sourceImagePointsPtr = static_cast<std::vector<Point2f>*>(userdata->val[4]);
    std::vector<Point2f>* sourceImagePointsShiftPtr = static_cast<std::vector<Point2f>*>(userdata->val[5]);
    Mat* intrinsicCameraMatPtr = static_cast<Mat*>(userdata->val[7]);

    Mat* image = static_cast<Mat*>(userdata->val[8]);

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
    int xNeg = 0 - image->cols / 2;
    int xPos = image->cols - image->cols / 2 - 1;
    int yNeg, yPos;
    if (image->rows % 2 == 1)
    {
        yNeg = 0 - image->cols / 2;
        yPos = image->rows - image->rows / 2 - 1;
    }
    else
    {
        yNeg = 0 - image->cols / 2 + 1;
        yPos = image->rows - image->rows / 2;
    }

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

void calcRotationMat(void* userdata)
{
#pragma region Casting of the data

    Vec<void*, 9>* data = static_cast<Vec<void*, 9>*>(userdata);
    Vec3i* sphereCoordinates = static_cast<Vec3i*>(data->val[0]);
    Mat* rotationMat = static_cast<Mat*>(data->val[2]);

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

    *rotationMat = rotMatZ * (((cos(sphereCoordinates->val[2] * PI / 180) * rotMatX)) + (1 - (cos(sphereCoordinates->val[2] * PI / 180)) * rotMatY));
}

Mat calcCameraImage(void* userdata)
{
    calcCameraPosition(userdata);

#pragma region Casting of the data

    Vec<void*, 9>* data = static_cast<Vec<void*, 9>*>(userdata);
    Point3d* cameraPosition = static_cast<Point3d*>(data->val[1]);
    Mat* rotationMat = static_cast<Mat*>(data->val[2]);
    std::vector<Point2f>* sourceImagePoints = static_cast<std::vector<Point2f>*>(data->val[4]);
    std::vector<Point2f>* sourceImagePointsShift = static_cast<std::vector<Point2f>*>(data->val[5]);
    std::vector<Point2f>* cameraImagePoints = static_cast<std::vector<Point2f>*>(data->val[6]);
    Mat* intrinsicCameraMat = static_cast<Mat*>(data->val[7]);
    Mat* image = static_cast<Mat*>(data->val[8]);

#pragma endregion

    Mat extrinsicCameraMat = Mat_<double>(3, 4);    
    // Fill the extrinsic camera parameter matrix
    for (int cY = 0; cY < 3; cY++)
        for (int cX = 0; cX < 3; cX++)
            extrinsicCameraMat.at<double>(cY, cX) = rotationMat->at<double>(cY, cX);
    extrinsicCameraMat.at<double>(0, 3) = cameraPosition->x;
    extrinsicCameraMat.at<double>(1, 3) = cameraPosition->y;
    extrinsicCameraMat.at<double>(2, 3) = cameraPosition->z;
    
    Mat pointIn3D = Mat_<double>(4, 1);
    // Fill the point vector from the image
    pointIn3D.at<double>(0, 2) = 0;
    pointIn3D.at<double>(0, 3) = 1;

    int c = 0;
    std::vector<Point2f> destinationPoints;
    for each (Point2f point in *sourceImagePointsShift)
    {
        pointIn3D.at<double>(0, 0) = point.x;
        pointIn3D.at<double>(0, 1) = point.y;

        Mat tempPoint = *intrinsicCameraMat * (extrinsicCameraMat * pointIn3D);

        point.x = tempPoint.at<double>(0, 0) / tempPoint.at<double>(0, 2);
        point.y = tempPoint.at<double>(0, 1) / tempPoint.at<double>(0, 2);

        if (c < sourceImagePointsShift->size() - 1) 
            destinationPoints.push_back(point);
        c++;
    }

    //Centering of the image
    Point2f outputCenter = sourceImagePointsShift->at(sourceImagePointsShift->size() - 1);
    Point2f centerOffset = outputCenter - Point2f(255, 255);
    for each (Point2f destinationPoint in destinationPoints)
        destinationPoint -= centerOffset;
    outputCenter -= centerOffset;

    //Create homography
    Mat homography = findHomography(*sourceImagePoints, destinationPoints, 0);

    //Transform the source image
    Mat sourceImageWarped;
    warpPerspective(*image, sourceImageWarped, homography, Size(512, 512));

    //Save the data
    destinationPoints.push_back(outputCenter);
    *cameraImagePoints = destinationPoints;
    return sourceImageWarped;
}

void calcCameraPosition(void* userdata)
{
#pragma region Casting of the data

    Vec<void*, 9>* data = static_cast<Vec<void*, 9>*>(userdata);
    Vec3i* sphereCoordinates = static_cast<Vec3i*>(data->val[0]);
    Point3d* cameraPosition = static_cast<Point3d*>(data->val[1]);

#pragma endregion
    
#pragma region Calculating the new camera position

    //Calculate the lengt of the vector on the x-y-plane
    double lengthOnXY = sphereCoordinates->val[0] * sin(sphereCoordinates->val[1] * PI / 180);

    //Calculate the coordinates on the x and y axis with the vector
    cameraPosition->x = lengthOnXY * cos(sphereCoordinates->val[2] * PI / 180);
    cameraPosition->y = lengthOnXY * sin(sphereCoordinates->val[2] * PI / 180);
    //Calculate the coordinate on the z axis with theta
    cameraPosition->z = sphereCoordinates->val[0] * cos(sphereCoordinates->val[1] * PI / 180);

#pragma endregion
}

Mat calcAffineTransformation(void* userdata)
{
#pragma region Casting of the data

    Vec<void*, 9>* data = static_cast<Vec<void*, 9>*>(userdata);
    Vec3i* affineTransValues = static_cast<Vec3i*>(data->val[3]);
    std::vector<Point2f>* sourcePoints = static_cast<std::vector<Point2f>*>(data->val[4]);
    std::vector<Point2f>* cameraImagePoints = static_cast<std::vector<Point2f>*>(data->val[6]);
    Mat* image = static_cast<Mat*>(data->val[8]);

#pragma endregion

    if (cameraImagePoints->size() == 0)
        return Mat();

    // Filling the needed matrices
    Mat scalingMat = (Mat_<double>(2, 2) <<
        affineTransValues->val[2], 0,
        0, 1);
    Mat rotMatAlpha = (Mat_<double>(2, 2) <<
        cos(affineTransValues->val[0] * PI / 180), -sin(affineTransValues->val[0] * PI / 180),
        sin(affineTransValues->val[0] * PI / 180), cos(affineTransValues->val[0] * PI / 180));
    Mat rotMatBeta = (Mat_<double>(2, 2) <<
        cos(affineTransValues->val[1] * PI / 180), -sin(affineTransValues->val[1] * PI / 180),
        sin(affineTransValues->val[1] * PI / 180), cos(affineTransValues->val[1] * PI / 180));

    //Calculation for the augmented matrix
    Mat augmentedMat = rotMatAlpha * (-rotMatBeta * (scalingMat * rotMatBeta));

    //Fill the transormation matrix
    Mat transformMat = (Mat_<double>(3, 3) <<
        augmentedMat.at<double>(0, 0), augmentedMat.at<double>(0, 1), image->cols / 2,
        augmentedMat.at<double>(1, 0), augmentedMat.at<double>(1, 1), image->rows / 2,
        0, 0, 1);

    //Fill the point vector from the image
    Mat pointIn2D = Mat_<double>(3, 1);
    pointIn2D.at<double>(0, 2) = 1;

    int c = 0;
    std::vector<Point2f> destinationPoints;
    for each (Point2f cameraPoint in *cameraImagePoints)
    {
        pointIn2D.at<double>(0, 0) = cameraPoint.x;
        pointIn2D.at<double>(0, 1) = cameraPoint.y;

        Mat tempPoint = transformMat * pointIn2D;

        cameraPoint.x = tempPoint.at<double>(0, 0) / tempPoint.at<double>(0, 2);
        cameraPoint.y = tempPoint.at<double>(0, 1) / tempPoint.at<double>(0, 2);

        if (c < cameraImagePoints->size() - 1)  
            destinationPoints.push_back(cameraPoint);
        c++;
    }

    //Centering of the image
    Point2f outputCenter = cameraImagePoints->at(cameraImagePoints->size() - 1);
    Point2f centerOffset = outputCenter - Point2f(255, 255);
    for each (Point2f destinationPoint in destinationPoints)
        destinationPoints.at(c) -= centerOffset;

    //Create homography
    Mat homography = findHomography(*sourcePoints, destinationPoints, 0);

    //Transform the source image
    Mat sourceWarped;
    warpPerspective(*image, sourceWarped, homography, Size(512, 512));

    return sourceWarped;
}
