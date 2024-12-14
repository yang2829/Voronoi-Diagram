#include "define.hpp"
#include "Arc.hpp"
#include "Beachline.hpp"
#include "Event.hpp"
#include "Fortune.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_MODULE(_fortune, m) {
    py::class_<Site>(m, "Site")
        .def(py::init<size_t, std::pair<double, double>>())
        .def_readonly("index", &Site::index)
        .def_readonly("point", &Site::point);

    py::class_<Edge>(m, "Edge")
        .def(py::init<std::pair<double, double>, std::pair<double, double>, std::pair<double, double>>())
        .def_readonly("s", &Edge::s)
        .def_readonly("d", &Edge::d)
        .def_readonly("v", &Edge::v)
        .def_readonly("s_finish", &Edge::s_finish)
        .def_readonly("d_finish", &Edge::d_finish);

    py::class_<Arc>(m, "Arc")
        .def(py::init<Arc*, Arc*, Site*, size_t, size_t, Arc::Color, Arc*>())
        .def(py::init<Site*, Arc::Color, Arc*>());

    py::class_<Beachline>(m, "Beachline")
        .def(py::init<>());

    py::class_<Event>(m, "Event")
        .def(py::init<Site*, double>())
        .def(py::init<double, std::pair<double, double>, Arc*>());

    py::class_<Fortune>(m, "Fortune")
        .def(py::init<size_t, size_t, size_t, int>(),pybind11::arg("n") = 8 , pybind11::arg("w") = 500, pybind11::arg("h") = 500, pybind11::arg("seed") = 1512)
        .def(py::init<std::vector<std::pair<double, double>>, size_t, size_t>())
        .def("RunAlgo", &Fortune::RunAlgo)
        .def("completeEdge", &Fortune::completeEdge)
        .def("npoints", &Fortune::npoints)
        .def("getw", &Fortune::getw)
        .def("geth", &Fortune::geth)
        .def("get_points", &Fortune::get_points)
        .def("get_edges", &Fortune::get_edges)
        .def_readwrite("info_out", &Fortune::info_out);
}