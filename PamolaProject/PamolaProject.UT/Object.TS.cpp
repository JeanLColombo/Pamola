#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "MockedObject.h"
#include "MockedElement.h"

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
}

BOOST_AUTO_TEST_SUITE_END()