import pygame
from math import cos, sin, ceil

class Hex:

    def __init__(self, size, image, color, number=None):
        self.x = 0
        self.y = 0
        self._size = size
        self._image = pygame.transform.scale(image, (2*self._size,2*self._size))
        pi2 = 2 * 3.14159265358979
        self._tile = True
        self._number = number
        self.color = color
        self._pointList = [
            (
                cos(i / 6 * pi2 + pi2/4) * self._size + self._size,
                sin(i / 6 * pi2 + pi2/4) * self._size + self._size
            )
            for i in range(0, 6)
        ]
        self.upperLeft = (
            min(self.pointList, key=lambda x: x[0])[0],
            min(self.pointList, key=lambda x: x[1])[1]
        )
        self.upperLeft = (0,0)
        self.upperRight = (
            max(self.pointList, key=lambda x: x[0])[0],
            min(self.pointList, key=lambda x: x[1])[1]
        )
        self.bottomLeft = (
            min(self.pointList, key=lambda x: x[0])[0],
            max(self.pointList, key=lambda x: x[1])[1]
        )
        self.bottomRight = (
            max(self.pointList, key=lambda x: x[0])[0],
            max(self.pointList, key=lambda x: x[1])[1]
        )
        self.height = abs(max(self._pointList, key= lambda x: x[1])[1]) - abs(min(self._pointList, key= lambda x: x[1])[1])


    def draw(self, surface):
        surface.blit(self._image, (self.x, self.y))
        return surface

    def render(self):
        pi2 = 2 * 3.14159265358979
        minY = min(self._pointList, key= lambda x: x[1])[1]
        self._pointList = [(x,y-minY) for x,y in self._pointList]
        self.height = abs(max(self._pointList, key= lambda x: x[1])[1]) - abs(min(self._pointList, key= lambda x: x[1])[1])
        self._image = pygame.transform.scale(self._image, (2*self._size,ceil(self.height)))
        self._image.set_colorkey((255,255,255))
        mask = pygame.Surface(self._image.get_rect().size)
        mask.set_colorkey((10,10,10))
        mask.fill((255,255,255,0))
        # draw hole in mask?
        pygame.draw.polygon(
            mask,
            (10, 10, 10),
            self._pointList,
            )
        pygame.draw.polygon(
            mask,
            self.color,
            self._pointList,
            2
            )
        if self._tile:
            pygame.draw.polygon(
                mask,
                self.color,
                [(
                    cos(i / 6 * pi2) * self._size/4 + self._size*0.875,
                    sin(i / 6 * pi2) * self._size/4 + self._size*0.875
                )
                for i in range(0, 6)],
                2
                )
            # font = pygame.font.SysFont(None, 24)
            # text = font.render(self._number, True, self.color)
            # mask.blit(text, (self._size*0.875,self._size*0.875))
        self._image.blit(mask, (0,0))

    def translate(self, x,y):
        self.x += x
        self.y += y
        self.upperLeft = (
            min(self.pointList, key=lambda x: x[0])[0],
            min(self.pointList, key=lambda x: x[1])[1]
        )
        self.upperLeft = (0,0)
        self.upperRight = (
            max(self.pointList, key=lambda x: x[0])[0],
            min(self.pointList, key=lambda x: x[1])[1]
        )
        self.bottomLeft = (
            min(self.pointList, key=lambda x: x[0])[0],
            max(self.pointList, key=lambda x: x[1])[1]
        )
        self.bottomRight = (
            max(self.pointList, key=lambda x: x[0])[0],
            max(self.pointList, key=lambda x: x[1])[1]
        )
        self.height = abs(max(self._pointList, key= lambda x: x[1])[1]) - abs(min(self._pointList, key= lambda x: x[1])[1])


    @property
    def pointList(self):
        return [(self.x +x, self.y + y) for x,y in self._pointList]
