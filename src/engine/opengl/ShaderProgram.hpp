#ifndef ZN_SHADERPROGRAM_HPP_INCLUDED
#define ZN_SHADERPROGRAM_HPP_INCLUDED

#include <string>
#include <unordered_map>
#include <GL/glew.h>
//#include "Matrix4.hpp"

namespace zn
{
namespace gl
{
	// Vertex attributes (for use in OpenGL3-based experimental version)
	enum Attrib
	{
		POSITION = 0,
		COLOR = 1,
		TEXCOORD0 = 2,
		NORMAL = 3
	};

	/*
		Shader program implementation for OpenGL 2.x or greater.
	*/

	class ShaderProgram
	{
	private :

		struct Shader
		{
			std::string sourcePath;
			GLuint ID = 0;

			Shader(GLuint sID, const std::string path)
				: sourcePath(path), ID(sID)
			{}
		};

		GLuint m_programID = 0;

		// Note: Uniforms affect a geometry (while attribs affect vertices)
		std::unordered_map<std::string,GLint> m_uniforms;

		Shader * m_vertex = nullptr;
		Shader * m_geometry = nullptr;
		Shader * m_fragment = nullptr;

	public :

		// Constructs an empty program.
		ShaderProgram() {}

		// Destroys the program and its shaders.
		~ShaderProgram();

		// Compiles and links the program from up to 3 shader types.
		// An empty source path means no shader, but at least 1 must be specified.
		// The old program will be erased if called twice.
		bool load(
			const std::string & vertSourcePath,
			const std::string & geomSourcePath,
			const std::string & fragSourcePath);

		// Deletes the program and its shaders.
		void unload();

		// Returns the program's ID.
		inline GLuint getID() const { return m_programID; }

		void setUniform(const std::string & name, const float value);

		void setUniformMat4(
			const std::string & name,
			bool transpose, const float matrixValues[16]);

	private :

		// Finds the location of an uniform using internal index.
		// If not found in the index, the program is queried.
		// Undefined uniform name leads to an undefined behavior.
		GLint getUniformLocation(const std::string & name);

		// Loads a shader from a source file,
		// and returns its ID in outShaderID.
		// Returns true if success, false if not.
		static bool loadShader(
			GLuint & outShaderID, GLenum type,
			const std::string & sourcePath);

	};

} // namespace gl
} // namespace zn

#endif // ZN_SHADERPROGRAM_HPP_INCLUDED

