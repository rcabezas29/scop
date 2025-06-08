#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include <cstring>
#include "structs/Face.hpp"
#include "MTLParser.hpp"
#include "Object.hpp"

class ObjParser
{
	private:
		std::vector<Face*>						_faces;
		std::vector<Vertex>						_vertices;
		std::vector<Vertex>						_texture_vertices;
		std::vector<std::pair<Vertex, Vertex> >	_lines;
		std::vector<Material>					_materials;

	public:
		ObjParser(const std::string file);
		virtual ~ObjParser(void);

		void	parse_vertex(const char *line);
		void	parse_texture_vertices(const char *line);
		void	parse_line(const char *line);
		void	parse_face(const char *line);
		void	parse_materials_file(const std::string line);
		Object	generate_object(void) const;

		class ParsingObjectException : public std::exception {
            private:
                const std::string message;

            public:
                ParsingObjectException(const std::string e) : message(e) {}
                virtual ~ParsingObjectException() throw() {}
                virtual const char * what() const throw()
                {
                    return this->message.c_str();
                }
        };
};
