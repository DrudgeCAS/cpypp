/** Tests for the utilities to related numeric objects.
 */

#include <catch2/catch_test_macros.hpp>

#include <Python.h>

#include <cpypp.hpp>

using namespace cpypp;

// Small integers are immortal from Python 3.12 on, and the reference count of
// an immortal object does not move.  Their count is only checked when it can.
static bool count_moves(PyObject* obj)
{
    return Py_REFCNT(obj) < (static_cast<Py_ssize_t>(1) << 30);
}

TEST_CASE("Integer can be built and parsed", "[Handle]")
{

    // Here we use simple integer of unity again, with the Python singleton
    // handling of it.

    PyObject* one = PyLong_FromLong(1);
    Py_ssize_t curr_count = Py_REFCNT(one);

    auto check_build_int = [&](auto v) {
        {
            Handle from_gen(v);
            CHECK(from_gen.get() == one);
            if (count_moves(one)) {
                CHECK(Py_REFCNT(one) == curr_count + 1);
            }

            long val;
            from_gen.as(val);
            CHECK(val == 1);
            CHECK(from_gen.as<decltype(v)>() == 1);
        }
        CHECK(Py_REFCNT(one) == curr_count);
    };

    SECTION("long") { check_build_int(1l); }

    SECTION("unsigned long") { check_build_int(1ul); }

    Py_DECREF(one);
}
