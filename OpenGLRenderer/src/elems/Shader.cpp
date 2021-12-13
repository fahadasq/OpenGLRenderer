#include <pch.h>
#include "Shader.h"
#include <ErrorHandler.h>
#include "UniformBufferStructs.h"

Shader::Shader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile)
{
    LoadShader(vShaderFile, fShaderFile, gShaderFile);
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererID));
}

void Shader::Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource)
{
    unsigned int sVertex, sFragment, gShader;
    // vertex Shader
    GLCall(sVertex = glCreateShader(GL_VERTEX_SHADER));
    GLCall(glShaderSource(sVertex, 1, &vertexSource, NULL));
    GLCall(glCompileShader(sVertex));

    CheckCompileErrors(sVertex, "VERTEX");

    // fragment Shader
    GLCall(sFragment = glCreateShader(GL_FRAGMENT_SHADER));
    GLCall(glShaderSource(sFragment, 1, &fragmentSource, NULL));
    GLCall(glCompileShader(sFragment));

    CheckCompileErrors(sFragment, "FRAGMENT");

    // if geometry shader source code is given, also compile geometry shader
    if (geometrySource != nullptr)
    {
        GLCall(gShader = glCreateShader(GL_GEOMETRY_SHADER));
        GLCall(glShaderSource(gShader, 1, &geometrySource, NULL));
        GLCall(glCompileShader(gShader));

        CheckCompileErrors(gShader, "GEOMETRY");
    }

    // shader program
    GLCall(m_RendererID = glCreateProgram());
    GLCall(glAttachShader(m_RendererID, sVertex));
    GLCall(glAttachShader(m_RendererID, sFragment));

    if (geometrySource != nullptr)
    {
        GLCall(glAttachShader(m_RendererID, gShader));
    }

    GLCall(glLinkProgram(m_RendererID));
    CheckCompileErrors(m_RendererID, "PROGRAM");

    // delete the shaders as they're linked into our program now and no longer necessary
    GLCall(glDeleteShader(sVertex));
    GLCall(glDeleteShader(sFragment));
    if (geometrySource != nullptr)
    {
        GLCall(glDeleteShader(gShader));
    }
}

void Shader::LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    try
    {
        // open files
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        // if geometry shader path is present, also load a geometry shader
        if (gShaderFile != nullptr)
        {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception e)
    {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    const char* gShaderCode = geometryCode.c_str();
    // 2. now create shader object from source
    Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
}

void Shader::Bind() const
{
    GLCall(glUseProgram(m_RendererID));
}

GLint Shader::GetUniformLocation(const std::string& name)
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    GLCall(GLint location = glGetUniformLocation(m_RendererID, name.c_str()));
    m_UniformLocationCache[name] = location;
    return location;
}

void Shader::CheckCompileErrors(GLuint object, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        GLCall(glGetShaderiv(object, GL_COMPILE_STATUS, &success));
        if (!success)
        {
            GLCall(glGetShaderInfoLog(object, 1024, NULL, infoLog));
            std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
    else
    {
        GLCall(glGetProgramiv(object, GL_LINK_STATUS, &success));
        if (!success)
        {
            GLCall(glGetProgramInfoLog(object, 1024, NULL, infoLog));
            std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
}

void Shader::SetFloat(const char* name, float value)
{
    GLint location = GetUniformLocation(name);

    GLCall(glUniform1f(location, value));
}
void Shader::SetInteger(const char* name, int value)
{
    GLint location = GetUniformLocation(name);

    GLCall(glUniform1i(location, value));
}
void Shader::SetVector2f(const char* name, float x, float y)
{
    GLint location = GetUniformLocation(name);

    GLCall(glUniform2f(location, x, y));
}
void Shader::SetVector2f(const char* name, const glm::vec2& value)
{
    GLint location = GetUniformLocation(name);

    GLCall(glUniform2f(location, value.x, value.y));
}
void Shader::SetVector3f(const char* name, float x, float y, float z)
{
    GLint location = GetUniformLocation(name);

    GLCall(glUniform3f(location, x, y, z));
}
void Shader::SetVector3f(const char* name, const glm::vec3& value)
{
    GLint location = GetUniformLocation(name);

    GLCall(glUniform3f(location, value.x, value.y, value.z));
}
void Shader::SetVector4f(const char* name, float x, float y, float z, float w)
{
    GLint location = GetUniformLocation(name);

    GLCall(glUniform4f(location, x, y, z, w));
}
void Shader::SetVector4f(const char* name, const glm::vec4& value)
{
    GLint location = GetUniformLocation(name);

    GLCall(glUniform4f(location, value.x, value.y, value.z, value.w));
}
void Shader::SetMatrix4(const char* name, const glm::mat4& matrix)
{
    GLint location = GetUniformLocation(name);

    GLCall(glUniformMatrix4fv(location, 1, false, glm::value_ptr(matrix)));
}

void Shader::SetUniformBindingPoint(const char* name, const unsigned int index)
{
    Bind();
    GLCall(unsigned int blockIndex = glGetUniformBlockIndex(m_RendererID, name));
    GLCall(glUniformBlockBinding(m_RendererID, blockIndex, index));
}

void Shader::BindUniformBlocks()
{
    int blockCount;
    GLCall(glGetProgramiv(m_RendererID, GL_ACTIVE_UNIFORM_BLOCKS, &blockCount));

    for (int i = 0; i < blockCount; i++)
    {
        int nameLength;
        GLCall(glGetActiveUniformBlockiv(m_RendererID, i, GL_UNIFORM_BLOCK_NAME_LENGTH, &nameLength));
        std::unique_ptr<char> ch = std::make_unique<char>();
        std::vector<GLchar> name;
        name.resize(nameLength);
        GLCall(glGetActiveUniformBlockName(m_RendererID, i, nameLength, NULL, &name[0]));
        const char* blockName = std::string(name.begin(), name.end() - 1).c_str();

        if (blockName == ViewProjection::GetName())
        {
            SetUniformBindingPoint(ViewProjection::GetName(), ViewProjection::slot);
        }
    }
}

MaterialUniformLayout Shader::GetMaterialUniforms()
{
    MaterialUniformLayout uniformLayout;
    std::vector<Uniform> materialUniforms;
    std::vector<TextureUniform> texUniforms;

    GLint i;
    GLint count;

    GLint size; // size of the variable
    GLenum type; // type of the variable (float, vec3 or mat4, etc)

    const GLsizei bufSize = 32; // maximum name length
    GLchar name[bufSize]; // variable name in GLSL
    GLsizei length; // name length

    GLCall(glGetProgramiv(m_RendererID, GL_ACTIVE_UNIFORMS, &count));

    unsigned int slot = 0;

    for (i = 0; i < count; i++)
    {
        GLCall(glGetActiveUniform(m_RendererID, (GLuint)i, bufSize, &length, &size, &type, name));

        std::string nameStr(name);

        if (nameStr.find("u_Material") != std::string::npos)
        {
            if (type != GL_SAMPLER_2D)
            {
                Uniform uniform(type, name);
                materialUniforms.push_back(uniform);
            }
            else
            {
                TextureUniform texUniform(slot, name);
                texUniforms.push_back(texUniform);
                slot++;
            }
        }
    }

    uniformLayout.uniforms = materialUniforms;
    uniformLayout.texUniforms = texUniforms;

    return uniformLayout;
}
