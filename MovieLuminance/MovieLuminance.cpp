// MovieLuminance.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <fstream>

int main()
{


   cv::VideoCapture video("D:\\CrowRabbit\\Videos\\0001-0135.avi");

   if(!video.isOpened())  // 成功したかどうかをチェック
       return -1;

   cv::Rect roi(0,0,500,500);//各引数に切り取りたい座標を入れよ。

   //JavaのArrayListみたいなもの。
   std::vector<double> Blue;
   std::vector<double> Green;
   std::vector<double> Red;

   //z=現在のフレーム目
   for(auto z = 0; z <= video.get(CV_CAP_PROP_FRAME_COUNT); ++z)
   {

      cv::Mat frame_raw;//生データ
      if (!video.grab())//次のフレームへ
         break;
      video.retrieve(frame_raw, z);//フレームを読み出す

      auto frame = frame_raw(roi);//ROIでリサイズ後

      auto blue_sum = 0.0;
      auto green_sum = 0.0;
      auto red_sum = 0.0; //各BGR画素数&初期化
      auto x = 0;
      auto y = 0;
      //各ドットの画素数をどんどん入れてく。
      for(y = 0; y < frame.cols; ++y)
      {

         for(x = 0; x < frame.rows; ++x)
         {
            blue_sum += frame.at<cv::Vec3b>(y,x)[0];

            green_sum += frame.at<cv::Vec3b>(y,x)[1];

            red_sum += frame.at<cv::Vec3b>(y,x)[2];


         }

      }


      //平均を出す。
      Blue.push_back( blue_sum / (x*y) );
      Green.push_back(  green_sum / (x*y) );
      Red.push_back(  red_sum / (x*y) );

   }

   //csvに出力する準備
   std::string filename="output.csv";//お好きな名前で
   std::ofstream writing_file;
   writing_file.open(filename, std::ios::out);


   //ここはオマケ
   std::cout << "Writing to "<< filename << std::endl;
   std::cout<< "please wait..." << std::endl;


   //ファイルに書き込む。

   for(auto i = 0; i < Blue.size(); ++i)
   {
      writing_file << Blue[i] << ","  << Green[i] << "," << Red[i] << std::endl;
   }


   return 0; //終わり

}
