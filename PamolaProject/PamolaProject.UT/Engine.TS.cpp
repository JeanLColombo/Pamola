#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "EngineHolder.h"
#include "ElementHolder.h"

BOOST_TEST_DECORATOR(*boost::unit_test::label("Engine") *boost::unit_test::description("Testing the Pamola::Engine Class"))
BOOST_AUTO_TEST_SUITE(EngineTestSuite)

BOOST_TEST_DECORATOR(*boost::unit_test::label("LifetimeManagement"))
BOOST_AUTO_TEST_CASE(StaticEngineCreation)
{
	BOOST_TEST(Pamola::Engine::getLocalEngine() != nullptr);
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("LifetimeManagement"))
BOOST_AUTO_TEST_CASE(RawEngineCreationDestruction)
{
	Pamola::UT::EngineHolder *eng = new Pamola::UT::EngineHolder;
	delete eng;
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("LifetimeManagement"))
BOOST_AUTO_TEST_CASE(ScopedEngineCreationDestruction)
{
	Pamola::UT::EngineHolder eng{};
}

BOOST_TEST_DECORATOR(*boost::unit_test::label("EngineMethods"))
BOOST_AUTO_TEST_CASE(getLocalEngineTest)
{
	auto eng = std::shared_ptr<Pamola::UT::EngineHolder>(new Pamola::UT::EngineHolder());
	BOOST_TEST(Pamola::Engine::getLocalEngine() == eng->getLocalEngine());
}

BOOST_AUTO_TEST_SUITE_END()