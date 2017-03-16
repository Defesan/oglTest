#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <string>

#include "SDL2/SDL.h"
#include "SDL2/SDL_test_common.h"

#if defined(__IPHONEOS__) || defined(__ANDROID__)
#define USING_OPENGLES
#endif

#ifdef USING_OPENGLES
#include "SDL_opengles.h"
#else
#include "SDL2/SDL_opengl.h"
#endif

bool init(SDL_GLContext** context, SDLTest_CommonState** state, int argc, char* argv[]);
void shutdown(SDL_GLContext* context, SDLTest_CommonState* state, int val);
void render();

int main(int argc, char* argv[])
{
	SDLTest_CommonState* state = NULL;
	SDL_GLContext* context = NULL;
	SDL_DisplayMode mode;
	SDL_Event event;
	std::fstream debug ("debug.txt", std::fstream::app);

	if(!init(&context, &state, argc, argv))
	{
		if(context && state)
		{
			shutdown(context, state, 1);
		}
	}
	
	SDL_GetCurrentDisplayMode(0, &mode);
	
	//Set rendering state for each window
	for(int i = 0; i < state->num_windows; i++)
	{
		#ifdef USING_OPENGLES
		state->window_w = mode.w;
		state->window_h = mode.h;
		#else
		state->window_w = 640;
		state->window_h = 640;
		#endif
		
		debug << state->window_w << std::endl << state->window_h << std::endl << std::endl;
		
		float aspectMod = 2.0f * (state->window_h / state->window_w);
		
		glViewport(0,0,state->window_w, state->window_h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		
		#ifdef USING_OPENGLES
		glOrthof(-2.0f, 2.0f, -1 * aspectMod, aspectMod, -2.0f, 2.0f);
		#else
		glOrtho(-2.0f, 2.0f, -1 * aspectMod, aspectMod, -2.0f, 2.0f);
		#endif
		
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glShadeModel(GL_SMOOTH);
	}
	//okay, so now everything should be set up.
	bool done = false;
	while(!done)
	{
		while(SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				#ifndef USING_OPENGLES
				//For now, only the desktop version handles any events. Still, I'd like to keep the option open, in case I find some I want to put on mobile, or on both.
				case SDL_WINDOWEVENT:
					switch (event.window.event)
					{
						case SDL_WINDOWEVENT_RESIZED:
							for(int i = 0; i < state->num_windows; i++)
							{
								if(event.window.windowID == SDL_GetWindowID(state->windows[i]))
								{
									int status = SDL_GL_MakeCurrent(state->windows[i], context[i]);
									if(status)
									{
										//We're in serious Inception territory, here. I mean, while->while->switch->case->switch->case->for->if->if!!!
										std::cout << "SDL_GL_MakeCurrent error: " << SDL_GetError() << std::endl;
										break;
									}
									glViewport(0,0,event.window.data1, event.window.data2);
									render();
									SDL_GL_SwapWindow(state->windows[i]);
									break;
								
								}
							
							}
							break;
							
						default:
							break;
					}
					
				case SDL_KEYUP:
					switch (event.key.keysym.scancode)
					{
						case SDL_SCANCODE_Q:
							done = true;
							break;
						
						default:
							break;
					}
					break;
					
				default:
					break;
				#endif
			}
		
		}
		for(int i = 0; i < state->num_windows; i++)
		{
		    render();
		    SDL_GL_SwapWindow(state->windows[i]);
		}
	}
	
	shutdown(context, state, 0);
	debug.close();
	return 0;
}

bool init(SDL_GLContext** context, SDLTest_CommonState** state, int argc, char* argv[])
{
	SDLTest_CommonState* tState = SDLTest_CommonCreateState(argv, SDL_INIT_VIDEO);
	SDL_GLContext* tContext = NULL;
	
	
	for(int i = 1; i < argc;)
	{
		int consumed = SDLTest_CommonArg(tState, i);
		std::cout << "CommonArg consumed " << consumed << " items." << std::endl;
		if(consumed == 0)
		{
			//Basically, i is is still less than the total number of arguments, but SDLTest_CommonArg couldn't find anything in there, so there's something there shouldn't be. Right?
			std::cerr << "Usage: " << argv[0] << SDLTest_CommonUsage(tState) << std::endl;
			return false;
		}
		i += consumed;
	}
	
	tState->window_flags |= SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS;
	
	#ifndef USING_OPENGLES
	tState->window_flags |= SDL_WINDOW_RESIZABLE;
	#endif
	
	//Having looked at the defaults, I think the rest is fine for now.
	
	if(!SDLTest_CommonInit(tState))
	{
		std::cerr << "Failed to initialize SDL state: " << SDL_GetError() << std::endl;
		return false;
	}
	
	tContext = (void**)SDL_calloc(tState->num_windows, sizeof(tContext));
	if(tContext == NULL)
	{
		std::cerr << "Out of memory." << std::endl;
	}
	
	#ifdef USING_OPENGLES
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
	#else
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	#endif
	
	for(int i = 0; i < tState->num_windows; i++)
	{
		tContext[i] = SDL_GL_CreateContext(tState->windows[i]);	
		if(!tContext[i])
		{
			std::cerr << "Could not create context: " << SDL_GetError() << std::endl;
			return false;
		}
	}
	
	if(tState->render_flags & SDL_RENDERER_PRESENTVSYNC)
	{
		SDL_GL_SetSwapInterval(1);
	}
	else
	{
		SDL_GL_SetSwapInterval(0);
	}
	
	*state = tState;
	*context = tContext;
	return true;
}


void shutdown(SDL_GLContext* context, SDLTest_CommonState* state, int val)
{
	if(context != NULL)
	{
		for(int i = 0; i < state->num_windows; i++)
		{
			if(context[i])
			{
				SDL_GL_DeleteContext(context[i]);
			}
		}
		SDL_free(context);
	}
	
	SDLTest_CommonQuit(state);
	exit(val);
}

void render()
{
	//Let's try rendering a cube
	
	//We need eight vertices.
	static GLfloat verts[8][3] =
	{
		{0.5f, 0.5f, 0.5f},
		{0.5f, -0.5f, 0.5f},
		{-0.5f, 0.5f, 0.5f},
		{-0.5f, -0.5f, 0.5f},
		{0.5f, 0.5f, -0.5f},
		{0.5f, -0.5f, -0.5f},
		{-0.5f, 0.5f, -0.5f},
		{-0.5f, -0.5f, -0.5f}
	};
	
	//Varied colors, but muted. Except for 7, who's an oddball.
	static GLubyte colors[8][4] =
	{
		{150, 0, 0, 255},
		{0, 150, 0, 255},
		{0, 0, 150, 255},
		{150, 150, 0, 255},
		{150, 150, 150, 255},
		{0, 150, 150, 255},
		{0, 0, 0, 255},
		{255, 255, 255, 255}
	};
	//And there are twelve triangles. Here...things get tricky.
	static GLubyte indices[36] =
	{ 0, 1, 3, 
	  0, 2, 3,
	  0, 2, 6,
	  0, 4, 6,
	  1, 0, 4,
	  1, 5, 4,
	  6, 7, 5,
	  6, 4, 5,
	  3, 1, 5,
	  3, 7, 5,
	  2, 3, 7,
	  2, 6, 7 };
	//I...think?

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glColorPointer(4, GL_UNSIGNED_BYTE, 0, colors);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, verts);
	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, indices);
	
	glMatrixMode(GL_MODELVIEW);
	glRotatef(0.25f, 0.25f, 0.25f, 0.25f);
}
