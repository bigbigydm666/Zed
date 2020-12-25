/*
 *                        .::::.
 *                      .::::::::.
 *                     :::::::::::
 *                  ..:::::::::::'
 *               '::::::::::::'
 *                 .::::::::::
 *            '::::::::::::::..
 *                 ..::::::::::::.
 *               ``::::::::::::::::
 *                ::::``:::::::::'        .:::.
 *               ::::'   ':::::'       .::::::::.
 *             .::::'      ::::     .:::::::'::::.
 *            .:::'       :::::  .:::::::::' ':::::.
 *           .::'        :::::.:::::::::'      ':::::.
 *          .::'         ::::::::::::::'         ``::::.
 *      ...:::           ::::::::::::'              ``::.
 *     ````':.          ':::::::::'                  ::::..
 *                        '.:::::'                    ':'````..
 */

/*
 * @Author: your name
 * @Date: 2020-12-24 09:53:07
 * @LastEditTime: 2020-12-25 09:42:38
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /ZedDriver/test.cpp
 */
/*
 * 
 * 　　┏┓　　　┏┓+ +
 * 　┏┛┻━━━┛┻┓ + +
 * 　┃　　　　　　　┃ 　
 * 　┃　　　━　　　┃ ++ + + +
 *  ████━████ ┃+
 * 　┃　　　　　　　┃ +
 * 　┃　　　┻　　　┃
 * 　┃　　　　　　　┃ + +
 * 　┗━┓　　　┏━┛
 * 　　　┃　　　┃　　　　　　　　　　　
 * 　　　┃　　　┃ + + + +
 * 　　　┃　　　┃
 * 　　　┃　　　┃ +  神兽保佑
 * 　　　┃　　　┃    代码无bug　　
 * 　　　┃　　　┃　　+　　　　　　　　　
 * 　　　┃　 　　┗━━━┓ + +
 * 　　　┃ 　　　　　　　┣┓
 * 　　　┃ 　　　　　　　┏┛
 * 　　　┗┓┓┏━┳┓┏┛ + + + +
 * 　　　　┃┫┫　┃┫┫
 * 　　　　┗┻┛　┗┻┛+ + + +
 * 
 */


/*
 * @Author: your name
 * @Date: 2020-12-24 09:53:07
 * @LastEditTime: 2020-12-24 09:53:08
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /ZedDriver/test.cpp
 */


#define MODE BLUE


#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/cvconfig.h>
#include <sl/Camera.hpp>
#include "ZED.hpp"

using namespace std;
using namespace cv;

int main()
{
   ZED camera;
   camera.init();
   camera.setCamera(MODE);
   vector<Mat> img;
   float distance;
   //设置识别参数

   int hMax = 255, hMin = 136, sMax = 255, sMin = 0, vMax = 255, vMin = 0;

   int dist1 = 5, range1 = 1;
   int dist2 = 0, range2 = 0;
      switch (MODE)
   {
   case 1:
      
      hMax = 255, hMin = 136;

      break;
   case 2:
      
      hMax = 187, hMin = 60;
      sMax = 255, sMin = 50;
   default:
      break;
   }
   namedWindow("control");
   cv::createTrackbar("hMax", "control", &hMax, 255);
   cv::createTrackbar("hMin", "control", &hMin, 255);
   cv::createTrackbar("sMax", "control", &sMax, 255);
   cv::createTrackbar("sMin", "control", &sMin, 255);
   cv::createTrackbar("vMax", "control", &vMax, 255);
   cv::createTrackbar("vMin", "control", &vMin, 255);
   cv::createTrackbar("dist1", "control", &dist1, 12);
   cv::createTrackbar("dist2", "control", &dist2, 10);
   cv::createTrackbar("range1", "control", &range1, 2);
   cv::createTrackbar("range2", "control", &range2, 10);

   //加载模板图像并得到轮廓
   Mat temp = imread("1.png", IMREAD_GRAYSCALE);
   vector<Mat> temp_contours;
   temp_contours.push_back(temp);
   Rect ROIRECT = Rect(camera.getWidth()/2 - 150, camera.getHeight()/2 - 150, 300, 300);

   while(1)
   {
      float dist = dist1 + 0.1 * dist2;
      float range = range1 + 0.1 * range2;
      //读取图像
      img = camera.getImg();
      imshow("DEPTH", img[1]);

      //预处理图像
      Mat src = img[0].clone();
      medianBlur(src, src, 3);
      GaussianBlur(src, src, Size(3, 3), 0);
      rectangle(src, ROIRECT, Scalar(255, 255, 255));
      Mat kernel = getStructuringElement(MORPH_RECT, Size(9, 9));
      Mat roihsv;
      Mat roisrc = src(ROIRECT);

      
      
      cvtColor(roisrc, roihsv, COLOR_BGR2HSV);
      Mat roisrc2 = roisrc.clone();
      cvtColor(roisrc2, roisrc2, COLOR_BGR2GRAY);
      Mat temp1;
      inRange(roihsv, Scalar(hMin, sMin, vMin), Scalar(hMax, sMax, vMax), temp1);

      Mat redFeature = temp1;
      morphologyEx(redFeature, redFeature, MORPH_CLOSE, kernel);
      Mat depthMask = camera.depthMask(dist, range, roisrc);
      Mat threshold_mask;
      threshold(depthMask, threshold_mask, 0, 255, THRESH_BINARY);
      imshow("666", threshold_mask);
      multiply(redFeature, depthMask, redFeature);
      multiply(roisrc2, depthMask, roisrc2);

      imshow("masked", roisrc2);

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
         //float distance = camera.calcDistance(Point(minRec.x + 0.5*minRec.width, minRec.y + 0.5*minRec.height));
         rectangle(roisrc, minRec, Scalar(0, 255, 0), 2);
         float distance = camera.calcDistance(Point(camera.getWidth()/2 - 150 + minRec.x + 0.5*minRec.width, camera.getHeight()/2 - 150 + minRec.y + 0.5*minRec.height));
			string text = "distance: " + std::to_string(distance) + " m";
         putText(src, text, Point(50,50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 0), 4, 8);
      }
      
      
      
      
      
      
      
      
      //int b = src.data[src.channels()*(src.cols*camera.height*0.5 + camera.width) + 0];    
      //int g = src.data[src.channels()*(src.cols*camera.height*0.5 + camera.width) + 1];
      //int r = src.data[src.channels()*(src.cols*camera.height*0.5 + camera.width) + 2];
      //circle(src, Point(960, 540), 1, Scalar(128, 121, 40));
      //cout << r << ' ' << g << ' ' << b << endl;
      
      imshow("result", src);
      imshow("threshold", redFeature);

      waitKey(1);
   }

   return 0;


}