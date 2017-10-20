Character = 
{
	name = "second_paddle",
	class = "Enemy",
	controller = "InputController",
	sprite = "data\\paddle.dds",
	fileLocation = "data\\second_paddle.lua",
	initial_position = { -350.0, -100.0, 0.0 },
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
			offset	= { 0.0, 73.0, 0.0, 0.0  },
			extents	= { 14.0, 73.0, 0.0, 0.0 }
		},
		sprite_color = { 255, 255, 255, 255 }
	}
}
