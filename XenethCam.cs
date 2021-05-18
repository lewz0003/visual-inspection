using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Xenics.Xeneth;

using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.IO;

namespace CRP6_GUI
{
    class XenethCam
    {
        #region VARIABLES
        // Settings

        // Private Variables
        private bool isConnected = false;
        private bool isStreaming = false;

        private XCamera camera = null;                          // XCamera object
        private ushort[] frameBuffer = null;                    // frame buffer
        private int imageCount = 0;                             // imagefile counter
        private string imageNameXeneth = "XenethImage";         // imagefile name
        //string imgFilePath = ".\\..\\..\\..\\..\\Image Results\\batch";
        string caliFilePath = ".\\..\\..\\..\\..\\Calibrations\\";

        string imgFilePathHard = "C:/Users/Inspection/Desktop/crp6/crp6-commercialaievaluation/Image Results/";

        string upFilePath;
        string upFullFilePath;
        string upProcFullFilePath;

        MemoryStream memoryStream = new MemoryStream();     //for streaming
        int Width = 640;                                    //for streaming
        int Height = 512;                                   //for streaming


        #endregion

        #region PUBLIC FUNCTIONS

        // Constructor
        public XenethCam()
        {

        }

        public bool GetStreamingState()
        {
            return isStreaming;
        }

        public bool GetConnectionState()
        {
            return isConnected;
        }

        public bool LoadCalibration(string caliFileName)
        {
            try
            {
                caliFileName = caliFilePath + caliFileName + ".xca";
                camera.LoadCalibration(caliFileName, XLoadCalibrationFlags.StartSoftwareCorrection);
                return true;
            }
            catch (XenethException ex)
            {
                Console.WriteLine("XenethException occurred: {0}", ex.Message);
                return false;
            }
        }

        public bool Connect()
        {

            if (isConnected)
                return false;

            try
            {
                Console.WriteLine("Connecting to cam://0");
                camera = new XCamera("cam://0");

                if (camera.Initialised)
                {
                    isConnected = true;

                    Console.WriteLine("Camera connected.");
                }
            }
            catch (XenethException ex)
            {
                Console.WriteLine("XenethException occurred: {0}", ex.Message);
            }
            return isConnected;
        }

        public bool Disconnect()
        {
            Console.WriteLine("isConnected: " + isConnected);
            if (isConnected == false || camera == null)
            {
                Console.WriteLine("Cannot disconnect camera");
                return isConnected;
            }

            try
            {
                if (camera.Capturing)
                {
                    Console.WriteLine("Stop capturing");
                    camera.StopCapture();
                }

                // CLose connection with the camera.
                Console.WriteLine("Disconnecting camera");
                camera.Close();
                isConnected = false;
            }
            catch (Exception ex)
            {
                Console.WriteLine("Exception caught: " + ex);
            }
            return isConnected;
        }

        public Image GetStreamFrame()
        {
            if (camera.Initialised)
            {
                camera.StartCapture();

                if (camera.Capturing)
                {
                    UInt32 frameSize = camera.FrameSize;
                    frameBuffer = new ushort[frameSize / 2];
                    camera.GetFrame(FrameType.Native, XGetFrameFlags.Blocking, frameBuffer, frameSize); //blocking

                    var bitmapSrc = BitmapSource.Create(Width, Height, 96, 96,
                                    PixelFormats.Gray16, null, frameBuffer, Width * 2);
                    TiffBitmapEncoder encoder = new TiffBitmapEncoder();
                    encoder.Compression = TiffCompressOption.Zip;
                    encoder.Frames.Add(BitmapFrame.Create(bitmapSrc));
                    encoder.Save(memoryStream);

                    {
                        var bitmap = new BitmapImage();
                        bitmap.BeginInit();
                        bitmap.StreamSource = memoryStream;
                        bitmap.CacheOption = BitmapCacheOption.OnLoad;
                        bitmap.EndInit();
                        //bitmap.Freeze();

                        FormatConvertedBitmap grayBitmapSource = new FormatConvertedBitmap();
                        grayBitmapSource.BeginInit();
                        grayBitmapSource.Source = bitmap;
                        grayBitmapSource.DestinationFormat = PixelFormats.Gray32Float;
                        grayBitmapSource.EndInit();

                        Image grayImage = new Image();
                        grayImage.Width = 640;
                        grayImage.Source = grayBitmapSource;

                        memoryStream.SetLength(0);//to clear memorystream

                        return grayImage;
                    }
                }
                else return null; 
            }
            else
            {
                Console.WriteLine("Camera not initialised");
                return null; 
            }
        }

        public string GetFrame(string imageName, string dateTimeString, string modelName) //foldercounter removed
        {
            if (camera.Initialised) 
            {
                Console.WriteLine("Start capturing.");
                camera.StartCapture();

                if (camera.Capturing)
                {
                    if (imageName != "")
                    {
                        if (imageNameXeneth != imageName)
                        { imageCount = 0; }
                        imageNameXeneth = imageName;
                    }
                
                    UInt32 frameSize = camera.FrameSize;
                    frameBuffer = new ushort[frameSize / 2];
                    camera.GetFrame(FrameType.Native, XGetFrameFlags.Blocking, frameBuffer, frameSize); //blocking

                    upFilePath = imgFilePathHard + dateTimeString; //foldercounter removed
                    Console.WriteLine("GetFrame:"+upFilePath);
                    System.IO.Directory.CreateDirectory(upFilePath);

                    upFullFilePath = upFilePath + "/" + imageNameXeneth + "_" + imageCount + "_" + modelName + ".png";
                    upProcFullFilePath = upFilePath + "/Processed Images/" + imageNameXeneth + "_" + imageCount + "_" + modelName + "_Processed.png";

                    camera.SaveData(upFullFilePath, XSaveDataFlags.Force16); //force16bit
                    imageCount++;
                    Console.WriteLine("Captured.");
                    Console.WriteLine(imageNameXeneth + "_" + imageCount + "_" + modelName);
                    return imageNameXeneth + "_" + imageCount + "_" + modelName; //modelPath unuse
                }
                return "Error";
            }
            else
            {
                Console.WriteLine("Camera not initialised");
                return "Error";
            }
        }

        public Image DisplayImage()//raw
        {
            // Create a BitmapSource   
            BitmapImage bitmap = new BitmapImage();
            bitmap.BeginInit();

            Console.WriteLine("DisplayRaw:"+upFullFilePath);
            if (File.Exists(upFullFilePath) != true)
            {
                Console.WriteLine("file does not exist");
                return null; 
            }
            bitmap.UriSource = new Uri(upFullFilePath);
            bitmap.EndInit();

            // Create a FormatConvertedBitmap   
            FormatConvertedBitmap grayBitmapSource = new FormatConvertedBitmap();

            // BitmapSource objects like FormatConvertedBitmap can only have their properties   
            // changed within a BeginInit/EndInit block.   
            grayBitmapSource.BeginInit();

            // Use the BitmapSource object defined above as the source for this new    
            // BitmapSource (chain the BitmapSource objects together).   
            grayBitmapSource.Source = bitmap;

            // Key of changing the bitmap format is DesitnationFormat property of BitmapSource.   
            // It is a type of PixelFormat. FixelFormat has dozens of options to set    
            // bitmap formatting.    
            grayBitmapSource.DestinationFormat = PixelFormats.Gray32Float;
            grayBitmapSource.EndInit();

            // Create a new Image   
            Image grayImage = new Image();
            grayImage.Width = 640;
            // Set Image source to new FormatConvertedBitmap   
            grayImage.Source = grayBitmapSource;

            // Add Image to Window 
            Console.WriteLine("displayed raw image");
            return grayImage;
        }

        public Image DisplayProcessed()//processed
        {
            //upProcFullFilePath
            BitmapImage bitmap = new BitmapImage();
            bitmap.BeginInit();

            Console.WriteLine("DisplayProccessed:" + upProcFullFilePath);
            if (File.Exists(upProcFullFilePath) != true)
            {
                Console.WriteLine("Processed file does not exist");
                return null;
            }
            bitmap.UriSource = new Uri(upProcFullFilePath);
            bitmap.EndInit();

            FormatConvertedBitmap rgbBitmapSource = new FormatConvertedBitmap();
            rgbBitmapSource.BeginInit();  
            rgbBitmapSource.Source = bitmap;   
            rgbBitmapSource.DestinationFormat = PixelFormats.Bgr32;
            rgbBitmapSource.EndInit();

            Image rgbImage = new Image();
            rgbImage.Width = 640;
            rgbImage.Source = rgbBitmapSource;

            Console.WriteLine("displayed proccessed image");
            return rgbImage;
        }

        //public void CoolingControl()
        //{
        //    //CoolingMode =                          //Values: Temperature (0), Power (1)

        //    //CoolingTargetTemperature = 322         //49degree(<50degree)
        //    //if(CoolingTargetTemperatureReached == 1)

        //    //CoolingPower=69                        //<70% power
        //    //CoolingMaximalPower=69  ??
        //    //if(CoolingActualPower =< CoolingMaximalPower)

        //}

        #endregion
    }
}
