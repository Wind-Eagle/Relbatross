#ifndef RELBATROSS_SRC_BASIC_HASH_H_
#define RELBATROSS_SRC_BASIC_HASH_H_

#include "types.h"

namespace basic {
extern hash_t zobrist_hash_pieces[kTotalPieceCount][64];
extern hash_t zobrist_hash_en_passant[64];
extern hash_t zobrist_hash_castling[16];
extern hash_t zobrist_hash_double_castling[256];
extern hash_t zobrist_hash_kingside_castling[2];
extern hash_t zobrist_hash_queenside_castling[2];
extern hash_t zobrist_hash_moveside[2];
extern hash_t zobrist_hash_changed_moveside;

void InitZobrist();

}  // namespace basic

#endif  // RELBATROSS_SRC_BASIC_HASH_H_
