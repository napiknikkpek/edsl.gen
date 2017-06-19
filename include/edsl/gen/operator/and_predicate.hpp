#ifndef _0D70DED7_D0BA_460D_A2FB_F6B1C9939B38_HPP
#define _0D70DED7_D0BA_460D_A2FB_F6B1C9939B38_HPP

#include <utility>

#include "edsl/gen/operand.hpp"

namespace edsl::gen {

template <typename T, typename Size>
auto operator&(operand<T, Size> subject) {
  return op(boost::hana::int_<Size::value + 1>{},
            [subject](auto /*sink*/, auto&&... args) {
              return invoke(subject, std::forward<decltype(args)>(args)...);
            });
}
}

#endif
