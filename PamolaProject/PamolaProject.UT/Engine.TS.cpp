#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>
#include <vector>
#include <iostream>
#include "MockedEngine.h"
#include "MockedElement.h"
#include "MockedModelSolver.h"

namespace bdata = boost::unit_test::data;

/*Test Functions and Classes*/
namespace Pamola
{
	namespace UT
	{
		namespace EngineTS
		{
			class EngineTestClass
			{
			private:

				std::shared_ptr<MockedEngine> scopedMockedEngine;

			public:

				EngineTestClass() : scopedMockedEngine(std::shared_ptr<Pamola::UT::MockedEngine>(new Pamola::UT::MockedEngine())) {}
				~EngineTestClass() {}

				void testFunctionGetLocalObjects(
					bool scoped,
					int numberOfObjects,
					int randomObject) {
										
					if (scoped)
						BOOST_TEST(scopedMockedEngine->getLocalObjects().size() == 0);
					else
						BOOST_TEST(Engine::getLocalEngine()->getLocalObjects().size() == 0);

					if (scoped)
						std::cout << "ScopedEngine: Creating " << numberOfObjects << " mocked objects. Random access at: " << randomObject << std::endl;
					else
						std::cout << "StaticEngine: Creating " << numberOfObjects << " mocked objects. Random access at: " << randomObject << std::endl;

					{
						auto MockedElementVector = massCreateMockedElements(scoped, numberOfObjects);

						if (scoped)
						{
							BOOST_TEST(scopedMockedEngine->getLocalObjects().size() == numberOfObjects);
							BOOST_TEST(MockedElementVector.at(randomObject) == scopedMockedEngine->getLocalObject(randomObject));
						}
						else
						{
							BOOST_TEST(Engine::getLocalEngine()->getLocalObjects().size() == numberOfObjects);
							BOOST_TEST(MockedElementVector.at(randomObject) == Engine::getLocalEngine()->getLocalObject(MockedElementVector.at(randomObject)->getId()));
						}

					}

					if (scoped)
						BOOST_TEST(scopedMockedEngine->getLocalObjects().size() == 0);
					else
						BOOST_TEST(Engine::getLocalEngine()->getLocalObjects().size() == 0);
				}
			private:

				std::vector<std::shared_ptr<Pamola::UT::MockedElement>> massCreateMockedElements(
					bool scoped,
					int numberOfObjects) {

					std::vector<std::shared_ptr<Pamola::UT::MockedElement>> output;

					for (int i = 0; i < numberOfObjects; i++)
					{
						if (scoped)
							output.push_back(scopedMockedEngine->createElement<Pamola::UT::MockedElement>());
						else
							output.push_back(createElement<Pamola::UT::MockedElement>());
					}

					return output;
				}

			};

		}
	}
}

/*Test Cases*/
BOOST_TEST_DECORATOR(*boost::unit_test::label("Engine") 
	*boost::unit_test::description("Testing the Pamola::Engine Class")
	*boost::unit_test::tolerance(1e-100))
BOOST_AUTO_TEST_SUITE(EngineTestSuite)

BOOST_TEST_DECORATOR(*boost::unit_test::label("LifetimeManagement"))
BOOST_AUTO_TEST_CASE(staticEngineCreation)
{
	BOOST_TEST(Pamola::Engine::getLocalEngine() != nullptr);
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("LifetimeManagement"))
BOOST_AUTO_TEST_CASE(rawEngineCreationDestruction)
{
	Pamola::UT::MockedEngine *eng = new Pamola::UT::MockedEngine;
	delete eng;
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("LifetimeManagement"))
BOOST_AUTO_TEST_CASE(scopedEngineCreationDestruction)
{
	Pamola::UT::MockedEngine eng{};
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("Methods"))
BOOST_AUTO_TEST_CASE(getLocalEngineTest)
{
	auto eng = std::shared_ptr<Pamola::UT::MockedEngine>(new Pamola::UT::MockedEngine());
	BOOST_TEST(Pamola::Engine::getLocalEngine() == eng->getLocalEngine());
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("Methods"))
BOOST_DATA_TEST_CASE(
	getLocalObjects,
	bdata::make({true,false}) ^ bdata::random(1,100) ^ bdata::random(0, 1000),
	typeOfEngine,numberOfObjects,randomIndex)
{
	Pamola::UT::EngineTS::EngineTestClass().testFunctionGetLocalObjects(
		typeOfEngine, 
		numberOfObjects, 
		randomIndex*numberOfObjects / 1000);
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("Methods"))
BOOST_AUTO_TEST_CASE(getSetModelSolver)
{
	auto mockedMS = std::shared_ptr<Pamola::UT::MockedModelSolver>(new Pamola::UT::MockedModelSolver);
	BOOST_TEST(Pamola::Engine::getLocalEngine()->getSolver() != mockedMS);
	Pamola::Engine::getLocalEngine()->setSolver(mockedMS);
	BOOST_TEST(Pamola::Engine::getLocalEngine()->getSolver() == mockedMS);
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("Methods"))
BOOST_DATA_TEST_CASE(
	createTerminalsFor,
	bdata::make({ true,false }) ^ bdata::random(1, 100),
	typeOfEngine, numberOfTerminals)
{
	std::shared_ptr<Pamola::Engine> testEngine;

	if (typeOfEngine)
	{
		testEngine = std::shared_ptr<Pamola::UT::MockedEngine>(new Pamola::UT::MockedEngine);
		std::cout << "ScopedEngine: Creating a mocked object with " << numberOfTerminals << " terminals." << std::endl;
	}
	else
	{
		testEngine = Pamola::Engine::getLocalEngine();
		std::cout << "StaticEngine: Creating a mocked object with " << numberOfTerminals << " terminals." << std::endl;
	}

	auto mockedElement = testEngine->createElement<Pamola::UT::MockedElement, int>(numberOfTerminals);
	   	 
	BOOST_TEST(testEngine->getLocalObjects().size() == (numberOfTerminals + 1));
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("Methods"))
BOOST_AUTO_TEST_CASE(createNode)
{
	auto mockedElement1 = Pamola::createElement<Pamola::UT::MockedElement, int>(1);
	auto mockedElement2 = Pamola::createElement<Pamola::UT::MockedElement, int>(1);

	auto node = mockedElement1->getTerminal(0)->connectTo(mockedElement2->getTerminal(0));

	BOOST_TEST(node != nullptr);
	BOOST_TEST(Pamola::Engine::getLocalEngine()->getLocalObjects().size() == 5);
	BOOST_TEST(node == Pamola::Engine::getLocalEngine()->getLocalObject(node->getId()));
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("Methods"))
BOOST_AUTO_TEST_CASE(createCircuit)
{
	auto mockedElement1 = Pamola::createElement<Pamola::UT::MockedElement, int>(1);
	auto mockedElement2 = Pamola::createElement<Pamola::UT::MockedElement, int>(1);

	auto circuit = mockedElement1->getTerminal(0)->connectTo(mockedElement2->getTerminal(0))->getCircuit();

	BOOST_TEST(circuit != nullptr);
	BOOST_TEST(Pamola::Engine::getLocalEngine()->getLocalObjects().size() == 6);
	BOOST_TEST(circuit == Pamola::Engine::getLocalEngine()->getLocalObject(circuit->getId()));
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("Methods"))
BOOST_AUTO_TEST_CASE(callSolver)
{
	auto mockedMS = std::shared_ptr<Pamola::UT::MockedModelSolver>(new Pamola::UT::MockedModelSolver);
	auto mockedElement = Pamola::createElement<Pamola::UT::MockedElement>();
	
	BOOST_TEST(mockedElement->getVar().real() == 0.0, 1e-12);
	BOOST_TEST(mockedElement->getVar().imag() == 0.0, 1e-12);

	Pamola::Engine::getLocalEngine()->setSolver(mockedMS);
	Pamola::Engine::getLocalEngine()->callSolver(*&mockedElement->getVariables(), *&mockedElement->getEquations());

	BOOST_TEST(mockedElement->getVar().real() == 4.0, 1e-12);
	BOOST_TEST(mockedElement->getVar().imag() == 3.0, 1e-12);
}

BOOST_AUTO_TEST_SUITE_END()