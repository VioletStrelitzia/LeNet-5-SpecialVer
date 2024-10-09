#include <iostream>
#include "TestDemo.h"
#include "YukiTensor.h"
#include "YukiAtri.h"
#include <functional>
#include <fstream>

using std::cout;
using namespace yuki;
using namespace yuki::cv;
using namespace yuki::atri;
using namespace yuki::atri::cnn;

void TestLayerPool() {
	int inChannel = 3;
	Matrix<Mat> input(inChannel, 1, Mat({ {2, -2, 5, 1},
										  {0, 1, -7, 2},
										  {-3, 5, 3, -1},
										  {-1, 2, 2, 0} }));
	yuki::atri::LayerMaxPool2D MaxPool1(inChannel, 4, 4);

	MaxPool1.forward(input);
	std::cout << "\nTest: LayerPool\n";
	auto o = MaxPool1.output[2][0];
	std::cout << input[2][0] << "\n";
	std::cout << "OutputData[0]: \n";
	for (int i = 0; i < o.rows(); ++i) {
		for (int j = 0; j < o.cols(); ++j) {
			std::cout << o[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	auto l = MaxPool1.output;
	std::cout << "MaxLocation[0]: \n";
	for (SizeType i = 0; i < l.rows(); ++i) {
		for (SizeType j = 0; j < l.cols(); ++j) {
			std::cout << "(" << l[i][j].rows() << "," << l[i][j].cols() << ") ";
		}
		std::cout << std::endl;
	}
	MaxPool1.backward(input, input);
	auto b = MaxPool1.delta;
	auto x = b.at(1);
	for (SizeType i = 0; i < x.rows(); ++i) {
		for (SizeType j = 0; j < x.cols(); ++j) {
			std::cout << x[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

}

void TestLayerFlatten() {
	SizeType inChannel = 3;
	Matrix<Mat> input(inChannel, 1, { {2, -2, 5, 1},
									{0, 1, -7, 2},
									{-3, 5, 3, -1},
									{-1, 2, 2, 0} });

	yuki::atri::LayerFlatten2D flatten(inChannel, input.at(0).rows(), input.at(0).cols());

	flatten.forward(input);
	std::cout << "\nTest: LayerFlatten\n";
	std::cout << "OutputData: \n";
	for (int i = 0; i < flatten.output.rows(); ++i) {
		std::cout << flatten.output[i][0] << " ";
	}
	std::cout << std::endl;
	flatten.backward(input, input);
	auto b = input;
	auto o = b.at(1);
	std::cout << "Backward_OutputData: \n";
	for (SizeType i = 0; i < o.rows(); ++i) {
		for (SizeType j = 0; j < o.cols(); ++j) {
			std::cout << o[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void be32toh(uint32_t& be) {
	be = ((be & 0x000000ff) << 24) |
		((be & 0x0000ff00) << 8) |
		((be & 0x00ff0000) >> 8) |
		((be & 0xff000000) >> 24);
}

void TestLenet5() {
	Lenet5 l5(true);
	cout << l5.conv1.weight.at(0, 0);
	////l5.load("Lenet-5_test.atri");

	//for (int t = 0; t < 30; ++t) {
	//	for (int i = 0; i < 64; ++i) {
	//		l5.forward(input);
	//		l5.backward(input, Mat{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
	//	}
	//	cout << l5.forward(input) << '\n';
	//	l5.update(0.01 / (t + 10));

	//	cout << "time " << t << " finished\n";
	//	cout << l5.forward(input) << '\n';
	//	
	//}
	//
	//cout << l5.forward(input);
	//
	//l5.save("Lenet-5_test.atri");

	string const trainImagesFilename = "train-images.idx3-ubyte";
	string const trainLabelsFilename = "train-labels.idx1-ubyte";

	ifstream infile(trainImagesFilename, std::ios::in | std::ios::binary);
	ifstream inlabel(trainLabelsFilename, std::ios::in | std::ios::binary);
	if (!infile.is_open()) {
		// 错误处理：文件无法打开  
		return;
	}

	// 读取文件头信息  
	uint32_t magic_number;
	infile.read(reinterpret_cast<char*>(&magic_number), 4);
	be32toh(magic_number);
	cout << '\n' << magic_number << '\n';
	
	//if (magic_number != 0x00000803) {
	//	// 错误处理：不正确的魔数  
	//	infile.close();
	//	return 1;
	//}

	uint32_t num_images, rows, cols;
	infile.read(reinterpret_cast<char*>(&num_images), 4);
	infile.read(reinterpret_cast<char*>(&rows), 4);
	infile.read(reinterpret_cast<char*>(&cols), 4);

	be32toh(num_images);
	be32toh(rows);
	be32toh(cols);

	cout << '\n' <<num_images << '\n' << rows << "\n" << cols << '\n';

	cout << num_images << std::endl;
	uint32_t temp;
	inlabel.read(reinterpret_cast<char*>(&temp), 4);
	inlabel.read(reinterpret_cast<char*>(&temp), 4);
	cout << num_images << ' ' << num_images << '\n';

	be32toh(num_images);
	int batch_counter = 0;

	for (int t = 0; t < num_images / 4; ++t) {
		unsigned char image_data[28 * 28];
		infile.read(reinterpret_cast<char*>(image_data), sizeof image_data);
		
		Image<PixelRGB> image(28, 28, { 0, 0, 0 });
		Mat input(28, 28);
		for (int r = 27, i = 0; r > -1; --r) {
			for (int c = 0; c < 28; ++c, ++i) {
				unsigned char pixel = 0xff ^ image_data[i];
				if (pixel != 0) {
					image.at(r, c) = { pixel, pixel, pixel };
				}
				input.at(r, c) = pixel;
			}
		}

		char label;
		inlabel.read(&label, sizeof label);
		//cout << t + 1 << ' ' << (int)(label) << '\n';
		Mat Label(10, 1, 0);
		for (int r = 1; r <= 10; ++r) {
			if (r == (int)label) {
				Label.at(r - 1) = 1.;
				break;
			}
		}
		cout << "label:" << (int)(label) << '\n' << l5.forward(input) << '\n';
		l5.backward(input, Label);
		if (batch_counter >= 100) {
			batch_counter = 0;
			l5.update(0.001);
			cout << t << '\n';
		} else {
			++batch_counter;
		}
		
	}
	
	l5.save("test111.mod");
	inlabel.close();
	infile.close();
}


//function<Mat(int const& inChannels_, int const& outChannels_, int const& kernelSize_)> _LayerConv2D::WeightInit = InitNormalKaimingKernel;
int main() {
	try {
		//TestDemo td;
		//td.TestLayerConv();
		//td.TestLayerFlatten();
		//td.TestLayerPool();
		//td.TestLenet5Forward();
		//td.TestResize_BILINEAR();
		TestLenet5();

	} catch (yuki::DefaultBase const& e) {
		cout << e.DefaultInfo();
	} catch (char const* str) {
		cout << str;
	}
	return 0;
}