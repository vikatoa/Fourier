#include <opencv2/opencv.hpp>
#include <iostream>

// g++ capture_image.cpp -o prog `pkg-config --cflags --libs opencv4` && ./prog

int main() {
    // Open default camera (usually /dev/video0)
    cv::VideoCapture cap("v4l2src device=/dev/video0 ! video/x-raw, width=640, height=480, framerate=30/1 ! videoconvert ! appsink", cv::CAP_GSTREAMER);

    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open camera." << std::endl;
        return -1;
    }

    cv::Mat frame;
    cap >> frame;  // Capture one frame

    if (frame.empty()) {
        std::cerr << "Error: Captured empty frame." << std::endl;
        return -1;
    }

    // Save image
    cv::imwrite("data/capture.jpg", frame);
    std::cout << "Image saved to capture.jpg" << std::endl;

    return 0;
}