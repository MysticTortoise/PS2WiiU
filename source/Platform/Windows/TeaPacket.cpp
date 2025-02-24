#ifdef TP_WIN
#include "TeaPacket/TeaPacket.hpp"
#include "TeaPacket/Video.hpp"

#include "TeaPacket/DebugMacros.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <filesystem>
#include "TeaPacket/Scene/SceneScript.hpp"
#include "TeaPacket/Graphics/Sprite.hpp"
#include "TeaPacket/Files/Files.hpp"

#include "windows/Video.hpp"

using namespace TeaPacket;

bool TeaPacket::ShouldRun(){
    return !glfwWindowShouldClose(TeaPacket::Video::window);
}

void TeaPacket::Delay(){}


#endif