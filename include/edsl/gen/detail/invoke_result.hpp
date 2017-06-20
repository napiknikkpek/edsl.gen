#ifndef _6BC3FFD7_D7CE_4950_AF3C_8F3ADB65AE0E_HPP
#define _6BC3FFD7_D7CE_4950_AF3C_8F3ADB65AE0E_HPP

#include <utility>

namespace edsl::gen::detail {

template <typename F, typename... Args>
struct invoke_result {
  using type = decltype(std::declval<F&&>()(std::declval<Args&&>()...));
};

template <typename F, typename... Args>
using invoke_result_t = typename invoke_result<F, Args...>::type;
}
#endif
