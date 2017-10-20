Character = 
{
	name = "wall3",
	class = "Dummy",
	controller = "InputController",
	sprite = "data\\Dummy.dds",
	fileLocation = "data\\wall3.lua",
	initial_position = { -600.0, 600.0, 0.0 },
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