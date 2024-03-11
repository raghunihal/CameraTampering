//https://medium.com/@simranjenny84/camera-tampering-detection-81b25f0d7383
/************************************************************************************************
This code is written in C++ and uses the OpenCV library for computer vision tasks. 
The code starts by including the necessary header files for OpenCV and the vector library. 
In the main function, it creates a VideoCapture object named "cap" to capture video from the default camera (index 0). 
Then, it creates a BackgroundSubtractorMOG2 object named "fgbg" using the createBackgroundSubtractorMOG2 function from OpenCV. 
This object is used to perform background subtraction on the video frames. 
Next, it declares two Mat objects named "frame" and "fgmask" to store the current frame and the foreground mask obtained from background subtraction. 
The code then reads the first frame from the video capture using the read function of the VideoCapture object. 
It applies the background subtraction algorithm to the frame using the apply function of the BackgroundSubtractorMOG2 object, and stores the result in the fgmask variable. 
After that, it creates a kernel for morphological operations using the getStructuringElement function. 
The code then enters a while loop that continues until the user presses the "Esc" key. 
Inside the loop, it reads the next frame from the video capture and checks if the frame is empty. 
If it is empty, it means that the end of the video has been reached, so the loop is exited. 
If the frame is not empty, it initializes an integer variable "a" to 0 and declares a vector of Rect objects named "bounding_rect" to store the bounding rectangles of the detected objects. 
It applies the background subtraction algorithm to the current frame and stores the result in the fgmask variable. 
Then, it performs morphological operations (erosion and dilation) on the fgmask using the erode and dilate functions. 
It displays the current frame using the imshow function. Next, it finds contours in the fgmask using the findContours function and stores them in a vector of vector of Point objects named "contours". 
It then iterates over the contours and calculates the bounding rectangles for each contour using the boundingRect function. 
The bounding rectangles are stored in the bounding_rect vector. 
After that, it iterates over the bounding_rect vector and checks if the width or height of each bounding rectangle is greater than or equal to 40. 
If it is, it adds the area of the bounding rectangle to the variable "a". 
If the value of "a" is greater than or equal to one-third of the total number of pixels in the frame, it means that camera tampering has been detected. 
In that case, it adds a text overlay to the frame using the putText function. Finally, it displays the frame with the text overlay using the imshow function. 
The code then waits for a key press for 30 milliseconds using the waitKey function. If the pressed key is the "Esc" key (ASCII value 27), the loop is exited. 
After the loop, it releases the video capture object and destroys all the windows created by OpenCV. 
The main function returns 0 to indicate successful execution of the program.
**************************************************************************************************/
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
        } else 
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
/*********************************************************************************************/

