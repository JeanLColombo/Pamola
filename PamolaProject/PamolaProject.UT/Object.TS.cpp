#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>
#include <set>
#include "MockedEngine.h"
#include "MockedObject.h"
#include "MockedElement.h"

namespace bdata = boost::unit_test::data;

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
BOOST_AUTO_TEST_CASE(getEngine)
{
	auto eng = std::shared_ptr<Pamola::UT::MockedEngine>(new Pamola::UT::MockedEngine);
	auto elem1 = eng->createElement<Pamola::UT::MockedElement>();
	auto elem2 = Pamola::createElement<Pamola::UT::MockedElement>();

	BOOST_TEST(elem1->getEngine() == eng);
	BOOST_TEST(elem2->getEngine() == Pamola::Engine::getLocalEngine());
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
BOOST_DATA_TEST_CASE(getConnectedComponents,
	bdata::make({ 0,1,2,3 }),
	numberOfterminals)
{
	auto mockedElement1 = Pamola::createElement<Pamola::UT::MockedElement>(numberOfterminals);
	auto mockedElement2 = Pamola::createElement<Pamola::UT::MockedElement>(1);

	auto connected1 = mockedElement1->getConnectedComponents();

	BOOST_TEST(connected1.size() == (1 + numberOfterminals));
	bool check1 = connected1.find(mockedElement1->getId()) != connected1.end();
	BOOST_TEST(check1, "Checking if mockedElement1 is inside connected1 list");

	for (auto &terminal : mockedElement1->getTerminals())
	{
		bool check2 = connected1.find(terminal->getId()) != connected1.end();
		BOOST_TEST(check2, "Checking if mockedElement1's terminals are inside connected1 list");
	}

	if (numberOfterminals != 0)
	{
		auto node = mockedElement1->getTerminal(0)->connectTo(mockedElement2->getTerminal(0));
	
		auto connected2 = mockedElement1->getConnectedComponents();
	
		BOOST_TEST(connected2.size() == (4 + numberOfterminals));
		bool check3 = connected2.find(mockedElement2->getId()) != connected2.end();
		BOOST_TEST(check3, "Checking if mockedElement2 is inside connected2 list");
		bool check4 = connected2.find(mockedElement2->getTerminal(0)->getId()) != connected2.end();
		BOOST_TEST(check4, "Checking if mockedElement2's terminal is inside connected2 list");
		bool check5 = connected2.find(node->getId()) != connected2.end();
		BOOST_TEST(check5, "Checking if node is inside connected2 list");
	}
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("ObjectMethods"))
BOOST_DATA_TEST_CASE(getCircuit,
	bdata::make({ 1,2,3 }),
	numberOfterminals)
{
	auto mockedElement1 = Pamola::createElement<Pamola::UT::MockedElement>(numberOfterminals);
	auto mockedElement2 = Pamola::createElement<Pamola::UT::MockedElement>(1);

	auto cir = mockedElement1->getTerminal(0)->connectTo(mockedElement2->getTerminal(0))->getCircuit();

	auto connected1 = mockedElement1->getConnectedComponents();
	
	for (auto &element : cir->getElements())
	{
		bool check = connected1.find(element->getId()) != connected1.end();
		BOOST_TEST(check, "Checking all elements are inside the circuit");
	}
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