#pragma once
/*
# Copyright (c) 2016-2020 Murilo Marques Marinho
#
#    This file is part of sas_conversions.
#
#    sas_conversions is free software: you can redistribute it and/or modify
#    it under the terms of the GNU Lesser General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    sas_conversions is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU Lesser General Public License for more details.
#
#    You should have received a copy of the GNU Lesser General Public License
#    along with sas_conversions.  If not, see <https://www.gnu.org/licenses/>.
#
# ################################################################
#
#   Author: Murilo M. Marinho, email: murilomarinho@ieee.org
#
# ################################################################*/

/**
 * @file sas_conversions.hpp
 * @brief Aggregated include header for conversion helpers.
 *
 * This header re-exports conversion helpers between DQ/Eigen and ROS
 * message types so other modules can include a single header to obtain all
 * conversion utilities.
 */
#include<sas_conversions/DQ_geometry_msgs_conversions.h>
#include<sas_conversions/std_std_msgs_conversions.h>
#include<sas_conversions/eigen3_std_conversions.h>

