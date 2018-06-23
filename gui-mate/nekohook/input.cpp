
#include "functional.hpp"

#include "input.hpp"

namespace input {

cat::Event<std::pair<int, int>> bounds_event;
cat::Event<std::pair<int, int>> mouse_event;
cat::Event<CatKey, bool> key_event;

}
