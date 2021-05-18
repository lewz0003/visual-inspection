# visual-inspection

visual inspection system (neural network method)

Process image using suaKIT
Capture image using Xenics infared camera

MainWindow.xaml is the User Interface of the program. It includes features such as live feed(Stream), image displays, 
processed image display, image directory, name input, camera calibration format file, change NN model, 
camera intitalisation(Connect), camera capture current frame(GrabFrame).

XenethCam.cs is the API writen to enable the functions of the camera. Functions in XenethCam.cs are called from MainWindow.xaml.
Filepath logic is implemented here that make use of computer clock to obtain the date and time. The aim is to 
provide ease in user file naming and to eliminate bugs arises from reusing same name. 

*Note: the code has not been cleaned due to reference reasons.
main.cpp encapsulates neural network integration. It retrieves captured image and process it against a selected NN model. 
An output image will be produced that contains information such as a rectangle box - containing the feature detected and 
its probability & uncertainty. 
