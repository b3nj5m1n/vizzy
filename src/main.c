#include <stdio.h>
#include <stdlib.h>
#define GLFW_INCLUDE_NONE
#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct config {
  GLFWwindow *window;
};

static void key_callback(GLFWwindow *window, int key, int scancode, int action,
                         int mods) {
  if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q) && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  printf("Key pressed.\n");
}

struct config *init() {
  struct config *config = (struct config *)malloc(sizeof(struct config));
  if (!glfwInit()) {
    printf("Initialization of GLFW failed.\n");
    exit(1);
  }
  GLFWwindow *window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
  if (!window) {
    printf("Failed to create window and OpenGL context.\n");
    exit(1);
  }
  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, key_callback);
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);
  config->window = window;
  return config;
}

void destruct(struct config *config) {
  glfwDestroyWindow(config->window);
  glfwTerminate();
}

void main_loop(struct config *config) {
  while (!glfwWindowShouldClose(config->window)) {
    glfwPollEvents();
  }
}

int main() {
  struct config *config = init();
  main_loop(config);
  destruct(config);
  return 0;
}
