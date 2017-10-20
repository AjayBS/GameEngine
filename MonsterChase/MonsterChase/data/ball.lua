
Character = 
{
	name = "ball",
	class = "Ball",
	controller = "InputController",
	sprite = "data\\ball.dds",
	fileLocation = "data\\ball.lua",
	initial_position = { -350.0, 200.0, 0.0 },
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
			offset	= { 0.0, 15.0, 0.0, 0.0 },
			extents	= { 16.0, 16.0, 0.0, 0.0 }
		},
		sprite_color = { 255, 255, 255, 255 }
	}
}