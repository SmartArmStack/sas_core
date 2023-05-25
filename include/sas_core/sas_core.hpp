/*
# Copyright (c) 2022-2023 Murilo Marques Marinho
#
#    This file is part of sas_core.
#
#    sas_core is free software: you can redistribute it and/or modify
#    it under the terms of the GNU Lesser General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    sas_core is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU Lesser General Public License for more details.
#
#    You should have received a copy of the GNU Lesser General Public License
#    along with sas_core.  If not, see <https://www.gnu.org/licenses/>.
#
# ################################################################
#
#   Author: Murilo M. Marinho, email: murilomarinho@ieee.org
#
# ################################################################*/
#pragma once

#include <eigen3/Eigen/Dense>

using namespace Eigen;

namespace sas
{

enum class Statistics{
    Mean
};

template<class T>
/**
 * @brief incremental_mean a simple implementation of incremental mean, for the many cases in which
 * keeping a vector of all values would be impractical.
 * @param current_mean the current value of the mean.
 * @param current_number_of_samples the current number of samples, not considering the new_sample.
 * @param new_sample the new sample that will change the mean.
 * @return the incremental mean, considering the new_sample.
 */
constexpr T incremental_mean(const T &current_mean, const int &current_number_of_samples, const T &new_sample)
{
    if(current_number_of_samples<0)
        throw std::range_error("incremental_mean::current_number_of_samples should be larger than 0");
    return (current_mean * current_number_of_samples + new_sample)/(current_number_of_samples+1);
}

VectorXd concatenate(const VectorXd& a, const VectorXd& b);
VectorXd concatenate(const std::vector<VectorXd>& as);

MatrixXd vstack(const MatrixXd& A, const MatrixXd& B);

MatrixXd block_diag(const std::vector<MatrixXd>& As);

std::vector<VectorXd> split(const VectorXd& a, const std::vector<int>& ns);

}
