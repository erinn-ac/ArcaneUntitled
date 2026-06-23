#include "config.h"

int main() {

  GLFWwindow* window;

  if (!glfwInit()) {
    std::cout << "Failed to initialize GLFW" << std::endl;
    return -1;
  }

  window = glfwCreateWindow(800, 600, "My Window", NULL, NULL);

  while(!glfwWindowShouldClose(window)) {
    glfwPollEvents();

  }
  glfwTerminate();

  return 0;
}