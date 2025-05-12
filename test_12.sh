#!/usr/bin/env bash
# test_12.sh — stress-test push_swap/checker_OS on 5-element lists
# Usage: ./test_12.sh [N_TESTS]
# Default N_TESTS=20, max moves allowed=12

# re-exec under bash if someone did “sh test_12.sh”
if [ -z "${BASH_VERSION:-}" ]; then
  exec bash "$0" "$@"
fi

set -euo pipefail

# number of random cases to try (override with first arg)
N_TESTS=${1:-20}
MAX_MOVES=12
COUNT=5

for ((i=1;i<=N_TESTS;i++)); do
  # generate 5 distinct integers in [–1000..1000]
  # seq|shuf|head is more portable than shuf -i
  args=( $(seq -1000 1000 | shuf | head -n "$COUNT") )

  # collect the moves from push_swap
  moves=$(./push_swap "${args[@]}")

  # count non-empty lines
  move_count=$(printf "%s\n" "$moves" | grep -c .)

  # feed moves into checker_OS and capture its output
  result=$(printf "%s\n" "$moves" | ./checker_linux "${args[@]}" 2>&1)

  if [[ $result != OK ]]; then
    echo "FAIL #$i: checker_OS returned '$result'" >&2
    echo "  args: ${args[*]}" >&2
    exit 1
  fi

  if (( move_count > MAX_MOVES )); then
    echo "FAIL #$i: used $move_count moves (> $MAX_MOVES)" >&2
    echo "  args: ${args[*]}" >&2
    exit 1
  fi
done

echo "✔ All $N_TESTS tests passed (≤ $MAX_MOVES moves, all OK)."

