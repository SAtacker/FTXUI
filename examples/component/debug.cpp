#include <stdlib.h>  // for EXIT_SUCCESS
#include <memory>    // for __shared_ptr_access
#include <string>  // for wstring, allocator, operator+, basic_string, char_traits
#include <vector>  // for vector, __alloc_traits<>::value_type

#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"  // for Menu, Renderer, Horizontal, Vertical
#include "ftxui/component/component_base.hpp"  // for ComponentBase
#include "ftxui/component/screen_interactive.hpp"  // for Component, ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for text, Element, operator|, window, flex, vbox
#include "ftxui/screen/string.hpp"  // for to_wstring

using namespace ftxui;

int main(int argc, const char* argv[]) {
  auto debug = Debug(L"Ohhoy:\n");

  debug << "Debug it here\n";
  auto screen = ScreenInteractive::TerminalOutput();
  screen.Loop(debug);
  return EXIT_SUCCESS;
}

// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.
