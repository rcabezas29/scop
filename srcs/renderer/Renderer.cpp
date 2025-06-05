#include <Renderer.hpp>

void	framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
}

void	processInput(GLFWwindow *window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

Renderer::Renderer()
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
		return ;
	}
	glfwMakeContextCurrent(this->_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return ;
	}
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(this->_window, framebuffer_size_callback);
}

Renderer::Renderer(const Renderer &copy)
{
	(void)copy;
}

Renderer	&Renderer::operator=(const Renderer &op)
{
	if (this == &op)
		return *this;
	return *this;
}

Renderer::~Renderer(void)
{
	glfwTerminate();
}

void	Renderer::render(const Object &obj)
{
	Shader			shader(SHADER_VERTEX, SHADER_FRAGMENT);
	unsigned int	VBO, VAO, EBO;

	// Create and compile the vertex shader
	shader.use();

	std::vector<Vertex>		vertices_vec = obj.get_vertices();
	std::vector<int>		indices_vec;
	for (const Face *face : obj.get_faces())
	{
		for (const int &index : face->indices)
		{
			indices_vec.push_back(index - 1); // Get the index of the vertex in the vertices vector
			// TODO: Add texture Vertex
		}
	}

	// unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices_vec.size() * 3, vertices_vec.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices_vec.size(), indices_vec.data(), GL_STATIC_DRAW);

	// Now set the vertex attributes pointers
	// The glVertexAttribPointer function is used to define an array of generic vertex attributes.
	// The first parameter is the index of the vertex attribute (0 in this case).
	// The second parameter is the size of the vertex attribute (3 for vec3).
	// The third parameter is the data type of the vertex attribute (GL_FLOAT for float).
	// The fourth parameter specifies whether fixed-point data values should be normalized (GL_FALSE means no normalization).
	// The fifth parameter specifies the stride (the byte offset between consecutive attributes).
	// The last parameter specifies the offset of the first component of the first attribute in the array.
	// specify the location and data format of the array of generic vertex attributes at index
	// 0, which is the position attribute in the vertex shader.
	// 3 is the size of the vertex attribute (vec3 = 3 floats), GL_FLOAT is the data type of the vertex attribute,
	// GL_FALSE means that the data should not be normalized, and the last parameter is the stride and offset.
	// In this case, the stride is 3 * sizeof(float) because each vertex consists of 3 floats (x, y, z),
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

	while (!glfwWindowShouldClose(this->_window))
	{
		processInput(this->_window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader.getID());
		glBindVertexArray(VAO);

		double  timeValue = glfwGetTime();
		float greenValue = static_cast<float>(sin(timeValue) / 2.0 + 0.5);
		int vertexColorLocation = glGetUniformLocation(shader.getID(), "color");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		// glDrawArrays(GL_TRIANGLES, 0, obj.get_faces().size() * 3); // Assuming each vertex has 3 components (x, y, z)
		glDrawElements(GL_TRIANGLES, obj.get_faces().size() * 3, GL_UNSIGNED_INT, 0); // Draw the triangles using the indices

		glfwSwapBuffers(this->_window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
    glDeleteProgram(shader.getID());
}
