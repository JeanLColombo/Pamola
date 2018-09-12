#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>
#include <vector>
#include <iostream>
#include "MockedEngine.h"
#include "MockedElement.h"

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
			public:

				EngineTestClass() : scopedMockedEngine(std::shared_ptr<Pamola::UT::MockedEngine>(new Pamola::UT::MockedEngine())) {}
				~EngineTestClass() {}

				std::shared_ptr<MockedEngine> scopedMockedEngine;

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
							BOOST_TEST(static_cast<std::shared_ptr<Object>>(MockedElementVector.at(randomObject)) == scopedMockedEngine->getLocalObject(randomObject));
						}
						else
						{
							BOOST_TEST(Engine::getLocalEngine()->getLocalObjects().size() == numberOfObjects);
							BOOST_TEST(static_cast<std::shared_ptr<Object>>(MockedElementVector.at(randomObject)) == Engine::getLocalEngine()->getLocalObject(randomObject));
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
BOOST_TEST_DECORATOR(*boost::unit_test::label("Engine") *boost::unit_test::description("Testing the Pamola::Engine Class"))
BOOST_AUTO_TEST_SUITE(EngineTestSuite)

BOOST_TEST_DECORATOR(*boost::unit_test::label("LifetimeManagement"))
BOOST_AUTO_TEST_CASE(StaticEngineCreation)
{
	BOOST_TEST(Pamola::Engine::getLocalEngine() != nullptr);
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("LifetimeManagement"))
BOOST_AUTO_TEST_CASE(RawEngineCreationDestruction)
{
	Pamola::UT::MockedEngine *eng = new Pamola::UT::MockedEngine;
	delete eng;
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("LifetimeManagement"))
BOOST_AUTO_TEST_CASE(ScopedEngineCreationDestruction)
{
	Pamola::UT::MockedEngine eng{};
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("EngineMethods"))
BOOST_AUTO_TEST_CASE(getLocalEngineTest)
{
	auto eng = std::shared_ptr<Pamola::UT::MockedEngine>(new Pamola::UT::MockedEngine());
	BOOST_TEST(Pamola::Engine::getLocalEngine() == eng->getLocalEngine());
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("EngineMethods"))
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

BOOST_AUTO_TEST_SUITE_END()