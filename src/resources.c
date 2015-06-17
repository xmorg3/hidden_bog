
//#include <SDL2/SDL.h>
#include "game.h"

/*  New wall dimensions for wall_all
picture 598x273
rightwall(at left x0 w118)
leftwall( at right, x618 w118)
middle wall x115  w505  (at 619)
*/

int start_sdl(GameCore *gc);
SDL_Texture * IMG_Load_w_error(GameCore *gc, char * imgfile);
void set_rect(SDL_Rect *r, int x, int y, int w, int h);
int load_resources(GameCore *gc);
void load_map_wall_textures(GameCore *gc, char *directory);

void start_ttf(GameCore *gc); //text.c
SDL_Rect fast_rect(int x, int y, int w, int h);//render.c
void clear_textures(GameCore *gc);


#include <SDL2/SDL_opengl.h> //new render code.
int start_sdl(GameCore *gc)
{
  //Temp settings
  gc->screen_size_x = 1024; //1360; //640; //set screensize. (why hardcode again?)
  gc->screen_size_y = 600; //768; //480; //v---- run SDL_Init()
  if (SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS
          | SDL_WINDOW_FULLSCREEN_DESKTOP) == -1) {
    printf("SDL_Init: %s \n", SDL_GetError() );
    return 1;
  }
  start_ttf(gc);  //load the fonts
  SDL_GetCurrentDisplayMode(0, &gc->current_dmode);
  gc->screen_size_x = gc->current_dmode.w;
  gc->screen_size_y = gc->current_dmode.h;
  
  SDL_RendererInfo displayRendererInfo; //new
  SDL_CreateWindowAndRenderer(gc->screen_size_x,
			      gc->screen_size_y,
			      SDL_WINDOW_OPENGL,
			      &gc->win,
			      &gc->renderer );
  SDL_GetRendererInfo(gc->renderer, &displayRendererInfo);

  if (gc->win == NULL){ //error check window
    printf("%s \n", SDL_GetError() );
    return 1;
  }
  //SDL_DestroyRenderer(gc->renderer);
  //gc->renderer = SDL_CreateRenderer(gc->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (gc->renderer == NULL){
    printf("%s \n", SDL_GetError() );
    return 1;
  }
  gc->font0 = TTF_OpenFont("data/font.ttf", 14);//font size?
  gc->current_font = gc->font0;
  if (gc->font0 == NULL) {
    printf("Error no font (data/font.ttf) ->from resources.c\n");
    return 1;
  }
  //get the display mode.
  

  gc->game_state = 1; //the game started
  return 0;
}

#include <SDL_image.h>

SDL_Texture * IMG_Load_w_error(GameCore *gc, char * imgfile)
{
  SDL_Texture * img;
  img = IMG_LoadTexture(gc->renderer, imgfile);
  if(img == NULL) {
    printf("Error! someone trolled you a null surface!(%s)\n", imgfile);
  }
  return img;
}

void set_rect(SDL_Rect *r, int x, int y, int w, int h)
{
  r->x = x;
  r->y = y;
  r->w = w;
  r->h = h;
}
int load_resources(GameCore *gc)
{
  //have we decided if we are using Surfaces or Textures?
  //IMG_Load(const char *file);
  gc->t_background = IMG_Load_w_error(gc, "data/paper_background.png");
  gc->w_background = IMG_Load_w_error(gc, "data/wood_background.png");
  gc->character_doll = IMG_Load_w_error(gc, "data/doll_male_blank.png");
  gc->t_buttons = IMG_Load_w_error(gc, "data/RPG_GUI_v1.png");
  gc->char_frame = IMG_Load_w_error(gc, "data/char_frame.png");
  gc->portraits_human_male = IMG_Load_w_error(gc, "data/char_male.png");

  set_rect(&gc->button_raised, 14,126, 283,55);
  set_rect(&gc->button_pressed,14,204, 283,55);
  set_rect(&gc->button_highlighted,14,282, 283,55);
  set_rect(&gc->radio_raised, 18,14,24,24);
  set_rect(&gc->radio_pressed,18,50,24,24);
  //src = fast_rect(0,0,280,800);
  set_rect(&gc->character_doll_rect, 0,0,288,800); //female rect x = 454, w = 220
  //viewport (top left)
  set_rect(&gc->player_viewport,
	   5,
	   5,
	   (gc->screen_size_x/4) * 3 - 5,
	   gc->screen_size_y - 137 ); //everything except portraits

  set_rect(&gc->tabbed_pane,
	   (gc->screen_size_x / 4) *3 + 5, //x
	   5, //y
	   gc->screen_size_x - (gc->screen_size_x / 4) *3 + 5, //w
	   gc->screen_size_y - 128  ); //h
  //message log (bottom)
  set_rect(&gc->message_log,
	   5,
	   gc->screen_size_y -128,
	   gc->screen_size_x - 7 ,
	   gc->screen_size_y );
  set_rect(&gc->button_plus_raised, 327,122,28,28); //rects for plus/minus on the source image
  set_rect(&gc->button_minus_raised, 366, 122,28,28);
  gc->stat_panel_x = 360;
  gc->stat_panel_y = 200; //set location for stat panel
  //first buttons for plus/minus on
  gc->dst_stat_minus = fast_rect(gc->stat_panel_x-32+20, gc->stat_panel_y, 20, 20);
  gc->dst_stat_plus = fast_rect( gc->stat_panel_x-32, gc->stat_panel_y, 20, 20); //stat sheets
  load_map_wall_textures(gc, "village_day/");
  //load_map_wall_textures(gc, "castle_dungeon/");
  return 0;
}//load_resources

SDL_Texture * load_texture_by_dir(GameCore *gc, char *directory, char *file)
{
  char strfile[300];
  SDL_Texture *t;
  strfile[0] = '\0';
  strcpy(strfile, "data/mods/oldschool/");
  strcat(strfile, directory); //  add the / in the argument
  strcat(strfile, file);
  printf("%s\n", strfile);
  t = IMG_Load_w_error(gc, strfile);
  return t;
}
void load_map_wall_textures(GameCore *gc, char *directory)
{
  clear_textures(gc);
  gc->wall_all = load_texture_by_dir(gc, directory, "wall_all0.png"); //new wall
  gc->floor_bottom_fobx_blank = load_texture_by_dir(gc, directory, "floor_bottom_fobx_blank.png");
  gc->sky_top_fobx_blank = load_texture_by_dir(gc, directory, "sky_top_fobx_blank.png");
  gc->wall_front_fov0_blank = load_texture_by_dir(gc,  directory, "wall_front_fov0_blank.png");
  gc->wall_front_fov1_blank = load_texture_by_dir(gc, directory, "wall_front_fov1_blank.png");
  gc->wall_left_fov0_blank = load_texture_by_dir(gc, directory, "wall_left_fov0_blank.png");
  gc->wall_left_fov1_blank = load_texture_by_dir(gc, directory, "wall_left_fov1_blank.png");
  gc->wall_left_fov2_blank = load_texture_by_dir(gc, directory, "wall_left_fov2_blank.png");
  gc->wall_right_fov0_blank = load_texture_by_dir(gc, directory, "wall_right_fov0_blank.png");
  gc->wall_right_fov1_blank = load_texture_by_dir(gc, directory, "wall_right_fov1_blank.png");
  gc->wall_right_fov2_blank = load_texture_by_dir(gc, directory, "wall_right_fov2_blank.png");
  
  gc->tall_wall_front_fov0 = load_texture_by_dir(gc,  directory, "tall_wall_front_fov0.png");
  gc->tall_wall_front_fov1 = load_texture_by_dir(gc, directory,  "tall_wall_front_fov1.png");
  gc->tall_wall_left_fov0 = load_texture_by_dir(gc, directory, "tall_wall_left_fov0.png");
  gc->tall_wall_left_fov1 = load_texture_by_dir(gc, directory, "tall_wall_left_fov1.png");
  gc->tall_wall_left_fov2 = load_texture_by_dir(gc, directory, "tall_wall_left_fov2.png");
  gc->tall_wall_right_fov0 = load_texture_by_dir(gc, directory, "tall_wall_right_fov0.png");
  gc->tall_wall_right_fov1 = load_texture_by_dir(gc, directory, "tall_wall_right_fov1.png");
  gc->tall_wall_right_fov2 = load_texture_by_dir(gc, directory, "tall_wall_right_fov2.png");

  gc->door_front_fov0_blank = load_texture_by_dir(gc, directory, "door_front_fov0_blank.png");
  gc->door_front_fov1_blank = load_texture_by_dir(gc, directory, "door_front_fov1_blank.png");
  
  gc->door_left_fov0_blank = load_texture_by_dir(gc, directory, "door_left_fov0_blank.png");
  gc->door_left_fov1_blank = load_texture_by_dir(gc, directory, "door_left_fov1_blank.png");
  gc->door_left_fov2_blank = load_texture_by_dir(gc, directory, "door_left_fov2_blank.png");

  gc->door_right_fov0_blank = load_texture_by_dir(gc, directory, "door_right_fov0_blank.png");
  gc->door_right_fov1_blank = load_texture_by_dir(gc, directory, "door_right_fov1_blank.png");
  gc->door_right_fov2_blank = load_texture_by_dir(gc, directory, "door_right_fov2_blank.png");
  gc->item1_fov0 = load_texture_by_dir(gc, directory, "item1_fov0.png");
  //load_texture_by_dir(gc->, "blank/", ".png");
}
void clear_textures(GameCore *gc)
{
  SDL_DestroyTexture(gc->floor_bottom_fobx_blank);// = load_texture_by_dir(gc, directory, "floor_bottom_fobx_blank.png");
  SDL_DestroyTexture(gc->sky_top_fobx_blank);// = load_texture_by_dir(gc, directory, "sky_top_fobx_blank.png");
  SDL_DestroyTexture(gc->wall_front_fov0_blank);// = load_texture_by_dir(gc,  directory, "wall_front_fov0_blank.png");
  SDL_DestroyTexture(gc->wall_front_fov1_blank);// = load_texture_by_dir(gc, directory, "wall_front_fov1_blank.png");
  SDL_DestroyTexture(gc->wall_left_fov0_blank);// = load_texture_by_dir(gc, directory, "wall_left_fov0_blank.png");
  SDL_DestroyTexture(gc->wall_left_fov1_blank);// = load_texture_by_dir(gc, directory, "wall_left_fov1_blank.png");
  SDL_DestroyTexture(gc->wall_left_fov2_blank);// = load_texture_by_dir(gc, directory, "wall_left_fov2_blank.png");
  SDL_DestroyTexture(gc->wall_right_fov0_blank);// = load_texture_by_dir(gc, directory, "wall_right_fov0_blank.png");
  SDL_DestroyTexture(gc->wall_right_fov1_blank);// = load_texture_by_dir(gc, directory, "wall_right_fov1_blank.png");
  SDL_DestroyTexture(gc->wall_right_fov2_blank);// = load_texture_by_dir(gc, directory, "wall_right_fov2_blank.png");
  SDL_DestroyTexture(gc->wall_all);// = load_texture_by_dir(gc, directory, "wall_all0.png"); //new wall
  SDL_DestroyTexture(gc->tall_wall_front_fov0);// = load_texture_by_dir(gc,  directory, "tall_wall_front_fov0.png");
  SDL_DestroyTexture(gc->tall_wall_front_fov1);// = load_texture_by_dir(gc, directory,  "tall_wall_front_fov1.png");
  SDL_DestroyTexture(gc->tall_wall_left_fov0);// = load_texture_by_dir(gc, directory, "tall_wall_left_fov0.png");
  SDL_DestroyTexture(gc->tall_wall_left_fov1);// = load_texture_by_dir(gc, directory, "tall_wall_left_fov1.png");
  SDL_DestroyTexture(gc->tall_wall_left_fov2);// = load_texture_by_dir(gc, directory, "tall_wall_left_fov2.png");
  SDL_DestroyTexture(gc->tall_wall_right_fov0);// = load_texture_by_dir(gc, directory, "tall_wall_right_fov0.png");
  SDL_DestroyTexture(gc->tall_wall_right_fov1);// = load_texture_by_dir(gc, directory, "tall_wall_right_fov1.png");
  SDL_DestroyTexture(gc->tall_wall_right_fov2);// = load_texture_by_dir(gc, directory, "tall_wall_right_fov2.png");
}
