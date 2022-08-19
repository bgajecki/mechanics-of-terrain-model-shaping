#include "Shaders.hpp"

namespace Engine
{
    const ShaderInfo& Shaders::getShaderInfo(const ShaderList_t shaderIndex)
    {
        ShaderInfo shaderInfo = this->getShaderPathAndType()[shaderIndex];
        std::string path = shaderInfo.source;
        std::ifstream file(path);
        std::stringstream stream;

        if (!file.is_open())
        {
            DEBUG(std::cerr << "Could not read file " << path << ". File does not exist." << std::endl);
            stream << "";
        }
        else
        {
            stream << file.rdbuf();
        }

        shaderInfo.source = stream.str().c_str();
        return shaderInfo;
    }
}