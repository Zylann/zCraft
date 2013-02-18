#ifndef SHADERPROGRAM_HPP_INCLUDED
#define SHADERPROGRAM_HPP_INCLUDED

#include <string>
#include <unordered_map>

#include "opengl.hpp"
#include "Matrix4.hpp"

namespace experimental
{
namespace gl
{
	/*
		Shader program implementation for OpenGL 3.x.
	*/

	class ShaderProgram
	{
	private :

		std::string m_fragmentSourcePath;
		std::string m_vertexSourcePath;

		GLuint m_vertexID = 0;
		GLuint m_fragmentID = 0;
		GLuint m_programID = 0;

	public :

		ShaderProgram() {}

		// Creates a shader from both fragment and vertex source files.
		// Use load to compile them.
		ShaderProgram(
			const std::string & vertSourcePath,
			const std::string & fragSourcePath);

		// Destroys the shader program.
		~ShaderProgram();

		// Compiles and links the program.
		// The old program will be erased if called twice.
		bool load();

		bool load(
			const std::string & vertSourcePath,
			const std::string & fragSourcePath);

		// Returns the program's ID.
		inline GLuint getID() const { return m_programID; }

		void setMatrix4(std::string name, bool transpose, const Matrix4 & matrix);

	private :

		bool loadShader(
			GLuint & outShaderID, GLenum type,
			const std::string & sourcePath);

	};

} // namespace gl
} // namespace experimental

#endif // SHADERPROGRAM_HPP_INCLUDED
