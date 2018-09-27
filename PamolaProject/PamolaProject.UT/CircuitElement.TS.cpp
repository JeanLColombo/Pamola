#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "MockedEngine.h"
#include "MockedElement.h"

/*Test Cases*/
BOOST_TEST_DECORATOR(*boost::unit_test::label("CircuitElement") *boost::unit_test::description("Testing the Pamola::CircuitElement Class"))
BOOST_AUTO_TEST_SUITE(CircuitElementTestSuite)

BOOST_TEST_DECORATOR(*boost::unit_test::label("Methods"))
BOOST_AUTO_TEST_CASE(circuitElementMainMethods)
{
	auto eng = std::shared_ptr<Pamola::UT::MockedEngine>(new Pamola::UT::MockedEngine());

	auto mockedElement1 = eng->createElement<Pamola::UT::MockedElement>();
	auto mockedElement2 = eng->createElement<Pamola::UT::MockedElement>(2);

	BOOST_TEST(mockedElement1->getTerminals().size() == 0);
	BOOST_TEST(mockedElement2->getTerminals().size() == 2);

	BOOST_TEST(mockedElement1->getNumberOfTerminals() == 0);
	BOOST_TEST(mockedElement2->getNumberOfTerminals() == 2);

	std::vector<std::shared_ptr<Pamola::Object>> mockedElement2terminalObjects;

	mockedElement2terminalObjects.push_back(eng->getLocalObject(2));
	mockedElement2terminalObjects.push_back(eng->getLocalObject(3));

	auto mockedElement2terminals = mockedElement2->getTerminals();

	std::vector<uint32_t> terminalsIds;

	for (auto &id : mockedElement2->getAdjacentComponents())
		terminalsIds.push_back(id);

	for (int i = 0; i < 2; i++)
	{
		BOOST_TEST(mockedElement2terminalObjects[i] == mockedElement2terminals[i]);
		BOOST_TEST(mockedElement2terminalObjects[i] == mockedElement2->getTerminal(i));
		BOOST_TEST(mockedElement2terminalObjects[i]->getId() == terminalsIds.at(i));
	}
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("Methods"))
BOOST_AUTO_TEST_CASE(getPamolaType)
{
	auto mockedElement = Pamola::createElement<Pamola::UT::MockedElement>();
	BOOST_TEST(static_cast<int>(mockedElement->getPamolaType()) == static_cast<int>(Pamola::Type::CircuitElement));
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("Methods"))
BOOST_AUTO_TEST_CASE(operatorOverloadsInequalities)
{
	std::shared_ptr<Pamola::CircuitElement> mockedElement1 = Pamola::createElement<Pamola::UT::MockedElement>();
	std::shared_ptr<Pamola::CircuitElement> mockedElement2 = Pamola::createElement<Pamola::UT::MockedElement>();

	BOOST_TEST(mockedElement1 < mockedElement2);
	BOOST_TEST(!(mockedElement2 < mockedElement1));

	BOOST_TEST(!(mockedElement1 > mockedElement2));
	BOOST_TEST(mockedElement2 > mockedElement1);

	BOOST_TEST(mockedElement1 <= mockedElement2);
	BOOST_TEST(!(mockedElement2 <= mockedElement1));

	BOOST_TEST(!(mockedElement1 >= mockedElement2));
	BOOST_TEST(mockedElement2 >= mockedElement1);
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("Methods"))
BOOST_AUTO_TEST_CASE(operatorOverloadsEqualities)
{
	std::shared_ptr<Pamola::CircuitElement> mockedElement1 = Pamola::createElement<Pamola::UT::MockedElement>();
	std::shared_ptr<Pamola::CircuitElement> mockedElement2 = Pamola::createElement<Pamola::UT::MockedElement>();

	auto eng = std::shared_ptr<Pamola::UT::MockedEngine>(new Pamola::UT::MockedEngine(mockedElement1->getId()));

	std::shared_ptr<Pamola::CircuitElement> mockedElement3 = eng->createElement<Pamola::UT::MockedElement>();

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