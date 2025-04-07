cd ../../
dir=$PWD
cd libraries/Windows/ffmpeg
echo "Configuring FFmpeg for Windows"

ffmpegBuildDir=$dir"/libraries/build/Windows/ffmpeg"

./configure --prefix=$ffmpegBuildDir \
--enable-static \
--disable-shared \
--disable-network \
--disable-doc \
--disable-programs 
make -j16
make install
make clean