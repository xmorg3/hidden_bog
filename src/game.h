
#include <SDL.h>
#include <SDL_ttf.h>

enum gate_state_numbers {
  GAME_QUIT,
  GAME_INIT,
  GAME_LOAD_RESOURCES,
  GAME_START_MENU,
  GAME_CHARGEN_MENU,
  GAME_OPTIONS_MENU,
  GAME_PLAY_INTRO_STORY,
  GAME_PLAY_IDLE,
  GAME_PLAYER_MOVE,
  GAME_PLAYER_COMBAT,
  GAME_PLAYER_STATUS,
  GAME_PLAYER_INVENTORY,
  GAME_PLAYER_CONVERSATION,
  GAME_PLAYER_CRAFTING
};
enum facing_direction {
  NORTH = 0,
  EAST  = 1,
  SOUTH = 2,
  WEST  = 3
};
typedef struct _Actor {
  char name[25];
  int sex; //1 male, 0 female
  int race; //number count for radio button in race selector.
  int portrait;
  int health, fatigue, mana;
  int level,
    experience,
    c_copper,   //currency
    c_silver,
    c_gold;
  int strength,
    intelligence,
    agility,
    wisdom,
    stamina,
    charisma,
    luck,
    bonus_attr;
    
    /*  new skills  */
  int skill_dagger,
    skill_sword,
    skill_axe,
    skill_crossbow,
    skill_archery,
    skill_throwing,
    skill_polearm, //spears halberds
    skill_club, //clubs and maces
    skill_spiked, //spiked weapons, picks, morning stars, beaks, sythes
    grappling, //wrestling
    biting,//chomp chomp
    hand2hand,//martial arts
    shielding,//bashing and blocking
    dodgemelee,
    dodgeranged,
    //social skills
    speeches, 
    lying,
    charming,
    empathy, //i feel your pain.
    debating, //arguing your point well.
    quickwit, //a smart mouth can have an effect on a weak mind.
    //less than honest skills
    pickpocket,
    lockpicking,
    traps, //disarming and setting of traps.
    //perception skills
    tracking,
    ambushing,
    lookout,
    findhidden, //doors, chests, traps
    //crafting skills
    woodcutting,
    stonecutting,
    tunneling, //find your own "path" through the maze
    bowmaking,
    fletching,
    clothmaking,
    blacksmithing, //making horseshoes!
    weaponsmithing,
    armorsmithing,
    leatherworking;
    
  int direction; //where you are facing.
  int map_x, map_y; //xy on current map
} Actor;

typedef struct _Scene { //Scene structure.
  char name[75]; //name of place
  int **tiles; //tiles!
  int **fog_tiles;
} Scene;

typedef struct _GameCore {
  SDL_Window *win;
  SDL_Renderer *renderer;
  SDL_Event sdl_event;
  SDL_DisplayMode current_dmode;
  int screen_size_x, screen_size_y;
  int game_state;
  int mapsize;
  int mouse_x, mouse_y;
  int stat_panel_x, stat_panel_y; //where to place the stats.
  int skill_panel_x, skill_panel_y; //panel for skills

  char messagelist[7][125];

  SDL_Texture *t_background;
  SDL_Texture *w_background; //wood background
  SDL_Texture *t_buttons;
  SDL_Texture *char_frame; //place on top of the character's portrait.
  SDL_Texture *character_doll;
  SDL_Texture *portraits_human_male;
  //note, there should be a func to load these textures on the fly?
  SDL_Texture *floor_bottom_fobx_blank,*sky_top_fobx_blank,
    *wall_front_fov0_blank, *wall_front_fov1_blank,
    *wall_left_fov0_blank, *wall_left_fov1_blank,
    *wall_left_fov2_blank, *wall_right_fov0_blank,
    *wall_right_fov1_blank, *wall_right_fov2_blank;
  SDL_Texture  *tall_wall_front_fov0, *tall_wall_front_fov1,
    *tall_wall_left_fov0,  *tall_wall_left_fov1,  *tall_wall_left_fov2,
  	 *tall_wall_right_fov0, *tall_wall_right_fov1, *tall_wall_right_fov2;
  SDL_Texture *wall_all; //gc->wall_all = load_texture_by_dir(gc, directory, "wall_all0.png");
  SDL_Texture *door_front_fov0_blank, *door_front_fov1_blank, *door_left_fov0_blank, *door_left_fov1_blank,
    *door_left_fov2_blank, *door_right_fov0_blank, *door_right_fov1_blank, *door_right_fov2_blank,
    *item1_fov0;
  
  SDL_Rect character_doll_rect;
  SDL_Rect char_frame_rect;
  SDL_Color current_color; //current color to draw in (like for text)
  TTF_Font *current_font;
  TTF_Font *font0;
  SDL_Rect *c_text_size;
  SDL_Rect player_viewport, message_log, tabbed_pane;
  SDL_Rect button_raised, button_pressed, button_highlighted, button_greyed;//source rects
  SDL_Rect radio_raised, radio_pressed, radio_highlighted, radio_greyed;//source rects
  SDL_Rect button_plus_raised, button_minus_raised; //source rects
  SDL_Rect dst_stat_plus, dst_stat_minus;

  Actor *player;
  Scene *current_map;

} GameCore;
