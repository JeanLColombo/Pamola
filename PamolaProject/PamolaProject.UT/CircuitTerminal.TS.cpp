#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>
#include "MockedEngine.h"
#include "MockedElement.h"

namespace bdata = boost::unit_test::data;

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
BOOST_AUTO_TEST_CASE(getNode)
{
	auto mockedElement = Pamola::createElement<Pamola::UT::MockedElement>(2);

	BOOST_TEST(mockedElement->getTerminal(0)->getNode() == nullptr);

	auto node = mockedElement->getTerminal(0)->connectTo(mockedElement->getTerminal(1));

	BOOST_TEST(mockedElement->getTerminal(0)->getNode() == node);
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("CircuitTerminalMethods"))
BOOST_AUTO_TEST_CASE(connectToDanglingTerminal)
{
	auto mockedElement1 = Pamola::createElement<Pamola::UT::MockedElement>(1);
	auto mockedElement2 = Pamola::createElement<Pamola::UT::MockedElement>(1);

	auto node1 = mockedElement1->getTerminal(0)->connectTo(mockedElement2->getTerminal(0));

	BOOST_TEST(node1 != nullptr);
	BOOST_TEST(node1 == mockedElement1->getTerminal(0)->getNode());
	BOOST_TEST(node1 == mockedElement2->getTerminal(0)->getNode());
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("CircuitTerminalMethods"))
BOOST_AUTO_TEST_CASE(connectToConnectedTerminal)
{
	auto mockedElement1 = Pamola::createElement<Pamola::UT::MockedElement>(1);
	auto mockedElement2 = Pamola::createElement<Pamola::UT::MockedElement>(1);
	auto mockedElement3 = Pamola::createElement<Pamola::UT::MockedElement>(1);
	
	mockedElement1->getTerminal(0)->connectTo(mockedElement2->getTerminal(0));

	auto node1 = mockedElement3->getTerminal(0)->connectTo(mockedElement2->getTerminal(0));

	BOOST_TEST(node1 != nullptr);
	BOOST_TEST(node1 == mockedElement1->getTerminal(0)->getNode());
	BOOST_TEST(node1 == mockedElement2->getTerminal(0)->getNode());
	BOOST_TEST(node1 == mockedElement3->getTerminal(0)->getNode());
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("CircuitTerminalMethods"))
BOOST_AUTO_TEST_CASE(ConnectedTerminalconnectTo)
{
	auto mockedElement1 = Pamola::createElement<Pamola::UT::MockedElement>(1);
	auto mockedElement2 = Pamola::createElement<Pamola::UT::MockedElement>(1);
	auto mockedElement3 = Pamola::createElement<Pamola::UT::MockedElement>(1);

	mockedElement1->getTerminal(0)->connectTo(mockedElement2->getTerminal(0));

	auto node1 = mockedElement1->getTerminal(0)->connectTo(mockedElement3->getTerminal(0));

	BOOST_TEST(node1 != nullptr);
	BOOST_TEST(node1 == mockedElement1->getTerminal(0)->getNode());
	BOOST_TEST(node1 == mockedElement2->getTerminal(0)->getNode());
	BOOST_TEST(node1 == mockedElement3->getTerminal(0)->getNode());
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("CircuitTerminalMethods"))
BOOST_AUTO_TEST_CASE(ConnectedTerminalconnectToConnectedTerminal)
{
	auto mockedElement1 = Pamola::createElement<Pamola::UT::MockedElement>(2);
	auto mockedElement2 = Pamola::createElement<Pamola::UT::MockedElement>(2);

	mockedElement1->getTerminal(0)->connectTo(mockedElement2->getTerminal(0));
	mockedElement1->getTerminal(1)->connectTo(mockedElement2->getTerminal(1));
	
	auto node1 = mockedElement1->getTerminal(0)->connectTo(mockedElement1->getTerminal(1));

	BOOST_TEST(node1 != nullptr);
	BOOST_TEST(node1 == mockedElement1->getTerminal(0)->getNode());
	BOOST_TEST(node1 == mockedElement2->getTerminal(0)->getNode());
	BOOST_TEST(node1 == mockedElement1->getTerminal(1)->getNode());
	BOOST_TEST(node1 == mockedElement2->getTerminal(1)->getNode());
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("CircuitTerminalMethods"))
BOOST_AUTO_TEST_CASE(ConnectedTerminalconnectToConnectedNode)
{
	auto mockedElement1 = Pamola::createElement<Pamola::UT::MockedElement>(2);
	auto mockedElement2 = Pamola::createElement<Pamola::UT::MockedElement>(2);

	mockedElement1->getTerminal(0)->connectTo(mockedElement2->getTerminal(0));
	mockedElement1->getTerminal(1)->connectTo(mockedElement2->getTerminal(1));

	auto node1 = mockedElement1->getTerminal(0)->connectTo(mockedElement1->getTerminal(1)->getNode());

	BOOST_TEST(node1 != nullptr);
	BOOST_TEST(node1 == mockedElement1->getTerminal(0)->getNode());
	BOOST_TEST(node1 == mockedElement2->getTerminal(0)->getNode());
	BOOST_TEST(node1 == mockedElement1->getTerminal(1)->getNode());
	BOOST_TEST(node1 == mockedElement2->getTerminal(1)->getNode());
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("CircuitTerminalMethods"))
BOOST_AUTO_TEST_CASE(ConnectedTerminalconnectToSameNode)
{
	auto mockedElement1 = Pamola::createElement<Pamola::UT::MockedElement>(2);

	mockedElement1->getTerminal(0)->connectTo(mockedElement1->getTerminal(1));

	auto node1 = mockedElement1->getTerminal(1)->connectTo(mockedElement1->getTerminal(0));

	BOOST_TEST(node1 != nullptr);
	BOOST_TEST(node1 == mockedElement1->getTerminal(0)->getNode());
	BOOST_TEST(node1 == mockedElement1->getTerminal(1)->getNode());

	auto node2 = mockedElement1->getTerminal(1)->connectTo(node1);

	BOOST_TEST(node2 != nullptr);
	BOOST_TEST(node2 == mockedElement1->getTerminal(0)->getNode());
	BOOST_TEST(node2 == mockedElement1->getTerminal(1)->getNode());
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("CircuitTerminalMethods"))
BOOST_AUTO_TEST_CASE(connectToSelf)
{
	auto mockedElement1 = Pamola::createElement<Pamola::UT::MockedElement>(1);

	auto node1 = mockedElement1->getTerminal(0)->connectTo(mockedElement1->getTerminal(0));

	BOOST_TEST(node1 == nullptr);
	BOOST_TEST(node1 == mockedElement1->getTerminal(0)->getNode());
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("CircuitTerminalMethods"))
BOOST_AUTO_TEST_CASE(connectToConnectedSelf)
{
	auto mockedElement1 = Pamola::createElement<Pamola::UT::MockedElement>(2);

	auto node1 = mockedElement1->getTerminal(0)->connectTo(mockedElement1->getTerminal(1));
	auto node2 = mockedElement1->getTerminal(0)->connectTo(mockedElement1->getTerminal(0));

	BOOST_TEST(node1 != nullptr);
	BOOST_TEST(node1 == node2);
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("CircuitTerminalMethods"))
BOOST_DATA_TEST_CASE(getSetCurrent,
	bdata::make({0.0,2.0,-2.0}) * bdata::make({ 0.0,1e-12,-1e-12}),
	realValue,imagValue)
{
	auto mockedElement1 = Pamola::createElement<Pamola::UT::MockedElement>(1);
	auto terminal = mockedElement1->getTerminal(0);

	BOOST_TEST(terminal->getCurrent().real() == 0.0, 1e-25);
	BOOST_TEST(terminal->getCurrent().imag() == 0.0, 1e-25);

	terminal->setCurrent(std::complex<double>(realValue, imagValue));

	BOOST_TEST(terminal->getCurrent().real() == realValue, 1e-25);
	BOOST_TEST(terminal->getCurrent().imag() == imagValue, 1e-25);
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("CircuitTerminalMethods"))
BOOST_AUTO_TEST_CASE(getVoltage)
{
	auto mockedElement1 = Pamola::createElement<Pamola::UT::MockedElement>(2);

	BOOST_TEST(isnan(mockedElement1->getTerminal(0)->getVoltage().real()));
	BOOST_TEST(isnan(mockedElement1->getTerminal(0)->getVoltage().imag()));

	auto node1 = mockedElement1->getTerminal(0)->connectTo(mockedElement1->getTerminal(1));

	BOOST_TEST(mockedElement1->getTerminal(0)->getVoltage().real() == 0.0, 1e-25);
	BOOST_TEST(mockedElement1->getTerminal(0)->getVoltage().imag() == 0.0, 1e-25);
	
	BOOST_TEST(!isnan(mockedElement1->getTerminal(0)->getVoltage().real()));
	BOOST_TEST(!isnan(mockedElement1->getTerminal(0)->getVoltage().imag()));
}

BOOST_AUTO_TEST_SUITE_END()