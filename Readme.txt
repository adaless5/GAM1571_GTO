Grand Theft Ottawa

General (no marks)
	- Make the map bigger and add some water areas
	- Make extra meshes as needed for the player/cars/boats
	
Movement
	- Allow the player to get in and out of any car/boat by pressing 'E'
	- The player should move slower in water than on roads

Camera
	- The camera should follow the player
	- Change zoom levels when on foot vs in a vehicle
	- Have the camera look ahead of where the car/boat is heading
		
Destruction
	- Cars should be destroyed if they enter water or hit a building with a lot of speed
	- Boats should be destroyed if they end up on land
	- Create a new event to destroy the vehicle
		- The game will only delete the vehicle at the start of the next frame when the event arrives

Vehicle movement:
	- Vehicles should more forward, turn and have velocity/momentum
		- You can grab code from the midterm if you want
		- The midterm player turns but doesn't have momentum

Checkpoint races
	- Add one or more cars to each road tile and one or more boats to each water tile
	- Create a timer variable that starts at 10 seconds
	- Show the timer using ImGui
	- Spawn a checkpoint box randomly on your map (smaller than a tile and not on buildings)
	- Using AABBs, collide with checkpoints to add 5 seconds to the timer and move the checkpoint randomly
	- Don't worry about rotating the player/car AABB
	- No need to handle running out of time
	
Extra - General Polish
	- Display the timer without imgui
	- Put delays on the destruction of vehicles, have them break-down before being destroyed/removed from the game
	- Handle camera transitions well, so it never pops between zoom levels or target location
	- Handle running out of time
	- More...