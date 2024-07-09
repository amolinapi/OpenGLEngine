#include "GLRender.h"
#include "GLWindow.h"
#include "GLCamera.h"
#include "GLGeometry.h"
#include "GLTexture.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>

glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
};

GLRender::GLRender()
{
    
}

void GLRender::renderLoop()
{
    //Z-BUFFER
    glEnable(GL_DEPTH_TEST);
    
    GLGeometry geo;
    geo.createGeometry();

    GLTexture tex;
    tex.createTexture();

    //Set value to uniforms on the shader
    geo.instance->ourShader.use();
    geo.instance->ourShader.setInt("texture1", 0);
    geo.instance->ourShader.setInt("texture2", 1);

    std::shared_ptr<GLCamera> sharedCamera = GLWindow::instance->getCamera();

    //RENDER LOOP
    while (!glfwWindowShouldClose(GLWindow::instance->getWindow()))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        sharedCamera->deltaTime = currentFrame - sharedCamera->lastFrame;
        sharedCamera->lastFrame = currentFrame;
        
        // INPUT
        GLWindow::instance->processInput();

        //RENDER
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //bind texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tex.getID());
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, tex.getID2());

        //DRAW
        geo.instance->ourShader.use();

        //TRANSFORMS
        glm::mat4 projection = glm::perspective(glm::radians(sharedCamera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        geo.instance->ourShader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = sharedCamera->GetViewMatrix();
        geo.instance->ourShader.setMat4("view", view);

        // render boxes
        glBindVertexArray(*geo.instance->getVAO());
        for (unsigned int i = 0; i < 10; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            geo.instance->ourShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        

        // Swap del buffer de color
        glfwSwapBuffers(GLWindow::instance->getWindow());
        //Checkear si algunos eventos han sido llamados
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, geo.instance->getVAO());
    glDeleteBuffers(1, geo.instance->getVBO());
    //glDeleteBuffers(1, geo.instance->getEBO());

    // Limpiar todo lo necesario antes de cerrar
    glfwTerminate();
}
