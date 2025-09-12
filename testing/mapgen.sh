#!/usr/bin/env bash
set -euo pipefail

OUT_DIR="testmaps"
mkdir -p "$OUT_DIR"

# mk <filename>  -- content is read from stdin
mk() {
  local f="$OUT_DIR/$1"
  mkdir -p "$(dirname "$f")"
  cat > "$f"
  echo "Wrote $f"
}

########### VALID MAPS ###########

mk valid_small.ber <<'EOF'
1111111
1C000E1
1000101
1P00001
1111111
EOF

mk valid_minimal_one_c.ber <<'EOF'
11111
1P0E1
10001
1C001
11111
EOF

mk valid_multi_collectibles.ber <<'EOF'
1111111111
1P000000E1
1010100001
1C0000C001
1000100001
1111111111
EOF

mk valid_large_specstyle.ber <<'EOF'
1111111111111111111111111111111111
1E0000000000000C00000C000000000001
1010010100100000101001000000010101
1010010010101010001001000000010101
1P0000000C00C0000000000000000000C1
1111111111111111111111111111111111
EOF

mk valid_snake_corridor.ber <<'EOF'
1111111111
1P00000001
1111111101
1000000101
1011110101
1010000101
1010111101
10100000E1
1C11111111
1111111111
EOF

mk valid_many_C_around_walls.ber <<'EOF'
111111111
1P0000001
1C1111001
1C0000C01
100011C01
1E0000001
111111111
EOF

########### ERROR: MISSING/EXTRA ###########

mk error_missing_exit.ber <<'EOF'
111111
1P0001
1C0001
100001
111111
EOF

mk error_missing_player.ber <<'EOF'
111111
1C0001
1000E1
100001
111111
EOF

mk error_missing_collectible.ber <<'EOF'
111111
1P0001
1000E1
100001
111111
EOF

mk error_duplicate_exit.ber <<'EOF'
1111111
1P000E1
1000101
1C000E1
1111111
EOF

mk error_duplicate_player.ber <<'EOF'
1111111
1P000E1
1000101
1C000P1
1111111
EOF

########### ERROR: RECTANGULARITY ###########

mk error_not_rect_short_row.ber <<'EOF'
111111
1P0E1
1C0001
111111
EOF

mk error_not_rect_long_row.ber <<'EOF'
111111
1P0000E1
1C0001
111111
EOF

########### ERROR: ENCLOSURE ###########

mk error_not_enclosed_top_gap.ber <<'EOF'
110111
1P0001
1C00E1
111111
EOF

mk error_not_enclosed_left_gap.ber <<'EOF'
111111
0P0001
1C00E1
111111
EOF

########### ERROR: REACHABILITY ###########

mk error_unreachable_collectible.ber <<'EOF'
1111111
1P000E1
1110111
1C00101
1111111
EOF

mk error_unreachable_exit.ber <<'EOF'
1111111
1P00001
1110111
1C00E01
1111111
EOF

mk error_blocked_player.ber <<'EOF'
111111
1P1111
1C0E11
111111
EOF

mk error_cavity_unreachable.ber <<'EOF'
111111111
1P0000001
111011101
1C0010E01
111011101
100000001
111111111
EOF

########### ERROR: INVALID CHARS / FILE FORM ###########

mk error_invalid_char.ber <<'EOF'
1111111
1P000E1
1R00101
1C00001
1111111
EOF

# empty file
: > "$OUT_DIR/error_empty_file.ber" && echo "Wrote $OUT_DIR/error_empty_file.ber"

mk error_space_in_map.ber <<'EOF'
111111
1P 0E1
1C0001
111111
EOF

# CRLF endings (optional, requires unix2dos to actually convert)
mk error_crlf.ber <<'EOF'
111111
1P0001
1C00E1
111111
EOF
if command -v unix2dos >/dev/null 2>&1; then
  unix2dos -q "$OUT_DIR/error_crlf.ber"
  echo "Converted to CRLF: $OUT_DIR/error_crlf.ber"
else
  echo "Note: install unix2dos to convert $OUT_DIR/error_crlf.ber to CRLF."
fi

# leading / trailing blank lines
mk error_leading_blank_line.ber <<'EOF'

111111
1P0001
1C00E1
111111
EOF

mk error_trailing_blank_line.ber <<'EOF'
111111
1P0001
1C00E1
111111

EOF

echo "Done. Test maps in $OUT_DIR"
