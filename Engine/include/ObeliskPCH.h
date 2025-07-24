#pragma once

// Engine-wide definitions
#define CURRENT_LOG_LEVEL LOG_LEVEL_TRACE

// Enable GLM experimental extensions
#define GLM_ENABLE_EXPERIMENTAL

// C++ Standard Library
#include <functional>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

// OpenGL-related
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

// Engine-wide Macros
#include "Obelisk/Logging/Log.h"
#include "Obelisk/Macros.h"