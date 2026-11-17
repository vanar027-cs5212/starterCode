#include <cstdlib>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "GLSL.h"

#include "Camera.h"

int CheckGLErrors(const char *s) {
  int errCount = 0;
  GLenum err;
  while ((err = glGetError()) != GL_NO_ERROR) {
    std::cerr << "OpenGL Error (" << s << "): 0x" << std::hex << err << std::dec << std::endl;
    errCount++;
  }
  return errCount;
}

struct vertexData {
    glm::vec3 pos;
    glm::vec3 color;
};

void ppos(const char *msg, Camera *camera) {
  auto pos = camera->getOrigin();
  printf("%s, pos: %f, %f, %f\n", msg, pos.x(), pos.y(), pos.z());
}

int main(void) {
  /* Initialize the library */
  if (!glfwInit()) {
    exit(-1);
  }
  // throw std::runtime_error("Error! initialization of glfw failed!");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  /* Create a windowed mode window and its OpenGL context */
  int winWidth = 1000;
  float aspectRatio = 1.0;// 16.0 / 9.0; // winWidth / (float)winHeight;
  int winHeight = winWidth / aspectRatio;

  GLFWwindow *window =
    glfwCreateWindow(winWidth, winHeight, "GLFW Example", NULL, NULL);
  if (!window) {
    std::cerr << "GLFW did not create a window!" << std::endl;

    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (err != GLEW_OK) {
    std::cerr << "GLEW Error! glewInit failed, exiting." << std::endl;
    exit(EXIT_FAILURE);
  }

  const GLubyte *renderer = glGetString(GL_RENDERER);
  const GLubyte *version = glGetString(GL_VERSION);
  std::cout << "Renderer: " << renderer << std::endl;
  std::cout << "OpenGL version supported: " << version << std::endl;

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glClearColor(0.4, 0.2, 0.6, 1.0);

  int fb_width, fb_height;
  glfwGetFramebufferSize(window, &fb_width, &fb_height);
  glViewport(0, 0, fb_width, fb_height);

  // Need to set a projection matrix that fits the aspect ratio set
  // by the window frame.
  //
  // The ortho parameters, in order: left, right, bottom, top, zNear, zFar
  float halfWidth = 15.0 / 2.0;
  float halfHeight = halfWidth / aspectRatio;
  float left = -halfWidth;
  float right = halfWidth;
  float bottom = -halfHeight;
  float top = halfHeight;
  float near = -5.0f;
  float far = 5.0f;
  glm::mat4 orthoMatrix =
    glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, near, far);

  float fov = glm::radians(45.0f);
  float zNear = 0.1f;
  float zFar = 100.0f;
  glm::mat4 perspMatrix = glm::perspective(fov, aspectRatio, zNear, zFar);

  // Toggle flag: start in perspective (or false for ortho)
  bool usePerspective = true,
       rotating = false;

  GLint major_version;
  glGetIntegerv(GL_MAJOR_VERSION, &major_version);
  std::cout << "GL_MAJOR_VERSION: " << major_version << std::endl;

  /* MAKE TRIANGLE VBO*/
  GLuint m_triangleVBO[2];
  // create a Vertex Array Buffer to hold our triangle data
  glGenBuffers(1, m_triangleVBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_triangleVBO[0]);

  // this is the actual triangle data that will be copied to
  // the GPU memory
  std::vector<vertexData> noProjectData{ // data that doesn't need projection to appear trianglish (for passthrough)
    {
      glm::vec3(-0.5f, -0.5f, 0.0f),// V0
      glm::vec3(0.1529f, 0.9608f, 0.5569f)// V0 color (#27F58E)
    },
    {
      glm::vec3(0.5f, -0.5f, 0.0f),// V1
      glm::vec3(0.5569f, 0.1529f, 0.9608f)// V1 color (#8E27F5)
    },
    {
      glm::vec3(0.0f, 0.5f, 0.0f),// V2
      glm::vec3(0.9608f, 0.5569f, 0.1529f)// V2 color (#F58E27)
    }
  };

  std::vector<vertexData> modelData{
    {
      glm::vec3(-3.0f, -3.0f, 0.0f),// V0
      glm::vec3(0.717647f, 0.368627f, 1.f)// V0 color (#B75EFF)
    },
    {
      glm::vec3(3.0f, -3.0f, 0.0f),// V1
      glm::vec3(1.0f, 0.717647f, 0.368627f)// V1 color (#FFB75E)
    },
    {
      glm::vec3(0.0f, 3.0f, 0.0f),// V2
      glm::vec3(0.368627f, 0.717647f, 1.0f)// V2 color (#5EB7FF)
    }
  };

  int numBytes = modelData.size() * sizeof(vertexData);

  // copy the numBytes from modelData t the GPU and store in
  // the currently bound VBO
  glBufferData(GL_ARRAY_BUFFER, numBytes, modelData.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // once copied, we no longer need the data on the host
  modelData.clear();
  /* MAKE TRIANGLE VAO */
  GLuint m_VAO;
  // create a vertex array object that will map the attributes in
  // our vertex buffer to different location attributes for our
  // shaders
  glGenVertexArrays(1, &m_VAO);
  glBindVertexArray(m_VAO);

  // VAO details here - we now have 2 attributes
  glBindBuffer(GL_ARRAY_BUFFER, m_triangleVBO[0]);
  // attr 0: Position of the vertex
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
  // attr 1: Color of the vertex
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (const GLvoid *)12);
  // bind
  glBindVertexArray(0);

  /* CREATE SHADERS*/
  // Create a shader using my GLSLObject class
  sivelab::GLSLObject shader;
  shader.addShader("shaders/vertexShader_withMatrixTransformation.glsl",
    sivelab::GLSLObject::VERTEX_SHADER);
  shader.addShader("shaders/fragmentShader_barycentricInterpolation.glsl",
    sivelab::GLSLObject::FRAGMENT_SHADER);
  shader.createProgram();

  // Uniform transformation matrices
  GLuint projMatrixID, viewMatrixID, modelMatrixID;
  projMatrixID = shader.createUniform("projMatrix");
  viewMatrixID = shader.createUniform("viewMatrix");
  modelMatrixID = shader.createUniform("modelMatrix");

  // Camera attributes
  // glm::vec3 m_pos(0, 0, 0.0f);
  glm::vec3 m_viewDir(0, 0, -1);
  // glm::vec3 m_U(1, 0, 0), m_V(0, 1, 0), m_W(0, 0, 1);

  Camera *camera = new PerspectiveCamera(Vec3(0, 0, 0.0f), Vec3(1, 0, 0), Vec3(0, 1, 0), Vec3(0, 0, 1), winWidth, winHeight);


  double timeDiff = 0.0,
         startFrameTime = 0.0, endFrameTime = 0.0;

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    endFrameTime = glfwGetTime();
    timeDiff = endFrameTime - startFrameTime;
    startFrameTime = glfwGetTime();

    // Clear the window's buffer (or clear the screen to our
    // background color)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 activeProjMatrix = orthoMatrix;
    if (usePerspective) {
      activeProjMatrix = perspMatrix * orthoMatrix;
    }
    // create the view matrix from our camera data
    glm::mat4 viewMatrix = camera->getViewMatrix();

    glm::mat4 modelMatrix = glm::mat4(1.0f);
    if (rotating) {
      modelMatrix = glm::rotate(modelMatrix, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
    }
    /* Render your objects here */
    shader.activate();


    // copy from the host to the device the view matrix and the projection matrix
    glUniformMatrix4fv(projMatrixID, 1, GL_FALSE, glm::value_ptr(activeProjMatrix));
    glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    shader.deactivate();

    // Swap the front and back buffers
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();

    float moveRatePerFrame = 0.05;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
      // move up
      camera->adjustPos(-1, camera->getV(), moveRatePerFrame);
      ppos("w pressed", camera);
    } else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
      // move down
      camera->adjustPos(1, camera->getV(), moveRatePerFrame);
      ppos("s pressed", camera);
    } else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
      // move left
      camera->adjustPos(1, camera->getU(), moveRatePerFrame);
      ppos("a pressed", camera);
    } else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
      // move right
      camera->adjustPos(-1, camera->getU(), moveRatePerFrame);
      ppos("d pressed", camera);
    } else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
      // move forward
      camera->adjustPos(1, camera->getW(), moveRatePerFrame);
      ppos("e pressed", camera);
    } else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
      // move backward
      camera->adjustPos(-1, camera->getW(), moveRatePerFrame);
      ppos("q pressed", camera);
    }
    // swap perspective mode
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
      usePerspective = true;
      auto m_pos = camera->getOrigin().to_glm();
      printf("Perspective mode enabled. m_pos: %f, %f, %f\n", m_pos.x, m_pos.y, m_pos.z);
    } else if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
      usePerspective = false;
      auto m_pos = camera->getOrigin().to_glm();
      printf("Orthographic mode enabled. m_pos: %f, %f, %f\n", m_pos.x, m_pos.y, m_pos.z);
    }
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
      rotating = !rotating;
      printf("toggled rotation: %s", rotating ? "true" : "false");
    }

    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
      std::cout << "fps: " << 1.0 / timeDiff << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, 1);
    }
  }

  glfwTerminate();
  return 0;
}
