#!/bin/sh

#./mkbl2 spl/u-boot-spl.bin bl2.bin 14336
#cat burn_files/E4412_N.bl1.SCP2G.bin spl/itop4412-spl.bin burn_files/env.bin u-boot.bin > image.bin
#dd iflag=dsync oflag=dsync if=./image.bin of=/dev/sdb seek=1
dd iflag=dsync oflag=dsync if=./burn_files/E4412_N.bl1.SCP2G.bin of=/dev/sdb seek=1
#dd iflag=dsync oflag=dsync if=./E4412_N.bl1.bin of=/dev/sdb seek=1
dd iflag=dsync oflag=dsync if=./spl/itop4412-spl.bin of=/dev/sdb seek=17
#dd iflag=dsync oflag=dsync if=./burn_files/env2.bin of=/dev/sdb seek=49
dd iflag=dsync oflag=dsync if=./u-boot.bin of=/dev/sdb seek=81
#dd iflag=dsync oflag=dsync if=./tzsw_SMDK4412_SCP_2GB.bin of=/dev/sdb  seek=705
sync
