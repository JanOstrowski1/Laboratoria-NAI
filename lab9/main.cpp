#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

bool compareContourAreas(vector<Point> contour1, vector<Point> contour2) {
    double i = fabs(contourArea(Mat(contour1)));
    double j = fabs(contourArea(Mat(contour2)));
    return (i < j);
}

int main(int argc, char **argv) {
    vector<int> lower = {0, 141, 87};
    vector<int> upper = {15, 255, 255};


    VideoCapture camera(0);
    if (!camera.isOpened())
        return -1;

    while (waitKey(1) != 27) {
        Mat src_img;

        camera.read(src_img);
        Mat bw_img;
        Mat red_img;

        imshow("ArUco", src_img);
    }
    return 0;
}