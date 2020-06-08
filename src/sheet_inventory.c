//want to know
#include "game.h" //access to GameCore
//What is the inventory?
//A fixed list of items,  

void draw_char_menu_frame(GameCore *gc); //backdrop frame
void render_inventory(GameCore *gc); //Access to GameCore
void add_item_to_inventory(GameCore *gc); //pick up an item
void drop_item(GameCore *gc);

void render_inventory(GameCore *gc) //render the inventory screen
{
  draw_char_menu_frame(gc);  //draw a portrait
  
}

void add_item_to_inventory(GameCore *gc) //pick up an item
{}

void drop_item(GameCore *gc) //remove an item from your inventory.
{}
