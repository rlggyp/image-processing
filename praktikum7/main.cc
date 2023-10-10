#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
  // Membaca citra input
  cv::Mat image = cv::imread("../../img/elka.jpg", cv::IMREAD_COLOR);

  // Memeriksa apakah citra berhasil dimuat
  if (image.empty()) {
    std::cerr << "Error loading input image." << std::endl;
    return 1;
  }

  // Membuat citra grayscale dengan inisialisasi nilai piksel ke 0
  cv::Mat grayscale_image(image.size(), CV_8UC1, cv::Scalar(0));

  // Variabel untuk nilai piksel grayscale
  unsigned char gray_value;

  // Mengonversi citra ke grayscale dengan rata-rata nilai piksel
  for (int i = 0; i < image.cols; ++i) {
    for (int j = 0; j < image.rows; ++j) {
      gray_value = ((short)(image.at<cv::Vec3b>(i, j)[0] + image.at<cv::Vec3b>(i, j)[1] + image.at<cv::Vec3b>(i, j)[2]) / 3);
      grayscale_image.at<unsigned char>(i, j) = gray_value;
    }
  }

  // Mendefinisikan kernel 3x3, 5x5, dan 7x7 untuk deteksi tepi (High-Pass Filter)
  // Kernel ini digunakan untuk operasi konvolusi untuk mendeteksi tepi dalam citra

  cv::Mat kernel3x3 = (cv::Mat_<float>(3, 3) << 
    -1.0, -1.0, -1.0,
    -1.0, 8.0, -1.0,
    -1.0, -1.0, -1.0);

  cv::Mat kernel5x5 = (cv::Mat_<float>(5, 5) << 
    -1.0, -1.0, -1.0, -1.0, -1.0,
    -1.0, -1.0, -1.0, -1.0, -1.0,
    -1.0, -1.0, 24.0,  -1.0, -1.0,
    -1.0, -1.0, -1.0, -1.0, -1.0,
    -1.0, -1.0, -1.0, -1.0, -1.0);

  cv::Mat kernel7x7 = (cv::Mat_<float>(7, 7) << 
    -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0,
    -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0,
    -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0,
    -1.0, -1.0, -1.0, 48.0, -1.0, -1.0, -1.0,
    -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0,
    -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0,
    -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0);

  // Menampilkan citra grayscale asli
  cv::imshow("Original Image", grayscale_image);

  // Mengaplikasikan filter High-Pass Filter (HPF) ke citra grayscale dengan kernel 3x3, 5x5, dan 7x7
  cv::Mat hpf_result;

  // Menggunakan kernel 3x3
  cv::filter2D(grayscale_image, hpf_result, -1, kernel3x3);
  cv::imshow("HPF Result 3x3", hpf_result);
  imwrite("hpf_result3x3.jpg", hpf_result);

  // Menggunakan kernel 5x5
  cv::filter2D(grayscale_image, hpf_result, -1, kernel5x5);
  cv::imshow("HPF Result 5x5", hpf_result);
  imwrite("hpf_result5x5.jpg", hpf_result);

  // Menggunakan kernel 7x7
  cv::filter2D(grayscale_image, hpf_result, -1, kernel7x7);
  cv::imshow("HPF Result 7x7", hpf_result);
  imwrite("hpf_result7x7.jpg", hpf_result);

  // Menunggu tombol keyboard 'ESC' (kode ASCII 27) untuk menutup jendela
  while (cv::waitKey(0) != 27);

  return 0;
}
