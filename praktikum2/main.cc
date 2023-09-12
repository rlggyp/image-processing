#include <opencv2/opencv.hpp>

int main() {
	cv::Mat image = cv::imread("../../img/black_flower.jpg");

	if (image.empty()) {
		std::cout << "Image not found!" << std::endl;
		return -1;
	}

	cv::imshow("default", image);

	int brightness(1), contrast(1);

  cv::namedWindow("brightness");
  cv::namedWindow("contrast");

  cv::createTrackbar("Brightness", "brightness", &brightness, 255);
  cv::createTrackbar("Contrast", "contrast", &contrast, 255);

  cv::Mat grayscale_image(image.size(), CV_8UC1, cv::Scalar(0, 0, 0));

	short gray_value;
	for (int i = 0; i < image.rows; ++i) {
		for (int j = 0; j < image.cols; ++j) {
      gray_value = ((short)(image.at<cv::Vec3b>(i, j)[0] + image.at<cv::Vec3b>(i, j)[1] + image.at<cv::Vec3b>(i, j)[2]) / 3);

      grayscale_image.at<unsigned char>(i, j) = gray_value;
		}
	}

  cv::Mat brightened_image(image.size(), CV_8UC1, cv::Scalar(0, 0, 0));
  cv::Mat contrasted_image(image.size(), CV_8UC1, cv::Scalar(0, 0, 0));
  cv::Mat auto_leveled_image(image.size(), CV_8UC1, cv::Scalar(0, 0, 0));

	// Calculate minimum and maximum pixel values manually
	unsigned char pixel_value;
  pixel_value = grayscale_image.at<uchar>(0, 0);
  unsigned char min_pixel_value = pixel_value;
  unsigned char max_pixel_value = pixel_value;

  for (int y = 0; y < grayscale_image.rows; ++y) {
  	for (int x = 0; x < grayscale_image.cols; ++x) {
  		pixel_value = grayscale_image.at<uchar>(y, x);

  	 	if (pixel_value < min_pixel_value) {
  	 		min_pixel_value = pixel_value;
  	 	}
  	 	if (pixel_value > max_pixel_value) {
  	 		max_pixel_value = pixel_value;
  	 	}
  	}
  }
	
	float new_value;

	while (cv::waitKey(10) != 27) {
		for (int y = 0; y < grayscale_image.rows; ++y) {
			for (int x = 0; x < grayscale_image.cols; ++x) {
				// brightened_image
				if (grayscale_image.at<uchar>(y, x) + brightness > 255) {
					brightened_image.at<uchar>(y, x) = 255;
				} else {
					brightened_image.at<uchar>(y, x) = grayscale_image.at<uchar>(y, x) + brightness;
				}
				
				//contrasted_image
				new_value = grayscale_image.at<uchar>(y, x) * contrast;
				if (new_value > 255) {
					contrasted_image.at<uchar>(y, x) = 255;
				} else {
					contrasted_image.at<uchar>(y, x) = static_cast<uchar>(new_value);
				}

				//auto_leveled_image
				pixel_value = grayscale_image.at<uchar>(y, x);
        new_value = static_cast<int>((pixel_value - min_pixel_value) * 255.0 / (max_pixel_value - min_pixel_value));
        auto_leveled_image.at<uchar>(y, x) = static_cast<uchar>(new_value);
			}
		}

		cv::imshow("brightness", brightened_image);
		cv::imshow("contrast", contrasted_image);
		cv::imshow("auto-level", auto_leveled_image);
	}

	return 0;
}
