Character = 
{
	name = "wall",
	class = "Ball",
	controller = "InputController",
	sprite = "data\\wall.dds",
	fileLocation = "data\\wall.lua",
	initial_position = { -400.0, 0.0, 0.0 },
	constantForce = 0.0000003,
	
	bounding_box = { 
			offset	= { -1.1, 1.2, 3.0 },
			size	= { 10.0, 4.0, 2.0 }
	},

	physics_settings = 
	{
		mass = 2.0,
		drag = 0.0000001
	},

	render_settings = 
	{
		spriteName = { 
			offset	= { 0.0, 400.0, 0.0, 0.0 },
			extents	= { 15.0, 400.0, 0.0, 0.0 }
		},
		sprite_color = { 255, 255, 255, 255 }
	}
}