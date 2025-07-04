#include <Renderer.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
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
	ProgramShader shader;
	unsigned int VBO, VAO, EBO;

	// shader.use();

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
		// Assuming the color is white for now, you can modify this to use actual colors if needed

		vertices_data.push_back(((double)rand()) / RAND_MAX); // Red
		vertices_data.push_back(((double)rand()) / RAND_MAX); // Green
		vertices_data.push_back(((double)rand()) / RAND_MAX); // Blue
		// Assuming texture coordinates are (0.0f, 0.0f) for now, you can modify this to use actual texture coordinates if needed
		vertices_data.push_back(texCoord[i++]);
		vertices_data.push_back(texCoord[i++]);
	}

	// unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices_data.size(), vertices_data.data(), GL_STATIC_DRAW);

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// load and create a texture
	// -------------------------
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char *data = stbi_load(TEXTURE_PATH, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	while (!glfwWindowShouldClose(this->_window))
	{
		processInput(this->_window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindTexture(GL_TEXTURE_2D, texture);

		shader.use();
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
