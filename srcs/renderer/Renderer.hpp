#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Object.hpp>
#include <ProgramShader.hpp>
#include <Texture.hpp>
#include <Camera.hpp>

#define SCR_WIDTH 1920
#define SCR_HEIGHT 1080

// Vertex layout constants
#define VERTEX_STRIDE (8 * sizeof(float))
#define POSITION_COMPONENTS 3
#define COLOR_COMPONENTS 3
#define TEXTURE_COMPONENTS 2
#define POSITION_OFFSET 0
#define COLOR_OFFSET (3 * sizeof(float))
#define TEXTURE_OFFSET (6 * sizeof(float))

// Rendering constants
#define ROTATION_SPEED 0.005f
#define FOV_DEGREES 45.0f
#define NEAR_PLANE 0.1f
#define FAR_PLANE 100.0f

struct RenderData
{
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	size_t indexCount;
	glm::vec3 centroid;
	bool isInitialized;

	RenderData() : VAO(0), VBO(0), EBO(0), indexCount(0), 
				   centroid(0.0f), isInitialized(false) {}
};

class Renderer
{
	private:
		GLFWwindow			*_window;
		Camera				_camera;
		bool				_useTexture;
		float				_rotationAngle;
		
		std::unique_ptr<ProgramShader>	_shader;
		std::unique_ptr<Texture>		_texture;
		RenderData						_renderData;

		// Initialization methods
		bool	initialize_OpenGL(void);
		void	setup_window(void);
		void	setup_callbacks(void);

		// Object processing methods
		void	prepare_object_data(const Object &obj);
		void	generate_vertex_data(const Object &obj, std::vector<float> &vertices, std::vector<unsigned int> &indices);
		void	calculate_centroid(const Object &obj);
		void	setup_buffers(const std::vector<float> &vertices, const std::vector<unsigned int> &indices);
		void	setup_vertex_attributes();

		// Rendering methods
		void	update_matrices(void);
		void	draw_frame(void);
		void	cleanup_render_data(void);

	public:
		Renderer(void);
		Renderer(const Renderer &copy) = delete;
		Renderer	&operator=(const Renderer &op) = delete;
		~Renderer(void);

		bool			initialize(void);
		void			render(const Object &obj);
		void			process_input(GLFWwindow *window);
		static void		scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
};
