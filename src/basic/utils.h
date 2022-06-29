#ifndef RELBATROSS_SRC_UTIL_UTILS_H_
#define RELBATROSS_SRC_UTIL_UTILS_H_

#include "types.h"

#include <ctime>
#include <random>

static std::mt19937 rndgen32(time(nullptr));
static std::mt19937_64 rndgen64(time(nullptr));

inline constexpr cell_t MakeCell(const Color c, const Piece p) {
  return static_cast<int8_t>(c) * 6 + static_cast<int8_t>(p);
}

inline constexpr coord_t MakeCoord(const subcoord_t x, const subcoord_t y) {
  return (x << 3) | y;
}

inline constexpr cell_t CharToCell(const char c) {
  switch (c) {
    case 'P':
      return 1;
    case 'N':
      return 2;
    case 'B':
      return 3;
    case 'R':
      return 4;
    case 'Q':
      return 5;
    case 'K':
      return 6;
    case 'p':
      return 7;
    case 'n':
      return 8;
    case 'b':
      return 9;
    case 'r':
      return 10;
    case 'q':
      return 11;
    case 'k':
      return 12;
  }
  __builtin_unreachable();
}

inline constexpr char CellToChar(const cell_t c) {
  switch (c) {
    case 1:
      return 'P';
    case 2:
      return 'N';
    case 3:
      return 'B';
    case 4:
      return 'R';
    case 5:
      return 'Q';
    case 6:
      return 'K';
    case 7:
      return 'p';
    case 8:
      return 'n';
    case 9:
      return 'b';
    case 10:
      return 'r';
    case 11:
      return 'q';
    case 12:
      return 'k';
  }
  __builtin_unreachable();
}

inline coord_t StringToCoord(const std::string s) {
  return ((s[1] - '1') << 3) + (s[0] - 'a');
}

inline std::string CoordToString(const coord_t c) {
  return std::string() + static_cast<char>(((c & 7) + 'a')) + static_cast<char>(((c >> 3) + '1'));
}

inline constexpr Color GetCellColor(const cell_t cell) {
  return (cell > kPieceColorOffset ? Color::kWhite : Color::kBlack);
}

inline std::vector<std::string> GetParsedCommand(const std::string& s) {
  std::string cur;
  std::vector<std::string> ans;
  for (auto i : s) {
    if (i == ' ') {
      if (!cur.empty()) {
        ans.push_back(cur);
      }
      cur = "";
    } else {
      cur += i;
    }
  }
  if (!cur.empty()) {
    ans.push_back(cur);
  }
  return ans;
}

#endif  // RELBATROSS_SRC_UTIL_UTILS_H_
