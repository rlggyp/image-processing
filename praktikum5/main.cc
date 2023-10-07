#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
  cv::Mat soccer_ball = cv::imread("../../img/soccer_ball_green_bg.jpg");

  cv::Mat soccer_ball_hsv = soccer_ball.clone();
  cv::Mat masking = cv::Mat::zeros(soccer_ball.rows, soccer_ball.cols, CV_8UC1);

  cv::cvtColor(soccer_ball_hsv, soccer_ball_hsv, cv::COLOR_BGR2HSV);

  // masking (isolate green color)
  for (int i = 0; i < soccer_ball_hsv.rows; ++i) {
    for (int j = 0; j < soccer_ball_hsv.cols; ++j) {
      if (soccer_ball_hsv.at<cv::Vec3b>(i, j)[0] >= 55 && soccer_ball_hsv.at<cv::Vec3b>(i, j)[0] <= 65) {
        masking.at<uchar>(i, j) = 0;
      } else {
        masking.at<uchar>(i, j) = 255;
      }
    }
  }

  cv::imshow("masking", masking);

  // create structuring element (kernel) for erosion and dilation
  cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));

  cv::Mat erosion_result;
  cv::erode(masking, erosion_result, kernel);

  cv::imshow("erosion", erosion_result);

  cv::Mat dilation_result;
  cv::dilate(masking, dilation_result, kernel);
  cv::imshow("dilation", dilation_result);

  cv::Mat erotioned_ball = soccer_ball.clone();
  cv::Mat dilationed_ball = soccer_ball.clone();

  for (int i = 0; i < soccer_ball.rows; ++i) {
    for (int j = 0; j < soccer_ball.cols; ++j) {
      // perform erosion
      if (erosion_result.at<uchar>(i, j) == 0) {
        erotioned_ball.at<cv::Vec3b>(i, j)[0] = 0;
        erotioned_ball.at<cv::Vec3b>(i, j)[1] = 0;
        erotioned_ball.at<cv::Vec3b>(i, j)[2] = 0;
      }

      // perform dilation
      if (dilation_result.at<uchar>(i, j) == 0) {
        dilationed_ball.at<cv::Vec3b>(i, j)[0] = 0;
        dilationed_ball.at<cv::Vec3b>(i, j)[1] = 0;
        dilationed_ball.at<cv::Vec3b>(i, j)[2] = 0;
      }
    }
  }
  
  cv::imshow("ball_erosion", erotioned_ball);
  cv::imshow("ball_dilation", dilationed_ball);

  cv::Mat dilationed_and_erotioned_ball = soccer_ball.clone();
  cv::Mat dilation_erotion_result;
  cv::erode(dilation_result, dilation_erotion_result, kernel);
  cv::imshow("dilation_erode", dilation_erotion_result);

  // dilation + erode
  for (int i = 0; i < soccer_ball.rows; ++i) {
    for (int j = 0; j < soccer_ball.cols; ++j) {
      // erosion
      if (dilation_erotion_result.at<uchar>(i, j) == 0) {
        dilationed_and_erotioned_ball.at<cv::Vec3b>(i, j)[0] = 0;
        dilationed_and_erotioned_ball.at<cv::Vec3b>(i, j)[1] = 0;
        dilationed_and_erotioned_ball.at<cv::Vec3b>(i, j)[2] = 0;
      }
    }
  }

  cv::imshow("dilationed_and_erotioned_ball", dilationed_and_erotioned_ball);

  cv::imwrite("masking.jpg", masking);
  cv::imwrite("erotion.jpg", erosion_result);
  cv::imwrite("dilation.jpg", dilation_result);
  cv::imwrite("dilation_erotion.jpg", dilation_erotion_result);
  cv::imwrite("erotioned_ball.jpg", erotioned_ball);
  cv::imwrite("dilationed_ball.jpg", dilationed_ball);
  cv::imwrite("dilationed_and_erotioned_ball.jpg", dilationed_and_erotioned_ball);

  while (cv::waitKey(0) != 27);

  return 0;
}