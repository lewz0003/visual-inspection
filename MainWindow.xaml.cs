using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;

using Xenics.Xeneth;
using Inspection; //suakit


namespace CRP6_GUI
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        XenethCam camera = null;
        string imageDirection = ".\\..\\..\\..\\..\\Image Results\\";
        string imageNaming = null;
        string fileName = null;
        int procFileFlag = 1;

        //string imgFilePathHard = "C:/Users/Inspection/Desktop/crp6/crp6-commercialaievaluation/Image Results/batch_";
        string dateTimeString;
        string modelPath;
        bool modelChanged = false;
        int firstPos;
        int lastPos;
        bool isModel = false;
        string modelName = "DynamoModel";
        string imageName;

        //int folderCounter = 0;

        private DispatcherTimer timer;
        //int frameCount = 0;

        ImageProcessing imgProc;//suakit

        public MainWindow()
        {
            InitializeComponent();
            Snackbar.MessageQueue.Enqueue("Welcome Inspection Team");
            camera = new XenethCam();
            imgProc = new ImageProcessing();//suakit
            //defectList = new List<double>();

            //while (System.IO.Directory.Exists(imgFilePathHard + folderCounter))
            //{
            //    folderCounter++;
            //}
            dateTimeString = DateTime.Now.ToString(@"MM_dd_yyyy hhmmss tt");

            timer = new DispatcherTimer { Interval = TimeSpan.FromTicks(1) };   //FromMilliseconds(1) or FromTicks(1)
            timer.Tick += TimerTick;
        }

        private void TimerTick(object sender, EventArgs e)
        {
            //var watch = System.Diagnostics.Stopwatch.StartNew();
            //frameCount++;
            StreamGrid.Children.Clear();
            Image streamImage = camera.GetStreamFrame();
            StreamGrid.Children.Add(streamImage);
            //var elapsedMs = watch.ElapsedMilliseconds;
            //Console.WriteLine(elapsedMs + " ms"); // maintain 40ms to achieve 25fps
        }

        private void LoadCalibrationBtn_Click(object sender, RoutedEventArgs e)
        {
            string filename = CalibrationFile.Text;
            bool x = false;
            x = camera.LoadCalibration(filename);
            if (x == true)
            {
                Snackbar.MessageQueue.Enqueue("Calibration Loaded");
                StreamBtn.IsEnabled = true;
                CaptureBtn.IsEnabled = true;
            }
            else
            {
                Snackbar.MessageQueue.Enqueue("Calibration Not Loaded");
                StreamBtn.IsEnabled = false;
                CaptureBtn.IsEnabled = false;
            }
        }

        private void ConnectTog_Checked(object sender, RoutedEventArgs e)
        {
            bool x = false;
            x = camera.Connect();
            if (x == true)
            {
                Snackbar.MessageQueue.Enqueue("Connected");
                //StreamBtn.IsEnabled = true;
                //CaptureBtn.IsEnabled = true;
                LoadCalibrationBtn.IsEnabled = true;
                LoadCalibrationBtn_Click(sender, e);   //autostream
                StreamBtn_Checked(sender, e);          //autostream           
            }
            else
            {
                Snackbar.MessageQueue.Enqueue("Not connected");
                LoadCalibrationBtn.IsEnabled = false;
                ConnectTog.IsChecked = false;
            }
        }

        private void ConnectTog_Unchecked(object sender, RoutedEventArgs e)
        {
            timer.Stop();
            try
            {
                bool x = false;
                x = camera.Disconnect();
                if (x == false)
                {
                    Snackbar.MessageQueue.Enqueue("Disconnected");
                    StreamBtn.IsEnabled = false;
                    CaptureBtn.IsEnabled = false;
                }
                else
                    Snackbar.MessageQueue.Enqueue("Unable to disconnected");
            }
            catch (Exception ex)
            {
                Console.WriteLine("Exception caught: " + ex);
            }
        }

        private void StreamBtn_Checked(object sender, RoutedEventArgs e)
        {
            timer.Start();
            Play.Visibility = Visibility.Collapsed;
        }

        private void StreamBtn_Unchecked(object sender, RoutedEventArgs e)
        {
            timer.Stop();
            Play.Visibility = Visibility.Visible;
        }

        private void CaptureBtn_Click(object sender, RoutedEventArgs e) 
        {
            imageName = ImageNaming.Text;
            RawImageDisplay.Children.Clear();
            ProcessedImageDisplay.Children.Clear();
            //imageCount++; 
            fileName = camera.GetFrame(imageName, dateTimeString, modelName);//foldercounter removed

            if (fileName == "Error")
            {
                Snackbar.MessageQueue.Enqueue("Image not captured");
                return;
            }
            else
            {
                Image rawImage = camera.DisplayImage();
                RawImageDisplay.Children.Add(rawImage);

                procFileFlag = imgProc.SegmentationEvaluatorTest();//suakit

                if (procFileFlag != 1)
                {
                    //if (procFileFlag == 2) Snackbar.MessageQueue.Enqueue("Folder and image do not exist");
                    if (procFileFlag == 3) Snackbar.MessageQueue.Enqueue("Image does not exist");
                    Image processedImage = camera.DisplayProcessed();
                    ProcessedImageDisplay.Children.Add(processedImage);

                    ViewBadge.Badge = fileName;
                    if (CountingBadge.Badge == null || Equals(CountingBadge.Badge, ""))
                        CountingBadge.Badge = 0;

                    var next = int.Parse(CountingBadge.Badge.ToString()) + 1;
                    CountingBadge.Badge = next < 9999 ? (object)next : null; //set counter up to 9999 then reset
                }
                else
                {
                    Snackbar.MessageQueue.Enqueue("Image not processed");
                }
            }
        }

        private void ExitBtn_Click(object sender, RoutedEventArgs e)
        {
            Application.Current.Shutdown();
        }

        private void PhotoDirectBtn_Click(object sender, RoutedEventArgs e)
        {
            System.Diagnostics.Process.Start("explorer.exe", imageDirection);
        }

        private void ViewBtn_Click(object sender, RoutedEventArgs e)
        {
            ViewBtn.IsEnabled = false;
        }

        private void ReturnBtn_Click(object sender, RoutedEventArgs e)
        {
            ViewBtn.IsEnabled = true;
            //ViewBadge.Badge = "yolo"; //test badge
        }

        private void TestSuaKIT_Click(object sender, RoutedEventArgs e)
        {
            //procFileFlag = imgProc.SegmentationEvaluatorTest(folderCounter);
            if (procFileFlag == 3) Snackbar.MessageQueue.Enqueue("Image does not exist");
            else if (procFileFlag == 1) Snackbar.MessageQueue.Enqueue("Image not processed");
            else
            {
                Image processedImage = camera.DisplayProcessed();
                ProcessedImageDisplay.Children.Add(processedImage);
            }
        }

        private void Grid_MouseDown(object sender, MouseButtonEventArgs e)
        {
            DragMove();
        }

        private void Model_Click(object sender, RoutedEventArgs e)
        {
            isModel = true;

            Microsoft.Win32.OpenFileDialog dlg = new Microsoft.Win32.OpenFileDialog();

            // Set filter for file extension and default file extension 
            dlg.DefaultExt = ".net";
            dlg.Filter = "Model Files (*.net)|*.net";

            // Display OpenFileDialog by calling ShowDialog method 
            Nullable<bool> result = dlg.ShowDialog();

            // Get the selected file name and display in a TextBox 
            if (result == true)
            {
                // Open document 
                modelPath = dlg.FileName;
                //Console.WriteLine(modelPath);

                firstPos = modelPath.LastIndexOf("\\");
                string str1 = modelPath.Substring(firstPos+1);
                //Console.WriteLine(str1);
                lastPos = str1.IndexOf(".");
                modelName = str1.Remove(lastPos);
                Console.WriteLine("Load model: "+ modelName);

                char[] modelPathArr = modelPath.ToCharArray();
                //Console.WriteLine(modelPathArr);

                for (int i = 0; i < modelPathArr.Length; i++)
                {
                    sbyte vOut = Convert.ToSByte(modelPathArr[i]);
                    imgProc.pathArr(vOut, i);//suakit
                }
                sbyte[] sbytes = Array.ConvertAll(modelPathArr, q => Convert.ToSByte(q));

                //unsafe //need to enable /unsafe
                //{
                //    fixed (sbyte* PtrSbyte = sbytes)
                //    {
                //        modelChanged = imgProc.changeModel(PtrSbyte);
                //    }
                //}

                modelChanged = imgProc.changeModel();//suakit
                if (modelChanged == true)
                {
                    Snackbar.MessageQueue.Enqueue("Model changed");
                    modelChanged = false;
                }
                else
                {
                    Snackbar.MessageQueue.Enqueue("Model unchanged");
                }
                isModel = false;
            }
        }

    }
}
