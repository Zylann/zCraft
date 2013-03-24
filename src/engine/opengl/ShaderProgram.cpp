/*
ShaderProgram.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include <fstream>
#include <iostream>

#include "ShaderProgram.hpp"

namespace zn
{
namespace gl
{
	ShaderProgram::~ShaderProgram()
	{
		unload();
	}

	void ShaderProgram::unload()
	{
		glDeleteProgram(m_programID);
		m_programID = 0;

		if(m_vertex != nullptr)
		{
			glDetachShader(m_programID, m_vertex->ID);
			glDeleteShader(m_vertex->ID);
			delete m_vertex;
			m_vertex = nullptr;
		}
		if(m_geometry != nullptr)
		{
			glDetachShader(m_programID, m_geometry->ID);
			glDeleteShader(m_geometry->ID);
			delete m_geometry;
			m_geometry = nullptr;
		}
		if(m_fragment != nullptr)
		{
			glDetachShader(m_programID, m_fragment->ID);
			glDeleteShader(m_fragment->ID);
			delete m_fragment;
			m_fragment = nullptr;
		}
	}

	bool ShaderProgram::load(
			const std::string & vertSourcePath,
			const std::string & geomSourcePath,
			const std::string & fragSourcePath)
	{
		if(vertSourcePath.empty() && geomSourcePath.empty() && fragSourcePath.empty())
		{
			std::cout << "ERROR: ShaderProgram::load: "
				<< "all source paths are empty." << std::endl;
			return false;
		}

		// Deletes the program if it was already loaded
		unload();

		/* Create shaders */

		GLuint sID;

		// Vertex shader
		if(!vertSourcePath.empty()) // If specified
		{
			if(!loadShader(sID, GL_VERTEX_SHADER, vertSourcePath))
			{
				return false;
			}
			m_vertex = new Shader(sID, vertSourcePath);
		}

		// Geometry shader
		if(!geomSourcePath.empty()) // If specified
		{
			if(!loadShader(sID, GL_GEOMETRY_SHADER, geomSourcePath))
			{
				unload(); // Cancel all
				return false; // Failed
			}
			m_geometry = new Shader(sID, geomSourcePath);
		}

		// Pixel shader
		if(!fragSourcePath.empty()) // If specified
		{
			if(!loadShader(sID, GL_FRAGMENT_SHADER, fragSourcePath))
			{
				unload(); // Cancel all
				return false; // Failed
			}
			m_fragment = new Shader(sID, fragSourcePath);
		}

		/* Link shaders into a program */

		std::cout << "INFO: linking shader program..." << std::endl;

		m_programID = glCreateProgram();

		// Attach shaders to the program
		if(m_vertex != nullptr)
			glAttachShader(m_programID, m_vertex->ID);
		if(m_geometry != nullptr)
			glAttachShader(m_programID, m_geometry->ID);
		if(m_fragment != nullptr)
			glAttachShader(m_programID, m_fragment->ID);

		// Generic input shader variables (only for OpenGL3-based experimental version)
//		glBindAttribLocation(m_programID, Attrib::POSITION, "in_Position");
//		glBindAttribLocation(m_programID, Attrib::COLOR, "in_Color");
//		glBindAttribLocation(m_programID, Attrib::TEXCOORD0, "in_TexCoord0");
//		glBindAttribLocation(m_programID, Attrib::NORMAL, "in_Normal");

		glLinkProgram(m_programID);

		/* Check errors */

		GLint isLinked = 0;
		glGetProgramiv(m_programID, GL_LINK_STATUS, &isLinked);
		if(isLinked != GL_TRUE)
		{
			// Retrieve error log size
			GLint errorSize = 0;
			glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &errorSize);

			// This string will contain the error message
			char * errorStr = new char[errorSize + 1];
			errorStr[errorSize] = '\0';

			// Retrieve the error log
			glGetProgramInfoLog(m_programID, errorSize, &errorSize, errorStr);

			// Display the error
			std::cout << "ERROR: ShaderProgram::load: "
				<< "Link error(s)." << std::endl
				<< errorStr << std::endl;

			// Free memory and return
			delete[] errorStr;
			unload(); // Rollback
			return false; // Error
		}

		return true; // Fine !
	}

	bool ShaderProgram::loadShader(
			GLuint & outShaderID, GLenum type, const std::string & sourcePath)
	{
		std::cout << "INFO: Compiling shader " << sourcePath << "..." << std::endl;

		/* Load shader source */

		std::string source, sourceLine;

		// Open source file
		std::ifstream sourceFile(sourcePath.c_str());
		if(!sourceFile)
		{
			std::cout << "ERROR: ShaderProgram::loadShader: "
				<< "Unable to read source file (" << sourcePath
				<< "). Cause : can't open, or file don't exists." << std::endl;
			return false;
		}

		// Read the whole content of the file
		while(std::getline(sourceFile, sourceLine))
			source += sourceLine + '\n';

		// Close source file
		sourceFile.close();

		/* Create and compile shader */

		outShaderID = glCreateShader(type);
		if(outShaderID == 0)
		{
			std::cout << "ERROR: ShaderProgram::loadShader: "
				<< "Unable to create shader. Cause : unknown type ("
				<< (int)type << ")" << std::endl;
			return false;
		}

		const GLchar * sourceStr = source.c_str();

		glShaderSource(outShaderID, 1, &sourceStr, 0);
		glCompileShader(outShaderID);

		/* Check compilation */

		GLint isCompiled = 0;
		glGetShaderiv(outShaderID, GL_COMPILE_STATUS, &isCompiled);

		if(isCompiled != GL_TRUE)
		{
			// Retrieve error log size
			GLint errorSize = 0;
			glGetShaderiv(outShaderID, GL_INFO_LOG_LENGTH, &errorSize);

			// This string will contain the error message
			char * errorStr = new char[errorSize + 1];
			errorStr[errorSize] = '\0';

			// Retrieve the error log
			glGetShaderInfoLog(outShaderID, errorSize, &errorSize, errorStr);

			// Display the error
			std::cout << "ERROR: ShaderProgram::loadShader: "
				<< "Compile error(s). (shader type is " << type << ") " << std::endl
				<< errorStr << std::endl;

			// Free memory and return
			delete[] errorStr;
			glDeleteShader(outShaderID);

			return false; // Error
		}

		return true; // Fine !
	}

	void ShaderProgram::bind()
	{
		glUseProgram(m_programID);
	}

	void ShaderProgram::unbind()
	{
		glUseProgram(0);
	}

	void ShaderProgram::setUniform(const std::string & name, const float value)
	{
		glUniform1f(getUniformLocation(name), value);
	}

	void ShaderProgram::setUniform(
			const std::string & name,
			const float x, const float y)
	{
		glUniform2f(getUniformLocation(name), x, y);
	}

	void ShaderProgram::setUniform(
			const std::string & name,
			const float x, const float y, const float z)
	{
		glUniform3f(getUniformLocation(name), x, y, z);
	}

	void ShaderProgram::setUniform(
			const std::string & name,
			const float x, const float y, const float z, const float w)
	{
		glUniform4f(getUniformLocation(name), x, y, z, w);
	}

	void ShaderProgram::setUniform(
			const std::string & name, bool transpose, const float matrixValues[16])
	{
		glUniformMatrix4fv(
			getUniformLocation(name),
			1, transpose, matrixValues);
	}

	GLint ShaderProgram::getUniformLocation(const std::string & name)
	{
		GLint loc;
		auto it = m_uniforms.find(name);
		if(it == m_uniforms.end())
		{
			loc = glGetUniformLocation(m_programID, name.c_str());
			m_uniforms[name] = loc;
		}
		else
		{
			loc = it->second;
		}
		return loc;
	}

} // namespace gl
} // namespace zn




