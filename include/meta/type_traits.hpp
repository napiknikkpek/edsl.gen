#ifndef _2AD6964F_CB4D_4D5F_80B3_D1213AC396C0_HPP
#define _2AD6964F_CB4D_4D5F_80B3_D1213AC396C0_HPP

#include <utility>

namespace meta {
template <typename F, typename... Args>
using invoke_result_t =
    decltype(std::declval<F&&>()(std::declval<Args&&>()...));
}
#endif
