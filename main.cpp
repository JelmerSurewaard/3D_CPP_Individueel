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
#include "TextControl.h"
#include "io.h"

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

TextControl* textWriter;
io* fileWriter;
int score = 0;
bool collision;

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

    delete textWriter, fileWriter, window;

    for (Object* object : objects) {
        delete(object);
    }

    return 0;
}


void init()
{
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(window, true);
    });

    tigl::shader->enableLighting(true);
    tigl::shader->setLightCount(1);

    tigl::shader->setLightDirectional(0, false);
    tigl::shader->setLightPosition(0, glm::vec3(0, 5, 0));
    tigl::shader->setLightAmbient(0, glm::vec3(0.1f, 0.1f, 0.15f));
    tigl::shader->setLightDiffuse(0, glm::vec3(0.8f, 0.8f, 0.8f));
    tigl::shader->setLightSpecular(0, glm::vec3(0, 0, 0));
    tigl::shader->setShinyness(0.25f);

    tigl::shader->enableFog(true);
    tigl::shader->setFogExp(0.1f);

    camera = std::make_shared<Camera>(window);

    glEnable(GL_DEPTH_TEST);

    textWriter = new TextControl("C:/Windows/Fonts/times.ttf", 20, 1920.0f, 1080.0f);
    
    Road* road = new Road("Road", 1, glm::vec3(0, 0, 0));
    Character* player = new Character("Character", 0.25f, glm::vec3(-3.5, 0.25f, -0.15f), 0, 0, "x");

    Cactus* cactus = new Cactus("Cactus", 0.25f, glm::vec3(0, 0.25f, -0.15f), 0.01f, -0.01f, "x");

    Cactus* cactus2 = new Cactus("Cactus", 0.25f, glm::vec3(2, 0.25f, -0.15f), 0.01f, -0.01f, "x");

    DinoBird* dinoBird = new DinoBird("DinoBird", 2, glm::vec3(4, 0.75f, -0.15f), 0, -0.01f, "x");

    objects.push_back(dinoBird);
    objects.push_back(player);
    objects.push_back(cactus);
    objects.push_back(cactus2);
    objects.push_back(road);

}

static const double updatesPerSecond = 100.;
static double timer = 1 / updatesPerSecond;
double lastFrameTime = .0;

void update()
{

    tigl::shader->enableLighting(camera->lightning);

    if (!collision)
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
                // removes Cactus when it reaches end of the road
                if (cactus.position.x < -3.5)
                {
                    if (camera->arrowUp > 0)
                    {
                        score++;
                        collision = false;
                    }
                    else {
                        collision = true;
                    }
                    objects.remove(object);
                    delete(object);
                    break;
                }
                cactus.update();
            }
            if (object->name == "DinoBird")
            {
                DinoBird& dinoBird = dynamic_cast<DinoBird&>(*object);
                // removes DinoBird when it reaches end of the road
                if (dinoBird.position.x < -3.5)
                {
                    if (camera->arrowDown > 0)
                    {
                        score++;
                        collision = false;
                    }
                    else {
                        collision = true;
                    }
                    objects.remove(object);
                    delete(object);
                    break;
                }
                dinoBird.update();
            }
            if (object->name == "Character")
            {
                Character& character = dynamic_cast<Character&>(*object);
                // Jumps when arrowUp is pressed
                if (camera->arrowUp > 0)
                {
                    character.jump();
                    camera->arrowUp -= 1;
                }

                // Ducks when arrowDown is pressed
                if (camera->arrowDown > 0)
                {
                    character.duck();
                    camera->arrowDown -= 1;
                }

                // Stands when nothing is pressed
                if (camera->arrowDown == 0 && camera->arrowUp == 0)
                {
                    character.stand();
                }

                character.update();
            }

            if (objects.size() < 5)
            {
                int random = rand() % 2 + 1;

                if (random == 1)
                {
                    Cactus* cactus = new Cactus("Cactus", 0.25f, glm::vec3(3, 0.25f, -0.15f), 0.01f, -0.01f + (-0.001f * score), "x");
                    objects.push_back(cactus);
                }
                else {
                    DinoBird* dinoBird = new DinoBird("DinoBird", 2, glm::vec3(3, 0.75f, -0.15f), 0, -0.01f + (-0.001f * score), "x");
                    objects.push_back(dinoBird);
                }
            }
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
        if (object->name == "DinoBird")
        {
            DinoBird& dinoBird = dynamic_cast<DinoBird&>(*object);
            dinoBird.draw();
        }
        if (object->name == "Character")
        {
            Character& character = dynamic_cast<Character&>(*object);
            character.draw();
        }
    }

    //Write text on screen
    textWriter->setScale(5.0f);
    std::string scoreString = std::to_string(score);
    std::string highScoreString = fileWriter->readFile();
    textWriter->drawText("Score: " + scoreString, -85, -210);
    textWriter->drawText("HighScore: " + highScoreString, 50, -210);

    int highScoreInt =  std::stoi(highScoreString, nullptr, 0);

    if (score > highScoreInt)
    {
        fileWriter->writeFile(scoreString);
    }

    if (collision)
    {
        textWriter->drawText("You are Dead, try harder next time!", -210, 0);
    }
}