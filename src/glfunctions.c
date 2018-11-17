#include <SDL_opengl.h> //new render code.
#include <SDL.h>
#include "game.h"


void display_initGL();
int display_setviewport( int width, int height );
void display_render(GameCore *gc);
void draw_background_texture(GameCore *gc, SDL_Texture *t);

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
    draw_background_texture(gc, gc->w_background);
    
    SDL_RenderPresent(gc->renderer);
}

void draw_background_texture(GameCore *gc, SDL_Texture *t)
{
  //render a GL backgroup
  //bind texture here!
  //glBindTexture( GL_TEXTURE_2D, t );
  SDL_GL_BindTexture(t, NULL, NULL );
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glBegin( GL_TRIANGLE_STRIP );            /* Drawing Using Triangles */
  glNormal3f(0, 0, 0);
  
  glTexCoord2f(0, 0); glVertex3f(0, 0,0); //Floor
  glTexCoord2f(0, 1); glVertex3f(0,-1,0); //top line
  glTexCoord2f(1, 1); glVertex3f(1,-1,0); //left line
  glTexCoord2f(1, 0); glVertex3f(1, 0,0); //bottom line
  
  glEnd();
}
