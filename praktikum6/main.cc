#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
  cv::Mat image = cv::imread("../../img/soccer_ball_stadium.jpg", cv::IMREAD_COLOR);

  if (image.empty()) {
      std::cerr << "Error loading input image." << std::endl;
      return 1;
  }

  // Define a 3x3 LPF kernel (averaging filter)
  cv::Mat kernel = (cv::Mat_<float>(3, 3) << 
    1.0/9, 1.0/9, 1.0/9,
    1.0/9, 1.0/9, 1.0/9,
    1.0/9, 1.0/9, 1.0/9);

  // Apply the LPF filter to the image
  cv::Mat lpf_result;

  cv::filter2D(image, lpf_result, -1, kernel);

  // Display the original image and LPF result
  cv::imshow("Original Image", image);
  cv::imshow("LPF Result", lpf_result);

  imwrite("lpf_result.jpg", lpf_result);

  while (cv::waitKey(0) != 27);

  return 0;
}