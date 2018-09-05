#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "ObjectHolder.h"

BOOST_TEST_DECORATOR(*boost::unit_test::label("Object") *boost::unit_test::description("Testing the Pamola::Object Class"))
BOOST_AUTO_TEST_SUITE(ObjectTestSuite)

BOOST_TEST_DECORATOR(*boost::unit_test::label("LifetimeManagement"))
BOOST_AUTO_TEST_CASE(RawObjectCreationDestruction)
{
	Pamola::ObjectHolder *obj = new Pamola::ObjectHolder;
	delete obj;
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("LifetimeManagement"))
BOOST_AUTO_TEST_CASE(ScopedObjectCreationDestruction)
{
	Pamola::ObjectHolder obj{};
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("ObjectMethods"))
BOOST_AUTO_TEST_CASE(ObjectGetCircuit)
{
	Pamola::ObjectHolder obj{};
	auto cir = obj.getCircuit();
	BOOST_TEST(cir == nullptr);
}

BOOST_AUTO_TEST_SUITE_END()