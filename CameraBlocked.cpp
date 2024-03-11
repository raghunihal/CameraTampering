/**********************************************************************************************
This C++ code uses the OpenCV library to access the camera and perform some image processing operations. 
First, it includes the necessary header file for the OpenCV library. Then, in the main function, it creates a VideoCapture object named "capture" to access the camera. 
If the camera cannot be opened, it prints an error message and returns -1. Next, 
it declares several Mat objects to store the frames and intermediate results of the image processing operations. 
Inside a while loop that runs indefinitely, it reads a frame from the camera using the "capture.read()" function. 
If the frame cannot be captured, it prints an error message and breaks out of the loop. 
The code then performs the following image processing operations on the captured frame: 
1. Converts the frame to grayscale using the "cv::cvtColor()" function. 
2. Applies the Canny edge detection algorithm to the grayscale image using the "cv::Canny()" function. 
3. Applies adaptive thresholding to the grayscale image using the "cv::adaptiveThreshold()" function. 
4. Performs a bitwise AND operation between the thresholded image and the Canny edge image using the "cv::bitwise_and()" function. 
   After that, it calculates the number of non-zero pixels in the resulting image using the "cv::countNonZero()" function. 
   If the number of non-zero pixels is less than 100, it prints a message indicating that the camera is blocked and overlays the message on the frame using the "cv::putText()" function. 
   Finally, it displays the frame in a window named "frame" using the "cv::imshow()" function. It waits for a key press using the "cv::waitKey()" function and checks if the pressed key is 'q'. 
   If so, it prints a message indicating that the program is terminating and breaks out of the loop. 
   Outside the loop, it releases the camera using the "capture.release()" function and destroys all the created windows using the "cv::destroyAllWindows()" function. 
   The program then returns 0 to indicate successful execution.


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

