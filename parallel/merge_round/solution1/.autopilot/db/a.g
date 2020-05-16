#!/bin/sh
lli=${LLVMINTERP-lli}
exec $lli \
    /home/users/alberto.giusti/FIDELTA/parallel/merge_round/solution1/.autopilot/db/a.g.bc ${1+"$@"}
