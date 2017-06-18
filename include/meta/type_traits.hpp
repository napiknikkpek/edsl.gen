#ifndef _709C2BBD_DCDB_4795_80DC_160C318677D7_HPP
#define _709C2BBD_DCDB_4795_80DC_160C318677D7_HPP

#include <utility>

namespace meta {

template <typename F, typename... Args>
using invoke_result_t =
    decltype(std::declval<F&&>()(std::declval<Args&&>()...));
}

#endif
