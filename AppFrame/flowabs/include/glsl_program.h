//
// by Jan Eric Kyprianidis <www.kyprianidis.com>
// Copyright (C) 2008-2011 Computer Graphics Systems Group at the
// Hasso-Plattner-Institut, Potsdam, Germany <www.hpi3d.de>
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// Modified by James Hung Kuo Chu in 2012/08/30
#pragma once

namespace flowabs
{
	class glsl_program 
	{
	public:
		glsl_program(const char *id, bool create = false);
		~glsl_program();

		void use();
		bool has_uniform( const char* name ) const;
		void set_uniform_1i( const char* name, int value );
		void set_uniform_1f( const char* name, float value );
		void set_uniform_2f( const char* name, float x, float y );
		void set_uniform_3f( const char* name, float x, float y, float z );

		void bind_sampler( const char* name, const texture_2d& tex, GLenum filter = GL_NEAREST );
		void draw( texture_2d *ca0, texture_2d *ca1 = 0, texture_2d *ca2 = 0, texture_2d *ca3 = 0);

		bool attach_shader( GLenum type, const char* source );
		bool attach_shader( GLuint sid );
		bool link();

		static void cleanup();

	private:
		glsl_program();
		glsl_program(const glsl_program&);
		GLuint m_id;
	};
}
