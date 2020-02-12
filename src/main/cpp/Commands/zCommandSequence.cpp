#include "Commands/zCommandSequence.h"
#include "Commands/zCommand.h"

zCommandSequence::zCommandSequence() {
  AddCommands
  (
      //Add commands in the sequence you want them to run.
      //When one finishes, the next will start.
      //
      //Add commands comma separated. No comma after the last one
      zCommand(),
      zCommand()
  );
}
