#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>
#include <algorithm>
#include "MockedEngine.h"
#include "MockedElement.h"

namespace bdata = boost::unit_test::data;

/*Test Cases*/
BOOST_TEST_DECORATOR(*boost::unit_test::label("CircuitTerminal") *boost::unit_test::description("Testing the Pamola::CircuitTerminal Class"))
BOOST_AUTO_TEST_SUITE(CircuitTerminalTestSuite)

BOOST_TEST_DECORATOR(*boost::unit_test::label("Methods"))
BOOST_AUTO_TEST_CASE(getElement) 
{
	auto mockedElement = Pamola::createElement<Pamola::UT::MockedElement>(1);

	BOOST_TEST(mockedElement == mockedElement->getTerminal(0)->getElement());
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("Methods"))
BOOST_AUTO_TEST_CASE(getNode)
{
	auto mockedElement = Pamola::createElement<Pamola::UT::MockedElement>(2);

	BOOST_TEST(mockedElement->getTerminal(0)->getNode() == nullptr);

	auto node = mockedElement->getTerminal(0)->connectTo(mockedElement->getTerminal(1));

	BOOST_TEST(mockedElement->getTerminal(0)->getNode() == node);
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("Methods"))
BOOST_AUTO_TEST_CASE(connectToDanglingTerminal)
{
	auto mockedElement1 = Pamola::createElement<Pamola::UT::MockedElement>(1);
	auto mockedElement2 = Pamola::createElement<Pamola::UT::MockedElement>(1);

	auto node1 = mockedElement1->getTerminal(0)->connectTo(mockedElement2->getTerminal(0));

	BOOST_TEST(node1 != nullptr);
	BOOST_TEST(node1 == mockedElement1->getTerminal(0)->getNode());
	BOOST_TEST(node1 == mockedElement2->getTerminal(0)->getNode());
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("Methods"))
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

BOOST_TEST_DECORATOR(*boost::unit_test::label("Methods"))
BOOST_AUTO_TEST_CASE(connectedTerminalconnectTo)
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

BOOST_TEST_DECORATOR(*boost::unit_test::label("Methods"))
BOOST_AUTO_TEST_CASE(connectedTerminalconnectToConnectedTerminal)
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

BOOST_TEST_DECORATOR(*boost::unit_test::label("Methods"))
BOOST_AUTO_TEST_CASE(connectedTerminalconnectToConnectedNode)
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

BOOST_TEST_DECORATOR(*boost::unit_test::label("Methods"))
BOOST_AUTO_TEST_CASE(connectedTerminalconnectToSameNode)
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

BOOST_TEST_DECORATOR(*boost::unit_test::label("Methods"))
BOOST_AUTO_TEST_CASE(connectToSelf)
{
	auto mockedElement1 = Pamola::createElement<Pamola::UT::MockedElement>(1);

	auto node1 = mockedElement1->getTerminal(0)->connectTo(mockedElement1->getTerminal(0));

	BOOST_TEST(node1 == nullptr);
	BOOST_TEST(node1 == mockedElement1->getTerminal(0)->getNode());
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("Methods"))
BOOST_AUTO_TEST_CASE(connectToConnectedSelf)
{
	auto mockedElement1 = Pamola::createElement<Pamola::UT::MockedElement>(2);

	auto node1 = mockedElement1->getTerminal(0)->connectTo(mockedElement1->getTerminal(1));
	auto node2 = mockedElement1->getTerminal(0)->connectTo(mockedElement1->getTerminal(0));

	BOOST_TEST(node1 != nullptr);
	BOOST_TEST(node1 == node2);
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("Methods"))
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

BOOST_TEST_DECORATOR(*boost::unit_test::label("Methods"))
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

BOOST_TEST_DECORATOR(*boost::unit_test::label("Methods"))
BOOST_AUTO_TEST_CASE(disconnectDisconnected)
{
	auto mockedElement1 = Pamola::createElement<Pamola::UT::MockedElement>(2);

	BOOST_TEST(!mockedElement1->getTerminal(0)->disconnect());
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("Methods"))
BOOST_AUTO_TEST_CASE(disconnectFromTerminal)
{
	auto mockedElement1 = Pamola::createElement<Pamola::UT::MockedElement>(2);
	mockedElement1->getTerminal(0)->connectTo(mockedElement1->getTerminal(1));

	BOOST_TEST(mockedElement1->getTerminal(0)->disconnect());
	BOOST_TEST(mockedElement1->getTerminal(0)->getNode() == nullptr);
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("Methods"))
BOOST_AUTO_TEST_CASE(disconnectFromNode)
{
	auto mockedElement1 = Pamola::createElement<Pamola::UT::MockedElement>(3);
	auto node = mockedElement1->getTerminal(0)->connectTo(mockedElement1->getTerminal(1));
	mockedElement1->getTerminal(0)->connectTo(mockedElement1->getTerminal(2));

	BOOST_TEST(mockedElement1->getTerminal(0)->disconnect());
	BOOST_TEST(node != nullptr);
	
	auto terminals = node->getTerminals();
	BOOST_TEST(terminals.size() == 2);
	BOOST_TEST((std::find(terminals.begin(), terminals.end(), mockedElement1->getTerminal(0)) == terminals.end()));
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("LifetimeManagement"))
BOOST_AUTO_TEST_CASE(disconnectByDescruction)
{
	auto mockedElement1 = Pamola::createElement<Pamola::UT::MockedElement>(1);
	
	{
		auto mockedElement2 = Pamola::createElement<Pamola::UT::MockedElement>(1);
		mockedElement1->getTerminal(0)->connectTo(mockedElement2->getTerminal(0));
	}

	BOOST_TEST(mockedElement1->getTerminal(0)->getNode() == nullptr);
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("Methods"))
BOOST_AUTO_TEST_CASE(isConnected)
{
	auto mockedElement1 = Pamola::createElement<Pamola::UT::MockedElement>(2);
	auto terminal = mockedElement1->getTerminal(0);
	
	BOOST_TEST(!terminal->isConnected());

	terminal->connectTo(mockedElement1->getTerminal(1));

	BOOST_TEST(terminal->isConnected());
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("Methods"))
BOOST_AUTO_TEST_CASE(getVariables)
{
	auto mockedElement1 = Pamola::createElement<Pamola::UT::MockedElement>(1);
	auto terminalVariables = mockedElement1->getTerminal(0)->getVariables();

	BOOST_TEST(terminalVariables.at(0).second().real() == mockedElement1->getTerminal(0)->getCurrent().real(), 1e-25);
	BOOST_TEST(terminalVariables.at(0).second().imag() == mockedElement1->getTerminal(0)->getCurrent().imag(), 1e-25);

	terminalVariables.at(0).first(std::complex<double>(2.0, 4.0));

	BOOST_TEST(mockedElement1->getTerminal(0)->getCurrent().real() == 2.0, 1e-25);
	BOOST_TEST(mockedElement1->getTerminal(0)->getCurrent().imag() == 4.0, 1e-25);
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("Methods"))
BOOST_AUTO_TEST_CASE(getAdjacentComponents)
{
	auto mockedElement1 = Pamola::createElement<Pamola::UT::MockedElement>(2);
	auto terminal = mockedElement1->getTerminal(0);
	auto adjacentComponents1 = terminal->getAdjacentComponents();

	BOOST_TEST(adjacentComponents1.size() == 1);
	BOOST_TEST((adjacentComponents1.find(mockedElement1->getId()) != adjacentComponents1.end()));

	auto node = terminal->connectTo(mockedElement1->getTerminal(1));

	auto adjacentComponents2 = terminal->getAdjacentComponents();

	BOOST_TEST(adjacentComponents2.size() == 2);
	BOOST_TEST((adjacentComponents2.find(mockedElement1->getId()) != adjacentComponents2.end()));
	BOOST_TEST((adjacentComponents2.find(node->getId()) != adjacentComponents2.end()));
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("Methods"))
BOOST_AUTO_TEST_CASE(getPamolaType)
{
	auto mockedElement1 = Pamola::createElement<Pamola::UT::MockedElement>(1);
	auto terminal = mockedElement1->getTerminal(0);

	BOOST_TEST(int(terminal->getPamolaType()) == int(Pamola::Type::CircuitTerminal));
}

BOOST_AUTO_TEST_SUITE_END()