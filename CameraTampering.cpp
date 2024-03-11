//https://medium.com/@simranjenny84/camera-tampering-detection-81b25f0d7383
/*********************************************************************************************/
#include <opencv2/opencv.hpp>
#include <vector>
/*********************************************************************************************/
int main() 
{
    cv::VideoCapture cap(0);
    cv::Ptr<cv::BackgroundSubtractorMOG2> fgbg = cv::createBackgroundSubtractorMOG2();
    cv::Mat frame, fgmask;
    bool ret = cap.read(frame);
    fgmask = fgbg->apply(frame);
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    
    while (true) 
    {
        ret = cap.read(frame);
        if (frame.empty()) 
        {
            std::cout << "End of frame" << std::endl;
            break;
        } 
        else 
        {
            int a = 0;
            std::vector<cv::Rect> bounding_rect;
            fgmask = fgbg->apply(frame);
            cv::erode(fgmask, fgmask, kernel, cv::Point(-1, -1), 5);
            cv::dilate(fgmask, fgmask, kernel, cv::Point(-1, -1), 5);
            cv::imshow("frame", frame);
            std::vector<std::vector<cv::Point>> contours;
            cv::findContours(fgmask, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
            for (size_t i = 0; i < contours.size(); i++) 
            {
                bounding_rect.push_back(cv::boundingRect(contours[i]));
            }
            for (size_t i = 0; i < contours.size(); i++) 
            {
                if (bounding_rect[i].width >= 40 || bounding_rect[i].height >= 40) 
                {
                    a += bounding_rect[i].width * bounding_rect[i].height;
                }
                if (a >= static_cast<int>(frame.total()) / 3) 
                {
                    cv::putText(frame, "CAMERA TAMPERING DETECTED", cv::Point(5, 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 255, 255), 2);
                }
                cv::imshow("frame", frame);
            }
        }
        //releasing camera and closing all the windows
        int k = cv::waitKey(30) & 0xff;
        if (k == 27) 
        {
            break;
        }
    }
    
    cap.release();
    cv::destroyAllWindows();
    return 0;
}
