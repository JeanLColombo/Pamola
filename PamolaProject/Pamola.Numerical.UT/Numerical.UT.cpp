#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Pamola.Numerical\Calculator.h"

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
				Assert::AreEqual(int(2*point), int(deriveAtPoint));
			}
						
		};

		TEST_METHOD(GradientAt1)
		{
			auto saddle = [](std::vector<double> X) {return (X[0] * X[0]) - (X[1] * X[1]); };
			auto saddleAnalitic = [](std::vector<double> X) {
				std::vector<double> retX{ (2 * X[0]) , (-2 * X[1]) };
				return retX; };
			Logger::WriteMessage("GradientAt1::Results");
			for (double pointX = -3.0; pointX <= 3.0; pointX+=0.1)
			{
				for (double pointY = -3.0; pointY <= 3.0; pointY += 0.1)
				{
					auto X = { pointX,pointY };
					auto saddleGrad = Calculus::gradientAt(X, saddle);
					Assert::IsTrue(pow((saddleGrad[0] - saddleAnalitic(X)[0]), 2.0) < pow(10, -5.0));
					Assert::IsTrue(pow((saddleGrad[0] - saddleAnalitic(X)[0]), 2.0) < pow(10, -5.0));
				}
			}
		};

		TEST_METHOD(JacobianAt1) 
		{
			auto f1 = [](std::vector<double> X) {return X[0] * X[0] + X[1] * X[1]; };
			auto f2 = [](std::vector<double> X) {return -X[1]; };
			auto f3 = [](std::vector<double> X) {return 2 * X[0]; };
			auto df1 = [](std::vector<double> X) {
				std::vector<double> retX{ (2 * X[0]) , (2 * X[1]) };
				return retX; };
			auto df2 = [](std::vector<double> X) {
				std::vector<double> retX{ 0 , -1 };
				return retX; };
			auto df3 = [](std::vector<double> X) {
				std::vector<double> retX{ 2 , 0 };
				return retX; };
			
			for (double pointX = -3.0; pointX <= 3.0; pointX += 0.1)
			{
				for (double pointY = -3.0; pointY <= 3.0; pointY += 0.1)
				{
					auto X = { pointX,pointY };
					auto jacobianOfF = Calculus::jacobianAt(X, { f1,f2,f3 });
					
					/*Assert::IsTrue(pow((df1(X)[0] - jacobianOfF[0][0]), 2.0) < pow(10, -5.0));
					Assert::IsTrue(pow((df1(X)[1] - jacobianOfF[0][1]), 2.0) < pow(10, -5.0));
					Assert::IsTrue(pow((df2(X)[0] - jacobianOfF[1][0]), 2.0) < pow(10, -5.0));
					Assert::IsTrue(pow((df2(X)[1] - jacobianOfF[1][1]), 2.0) < pow(10, -5.0));
					Assert::IsTrue(pow((df3(X)[0] - jacobianOfF[2][0]), 2.0) < pow(10, -5.0));
					Assert::IsTrue(pow((df3(X)[1] - jacobianOfF[2][1]), 2.0) < pow(10, -5.0));*/

					Assert::IsTrue(pow((df1(X)[0] - jacobianOfF(0,0)), 2.0) < pow(10, -5.0));
					Assert::IsTrue(pow((df1(X)[1] - jacobianOfF(0,1)), 2.0) < pow(10, -5.0));
					Assert::IsTrue(pow((df2(X)[0] - jacobianOfF(1,0)), 2.0) < pow(10, -5.0));
					Assert::IsTrue(pow((df2(X)[1] - jacobianOfF(1,1)), 2.0) < pow(10, -5.0));
					Assert::IsTrue(pow((df3(X)[0] - jacobianOfF(2,0)), 2.0) < pow(10, -5.0));
					Assert::IsTrue(pow((df3(X)[1] - jacobianOfF(2,1)), 2.0) < pow(10, -5.0));
				}
			}

		};

	};
}