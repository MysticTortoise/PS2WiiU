#!/bin/sh

# original config script by rw-r-r-0644
# modified by GaryOderNichts

cd ../../
dir=$PWD
cd libraries/Common/ffmpeg
echo "Configuring FFmpeg for Wii U"

ffmpegBuildDir=$dir"/libraries/build/WiiU/ffmpeg"

export PATH=$DEVKITPPC/bin:$PATH
export ARCH="-mcpu=750 -meabi -mhard-float"
export CFLAGS=""

./configure --prefix=$ffmpegBuildDir \
--enable-cross-compile \
--cross-prefix=$DEVKITPPC/bin/powerpc-eabi- \
--disable-shared \
--disable-runtime-cpudetect \
--disable-programs \
--disable-doc \
--disable-network \
--enable-protocol=file \
--enable-static \
--arch=ppc \
--cpu=750 \
--target-os=none \
--extra-cflags=" -D__WIIU__ $CFLAGS $ARCH -I$WUT_ROOT/include" \
--extra-cxxflags=" -D__WIIU__ $CFLAGS -fno-rtti -fno-exceptions -std=gnu++11 $ARCH" \
--extra-ldflags=" -Wl,-q -Wl,-z,nocopyreloc -specs=$WUT_ROOT/share/wut.specs -L$WUT_ROOT/lib -lwut" \
--disable-debug \
--disable-bzlib \
--disable-iconv \
--disable-lzma \
--disable-securetransport \
--disable-xlib \
--disable-zlib

make
make install
make clean