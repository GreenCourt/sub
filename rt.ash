#!/bin/ash
[ $# -ne 2 -a $# -ne 3 ] && echo "usage: $0 generator exe1 [exe2]" >&2 && exit 1
make -s "$@" || exit $?

TLE=10

GEN="`realpath "$1"`" || exit $?
EXE1="`realpath "$2"`" || exit $?
[ $# -eq 2 ] || EXE2="`realpath "$3"`" || exit $?

for i in `seq 10000`
do
  printf "\r%d: %s " "$i" "$GEN"
  I="`timeout $TLE "$GEN"`" || exit $?

  printf "\r%d: %s " "$i" "$EXE1"
  O1="`echo "$I" | timeout $TLE "$EXE1" 2>/dev/null`"
  if [ $? -ne 0 ] 
  then
    echo "$I" > failed
    echo RE
    echo "$I" | head -v
    exit 1
  fi

  [ $# -eq 2 ] && continue

  printf "\r%d: %s " "$i" "$EXE2"
  O2="`echo "$I" | timeout $TLE "$EXE2" 2>/dev/null`"
  if [ $? -ne 0 ] 
  then
    echo "$I" > failed
    echo RE
    echo "$I" | head -v
    exit 1
  fi

  if ! diff -q -b <(echo "$O1") <(echo "$O2")
  then
    echo "$I" > failed
    echo "$I" | head -v
    echo
    echo "___ $EXE1 ___"; echo "$O1" | head
    echo
    echo "___ $EXE2 ___"; echo "$O2" | head
    exit 1
  fi
done
