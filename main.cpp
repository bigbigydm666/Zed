/*
 *                   江城子 . 程序员之歌
 * 
 *               十年生死两茫茫，写程序，到天亮。
 *                   千行代码，Bug何处藏。
 *               纵使上线又怎样，朝令改，夕断肠。
 * 
 *               领导每天新想法，天天改，日日忙。
 *                   相顾无言，惟有泪千行。
 *               每晚灯火阑珊处，夜难寐，加班狂。
 * 
 */

/*
 *  ┌───┐   ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┐
 *  │Esc│   │ F1│ F2│ F3│ F4│ │ F5│ F6│ F7│ F8│ │ F9│F10│F11│F12│ │P/S│S L│P/B│  ┌┐    ┌┐    ┌┐
 *  └───┘   └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┘  └┘    └┘    └┘
 *  ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┬───┬───┐ ┌───┬───┬───┬───┐
 *  │~ `│! 1│@ 2│# 3│$ 4│% 5│^ 6│& 7│* 8│( 9│) 0│_ -│+ =│ BacSp │ │Ins│Hom│PUp│ │N L│ / │ * │ - │
 *  ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┼───┼───┤ ├───┼───┼───┼───┤
 *  │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │{ [│} ]│ | \ │ │Del│End│PDn│ │ 7 │ 8 │ 9 │   │
 *  ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ └───┴───┴───┘ ├───┼───┼───┤ + │
 *  │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │: ;│" '│ Enter  │               │ 4 │ 5 │ 6 │   │
 *  ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤     ┌───┐     ├───┼───┼───┼───┤
 *  │ Shift  │ Z │ X │ C │ V │ B │ N │ M │< ,│> .│? /│  Shift   │     │ ↑ │     │ 1 │ 2 │ 3 │   │
 *  ├─────┬──┴─┬─┴──┬┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤ ┌───┼───┼───┐ ├───┴───┼───┤ E││
 *  │ Ctrl│    │Alt │         Space         │ Alt│    │    │Ctrl│ │ ← │ ↓ │ → │ │   0   │ . │←─┘│
 *  └─────┴────┴────┴───────────────────────┴────┴────┴────┴────┘ └───┴───┴───┘ └───────┴───┴───┘
 */



#define MODE BLUE


#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/cvconfig.h>
#include <sl/Camera.hpp>
#include "ZED.hpp"
using namespace std;
using namespace cv;




int main(int argc, char **argv)
{
   //创建zed相机对象
   sl::Camera zed;
   //设置参数
   sl::InitParameters init_params;
   init_params.camera_resolution = sl::RESOLUTION::HD2K;
   init_params.depth_mode = sl::DEPTH_MODE::ULTRA;
   init_params.coordinate_units = sl::UNIT::METER;
   //f (argc > 1) init_params.input.setFromSVOFile(argv[1]);



   //打开相机
   sl::ERROR_CODE returned_state = zed.open();
   if (returned_state != sl::ERROR_CODE::SUCCESS) 
   {
      std::cout << "Error " << returned_state << ", exit program.\n";
      return EXIT_FAILURE;
   }

   //设置runtime参数
   
   cv::namedWindow("control", 1);
   sl::RuntimeParameters runtime_params;
   runtime_params.sensing_mode = sl::SENSING_MODE::STANDARD;
   runtime_params.confidence_threshold = 50;
   runtime_params.texture_confidence_threshold = 100;
   int hMax = 255, hMin = 136, sMax = 255, sMin = 0, vMax = 255, vMin = 0;
   switch (MODE)
   {
   case 1:
      zed.setCameraSettings(sl::VIDEO_SETTINGS::SATURATION, 8);
      zed.setCameraSettings(sl::VIDEO_SETTINGS::WHITEBALANCE_TEMPERATURE, 2800);

      hMax = 255, hMin = 136;

      break;
   case 2:
      zed.setCameraSettings(sl::VIDEO_SETTINGS::SATURATION, 8);
      zed.setCameraSettings(sl::VIDEO_SETTINGS::WHITEBALANCE_TEMPERATURE, 5600);    

      hMax = 187, hMin = 60;
      sMax = 255, sMin = 50;
   default:
      break;
   }
   cv::createTrackbar("hMax", "control", &hMax, 255);
   cv::createTrackbar("hMin", "control", &hMin, 255);
   cv::createTrackbar("sMax", "control", &sMax, 255);
   cv::createTrackbar("sMin", "control", &sMin, 255);
   cv::createTrackbar("vMax", "control", &vMax, 255);
   cv::createTrackbar("vMin", "control", &vMin, 255);
   

   // Prepare new image size to retrieve half-resolution images
   sl::Resolution image_size = zed.getCameraInformation().camera_resolution;
   int new_width = image_size.width;
   int new_height = image_size.height;


   sl::Resolution new_image_size(new_width, new_height);

   // To share data between sl::Mat and cv::Mat, use slMat2cvMat()
   // Only the headers and pointer to the sl::Mat are copied, not the data itself
   sl::Mat image_zed(new_width, new_height, sl::MAT_TYPE::U8_C4);
   cv::Mat image_ocv = slMat2cvMat(image_zed);


   sl::Mat depth_image_zed(new_width, new_height, sl::MAT_TYPE::U8_C4);
   cv::Mat depth_image_ocv = slMat2cvMat(depth_image_zed);

   sl::Mat point_cloud;

   Mat temp = imread("1.png", IMREAD_GRAYSCALE);
   vector<Mat> temp_contours;
   temp_contours.push_back(temp);
   if(temp.empty())
   {
      cerr<<"could not load image"<<endl;
      exit(1);
   }
   Rect ROIRECT = Rect(new_width/2 - 150, new_height/2 - 150, 300, 300);


   while(1)
   {

   if (zed.grab(runtime_params) == sl::ERROR_CODE::SUCCESS)
      {

      // Retrieve the left image, depth image in half-resolution
      zed.retrieveImage(image_zed, sl::VIEW::LEFT, sl::MEM::CPU, new_image_size);

      // retrieve CPU -> the ocv reference is therefore updated
      zed.retrieveImage(depth_image_zed, sl::VIEW::DEPTH, sl::MEM::CPU, new_image_size);

      // Retrieve the RGBA point cloud in half-resolution
      // To learn how to manipulate and display point clouds, see Depth Sensing sample
      zed.retrieveMeasure(point_cloud, sl::MEASURE::XYZRGBA, sl::MEM::CPU, new_image_size);

      // Display image and depth using cv:Mat which share sl:Mat data
      //cv::imshow("Image", image_ocv);
      cv::imshow("Depth", depth_image_ocv);

      //开始处理图像，寻找轮廓
      cv::Mat src = image_ocv.clone();
      medianBlur(src, src, 3);
      GaussianBlur(src, src, Size(5, 5), 0);
      Mat img = src.clone();
      rectangle(src, ROIRECT, Scalar(255, 255, 255));
      Mat kernel = getStructuringElement(MORPH_RECT, Size(9, 9));

      Mat roihsv;
      Mat roisrc = src(ROIRECT);
      cvtColor(roisrc, roihsv, COLOR_BGR2HSV);
      Mat roisrc2 = roisrc.clone();
      Mat temp1;
      inRange(roihsv, Scalar(hMin, sMin, vMin), Scalar(hMax, sMax, vMax), temp1);

      Mat redFeature = temp1;
      morphologyEx(redFeature, redFeature, MORPH_CLOSE, kernel);
      vector<vector<Point>> contours;
      findContours(redFeature, contours, 0, 1);
      Rect minRec;
      double pro = 1;
      double min_pro = 999;
      int min_pro_loc = -1;
      if(!contours.empty())
      {
         drawContours(roisrc, contours, -1, Scalar(128, 128, 240), 2);

      
         for(int i = 0; i < contours.size(); i++)
         {
            if(contourArea(contours[i]) < 1000)   continue;
            minRec = boundingRect(contours[i]);
            if(minRec.width >= minRec.height)   continue;
            pro = matchShapes(contours[i], temp_contours[0], CONTOURS_MATCH_I1, 0);
            if(pro < min_pro)
            {
               min_pro = pro;
               min_pro_loc = i;
            }
            //cout<<pro<<' '<<min_pro<<endl;
         } 
      }
      
      
      
      
      
      
      
      
      
      //框选并测距
      if(min_pro_loc>= 0)
      {  
         minRec = boundingRect(contours[min_pro_loc]);


         rectangle(roisrc, minRec, Scalar(0, 255, 0), 2);
         sl::float4 point3D;
         point_cloud.getValue(new_width/2 - 150 + minRec.x + 0.5*minRec.width, new_height/2 - 150 + minRec.y + 0.5*minRec.height, &point3D);
         float distance= sqrt(point3D.x*point3D.x + point3D.y*point3D.y + point3D.z*point3D.z);
			string text = "distance: " + std::to_string(distance/10) + " cm";
         putText(src, text, Point(50,50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 0), 4, 8);
      }
      
      
      
      
      
      
      
      
      int b = src.data[src.channels()*(src.cols*540 + 960) + 0];    
      int g = src.data[src.channels()*(src.cols*540 + 960) + 1];
      int r = src.data[src.channels()*(src.cols*540 + 960) + 2];
      circle(src, Point(960, 540), 1, Scalar(128, 121, 40));
      //cout << r << ' ' << g << ' ' << b << endl;
      
      imshow("result", src);
      imshow("threshold", redFeature);


      
      // Handle key event
      //key = cv::waitKey(10);
      //processKeyEvent(zed, key);
      cv::waitKey(5);
      }


   }
   return 0;
   
}




