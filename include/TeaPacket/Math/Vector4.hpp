#pragma once



namespace TeaPacket::Math{
    class Vector4{
        public:
            float x;
            float y;
            float z;
            float w;

            Vector4(float x = 1, float y = 1, float z = 1, float w = 0);
    };
}

union Color
{
    TeaPacket::Math::Vector4 vec;
    struct{
        float r;
        float g;
        float b;
        float a;
    };
};
