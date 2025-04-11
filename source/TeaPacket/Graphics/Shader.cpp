#include "TeaPacket/Graphics/Shader.hpp"

#include "TeaPacket/Files/Files.hpp"

#include "TeaPacket/Logging.hpp"

#include <cstring>
#include <vector>
#include <regex>

const char* beginToken = "#include \"";
const char* endToken = "\"";


std::string& TeaPacket::Graphics::Shader::ParseShaderText(std::string& text){
    size_t pos = -1;
    size_t endPos;
    while(true){
        pos = text.find(beginToken);
        if(pos == std::string::npos){ break; }
        endPos = text.find(endToken, pos + strlen(beginToken));
        size_t beginPos = pos + strlen(beginToken);
        std::string path = text.substr(beginPos, endPos-beginPos);
        text = std::regex_replace(text, std::regex(beginToken + path + endToken), TeaPacket::Files::ReadTextFile(path.c_str()));
    }

    return text;
}