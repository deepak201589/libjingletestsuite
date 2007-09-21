#!/bin/sh
# MSE, team chop-chop 

mknod /dev/hitbox c 62 0
mknod /dev/nistnet c 62 1
chown root /dev/hitbox
chown root /dev/nistnet
mknod /dev/mungebox c 63 0
chown root /dev/mungebox
mknod /dev/spybox c 64 0
chown root /dev/spybox

/root/nistnet-3.0a/Load.Nistnet
cnistnet -u
#cnistnet -a 0.0.0.0 0.0.0.0 add new --delay 80
#cnistnet -R
