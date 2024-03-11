/*********************************************************************************************/
#include <opencv2/opencv.hpp>
/*********************************************************************************************/
int main() 
{
    cv::VideoCapture capture(0);
    if (!capture.isOpened()) 
    {
        std::cerr << "cannot access cam" << std::endl;
        return -1;
    }
    
    cv::Mat frame, gray, canny_img, mask, and_mask;
    while (true) 
    {
        bool isCapture = capture.read(frame);
        if (!isCapture) 
        {
            std::cerr << "cannot access cam" << std::endl;
            break;
        }
        
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        cv::Canny(gray, canny_img, 0, 255);
        cv::adaptiveThreshold(gray, mask, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY_INV, 3, 3);
        cv::bitwise_and(mask, canny_img, and_mask);
        
        int nonzero_area = cv::countNonZero(and_mask);
        if (nonzero_area < 100) 
        {
            std::cout << "camera blocked" << std::endl;
            cv::putText(frame, "CAMERA IS BLOCKED", cv::Point(20, 50), cv::FONT_HERSHEY_PLAIN, 5, cv::Scalar(0, 0, 255), 1, cv::LINE_AA, false);
        }
        
        cv::imshow("frame", frame);
        char key = static_cast<char>(cv::waitKey(1));
        if (key == 'q') 
        {
            std::cout << "terminating the program" << std::endl;
            break;
        }
    }
    
    capture.release();
    cv::destroyAllWindows();
    return 0;
}
/*********************************************************************************************/



