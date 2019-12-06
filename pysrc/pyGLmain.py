#/usr/bin/python3

import pygame
from pygame.locals import *
from OpenGL.GL import *
from OpenGL.GLU import *

from files.primitives import shapes
from files.scene import scene

#mesh = pymesh.load_mesh("dungeonquart01.obj")
yrot = 0
yrot_tracker=0
angle = 0

sn = scene()

def draw():
    #s = shapes()
    #glEnable(GL_LIGHTING);
    #glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    
    #glEnable(GL_LIGHT1) 
    glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE )
    #textures
    glEnable(GL_TEXTURE_2D)
    glEnable(GL_BLEND)
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT)
    sn.draw_scene(sn.maploc)
    pygame.display.flip()
    pygame.time.wait(10)
def input():
    global yrot
    global angle
    global yrot_tracker
    key = pygame.key.get_pressed()
    if key[pygame.K_RIGHT]:
        yrot = 5
        angle = 5
        yrot_tracker += 5
        if yrot_tracker >= 45:
            yrot_tracker = 45
            yrot = 0
            angle = 0
        return "playing"
    elif key[pygame.K_LEFT]:
        yrot = +5
        angle = -5
        yrot_tracker -= 5
        if yrot_tracker <= -45:
            yrot_tracker = -45
            yrot = 0
            angle = 0
        return "playing"
    elif key[pygame.K_ESCAPE]:
        #pygame.event.post(QUIT)
        return "exit"
    else:
        angle = 0
        yrot = 0
        return "playing"

def main():
    pygame.init()
    display = (800,600)
    pygame.display.set_mode(display, DOUBLEBUF|OPENGL)
    gluPerspective(45, (display[0]/display[1]), 0.1, 50.0)
    glTranslatef(0.0, 0.0, -1.5)
    glScale(3.5, 3.5, 3.5)
    game_state = "playing"
    while game_state == "playing":
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                print("debug: you wanted to quit?")
                pygame.quit()
            if event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE:
                game_state = "exit"
        game_state = input()
        glRotatef(angle, 0,yrot,0)
        draw()
        #print("game_state = ", game_state, "loop again")
    print("somehow you got to the end of the loop")
main()
