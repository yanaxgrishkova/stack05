#include <catch.hpp>

#include "stack.hpp"

TEST_CASE("push", "") {
    stack<int> s1;
    s1.push(1);
    s1.push(2);
    s1.push(3);
    s1.push(4);
    s1.push(5);
    REQUIRE(s1.count() == 5);
}

TEST_CASE("try_pop", "") {
    stack<int> s1;
    s1.push(1);
    s1.push(2);
    s1.push(3);
    s1.push(4);
    s1.push(5);
    REQUIRE(s1.count() == 5);
    s1.try_pop();
    REQUIRE(s1.count() == 4);
    s1.try_pop();
    REQUIRE(s1.count() == 3);
    s1.try_pop();
    REQUIRE(s1.count() == 2);
}

TEST_CASE("wait_and_pop", "") {
    stack<int> s1;
    s1.push(1);
    s1.push(2);
    s1.push(3);
    s1.push(4);
    s1.push(5);
    REQUIRE(s1.count() == 5);
    s1.wait_and_pop();
    REQUIRE(s1.count() == 4);
    s1.wait_and_pop();
    REQUIRE(s1.count() == 3);
    s1.wait_and_pop();
    REQUIRE(s1.count() == 2);
}

