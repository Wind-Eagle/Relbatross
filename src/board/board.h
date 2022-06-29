#ifndef RELBATROSS_SRC_BOARD_BOARD_H_
#define RELBATROSS_SRC_BOARD_BOARD_H_

#include "../basic/types.h"

#include <string>

// Here is the board class. Bitboard of all pieces is stored in b_pieces[0]
// to use memory effectively. sizeof(Board) = 200
struct Board {
  cell_t cells[64];
  Color move_side;
  Castling castling;
  coord_t en_passant_coord;

  uint16_t move_counter;
  uint16_t move_number;

  bitboard_t b_pieces[kTotalPieceCount];
  bitboard_t b_color[2];
  hash_t hash;

  void GetFromFEN(const std::string& s);
  void LoadToFEN(std::string& s);
  void SetStartPos();
  void BuildBitboards();
  void CalculateHash();
};

#endif  // RELBATROSS_SRC_BOARD_BOARD_H_
