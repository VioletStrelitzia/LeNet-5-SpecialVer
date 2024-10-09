//#include "TestDemo.h"
//
//namespace yuki {
//	void TestDemo::TestLayerConv() {
//		SizeType inChannel = 3, outChannel = 4;
//		yuki::atri::cnn::LayerConv2D conv(inChannel, outChannel, yuki::atri::cnn::ReLU, yuki::atri::cnn::InitNormalKaimingKernel);
//
//		vector<Image<double>> input(inChannel, { {2, -2, 5, 1},
//								 {0, 1, -7, 2},
//								 {-3, 5, 3, -1},
//								 {-1, 2, 2, 0} });
//
//		std::cout << Image<double>({ {2, -2, 5, 1},
//								 {0, 1, -7, 2},
//								 {-3, 5, 3, -1},
//								 {-1, 2, 2, 0} }) << "\n\n";
//		conv.forward(input);
//
//		std::cout << "\nTest: LayerConv\n";
//		for (int i = 0; i < inChannel; ++i) {
//			std::cout << input[i] << "\n\n";
//		}
//		Image<double> k = conv._kernel[0][0];
//		std::cout << "Kernel[0][0]: \n";
//		std::cout << k << std::endl;
//
//		std::cout << "Kernel[1][0]: \n";
//		k = conv._kernel[1][0];
//		std::cout << k << std::endl;
//
//		Image<double> output = conv._OutputData[0];
//		std::cout << "OutputDataSize: " << conv._OutputData.size() << std::endl;
//		std::cout << std::endl;
//
//		std::cout << "OutputData[0]: \n";
//		std::cout << output;
//		std::cout << std::endl;
//
//		output = conv._OutputData[1];
//		std::cout << "OutputData[1]: \n";
//		for (SizeType i = 0; i < output.rows(); ++i) {
//			for (SizeType j = 0; j < output.cols(); ++j) {
//				std::cout << output[i][j] << " ";
//			}
//			std::cout << std::endl;
//		}
//		std::cout << std::endl;
//	}
//
//	void TestDemo::TestLayerPool() {
//		SizeType inChannel = 3;
//		vector<Image<double>> input(inChannel, Image<double>({ {2, -2, 5, 1},
//															   {0, 1, -7, 2},
//															   {-3, 5, 3, -1},
//															   {-1, 2, 2, 0} }));
//		yuki::atri::cnn::LayerMaxPool2D MaxPool1(inChannel);
//
//		MaxPool1.forward(input);
//		std::cout << "\nTest: LayerPool\n";
//		auto o = MaxPool1._OutputData[0];
//		std::cout << input[0] << "\n";
//		std::cout << "OutputData[0]: \n";
//		for (SizeType i = 0; i < o.rows(); ++i) {
//			for (SizeType j = 0; j < o.cols(); ++j) {
//				std::cout << o[i][j] << " ";
//			}
//			std::cout << std::endl;
//		}
//		std::cout << std::endl;
//
//		auto l = MaxPool1._MaxLocation[0];
//		std::cout << "MaxLocation[0]: \n";
//		for (SizeType i = 0; i < l.rows(); ++i) {
//			for (SizeType j = 0; j < l.cols(); ++j) {
//				std::cout << "(" << l[i][j].row << "," << l[i][j].col << ") ";
//			}
//			std::cout << std::endl;
//		}
//
//		auto b = MaxPool1.backward();
//		o = b[1];
//		for (SizeType i = 0; i < o.rows(); ++i) {
//			for (SizeType j = 0; j < o.cols(); ++j) {
//				std::cout << o[i][j] << " ";
//			}
//			std::cout << std::endl;
//		}
//		std::cout << std::endl;
//
//		
//	}
//
//	void TestDemo::TestLayerFlatten() {
//		SizeType inChannel = 3;
//		vector<Image<double>> input(inChannel, Image<double>({ {2, -2, 5, 1},
//																			 {0, 1, -7, 2},
//																			 {-3, 5, 3, -1},
//																			 {-1, 2, 2, 0} }));
//
//		yuki::atri::cnn::LayerFlatten2D flatten(inChannel, inChannel * input[0].rows() * input[0].cols());
//
//		flatten.forward(input);
//		std::cout << "\nTest: LayerFlatten\n";
//		std::cout << "OutputData: \n";
//		for (int i = 0; i < flatten._OutputData.size(); ++i) {
//			std::cout << flatten._OutputData[i] << " ";
//		}
//		std::cout << std::endl;
//
//		auto b = flatten.backward();
//		auto o = b[1];
//		std::cout << "Backward_OutputData: \n";
//		for (SizeType i = 0; i < o.rows(); ++i) {
//			for (SizeType j = 0; j < o.cols(); ++j) {
//				std::cout << o[i][j] << " ";
//			}
//			std::cout << std::endl;
//		}
//	}
//
//	void TestDemo::TestResize_BILINEAR() {
//		Image<cv::PixelRGBA> im;
//		std::cout << "\nTest: Resize_BILINEAR\n";
//		yuki::cv::ImageRead("D://picture/Morpho menelaus.bmp", im);
//		yuki::cv::ImageWrite("D://picture/Morpho_menelaus_TestResize_BILINEAR_2SizeBigger.bmp", yuki::cv::TfmShapeResize(im, im.rows() * 2, im.cols() * 2));
//		yuki::cv::ImageWrite("D://picture/Morpho_menelaus_TestResize_BILINEAR_2SizeSmaller.bmp", yuki::cv::TfmShapeResize(im, im.rows() / 2, im.cols() / 2));
//	}
//
//	void TestDemo::TestFCForward() {
//		yuki::atri::cnn::LayerLinear fc(120, 84, yuki::atri::cnn::ReLU, yuki::atri::cnn::InitNormalXavier);
//
//	}
//
//	void TestDemo::TestLenet5Forward() {
//		std::cout << "\nTest: Lenet5Forward\n";
//		yuki::atri::cnn::Lenet5 net;
//		auto input = Image<double>(32, 32, 255);
//		auto output = net.forward(input);
//		for (int i = 0; i < output.size(); ++i) {
//			printf("%.6lf ", output[i]);
//		}
//		std::cout << std::endl;
//	}
//
//}