from tkinter import *
from tkinter import simpledialog
from tkinter.filedialog import *
from PIL import Image, ImageTk
import os
import json

mapW = 10
mapH = 10
tileW = 64
tileH = 64
tileSetCols = 8
tileSetRows = 8

tileSet = []
objSet = []
selectedTile = 0
selectedObj = 0
onTile = True

tileMap = []
collision = []
setW = 512
setH = 512



# gets the relative path to Game/Assets/Images/Tiles1.bmp
imgFile = os.path.abspath(os.path.join(os.path.dirname( __file__ ), os.pardir, 'Assets', 'Images', 'Tiles1.bmp'))


class Tile():
    def __init__(self, x, y, editor):
        self.xPos = x
        self.yPos = y
        self.tileID = -1
        self.objID = -1
        self.label = None
        self.editor = editor

    # give the tile a reference to its label (to hold the image) in the grid
    def giveLabel(self, label):
        self.label = label

    # set the tile to a new tile
    def setTile(self):
        if (self.tileID == -1 and self.objID == -1):
            self.label.config(image = "")
            self.label.image = ""
        elif (self.tileID == -1):
            self.label.config(image = objSet[self.objID].image)
            self.label.image = objSet[self.objID].image
        elif (self.objID == -1):
            self.label.config(image = tileSet[self.tileID])
            self.label.image = tileSet[self.tileID]
        else:
            obj = ImageTk.getimage(objSet[self.objID].image)
            tile = ImageTk.getimage(tileSet[self.tileID])
            temp = ImageTk.PhotoImage(tile)
            temp.paste(obj)

            self.label.config(image = temp)
            self.label.image = temp

            # self.label.config(image = objSet[self.objID].image)
            # self.label.image = objSet[self.objID].image


    # handles set tile event
    def setTileEvent(self, event):
        if (onTile):
            self.tileID = selectedTile
        else: # onObj
            # remove prev obj
            if (self.objID >= 0):
                prevObj = objSet[self.objID]
                prevObj.xPos = -1
                prevObj.yPos = -1
            # remove curr obj from prev coordinate
            currObj = objSet[selectedObj]
            if (currObj.xPos >= 0 and currObj.yPos >= 0):
                tileMap[currObj.yPos][currObj.xPos].objID = -1
                tileMap[currObj.yPos][currObj.xPos].setTile()
            # set curr obj position to this coordinate
            currObj.xPos = self.xPos
            currObj.yPos = self.yPos
            self.editor.posLabel.config(text = "Position: (" + str(objSet[selectedObj].xPos) + ", " + str(objSet[selectedObj].yPos) + ")")
            # update our obj to curr obj
            self.objID = selectedObj
        self.setTile()

    # clear tile and object
    def clearEvent(self, event):
        # update obj pos
        if self.objID >= 0 and self.objID < len(objSet):
            objSet[self.objID].xPos = -1
            objSet[self.objID].yPos = -1
            self.editor.posLabel.config(text = "Position: (" + str(objSet[self.objID].xPos) + ", " + str(objSet[self.objID].yPos) + ")")
        # clear
        self.objID = -1
        self.tileID = -1
        self.setTile()


class Object():
    def __init__(self, name, spriteSheet, xPos = -1, yPos = -1, tag = ""):
        self.name = name
        self.xPos = xPos
        self.yPos = yPos
        self.path = spriteSheet
        self.image = ImageTk.PhotoImage(Image.open(spriteSheet).crop((0, 0, tileW, tileH)))
        self.tag = tag




# Game editor window
class Editor(Frame):

    # Nested class
    class SelectionLabel():
        def __init__(self, id, editor, label, isTile):
            self.editor = editor
            self.id = id
            self.label = label
            self.isTile = isTile

        # event when the tile is clicked on
        def select(self, event):
            global selectedTile, selectedObj, onTile
            if onTile:
                self.editor.tileSelection[selectedTile].deselect()
            else: # on obj
                self.editor.objSelection[selectedObj].deselect()
                objSet[selectedObj].tag = self.editor.entryText.get()
            if self.isTile:
                selectedTile = self.id
                onTile = True
                self.label.config(bg="yellow")
                self.editor.previewLabel.config(image=tileSet[self.id])
                self.editor.objTextFrame.pack_forget()
                self.editor.textFrame.pack(side = RIGHT, fill=BOTH, expand=True, padx=(10, 0))
                self.editor.idLabel.config(text = "Tile ID: " + str(selectedTile))
                if collision.__contains__(self.id):
                    self.editor.collisionToggle.select()
                else:
                    self.editor.collisionToggle.deselect()
            else: # is object
                selectedObj = self.id
                onTile = False
                self.label.config(bg="yellow")
                self.editor.previewLabel.config(image=objSet[self.id].image)
                self.editor.textFrame.pack_forget()
                self.editor.objTextFrame.pack(side = RIGHT, fill=BOTH, expand=True, padx=(10, 0))
                self.editor.posLabel.config(text = "Position: (" + str(objSet[selectedObj].xPos) + ", " + str(objSet[selectedObj].yPos) + ")")
                self.editor.tagLabel.config(text = "Tag: ")
                self.editor.entryText.set(objSet[selectedObj].tag)


        def manualSelect(self):
            global selectedTile, onTile
            if onTile:
                self.editor.tileSelection[selectedTile].deselect()
            else: # on obj
                self.editor.objSelection[selectedObj].deselect()
            selectedTile = self.id
            onTile = True
            self.label.config(bg="yellow")
            self.editor.previewLabel.config(image=tileSet[self.id])
            self.editor.objTextFrame.pack_forget()
            self.editor.textFrame.pack(side = RIGHT, fill=BOTH, expand=True)
            self.editor.idLabel.config(text = "Tile ID: " + str(selectedTile))
            if collision.__contains__(self.id):
                self.editor.collisionToggle.select()
            else:
                self.editor.collisionToggle.deselect()

        # unhighlight
        def deselect(self):
            self.label.config(bg='grey')
    

    # Editor init
    def __init__(self, master=None):
        super().__init__(master)
        self.master = master
        self.master.geometry("400x780+0+0")
        self.pack(fill = BOTH, expand = True)
        self.create_widgets()
        self.gameWin


    def create_widgets(self):
        # create menu bar
        self.option_add('*tearOff', FALSE)
        menubar = Menu(self.master)
        self.master.config(menu=menubar)
        # file dropdown
        menu_file = Menu(menubar)
        menubar.add_cascade(menu = menu_file, label = 'File')
        menu_file.add_command(label = 'New Map', command = self.newMap)
        menu_file.add_command(label = 'Open Map', command = self.openMap)
        menu_file.add_command(label = 'Save Map', command = self.saveMap)
        menu_file.add_command(label = 'Import Objects', command = self.openObjs)
        menu_file.add_command(label = 'Export Objects', command = self.saveObjs)
        
        # edit dropdown
        menu_edit = Menu(menubar)
        menubar.add_cascade(menu = menu_edit, label = 'Edit')
        menu_edit.add_command(label = 'Open Tile Set', command = self.openSet)
        menu_edit.add_command(label = 'New Object', command = self.newObj)

        # properties window
        propertiesLabel = Label(self, text = "Properties")
        propertiesLabel.pack(side = TOP, fill = BOTH)
        self.frameProperties = Frame(self, borderwidth = 20)
        self.frameProperties.pack(side = TOP, anchor = "nw", fill=BOTH)
        # preview pic
        self.previewFrame = Frame(self.frameProperties, width = tileW, height = tileH, borderwidth = 2, relief = "groove")
        self.previewFrame.pack(side = LEFT)
        self.previewLabel = Label(self.previewFrame, image = tileSet[selectedTile], borderwidth=5)
        self.previewLabel.pack()
        # text properties
        self.textFrame = Frame(self.frameProperties)
        self.textFrame.pack(side = RIGHT, fill=BOTH, expand=True, padx=(10, 0))
        self.objTextFrame = Frame(self.frameProperties)
        # tile id num
        self.idLabel = Label(self.textFrame, text = "Tile ID: " + str(selectedTile))
        self.idLabel.pack(anchor = "w", fill=Y)
        # collision checkbox
        self.collisionToggleVal = IntVar()
        self.collisionToggle = Checkbutton(self.textFrame, text="Solid", variable=self.collisionToggleVal, onvalue=1, offvalue=0, command=self.toggleCollision)
        self.collisionToggle.pack(anchor = "w", fill=Y)
        # xPos, yPos
        self.posLabel = Label(self.objTextFrame)
        self.posLabel.pack(anchor = "w", fill=Y)
        # tag
        tagFrame = Frame(self.objTextFrame)
        tagFrame.pack(anchor = "w", fill=Y)
        self.tagLabel = Label(tagFrame)
        self.tagLabel.pack(side = LEFT, anchor = "w", fill=Y)
        self.entryText = StringVar()
        self.tagEntry = Entry(tagFrame, textvariable = self.entryText)
        self.tagEntry.pack(side = LEFT, anchor = "w", fill=Y)

        # selection lists
        tileSetLabel = Label(self, text = "Tiles")
        tileSetLabel.pack(side = TOP, fill = BOTH)
        frameSelections = Frame(self)
        frameSelections.pack(side = LEFT, fill=BOTH)
        # tile select
        frameTile = Frame(frameSelections)
        frameTile.pack(side=TOP, fill=BOTH)
        self.canvas = Canvas(frameTile, bg="grey")
        vsb = Scrollbar(frameTile, orient="vertical", command=self.canvas.yview)
        self.canvas.configure(yscrollcommand=vsb.set)
        vsb.pack(side=RIGHT, fill=BOTH)
        self.createFrameMap()
        self.canvas.pack(side = LEFT, anchor = "nw", fill=BOTH, expand=True)

        self.tileSelection[selectedTile].manualSelect()

        # object list
        objSetLabel = Label(frameSelections, text = "Game Objects")
        objSetLabel.pack(side = TOP, fill = BOTH)
        frameObject = Frame(frameSelections)
        frameObject.pack(side=TOP, fill=BOTH)
        self.canvasObj = Canvas(frameObject, bg="grey")
        vsbObj = Scrollbar(frameObject, orient="vertical", command=self.canvasObj.yview)
        self.canvasObj.configure(yscrollcommand=vsbObj.set)
        vsbObj.pack(side=RIGHT, fill=BOTH)
        self.createObjList()
        self.canvasObj.pack(side = LEFT, anchor = "nw", fill=BOTH, expand=True)

        # make game window
        self.gameWin = Toplevel(self.master)
        self.game = Game(self.gameWin, self)


    def createFrameMap(self):
        self.frameMap = Frame(self.canvas)
        self.frameMap.pack(fill = BOTH, expand = True)
        self._frameMap_id = self.canvas.create_window(
                                0, 0,
                                anchor='nw',
                                window=self.frameMap)
        self.tileSelection = []
        for i in range(len(tileSet)):
            imgLabel = Label(self.frameMap, image = tileSet[i], borderwidth=5)
            imgLabel.grid(row=int(i/4), column=i%4, sticky = "nsew")
            sl = self.SelectionLabel(i, self, imgLabel, True)
            imgLabel.bind('<Button-1>', sl.select)
            self.tileSelection.append(sl)
        self.frameMap.bind('<Configure>', self.onFrameMapConfigure)


    def createObjList(self):
        self.frameObj = Frame(self.canvasObj)
        self.frameObj.pack(fill = BOTH, expand = True)
        self._frameObj_id = self.canvasObj.create_window(
                                0, 0,
                                anchor='nw',
                                window=self.frameObj)
        self.objSelection = []
        for i in range(len(objSet)):
            objectFrame = Frame(self.frameObj)
            objectFrame.grid(row=i, column=0, sticky = "nsew")
            imgLabel = Label(objectFrame, image = objSet[i].image, borderwidth=5)
            nameLabel = Label(objectFrame, text = objSet[i].name)
            imgLabel.grid(row=0, column=0, sticky = "nsew")
            nameLabel.grid(row=0, column=1, sticky = "nsew")
            sl = self.SelectionLabel(i, self, imgLabel, False)
            imgLabel.bind('<Button-1>', sl.select)
            nameLabel.bind('<Button-1>', sl.select)
            self.objSelection.append(sl)
            if (objSet[i].yPos >= 0 and objSet[i].yPos < mapH) and (objSet[i].xPos >= 0 and objSet[i].xPos < mapW):
                tileMap[objSet[i].yPos][objSet[i].xPos].objID = i
                tileMap[objSet[i].yPos][objSet[i].xPos].setTile()
        self.frameObj.bind('<Configure>', self.onFrameMapConfigure)
        



    # create a new map
    def newMap(self):
        # take in new map w and h
        global mapW
        global mapH
        tempW = simpledialog.askinteger("Input", "Map Width", parent = self)
        if tempW is None:
            return False
        tempH = simpledialog.askinteger("Input", "Map Height", parent = self)
        if tempH is None:
            return False
        mapW = tempW
        mapH = tempH
        # reset Game window
        self.gameWin.destroy()
        self.gameWin = Toplevel(self.master)
        self.game = Game(self.gameWin, self)

    # open map from file
    def openMap(self):
        global mapH, mapW
        global imgFile, setW, setH, tileW, tileH, collision, tileMap
        
        jsonFile = askopenfile(parent=root, mode='r',title='Choose a file', initialdir = os.path.abspath(os.path.join(os.path.dirname( __file__ ), 'Assets', 'Levels')))
        if jsonFile:
            # read the json and update our global vars
            data = json.load(jsonFile)
            imgFile = data["tileSet"]
            setW = data["setW"]
            setH = data["setH"]
            tileW = data["tileW"]
            tileH = data["tileH"]
            collision = data["collision"]
            tileIDs = data["map"]
            mapH = len(tileIDs)
            mapW = len(tileIDs[0])
            # update tileSet
            tileSetCols = int(setW / tileW)
            tileSetRows = int(setH / tileH)
            tileSet.clear()
            for tileID in range(0, tileSetCols * tileSetRows):
                left = (tileID % tileSetCols) * tileW
                top = (tileID // tileSetCols) * tileH
                right = left + tileW
                bottom = top + tileH
                tileSet.append(ImageTk.PhotoImage(img.crop((left, top, right, bottom))))
            self.frameMap.destroy
            self.createFrameMap()
            self.tileSelection[selectedTile].manualSelect()
            # update tileMap
            self.gameWin.destroy()
            self.gameWin = Toplevel(self.master)
            self.game = Game(self.gameWin, self)
            for row_index in range(mapH):
                for col_index in range(mapW):
                    tileMap[row_index][col_index].tileID = tileIDs[row_index][col_index]
                    tileMap[row_index][col_index].setTile()


    def openObjs(self):
        global objSet
        jsonFile = askopenfile(parent=root,mode='r',title='Choose a file', initialdir = os.path.abspath(os.path.join(os.path.dirname( __file__ ), 'Assets', 'Levels')))
        if jsonFile:
            data = json.load(jsonFile)
            for key in data:
                val = data[key]
                objSet.append(Object(key, val['spriteSheet'], val['xPos'], val['yPos'], val['tag']))
        self.frameObj.destroy
        self.createObjList()
        self.tileSelection[selectedTile].manualSelect()
            


    
    # save map to file
    def saveMap(self):
        file = asksaveasfile(parent=root, mode='w', title='Choose a file', filetypes = [('JSON File', '*.json')], defaultextension=json, initialdir = os.path.abspath(os.path.join(os.path.dirname( __file__ ), 'Assets', 'Levels')))
        if file:
            tileIDs = [[tile.tileID for tile in row] for row in tileMap]
            numColumns = len(tileMap)
            numRows = len(tileMap[0])
            export = { "tileSet" : imgFile, "setW" : setW, "setH" : setH, "tileW" : tileW, "tileH" : tileH, "collision" : collision, "map" : tileIDs, "numColumns" : numColumns, "numRows" : numRows}
            json.dump(export, file)


    def saveObjs(self):
        if not onTile:
            objSet[selectedObj].tag = self.entryText.get()
        file2 = asksaveasfile(parent=root, mode='w', title='Choose a file', filetypes = [('JSON File', '*.json')], defaultextension=json, initialdir = os.path.abspath(os.path.join(os.path.dirname( __file__ ), 'Assets', 'Levels')))
        if file2:
            export = {}
            for obj in objSet:
                export[obj.name] = {'tag' : obj.tag, 'xPos' : obj.xPos, 'yPos' : obj.yPos, 'spriteSheet' : obj.path}
            json.dump(export, file2)

        
    def newObj(self):
        global objSet
        name = simpledialog.askstring("Input", "Object Name", parent = self)
        if name is None:
            return False
        imgFile = askopenfile(parent=root,mode='r',title='Choose a file', initialdir = os.path.abspath(os.path.join(os.path.dirname( __file__ ), 'Assets', 'Images')))
        if imgFile is None:
            return False
        objSet.append(Object(name, imgFile.name))
        self.frameObj.destroy()
        self.createObjList()
        if not onTile:
            self.objSelection[selectedObj].manualSelect()

    

    # select tile set
    def openSet(self):
        # take in number of rows and cols
        global img
        global tileW
        global tileH
        global tileSetRows
        global tileSetCols
        global setW
        global setH
        global imgFile
        tempimgFile = askopenfile(parent=root,mode='r',title='Choose a file', initialdir = os.path.abspath(os.path.join(os.path.dirname( __file__ ), 'Assets', 'Images')))
        if tempimgFile is not None:
            img = Image.open(tempimgFile.name)
            # calc tile set dimensions
            temptileW = simpledialog.askinteger("Input", "Tile Width", parent = self)
            if temptileW is None:
                return False
            temptileH = simpledialog.askinteger("Input", "Tile Height", parent = self)
            if temptileH is None:
                return False
            imgFile = tempimgFile.name
            tileW = temptileW
            tileH = temptileH
            setW, setH = img.size
            tileSetCols = int(setW / tileW)
            tileSetRows = int(setH / tileH)
            # update tileSet
            tileSet.clear()
            for tileID in range(0, tileSetCols * tileSetRows):
                left = (tileID % tileSetCols) * tileW
                top = (tileID // tileSetCols) * tileH
                right = left + tileW
                bottom = top + tileH
                tileSet.append(ImageTk.PhotoImage(img.crop((left, top, right, bottom))))
            self.frameMap.destroy()
            self.createFrameMap()
            self.tileSelection[selectedTile].manualSelect()
            self.game.frameMap.destroy()
            self.game.createTileMap()

    # Handles window resize
    def onFrameMapConfigure(self, event):       
        self.canvas.configure(scrollregion=self.frameMap.bbox('all'))
        self.canvasObj.configure(scrollregion=self.frameObj.bbox('all'))


    # handles collision toggle
    def toggleCollision(self):
        if self.collisionToggleVal.get() == 1:
            collision.append(selectedTile)
        elif self.collisionToggleVal.get() == 0:
            collision.remove(selectedTile)




# Game window
class Game(Frame):

    def __init__(self, master, editor):
        super().__init__(master)
        self.master = master
        self.editor = editor
        self.master.geometry("1280x800+405+0")
        self.pack(fill = BOTH, expand = True)
        self.create_widgets()


    def create_widgets(self):
        global tileMap
        tileMap = [[Tile(x, y, self.editor) for x in range(mapW)] for y in range(mapH)]
        # create widgets
        self.canvas = Canvas(self, bg="grey")
        self.createTileMap()
        # Create scrollbars
        vsb = Scrollbar(self, orient="vertical", command=self.canvas.yview)
        self.canvas.configure(yscrollcommand=vsb.set)
        vsb.pack(side=RIGHT, fill=BOTH)
        hsb = Scrollbar(self, orient="horizontal", command=self.canvas.xview)
        self.canvas.configure(xscrollcommand=hsb.set)
        hsb.pack(side=BOTTOM, fill=BOTH)
        self.canvas.pack(side = LEFT, anchor = "nw", fill=BOTH, expand=True)

    # Create a grid of images inside the frame
    def createTileMap(self):
        self.frameMap = Frame(self.canvas)
        self.frameMap.pack(fill = BOTH, expand = True)
        self._frameMap_id = self.canvas.create_window(
                                0, 0,
                                anchor='nw',
                                window=self.frameMap)
        self.frameMap.bind('<Configure>', self.onFrameMapConfigure)
        for row_index in range(mapH):
            for col_index in range(mapW):
                imgFrame = Frame(self.frameMap, width = tileW, height = tileH)
                imgFrame.propagate(False)
                imgFrame.grid(row=row_index, column=col_index, sticky = "nsew")
                imgLabel = Label(imgFrame, image = None)
                imgLabel.bind('<Button-1>', tileMap[row_index][col_index].setTileEvent)
                imgLabel.bind('<Button-3>', tileMap[row_index][col_index].clearEvent)
                tileMap[row_index][col_index].giveLabel(imgLabel)
                tileMap[row_index][col_index].setTile()
                imgLabel.pack(fill=BOTH, expand=True)


    # Handles window resize
    def onFrameMapConfigure(self, event):       
        self.canvas.configure(scrollregion=self.frameMap.bbox('all'))


                


    


### main ###
root = Tk()
# set up tileSet
img = Image.open(imgFile)
for tileID in range(0, tileSetCols * tileSetRows):
    left = (tileID % tileSetCols) * tileW
    top = (tileID // tileSetCols) * tileH
    right = left + tileW
    bottom = top + tileH
    tileSet.append(ImageTk.PhotoImage(img.crop((left, top, right, bottom))))
# start program
root.title("GGD Engine")
editor = Editor(master=root)
editor.mainloop()