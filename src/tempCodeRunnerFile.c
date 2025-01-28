#include<stdio.h>// it is used to manage input and output
#include<GL/glut.h> // it is used to create a window and input 


void Draw() // it is used to draw graphics on the screen
{
glClear(GL_COLOR_BUFFER_BIT);// it is clear the window color which is used previously
glBegin(GL_LINES);
glVertex2d(300,300);
glVertex2d(100,100);
glEnd();
glFlush();



}

int main(int argc,char** argv)
{
glutInit(&argc , argv);
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
glutInitWindowPosition(0,0);// these lines are used to place window at the top of the the screen
glutInitWindowSize(640,480);
glutCreateWindow(" Draw ");
glClearColor(1.0,1.0,1.0,0);
glColor3f(0.0,0.0,1.0);
gluOrtho2D(0,640,0,480);
glutDisplayFunc(Draw);
glutMainLoop();
return 0;

}
// gcc app.c glad.c -o app -I"d:\Programs\CG\include" -L"d:\Programs\CG\lib" -lfreeglut -lopengl32 -lgdi32 -o app.exe
//gcc app.c glad.c -o app -I"d:\Programs\CG\include" -L"d:\Programs\CG\lib" -lglfw3dll -lopengl32 -lgdi32

/*#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

// Callback function to adjust the viewport when the window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        printf("Failed to initialize GLFW\n");
        return -1;
    }

    // Set GLFW window properties
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // OpenGL version 3.x
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);  
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Basic OpenGL Window", NULL, NULL);
    if (window == NULL) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);  // Make the window's context current

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize GLAD\n");
        return -1;
    }

    // Set the viewport
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Main render loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the screen with a color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap the buffers and poll for events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up and terminate GLFW
    glfwTerminate();
    return 0;
}
*/

