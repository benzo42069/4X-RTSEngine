#include <doctest/doctest.h>
#include "company/engine/Expression.hpp"

TEST_CASE("expression engine evaluates arithmetic and bool") {
    using namespace company::engine;
    Context ctx{{"population", 5}, {"threshold", 3}};
    nlohmann::json expr = { {"op", "gt"}, {"args", {{{"op", "add"}, {"args", {"population", 2}}}, "threshold"}} };
    CHECK(EvalBool(expr, ctx));
}
