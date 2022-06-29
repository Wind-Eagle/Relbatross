#include "board.h"
#include "../basic/hash.h"
#include "../basic/utils.h"

#include <iostream>

void Board::GetFromFEN(const std::string& s) {
  for (coord_t i = 0; i < 64; i++) {
    cells[i] = kEmptyCell;
  }
  move_number = 0;
  move_counter = 0;
  castling = Castling::kNone;
  size_t pos = 0;
  subcoord_t x = 7;
  subcoord_t y = 0;
  for (size_t i = 0; i < s.size(); i++) {
    if (s[i] == ' ') {
      pos = i;
      break;
    }
    if (s[i] == '/') {
      x--;
    } else if (s[i] > '9') {
      cells[i] = CharToCell(s[i]);
    } else {
      y += s[i] - '0';
    }
  }
  if (s[pos + 1] == 'w') {
    move_side = Color::kWhite;
  } else {
    move_side = Color::kBlack;
  }
  pos += 3;
  for (size_t i = pos; i < s.size(); i++) {
    if (s[i] == 'K') {
      castling ^= Castling::kWhiteKingside;
    } else if (s[i] == 'Q') {
      castling ^= Castling::kWhiteQueenside;
    } else if (s[i] == 'k') {
      castling ^= Castling::kBlackKingside;
    } else if (s[i] == 'q') {
      castling ^= Castling::kBlackQueenside;
    } else if (s[i] == ' ') {
      pos = i + 1;
      break;
    }
  }
  if (s[pos] == '-') {
    en_passant_coord = kInvalidCoord;
    pos += 2;
  } else {
    en_passant_coord = StringToCoord(s.substr(pos, 2));
    pos += 3;
  }
  for (size_t i = pos; i < s.size(); i++) {
    if (s[i] == ' ') {
      pos = i + 1;
      continue;
    }
    move_counter *= 10;
    move_counter += s[i] - '0';
  }
  for (size_t i = pos; i < s.size(); i++) {
    move_number *= 10;
    move_number += s[i] - '0';
  }
  BuildBitboards();
  CalculateHash();
}

void Board::LoadToFEN(std::string& s) {
  s = "";
  int space = 0;
  for (subcoord_t i = 7; i >= 0; i--) {
    for (subcoord_t j = 0; j < 8; j++) {
      if (cells[MakeCoord(i, j)] == kEmptyCell) {
        space++;
      } else {
        if (space > 0) {
          s += std::to_string(space);
        }
        s += CellToChar(cells[MakeCoord(i, j)]);
        space = 0;
      }
    }
    if (space > 0) {
      s += std::to_string(space);
    }
    if (i > 0) {
      s += '/';
    }
  }
  if (move_side == Color::kWhite) {
    s += " w ";
  } else {
    s += " b ";
  }
  if (castling == Castling::kNone) {
    s += "- ";
  } else {
    if ((castling & Castling::kWhiteKingside) != Castling::kNone) {
      s += 'K';
    }
    if ((castling & Castling::kWhiteQueenside) != Castling::kNone) {
      s += 'Q';
    }
    if ((castling & Castling::kBlackKingside) != Castling::kNone) {
      s += 'k';
    }
    if ((castling & Castling::kBlackQueenside) != Castling::kNone) {
      s += 'q';
    }
    s += ' ';
  }
  if (en_passant_coord == kInvalidCoord) {
    s += "- ";
  } else {
    s += CoordToString(en_passant_coord) + " ";
  }
  s += std::to_string(move_counter) + " ";
  s += std::to_string(move_number);
}

void Board::SetStartPos() {
  GetFromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

void Board::BuildBitboards() {
  for (cell_t i = 0; i < kTotalPieceCount; i++) {
    b_pieces[i] = 0;
  }
  b_color[0] = b_color[1] = 0;
  for (coord_t i = 0; i < 64; i++) {
    b_pieces[cells[i]] |= (1ULL << i);
    b_color[static_cast<int8_t>(GetCellColor(cells[i]))] |= (1ULL << i);
  }
  b_pieces[0] = b_color[0] | b_color[1];
}

void Board::CalculateHash() {
  hash = 0;
  for (int i = 0; i < 64; i++) {
    hash ^= basic::zobrist_hash_pieces[cells[i]][i];
  }
  hash ^= basic::zobrist_hash_moveside[static_cast<int8_t>(move_side)];
}