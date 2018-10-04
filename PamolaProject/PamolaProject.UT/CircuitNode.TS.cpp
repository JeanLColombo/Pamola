#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>
#include "MockedElement.h"

namespace bdata = boost::unit_test::data;

/*Test Functions and Classes*/
namespace Pamola
{
	namespace UT
	{
		namespace CircuitNodeTS
		{
			class CircuitNodeTestClass
			{
			public:

				void checkTerminalsInNode(std::shared_ptr<CircuitNode> node, std::vector<std::shared_ptr<CircuitTerminal>> terminals)
				{
					BOOST_TEST(areInNode(node, terminals));
				}

				void checkTerminalsNotInNode(std::shared_ptr<CircuitNode> node, std::vector<std::shared_ptr<CircuitTerminal>> terminals)
				{
					BOOST_TEST(!areInNode(node, terminals));
				}

			private:

				bool areInNode(std::shared_ptr<CircuitNode> node, std::vector<std::shared_ptr<CircuitTerminal>> terminals)
				{
					auto nodeTerminals = node->getTerminals();

					for (auto &terminal : terminals)
						if ((std::find(nodeTerminals.begin(), nodeTerminals.end(), terminal) == nodeTerminals.end()))
							return false;

					return true;
				}


			};

		}
	}
}

/*Test Cases*/
BOOST_TEST_DECORATOR(*boost::unit_test::label("CircuitNode") 
	*boost::unit_test::description("Testing the Pamola::CircuitNode Class") 
	*boost::unit_test::tolerance(1e-100))
BOOST_AUTO_TEST_SUITE(CircuitNodeTestSuite)

BOOST_TEST_DECORATOR(*boost::unit_test::label("Methods"))
BOOST_AUTO_TEST_CASE(connectToNode)
{
	auto mockedElement1 = Pamola::createElement<Pamola::UT::MockedElement, int>(2);
	auto mockedElement2 = Pamola::createElement<Pamola::UT::MockedElement, int>(2);

	std::weak_ptr<Pamola::CircuitNode> node1 = mockedElement1->getTerminal(0)->connectTo(mockedElement2->getTerminal(0));
	std::weak_ptr<Pamola::CircuitNode> node2 = mockedElement1->getTerminal(1)->connectTo(mockedElement2->getTerminal(1));

	node1.lock()->connectTo(node2.lock());

	BOOST_TEST(node1.lock() != nullptr);
	BOOST_TEST(node2.lock() == nullptr);

	BOOST_TEST(node1.lock()->getTerminals().size() == 4);
	
	Pamola::UT::CircuitNodeTS::CircuitNodeTestClass().checkTerminalsInNode(node1.lock(), mockedElement1->getTerminals());
	Pamola::UT::CircuitNodeTS::CircuitNodeTestClass().checkTerminalsInNode(node1.lock(), mockedElement2->getTerminals());
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("Methods"))
BOOST_AUTO_TEST_CASE(connectToSelfNode)
{
	auto mockedElement = Pamola::createElement<Pamola::UT::MockedElement, int>(2);
	auto terminal1 = mockedElement->getTerminal(0);
	auto terminal2 = mockedElement->getTerminal(1);

	terminal1->connectTo(terminal2);

	auto node1 = terminal1->getNode();
	auto node2 = terminal2->getNode();

	BOOST_TEST(node1 == node1->connectTo(node2));
	BOOST_TEST(node1 == node2->connectTo(node1));

	Pamola::UT::CircuitNodeTS::CircuitNodeTestClass().checkTerminalsInNode(node1, mockedElement->getTerminals());
	Pamola::UT::CircuitNodeTS::CircuitNodeTestClass().checkTerminalsInNode(node2, mockedElement->getTerminals());
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("Methods"))
BOOST_AUTO_TEST_CASE(getTerminals)
{
	auto mockedElement1 = Pamola::createElement<Pamola::UT::MockedElement, int>(2);
	auto mockedElement2 = Pamola::createElement<Pamola::UT::MockedElement, int>(1);

	auto node1 = mockedElement1->getTerminal(0)->connectTo(mockedElement1->getTerminal(1));

	BOOST_TEST(node1->getTerminals().size() == 2);
	Pamola::UT::CircuitNodeTS::CircuitNodeTestClass().checkTerminalsInNode(node1, mockedElement1->getTerminals());

	mockedElement2->getTerminal(0)->connectTo(node1);

	BOOST_TEST(node1->getTerminals().size() == 3);
	Pamola::UT::CircuitNodeTS::CircuitNodeTestClass().checkTerminalsInNode(node1, mockedElement2->getTerminals());

	mockedElement2->getTerminal(0)->disconnect();

	BOOST_TEST(node1->getTerminals().size() == 2);
	Pamola::UT::CircuitNodeTS::CircuitNodeTestClass().checkTerminalsNotInNode(node1, mockedElement2->getTerminals());
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("Methods"))
BOOST_DATA_TEST_CASE(getSetVoltage,
	bdata::make({ 0.0,2.0,-2.0 }) * bdata::make({ 0.0,1e-12,-1e-12 }),
	realValue, imagValue)
{
	auto mockedElement1 = Pamola::createElement<Pamola::UT::MockedElement, int>(2);

	auto node1 = mockedElement1->getTerminal(0)->connectTo(mockedElement1->getTerminal(1));

	BOOST_TEST(node1->getVoltage().real() == 0.0);
	BOOST_TEST(node1->getVoltage().imag() == 0.0);

	node1->setVoltage(std::complex<double>(realValue, imagValue));

	BOOST_TEST(node1->getVoltage().real() == realValue);
	BOOST_TEST(node1->getVoltage().imag() == imagValue);

}

BOOST_TEST_DECORATOR(*boost::unit_test::label("Methods"))
BOOST_DATA_TEST_CASE(getEquations,
	bdata::make({ 0.0,3.0,15.0,-12.2}) ^ bdata::make({ 0.0,-3.0,5.0,-7.7}) ^ bdata::make({ 0.0,0.0,20.0,-19.9 }),
	current1,current2,sumOfCurrents)
{
	auto mockedElement1 = Pamola::createElement<Pamola::UT::MockedElement, int>(2);

	auto equations = (mockedElement1->getTerminal(0)->connectTo(mockedElement1->getTerminal(1)))->getEquations();

	mockedElement1->getTerminal(0)->setCurrent(std::complex<double>(current1, current2));
	mockedElement1->getTerminal(1)->setCurrent(std::complex<double>(current2, current1));

	BOOST_TEST(equations.at(0)().real() == sumOfCurrents);
	BOOST_TEST(equations.at(0)().imag() == sumOfCurrents);
}

BOOST_AUTO_TEST_SUITE_END()