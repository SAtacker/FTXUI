#include <stdio.h>
#include <unistd.h>
#include <memory>  // for allocator, __shared_ptr_access
#include <string>  // for operator+, char_traits, wstring

#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"       // for Input, Renderer, Vertical
#include "ftxui/component/component_base.hpp"  // for ComponentBase
#include "ftxui/component/container.hpp"       // for Container
#include "ftxui/component/screen_interactive.hpp"  // for Component, ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for text, hbox, Element, separator, operator|, vbox, border

std::string result;

void pipe_test(std::wstring* command) {
  std::string c(command->begin(), command->end());
  const char* cmd = c.c_str();
  result = "";
  std::array<char, 128> buffer;
  pid_t pid = 0;
  int pipefd[2];
  FILE* output;

  pipe(pipefd);
  pid = fork();
  if (pid == 0) {
    // Redirect its standard output to our pipe and replace process
    // with child
    close(pipefd[0]);
    dup2(pipefd[1], STDOUT_FILENO);
    dup2(pipefd[1], STDERR_FILENO);
    setvbuf(stdout, NULL, _IOLBF, 1000);
    execl("/bin/sh", "sh", "-c", cmd, (char*)NULL);
  }

  // Only parent gets here. Listen to what the child says
  close(pipefd[1]);
  output = fdopen(pipefd[0], "r");

  while (fgets(buffer.data(), buffer.size(), output) != nullptr) {
    result += buffer.data();
  }
  fclose(output);
}

int main(int argc, const char* argv[]) {
  using namespace ftxui;

  std::wstring command;

  Component input_command = Input(&command, "Command: ");
  Component execute = Button(L"Execute", [&] { pipe_test(&command); });

  auto renderer = Renderer(
      Container::Vertical({
          input_command,
          execute,
      }),
      [&] {
        return vbox({
                   text(L"Command Entered: " + command),
                   separator(),
                   hbox({text(L" Enter Command  : "), input_command->Render()}),
                   hbox({text(L" Press to execute   : "), execute->Render()}),
                   separator(),
                   text(L"Result:" + to_wstring(result)) | frame | flex,
               }) |
               border | frame | flex;
      });

  auto screen = ScreenInteractive::Fullscreen();
  screen.Loop(renderer);
}
