import pygame
import pathlib
import hex
import os
from images.imageloader import ImageLoader
import board


pygame.init()
screenInfo = pygame.display.Info()

# screen = pygame.display.set_mode([1500, 1400])
# screen.set_colorkey((255,255,255))
# imagePath = os.path.join(os.path.dirname(os.path.realpath(__file__)), ".\images")
screen = pygame.display.set_mode([screenInfo.current_w, screenInfo.current_h])
imagePath = os.path.join(os.path.dirname(os.path.realpath(__file__)), "./images")
imLoader = ImageLoader(imagePath)
# image = imLoader.ironOre
running = True
test = board.fourPersonPlayingfield(0,0,imLoader)

boat = imLoader.boat
# boat = hex.Hex(100, image, (255,0,0))
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    screen.fill((255,255,255))
    for tile in test:
        tile.render()
    screen.blits([(tile._image, (int(tile.x), int(tile.y))) for tile in test])
#     boathex = hex.Hex(50, imLoader.boat, (255,255,255))
#     boathex.render((255,255,255))
    pygame.display.update()

pygame.quit()
