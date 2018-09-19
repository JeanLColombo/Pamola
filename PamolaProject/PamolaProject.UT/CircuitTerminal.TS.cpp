#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "MockedEngine.h"
#include "MockedElement.h"

/*Test Cases*/
BOOST_TEST_DECORATOR(*boost::unit_test::label("CircuitTerminal") *boost::unit_test::description("Testing the Pamola::CircuitTerminal Class"))
BOOST_AUTO_TEST_SUITE(CircuitTerminalTestSuite)

BOOST_TEST_DECORATOR(*boost::unit_test::label("CircuitTerminalMethods"))
BOOST_AUTO_TEST_CASE(getElement) 
{
	auto mockedElement = Pamola::createElement<Pamola::UT::MockedElement>(1);

	BOOST_TEST(mockedElement == mockedElement->getTerminal(0)->getElement());
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("CircuitTerminalMethods"))
BOOST_AUTO_TEST_CASE(connectTo)
{
	auto mockedElement1 = Pamola::createElement<Pamola::UT::MockedElement>(1);
	auto mockedElement2 = Pamola::createElement<Pamola::UT::MockedElement>(1);

	auto node1 = mockedElement1->getTerminal(0)->connectTo(mockedElement2->getTerminal(0));

	BOOST_TEST(node1 != nullptr);
	BOOST_TEST(node1 == mockedElement1->getTerminal(0)->getNode());
	BOOST_TEST(node1 == mockedElement2->getTerminal(0)->getNode());
}

//TODO: test all possible scenarios of connectTo. Inclunding a terminal connecting to itself.

BOOST_AUTO_TEST_SUITE_END()