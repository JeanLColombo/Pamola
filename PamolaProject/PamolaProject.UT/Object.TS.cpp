#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <set>
#include "MockedEngine.h"
#include "MockedObject.h"
#include "MockedElement.h"

/*Test Functions and Classes*/
namespace Pamola
{
	namespace UT
	{
		namespace ObjectTS
		{
			class ObjectTestClass
			{
			private:

				std::unique_ptr<MockedEngine> mockedEngine;

			public:

				ObjectTestClass() : mockedEngine(std::unique_ptr<Pamola::UT::MockedEngine>(new Pamola::UT::MockedEngine())) {}

			private:

				std::set<std::shared_ptr<Pamola::UT::MockedElement>> createMockedObjects(int numberOfElements) {
				
					std::set<std::shared_ptr<Pamola::UT::MockedElement>> output;

					for (int i = 0; i < numberOfElements; i++)
						output.insert(mockedEngine->createElement<Pamola::UT::MockedElement>());
					
					return output;
				}


			};

		}
	}
}

/*Test Cases*/
BOOST_TEST_DECORATOR(*boost::unit_test::label("Object") *boost::unit_test::description("Testing the Pamola::Object Class"))
BOOST_AUTO_TEST_SUITE(ObjectTestSuite)

BOOST_TEST_DECORATOR(*boost::unit_test::label("LifetimeManagement"))
BOOST_AUTO_TEST_CASE(RawObjectCreationDestruction)
{
	Pamola::UT::MockedObject *obj = new Pamola::UT::MockedObject;
	delete obj;
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("LifetimeManagement"))
BOOST_AUTO_TEST_CASE(ScopedObjectCreationDestruction)
{
	Pamola::UT::MockedObject obj{};
	obj.getVariables();
	obj.getAdjacentComponents();
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("ObjectMethods"))
BOOST_AUTO_TEST_CASE(getId)
{
	Pamola::UT::MockedObject obj1{};
	auto eng = std::shared_ptr<Pamola::UT::MockedEngine>(new Pamola::UT::MockedEngine);
	auto elem1 = eng->createElement<Pamola::UT::MockedElement>();
	auto elem2 = eng->createElement<Pamola::UT::MockedElement>();
	BOOST_TEST(obj1.getId() == 0);
	BOOST_TEST(elem1->getId() == 0);
	BOOST_TEST(elem2->getId() == 1);
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("ObjectMethods"))
BOOST_AUTO_TEST_CASE(getPamolaType)
{
	Pamola::UT::MockedObject obj{};
	BOOST_TEST(static_cast<int>(obj.getPamolaType()) == static_cast<int>(Pamola::Type::Error));
	BOOST_TEST(static_cast<int>(obj.getBasePamolaType()) == static_cast<int>(Pamola::Type::Other));
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("ObjectMethods"))
BOOST_AUTO_TEST_CASE(getEquations)
{
	Pamola::UT::MockedObject obj{};
	BOOST_TEST(obj.getEquations().size() == 0);
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("ObjectMethods"))
BOOST_AUTO_TEST_CASE(OperatorOverloadsInequalities)
{
	std::shared_ptr<Pamola::Object> mockedElement1 = Pamola::createElement<Pamola::UT::MockedElement>();
	std::shared_ptr<Pamola::Object> mockedElement2 = Pamola::createElement<Pamola::UT::MockedElement>();

	BOOST_TEST(mockedElement1 < mockedElement2);
	BOOST_TEST(!(mockedElement2 < mockedElement1));

	BOOST_TEST(!(mockedElement1 > mockedElement2));
	BOOST_TEST(mockedElement2 > mockedElement1);
	
	BOOST_TEST(mockedElement1 <= mockedElement2);
	BOOST_TEST(!(mockedElement2 <= mockedElement1));

	BOOST_TEST(!(mockedElement1 >= mockedElement2));
	BOOST_TEST(mockedElement2 >= mockedElement1);
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("ObjectMethods"))
BOOST_AUTO_TEST_CASE(OperatorOverloadsEqualities)
{
	std::shared_ptr<Pamola::Object> mockedElement1 = Pamola::createElement<Pamola::UT::MockedElement>();
	std::shared_ptr<Pamola::Object> mockedElement2 = Pamola::createElement<Pamola::UT::MockedElement>();

	auto eng = std::shared_ptr<Pamola::UT::MockedEngine>(new Pamola::UT::MockedEngine(mockedElement1->getId()));
	
	std::shared_ptr<Pamola::Object> mockedElement3 = eng->createElement<Pamola::UT::MockedElement>();

	BOOST_TEST(mockedElement3 == mockedElement1);
	BOOST_TEST(!(mockedElement3 == mockedElement2));
	
	BOOST_TEST(!(mockedElement3 != mockedElement1));
	BOOST_TEST(mockedElement3 != mockedElement2);
	
	BOOST_TEST(mockedElement3 <= mockedElement1);
	BOOST_TEST(mockedElement3 <= mockedElement2);

	BOOST_TEST(mockedElement3 >= mockedElement1);
	BOOST_TEST(!(mockedElement3 >= mockedElement2));

}


BOOST_AUTO_TEST_SUITE_END()