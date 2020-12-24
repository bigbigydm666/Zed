/*
 * @Author: your name
 * @Date: 2020-12-24 09:53:07
 * @LastEditTime: 2020-12-24 17:15:11
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
   while(1)
   {

      img = camera.getImg();

      imshow("111", img[0]);
      imshow("222", img[1]);
      waitKey(1);
   }

   return 0;


}