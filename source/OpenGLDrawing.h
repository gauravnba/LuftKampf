#ifdef OPENGLSTUFF_CPP
#define extern 
#endif

void endOpenGLDrawing();
void startOpenGLDrawing();
void initOpenGLDrawing( GL_Window *window, Keys *keys, float32_t backRed, float32_t backGreen, float32_t backBlue);

extern GL_Window*	g_window;
extern Keys*		g_keys;

#undef extern