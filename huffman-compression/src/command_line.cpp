#include <stdexcept>
#include "./command_line.hpp"

void CommandLine::parse(int argc, char** argv) {
  for (int i = 0; i < argc; ++i) {
    for (Arg* arg : args) {
      if (arg->canProcess(argv[i])) {
        arg->process(i, argc, argv);
        break;
      }
    }
    for (int j = 0; j < xorArgsA.size(); ++j) {
      auto& argA = *xorArgsA[j];
      auto& argB = *xorArgsB[j];
      if (argA.canProcess(argv[i])) {
        if (argB.isDoneProcessing()) {
          throw std::runtime_error("Supplying both flags");
        }
        argA.process(i, argc, argv);
        argB.xorProcess(i, argc, argv);
      }
      if (argB.canProcess(argv[i])) {
        if (argA.isDoneProcessing()) {
          throw std::runtime_error("Supplying both flags");
        }
        argB.process(i, argc, argv);
        argA.xorProcess(i, argc, argv);
      }
    }
  }
}
void CommandLine::add(Arg& arg) { args.push_back(&arg); }

void CommandLine::xorAdd(Arg& a, Arg& b) {
  xorArgsA.push_back(&a);
  xorArgsB.push_back(&b);
}

