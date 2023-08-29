#include <opencv2/opencv.hpp>
#include <cmath>

float DegreeToRadian(float &angle) {
  return (M_PI / 180.0 * angle);
}

bool GetRotation2D(cv::Point &point, int &row, int &col, short &center_x, short &center_y, float degree) {
  float angle = DegreeToRadian(degree);

  point.x = round((row - center_x) * std::cos(angle) - (col - center_y) * std::sin(angle) + center_x);
  point.y = round((row - center_x) * std::sin(angle) + (col - center_y) * std::cos(angle) + center_y);

  return !(point.x < 0 || point.x > center_x * 2 - 1 || point.y < 0 || point.y > center_y * 2 - 1);
}

int main() {
    // Load an image
    cv::Mat image = cv::imread("../../img/elka.jpg");

    if (image.empty()) {
        std::cout << "Image not found!" << std::endl;
        return -1;
    }

    cv::imshow("original_image", image);

    cv::Mat blue_image(image.size(), CV_8UC3, cv::Scalar(0, 0, 0));
    cv::Mat green_image(image.size(), CV_8UC3, cv::Scalar(0, 0, 0));
    cv::Mat red_image(image.size(), CV_8UC3, cv::Scalar(0, 0, 0));

    for (int i = 0; i < image.cols; ++i) {
      for (int j = 0; j < image.rows; ++j) {
        blue_image.at<cv::Vec3b>(i, j)[0] = image.at<cv::Vec3b>(i, j)[0];
        green_image.at<cv::Vec3b>(i, j)[1] = image.at<cv::Vec3b>(i, j)[1];
        red_image.at<cv::Vec3b>(i, j)[2] = image.at<cv::Vec3b>(i, j)[2];
      }
    }

    cv::imshow("blue_image", blue_image);
    cv::imshow("green_image", green_image);
    cv::imshow("red_image", red_image);

    cv::Mat flip_image(image.size(), CV_8UC3, cv::Scalar(0, 0, 0));
    cv::Mat grayscale_image(image.size(), CV_8UC1, cv::Scalar(0));

    unsigned char gray_value;

    for (int i = 0; i < image.cols; ++i) {
      for (int j = 0; j < image.rows; ++j) {
        flip_image.at<cv::Vec3b>(image.cols-1-i, j)[0] = image.at<cv::Vec3b>(i, j)[0];
        flip_image.at<cv::Vec3b>(image.cols-1-i, j)[1] = image.at<cv::Vec3b>(i, j)[1];
        flip_image.at<cv::Vec3b>(image.cols-1-i, j)[2] = image.at<cv::Vec3b>(i, j)[2];

        gray_value = ((short)(image.at<cv::Vec3b>(i, j)[0] + image.at<cv::Vec3b>(i, j)[1] + image.at<cv::Vec3b>(i, j)[2]) / 3);
        grayscale_image.at<unsigned char>(i, j) = gray_value;
      }
    }

    cv::imshow("flip_image", flip_image);
    cv::imshow("grayscale_image", grayscale_image);

    cv::Mat rotated_image(image.size(), CV_8UC3, cv::Scalar(0, 0, 0));

    short center_x = rotated_image.cols / 2; // center x
    short center_y = rotated_image.rows / 2; // center y

    cv::Point point;

    for (int i = 0; i < image.cols; ++i) {
      for (int j = 0; j < image.rows; ++j) {
        if (GetRotation2D(point, i, j, center_x, center_y, 20)) { // rotated 20 degree
          rotated_image.at<cv::Vec3b>(i, j)[0] = image.at<cv::Vec3b>(point.x, point.y)[0];
          rotated_image.at<cv::Vec3b>(i, j)[1] = image.at<cv::Vec3b>(point.x, point.y)[1];
          rotated_image.at<cv::Vec3b>(i, j)[2] = image.at<cv::Vec3b>(point.x, point.y)[2];
        }
      }
    }

    cv::imshow("rotated_image1", rotated_image);

    rotated_image = cv::Mat(image.size(), CV_8UC3, cv::Scalar(0, 0, 0)); // assign black color

    for (int i = 0; i < image.cols; ++i) {
      for (int j = 0; j < image.rows; ++j) {
        if (GetRotation2D(point, i, j, center_x, center_y, -135)) { // rotated -135 degree
          rotated_image.at<cv::Vec3b>(i, j)[0] = image.at<cv::Vec3b>(point.x, point.y)[0];
          rotated_image.at<cv::Vec3b>(i, j)[1] = image.at<cv::Vec3b>(point.x, point.y)[1];
          rotated_image.at<cv::Vec3b>(i, j)[2] = image.at<cv::Vec3b>(point.x, point.y)[2];
        }
      }
    }

    cv::imshow("rotated_image2", rotated_image);

    while (cv::waitKey(1) != 27);

    return 0;
}
