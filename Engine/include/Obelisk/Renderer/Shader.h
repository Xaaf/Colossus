#pragma once

#include "ObeliskPCH.h"
#include "Obelisk/Core/AssetManager.h"

namespace Obelisk {

/**
 * @brief OpenGL shader program wrapper for vertex and fragment shaders.
 *
 * The Shader class encapsulates OpenGL shader compilation, linking, and usage.
 * It automatically loads shader source code from files using the AssetManager,
 * compiles vertex and fragment shaders, links them into a program, and provides
 * convenient methods for setting uniform variables.
 *
 * Key features:
 * - Automatic shader loading from asset files
 * - Comprehensive error checking and logging
 * - Type-safe uniform variable setting
 * - RAII resource management
 * - Support for common uniform types (bool, int, float, vectors, matrices)
 *
 * @example
 * ```cpp
 * // Load shaders from assets directory
 * Shader myShader("shaders/basic.vert", "shaders/basic.frag");
 *
 * // Use shader and set uniforms
 * myShader.Use();
 * myShader.SetMat4("projection", projectionMatrix);
 * myShader.SetVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
 *
 * // Render geometry...
 * ```
 */
class OBELISK_API Shader {
    private:
        unsigned int m_ProgramID;  ///< OpenGL shader program ID

        int m_Success = -1;  ///< Compilation/linking success flag
        char m_InfoLog[512] =
            {};  ///< OpenGL info log buffer for error messages

        /**
         * @brief Load shader source code from a file.
         *
         * Uses the AssetManager to resolve the file path and loads the complete
         * shader source code as a string. Handles file reading errors
         * gracefully with appropriate logging.
         *
         * @param filepath Relative path to the shader file (e.g.,
         * "shaders/basic.vert")
         * @return Complete shader source code as a string, or empty string on
         * error
         */
        static std::string LoadShaderSource(const std::string& filepath);

        /**
         * @brief Get the OpenGL location of a uniform variable.
         *
         * Queries OpenGL for the location of a named uniform variable in the
         * currently bound shader program. Logs warnings for uniforms that
         * don't exist in the shader.
         *
         * @param uniformName Name of the uniform variable in the shader
         * @return OpenGL uniform location, or -1 if the uniform doesn't exist
         */
        [[nodiscard]] unsigned int GetUniformLocation(
            const std::string& uniformName) const;

        /**
         * @brief Check for shader compilation or linking errors.
         *
         * Queries OpenGL for compilation or linking status and logs detailed
         * error information if any errors occurred. This is called internally
         * during shader creation to provide diagnostic information.
         *
         * @param shader OpenGL shader or program ID to check
         * @param type Type of check ("VERTEX", "FRAGMENT", or "PROGRAM")
         */
        void CheckCompileErrors(unsigned int shader, const std::string& type);

    public:
        /**
         * @brief Default constructor creating an invalid shader.
         *
         * Creates a shader object without loading any shader files.
         * Use the parameterized constructor or load shaders manually
         * to create a usable shader program.
         */
        Shader() = default;

        /**
         * @brief Create and compile a shader program from vertex and fragment
         * shader files.
         *
         * Loads shader source code from the specified files, compiles both
         * shaders, links them into a program, and performs error checking. The
         * shader is ready to use immediately after construction if compilation
         * succeeds.
         *
         * @param vertexPath Relative path to the vertex shader file
         * @param fragmentPath Relative path to the fragment shader file
         *
         * @note Logs detailed error information if compilation or linking fails
         * @note Uses AssetManager for reliable file path resolution
         */
        Shader(const std::string& vertexPath, const std::string& fragmentPath);

        /**
         * @brief Destructor that cleans up OpenGL resources.
         *
         * Automatically deletes the OpenGL shader program to prevent resource
         * leaks. Safe to call even if the shader was not successfully created.
         */
        ~Shader();

        /**
         * @brief Bind this shader program for rendering.
         *
         * Makes this shader program the active program for subsequent rendering
         * operations. All uniform setting and drawing calls will use this
         * shader until another shader is bound or the program is unbound.
         */
        void Use() const;

        // Uniform utility functions

        /**
         * @brief Set a boolean uniform variable.
         *
         * @param name Name of the uniform variable in the shader
         * @param value Boolean value to set
         */
        void SetBool(const std::string& name, bool value) const;

        /**
         * @brief Set an integer uniform variable.
         *
         * @param name Name of the uniform variable in the shader
         * @param value Integer value to set
         */
        void SetInt(const std::string& name, int value) const;

        /**
         * @brief Set a float uniform variable.
         *
         * @param name Name of the uniform variable in the shader
         * @param value Float value to set
         */
        void SetFloat(const std::string& name, float value) const;

        /**
         * @brief Set a 2D vector uniform variable.
         *
         * @param name Name of the uniform variable in the shader
         * @param value 2D vector value to set
         */
        void SetVec2(const std::string& name, const glm::vec2& value) const;

        /**
         * @brief Set a 3D vector uniform variable.
         *
         * @param name Name of the uniform variable in the shader
         * @param value 3D vector value to set
         */
        void SetVec3(const std::string& name, const glm::vec3& value) const;

        /**
         * @brief Set a 4D vector uniform variable.
         *
         * @param name Name of the uniform variable in the shader
         * @param value 4D vector value to set
         */
        void SetVec4(const std::string& name, const glm::vec4& value) const;

        /**
         * @brief Set a 4x4 matrix uniform variable.
         *
         * @param name Name of the uniform variable in the shader
         * @param value 4x4 matrix value to set (column-major order)
         */
        void SetMat4(const std::string& name, const glm::mat4& value) const;
};

}  // namespace Obelisk