# OpenGLRenderer
An unfinished project I began in my second year of high school and stopped working on it after about 4 or 5 months of work.
This is a pseudo-engine that uses OpenGL to render objects in a (hopefully) orderly fashion, it is written in C++. It contains most of the basics of a game engine such as Unity and Unreal (A render panel, a hierarchy, an inspector, etc..). It also has a rather sloppy attempt at reading and writing asset files for the engine, there's a lot of room for improvement.

# Resource Manager
The resource manager is responsible for keeping track of the various assets used in the engine (Textures, 3D models, Shaders, etc...) such that it optimises the process of loading these assets in and out of the engine, in addition to keeping track of these assets in memory. The purpose is to not have the same asset loading more than once in memory, but to have assets of the same resource be made into one, which is shared across the objects who use them. This also optimizes the process of loading in an asset that newly-created object uses. If the asset is already one which another separate object uses, the newly-created object simply uses that asset as it already exists in memory. Otherwise, the asset is simply created anew.

These resources are packaged into asset files. These asset files contain:
    - The filepath of the resource itself (.obj for models, .png/.jpg for textures etc...)
    - The unique ID of the asset
    - The asset type (Shader, Texture, etc...)
    - Any other data that is relevant for the asset

One of the issues is that the asset files - which are responsible for referencing the file path for the resource itself - write the filepaths in raw "C:\Users\fahad...etc" rather than a local path. I also stopped working on this project around the same time I tried working on a material system, which would've been responsible for creating assets of a given set of shaders with specific shader variables (à la Unity). I can't remember what I was having trouble with exactly but I'm sure whatever I did was sub-optimal.

# Graphic User Interface
The engine uses the basic ImGui interface for the GUI, in addition to ImGuizmo for the 3D transform manipulation. There are quite a few windows. Firstly there's the render window, which shows what is being rendered. In addition to an inspector window, which shows the data of any given selected objects components/variables. A hierarchy panel, which shows the list of objects that exist in the scene and can create or delete objects. And a content browser panel, which shows the content of the files in the local repo, it's purpose is to be an interface to edit the resource and asset files.

# Elements
The engine is comprised of many parts and elements. First off, there are the basic OpenGL objects, these are the essentially the elements that OpenGL uses to load relevant data into the VRAM (GPU memory) and execute GPU code. They are abstracted nicely into classes and such. There are also the slightly more abstract parts, such as the camera class, which - as you might guess - is responsible for manipulating the camera position depending on user input using generic WASD movement and mouse control.

# Basic Order
If you are familiar with Unity you will be no stranger to how this is set up. Essentially any given scene is made up of objects (referred to as GameObjects). These objects are comprised of multiple components. First there is the transform component, which is responsible for the objects position, rotation, and scale in the scene. Second there is the mesh component, which is responsible for handling *what* mesh (3D model) the object has. Lastly there's the material component, which is responsible for *how* the object's mesh is rendered on-screen. It contains a shader object, shaders are essentially GPU code that dictate what color pixel is shown in the screen given an input from an object. 


#### Vertex Shaders
The first piece of data that's passed onto shaders as input is usually vertex data, which is derived from the object's mesh or model. That vertex data is manipulated in code to be shown how the programmer would like for it be shown, or more particularly *where* the pixels should be on-screen. In this case, the vertex data of the mesh is manipulated according to the transform of the object, then to the view transform of the camera. Essentially, we are placing the mesh in the place it should be on the screen, according to where the object is located in the scene, and where the camera is positioned.

#### Fragment Shaders
After we've concluded *where* the pixels should be on screen, we now must program *what* color the pixel should be. This is handled by the fragment shader, also known as the pixel shader. Probably the most fun part of graphics programming, fragment shaders give programmers much flexibility in how they can be manipulated. They usually take in as input, data that should be relevant to the color of the given pixel. That includes the object's allocated textures (which are given in integer form), the UV data or the data responsible for *how* the texture is mapped onto the 3D model, in addition to various lights that may exist in the scene and affect the way the object appears to the viewer. There are also other variables that exist in shader code that are not fixed, but rather things that the user can manipulate as they see fit. These shader or material variables appear in the inspector panel for the users to toy around with.

And that is essentially how the engine works, a set of game objects in a scene, each game object has a transform, mesh, and material component that can be changed as the user sees fit, and a camera for the user to move the scene around in. In addition to a resource manager designed to optimise the process of loading and unloading the resources into the engine.

# Conclusion
The project is deeply flawed, but still, this was a fairly major technical accomplishment for me to do in high school. I may even pick it up again in the future, because the framework overall is quite solid.
