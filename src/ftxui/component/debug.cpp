#include <algorithm>   // for max, min
#include <functional>  // for function
#include <memory>      // for shared_ptr, allocator
#include <string>      // for wstring, basic_string
#include <utility>     // for move

#include "ftxui/component/captured_mouse.hpp"     // for CapturedMouse
#include "ftxui/component/component.hpp"          // for Make, Input
#include "ftxui/component/component_base.hpp"     // for ComponentBase
#include "ftxui/component/component_options.hpp"  // for InputOption
#include "ftxui/component/event.hpp"  // for Event, Event::ArrowLeft, Event::ArrowRight, Event::Backspace, Event::Custom, Event::Delete, Event::End, Event::Home, Event::Return
#include "ftxui/component/mouse.hpp"  // for Mouse, Mouse::Left, Mouse::Pressed
#include "ftxui/component/screen_interactive.hpp"  // for Component
#include "ftxui/dom/elements.hpp"  // for operator|, Element, text, reflect, dim, flex, focus, inverted, hbox, size, frame, select, underlined, Decorator, EQUAL, HEIGHT
#include "ftxui/screen/box.hpp"    // for Box
#include "ftxui/util/ref.hpp"      // for StringRef, Ref, ConstStringRef

namespace ftxui {

// An input box. The user can type text into it.
class DebugBase : public ComponentBase {
 public:
  DebugBase(ConstStringRef placeholder) : placeholder_(placeholder) {}

  // Component implementation:
  Element Render() override {
    return text(*placeholder_ + to_wstring(debugText.str()));
  }

 private:
  ConstStringRef placeholder_;
};

Component operator<<(Component deb, std::string whatev) {
  *deb.get() << whatev;
  return deb;
}

Component Debug(ConstStringRef placeholder) {
  return Make<DebugBase>(placeholder);
}

}  // namespace ftxui

// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.
