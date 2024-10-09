#include "YukiAtri.h"

namespace yuki {
	namespace atri {
		
		//namespace cnn {

		//	/**************************************************************************************
		//	* LayerConv2D
		//	**************************************************************************************/
		//	LayerConv2D::LayerConv2D(SizeType const& inChannel, SizeType const& outChannel, double (*ActivationFunction) (double const&), Mat(*Init) (SizeType const&, SizeType const&, SizeType const&), SizeType const& kernelSize, SizeType const& padding, SizeType const& stride) :
		//		_inChannels(inChannel),
		//		_outChannels(outChannel),
		//		_ActivationFunction(ActivationFunction),
		//		_kernelSize(kernelSize),
		//		_stride(stride),
		//		_padding(padding),
		//		_bias(outChannel, 0),
		//		_kernel(inChannel) {
		//		
		//		for (SizeType o = 0; o < this->_outChannels; ++o) {
		//			for (SizeType i = 0; i < this->_inChannels; ++i) {
		//				this->_kernel[i].push_back(Init(inChannel, outChannel, kernelSize));
		//			}
		//		}
		//	}

		//	vector<Mat> LayerConv2D::forward(vector<Mat> const& InputData) {
		//		if (InputData.size() != this->_inChannels) {
		//			throw "ERROR: inChannel | in void LayerConv2D::forward(const vector<Mat>& InputData)\n";
		//		}
		//		this->_OutputData.clear();
		//		
		//		for (SizeType o = 0; o < this->_outChannels; ++o) {
		//			Mat tmp((InputData[0].rows() + (this->_padding - this->_kernel[0][0].rows() / 2) * 2) / this->_stride, (InputData[0].cols() + (this->_padding - this->_kernel[0][0].cols() / 2) * 2) / this->_stride, 0);
		//			for (SizeType i = 0; i < this->_inChannels; ++i) {
		//				tmp += yuki::cv::convolute(InputData[i], this->_kernel[i][o], this->_stride, this->_padding);
		//			}
		//			this->_OutputData.push_back(tmp);
		//			for (SizeType r = 0; r < this->_OutputData[o].rows(); ++r) {
		//				for (SizeType c = 0; c < this->_OutputData[o].cols(); ++c) {
		//					this->_OutputData[o][r][c] = this->_ActivationFunction(this->_OutputData[o][r][c] + this->_bias[o]);
		//				}
		//			}
		//		}

		//		return this->_OutputData;
		//	}

		//	/**************************************************************************************
		//	* LayerMaxPool2D
		//	**************************************************************************************/
		//	LayerMaxPool2D::LayerMaxPool2D(SizeType const& inChannel, SizeType const& kernelSize) :
		//		_inChannels(inChannel),
		//		_kernelSize(kernelSize) {}

		//	vector<Mat> LayerMaxPool2D::forward(const vector<Mat>& InputData) {
		//		if (InputData.size() != this->_inChannels) {
		//			throw "ERROR: inChannel | in void LayerMaxPool2D::forward(const vector<Mat>& InputData)\n";
		//		}
		//		this->_OutputData.clear();
		//		this->_MaxLocation.clear();

		//		for (SizeType o = 0; o < this->_inChannels; ++o) {
		//			Mat TmpMax(InputData[0].rows() / this->_kernelSize, InputData[0].cols() / this->_kernelSize);
		//			Image<cv::point> TmpLoc(InputData[0].rows() / this->_kernelSize, InputData[0].cols() / this->_kernelSize);
		//			
		//			/* r, c是在输入图的行、列，R, C是在输出图的行、列 */
		//			for (SizeType r = 0, R = 0; R < TmpMax.rows(); r += this->_kernelSize, ++R) {
		//				for (SizeType c = 0, C = 0; C < TmpMax.cols(); c += this->_kernelSize, ++C) {
		//					double max = InputData[o][r][c];
		//					cv::point loc(r, c);
		//					
		//					for (SizeType i = r; i < r + this->_kernelSize; ++i) {
		//						for (SizeType j = c; j < c + this->_kernelSize; ++j) {
		//							if (InputData[o][i][j] > max) {
		//								max = InputData[o][i][j];
		//								loc = cv::point(i, j);
		//							}
		//						}
		//					}

		//					TmpMax[R][C] = max;
		//					TmpLoc[R][C] = loc;
		//				}
		//			}

		//			this->_OutputData.push_back(TmpMax);
		//			this->_MaxLocation.push_back(TmpLoc);

		//		}

		//		return this->_OutputData;
		//	}

		//	vector<Mat> LayerMaxPool2D::backward() {
		//		vector<Mat> OutputData(this->_OutputData.size(), Mat(this->_OutputData[0].rows() * this->_kernelSize, this->_OutputData[0].cols() * this->_kernelSize, 0));

		//		for (SizeType o = 0; o < this->_MaxLocation.size(); ++o) {
		//			for (SizeType r = 0; r < this->_MaxLocation[o].rows(); ++r) {
		//				for (SizeType c = 0; c < this->_MaxLocation[o].cols(); ++c) {
		//					OutputData[o][this->_MaxLocation[o][r][c].row][this->_MaxLocation[o][r][c].col] = this->_OutputData[o][r][c];
		//				}
		//			}
		//		}
		//		
		//		return OutputData;
		//	}

		//	vector<Mat> LayerMaxPool2D::backward(const vector<Mat> InputData) {
		//		vector<Mat> OutputData(this->_inChannels, Mat(InputData[0].rows() * this->_kernelSize, InputData[0].cols() * this->_kernelSize, 0));

		//		for (SizeType o = 0; o < this->_MaxLocation.size(); ++o) {
		//			for (SizeType r = 0; r < this->_MaxLocation[o].rows(); ++r) {
		//				for (SizeType c = 0; c < this->_MaxLocation[o].cols(); ++c) {
		//					OutputData[o][this->_MaxLocation[o][r][c].row][this->_MaxLocation[o][r][c].col] = InputData[o][r][c];
		//				}
		//			}
		//		}

		//		return OutputData;
		//	}

		//	/**************************************************************************************
		//	* LayerFlatten2D
		//	**************************************************************************************/
		//	LayerFlatten2D::LayerFlatten2D(SizeType const& inChannel, SizeType const& outChannel) :
		//		_inChannels(inChannel),
		//		_outChannels(outChannel) {}

		//	vector<double> LayerFlatten2D::forward(const vector<Mat>& InputData) {
		//		if (InputData.size() != this->_inChannels) {
		//			throw "ERROR: inChannel | in void LayerFlatten::forward(const vector<Mat>& InputData)\n";
		//		}
		//		if (InputData.size() * InputData[0].rows() * InputData[0].cols() != this->_outChannels) {
		//			throw "ERROR: outChannel | in void LayerFlatten::forward(const vector<Mat>& InputData)\n";
		//		}

		//		this->_InputDataRow = InputData[0].rows();
		//		this->_InputDataCol = InputData[0].cols();

		//		this->_OutputData.clear();

		//		for (SizeType i = 0; i < this->_inChannels; ++i) {
		//			for (SizeType r = 0; r < InputData[i].rows(); ++r) {
		//				for (SizeType c = 0; c < InputData[i].cols(); ++c) {
		//					this->_OutputData.push_back(InputData[i][r][c]);
		//				}
		//			}
		//		}


		//		return this->_OutputData;
		//	}

		//	vector<Mat> LayerFlatten2D::backward() {
		//		vector<Mat> OutputData(this->_inChannels, Mat(this->_InputDataRow, this->_InputDataCol));

		//		for (SizeType i = 0, j = 0; i < this->_inChannels; ++i) {
		//			for (SizeType r = 0; r < this->_InputDataRow; ++r) {
		//				for (SizeType c = 0; c < this->_InputDataCol; ++c) {
		//					OutputData[i][r][c] = this->_OutputData[j++];
		//				}
		//			}
		//		}
		//		
		//		return OutputData;
		//	}

		//	/**************************************************************************************
		//	* LayerLinear
		//	**************************************************************************************/
		//	LayerLinear::LayerLinear(SizeType const& inChannel, SizeType const& outChannel, double (*ActivationFunction) (double const&), double (*Init) (SizeType const&, SizeType const&)) :
		//		_inChannels(inChannel),
		//		_outChannels(outChannel),
		//		_weight(inChannel, vector<double>(outChannel)),
		//		_bias(outChannel, 0),
		//		_ActivationFunction(ActivationFunction) {
		//	
		//		for (SizeType o = 0; o < this->_outChannels; ++o) {
		//			for (SizeType i = 0; i < this->_inChannels; ++i) {
		//				this->_weight[i][o] = Init(inChannel, outChannel);
		//			}
		//		}
		//	}

		//	vector<double> LayerLinear::forward(const vector<double>& InputData) {
		//		if (InputData.size() != this->_inChannels) {
		//			throw "ERROR: inChannel | in void LayerLinear::forward(const vector<double>& InputData)\n";
		//		}
		//		this->_OutputData.clear();

		//		double tmp;
		//		for (SizeType o = 0; o < this->_outChannels; ++o) {
		//			tmp = 0;
		//			for (SizeType i = 0; i < this->_inChannels; ++i) {
		//				tmp += InputData[i] * this->_weight[i][o];
		//			}
		//			/* + 偏置 激活函数 */
		//			this->_OutputData.push_back(this->_ActivationFunction(tmp + this->_bias[o]));
		//		}

		//		return this->_OutputData;
		//	}

		//	Lenet5::Lenet5() :
		//		conv1(1, 6, ReLU, InitNormalKaimingKernel, 5, 0, 1),
		//		pool2(6, 2),
		//		conv3(6, 16, ReLU, InitNormalKaimingKernel, 5, 0, 1),
		//		pool4(16, 2),
		//		conv5(16, 120, ReLU, InitNormalKaimingKernel, 5, 0, 1),
		//		flatten6(120, 120),
		//		FullConnect7(120, 84, ReLU, InitNormalKaiming),
		//		OutputLayer8(84, 10, ReLU, InitNormalKaiming) {}

		//	vector<double> Lenet5::forward(const Mat InputImage) {
		//		vector<Mat> x1;
		//		x1.push_back(InputImage);
		//		x1 = this->conv1.forward(x1);
		//		x1 = this->pool2.forward(x1);
		//		x1 = this->conv3.forward(x1);
		//		x1 = this->pool4.forward(x1);
		//		x1 = this->conv5.forward(x1);
		//		vector<double> x2;
		//		x2 = this->flatten6.forward(x1);
		//		x2 = this->FullConnect7.forward(x2);
		//		x2 = this->OutputLayer8.forward(x2);
		//		return x2;
		//	}

		//	void Lenet5::bacward(const vector<double> loss) {

		//	}

		//	void Lenet5::step() {

		//	}

		//}
		
	}
}
