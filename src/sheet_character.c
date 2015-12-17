
void draw_char_menu_frame(GameCore *gc); //backdrop frame

void draw_sheet_character(GameCore *gc)
{
  draw_char_menu_frame(gc);
  //draw a portrait
  draw_character_attributes(gc, gc->stat_panel_x, gc->stat_panel_y, 1);
}
