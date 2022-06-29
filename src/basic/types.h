#ifndef RELBATROSS_SRC_BASIC_TYPES_H_
#define RELBATROSS_SRC_BASIC_TYPES_H_

#include <cstdint>

// There is no namespace basic on purpose, to make code
// shorter and simpler. Don't really like writing using in each file.

#define ENUM_TO_INT_OP(type, base, op)                                           \
  inline constexpr type operator op(const type a, const type b) {                \
    return static_cast<type>(static_cast<base>(a) op static_cast<base>(b));      \
  }

#define ENUM_ASSIGNMENT_OP(type, op)                                             \
  inline constexpr type &operator op##=(type &a, const type b) {                 \
    a = a op b;                                                                  \
    return a;                                                                    \
  }

#define ENUM_TO_INT(type, base)      \
  ENUM_TO_INT_OP(type, base, &)      \
  ENUM_TO_INT_OP(type, base, |)      \
  ENUM_TO_INT_OP(type, base, ^)      \
  ENUM_ASSIGNMENT_OP(type, &)        \
  ENUM_ASSIGNMENT_OP(type, |)        \
  ENUM_ASSIGNMENT_OP(type, ^)        \
  inline constexpr type operator~(const type a) { return type::kAll ^ a; }

using coord_t = int8_t;
using subcoord_t = int8_t;
using cell_t = int8_t;
using bitboard_t = uint64_t;
using hash_t = uint64_t;

enum class Color : int8_t {
  kWhite = 0,
  kBlack = 1
};

enum class Piece : int8_t {
  kPawn = 1,
  kKnight = 2,
  kBishop = 3,
  kRook = 4,
  kQueen = 5,
  kKing = 6
};
constexpr coord_t kInvalidCell = -1;
constexpr coord_t kEmptyCell = 0;
constexpr coord_t kInvalidCoord = -1;

constexpr int8_t kPieceColorOffset = 6;
constexpr int8_t kTotalPieceCount = 13;

enum class Castling : uint8_t {
  kNone = 0,
  kWhiteKingside = 1,
  kWhiteQueenside = 2,
  kWhiteAll = kWhiteKingside | kWhiteQueenside,
  kBlackKingside = 4,
  kBlackQueenside = 8,
  kBlackAll = kBlackKingside | kBlackQueenside,
  kAll = kWhiteAll | kBlackAll
};

ENUM_TO_INT(Castling, uint8_t)

#endif  // RELBATROSS_SRC_BASIC_TYPES_H_
