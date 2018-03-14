/**********************************************************************************************************************
This file is part of the Control Toolbox (https://adrlab.bitbucket.io/ct), copyright by ETH Zurich, Google Inc.
Authors:  Michael Neunert, Markus Giftthaler, Markus Stäuble, Diego Pardo, Farbod Farshidian
Licensed under Apache2 license (see LICENSE file in main directory)
**********************************************************************************************************************/

#pragma once

#include "EstimatorBase.h"
#include "LinearMeasurementModel.h"

namespace ct {
namespace optcon {

template <size_t STATE_DIM, typename SCALAR>
struct SteadyStateKalmanFilterSettings;

template <size_t STATE_DIM, typename SCALAR = double>
class SteadyStateKalmanFilter : public EstimatorBase<STATE_DIM, SCALAR>
{
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    static const size_t STATE_D = STATE_DIM;
    using Base                  = EstimatorBase<STATE_DIM, SCALAR>;
    using typename Base::state_vector_t;

    SteadyStateKalmanFilter(const state_vector_t& x0 = state_vector_t::Zero(), size_t maxDAREIterations = 1000);

    SteadyStateKalmanFilter(const SteadyStateKalmanFilterSettings<STATE_DIM, SCALAR>& sskf_settings);

    template <size_t CONTROL_DIM>
    const state_vector_t& predict(SystemModelBase<STATE_DIM, CONTROL_DIM, SCALAR>& f,
        const ct::core::ControlVector<CONTROL_DIM, SCALAR>& u,
        const ct::core::StateMatrix<STATE_DIM, SCALAR>& Q,
        const ct::core::Time& t = 0);

    template <size_t OUTPUT_DIM>
    const state_vector_t& update(const ct::core::OutputVector<OUTPUT_DIM, SCALAR>& y,
        LinearMeasurementModel<OUTPUT_DIM, STATE_DIM, SCALAR>& h,
        const ct::core::OutputMatrix<OUTPUT_DIM, SCALAR>& R,
        const ct::core::Time& t = 0);

    void setMaxDAREIterations(size_t maxDAREIterations);

private:
    size_t maxDAREIterations_;
    ct::core::StateMatrix<STATE_DIM, SCALAR> P_;
    ct::core::StateMatrix<STATE_DIM, SCALAR> A_;
    ct::core::StateMatrix<STATE_DIM, SCALAR> Q_;
};

}  // optcon
}  // ct
