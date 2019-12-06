#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Nov 28 06:55:23 2019

@author: tcooper
"""

from pygame.locals import *
from OpenGL.GL import *
from OpenGL.GLU import *

from files.primitives import shapes

class scene:
    def __init__(self):
        #get location on the map
        #draw your location with shapes.cube_at
        self.s = shapes()
        self.maploc = [  ["#", "+", "#"],
                         ["#", "+", "#"],
                         ["#", "@", "#"]
                          ]
    def draw_farleft_tile(self, tile): #x,y here is as it is on a flat map
        if tile == "#":
            self.s.color(0.2, 0.2, 0.2)
            self.s.cube_at(-2,0,-4)
    def draw_left_tile(self, tile):
        if tile == "#":
            self.s.color(0.2, 0.2, 0.2)
            self.s.cube_at(-2,0,-2)
    def draw_closelefttile(self, tile):
        if tile == "#":
            self.s.color(0.2, 0.2, 0.2)
            self.s.cube_at(-2, 0, 0)
    def draw_farcenter_tile(self, tile):
        if tile == "#":
            self.s.cube_at(0,0,-4)
    def draw_farright_tile(self, tile):
        if tile == "#":
            self.s.color(0.2, 0.2, 0.2)
            self.s.cube_at(2,0,-4)
    def draw_right_tile(self, tile):
        if tile == "#":
            self.s.color(0.2, 0.2, 0.2)
            self.s.cube_at(2,0,-2)
    def draw_closeright_tile(self, tile):
        if tile == "#":
            self.s.color(0.2, 0.2, 0.2)
            self.s.cube_at(2,0,0)
    def draw_scene(self, maploc):
        self.s.push()
        self.draw_farleft_tile(maploc[0][0])
        self.draw_farcenter_tile(maploc[0][1])
        self.draw_farright_tile(maploc[0][2])
        
        self.draw_left_tile(maploc[1][0])
        self.draw_right_tile(maploc[1][2])
        
        self.draw_closelefttile(maploc[2][0])
        self.draw_closeright_tile(maploc[2][2])
        self.s.pop()
        
        #bottom
        self.s.push()
        glColor3f(0.4, 0.4, 0.4)
        self.s.cube_at(0,-2,-4)
        self.s.cube_at(0,-2,-2)
        self.s.cube_at(0,-2,0)
        self.s.pop()
        
        #top
        self.s.push()
        glColor3f(0.4, 0.4, 0.4)
        self.s.cube_at(0,2,-4)
        self.s.cube_at(0,2,-2)
        self.s.cube_at(0,2,0)
        self.s.pop()