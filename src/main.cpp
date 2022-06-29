#include "api/uci_interaction.h"
#include "basic/init.h"

#include <iostream>

int main() {
  basic::Init();
  uci::StartUciInteraction();
}
