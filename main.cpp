#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <exception>
#include "include/shader.h"
#include "include/triangle.h"
#include "include/line.h"
#include "deps/stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// ���������
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

/*
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
*/

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL for Ravesli.com", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader shaders("./shader.vert", "./shader.frag");
    if(!shaders.AreShadersOk())
        std::cout<<"Shaders errors:"<<shaders.GetErrorMessage()<<std::endl;


    // ���������������� ��������� ������ ��� ��������� ��������� � ������ �������
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    Triangle triangle(Point(-0.5f, -0.5f, 0.0f),
                      Point(0.5f, -0.5f, 0.0f),
                      Point(0.0f,  0.2f, 0.0f));
    triangle.SetTextureCoordinates(Point(0.2f, 0.2f, 0.0f),
                                   Point(0.8f, 0.2f, 0.0f),
                                   Point(0.6f, 0.5f, 0.0f));
    triangle.CreateGeometry();

    //Line line(Point(-0.5,-0.5,0.0), Point(0.5,0.5,0.0));
    //line.CreateGeometry();


    // Textures
    int width, height, nrChannels;
    unsigned char *data = stbi_load("8_9.jpg", &width, &height, &nrChannels, 0);
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout<<"Error on texture loading..."<<std::endl;
    }

    stbi_image_free(data);

    // ���� ����������
    while (!glfwWindowShouldClose(window))
    {
        // ��������� �����
        processInput(window);

        float time = glfwGetTime();
        float green = sin(time) / 2.0f + 0.5f;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaders.Use();
        shaders.SetUniformV4("current_colour", 0.0f, green, 0.0f, 1.0f);
        shaders.SetUniformFloat("shift", green);

        triangle.Refresh();
        triangle.Draw();

        //line.Refresh();
        //line.Draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

// ��������� ���� ������� �����: ������ GLFW � �������/���������� ������ ���� � ������ ����� � ��������������� ��������� ������ �������
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: ������ ���, ����� ���������� ������� ���� (������������� ��� ������������ ��������), ���������� ������ callback-�������
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // ����������, ��� ���� ��������� ������������� ����� �������� ����.
    // �������� ��������, ������ ���� �� Retina-�������� ����� ����������� ������, ��� ������� � ���������
    glViewport(0, 0, width, height);
}
