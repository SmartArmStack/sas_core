/*
# Copyright (c) 2016-2026 Murilo Marques Marinho
#
#    This file is part of sas_robot_driver.
#
#    sas_robot_driver is free software: you can redistribute it and/or modify
#    it under the terms of the GNU Lesser General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    sas_robot_driver is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU Lesser General Public License for more details.
#
#    You should have received a copy of the GNU Lesser General Public License
#    along with sas_robot_driver.  If not, see <https://www.gnu.org/licenses/>.
#
# ################################################################
#
#   Author: Murilo M. Marinho, email: murilomarinho@ieee.org
#
# #################################################################
# Contributors:
*/

#include "sas_core_py.hpp"
#include <sas_core/sas_robot_driver.hpp>

namespace sas
{

//https://pybind11.readthedocs.io/en/stable/advanced/classes.html
//Trampoline class
class RobotDriverPy: public RobotDriver, public py::trampoline_self_life_support
{
public:
    RobotDriverPy(const std::shared_ptr<ShutdownSignaler>& ss):
    RobotDriver(ss)
    {
    };
    ~RobotDriverPy()=default;

    /* Trampoline (need one for each virtual function) */
    VectorXd get_joint_positions() override
    {
        PYBIND11_OVERRIDE_PURE(
            VectorXd,                  /* Return type */
            RobotDriver,               /* Parent class */
            get_joint_positions,       /* Name of function in C++ (must match Python name) */
                                   /* Argument(s) */
            );
    }
    void set_target_joint_positions(const VectorXd& set_target_joint_positions_rad) override
    {
        PYBIND11_OVERRIDE_PURE(
                void,
                RobotDriver,
                set_target_joint_positions,
                set_target_joint_positions_rad
                );
    }

    VectorXd get_joint_velocities() override
    {
        PYBIND11_OVERRIDE(
            VectorXd,
            RobotDriver,
            get_joint_velocities,
            );
    }

    void set_target_joint_velocities(const VectorXd& set_target_joint_velocities) override
    {
        PYBIND11_OVERRIDE(
        void,
        RobotDriver,
        set_target_joint_velocities,
        set_target_joint_velocities
        );
    }

    VectorXd get_joint_torques() override
    {
        PYBIND11_OVERRIDE(
        VectorXd,
        RobotDriver,
        get_joint_torques,
        );
    }


    void set_target_joint_torques(const VectorXd& set_target_joint_torques) override
    {
        PYBIND11_OVERRIDE(
        void,
        RobotDriver,
        set_target_joint_torques,
        set_target_joint_torques
        );
    }

    //std::tuple<VectorXd, VectorXd> get_joint_limits() override
    //{
    //    PYBIND11_OVERRIDE(
    //    std::tuple<VectorXd, VectorXd>,
    //    RobotDriver,
    //    get_joint_limits,
    //    );
    //}

    void set_joint_limits(const std::tuple<VectorXd, VectorXd>& joint_limits) override
    {
        PYBIND11_OVERRIDE(
        void,
        RobotDriver,
        set_joint_limits,
        joint_limits
        );
    }

    void connect() override
    {
        PYBIND11_OVERRIDE_PURE(
        void,
        RobotDriver,
        connect,
        );
    }

    void disconnect() override
    {
        PYBIND11_OVERRIDE_PURE(
        void,
        RobotDriver,
        disconnect,
        );
    }

    void initialize() override
    {
        PYBIND11_OVERRIDE_PURE(
        void,
        RobotDriver,
        initialize,
        );
    }

    void deinitialize() override
    {
        PYBIND11_OVERRIDE_PURE(
        void,
        RobotDriver,
        deinitialize,
        );
    }
};

void init_sas_robot_driver_py(py::module& m)
{
    py::class_<
            RobotDriver,
            RobotDriverPy,
            py::smart_holder
            > c(m,"RobotDriver");

    c.def(py::init<const std::shared_ptr<ShutdownSignaler>&>());

    c.def("get_joint_positions", &RobotDriver::get_joint_positions, "");
    c.def("set_target_joint_positions", &RobotDriver::set_target_joint_positions, "");

    c.def("get_joint_velocities", &RobotDriver::get_joint_velocities, "");
    c.def("set_target_joint_velocities", &RobotDriver::set_target_joint_velocities, "");

    c.def("get_joint_torques", &RobotDriver::get_joint_torques, "");
    c.def("set_target_joint_torques", &RobotDriver::set_target_joint_torques, "");

    c.def("get_joint_limits", &RobotDriver::get_joint_limits, "");
    c.def("set_joint_limits", &RobotDriver::set_joint_limits, "");

    c.def("watchdog_start", &RobotDriver::watchdog_start, "");
    c.def("watchdog_trigger", &RobotDriver::watchdog_trigger, "");
    c.def("watchdog_set_maximum_acceptable_delay", &RobotDriver::watchdog_set_maximum_acceptable_delay, "");
    c.def("check_for_watchdog_exceptions", &RobotDriver::check_for_watchdog_exceptions, "");

    c.def("connect", &RobotDriver::connect, "");
    c.def("disconnect", &RobotDriver::disconnect, "");

    c.def("initialize", &RobotDriver::initialize, "");
    c.def("deinitialize", &RobotDriver::deinitialize, "");
}

}