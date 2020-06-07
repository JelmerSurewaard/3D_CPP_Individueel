#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include "ObjModel.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"
#include "Character.h"
#include "DinoBird.h"
#include "Cactus.h"
#include "Road.h"
#include "Object.h"

using tigl::Vertex;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

GLFWwindow* window;

std::shared_ptr<Camera> camera;

void init();
void update();
void draw();

std::list<Object*> objects;

int main(void)
{
    if (!glfwInit())
        throw "Could not initialize glwf";
    window = glfwCreateWindow(1400, 800, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        throw "Could not initialize glwf";
    }
    glfwMakeContextCurrent(window);

    tigl::init();

    init();

	while (!glfwWindowShouldClose(window))
	{
		update();
		draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

    return 0;
}


void init()
{
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(window, true);
    });

    camera = std::make_shared<Camera>(window);

    glEnable(GL_DEPTH_TEST);

    //steve.createCharacter("Steve", 1, glm::vec3(0, 0, 0), 0, 0.01f, "y");
    //bird.CreateDinoBird("Bird", 10, glm::vec3(0, 0, 0), 0, 0, "y");

    Cactus* cactus = new Cactus();
    cactus->createModel("Cactus", 1, glm::vec3(0, 0.25f, -0.50f), 0, 0.005f, "x");
    Road* road = new Road();
    road->createModel("Road", 1, glm::vec3(0, 0, 0));
    objects.push_back(cactus);
    objects.push_back(road);

}

static const double updatesPerSecond = 100.;
static double timer = 1 / updatesPerSecond;
double lastFrameTime = .0;

void update()
{

    for (Object* object : objects)
    {
        if (object->name == "Road")
        {
            Road& road = dynamic_cast<Road&>(*object);
            road.update();
        }
        if (object->name == "Cactus")
        {
            Cactus& cactus = dynamic_cast<Cactus&>(*object);
            cactus.update();
        }

        
    }

    
    

    double currentFrameTime = glfwGetTime();
    double deltaTime = currentFrameTime - lastFrameTime;
    lastFrameTime = currentFrameTime;

    timer -= deltaTime;
    if (timer <= 0) {
        timer = 1. / updatesPerSecond;
        camera->updateKeyInput(window);
        camera->checkTargetRadius();
        camera->checkTargetRotation();
    }
}

void draw()
{
    glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    glm::mat4 projection = glm::perspective(glm::radians(75.0f), viewport[2] / (float)viewport[3], 0.01f, 500.0f);

    tigl::shader->setProjectionMatrix(projection);
    tigl::shader->setViewMatrix(camera->getMatrix());
    //tigl::shader->setModelMatrix(glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0,1,0)));

    tigl::shader->enableColor(true);
    tigl::shader->enableTexture(true);

    glEnable(GL_DEPTH_TEST);
    
    for (Object* object : objects)
    {
        if (object->name == "Road")
        {
            Road& road = dynamic_cast<Road&>(*object);
            road.draw();
        }
        if (object->name == "Cactus")
        {
            Cactus& cactus = dynamic_cast<Cactus&>(*object);
            cactus.draw();
        }

        //object.update();
    }

}