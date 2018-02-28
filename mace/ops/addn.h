//
// Copyright (c) 2017 XiaoMi All rights reserved.
//

#ifndef MACE_OPS_ADDN_H_
#define MACE_OPS_ADDN_H_

#include <vector>

#include "mace/core/operator.h"
#include "mace/kernels/addn.h"

namespace mace {

template <DeviceType D, class T>
class AddNOp : public Operator<D, T> {
 public:
  AddNOp(const OperatorDef &operator_def, Workspace *ws)
      : Operator<D, T>(operator_def, ws) {}

  bool Run(StatsFuture *future) override {
    Tensor *output_tensor = this->Output(0);
    int n = this->inputs_.size();
    std::vector<const Tensor *> inputs(n, nullptr);
    inputs[0] = this->Input(0);
    for (int i = 1; i < n; ++i) {
      inputs[i] = this->Input(i);
      MACE_CHECK(inputs[0]->dim_size() == inputs[i]->dim_size());
      MACE_CHECK(inputs[0]->size() == inputs[i]->size());
    }

    functor_(inputs, output_tensor, future);
    return true;
  }

 private:
  kernels::AddNFunctor<D, T> functor_;
};

}  // namespace mace

#endif  // MACE_OPS_ADDN_H_
