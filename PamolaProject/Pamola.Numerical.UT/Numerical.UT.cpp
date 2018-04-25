#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Pamola.Numerical\Calculator.h"
#include "..\Pamola.Numerical\NewtonRaphson.h"
#include <complex>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PamolaNumericalUT
{		
	TEST_CLASS(DifferentialCalculus)
	{
	public:

		TEST_METHOD(DeriveAt1)
		{
			auto square = [](double x) {return x * x; };
			Logger::WriteMessage("DeriveAt1::Results");
			for (double point = -3.0; point <= 3.0; point++)
			{
				auto deriveAtPoint = Calculus::deriveAt(point, square);
				Logger::WriteMessage((std::to_string(point) + " | " + std::to_string(deriveAtPoint)).c_str());
				Assert::AreEqual(int(2 * point), int(deriveAtPoint));
			}

		};

		TEST_METHOD(DeriveAt2)
		{
			using namespace std::literals;
			auto square = [](std::complex<double> x) {return x * (x + 1.0i); };
			Logger::WriteMessage("DeriveAt2::Results");
			for (double point = -3.0; point <= 3.0; point++)
			{
				auto x = point + 2.0i*point;
				auto deriveAtPoint = Calculus::deriveAt(x, square);
				Logger::WriteMessage((std::to_string(x.real()) + " | " + std::to_string(deriveAtPoint.real())).c_str());
				Assert::AreEqual(int(pow(2.0 * x.real() - deriveAtPoint.real(),2.0)), 0);
				Logger::WriteMessage((std::to_string(x.imag()) + " | " + std::to_string(deriveAtPoint.imag())).c_str());
				Assert::AreEqual(int(pow(2.0 * x.imag() + 1.0 - deriveAtPoint.imag(), 2.0)), 0);
			};
		};


		TEST_METHOD(GradientAt1)
		{
			auto saddle = [](Eigen::VectorXd X) {return (X(0) * X(0)) - (X(1) * X(1)); };
			auto saddleAnalitic = [](Eigen::VectorXd X) {
				Eigen::VectorXd retX{ 2 };
				retX << (2 * X(0)), (-2 * X(1));
				return retX; };
			Logger::WriteMessage("GradientAt1::Results");
			Eigen::VectorXd X{ 2 };
			for (double pointX = -3.0; pointX <= 3.0; pointX += 0.1)
			{
				X(0) = pointX;
				for (double pointY = -3.0; pointY <= 3.0; pointY += 0.1)
				{
					X(1) = pointY;
					auto saddleGrad = Calculus::gradientAt(X, saddle);
					Assert::IsTrue(pow((saddleGrad(0) - saddleAnalitic(X)(0)), 2.0) < pow(10, -5.0));
					Assert::IsTrue(pow((saddleGrad(1) - saddleAnalitic(X)(1)), 2.0) < pow(10, -5.0));
				}
			}
		};

		TEST_METHOD(GradientAt2)
		{
			using namespace std::literals;
			auto saddle = [](Eigen::VectorXcd X) {return (X(0) * X(0)) - (X(1) * X(1)) + X(0)*X(1)*1.0i; };
			auto saddleAnalitic = [](Eigen::VectorXcd X) {
				Eigen::VectorXcd retX{ 2 };
				retX << (2.0*X(0) + X(1)*1.0i), (-2.0*X(1) + X(0)*1.0i);
				return retX; };
			Logger::WriteMessage("GradientAt2::Results");
			Eigen::VectorXcd X{ 2 };
			for (double pointX = -3.0; pointX <= 3.0; pointX += 0.1)
			{
				X(0) = pointX * (1.0 + 1.0i);
				for (double pointY = -3.0; pointY <= 3.0; pointY += 0.1)
				{
					X(1) = pointY * (1.0 - 1.0i);
					auto saddleGrad = Calculus::gradientAt(X, saddle);
					Assert::IsTrue(pow((saddleGrad(0).real() - saddleAnalitic(X)(0).real()), 2.0) < pow(10, -5.0));
					Assert::IsTrue(pow((saddleGrad(1).real() - saddleAnalitic(X)(1).real()), 2.0) < pow(10, -5.0));
					Assert::IsTrue(pow((saddleGrad(0).imag() - saddleAnalitic(X)(0).imag()), 2.0) < pow(10, -5.0));
					Assert::IsTrue(pow((saddleGrad(1).imag() - saddleAnalitic(X)(1).imag()), 2.0) < pow(10, -5.0));
				}
			}
		};

		TEST_METHOD(JacobianAt1)
		{
			auto f1 = [](Eigen::VectorXd X) {return X(0) * X(0) + X(1) * X(1); };
			auto f2 = [](Eigen::VectorXd X) {return -X(1); };
			auto f3 = [](Eigen::VectorXd X) {return 2 * X(0); };
			auto df1 = [](Eigen::VectorXd X) {
				Eigen::VectorXd retX{ 2 };
				retX << (2 * X(0)), (2 * X(1));
				return retX; };
			auto df2 = [](Eigen::VectorXd X) {
				Eigen::VectorXd retX{ 2 };
				retX << 0, -1;
				return retX; };
			auto df3 = [](Eigen::VectorXd X) {
				Eigen::VectorXd retX{ 2 };
				retX << 2, 0;
				return retX; };

			for (double pointX = -3.0; pointX <= 3.0; pointX += 0.1)
			{
				for (double pointY = -3.0; pointY <= 3.0; pointY += 0.1)
				{
					Eigen::VectorXd X{ 2 };
					X << pointX, pointY;
					auto jacobianOfF = Calculus::jacobianAt(X, { f1,f2,f3 });

					Assert::IsTrue(pow((df1(X)(0) - jacobianOfF(0, 0)), 2.0) < pow(10, -5.0));
					Assert::IsTrue(pow((df1(X)(1) - jacobianOfF(0, 1)), 2.0) < pow(10, -5.0));
					Assert::IsTrue(pow((df2(X)(0) - jacobianOfF(1, 0)), 2.0) < pow(10, -5.0));
					Assert::IsTrue(pow((df2(X)(1) - jacobianOfF(1, 1)), 2.0) < pow(10, -5.0));
					Assert::IsTrue(pow((df3(X)(0) - jacobianOfF(2, 0)), 2.0) < pow(10, -5.0));
					Assert::IsTrue(pow((df3(X)(1) - jacobianOfF(2, 1)), 2.0) < pow(10, -5.0));
				}
			}

		};

		TEST_METHOD(JacobianAt2)
		{
			using namespace std::literals;
			auto f1 = [](Eigen::VectorXcd X) {return X(0) * X(0) + (X(1) * X(1))*(1.0i); };
			auto f2 = [](Eigen::VectorXcd X) {return -X(1) + 1.0i; };
			auto f3 = [](Eigen::VectorXcd X) {return 2.0 * X(0); };
			auto df1 = [](Eigen::VectorXcd X) {
				Eigen::VectorXcd retX{ 2 };
				retX << (2.0 * X(0)), (2.0i * X(1));
				return retX; };
			auto df2 = [](Eigen::VectorXcd X) {
				Eigen::VectorXcd retX{ 2 };
				retX << 0.0, -1.0;
				return retX; };
			auto df3 = [](Eigen::VectorXcd X) {
				Eigen::VectorXcd retX{ 2 };
				retX << 2.0, 0.0;
				return retX; };

			for (double pointX = -3.0; pointX <= 3.0; pointX += 0.1)
			{
				for (double pointY = -3.0; pointY <= 3.0; pointY += 0.1)
				{
					Eigen::VectorXcd X{ 2 };
					X << pointX * (1.0 + 2.0i), pointY*(1.0 - 0.5i);
					auto jacobianOfF = Calculus::jacobianAt(X, { f1,f2,f3 });

					Assert::IsTrue(pow((df1(X)(0).real() - jacobianOfF(0, 0).real()), 2.0) < pow(10, -5.0));
					Assert::IsTrue(pow((df1(X)(1).real() - jacobianOfF(0, 1).real()), 2.0) < pow(10, -5.0));
					Assert::IsTrue(pow((df2(X)(0).real() - jacobianOfF(1, 0).real()), 2.0) < pow(10, -5.0));
					Assert::IsTrue(pow((df2(X)(1).real() - jacobianOfF(1, 1).real()), 2.0) < pow(10, -5.0));
					Assert::IsTrue(pow((df3(X)(0).real() - jacobianOfF(2, 0).real()), 2.0) < pow(10, -5.0));
					Assert::IsTrue(pow((df3(X)(1).real() - jacobianOfF(2, 1).real()), 2.0) < pow(10, -5.0));

					Assert::IsTrue(pow((df1(X)(0).imag() - jacobianOfF(0, 0).imag()), 2.0) < pow(10, -5.0));
					Assert::IsTrue(pow((df1(X)(1).imag() - jacobianOfF(0, 1).imag()), 2.0) < pow(10, -5.0));
					Assert::IsTrue(pow((df2(X)(0).imag() - jacobianOfF(1, 0).imag()), 2.0) < pow(10, -5.0));
					Assert::IsTrue(pow((df2(X)(1).imag() - jacobianOfF(1, 1).imag()), 2.0) < pow(10, -5.0));
					Assert::IsTrue(pow((df3(X)(0).imag() - jacobianOfF(2, 0).imag()), 2.0) < pow(10, -5.0));
					Assert::IsTrue(pow((df3(X)(1).imag() - jacobianOfF(2, 1).imag()), 2.0) < pow(10, -5.0));
				}
			}

		};

	};


	TEST_CLASS(Optimizations)
	{
		TEST_METHOD(NewtonRaphsonClassicalOneVar)
		{
			using namespace SystemSolver;
			auto roots = [](double x) {return x * x - 2.0; };
			double x0 = +3.0;
			double error = 1.0;
			int i = 0;
			NewtonRaphson calculator;
			while (error >= 1.0e-6 && i < 100)
			{
				auto x1 = calculator.iterate(x0, roots);
				error = pow((x1 - x0), 2);
				x0 = x1;
				i++;
			}
			
			Logger::WriteMessage(("Root is: " + std::to_string(x0) 
				+ " | iterations = " + std::to_string(i)).c_str());
		};
		TEST_METHOD(NewtonRaphsonClassicalMultVarLinear)
		{
			using namespace SystemSolver;
			auto line1 = [](Eigen::VectorXd X) {
				return X(0) + X(1) - 2; };
			auto line2 = [](Eigen::VectorXd X) {
				return X(0) - X(1) + 5; };
			Eigen::VectorXd X0{ 2 };
			X0 << 0.0, 0.0;
			double error = 1.0;
			int i = 0;
			NewtonRaphson calculator;
			std::vector<multVarFunc> F = { line1,line2 };
			while (error >= 1.0e-6 && i < 100)
			{
				auto X1 = calculator.iterate(X0, F);
				error = pow((X1(0) - X0(0)), 2) + pow((X1(1) - X0(1)), 2);
				X0 = X1;
				i++;
			}

			Logger::WriteMessage("System Solution:");
			Logger::WriteMessage(("i = " + std::to_string(i)).c_str());
			Logger::WriteMessage(("X(0) = " + std::to_string(X0(0))).c_str());
			Logger::WriteMessage(("X(1) = " + std::to_string(X0(1))).c_str());
		};
		TEST_METHOD(NewtonRaphsonClassicalMultVarNonLinear1)
		{
			using namespace SystemSolver;
			auto line1 = [](Eigen::VectorXd X) {
				return X(0) + X(1) - 3; };
			auto notLine2 = [](Eigen::VectorXd X) {
				return X(0)*X(1) + 5; };
			Eigen::VectorXd X0{ 2 };
			X0 << 0.0, 0.0;
			double error = 1.0;
			int i = 0;
			NewtonRaphson calculator;
			std::vector<multVarFunc> F = { line1,notLine2 };
			while (error >= 1.0e-6 && i < 100)
			{
				auto X1 = calculator.iterate(X0, F);
				error = pow((X1(0) - X0(0)), 2) + pow((X1(1) - X0(1)), 2);
				X0 = X1;
				i++;
			}

			Logger::WriteMessage("System Solution:");
			Logger::WriteMessage(("i = " + std::to_string(i)).c_str());
			Logger::WriteMessage(("X(0) = " + std::to_string(X0(0))).c_str());
			Logger::WriteMessage(("X(1) = " + std::to_string(X0(1))).c_str());
		};
		TEST_METHOD(NewtonRaphsonClassicalMultVarNonLinear2)
		{
			using namespace SystemSolver;
			auto notLine1 = [](Eigen::VectorXd X) {
				return X(0)*X(1)*X(2) - 25; };
			auto notLine2 = [](Eigen::VectorXd X) {
				return X(0)*X(0) - X(1) + X(2); };
			auto notLine3 = [](Eigen::VectorXd X) {
				return X(0) - X(1) + 2*X(2) + 30; };
			Eigen::VectorXd X0{ 3 };
			X0 << 1.0, 1.0, 1.0;
			double error = 1.0;
			int i = 0;
			NewtonRaphson calculator;
			std::vector<multVarFunc> F = { notLine1,notLine2,notLine3 };
			while (error >= 1.0e-6 && i < 100)
			{
				auto X1 = calculator.iterate(X0, F);
				error = pow((X1(0) - X0(0)), 2) + pow((X1(1) - X0(1)), 2) + pow((X1(2) - X0(2)), 2);
				X0 = X1;
				i++;
			}

			Logger::WriteMessage("System Solution:");
			Logger::WriteMessage(("i = " + std::to_string(i)).c_str());
			Logger::WriteMessage(("X(0) = " + std::to_string(X0(0))).c_str());
			Logger::WriteMessage(("X(1) = " + std::to_string(X0(1))).c_str());
			Logger::WriteMessage(("X(2) = " + std::to_string(X0(2))).c_str());
		};
		TEST_METHOD(NewtonRaphsonClassicalMultVarNonLinear3)
		{
			using namespace SystemSolver;
			auto notLine1 = [](Eigen::VectorXd X) {
				return X(0)*X(1) - 25; };
			auto notLine2 = [](Eigen::VectorXd X) {
				return X(0)*X(0) - X(1); };
			auto notLine3 = [](Eigen::VectorXd X) {
				return -2*X(0)*X(1) + 50; };
			Eigen::VectorXd X0{ 2 };
			X0 << 1.0, 1.0;
			double error = 1.0;
			int i = 0;
			NewtonRaphson calculator;
			std::vector<multVarFunc> F = { notLine1,notLine2,notLine3 };
			while (error >= 1.0e-6 && i < 100)
			{
				auto X1 = calculator.iterate(X0, F);
				error = pow((X1(0) - X0(0)), 2) + pow((X1(1) - X0(1)), 2);
				X0 = X1;
				i++;
			}

			Logger::WriteMessage("System Solution:");
			Logger::WriteMessage(("i = " + std::to_string(i)).c_str());
			Logger::WriteMessage(("X(0) = " + std::to_string(X0(0))).c_str());
			Logger::WriteMessage(("X(1) = " + std::to_string(X0(1))).c_str());
		};
	};
};