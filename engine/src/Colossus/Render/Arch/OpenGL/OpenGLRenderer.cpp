#include "Colossus/Render/Arch/OpenGL/OpenGLRenderer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Colossus/Engine.h"
#include "Colossus/Input/Keyboard.h"
#include "Colossus/Render/Arch/OpenGL/Shader.h"
#include "Colossus/Render/Arch/OpenGL/Texture.h"
#include "Colossus/Render/Mesh.h"

using namespace Colossus;

std::vector<float> vertices = {
    // positions          // texture coords
    0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  // top right
    0.5f,  -0.5f, 0.0f, 1.0f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // bottom left
    -0.5f, 0.5f,  0.0f, 0.0f, 1.0f   // top left
};
std::vector<int> inds = {
    0, 1, 3,  // first triangle
    1, 2, 3   // second triangle
};

Shader shader;
Texture texture;

void temp_shaders() {
    shader.create("assets/shaders/default.vert", "assets/shaders/default.frag");
    texture.create("assets/textures/wall.jpg");

    LOG_INFO("OpenGL", "All done!");
}

// =======================

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    LOG_TRACE("OpenGL", "Resizing to " << width << "x" << height);
    glViewport(0, 0, width, height);
}

void keyboard_callback(GLFWwindow* window, int key, int scancode, int action,
                       int mods) {
    LOG_TRACE("OpenGL", "Passing key callback through abstraction layer");
    Keyboard::callback(key, action);
}

bool OpenGLRenderer::initialise() {
    LOG_TRACE("OpenGL", "Calling OpenGLRenderer::initialise");

    // Initialise
    if (!glfwInit()) {
        LOG_ERROR("OpenGL", "Failed to initialise GLFW!");
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    return true;
}

bool OpenGLRenderer::createWindow() {
    LOG_TRACE("OpenGL", "Calling OpenGLRenderer::createWindow");

    m_WindowName = "Heroes of Colossus";
    m_Width = 1280;
    m_Height = 720;

    m_Window = glfwCreateWindow(m_Width, m_Height, m_WindowName.c_str(),
                                nullptr, nullptr);

    if (m_Window == nullptr) {
        LOG_ERROR("OpenGL", "Failed to create new window!");
        glfwTerminate();

        return false;
    }

    glfwMakeContextCurrent(m_Window);

    // Set callbacks
    glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);
    glfwSetKeyCallback(m_Window, keyboard_callback);

    LOG_INFO("OpenGL", "Successfully set callbacks");

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        LOG_ERROR("OpenGL", "Failed to initialise GLAD!");
        glfwTerminate();

        return false;
    }

    glViewport(0, 0, m_Width, m_Height);

    LOG_INFO("OpenGL",
             "Initialised OpenGL viewport with " << m_Width << "x" << m_Height);
    LOG_INFO("OpenGL", " > GLFW v" << glfwGetVersionString() << ", OpenGL v"
                                   << glGetString(GL_VERSION));
    LOG_INFO("OpenGL", " > Graphics Card: " << glGetString(GL_RENDERER) << ", "
                                            << glGetString(GL_VENDOR));

    // TODO: Remove!
    temp_shaders();

    Mesh mesh(vertices, inds);
    addMesh(mesh);

    return true;
}

void OpenGLRenderer::render() {
    glClearColor(0.2f, 0.2f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.use();

    auto transform = glm::mat4(1.0f);
    transform =
        glm::rotate(transform, glm::radians(-90.0f), glm::vec3(0.0, 0.0, 1.0));
    transform = glm::scale(transform, glm::vec3(0.5, 0.5, 0.5));

    unsigned transformLoc = glGetUniformLocation(shader.getId(), "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

    glBindTexture(GL_TEXTURE_2D, texture.getId());

    for (auto& it : meshBufferMap) {
        LOG_DEBUG("OpenGL", "Rendering VAO " << it.second.vao);
        glBindVertexArray(it.second.vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glBindVertexArray(0);
    }

    glfwSwapBuffers(m_Window);
    glfwPollEvents();

    if (glfwWindowShouldClose(m_Window)) {
        Engine::getInstance()->stop();
    }
}

void OpenGLRenderer::stop() {
    LOG_INFO("OpenGL", "Terminating GLFW");

    glfwTerminate();
}

void OpenGLRenderer::addMesh(const Mesh& mesh) {
    BufferIDs bufferIDs = createBuffers(mesh);
    meshBufferMap[&mesh] = bufferIDs;
}

BufferIDs OpenGLRenderer::createBuffers(const Mesh& mesh) {
    BufferIDs bufferIDs{};

    // Generate and bind VAO
    glGenVertexArrays(1, &bufferIDs.vao);
    glBindVertexArray(bufferIDs.vao);

    // Generate and bind VBO
    glGenBuffers(1, &bufferIDs.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, bufferIDs.vbo);
    glBufferData(GL_ARRAY_BUFFER, mesh.getVerticesSize() * sizeof(float),
                 mesh.getVertices(), GL_STATIC_DRAW);

    // Generate and bind EBO
    glGenBuffers(1, &bufferIDs.ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferIDs.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.getIndicesSize(),
                 mesh.getIndices(), GL_STATIC_DRAW);

    // TODO: The stride we take right now isn't very universal. Consider
    // changing! Setup position attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void*)nullptr);
    glEnableVertexAttribArray(0);

    // Setup texture attributes
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    LOG_INFO("OpenGL", "Created new buffers for mesh - vao: "
                           << bufferIDs.vao << ", vbo: " << bufferIDs.vbo
                           << ", ebo: " << bufferIDs.ebo);

    return bufferIDs;
}
