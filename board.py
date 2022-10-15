import random
from hex import Hex
from math import cos, sin


COLORDICT = {
        'grain': (202, 184, 162),
        'weiland': (163, 232, 140),
        'forrest': (2, 94, 4),
        'mountain': (255, 140, 0),
        'mine': (142, 141, 145),
        'desert': (222, 184, 135)
        }
pi2 = 2 * 3.14159265358979

def fourPersonPlayingfield(centerX, centerY, images, size=100):
    AllFields = ['grain']*4+['weiland']*4+['forrest']*4+['mountain']*3+['mine']*3+['desert']
    random.shuffle(AllFields)

    hexFields = []
    for field in AllFields:
        image = getattr(images, field)
        color = COLORDICT[field]
        hexFields.append(Hex(size, image, color, 1))


    columns = [3,4,5,4,3]
    board = []
    fieldCount = 0
    x = 600
    y = 600
    for columnCount, column in enumerate(columns):
        for count in range(column):
            tile = hexFields[fieldCount]
            tile.translate(x,y)
            board.append(tile)
            fieldCount += 1
            y += tile.height 
        try:
            if columns[columnCount+1] < column:
                x,y = board[-columns[columnCount]].bottomRight
                x,y = board[-columns[columnCount]].bottomRight
                y -= tile.height/2
            else:
                x,y = board[-columns[columnCount]].upperRight
                y -= tile.height/2
        except:
            pass


    return board
