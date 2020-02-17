#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/Rect.h"

TEST_CASE("Test Rect", "[rect]") {
    Rect rect(1.0, 2.0, 3.0, 4.0);

    REQUIRE(rect.X() == 1.0);
    REQUIRE(rect.Y() == 2.0);
    REQUIRE(rect.Width() == 3.0);
    REQUIRE(rect.Height() == 4.0);

    SECTION("test overlapping") {
        SECTION("with non overlapping rects") {
            Rect a(0,0, 2, 2);
            Rect b(2, 2, 2, 2);
            REQUIRE(!a.Overlap(b));
        }

        SECTION("with rects overlapping by a corner") {
            Rect a(0,0, 2, 2);
            Rect b(1, 1, 2, 2);
            REQUIRE(a.Overlap(b));
        }

        SECTION("with rects overlapping by a side") {
            Rect a(0,0, 2, 2);
            Rect b(-1, -1, 4, 4);
            REQUIRE(a.Overlap(b));
        }

        SECTION("with the same rect") {
            Rect a(0,0, 2, 2);
            REQUIRE(a.Overlap(a));
        }
    }
}
