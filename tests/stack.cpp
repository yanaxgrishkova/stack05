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

TEST_CASE("pop") 
{
    stack<int> s1;
    s1.push(5);
    s1.push(7);
    s1.push(9);
    s1.pop();
    REQUIRE(s1.count() == 2);
}
