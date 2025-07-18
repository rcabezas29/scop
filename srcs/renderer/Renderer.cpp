#include <Renderer.hpp>

unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
}

void	Renderer::scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
	(void)xoffset;	
	// Get the renderer instance from the window user pointer
	Renderer* renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
	if (renderer)
		renderer->_camera.processScroll(static_cast<float>(yoffset));

	// This function is not used in the current implementation, but can be used to handle scroll input.
}

void Renderer::processInput(GLFWwindow *window)
{
	static bool keyPressed = false;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
	{
		if (!keyPressed)
		{
			keyPressed = true;
			this->_useTexture = !this->_useTexture;
		}
	}
	else
		keyPressed = false;
}

Renderer::Renderer() : _useTexture(true)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	this->_window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (this->_window == NULL)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(this->_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return;
	}
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(this->_window, framebuffer_size_callback);
	glfwSetWindowUserPointer(this->_window, this);
	glfwSetScrollCallback(this->_window, Renderer::scroll_callback);
	this->_object_centroid = glm::vec3(0.0f, 0.0f, 0.0f);
}

Renderer::Renderer(const Renderer &copy)
{
	(void)copy;
}

Renderer &Renderer::operator=(const Renderer &op)
{
	if (this == &op)
		return *this;
	return *this;
}

Renderer::~Renderer(void)
{
	glfwTerminate();
}

void Renderer::render(const Object &obj)
{
	ProgramShader	shader;
	Texture			texture;
	glm::mat4		model(1.0f), view(1.0f), projection(1.0f);
	float			rotationAngle = 0.0f;
	unsigned int	VBO, VAO, EBO;

	std::vector<float> vertices_data;
	std::vector<unsigned int> indices_vec;
	float texCoord[] = {
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f};

	for (const Face *face : obj.get_faces())
		for (const int &index : face->indices)
			indices_vec.push_back(index - 1); // Get the index of the vertex in the vertices vector
	srand(time(NULL));
	int i = 0;
	for (const Vertex &vertex : obj.get_vertices())
	{
		vertices_data.push_back(vertex.x);
		vertices_data.push_back(vertex.y);
		vertices_data.push_back(vertex.z);

		vertices_data.push_back(((double)rand()) / RAND_MAX); // Red
		vertices_data.push_back(((double)rand()) / RAND_MAX); // Green
		vertices_data.push_back(((double)rand()) / RAND_MAX); // Blue

		vertices_data.push_back(texCoord[i % 8]); // U coordinate
		++i;
		vertices_data.push_back(texCoord[i % 8]); // V coordinate
		++i;
	}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices_data.size(), vertices_data.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices_vec.size(), indices_vec.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	std::vector<Vertex>		vertices = obj.get_vertices();
	for (const Vertex& vertex : vertices)
	{
		this->_object_centroid.x += vertex.x;
		this->_object_centroid.y += vertex.y;
		this->_object_centroid.z += vertex.z;
	}
	if (!vertices.empty())
		this->_object_centroid /= static_cast<float>(vertices.size());

	projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	
	while (!glfwWindowShouldClose(this->_window))
	{
		this->processInput(this->_window);
		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDepthFunc(GL_LESS);
		
		glBindTexture(GL_TEXTURE_2D, texture.get_id());
		
		shader.setInt("aIsTexture", this->_useTexture ? 1 : 0);
		shader.use();
		
		rotationAngle += 0.005f;
		view = this->_camera.getViewMatrix();
		model = glm::mat4(1.0f);
		model = glm::rotate(model, rotationAngle, glm::vec3(0.0f, 1.0f, 0.0f));  // Rotate around Y axis
		model = glm::translate(model, -this->_object_centroid);  // Center the object at origin

		unsigned int modelLoc = glGetUniformLocation(shader.getID(), "model");
		unsigned int viewLoc = glGetUniformLocation(shader.getID(), "view");

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
		shader.setMat4("projection", projection);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, obj.get_faces().size() * 3, GL_UNSIGNED_INT, 0); // Draw the triangles using the indices

		glfwSwapBuffers(this->_window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shader.getID());
}
