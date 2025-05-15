#include "shaders/inc/textureFormats.glsl"

vec4 yuv_to_rgb(vec4 yuv){
    yuv.g = yuv.g - 0.5;
    yuv.b = yuv.b - 0.5;
    return vec4(
        yuv.r + 1.402 * yuv.b,
        yuv.r - 0.344 * yuv.g - 0.714 * yuv.b,
        yuv.r + 1.772 * yuv.g,
        1.0
    );
}