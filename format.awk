#!/bin/awk -f
BEGIN {
    for (i = 0; i < 256; i++) ord[sprintf("%c", i)] = i
    printf "char words[] = {"
}
{
    n = length($0)
    for (i = 1; i <= n; i++) printf "%d,", ord[substr($0, i, 1)]
    for (i = n; i < 9; i++) printf "0,"
}
END { printf "0};\n" }
