#include "PyConnext.hpp"
#include <pybind11/functional.h>
#include <dds/sub/cond/ReadCondition.hpp>
#include <dds/sub/cond/QueryCondition.hpp>
#include "PyCondition.hpp"
#include "PyAnyDataReader.hpp"

namespace pyrti {

template<>
void init_class_defs(py::class_<PyReadCondition, PyIReadCondition>& cls) {
    cls
        .def(
            py::init([](PyIAnyDataReader& adr, const dds::sub::status::DataState& ds) {
                return PyReadCondition(rti::sub::cond::create_read_condition_ex(adr.get_any_datareader(), ds));
            }),
            py::arg("reader"),
            py::arg("status"),
            "Create a ReadCondition."
        )
        .def(
            py::init(
                [](PyIAnyDataReader& dr, const dds::sub::status::DataState& ds, std::function<void()>& func) {
                    return PyReadCondition(
                        rti::sub::cond::create_read_condition_ex(
                            dr.get_any_datareader(), 
                            ds,
                            func
                        )
                    );
                }
            ),
            py::arg("reader"),
            py::arg("status"),
            py::arg("handler"),
            "Create a ReadCondition."
        )
        .def(
            py::init(
                [](PyIAnyDataReader& dr, const rti::sub::status::DataStateEx& ds) {
                    return PyReadCondition(
                        rti::sub::cond::create_read_condition_ex(
                            dr.get_any_datareader(), 
                            ds
                        )
                    );
                }
            ),
            py::arg("reader"),
            py::arg("status"),
            "Create a ReadCondition."
        )
        .def(
            py::init(
                [](PyIAnyDataReader& dr, const rti::sub::status::DataStateEx& ds, std::function<void()>& func) {
                    return PyReadCondition(
                        rti::sub::cond::create_read_condition_ex(
                            dr.get_any_datareader(), 
                            ds,
                            func
                        )
                    );
                }
            ),
            py::arg("reader"),
            py::arg("status"),
            py::arg("handler"),
            "Create a ReadCondition."
        )
        .def(
            py::init(
                [](PyICondition& py_c) {
                    auto c = py_c.get_condition();
                    return PyReadCondition(dds::core::polymorphic_cast<dds::sub::cond::ReadCondition>(c));
                }
            ),
            "Cast a compatible Condition to a ReadCondition."
        );
}

template<>
void init_class_defs(py::class_<PyIReadCondition, PyICondition>& cls) {
    cls
        .def_property_readonly(
            "state_filter",
            &PyIReadCondition::py_state_filter,
            "Returns the DataState of this condition."
        )
        .def_property_readonly(
            "data_reader",
            &PyIReadCondition::py_data_reader,
            "Returns the DataReader associated to this condition."
        )
        .def(
            "close",
            &PyIReadCondition::py_close,
            "Returns the DataReader associated to this condition."
        )
        .def_property_readonly(
            "closed",
            &PyIReadCondition::py_closed,
            "Returns the DataReader associated to this condition."
        )
        .def(
            "__enter__",
            [](PyIReadCondition& rc) -> PyIReadCondition& {
                return rc;
            }
        )
        .def(
            "__exit__",
            [](PyIReadCondition& rc) {
                rc.py_close();
            }
        )
        .def(
            "__eq__",
            [](PyIReadCondition& rc, PyIReadCondition& other) {
                return rc.get_read_condition() == other.get_read_condition();
            },
            py::is_operator(),
            "Test for equality."
        )
        .def(
            "__ne__",
            [](PyIReadCondition& rc, PyIReadCondition& other) {
                return rc.get_read_condition() != other.get_read_condition();
            },
            py::is_operator(),
            "Test for inequality."
        );
}

template<>
void process_inits<dds::sub::cond::ReadCondition>(py::module& m, ClassInitList& l) {
    l.push_back(
        [m]() mutable {
            return init_class<PyIReadCondition, PyICondition>(m, "IReadCondition");
        }
    );

    l.push_back(
        [m]() mutable {
            return init_class<PyReadCondition, PyIReadCondition>(m, "ReadCondition");
        }
    );
}

}
