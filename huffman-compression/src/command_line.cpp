#include <stdexcept>
#include "./command_line.hpp"

void CommandLine::parse(int argc, char** argv) {
  argument_count = argc;
  argument_values = argv;
  for (int i = 0; i < argument_count; ++i) {
	passToNormalArguments(i);
	passToXoredArguments(i);
  }
}

void CommandLine::passToNormalArguments(int index) {
  for (Arg* arg : args) {
    if (arg->canProcess(argument_values[index])) {
      arg->process(index, argument_count, argument_values);
	  return;
    }
  }
}

void CommandLine::passToXoredArguments(int index) {
  for (auto [argA, argB] : xorArgs) {
    if (argA->canProcess(argument_values[index])) {
      if (argB->isResolved()) {
        throw std::runtime_error("Both flags are supplied");
      }
      argA->process(index, argument_count, argument_values);
      argB->xorProcess();
    }
    if (argB->canProcess(argument_values[index])) {
      if (argA->isResolved()) {
        throw std::runtime_error("Both flags are supplied");
      }
      argB->process(index, argument_count, argument_values);
      argA->xorProcess();
    }
  }
}

void CommandLine::add(Arg& arg) { args.push_back(&arg); }

void CommandLine::xorAdd(Arg& a, Arg& b) {
  xorArgs.emplace_back(&a, &b);
}

