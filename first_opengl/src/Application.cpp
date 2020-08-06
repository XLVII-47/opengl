#include <iostream>

#include<glad/glad.h>

#include<GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "shaderprogram.hpp"
#include "Square.hpp"
#include "Texture.hpp"
#include "camera.hpp"
#include<vector>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

glm::vec3 lightPos(1.2f, 0.0f, 2.0f);

float vertices[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};



int main(int argc, char** argv)
{
	if (!glfwInit())
		return -1;


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "hzlm", NULL, NULL);


	if (window == NULL)
	{
		std::cout << "Pencere Olusturulamadi" << std::endl;

		glfwTerminate();

		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	
	ShaderProgram program;
	program.attachShader("./shaders/vs.glsl", GL_VERTEX_SHADER);
	program.attachShader("./shaders/fs.glsl", GL_FRAGMENT_SHADER);
	program.link();

	ShaderProgram light;
	light.attachShader("./shaders/lightcubevs.glsl", GL_VERTEX_SHADER);
	light.attachShader("./shaders/lightcubefs.glsl", GL_FRAGMENT_SHADER);
	light.link();


	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	// glBindVertexArray(0);
	/*
	program.use();
	program.addUniform("model");
	program.addUniform("view");
	program.addUniform("projection");
	program.addUniform("material");
	program.addUniform("light");
	program.addUniform("viewPos");

	light.use();
	light.addUniform("model");
	light.addUniform("view");
	light.addUniform("projection");
	*/
	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	// we only need to bind to the VBO, the container's VBO's data already contains the data.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	// set the vertex attribute 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	

	program.use();
	program.setInt("material.diffuse", 0);
	program.setInt("material.specular", 1);
	Texture textures;
	unsigned int diffuseMap = textures.load_texture("./images/container2.jpg");
	unsigned int specularMap = textures.load_texture("./images/container3.jpg");

	glm::mat4 proj = glm::perspective(glm::radians(90.0f), (float)800 / (float)800, 0.1f, 100.0f);

	glEnable(GL_DEPTH_TEST);

	glm::vec3 init[8];
	init[0] = glm::vec3(2.0f, 2.0f, -2.0f);
	init[1] = glm::vec3(2.0f, -2.0f, -2.0f);
	init[2] = glm::vec3(4.0f, 2.0f, -2.0f);
	init[3] = glm::vec3(4.0f, -2.0f, -2.0f);
	init[4] = glm::vec3(6.0f, 2.0f, -2.0f);
	init[5] = glm::vec3(6.0f, -2.0f, -2.0f);
	init[6] = glm::vec3(8.0f, 2.0f, -2.0f);
	init[7] = glm::vec3(8.0f, 8.0f, 8.0f);
	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};

	float angle = 0.02f;
	while (!glfwWindowShouldClose(window))
	{
		/*
		int height, width;
		glfwGetWindowSize(window, &width, &height);

		glViewport(0, 0, width, height);
		*/
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		processInput(window);



		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// create transformations
			
		glm::mat4 cam = camera.GetViewMatrix();

		glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		//transform = glm::translate(transform, init[0]);
		//transform = glm::rotate(transform, -(float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
			
		// get matrix's uniform location and set matrix
		program.use();//kullanılacak shader

		//program.setmat4("model", &transform);
		program.setmat4("view", &cam);
		program.setmat4("projection", &proj);

		program.setvec3("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
		program.setvec3("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
		program.setvec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		program.setvec3("light.position", lightPos);
		program.setFloat("light.constant", 1.0f);
		program.setFloat("light.linear", 0.09f);
		program.setFloat("light.quadratic", 0.032f);
		program.setvec3("light.position", camera.Position);
		program.setvec3("light.direction", camera.Front);
		program.setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
		// material properties

		/*
		   Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
		   the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
		   by defining light types as classes and set their values in there, or by using a more efficient uniform approach
		   by using 'Uniform buffer objects', but that is something we'll discuss in the 'Advanced GLSL' tutorial.
		*/
		// directional light
		program.setvec3("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
		program.setvec3("dirLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		program.setvec3("dirLight.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
		program.setvec3("dirLight.specular", glm::vec3(0.5f, 0.5f, 0.5f));
		// point light 1
		program.setvec3("pointLights[0].position", pointLightPositions[0]);
		program.setvec3("pointLights[0].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		program.setvec3("pointLights[0].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
		program.setvec3("pointLights[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		program.setFloat("pointLights[0].constant", 1.0f);
		program.setFloat("pointLights[0].linear", 0.09);
		program.setFloat("pointLights[0].quadratic", 0.032);
		// point light 2
		program.setvec3("pointLights[1].position", pointLightPositions[1]);
		program.setvec3("pointLights[1].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		program.setvec3("pointLights[1].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
		program.setvec3("pointLights[1].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		program.setFloat("pointLights[1].constant", 1.0f);
		program.setFloat("pointLights[1].linear", 0.09);
		program.setFloat("pointLights[1].quadratic", 0.032);
		// point light 3
		program.setvec3("pointLights[2].position", pointLightPositions[2]);
		program.setvec3("pointLights[2].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		program.setvec3("pointLights[2].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
		program.setvec3("pointLights[2].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		program.setFloat("pointLights[2].constant", 1.0f);
		program.setFloat("pointLights[2].linear", 0.09);
		program.setFloat("pointLights[2].quadratic", 0.032);
		// point light 4
		program.setvec3("pointLights[3].position", pointLightPositions[3]);
		program.setvec3("pointLights[3].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		program.setvec3("pointLights[3].diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
		program.setvec3("pointLights[3].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		program.setFloat("pointLights[3].constant", 1.0f);
		program.setFloat("pointLights[3].linear", 0.09);
		program.setFloat("pointLights[3].quadratic", 0.032);
		// spotLight
		program.setvec3("spotLight.position", camera.Position);
		program.setvec3("spotLight.direction", camera.Front);
		program.setvec3("spotLight.ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		program.setvec3("spotLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
		program.setvec3("spotLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		program.setFloat("spotLight.constant", 1.0f);
		program.setFloat("spotLight.linear", 0.09);
		program.setFloat("spotLight.quadratic", 0.032);
		program.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
		program.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));




	
		//program.setvec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f)); // specular lighting doesn't have full effect on this object's material
		program.setFloat("material.shininess", 64.0f);

		program.setvec3("viewPos", camera.Position);
		textures.activatetexture(GL_TEXTURE0, diffuseMap);
		textures.activatetexture(GL_TEXTURE1, specularMap);
		glBindVertexArray(VAO);
		for (unsigned int i = 0; i < 8; i++)
		{
			// calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, init[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			program.setmat4("model", &model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		

		

		glBindVertexArray(lightVAO);
		for (unsigned int i = 0; i < 4; i++)
		{
			glm::mat4 transform = glm::mat4(1.0f);
			transform = glm::translate(transform, pointLightPositions[i]);
			transform = glm::scale(transform, glm::vec3(0.2f)); // Make it a smaller cube
			light.use();
			light.setmat4("model", &transform);
			light.setmat4("view", &cam);
			light.setmat4("projection", &proj);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime * 2);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime * 2);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime * 2);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime * 2);
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset*1.5, yoffset*1.5);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
