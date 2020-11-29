# BUG ENGINE

This is an Engine developed for the First Assignment of the Advanced Programming Master by UPC Tech School.
It's a work in progress. For now, it is a simple geometry viewer supporting Drag&Drop that has the feature of loading a Model with a .fbx format and being able to change the texture of this Model. An orbital camera is set up, and it allows you to move around the Engine world and the model. We have added a simple user-friendly UI to modify different basic parameters.  

Here you can find the link to the project: https://github.com/lowysole/BugEngine

Here you have the link to the release: https://github.com/lowysole/BugEngine/releases


## UI Information

In the Engine we have three UI Windows:  

 - Console
  	 - All the Logs from the Texture Loader and Application are written. You can check there if there is any problem importing the textures.
 - Inspector
	 - For now, there is information for the Model and the Camera. 
		- Model: the information of the current model loaded is displayed like the number of vertices, the transformation of the model, and information about the texture.
		- Camera: basic read-only parameters and other modifiable like the position, rotation and the velocity of the camera. See in Camera Controls how to use the camera. 
 - Configuration
	 - Information about the application, hardware and software used and other general configurations of the Engine like background color, windows settings, etc.

## How to Use

### Texture Loading

The logic we use to load the texture is the following:

 - First check on the path described in the FBX
 - Then check on the same folder you loaded the FBX
 - Last, try in “Textures/” folder

You can change the Default Textures directory in the Texture Configuration windows. If you have any problem with the extension of the file, you can also change it in the configuration windows. 

### Camera Controls
The camera controls are a replica of the ones used in Unity
 - While Right-clicking, “WASD” movement and free look around.
 - Mouse wheel to zoom in and out. 
 - Alt+Left click to orbit the object.
 - Alt+Right click to zoom in and out.
 - Press “f” to focus the camera around the current geometry.
 - Holding SHIFT duplicates movement speed. 
	 

## Further developments
Some ideas to improve the Engine are:
  - Add the CameraView to a new UI window
  - Make UI windows adaptable to the change of the aspect ratio dynamically
  - Optimize the loading textures logic
  - Change the way we calculate the bouncing box of the model  
  
  
### Credit
Llorenç Solé Franquesa ~ @lowysole.

GitHub: https://github.com/lowysole/

