#ifndef _TINY_SHADER_H
#define _TINY_SHADER_H

#include <string>

#include "gl3w/GL/gl3w.h"

#include "Tiny/Math/Vector4.h"
#include "Tiny/Math/RectangularMatrix.h"
#include "Tiny/Math/Matrix4.h"
#include "Tiny/Math/MathForward.h"
#include "Tiny/FileSystem/FileSystem.h"
#include "Tiny/Core/Service.h"

namespace Tiny {
	namespace Graphics {

		const int infoLen = 1024;

		class Shader
		{
		public:
			std::size_t ID() const { return id; }
			~Shader() { glDeleteProgram(id); }
			Shader() = default;
			Shader(const std::string vertexPath, const std::string fragPath)
			{
				std::string vsrc = Tiny::FileSystem::ReadChar(vertexPath);
				std::string fsrc = Tiny::FileSystem::ReadChar(fragPath);
				
				const char* vShaderCode = vsrc.c_str();
				const char* fShaderCode = fsrc.c_str();

				unsigned vertex = glCreateShader(GL_VERTEX_SHADER);
				glShaderSource(vertex, 1, &vShaderCode, NULL);
				glCompileShader(vertex);
				checkCompileErrors(vertex, "VERTEX");

				unsigned fragment = glCreateShader(GL_FRAGMENT_SHADER);
				glShaderSource(fragment, 1, &fShaderCode, NULL);
				glCompileShader(fragment);
				checkCompileErrors(fragment, "FRAGMENT");

				id = glCreateProgram();
				glAttachShader(id, vertex);
				glAttachShader(id, fragment);
				glLinkProgram(id);
				checkCompileErrors(id, "PROGRAM");

				glDeleteShader(vertex);
				glDeleteShader(fragment);
			}

			void use()
			{
				glUseProgram(id);
			}

			void setBool(const std::string& name, bool value) const
			{
				glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
			}

			void setInt(const std::string& name, int value) const
			{
				glUniform1i(glGetUniformLocation(id, name.c_str()), value);
			}

			void setFloat(const std::string& name, float value) const
			{
				glUniform1f(glGetUniformLocation(id, name.c_str()), value);
			}

			void setVec2(const std::string& name, const Math::Vector2f& value) const
			{
				glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
			}

			void setVec2(const std::string& name, float x, float y) const
			{
				glUniform2f(glGetUniformLocation(id, name.c_str()), x, y);
			}

			void setVec3(const std::string& name, const Math::Vector3f& value) const
			{
				glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
			}

			void setVec3(const std::string& name, float x, float y, float z) const
			{
				glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z);
			}

			void setVec4(const std::string& name, const Math::Vector4f& value) const
			{
				glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
			}

			void setMat2(const std::string& name, const Math::Matrix2f& value) const
			{
				glUniformMatrix2fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &value[0][0]);
			}

			void setMat3(const std::string& name, const Math::Matrix3f& value) const
			{
				glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &value[0][0]);
			}

			void setMat4(const std::string& name, const Math::Matrix4f& value) const
			{
				glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &value[0][0]);
			}
		private:
			std::size_t id;

			void checkCompileErrors(unsigned int shader, std::string type)
			{
				int success;
				char infoLog[infoLen];
				if (type != "PROGRAM")
				{
					glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
					if (!success)
					{
						glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);
						Tiny::Service::Log().E("error£ºshader compile: type:{}, info:{}", type, infoLog);
					}
				}
				else
				{
					glGetShaderiv(shader, GL_LINK_STATUS, &success);
					if (!success)
					{
						glGetProgramInfoLog(shader, sizeof(infoLog), NULL, infoLog);
						Tiny::Service::Log().E("error: shader link:", infoLog);
					}
				}
			}
		};
	}
}

#endif