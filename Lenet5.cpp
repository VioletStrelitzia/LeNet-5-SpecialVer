#include "Lenet5.h"
namespace yuki {
namespace atri {

Lenet5::Lenet5(bool const& isInit_) :
	//LossFunc(LossCrossEntropy),
	// 28 * 28
	conv1(1, 6, 28, 28, 5, true, sigmoid, "conv1", isInit_, true, initNormalKaimingKernel, initZero, sigmoidDeriv),
	// 28 * 28
	pool2(6, 28, 28, 2, "pool2", true),
	// 14 * 14
	conv3(6, 16, 14, 14, 5, false, sigmoid, "conv3", isInit_, true, initNormalKaimingKernel, initZero, sigmoidDeriv),
	// 10 * 10
	pool4(16, 10, 10, 2, "pool4", true),
	// 5 * 5
	conv5(16, 120, 5, 5, 5, false, sigmoid, "conv5", isInit_, true, initNormalKaimingKernel, initZero, sigmoidDeriv),
	// 1 * 1
	flatten6(120, 1, 1, "flatten6", true),
	fullConnect7(120, 84, sigmoid, "fullConnect7", isInit_, true, initNormalKaiming, initZero, sigmoidDeriv),
	fullConnect8(84, 10, sigmoid, "fullConnect8", isInit_, true, initNormalKaiming, initZero, sigmoidDeriv),
	outputLayer9(10, "softmax9", true),
	output(outputLayer9.output) {}


auto Lenet5::forward(InputType const& InputImage) -> OutputType {
	conv1.forward(Matrix<InputType>(1, 1, InputImage));
	pool2.forward(conv1.Output());
	conv3.forward(pool2.Output());
	pool4.forward(conv3.Output());
	conv5.forward(pool4.Output());
	flatten6.forward(conv5.Output());
	fullConnect7.forward(flatten6.Output());
	fullConnect8.forward(fullConnect7.Output());
	outputLayer9.forward(fullConnect8.Output());
	return outputLayer9.Output();
}

auto Lenet5::backward(InputType const& InputImage, Mat const& label) -> void {
	Mat& lossBack = outputLayer9.delta;
	double deno2 = 0, deno = 0, nume = 0;
	for (SizeType i = 0; i < label.rows(); ++i) {
		deno2 += output.at(i) * output.at(i);
		nume += output.at(i) * label.at(i);
	}
	deno = sqrt(deno2);
	//cout << '\n' << output<< '\n' << deno << ' ' << deno2 << '\n';
	for (SizeType i = 0; i < label.rows(); ++i) {
		//lossBack.at(i) = -label.at(i) * log(output.at(i));
		
		lossBack.at(i) = (label.at(i) * deno - nume * output.at(i) / deno) / deno2;
	}
	//cout << "\nlossBack\n" << lossBack << '\n';
	LayerConv2D::LossOutputContainer zero;

	outputLayer9.backward(fullConnect8.delta, fullConnect8.output);
	fullConnect8.backward(fullConnect7.delta, fullConnect7.output);
	fullConnect7.backward(flatten6.delta, flatten6.output);
	flatten6.backward(conv5.delta, conv5.output);
	conv5.backward(pool4.delta, pool4.output);
	pool4.backward(conv3.delta, conv3.output);
	conv3.backward(pool2.delta, pool2.output);
	pool2.backward(conv1.delta, conv1.output);
	conv1.backward(zero, Matrix<InputType>(1, 1, InputImage));

	//cout << "asdsdadada\n";
	//cout << lossBack << '\n';
	//cout << "fullConnect8.delta\n" << fullConnect8.delta << '\n';
	//cout << "fullConnect7.delta\n" << fullConnect7.delta << '\n';
	//cout << "fullConnect6.delta\n" << flatten6.delta << '\n';
	//cout << "fullConnect8.grad\n" << fullConnect7.GradCurrent() << '\n';
	//cout << conv1.delta << '\n';
}

auto Lenet5::update(double const& learningRate) -> void {
	//cout << fullConnect8.gradWeight_Accumulated << '\n';
	fullConnect8.update(learningRate);
	fullConnect7.update(learningRate);
	conv5.update(learningRate);
	conv3.update(learningRate);
	conv1.update(learningRate);
}

auto Lenet5::save(string const& filename) -> void {
	ofstream outfile(filename, std::ios::binary);
	conv1.save(outfile);
	conv3.save(outfile);
	conv5.save(outfile);
	fullConnect7.save(outfile);
	fullConnect8.save(outfile);
	outfile.close();
}

auto Lenet5::load(string const& filename) -> void {
	ifstream infile(filename, std::ios::binary);
	if (infile.is_open()) {
		conv1.load(infile);
		conv3.load(infile);
		conv5.load(infile);
		fullConnect7.load(infile);
		fullConnect8.load(infile);
	}
	infile.close();
}

}}