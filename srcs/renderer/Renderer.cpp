#include <Renderer.hpp>

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
}

void	Renderer::scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
	(void)xoffset;
	Renderer *renderer = static_cast<Renderer *>(glfwGetWindowUserPointer(window));
	if (renderer)
		renderer->_camera.processScroll(static_cast<float>(yoffset));
}

void	Renderer::process_input(GLFWwindow *window)
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

Renderer::Renderer(void) : _window(nullptr), _useTexture(true), _rotationAngle(0.0f) {}

Renderer::~Renderer(void)
{
	cleanup_render_data();
	if (this->_window)
		glfwTerminate();
}

bool	Renderer::initialize(void)
{
	if (!initialize_OpenGL())
	{
		std::cerr << "Failed to initialize OpenGL" << std::endl;
		return false;
	}
	setup_window();
	setup_callbacks();
	try
	{
		this->_shader = std::make_unique<ProgramShader>();
		this->_texture = std::make_unique<Texture>();
	}
	catch (const std::exception &e)
	{
		std::cerr << "Failed to initialize shader or texture: " << e.what() << std::endl;
		return false;
	}
	return true;
}

bool	Renderer::initialize_OpenGL(void)
{
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return false;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	return true;
}

void	Renderer::setup_window(void)
{
	this->_window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "SCOP - 3D Object Viewer", NULL, NULL);
	if (!this->_window)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return ;
	}
	glfwMakeContextCurrent(this->_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return;
	}

	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
}

void Renderer::setup_callbacks(void)
{
	glfwSetFramebufferSizeCallback(this->_window, framebuffer_size_callback);
	glfwSetWindowUserPointer(this->_window, this);
	glfwSetScrollCallback(this->_window, Renderer::scroll_callback);
}

void Renderer::prepare_object_data(const Object &obj)
{
	if (this->_renderData.isInitialized)
		cleanup_render_data();

	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	generate_vertex_data(obj, vertices, indices);
	calculate_centroid(obj);
	setup_buffers(vertices, indices);
	setup_vertex_attributes();

	this->_renderData.indexCount = indices.size();
	this->_renderData.isInitialized = true;
}

void Renderer::generate_vertex_data(const Object &obj, std::vector<float> &vertices, std::vector<unsigned int> &indices)
{
	// Generate indices
	for (const Face *face : obj.get_faces())
		for (const int &index : face->indices)
			indices.push_back(index - 1); // Convert to 0-based indexing

	// Find max Y and Z for texture coordinate normalization
	float max_y = 0.0f, max_z = 0.0f;
	for (const Vertex &vertex : obj.get_vertices())
	{
		if (vertex.y > max_y) max_y = vertex.y;
		if (vertex.z > max_z) max_z = vertex.z;
	}

	// Avoid division by zero
	if (max_y == 0.0f) max_y = 1.0f;
	if (max_z == 0.0f) max_z = 1.0f;

	// Generate vertex data with positions, colors, and texture coordinates
	srand(time(NULL));
	for (const Vertex &vertex : obj.get_vertices())
	{
		// Position
		vertices.push_back(vertex.x);
		vertices.push_back(vertex.y);
		vertices.push_back(vertex.z);

		// Random color
		vertices.push_back(static_cast<float>(rand()) / RAND_MAX);
		vertices.push_back(static_cast<float>(rand()) / RAND_MAX);
		vertices.push_back(static_cast<float>(rand()) / RAND_MAX);

		// Texture coordinates
		vertices.push_back(vertex.y / max_y);
		vertices.push_back(vertex.z / max_z);
	}
}

void Renderer::calculate_centroid(const Object &obj)
{
	this->_renderData.centroid = glm::vec3(0.0f);
	const std::vector<Vertex> &vertices = obj.get_vertices();
	
	if (!vertices.empty())
	{
		for (const Vertex &vertex : vertices)
		{
			this->_renderData.centroid.x += vertex.x;
			this->_renderData.centroid.y += vertex.y;
			this->_renderData.centroid.z += vertex.z;
		}
		this->_renderData.centroid /= static_cast<float>(vertices.size());
	}
}

void Renderer::setup_buffers(const std::vector<float> &vertices, const std::vector<unsigned int> &indices)
{
	glGenVertexArrays(1, &this->_renderData.VAO);
	glGenBuffers(1, &this->_renderData.VBO);
	glGenBuffers(1, &this->_renderData.EBO);

	glBindVertexArray(this->_renderData.VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->_renderData.VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_renderData.EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}

void Renderer::setup_vertex_attributes()
{
	// Position attribute (location = 0)
	glVertexAttribPointer(0, POSITION_COMPONENTS, GL_FLOAT, GL_FALSE, VERTEX_STRIDE, (void*)POSITION_OFFSET);
	glEnableVertexAttribArray(0);

	// Color attribute (location = 1)
	glVertexAttribPointer(1, COLOR_COMPONENTS, GL_FLOAT, GL_FALSE, VERTEX_STRIDE, (void*)COLOR_OFFSET);
	glEnableVertexAttribArray(1);

	// Texture coordinate attribute (location = 2)
	glVertexAttribPointer(2, TEXTURE_COMPONENTS, GL_FLOAT, GL_FALSE, VERTEX_STRIDE, (void*)TEXTURE_OFFSET);
	glEnableVertexAttribArray(2);
}

void Renderer::render(const Object &obj)
{
	if (!this->_window || !this->_shader || !this->_texture)
	{
		std::cerr << "Renderer not properly initialized" << std::endl;
		return;
	}

	// Prepare object data if not already done
	if (!this->_renderData.isInitialized)
		this->prepare_object_data(obj);

	// Main rendering loop
	while (!glfwWindowShouldClose(this->_window))
	{
		this->process_input(this->_window);
		this->draw_frame();

		glfwSwapBuffers(this->_window);
		glfwPollEvents();
	}
}

void Renderer::draw_frame(void)
{
	// Clear the screen
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDepthFunc(GL_LESS);

	// Use shader and bind texture
	this->_shader->use();
	glBindTexture(GL_TEXTURE_2D, this->_texture->get_id());
	this->_shader->setInt("aIsTexture", this->_useTexture ? 1 : 0);

	// Update matrices
	this->update_matrices();

	// Draw the object
	glBindVertexArray(this->_renderData.VAO);
	glDrawElements(GL_TRIANGLES, this->_renderData.indexCount, GL_UNSIGNED_INT, 0);
}

void Renderer::update_matrices(void)
{
	// Update rotation
	this->_rotationAngle += ROTATION_SPEED;

	// Calculate matrices
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, this->_rotationAngle, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, -this->_renderData.centroid);

	glm::mat4 view = this->_camera.getViewMatrix();

	glm::mat4 projection = glm::perspective(
		glm::radians(FOV_DEGREES), 
		static_cast<float>(SCR_WIDTH) / static_cast<float>(SCR_HEIGHT), 
		NEAR_PLANE, 
		FAR_PLANE
	);

	// Set uniforms
	unsigned int modelLoc = glGetUniformLocation(_shader->getID(), "model");
	unsigned int viewLoc = glGetUniformLocation(_shader->getID(), "view");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	_shader->setMat4("projection", projection);
}

void Renderer::cleanup_render_data()
{
	if (this->_renderData.VAO != 0)
	{
		glDeleteVertexArrays(1, &this->_renderData.VAO);
		this->_renderData.VAO = 0;
	}
	if (this->_renderData.VBO != 0)
	{
		glDeleteBuffers(1, &this->_renderData.VBO);
		this->_renderData.VBO = 0;
	}
	if (this->_renderData.EBO != 0)
	{
		glDeleteBuffers(1, &this->_renderData.EBO);
		this->_renderData.EBO = 0;
	}
	this->_renderData.isInitialized = false;
}
