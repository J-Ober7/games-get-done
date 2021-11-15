import sys
sys.path.append('./bin')

import mygameengine


def generateBGMap(tileMap):
    tileMap.background = True
    for y in range(tileMap.m_MapY):
        for x in range(tileMap.m_MapX):
            tileMap.SetTile(x,y,26)

class EnemyAIComponent(mygameengine.Component):
    def __init__(self):
        mygameengine.Component.__init__(self)
    

    def Update(self, gameObject):
        print("update is being called")
        self.parent = gameObject

        self.parent.position.x += self.parent.m_xVel

    # TODO add a isActive field to GameObject to prevent rendering and updating as necessary
    def handleCollision(self):
        collisionList = self.parent.collisions
        for i in range(len(collisionList)):
            currCollision = collisionList[i];
            if currCollision.type == mygameengine.CollisionType.Right:
                self.parent.m_xVel = -abs(self.parent.m_xVel)
            elif currCollision.type == mygameengine.CollisionType.Left:
                self.parent.m_xVel = abs(self.parent.m_xVel)
            elif currCollision.type == mygameengine.CollisionType.Bottom and currCollision.parentTag == "player":
                print(" enemy dead ");
                self.parent.isActive = False



engine = mygameengine.GGDProgram(1280, 720)

# TILE MAPS -------------------------s-----------------------------------------------------

# tile map background

tileMapObject = mygameengine.GameObject()
engine.initializeRendering(tileMapObject)

tmComp = engine.requestComponent("tilemap")
tmComp.init("Assets/Images/Tiles1.bmp", 8,8,64,64,64,64,80,40,.5)
generateBGMap(tmComp)
#tileMapObject.AddComponent(tmComp)

# tile map foreground
foreground = mygameengine.GameObject()
engine.initializeRendering(foreground)
temp = engine.loadJSON("Assets/Levels/Tilemap2.json", 64, 64)
temp.debug = True
foreground.AddComponent(temp)

foreground2 = mygameengine.GameObject()
foreground2.init(1200, 0, 0, 0, 0, 0, "map")
engine.initializeRendering(foreground2)
temp2 = engine.loadJSON("Assets/Levels/Tilemap2.json", 64, 64)
temp2.debug = True
foreground2.AddComponent(temp2)

#foregroundTM = engine.requestComponent("tilemap")
#foregroundTM.init("Assets/Images/Tiles1.bmp", 8,8,64,64,64,64,80,40)

#for x in range(15):
#    foregroundTM.SetTile(x,10,1)
#    foregroundTM.SetTile(x,11,1)
#    foregroundTM.SetTile(x,12,1)
#foregroundTM.SetTile(8,9,1)
#foregroundTM.addCollidableTile(1)


# BACKGROUND--------------------------------------------------------------------------------

#background image
background = mygameengine.GameObject()
background.init(0, 0, 2000, 1500, 0, 0)
engine.initializeRendering(background)

backgroundSprite = engine.requestComponent("sprite")
backgroundSprite.init(0,0,2000,1500,0,1,400,300,1,1,"./Assets/Images/Midleground.bmp", .5)
background.AddComponent(backgroundSprite)


# GAMEOBJECTS  ------------------------------------------------------------------------------

# add sprite component and initialize
player = mygameengine.GameObject()
player.init(400, 560, 72, 72, 1, 0, "enemy")
engine.initializeRendering(player)

player = mygameengine.GameObject()
player.init(400, 360, 72, 72, 1, 0, "enemy")
engine.initializeRendering(player)

spriteComponent = engine.requestComponent("sprite")
spriteComponent.init(400, 560, 72, 72, 0, 27, 75,87,4,7, "./Assets/Images/sprite.bmp")
player.AddComponent(spriteComponent)

playerCollision = engine.requestComponent("collision")
player.AddComponent(playerCollision)
playerCollision.parent = player

enemyComp = EnemyAIComponent()
player.AddComponent(enemyComp)

player2 = mygameengine.GameObject()
player2.init(200, 100, 88, 88, 0, 0, "player")
engine.initializeRendering(player2)

player2sprite = engine.requestComponent("sprite")
player2sprite.init(100,100,200,88,21,30,100,44,1,41,"./Assets/Images/spritesheet.bmp")
player2sprite.SetSpriteOffset(-56, 0);
player2.AddComponent(player2sprite)

player2sprite.AddAnimation("Idle", 21, 30)
player2sprite.AddAnimation("Death", 6, 15)
player2sprite.AddAnimation("Run", 33, 40)
player2sprite.AddAnimation("Fall", 16, 17)
player2sprite.AddAnimation("Jump", 31, 32)
player2sprite.AddAnimation("Attack", 0, 5)
player2sprite.animationSpeed = 5

# transform components
p2Transform = engine.requestComponent("transform")
player2.AddComponent(p2Transform)

#physics components
p2Physics = engine.requestComponent("physics")
player2.AddComponent(p2Physics)
player2.m_yAcel = 0
p2Physics.m_Gravity = -2;
p2Physics.m_MaxGravity = -4;
p2Physics.m_MaxYVel = -10;

#collision component
p2Collision = engine.requestComponent("collision")
p2Collision.init(player2)
p2Collision.isMovable = True
player2.AddComponent(p2Collision)

batEnemy = mygameengine.GameObject()
batEnemy.init(1000,570,70,40,-3,0,"enemy")
engine.initializeRendering(batEnemy)

batEnemySprite = engine.requestComponent("sprite")
batEnemySprite.init(1000,570,70,40,0,21,35,20,1,22,"./Assets/Images/Bat_flying_strip22.bmp")
batEnemySprite.SetSpriteOffset(0,0)
batEnemySprite.animationSpeed = 5;
batEnemy.AddComponent(batEnemySprite)

batEnemyComp = EnemyAIComponent()
batEnemy.AddComponent(batEnemyComp)

batCollision = engine.requestComponent("collision")
batCollision.init(batEnemy)
batEnemy.AddComponent(batCollision)

player2.debug = True
batEnemy.debug = True

running = True

player.isActive = False
playerMoveLeft = False
playerMoveRight = False
playerRise = False
print("starting game")

# GAME LOOP -------------------------------------------------------------------------------------

while running:
    engine.startFrameLimit()
    # ----------------------------------- UPDATE--------------------------------------
    if player2.isGrounded:
        player2sprite.SetFrames("Idle")
    engine.input()
    for event in engine.eventLog:
        if event.type == "quit":
            running = False
            break;
        if event.type == "key":
            #print(event.id + " key up " + str(event.isDown))
            if event.id == "D" and event.isDown:
                playerMoveRight = True
            elif event.id == "D":
                playerMoveRight = False
            elif event.id == "A" and event.isDown:
                playerMoveLeft = True
            elif event.id == "A":
                playerMoveLeft = False
            
            if event.id == "Space" :
                if (player2.isGrounded):
                    player2sprite.SetFrames("Jump")
                    player2.m_yVel = 40
                    player2.isGrounded = False
            #elif not event.isDown:
        if event.type == "mouse":
            print(event.id + " mouse up " + str(event.isDown) + " x: " + str(event.x) + " y: " + str(event.y))

    if not player2.isGrounded:
        if player2.m_yVel < 0:
            playerRise = False
            player2sprite.SetFrames("Fall")
        elif player2.m_yVel > 0:
            playerRise = True
            player2sprite.SetFrames("Death")

    if player2.isGrounded and playerMoveRight and playerMoveLeft:
        player2sprite.SetFrames("Idle")
        player2.m_xVel = 0
    elif player2.isGrounded and playerMoveRight and not playerMoveLeft:
        player2sprite.SetFrames("Run")
        player2.m_xVel = 5
        player2sprite.FlipHorizontal(False)
    elif player2.isGrounded and playerMoveLeft and not playerMoveRight:
        player2sprite.SetFrames("Run")
        player2.m_xVel = -5
        player2sprite.FlipHorizontal(True)
    elif not player2.isGrounded and playerMoveLeft and not playerMoveRight:
        print("moving left in the air")
        player2.m_xVel = -5
        player2sprite.FlipHorizontal(True)
    elif not player2.isGrounded and not playerMoveLeft and playerMoveRight:
        print("moving right in the air")
        player2.m_xVel = 5
        player2sprite.FlipHorizontal(False)
    elif playerMoveLeft and playerMoveRight:
        player2.m_xVel = 0
    elif not playerMoveRight and not playerMoveLeft:
        if player2.isGrounded:
            player2sprite.SetFrames("Idle")
        player2.m_xVel = 0

    #player.update()
    # TODO need to make a separate camera update function since collision detection uses current positions
    engine.camera.x = max(player2.GetXPosition() - (int)(1280/2), 0)
    engine.camera.y = max(player2.GetYPosition() - (int)(720/2), 0)

    if player2.GetXPosition() + player2.m_xVel < 0:
        player2.m_xVel = 0
    if player2.position.y + player2.m_yVel < 0:
        player2.m_yVel = 0


    tileMapObject.update()
    background.update()
    foreground.update()
    foreground2.update()
    player2.update()
    batEnemy.update()
    #player.update()
    engine.update()
    batEnemyComp.handleCollision()
    player2.clearCollisions()
    #player.clearCollisions()

    engine.UpdateCamera()

    # ----------------------------------- RENDERING--------------------------------------    
    engine.RenderClear()
    tileMapObject.render()
    background.render()
    foreground.render()
    foreground2.render()
    #player.render()
    player2.render()
    batEnemy.render()
    #player.render()
    engine.RenderPresent()
    
    # Frame capping
    engine.closeFrameLimit(30)

engine.Shutdown()
print("game engine shut down")