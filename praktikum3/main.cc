#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // Baca gambar
    cv::Mat image = cv::imread("../../img/orange_flower.jpg", cv::IMREAD_GRAYSCALE);

    // Inisialisasi array untuk menyimpan histogram
    int histogram[256] = {0};
    int darked_histogram[256] = {0};
    int lighted_histogram[256] = {0};

    // Clone gambar asli untuk menghasilkan gambar yang diredupkan dan diterangi
    cv::Mat darked_grayscale = image.clone();
    cv::Mat lighted_grayscale = image.clone();

    // Jumlah yang akan digunakan untuk mengurangkan dan menambahkan intensitas piksel
    uchar num = 51;

    // Loop melalui setiap piksel dan hitung frekuensinya
    for (int i = 0; i < image.rows; ++i) {
    	for (int j = 0; j < image.cols; ++j) {
    		// Mengurangkan nilai intensitas piksel dari gambar yang diredupkan
    		if (darked_grayscale.at<uchar>(i, j) - num < 0)
    			darked_grayscale.at<uchar>(i, j) = 0;
    		else
    			darked_grayscale.at<uchar>(i, j) -= num;

    		// Menambahkan nilai intensitas piksel ke gambar yang diterangi
    		if (lighted_grayscale.at<uchar>(i, j) + num > 255)
    			lighted_grayscale.at<uchar>(i, j) = 255;
    		else
    			lighted_grayscale.at<uchar>(i, j) += num;
    	}
    }

    // Tampilkan gambar asli, diredupkan, dan diterangi
    cv::imshow("grayscale_image", image);
    cv::imshow("darked_grayscale", darked_grayscale);
    cv::imshow("lighted_grayscale", lighted_grayscale);

    int pixel_value;

    // Hitung histogram untuk gambar asli, diredupkan, dan diterangi
    for (int i = 0; i < image.rows; ++i) {
    	for (int j = 0; j < image.cols; ++j) {
    		pixel_value = static_cast<int>(image.at<uchar>(i, j));
    		histogram[pixel_value] += 1;

    		pixel_value = static_cast<int>(darked_grayscale.at<uchar>(i, j));
    		darked_histogram[pixel_value] += 1;

    		pixel_value = static_cast<int>(lighted_grayscale.at<uchar>(i, j));
    		lighted_histogram[pixel_value] += 1;
    	}
    }

    int image_size = image.rows * image.cols;

    // Hitung kumulatif histogram untuk gambar asli, diredupkan, dan diterangi
    int c[3][256];
    c[0][0] = histogram[0];
    c[1][0] = darked_histogram[0];
    c[2][0] = lighted_histogram[0];

    for (int i = 1; i < 256; ++i) {
    	c[0][i] = c[0][i-1] + histogram[i];
    	c[1][i] = c[1][i-1] + darked_histogram[i];
    	c[2][i] = c[2][i-1] + lighted_histogram[i];
    }

    // Terapkan histogram equalization ke gambar asli, diredupkan, dan diterangi
    for (int i = 0; i < image.rows; ++i) {
    	for (int j = 0; j < image.cols; ++j) {
    		pixel_value = static_cast<int>(image.at<uchar>(i, j));
    		image.at<uchar>(i, j) = static_cast<uchar>(255 * c[0][pixel_value] / image_size);

    		pixel_value = static_cast<int>(darked_grayscale.at<uchar>(i, j));
    		darked_grayscale.at<uchar>(i, j) = static_cast<uchar>(255 * c[1][pixel_value] / image_size);

    		pixel_value = static_cast<int>(lighted_grayscale.at<uchar>(i, j));
    		lighted_grayscale.at<uchar>(i, j) = static_cast<uchar>(255 * c[2][pixel_value] / image_size);
    	}
    }

    // Tampilkan hasil dari histogram equalization
    cv::imshow("result_grayscale", image);
    cv::imshow("result_darked", darked_grayscale);
    cv::imshow("result_lighted", lighted_grayscale);

		for (int i = 0; i < 256; ++i) {
			histogram[i] = 0;
			darked_histogram[i] = 0;
			lighted_histogram[i] = 0;
		}

    // Tunggu hingga tombol Esc (kode 27) ditekan
    while (cv::waitKey(10) != 27);

    return 0;
}
