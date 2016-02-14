VertexShader
{
	#version 330

	layout(location = 0) in vec4 inPosition;
	layout(location = 1) in vec4 inColour;

	/*layout(binding = 0)*/ uniform Transforms
	{
		mat4 projection;
		mat4 world;
	} transforms;

	out vec4 colour;

	void main()
	{
		colour = inColour;
		gl_Position = transforms.projection * transforms.world * inPosition;
	}
}

FragmentShader
{
    #version 330

    in vec4 colour;
    out vec4 outColour;

    void main()
    {
		outColour = colour;
    }
}
