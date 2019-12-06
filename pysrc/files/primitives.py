#/usr/bin/python3

#import pygame
#from pygame.locals import *
#import OpenGL.GL
from OpenGL.GL import *
from OpenGL.GLU import *
import pygame

verticies = (
    (1, -1, -1),
    (1, 1, -1),
    (-1, 1, -1),
    (-1, -1, -1),
    (1, -1, 1),
    (1, 1, 1),
    (-1, -1, 1),
    (-1, 1, 1)
    )

edges = (
    (0,1),
    (0,3),
    (0,4),
    (2,1),
    (2,3),
    (2,7),
    (6,3),
    (6,4),
    (6,7),
    (5,1),
    (5,4),
    (5,7)
    )

texCoords = (
    (0.0, 0.0),  # lower-left corner  
    (1.0, 0.0),  # lower-right corner
    (1.0, 1.0)   # top-right corner
    (0.0, 1.0)   # top left corner
    )

img = pygame.image.load('tiles.jpeg')

class shapes:
    def cube_at(self,x,y,z):    
        glBegin(GL_POLYGON) #(GL_LINES)
        for edge in edges:
            for vertex in edge:
                vtp = verticies[vertex]
                #print(vtp) #debug
                vx = vtp[0]
                #print("vx = ", vx) #debug
                vy = vtp[1]
                #print("vy = ", vy)
                vz = vtp[2]
                #print("vz = ", vz) #debug
                glVertex3f(vx+x, vy+y, vz+z)
        glEnd()
    def color(self,r,g,b):
        glColor3f(r,g,b)
    def push(self):
        glPushMatrix()
    def pop(self):
        glPopMatrix()
    def loadImage(image): #https://www.pygame.org/wiki/SimpleOpenGL2dClasses
        textureSurface = pygame.image.load(image)
        textureData = pygame.image.tostring(textureSurface, "RGBA", 1)
        width = textureSurface.get_width()
        height = textureSurface.get_height()
        texture = glGenTextures(1)
        glBindTexture(GL_TEXTURE_2D, texture)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, textureData)
        return texture, width, height
    
    #def createTexture(self, t):
    #    texture = glGenTextures(1)
    #    glBindTexture(GL_TEXTURE_2D, t) 
    #    #https://www.pygame.org/wiki/SimpleOpenGL2dClasses
    #    glBindTexture(GL_TEXTURE_2D, texture)
    #    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)
    #    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)
    #    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
    #    GL_UNSIGNED_BYTE, textureData)
