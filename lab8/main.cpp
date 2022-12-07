#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2\opencv.hpp>
#include <iostream>

int main(int argc, char** argv)
{
    using namespace cv;
    VideoCapture vc(0);
    if (!vc.isOpened() ) return 1;
    cv::Mat frame;

    cv::namedWindow("Window", WINDOW_AUTOSIZE); // Create a window for display.
    int i = 0;
    while (waitKey(10) != 27) {
        vc >> frame;
//        std::cout << "frame info: " << frame.rows << " " << frame.cols << std::endl;
//        imwrite("frame" + std::to_string(i++) + ".png", frame);
//        cv::flip(frame, frame, 1);

        // Convert input image to HSV
        cv::cvtColor(frame, frame, cv::COLOR_BGR2HSV);
        MatExpr maxElement= cv::max(frame,cv::COLOR_BGR2HSV);

        Point p1(0, 0), p2(100, 0);
        Point p3(200, 0), p4(500, 500);
        int thickness = 2;
        line(frame, p1, p3, Scalar(255, 0, 0),
             thickness, LINE_8);
        cv::imshow("Frame", frame);




    }
    return 0;
}