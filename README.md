#CameraBlocked.cpp
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
