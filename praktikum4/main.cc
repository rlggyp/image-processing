#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
  cv::Mat soccer_ball = cv::imread("../../img/soccer_ball_green_bg.jpg");
  cv::Mat stadium = cv::imread("../../img/soccer_ball_stadium.jpg");

  cv::imshow("soccer_ball", soccer_ball);
  cv::imshow("stadium", stadium);

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

  // AND operation
  cv::Mat result_and = soccer_ball.clone();

  for (int i = 0; i < soccer_ball.rows; ++i) {
    for (int j = 0; j < soccer_ball.cols; ++j) {
      result_and.at<cv::Vec3b>(i, j)[0] &= masking.at<uchar>(i, j);
      result_and.at<cv::Vec3b>(i, j)[1] &= masking.at<uchar>(i, j);
      result_and.at<cv::Vec3b>(i, j)[2] &= masking.at<uchar>(i, j);
    }
  }

  cv::imshow("and", result_and);

  // XOR operation
  cv::Mat result_xor = soccer_ball.clone();

  for (int i = 0; i < soccer_ball_hsv.rows; ++i) {
    for (int j = 0; j < soccer_ball_hsv.cols; ++j) {
      result_xor.at<cv::Vec3b>(i, j)[0] &= 255^masking.at<uchar>(i, j);
      result_xor.at<cv::Vec3b>(i, j)[1] &= 255^masking.at<uchar>(i, j);
      result_xor.at<cv::Vec3b>(i, j)[2] &= 255^masking.at<uchar>(i, j);
    }
  }

  cv::imshow("xor", result_xor);

  // NOT operation
  cv::Mat result_not = stadium.clone();

  for (int i = 0; i < soccer_ball_hsv.rows; ++i) {
    for (int j = 0; j < soccer_ball_hsv.cols; ++j) {
      if (masking.at<uchar>(i, j) != 0) {
        result_not.at<cv::Vec3b>(i, j)[0] = !(255&masking.at<uchar>(i, j));
        result_not.at<cv::Vec3b>(i, j)[1] = !(255&masking.at<uchar>(i, j));
        result_not.at<cv::Vec3b>(i, j)[2] = !(255&masking.at<uchar>(i, j));
      }
    }
  }

  cv::imshow("not", result_not);

  // OR operation
  cv::Mat result_or = result_not.clone();

  for (int i = 0; i < soccer_ball_hsv.rows; ++i) {
    for (int j = 0; j < soccer_ball_hsv.cols; ++j) {
      result_or.at<cv::Vec3b>(i, j)[0] |= result_and.at<cv::Vec3b>(i, j)[0];
      result_or.at<cv::Vec3b>(i, j)[1] |= result_and.at<cv::Vec3b>(i, j)[1];
      result_or.at<cv::Vec3b>(i, j)[2] |= result_and.at<cv::Vec3b>(i, j)[2];
    }
  }

  cv::imshow("or", result_or);

  while (cv::waitKey(0) != 27);

  return 0;
}