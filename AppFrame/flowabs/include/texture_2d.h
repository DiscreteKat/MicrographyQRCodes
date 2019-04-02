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
	class texture_2d 
	{
	public:
		texture_2d() : m(0) {}

		texture_2d( GLint format, int w, int h, GLenum pixel_format = GL_BGRA, 
			GLenum pixel_type = GL_UNSIGNED_BYTE, GLvoid *pixel_data = 0 ) 
			: m( get_buffer( format, w, h ) )
		{ 
			glPushAttrib(GL_TEXTURE_BIT);
			glEnable(GL_TEXTURE_2D);

			GLint old_binding;
			glGetIntegerv(GL_TEXTURE_BINDING_2D, &old_binding);
			bind();
			set_wrap( GL_CLAMP, GL_CLAMP );
			set_filter( GL_NEAREST, GL_NEAREST );
			if (pixel_data || (m->format == -1)) {
				glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
				glTexImage2D( GL_TEXTURE_2D, 0, format, w, h, 0, pixel_format, pixel_type, pixel_data );
				m->w = w;
				m->h = h;
				m->format = format;
			}
			glBindTexture( GL_TEXTURE_2D, old_binding );

			glPopAttrib();
		}

		texture_2d( const texture_2d& img ) {
			m = img.m; 
			if (m) {
				++m->ref_count;
			}
		}

		~texture_2d() {
			if (m) {
				if ( --m->ref_count == 0 ) put_buffer( m );
			}
			m = 0;
		}

		const texture_2d& operator=( const texture_2d& img ) {
			if ( this != &img ) { 
				if (m) {
					if ( --m->ref_count == 0 ) put_buffer( m );
				}
				m = img.m; 
				if (m) {
					++m->ref_count;
				}
			}
			return *this;
		}

		texture_2d clone_format() const {
			if (!m) {
				return texture_2d();
			}
			return texture_2d(m->format, m->w, m->h);
		}

		bool is_valid() const {
			return m && m->id;
		}

		int get_width() const {
			return m->w;
		}

		int get_height() const {
			return m->h;
		}

		GLuint get_id() const { 
			return m->id; 
		}

		void bind() const {
			glBindTexture( GL_TEXTURE_2D, m->id );
		}

		/*
		void set_data( GLint format, int w, int h, 
		GLenum pixel_format, GLenum pixel_type, GLvoid *pixel_data ) 
		{
		glTexImage2D( GL_TEXTURE_2D, 0, format, w, h, 0, pixel_format, pixel_type, pixel_data );
		m->w = w;
		m->h = h;
		m->format = format;
		}
		*/

		void set_wrap( GLint wrap_s, GLint wrap_t ) {
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t );
		}

		void set_filter( GLint min_filter, GLint mag_filter ) {
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter );
		}

	public:
		struct buffer_t {
			int ref_count;
			GLuint id;
			GLint format;
			int w;
			int h;

			buffer_t() {
				ref_count = 1;
				glGenTextures(1, &id);
				format = -1;
				w = -1;
				h = -1;
			}

			~buffer_t() {
				ref_count = 0;
				glDeleteTextures(1, &id);
				id = 0;
				format = -1;
				w = -1;
				h = -1;
			}
		};

		static buffer_t* get_buffer( GLint format, int w, int h );
		static void put_buffer( buffer_t *b );
		static void cleanup();

		buffer_t *m;
	};
}
