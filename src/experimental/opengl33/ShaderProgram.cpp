/*
ShaderProgram.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include <fstream>
#include <iostream>

#include "ShaderProgram.hpp"

namespace experimental
{
namespace gl
{
	ShaderProgram::ShaderProgram(
			const std::string & vertSourcePath,
			const std::string & fragSourcePath)
	{
		m_vertexSourcePath = vertSourcePath;
		m_fragmentSourcePath = fragSourcePath;
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(m_programID);
	}

	bool ShaderProgram::load(
			const std::string & vertSourcePath,
			const std::string & fragSourcePath)
	{
		m_vertexSourcePath = vertSourcePath;
		m_fragmentSourcePath = fragSourcePath;
		return load();
	}

	bool ShaderProgram::load()
	{
		if(m_vertexSourcePath.empty() || m_fragmentSourcePath.empty())
		{
			std::cout << "ERROR: ShaderProgram::load(void): "
				<< "a source path is empty." << std::endl;
			return false;
		}

		// Deletes the program if it was already loaded
		glDeleteProgram(m_programID);

		/* Create shaders */

		// Vertex shader
		if(!loadShader(m_vertexID, GL_VERTEX_SHADER, m_vertexSourcePath))
			return false; // Failed

		// Pixel shader
		if(!loadShader(m_fragmentID, GL_FRAGMENT_SHADER, m_fragmentSourcePath))
		{
			glDeleteShader(m_vertexID);
			return false; // Failed
		}

		/* Link shaders into a program */

		std::cout << "INFO: linking shader program..." << std::endl;

		m_programID = glCreateProgram();

		// Attach shaders to the program
		glAttachShader(m_programID, m_vertexID);
		glAttachShader(m_programID, m_fragmentID);

		// Generic input shader variables
		glBindAttribLocation(m_programID, ShaderIn::POSITION, "in_Position");
		glBindAttribLocation(m_programID, ShaderIn::COLOR, "in_Color");
		glBindAttribLocation(m_programID, ShaderIn::TEXCOORD0, "in_TexCoord0");
		glBindAttribLocation(m_programID, ShaderIn::NORMAL, "in_Normal");

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
			glDeleteProgram(m_programID);
			// Don't leak shaders
			glDeleteShader(m_vertexID);
			glDeleteShader(m_fragmentID);

			return false; // Error
		}

		/* Linked successfully, now detach shaders */

		glDetachShader(m_programID, m_vertexID);
		glDetachShader(m_programID, m_fragmentID);

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
				<< "Unable to read source file. "
				<< "Cause : can't open, or file don't exists." << std::endl;
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

	void ShaderProgram::setMatrix4(
			std::string name, bool transpose, const Matrix4 & matrix)
	{
		// TODO ShaderProgram: map uniforms into an unordered_map
		glUniformMatrix4fv(
			glGetUniformLocation(m_programID, name.c_str()),
			1, transpose, matrix.values());
	}


} // namespace gl
} // namespace engine




