#!/bin/sh
function warn {
  echo "Warning: $1 does not seem to have the correct copyright format"
}

function replace {
  # first occurence of start of copyright block
  s=$(sed -e "$1!d" -e "0,$1=" -e"$1d" < $3)
  # first occurence of end of copyright block
  e=$(sed -e "$2!d" -e "0,$2=" -e"$2d" < $3)
  # Check if copyright block delimters found.
  if test -n "$s" -a -n "$e"; then
  # Check if copyright delimters are ordered properly.
    if test "$s" -lt "$e"; then
      # Replace copyright block with template.
      sed -e "${e}r$4" -e "${s},${e}d" < $3 > $3.tmp
      mv $3.tmp $3
      echo "ok: $3"
    else
      warn $3
    fi
  else
    warn $3
  fi
}

# C source and header files
for name in $(find .. -wholename "../applications/texture" -prune -o -name "*.[ch]" -print -o -name "nfftconf.h.in" -print); do
  replace "/^ \* Copyright/" "/^ \* Franklin Street/" $name "copyright.txt"
done

# MATLAB scripts
for name in $(find .. -wholename "../applications/texture" -prune -o -name "*.m" -print); do
  replace "/^% Copyright/" "/^% Franklin Street/" $name "copyright_matlab.txt"
done