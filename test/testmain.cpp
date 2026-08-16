#include <catch2/catch_session.hpp>

#include <Python.h>

int main(int argc, char* argv[])
{
    Py_Initialize();
    int result = Catch::Session().run(argc, argv);
    Py_Finalize();
    return result;
}
