#!/bin/sh
lli=${LLVMINTERP-lli}
exec $lli \
    /home/users/alberto.giusti/Desktop/backup/variableQuery/fidelta_apint/solution1/.autopilot/db/a.g.bc ${1+"$@"}
