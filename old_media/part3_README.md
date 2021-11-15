## Final Project - Part 3

## Step 0 - (New!) Engine Architecture Diagram

Your project should have an 'engine architecture' diagram on your website which describes the major components of the engine. See [./media/C4Engine.pdf](./media/C4Engine.pdf) as an example. Note, some IDEs can automatically generate these, though you can draw it yourself and highlight the most important components. Think of this as a high-level diagram you would give an engineer the first day of work so they would know the components and how they interact if they want to modify the engine.

![image](https://user-images.githubusercontent.com/55151815/116157706-7495c680-a6bb-11eb-8f91-7628da17df42.png)

## Step 1 - Documentation

Now that you are going to be maintaining the code for your company for many years, it is important to properly document your code. You will continue to use 'Doxygen' <a href="http://www.doxygen.nl/">(Doxygen webpage)</a> or [Doxypress](https://www.copperspice.com/documentation-doxypress.html) to document the source code and automatically generate .html pages. Your documentation should cover your classes and functions.

An example of a well documented probjects can be found here: 

- https://www.ogre3d.org/docs/api/1.9/
- http://www.horde3d.org/docs/html/_api.html

### Doxygen style comments

Some examples of documentation are listed here: http://www.doxygen.nl/manual/docblocks.html 

Comments within code are in the style of:

```cpp
/*!
 * ... text ...
 */

/*!
 ... text ...
*/

//!
//!... text ...
//!

/*! \brief Brief description.
 *         Brief description continued.
 *
 *  Detailed description starts here.
 */

```
**Note**: A helpful tool to use may be: [Doxywizard](http://www.doxygen.nl/manual/doxywizard_usage.html)

## Step 2 - Build (binary file)
You need to have a compiled binary of your game for your operating system (Either Windows, Mac, or Linux). You can assume a target audience of either a 64-bit Mac, Ubuntu Linux, or a Windows 10 machine. There should additionally be instructions about how to compile your code from source. The compilation should be trivial (running `python build.py` for example, or listing a series of 'apt-get install' in a single command or a script you have built. **Make it trivial** so customers/course staff do not get frustrated :) ).

## Step 3 - Post mortem
A post mortem in games is a look back at what could be improved. Write a brief (2-3 paragraphs) on what could be improved if you had an additional 8 weeks to work on this project. Where would you allocate time, what tools would you build, would you use any different tools, etc.

*Edit here a draft of your post mortem here if you like--the final copy goes in your 1-page .html website. Think of this section as a good 'reflection' for what you can improve on your next project you complete.*

Paragraph 1 - TileMap 

   For our TileMap Editor we wanted to create an environment where the user could easily load up any sprite sheets that they had, and have the tiles or gameobject within that sprite sheet be easily accessible to them within our environment. They would be able to see all of the individual tiles displayed in a grid with the properties for each tile being displayed when you click on that tile. Then being able to paint that tile into the game world, and ideally also be able to paint background tiles into the world. We also wanted to be able to have a displayed hierarchy of all of the different game objects within the level and give the user accessibility to change any aspects of the gameobject that they would want. In our current iteration we provide the user the ability to visually paint their tiles onto a tile map, and also visually place game objects onto the tilemap. We also allow the user to edit specific settings about the gameobjects. If we were given an extra 8 weeks to improve on our current design we would most likely spend most of it working on updating user experience. I believe Tkinter would still work fine for the basics of building up what we already have, and it does it's job well enough for our purpose. The actual work that we would allote most of our time into is cleaning up the UI so it is much simpler and easier for the user to see and edit what information they would like to edit. As the information panel currently only has set information that we pre-determined that the user would be able to edit. It would be nice if the user was able to add any other parameters that they believe that the object or tile should have, such as maybe allowing for moving tiles and such. And being able to add user customizability to the interface so that they could move the windows to specific areas that they feel would be better for their specific work.

Paragraph 2 - Engine

   Our Engine has a lot of work put into it in order to make sure that everything is working properly. It pulls JSON files that are produced from our Editor and is able to turn them into playable levels, and it also reads through a JSON with a list of all of the GameObjects on that level. However that feature was not able to be fully produced in time for this assignment, if there was an extra 8 weeks of time we would be able to properly implement this function fully to be able to incorporate the full capabilities of our editor. 

 
   
Paragraph 3 - Other

## Step 4 - Website

I think it is incredibly important to build a portfolio of your game development works! You will be building a 1 page website(it can be all html) to market your assignment. You can re-use this template for your next project, and potentially other personal projects.

The following are the requirements for a 1-page .html page.

1. Provide a 1 minute video trailer followed by at least 3 screenshots of your game (order matters, video first, then screenshots below)
2. Your documentation (i.e. a link to your doxygen generated files)
3. **An image** of your engine architecture.
4. A link to your binary
5. A short post mortem (i.e. A few paragraphs describing how you would take the project further, what went well, and what you would change if given another month on the project) should be put together on a 1-page .html page. 

This website will be the first place I look to grab your project files and binaries. 

https://j-ober7.github.io/GGDSite/
