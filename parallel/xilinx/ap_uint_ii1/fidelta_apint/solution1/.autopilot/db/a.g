#!/bin/sh
lli=${LLVMINTERP-lli}
exec $lli \
    /home/users/alberto.giusti/Desktop/backup/ap_uint_ii1/fidelta_apint/solution1/.autopilot/db/a.g.bc ${1+"$@"}