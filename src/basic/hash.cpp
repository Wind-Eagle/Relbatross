#include "hash.h"
#include "utils.h"

namespace basic {
hash_t zobrist_hash_pieces[kTotalPieceCount][64];
hash_t zobrist_hash_en_passant[64];
hash_t zobrist_hash_castling[16];
hash_t zobrist_hash_double_castling[256];
hash_t zobrist_hash_kingside_castling[2];
hash_t zobrist_hash_queenside_castling[2];
hash_t zobrist_hash_moveside[2];
hash_t zobrist_hash_changed_moveside;

void InitZobrist() {
  for (cell_t i = 0; i < kTotalPieceCount; i++) {
    for (coord_t j = 0; j < 64; j++) {
      zobrist_hash_pieces[i][j] = rndgen64();
    }
    zobrist_hash_en_passant[i] = rndgen64();
  }
  for (int i = 0; i < 16; i++) {
    zobrist_hash_castling[i] = rndgen64();
  }
  for (int i = 0; i < 256; i++) {
    zobrist_hash_double_castling[i] = zobrist_hash_castling[i >> 4] ^ zobrist_hash_castling[i & 15];
  }
  zobrist_hash_moveside[0] = rndgen64();
  zobrist_hash_moveside[1] = rndgen64();
  zobrist_hash_changed_moveside = zobrist_hash_moveside[0] ^ zobrist_hash_moveside[1];
  for (Color c : {Color::kWhite, Color::kBlack}) {
    const int index = static_cast<int>(c);
    const coord_t offset = (c == Color::kWhite) ? 0 : 56;
    zobrist_hash_queenside_castling[index] =
        zobrist_hash_pieces[MakeCell(c, Piece::kKing)][offset + 4]
            ^ zobrist_hash_pieces[MakeCell(c, Piece::kRook)][offset]
            ^ zobrist_hash_pieces[MakeCell(c, Piece::kKing)][offset + 2]
            ^ zobrist_hash_pieces[MakeCell(c, Piece::kRook)][offset + 3];
    zobrist_hash_kingside_castling[index] =
        zobrist_hash_pieces[MakeCell(c, Piece::kKing)][offset + 4]
            ^ zobrist_hash_pieces[MakeCell(c, Piece::kRook)][offset + 7]
            ^ zobrist_hash_pieces[MakeCell(c, Piece::kKing)][offset + 6]
            ^ zobrist_hash_pieces[MakeCell(c, Piece::kRook)][offset + 5];
  }
}

}  // namespace basic

