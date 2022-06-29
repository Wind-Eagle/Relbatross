#include "uci_interaction.h"
#include "../board/board.h"
#include "../basic/utils.h"

#include <iostream>
#include <vector>

namespace uci {
static void UciStart() {
  std::cout << "Hello! I'm Relbatross. I'm currently under construction, ";
  std::cout << "so I am not able to play yet.\n";
  std::cout << "id name Relbatross x64 version unknown" << std::endl;
  std::cout << "id author Wind_Eagle" << std::endl;
  std::cout << "uciok" << std::endl;
}

static void UciReady() {
  std::cout << "readyok" << std::endl;
}

static void CheckEasterEgg(const std::vector<std::string>& cmd) {
  if (cmd[0] == "hello") {
    std::cout << "Hello!" << std::endl;
  }
  if (cmd[0] == "sofcheck") {
    std::cout << "SoFCheck <3" << std::endl;
  }
  if (cmd[0] == "relbatross") {
    std::cout << "At your service." << std::endl;
  }
  if (cmd[0] == "albatross") {
    std::cout << "Beware the mighty Albatross! (or not so mighty...)" << std::endl;
  }
  if (cmd[0] == "seagull") {
    std::cout << "Old cute weakling" << std::endl;
  }
}

static void HandlePosition(Board& board, const std::vector<std::string>& cmd) {
  if (cmd.size() <= 1) {
    return;
  }
  std::string fen = cmd[1];
  int offset = 7;
  if (fen == "startpos") {
    offset = 2;
    board.SetStartPos();
  } else {
    for (int i = 1; i < 7; i++) {
      fen += cmd[i];
    }
    board.GetFromFEN(fen);
  }
  if (cmd.size() > offset && cmd[offset] == "moves") {
    std::cout << "Moves are not implemented yet." << std::endl;
  }
}

static void HandleGo() {
  std::cout << "Not implemented yet." << std::endl;
}

void StartUciInteraction() {
  Board board;
  board.SetStartPos();
  while (true) {
    std::string command;
    getline(std::cin, command);
    if (command.empty()) {
      continue;
    }
    std::vector<std::string> parsed_command = GetParsedCommand(command);
    if (parsed_command[0] == "uci") {
      UciStart();
    } else if (parsed_command[0] == "isready") {
      UciReady();
    } else if (parsed_command[0] == "position") {
      HandlePosition(board, parsed_command);
    } else if (parsed_command[0] == "go") {
      HandleGo();
    } else if (parsed_command[0] == "quit") {
      break;
    } else  {
      CheckEasterEgg(parsed_command);
    }
  }
}

}  // namespace uci