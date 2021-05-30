#include <Python.h>
#include <pybind11/embed.h>

#include <pybind11/pybind11.h>
#include <iostream>

//pybind11::scoped_interpreter guard{};
//
//auto sys = pybind11::module::import("sys");
//pybind11::print(sys.attr("path"));

//
//    BUILD THIS PROJESC IN RELEASE CONFIGURATION !!!!!!!!!
//

void arka()
{
	std::cout << "ARKA GDYNIA KURWA SWINIA!" << std::endl;
}

void check_dll()
{
	std::cout << "DLL dziala!" << std::endl;
}

int add(int a, int b)
{
	return a + b;
}

PYBIND11_MODULE(pybind_test, m) 
{
	m.doc() = "pybind11 example plugin";

	m.def("arka", &arka);
	m.def("check_dll", &check_dll);
	m.def("add", &add);
}