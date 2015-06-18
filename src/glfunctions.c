#include <SDL2/SDL_opengl.h> //new render code.

void display_initGL();
int display_setviewport( int width, int height );
void display_render();
void display_initGL()
{
    /* Enable smooth shading */
    glShadeModel( GL_SMOOTH ); 
    /* Set the background black */
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f ); 
    /* Depth buffer setup */
    glClearDepth( 1.0f ); 
    /* Enables Depth Testing */
    glEnable( GL_DEPTH_TEST ); 
    /* The Type Of Depth Test To Do */
    glDepthFunc( GL_LEQUAL ); 
    /* Really Nice Perspective Calculations */
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
}

int display_setviewport( int width, int height )
{
    /* Height / width ration */
    GLfloat ratio; 
    /* Protect against a divide by zero */
    if ( height == 0 ) {
        height = 1;
    } 
    ratio = ( GLfloat )width / ( GLfloat )height; 
    /* Setup our viewport. */
    glViewport( 0, 0, ( GLsizei )width, ( GLsizei )height ); 
    /* change to the projection matrix and set our viewing volume. */
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( ); 
    /* Set our perspective */
    //gluPerspective( 45.0f, ratio, 0.1f, 100.0f ); 
    /* Make sure we're chaning the model view and not the projection */
    glMatrixMode( GL_MODELVIEW ); 
    /* Reset The View */
    glLoadIdentity( ); 
    return 1;
}

#include <SDL2/SDL.h>
#include "game.h"
void display_render(GameCore *gc)
{
    /* Set the background black */
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    /* Clear The Screen And The Depth Buffer */
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
     /* Move Left 1.5 Units And Into The Screen 6.0 */
    glLoadIdentity();
    glTranslatef( 0.0f, 0.0f, 0.0f );
 
    //run macrofucntions.
    
    SDL_RenderPresent(gc->renderer);
}
