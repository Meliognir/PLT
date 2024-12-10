#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"
#include "../../src/shared/engine.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestStaticAssert) {
    BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestPlayer) {
    {
        Player player(12,"Coucou");
        BOOST_CHECK_EQUAL(player.getPlayerId(), 12);
    }
}


/* vim: set sw=2 sts=2 et : */
