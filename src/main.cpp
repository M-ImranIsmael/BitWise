#include <bitset>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace ftxui;

int DetectBase(const std::string &input) {
  if (input.size() > 2 && input.substr(0, 2) == "0x") {
    return 16;
  }
  if (input.size() > 2 && input.substr(0, 2) == "0b") {
    return 2;
  }
  if (input.size() > 1 && input[0] == '0' && input.size() > 2) {
    return 8;
  }
  return 10;
}

std::string ConvertBase(const std::string &input, int from_base, int to_base) {
  unsigned long long value = std::stoull(input, nullptr, from_base);
  std::stringstream ss;
  if (to_base == 2) {
    ss << std::bitset<32>(value).to_string();
  } else {
    ss << std::uppercase << std::setbase(to_base) << value;
  }
  return ss.str();
}

Element ConvertToAllBases(const std::string &input) {
  int base = DetectBase(input);
  try {
    std::string sanitized_input = input;
    if (base == 2) {
      sanitized_input = input.substr(2);  // Remove the "0b" prefix for binary
    } else if (base == 16) {
      sanitized_input = input.substr(2);  // Remove the "0x" prefix for hex
    }
    
    // Create colored results
    return vbox({
      text("Binary: " + ConvertBase(sanitized_input, base, 2)) | color(Color::Cyan),
      text("Decimal: " + ConvertBase(sanitized_input, base, 10)) | color(Color::Green),
      text("Hexadecimal: " + ConvertBase(sanitized_input, base, 16)) | color(Color::Yellow),
    });
  } catch (const std::exception &) {
    return text("Invalid Input") | color(Color::Red);
  }
}

int main() {
  auto screen = ScreenInteractive::TerminalOutput();

  std::string input_value = "0";

  auto input_component = Input(&input_value, "Input value");

  auto result = [&]() { return ConvertToAllBases(input_value); };

  auto component = Container::Vertical({
      input_component,
      Renderer([&] { return result(); }),
  });

  auto renderer = Renderer(component, [&] {
    return vbox({
        text("Multi-Base Interactive Calculator") | bold | nothing,
        separator(),
        component->Render(),
    });
  });

  screen.Loop(renderer);

  return 0;
}
