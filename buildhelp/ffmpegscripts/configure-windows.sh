cd ../../
dir=$PWD
cd libraries/Common/ffmpeg
echo "Configuring FFmpeg for Windows"

ffmpegBuildDir=$dir"/libraries/build/Windows/ffmpeg"

./configure --prefix=$ffmpegBuildDir \
--enable-static \
--disable-shared \
--disable-network \
--disable-doc \
--disable-programs 
make
make install
make clean