# CameraBlocked.cpp
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

# CameraTampering.cpp
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
