#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "..\PamolaProject\PamolaEngine.h"

BOOST_TEST_DECORATOR(*boost::unit_test::label("Engine") *boost::unit_test::description("Testing the Pamola::Engine Class"))
BOOST_AUTO_TEST_SUITE(EngineTestSuite)

BOOST_TEST_DECORATOR(*boost::unit_test::label("LifetimeManagement"))
BOOST_AUTO_TEST_CASE(StaticEngineCreationDestruction)
{
	BOOST_TEST(Pamola::Engine::getLocalEngine() != nullptr);
}

//BOOST_TEST_DECORATOR(*boost::unit_test::label("LifetimeManagement"))
//BOOST_AUTO_TEST_CASE(ScopedStaticEngineCreationDestruction)
//{
//	Pamola::Engine eng;
//	BOOST_TEST(Pamola::Engine::getLocalEngine() == eng.getLocalEngine());
//}

BOOST_AUTO_TEST_SUITE_END()